#pragma once

/**
 * \file debug.h
 * \brief Declarations for the debug console and logging subsystem.
 *
 * Provides functions to allocate/deallocate the debug console,
 * write formatted debug output, and handle fatal error reporting
 * with proper plugin shutdown.
 */

/*--- Global flags and handles (defined in cfg.c / debug.c / etc.) ---*/

/** \brief Non-zero once the debug console has been allocated (checked by alloc_console/dealloc logic). */
extern unsigned char console_allocated;
/** \brief Handle of the console log file ("console.log"), or 0 when the log is not open. */
extern unsigned int console_log_handle;

/*--- SPU plugin destroy callback ---*/
/** \brief SPU plugin destroy callback installed by spu_load_plugin(); invoked during fatal-error shutdown. */
extern int ( *spu_destroy_cb)(unsigned long);

/*--- CD-ROM deinit callback ---*/
/** \brief CD-ROM plugin deinit callback installed by the CDR plugin loader; invoked during fatal-error shutdown. */
extern int ( *cdrom_deinit_cb)(unsigned long);

/*--- Console management ---*/

/**
 * \brief Allocates a new Windows console for debug output.
 *
 * If the console has not been allocated yet, calls AllocConsole()
 * and sets the console title to "ePSXe - Enhanced PSX emulator".
 * Stores the standard output handle for later WriteConsoleA calls.
 *
 * \return 1 if the console was allocated, 0 otherwise.
 */
int alloc_console(void);

/**
 * \brief Retrieves the current tick count and caches it.
 *
 * Wraps GetTickCount() and stores the result in last_tick_count.
 *
 * \return Current tick count in milliseconds since system startup.
 */
unsigned long get_tick_count(void);

/**
 * \brief Sets the console-log-flush pending flag.
 *
 * Signals that pending console output should be flushed
 * on the next opportunity.
 */
void set_console_log_flush_pending(void);

/**
 * \brief Reopens the console.log file if it has not been opened yet.
 *
 * Opens "console.log" in append mode on first call.
 * Subsequent calls return the existing file handle.
 *
 * \return Non-zero if the log is enabled, 0 otherwise.
 */
char reopen_console_log(void);

/*--- Debug printing ---*/

/**
 * \brief Prints a formatted string to the debug log without flushing.
 *
 * Formats the message into a 32 KB buffer, writes it to the
 * console log file (if enabled), and to the Windows console
 * (if allocated). Does NOT flush the file buffer.
 *
 * \param Format printf-style format string.
 * \param ...    Format arguments.
 */
void dbg_print_no_flush(const char *Format, ...);

/**
 * \brief Prints a formatted string to the debug log and flushes.
 *
 * Formats the message into a 32 KB buffer, writes it to the
 * console log file (if enabled), and to the Windows console
 * (if allocated). Flushes the file buffer before returning.
 *
 * \param Format printf-style format string.
 * \param ...    Format arguments.
 * \return The result of fflush() on the console log file, or 0 if not available.
 */
int dbg_print(const char *Format, ...);

/**
 * \brief Dumps a formatted string into the console log stream.
 *
 * Formats the message into a 32 KB buffer and writes it to
 * the given stream if the stream pointer is valid and the
 * console log is enabled.
 *
 * \param Stream   Target FILE stream (may be NULL).
 * \param Format   printf-style format string.
 * \param ...      Format arguments.
 */
void dump_log(FILE *Stream, const char *Format, ...);

/**
 * \brief Handles a fatal error: shuts down all subsystems and displays the message.
 *
 * Saves memcards, closes network, destroys GPU and SPU plugins,
 * deinitializes the dynarec, frees PPF patches, closes the error log,
 * deallocates the console, and terminates the process with exit code 0.
 * The error message is written to the console log (if enabled) or
 * to stdout.
 *
 * \param Format printf-style format string describing the error.
 * \param ...    Format arguments.
 */
void ui_error(const char *Format, ...);

/**
 * \brief Handles a fatal error with a message box.
 *
 * Saves memcards, closes network, destroys GPU and SPU plugins,
 * deinitializes the dynarec, frees PPF patches, closes the error log,
 * deallocates the console, and terminates the process with exit code 1.
 * The error message is displayed in a MessageBox and also written
 * to the console log (if enabled).
 *
 * \param Format printf-style format string describing the error.
 * \param ...    Format arguments.
 */
void fatal_error_with_message_box(const char *Format, ...);
