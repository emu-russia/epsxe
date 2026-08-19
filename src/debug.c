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
