/*
 * debug_demo.c - Demonstrates all functions from src/debug.c
 *
 * Standalone Win32 application with stub implementations of
 * external ePSXe dependencies.
 *
 * Build: cl /Fe:debug_demo.exe debug_demo.c user32.lib kernel32.lib gdi32.lib
 */

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "../../src/debug.h"

/* ========================================================================== */
/* Stub implementations for external ePSXe symbols                            */
/* ========================================================================== */

unsigned char console_allocated = 1;
unsigned char console_log_enabled = 1;
unsigned char console_log_flush_pending = 0;
unsigned long last_tick_count = 0;
unsigned char dynarec_active = 0;
unsigned int console_log_handle = NULL;
FILE *error_log_file = NULL;
FILE __stdout;

int (__cdecl *spu_destroy_cb)(unsigned long) = NULL;
int (__cdecl *cdrom_deinit_cb)(unsigned long) = NULL;

void nullsub_1(void) {}
void sio_memcard_both_save(void) {}
HMODULE net_close(void) { return NULL; }
HMODULE gpu_destroy(void) { return NULL; }
void ppf_free(void) {}
void dynarec_deinit(void) {}

/* ========================================================================== */
/* Demo state                                                                 */
/* ========================================================================== */

#define LOG_BUF_SIZE 4096
#define BTN_COUNT 11
#define ID_LOG   100
#define ID_STAT  101

static char log_buffer[LOG_BUF_SIZE];
static int log_pos = 0;

static void log_append(const char *text)
{
    int len = (int)strlen(text);
    if (log_pos + len + 1 < LOG_BUF_SIZE) {
        memcpy(log_buffer + log_pos, text, (size_t)len);
        log_pos += len;
        log_buffer[log_pos] = '\0';
    }
}

static void log_append_fmt(const char *fmt, ...)
{
    char tmp[512];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(tmp, fmt, ap);
    va_end(ap);
    log_append(tmp);
}

static void log_clear(void)
{
    log_pos = 0;
    log_buffer[0] = '\0';
}

static const char *bool_str(int val)
{
    return val ? "true" : "false";
}

/* ========================================================================== */
/* Button IDs and texts                                                       */
/* ========================================================================== */

static const int btn_ids[BTN_COUNT] = {
    200, 201, 202, 203, 204,
    205, 206, 207, 208, 209,
    210
};

static const char *btn_texts[BTN_COUNT] = {
    "1. alloc_console",
    "2. free_console",
    "3. get_tick_count",
    "4. set_flush_pending",
    "5. check_flush_pending",
    "6. reopen_console_log",
    "7. dbg_print",
    "8. dbg_print_no_flush",
    "9. dump_log",
    "10. fatal_error",
    "11. ui_error"
};

/* ========================================================================== */
/* Command handlers                                                           */
/* ========================================================================== */

static void on_alloc_console(HWND hwnd)
{
    int ret = alloc_console();
    log_append(">>> alloc_console()\r\n");
    log_append_fmt("    console_allocated = %s\r\n", bool_str(console_allocated));
    log_append_fmt("    return = %d\r\n", ret);
    log_append("\n");
}

static void on_free_console(HWND hwnd)
{
    int ret = free_console();
    log_append(">>> free_console()\r\n");
    log_append_fmt("    console_allocated = %s\r\n", bool_str(console_allocated));
    log_append_fmt("    return = %d\r\n", ret);
    log_append("\n");
}

static void on_get_tick_count(HWND hwnd)
{
    unsigned long tick = get_tick_count();
    log_append(">>> get_tick_count()\r\n");
    log_append_fmt("    last_tick_count = %lu\r\n", last_tick_count);
    log_append_fmt("    return = %lu\r\n", tick);
    log_append("\n");
}

static void on_set_flush_pending(HWND hwnd)
{
    set_console_log_flush_pending();
    log_append(">>> set_console_log_flush_pending()\r\n");
    log_append_fmt("    console_log_flush_pending = %s\r\n", bool_str(console_log_flush_pending));
    log_append("\n");
}

static void on_check_flush_pending(HWND hwnd)
{
    char was = check_and_clear_console_log_flush_pending();
    log_append(">>> check_and_clear_console_log_flush_pending()\r\n");
    log_append_fmt("    was_pending = %s\r\n", bool_str(was));
    log_append_fmt("    console_log_flush_pending = %s\r\n", bool_str(console_log_flush_pending));
    log_append("\n");
}

static void on_reopen_console_log(HWND hwnd)
{
    char ret = reopen_console_log();
    log_append(">>> reopen_console_log()\r\n");
    log_append_fmt("    console_log_enabled = %s\r\n", bool_str(console_log_enabled));
    log_append_fmt("    console_log_handle = %p\r\n", (void *)console_log_handle);
    log_append_fmt("    return = %d\r\n", ret);
    log_append("\n");
}

static void on_dbg_print(HWND hwnd)
{
    int ret = dbg_print("dbg_print demo: value=%d, string=%s, float=%.2f\r\n", 42, "hello", 3.14);
    log_append(">>> dbg_print(\"dbg_print demo: value=42, string=hello, float=3.14\")\r\n");
    log_append_fmt("    fflush return = %d\r\n", ret);
    log_append("\n");
}

static void on_dbg_print_no_flush(HWND hwnd)
{
    dbg_print_no_flush("dbg_print_no_flush demo: no flush yet\r\n");
    log_append(">>> dbg_print_no_flush(\"dbg_print_no_flush demo: no flush yet\")\r\n");
    log_append("    (output not flushed - use dbg_print to flush)\r\n");
    log_append("\n");
}

