# Debug Module

## Overview

The **debug** module (`src/debug.c`) provides the debug console and logging infrastructure for ePSXe. It handles Windows console allocation/deallocation, formatted debug output to both the console and log files, and the emergency shutdown path for fatal errors.

The module is a thin wrapper around Windows API (`AllocConsole`, `FreeConsole`, `WriteConsoleA`) and the MSVC CRT (`fprintf`, `fflush`, `vsprintf`).

---

## Memory Layout

Several variables used by this module reside at fixed addresses in the `.data` / `.bss` segments. These come from the original IDA Pro disassembly and are preserved for compatibility with the memory layout.

| Address | Symbol | Type | Description |
|---------|--------|------|-------------|
| `0x458A00` | `__stdout` | `FILE` | MSVC CRT `_iob[1]` — predefined stdout handle |
| `0x4FF9F0` | `console_log_flush_pending` | `unsigned char` | Set by `set_console_log_flush_pending()`, cleared by `check_and_clear_console_log_flush_pending()` |
| `0x4FF9F2` | `console_log_enabled` | `unsigned char` | Non-zero when `console.log` output is enabled |
| — | `console_allocated` | `unsigned char` | Defined in `cfg.c` — non-zero when a Windows console is active |
| — | `console_log_handle` | `FILE *` | Handle to the open `console.log` file |
| — | `error_log_file` | `FILE *` | Handle to the error log file (closed during shutdown) |
| — | `last_tick_count` | `unsigned long` | Cached result of the last `GetTickCount()` call |
| — | `dynarec_active` | `int` | Non-zero when the dynarec JIT is active (value == 1 means dynarec is initialized) |

---

## Global State

### `static HANDLE h_console_output`

Module-level static variable that stores the `HANDLE` returned by `GetStdHandle(STD_OUTPUT_HANDLE)`. Used by `WriteConsoleA` calls in `dbg_print_no_flush()`, `ui_error()`, and `dbg_print()`.

---

## Functions

### Console Management

#### `alloc_console()`

Allocates a new Windows debug console.

**Behavior:**
1. Checks `console_allocated` flag.
2. If set, calls `AllocConsole()` and sets the console title to `"ePSXe - Enhanced PSX emulator"`.
3. Retrieves the standard output handle via `GetStdHandle(0xFFFFFFF5)` (`STD_OUTPUT_HANDLE`).
4. Stores the handle in `h_console_output`.
5. Returns the lowest byte of the handle (non-zero if console was allocated, 0 otherwise).

**Called from:** `main.c` — `epsxe_main_loop_runner()`.

---

#### `free_console()`

Deallocates the debug console.

**Behavior:**
1. Checks `console_allocated` flag.
2. If set, calls `FreeConsole()`.
3. Returns the value of `console_allocated` (1 if freed, 0 if not).

**Called from:** `ui_error()`, `fatal_error_with_message_box()`, `mainwnd.c`.

---

#### `get_tick_count()`

Retrieves the current system tick count via `GetTickCount()` and caches it in `last_tick_count`.

**Returns:** Current tick count in milliseconds since system startup.

**Called from:** `main.c` — `epsxe_main_loop_runner()`.

---

### Console Log Flush Control

These two functions implement a deferred-flush mechanism for the console log file.

#### `set_console_log_flush_pending()`

Sets `console_log_flush_pending` (at `0x4FF9F0`) to 1, signaling that pending console output should be flushed on the next opportunity.

---

#### `check_and_clear_console_log_flush_pending()`

Atomically reads and clears `console_log_flush_pending`. Returns the previous value.

**Pattern:**
```c
char was_pending = console_log_flush_pending;
if (console_log_flush_pending)
    console_log_flush_pending = 0;
return was_pending;
```

---

### Debug Printing

All three functions format messages into a 32 KB (`0x8000` bytes) heap-allocated buffer using `vsprintf()`, then write to `__stdout` (the MSVC CRT `FILE` struct at `0x458A00`). If a console is allocated, they also write to it via `WriteConsoleA()`.

#### `dbg_print_no_flush(const char *Format, ...)`

Prints a formatted message to the debug log **without** flushing the file buffer.

**Flow:**
1. `va_start()` + `malloc(0x8000)` — allocate buffer.
2. `vsprintf(buf, Format, arg_list)` — format message.
3. `fprintf(&__stdout, "%s", buf)` — write to stdout.
4. If `console_allocated`: `WriteConsoleA(h_console_output, buf, ...)` — write to console window.
5. `free(buf)` — release buffer.

---

#### `dbg_print(const char *Format, ...)`

Same as `dbg_print_no_flush()` but **flushes** the file buffer before returning.

**Additional step:** Returns `fflush(&__stdout)` — the result of flushing stdout.

---

