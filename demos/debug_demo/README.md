# Debug Module Demo

Standalone Win32 application demonstrating all functions from `src/debug.c`.

## Overview

This demo provides a graphical interface with buttons for each debug function:

| # | Button | Function | Description |
|---|--------|----------|-------------|
| 1 | `alloc_console` | `alloc_console()` | Allocates a Windows console |
| 2 | `free_console` | `free_console()` | Deallocates the console |
| 3 | `get_tick_count` | `get_tick_count()` | Gets system tick count |
| 4 | `set_flush_pending` | `set_console_log_flush_pending()` | Sets flush pending flag |
| 5 | `check_flush_pending` | `check_and_clear_console_log_flush_pending()` | Checks and clears flag |
| 6 | `reopen_console_log` | `reopen_console_log()` | Opens/reenables console.log |
| 7 | `dbg_print` | `dbg_print()` | Formatted debug output + flush |
| 8 | `dbg_print_no_flush` | `dbg_print_no_flush()` | Formatted debug output (no flush) |
| 9 | `dump_log` | `dump_log()` | Dumps to file stream |
| 10 | `fatal_error (msgbox)` | `fatal_error_with_message_box()` | Shows MessageBox + exits (code 1) |
| 11 | `ui_error (exit)` | `ui_error()` | Cleans up + exits (code 0) |

## Build

### Prerequisites

- Microsoft Visual Studio (cl.exe)
- Windows SDK

### Build and Run

```batch
build.bat
```

Or manually:

```batch
cl /Fe:debug_demo.exe debug_demo.c user32.lib kernel32.lib gdi32.lib /link /SUBSYSTEM:WINDOWS
debug_demo.exe
```

## How It Works

The demo includes `../src/debug.h` and provides stub implementations for all external ePSXe dependencies:

- `console_allocated` — console allocation flag
- `console_log_enabled` — log file enabled flag
- `console_log_flush_pending` — deferred flush flag
- `spu_destroy_cb` / `cdrom_deinit_cb` — plugin callbacks (NULL in demo)
- `sio_memcard_both_save()`, `net_close()`, `gpu_destroy()`, etc. — no-op stubs

This allows the demo to run standalone without linking the full ePSXe codebase.

## Output

Each button click:
1. Executes the corresponding debug function
2. Logs the call and return values to the GUI log area
3. Outputs to the Windows console (if allocated via button #1)

Buttons #10 and #11 demonstrate the fatal error paths — they show a message box and terminate the process.

## Files

| File | Description |
|------|-------------|
| `debug_demo.c` | Win32 application source |
| `build.bat` | Build script for MSVC |
| `README.md` | This file |