static void on_dump_log(HWND hwnd)
{
    FILE *tmp = fopen("demo_dump.log", "w");
    if (tmp) {
        dump_log(tmp, "dump_log demo: writing to file\r\n");
        fclose(tmp);
        log_append(">>> dump_log(FILE*, \"dump_log demo: writing to file\")\r\n");
        log_append("    wrote to demo_dump.log\r\n");
        log_append("\r\n");
    } else {
        log_append(">>> dump_log(FILE*, ...) - FAILED to open file\r\n\r\n");
    }
}

static void on_fatal_error_with_msgbox(HWND hwnd)
{
    log_append(">>> fatal_error_with_message_box demo\r\n");
    log_append("    Calling fatal_error_with_message_box...\r\n");
    log_append("    (This will show a message box and exit the demo)\r\n\r\n");

    fatal_error_with_message_box("Demo fatal error: this is a test message box from debug_demo.exe");
}

static void on_ui_error(HWND hwnd)
{
    log_append(">>> ui_error demo\r\n");
    log_append("    Calling ui_error...\r\n");
    log_append("    (This will clean up and exit the demo)\r\n\r\n");

    ui_error("Demo UI error: this is a test error message from debug_demo.exe");
}

/* ========================================================================== */
/* Button creation helper                                                     */
/* ========================================================================== */

static HWND create_button(HWND parent, int id, int x, int y, int w, int h, const char *text)
{
    return CreateWindowExA(
        0,
        "BUTTON",
        text,
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        x, y, w, h,
        parent,
        (HMENU)(LONG_PTR)id,
        GetModuleHandle(NULL),
        NULL
    );
}

/* ========================================================================== */
/* Window procedure                                                           */
/* ========================================================================== */

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:
    {
        int btn_width = 200;
        int btn_height = 18;
        int gap = 10;
        int i;
        int col, row;
        int x, y;

        /* Buttons: top area (y=10..100) */
        for (i = 0; i < BTN_COUNT; i++) {
            col = i % 3;
            row = i / 3;
            x = 10 + col * (btn_width + gap);
            y = 10 + row * (btn_height + gap);

            create_button(hwnd, btn_ids[i], x, y, btn_width, btn_height, btn_texts[i]);
        }

        /* Log edit control: middle area (y=115..bottom-20) */
        CreateWindowExA(
            WS_EX_CLIENTEDGE,
            "EDIT",
            NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
            0, 115, 0, 0,
            hwnd,
            (HMENU)(LONG_PTR)ID_LOG,
            GetModuleHandle(NULL),
            NULL
        );

        /* Status bar: bottom */
        CreateWindowExA(
            0,
            "StatusBar",
            "Ready",
            WS_CHILD | WS_VISIBLE,
            0, 0, 0, 0,
            hwnd,
            (HMENU)(LONG_PTR)ID_STAT,
            GetModuleHandle(NULL),
            NULL
        );

        /* Initial log text */
        log_append("ePSXe Debug Module Demo\r\n");
        log_append("========================\r\n\r\n");
        log_append("Click buttons to demonstrate each debug function.\r\n");
        log_append("Console output also appears in the Windows console.\r\n\r\n");

        break;
    }

    case WM_SIZE:
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        HWND h_log = GetDlgItem(hwnd, ID_LOG);
        HWND h_stat = GetDlgItem(hwnd, ID_STAT);

        /* Log fills middle area */
        SetWindowPos(h_log, NULL, 0, 115, rc.right, rc.bottom - 135, SWP_NOZORDER);
        /* Status bar at bottom */
        SetWindowPos(h_stat, NULL, 0, rc.bottom - 20, rc.right, 20, SWP_NOZORDER);
        break;
    }

    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        int i;

        /* Find which button was clicked and update status bar */
        for (i = 0; i < BTN_COUNT; i++) {
            if (id == btn_ids[i]) {
                char buf[256];
                sprintf(buf, "Executed: %s", btn_texts[i]);
                SendMessage(GetDlgItem(hwnd, ID_STAT), WM_SETTEXT, 0, (LPARAM)buf);
                break;
            }
        }

        /* Dispatch to handler */
        switch (id) {
        case 200:  on_alloc_console(hwnd); break;
        case 201:  on_free_console(hwnd); break;
        case 202:  on_get_tick_count(hwnd); break;
        case 203:  on_set_flush_pending(hwnd); break;
        case 204:  on_check_flush_pending(hwnd); break;
        case 205:  on_reopen_console_log(hwnd); break;
        case 206:  on_dbg_print(hwnd); break;
        case 207:  on_dbg_print_no_flush(hwnd); break;
        case 208:  on_dump_log(hwnd); break;
        case 209:  on_fatal_error_with_msgbox(hwnd); break;
        case 210:  on_ui_error(hwnd); break;
        default:
            break;
        }

        /* Update log display only when a button was clicked */
        if (i < BTN_COUNT) {
            HWND h_log = GetDlgItem(hwnd, ID_LOG);
            if (h_log) {
                SendMessage(h_log, EM_SETSEL, -1, -1);
                SendMessage(h_log, EM_REPLACESEL, 0, (LPARAM)"");
                SendMessage(h_log, EM_REPLACESEL, 1, (LPARAM)log_buffer);
            }
        }

        /* NOTE: without the above guard updating the edit control triggers EN_UPDATE/WM_COMMAND
           which re-enters this handler and caused a stack overflow. */

        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }

    return 0;
}

/* ========================================================================== */
/* WinMain                                                                    */
/* ========================================================================== */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char cls_name[] = "DebugDemoClass";
    WNDCLASSA wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszClassName = cls_name;

    if (!RegisterClassA(&wc))
        return 1;

    hwnd = CreateWindowExA(
        0,
        cls_name,
        "ePSXe Debug Module Demo",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd)
        return 1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}