#### `dump_log(FILE *Stream, const char *Format, ...)`

Dumps a formatted message to an arbitrary `FILE *` stream.

**Behavior:**
1. Allocates a 32 KB buffer and formats the message.
2. If `Stream` is non-NULL and `console_log_enabled` is non-zero, writes to `Stream`.
3. Frees the buffer.

**Used by:** `hw.c`, `mem.c`, `loader.c` — for hardware register dumps and CD-ROM debug output.

---

### Console Log File

#### `reopen_console_log()`

Opens `"console.log"` in append mode (`"a"`) if `console_log_enabled` is set and `console_log_handle` is NULL. Subsequent calls return the existing handle.

**Returns:** Non-zero if log is enabled, 0 otherwise.

**Called from:** `main.c` — `epsxe_main_loop_runner()`, at the start of each emulation frame.

---

### Fatal Error Handling

Both functions perform a full subsystem shutdown sequence before terminating the process. They are called when a fatal, unrecoverable error occurs.

#### `ui_error(const char *Format, ...)`

**Shutdown sequence:**
1. `sio_memcard_both_save()` — save both memcard states.
2. `net_close()` — close network connection.
3. `nullsub_1()` — placeholder callback (no-op).
4. `spu_destroy_cb(0)` — destroy SPU plugin (if callback is set).
5. `dynarec_deinit()` — deinitialize dynarec JIT (if `dynarec_active == 1`).
6. `gpu_destroy()` — destroy GPU plugin.
7. `cdrom_deinit_cb(0)` — deinit CD-ROM plugin (if callback is set).
8. `ppf_free()` — free PPF patch data.
9. `check_and_clear_console_log_flush_pending()` — flush pending log output.
10. Write error message to `__stdout` (if `console_log_flush_pending`) or `stdout` via `printf()`.
11. `fclose(error_log_file)` — close error log.
12. `nullsub_1()` — another placeholder callback.
13. `free_console()` — deallocate console.
14. `exit(0)` — terminate process.

---

#### `fatal_error_with_message_box(const char *Format, ...)`

Same shutdown sequence as `ui_error()`, with two differences:
1. The error message is displayed in a Windows `MessageBoxA` with caption `"Error running ePSXe"`.
2. Process terminates with `exit(1)` (non-zero exit code).

**Note:** `gpu_destroy()` is called **after** the message box, so the GPU plugin may still be active when the dialog is displayed.

---

## Callbacks

The module depends on several function pointers defined elsewhere in the codebase:

| Symbol | Type | Source |
|--------|------|--------|
| `spu_destroy_cb` | `int (__cdecl *)(unsigned long)` | `ui_misc.c` — set to `spucore_destroy` or `spu_destroy` |
| `cdrom_deinit_cb` | `int (__fastcall *)(unsigned long)` | `ui_misc.c` — set to `W9x_cdrom_deinit` or similar |
| `nullsub_1` | `void (void)` | `dynarec.c` — no-op stub used as placeholder |
| `sio_memcard_both_save` | `char (void)` | `sio.c` |
| `net_close` | `HMODULE (void)` | `net.c` |
| `gpu_destroy` | `HMODULE (void)` | `gpu_plugin.c` |
| `ppf_free` | `void (void)` | `ppf.c` |
| `dynarec_deinit` | `void (void)` | `dynarec.c` |

---

## Buffer Sizes

All debug printing functions allocate a **32 KB** (`0x8000` bytes) buffer on the heap for formatted output. This is a fixed size — messages longer than 32 KB will overflow the buffer via `vsprintf()`, which is a potential security concern.

---

## Call Graph

```
epsxe_main_loop_runner() [main.c]
  ├── alloc_console()
  ├── get_tick_count()
  ├── reopen_console_log()
  │
  └── (on fatal error)
      ├── ui_error()
      │   ├── sio_memcard_both_save()
      │   ├── net_close()
      │   ├── spu_destroy_cb()
      │   ├── dynarec_deinit()
      │   ├── gpu_destroy()
      │   ├── cdrom_deinit_cb()
      │   ├── ppf_free()
      │   ├── check_and_clear_console_log_flush_pending()
      │   ├── free_console()
      │   └── exit(0)
      │
      └── fatal_error_with_message_box()
          ├── (same shutdown sequence as ui_error)
          ├── MessageBoxA()
          └── exit(1)
```

---

## Debug Log File

When enabled, ePSXe writes all debug output to `console.log` in the working directory. The log is opened in **append** mode on first call to `reopen_console_log()` and kept open for the lifetime of the process.

Log output is used for:
- Hardware register access traces (`hw.c`)
- Memory read/write traces (`mem.c`)
- CD-ROM operations (`loader.c`)
- General debug messages (`dbg_print()`, `dbg_print_no_flush()`)
