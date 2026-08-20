#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
int ( *cdrom_deinit_cb)();
static unsigned char console_log_enabled;
static unsigned char console_log_flush_pending;
static unsigned char dynarec_active;
static FILE *error_log_file;
static unsigned int last_tick_count;
int ( *spu_destroy_cb)();

#include "debug.h"

/** Console output handle, set by alloc_console(). */
static HANDLE h_console_output;

int alloc_console(void)
{
    HANDLE std_handle = INVALID_HANDLE_VALUE;

    if (console_allocated)
    {
        AllocConsole();
        SetConsoleTitleA("ePSXe - Enhanced PSX emulator");
        std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        h_console_output = std_handle;
    }
    return (char)std_handle;
}

static int free_console(void)
{
    char allocated;

    allocated = console_allocated;
    if (console_allocated)
        return FreeConsole();
    return allocated;
}

unsigned long get_tick_count(void)
{
    unsigned long tick;

    tick = GetTickCount();
    last_tick_count = tick;
    return tick;
}

void set_console_log_flush_pending(void)
{
    console_log_flush_pending = 1;
}

static char check_and_clear_console_log_flush_pending(void)
{
    char was_pending;

    was_pending = console_log_flush_pending;
    if (console_log_flush_pending)
        console_log_flush_pending = 0;
    return was_pending;
}

void dbg_print_no_flush(const char *Format, ...)
{
    char *buf;
    DWORD chars_written;
    va_list arg_list;

    va_start(arg_list, Format);
    buf = (char *)malloc(0x8000u);
    if (buf) {
        vsprintf(buf, Format, arg_list);
        fprintf(stdout, "%s", buf);
        if (console_allocated)
            WriteConsoleA(h_console_output, buf, (DWORD)strlen(buf), &chars_written, nullptr);
        free(buf);
    }
}

void ui_error(const char *Format, ...)
{
    char *buf;
    va_list arg_list;

    va_start(arg_list, Format);
    sio_memcard_both_save();
    net_close();
    nullsub_1();
    if (spu_destroy_cb)
        spu_destroy_cb(0);
    if (dynarec_active == 1)
        dynarec_deinit();
    gpu_destroy();
    if (cdrom_deinit_cb)
        cdrom_deinit_cb(0);
    ppf_free();
    check_and_clear_console_log_flush_pending();
    if (console_log_flush_pending)
    {
        buf = (char *)malloc(0x8000u);
        vsprintf(buf, Format, arg_list);
        fprintf(stdout, "%s", buf);
        if (console_allocated)
            WriteConsoleA(h_console_output, buf, (DWORD)strlen(buf), nullptr, nullptr);
        free(buf);
    }
    else
    {
        buf = (char *)malloc(0x8000u);
        vsprintf(buf, Format, arg_list);
        printf("%s", buf);
        free(buf);
    }
    check_and_clear_console_log_flush_pending();
    if (error_log_file)
        fclose(error_log_file);
    nullsub_1();
    free_console();
    exit(0);
}

void fatal_error_with_message_box(const char *Format, ...)
{
    char *buf;
    va_list arg_list;

    va_start(arg_list, Format);
    sio_memcard_both_save();
    net_close();
    nullsub_1();
    if (spu_destroy_cb)
        spu_destroy_cb(0);
    if (dynarec_active == 1)
        dynarec_deinit();
    buf = (char *)malloc(0x8000u);
    vsprintf(buf, Format, arg_list);
    fprintf(stdout, "%s", buf);
    MessageBoxA(nullptr, buf, "Error running ePSXe", 0x10u);
    free(buf);
    gpu_destroy();
    if (cdrom_deinit_cb)
        cdrom_deinit_cb(0);
    ppf_free();
    check_and_clear_console_log_flush_pending();
    if (error_log_file)
        fclose(error_log_file);
    free_console();
    exit(1);
}

int dbg_print(const char *Format, ...)
{
    char *buf;
    DWORD chars_written;
    va_list arg_list;

    va_start(arg_list, Format);
    buf = (char *)malloc(0x8000u);
    if (buf) {
        vsprintf(buf, Format, arg_list);
        fprintf(stdout, "%s", buf);
        if (console_allocated)
            WriteConsoleA(h_console_output, buf, (DWORD)strlen(buf), &chars_written, nullptr);
        free(buf);
    }
    return fflush(stdout);
}

char reopen_console_log(void)
{
    if (console_log_enabled)
    {
        if (!console_log_handle)
        {
            console_log_handle = fopen("console.log", "a");
        }
    }
    return (char)console_log_enabled;
}

void dump_log(FILE *Stream, const char *Format, ...)
{
    char *buf;
    va_list arg_list;

    va_start(arg_list, Format);
    buf = (char *)malloc(0x8000u);
    if (buf) {
        vsprintf(buf, Format, arg_list);
        if (Stream && console_log_enabled)
            fprintf(Stream, "%s", buf);
        free(buf);
    }
}

#ifdef _DEBUG
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#include <crtdbg.h>
#include <rtcapi.h>

/*
 * Debug-build crash reporter (issue #28 debugging session).
 * Writes the exception and a symbolized stack trace to "crash.log"
 * in the working directory, then terminates the process.
 */

/* Log /RTC run-time-check failures (uninitialized variable reads etc.)
 * instead of popping the "Microsoft Visual C++ Runtime Library" dialog. */
static int __cdecl epsxe_rtc_error_func(int errorType, const char *filename, int linenumber)
{
    void *frames[16];
    USHORT nframes = RtlCaptureStackBackTrace(0, 16, frames, NULL);
    HANDLE process = GetCurrentProcess();
    FILE *f = fopen("rtc.log", "a");
    if (f) {
        int i;
        fprintf(f, "RTC error %d at %s:%d\n", errorType, filename ? filename : "?", linenumber);
        for (i = 2; i < (int)nframes; ++i) {
            char symbuf[sizeof(SYMBOL_INFO) + 1024];
            SYMBOL_INFO *sym = (SYMBOL_INFO *)symbuf;
            DWORD64 disp = 0;
            if ((ULONG_PTR)frames[i] < 0x10000)
                break;
            sym->SizeOfStruct = sizeof(SYMBOL_INFO);
            sym->MaxNameLen = 1024;
            if (SymFromAddr(process, (DWORD64)(ULONG_PTR)frames[i], &disp, sym))
                fprintf(f, "  0x%08llX  %s+0x%llX\n", (DWORD64)(ULONG_PTR)frames[i], sym->Name, disp);
            else
                fprintf(f, "  0x%08llX\n", (DWORD64)(ULONG_PTR)frames[i]);
        }
        fclose(f);
    }
    return 0; /* continue execution instead of showing the dialog */
}

/* Log invalid CRT parameters (memcpy size etc.) instead of popping the
 * "Microsoft Visual C++ Runtime Library - Runtime Error!" dialog. */
static void __cdecl epsxe_invalid_parameter_handler(
    const wchar_t *expression, const wchar_t *function,
    const wchar_t *file, unsigned int line, uintptr_t reserved)
{
    FILE *f = fopen("crash.log", "a");
    if (f) {
        fprintf(f, "=== Invalid CRT parameter ===\n");
        if (expression) fprintf(f, "Expression: %ls\n", expression);
        if (function)   fprintf(f, "Function:   %ls\n", function);
        if (file)       fprintf(f, "File:       %ls:%u\n", file, line);
        else            fprintf(f, "File:       <unknown>:%u\n", line);
        fclose(f);
    }
    _set_invalid_parameter_handler(epsxe_invalid_parameter_handler);
}
static LONG WINAPI epsxe_crash_handler(struct _EXCEPTION_POINTERS *ep)
{
    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    FILE *f;
    STACKFRAME64 frame;
    CONTEXT context;
    DWORD machine = IMAGE_FILE_MACHINE_I386;
    int depth = 0;

    f = fopen("crash.log", "a");
    if (f) {
        fprintf(f, "=== ePSXe crash at %lu ===\n", (unsigned long)GetTickCount());
        fprintf(f, "Exception code: 0x%08lX\n", (unsigned long)ep->ExceptionRecord->ExceptionCode);
        fprintf(f, "Faulting address: 0x%08lX\n", (unsigned long)ep->ExceptionRecord->ExceptionAddress);
        fflush(f);
    }

    context = *ep->ContextRecord;

    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
    SymInitialize(process, NULL, TRUE);

    memset(&frame, 0, sizeof(frame));
    frame.AddrPC.Offset = context.Eip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Ebp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context.Esp;
    frame.AddrStack.Mode = AddrModeFlat;

    if (f)
        fprintf(f, "Stack trace:\n");
    while (StackWalk64(machine, process, thread, &frame, &context, NULL,
                       SymFunctionTableAccess64, SymGetModuleBase64, NULL)) {
        DWORD64 addr = frame.AddrPC.Offset;
        char symbuf[sizeof(SYMBOL_INFO) + 1024];
        SYMBOL_INFO *sym = (SYMBOL_INFO *)symbuf;
        DWORD64 disp = 0;
        IMAGEHLP_LINE64 line;
        DWORD ldisp = 0;

        if (addr == 0)
            break;
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = 1024;
        if (f) {
            if (SymFromAddr(process, addr, &disp, sym)) {
                fprintf(f, "  0x%08llX  %s+0x%llX", addr, sym->Name, disp);
                memset(&line, 0, sizeof(line));
                line.SizeOfStruct = sizeof(line);
                if (SymGetLineFromAddr64(process, addr, &ldisp, &line))
                    fprintf(f, "  [%s:%lu]", line.FileName, line.LineNumber);
                fprintf(f, "\n");
            } else {
                fprintf(f, "  0x%08llX\n", addr);
            }
            fflush(f);
        }
        if (++depth >= 32)
            break;
    }

    if (f)
        fclose(f);
    SymCleanup(process);
    fflush(stdout);
    TerminateProcess(process, 0xC0000005u);
    return EXCEPTION_EXECUTE_HANDLER;
}

void install_crash_handler(void)
{
    /* Redirect debug-CRT error/assertion reports (heap corruption, asserts)
     * from the modal dialog to stderr so the session does not block on a
     * "Runtime Error!" message box. */
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _set_invalid_parameter_handler(epsxe_invalid_parameter_handler);
    _RTC_SetErrorFunc(epsxe_rtc_error_func);
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
    SymInitialize(GetCurrentProcess(), NULL, TRUE);
    SetUnhandledExceptionFilter(epsxe_crash_handler);
}
#endif
