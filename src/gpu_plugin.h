#pragma once

/**
 * \file gpu_plugin.h
 * \brief Emulator-side wrapper around the external GPU (video) plugin.
 *
 * Loads the user-selected GPU DLL ("plugins\..."), owns the emulator's output
 * window and DirectInput initialization, and forwards GPU register, data and
 * DMA operations to the plugin. Also handles the GPU DMA channels 2 and 6
 * completion interrupts and savestate (freeze) support.
 */

/* Decompiled globals (previously generated in src/_gen) */

/** Delay counter used by gpu_dma2_interrupt() before the DMA-2 completion interrupt is asserted. */
extern unsigned char gpu_dma2_delay_counter;

/** State of the GPU DMA channel 2 transfer (0 = idle, 1 = DMA chain in progress, -2 = completed/interrupt asserted). */
extern unsigned char gpu_dma2_state;

/** Delay counter used by gpu_dma6_interrupt() before the DMA-6 completion interrupt is asserted. */
extern unsigned char gpu_dma6_delay_counter;

/** Storage for the GPU DMA channel 2 CHCR register value; written in hw.c and read by the DMA routines to determine the transfer mode. */
extern unsigned int gpu_dma_channel_status[1];

/** Application instance handle used when creating the DirectInput object. */
extern unsigned int hInst_For_DInput;

/** Handle of the emulator's main output window, passed to the GPU/SPU plugins and used for DirectInput/DirectSound. */
extern unsigned int hOutputWnd;

/** Flag enabling high-resolution performance-counter frame throttling (set from the command line). */
extern unsigned char use_performance_counters;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Closes the GPU plugin.
 *
 * Calls the plugin's GPUclose() and marks the plugin as closed.
 *
 * \return The result of the GPUclose() call.
 */
int gpu_close();

/**
 * \brief Closes the emulator output window and unregisters its window class.
 *
 * Restores the display settings and cursor, destroys the "EPSX" window and
 * unregisters the window class.
 *
 * \return Non-zero on success.
 */
BOOL gpu_close_output_window();

/**
 * \brief Creates the emulator output window.
 *
 * Registers the "EPSX" window class, creates the 640x480 output window,
 * hides the cursor and brings the window to the foreground.
 *
 * \return The handle returned by SetFocus() on the new window.
 */
HWND gpu_create_output_window();

/**
 * \brief Forwards cursor position updates to the GPU plugin.
 *
 * Calls the plugin's GPUcursor() with the given cursor coordinates (x, y)
 * and cursor flags.
 *
 * \return The plugin's GPUcursor() call result.
 */
int (__stdcall * gpu_cursor(int x, int y, int flag))(uint32_t, uint32_t, uint32_t);

/**
 * \brief Shuts down and releases the GPU plugin.
 *
 * Closes the plugin (unless already closed), calls GPUshutdown(), restores
 * the display settings and cursor, and destroys the output window.
 *
 * \return The module handle, or the result of the last window/dialog operation.
 */
HMODULE gpu_destroy();

/**
 * \brief Forwards display flags to the GPU plugin.
 *
 * Calls the plugin's GPUdisplayFlags() with the given display flags.
 *
 * \return The plugin's GPUdisplayFlags() call result.
 */
int (__stdcall * gpu_display_flags(int flags))(uint32_t);

/**
 * \brief Performs a GPU (DMA channel 2) transfer.
 *
 * Routes GPU-data DMA modes (CHCR 0x1000200/0x1000201) to the plugin's
 * GPUreadDataMem/GPUreadData or GPUwriteDataMem/GPUwriteData, and DMA-chain
 * mode (0x1000401) to GPUdmaChain(). Asserts the DMA-2 interrupt once the
 * transfer completes.
 *
 * \return The result of the interrupt assertion, or the channel status.
 */
char gpu_dma();

/**
 * \brief Handles the GPU DMA channel 2 completion interrupt.
 *
 * Counts down the DMA-2 delay counter and, once it reaches zero, clears the
 * transfer-active bit in the channel status, asserts the DMA-2 interrupt and
 * marks the transfer as complete.
 *
 * \return The remaining delay counter, or the result of irq_dma_assert_int(2).
 */
char gpu_dma2_interrupt();

/**
 * \brief Handles the GPU DMA channel 6 completion interrupt.
 *
 * Counts down the DMA-6 delay counter and, once it reaches zero, clears the
 * transfer-active bit in the channel status and asserts the DMA-6 interrupt.
 *
 * \return The remaining delay counter, or the result of irq_dma_assert_int(6).
 */
char gpu_dma6_interrupt();

/**
 * \brief Queries the GPU plugin's savestate size for a slot.
 *
 * Calls the plugin's GPUfreeze(2, &slot), passing the given savestate slot
 * number, to query the freeze buffer size.
 *
 * \return The plugin's GPUfreeze() call result.
 */
int (__stdcall * gpu_do_freeze(int slot))(uint32_t, uint32_t);

/**
 * \brief Advances the GPU frame: pumps messages and updates the display.
 *
 * Drains the output window's message queue, throttles to the performance-
 * counter frame budget (when enabled) and calls the plugin's GPUupdateLace();
 * then processes input.
 *
 * \return The result of cont_process_input().
 */
int gpu_frame_update();

/**
 * \brief Saves the GPU plugin state into a gzip savestate.
 *
 * Calls GPUfreeze(1, buf) to capture the plugin state, writes the id string
 * and the freeze buffer to the gzip file, and saves the current screen
 * picture via GPUgetScreenPic() to "<picname>.pic" when available.
 *
 * \param id      Savestate identifier string written to the file.
 * \param ArgList File descriptor of the open gzip savestate.
 * \param picname Base filename used for the screen-picture file.
 */
void gpu_freeze(const char *id, int ArgList, const char *picname);

/**
 * \brief Hides the on-screen savestate picture.
 *
 * Calls the plugin's GPUshowScreenPic(0) to hide the picture.
 *
 * \return The plugin's GPUshowScreenPic() call result.
 */
int (__stdcall *gpu_hide_screen_pic())(uint32_t);

/**
 * \brief Initializes the frame-throttling performance counter.
 *
 * Queries the performance-counter frequency and computes the frame delay
 * threshold (16 ms for NTSC, 20 ms otherwise) used by gpu_frame_update().
 *
 * \return Status of QueryPerformanceFrequency()/QueryPerformanceCounter(), or the use_performance_counters flag.
 */
char gpu_init_performance_counter();

/**
 * \brief Loads and initializes the external GPU plugin DLL.
 *
 * Builds the plugin path from the VideoPlugin configuration, loads the DLL,
 * resolves all GPU exports via GetProcAddress, calls GPUinit(), initializes
 * the net plugin and creates the output window.
 *
 * \return The output window handle.
 */
HWND gpu_load_plugin();

/**
 * \brief Takes a screenshot through the GPU plugin.
 *
 * Calls the plugin's GPUmakeSnapshot().
 *
 * \return The plugin's GPUmakeSnapshot() call result.
 */
int (*gpu_make_snapshot())(void);

/**
 * \brief Opens the GPU plugin with the output window.
 *
 * Calls the plugin's GPUopen(hOutputWnd), marks the plugin as open and
 * (re)initializes DirectInput for the output window.
 *
 * \return The result of diUpdateJoystickStates().
 */
int gpu_open();

/**
 * \brief Opens the GPU plugin with the output window and input.
 *
 * Calls the plugin's GPUopen(hOutputWnd), initializes DirectInput, updates
 * the joystick states and queries the plugin's freeze size.
 *
 * \return The result of gpu_do_freeze(0).
 */
int (__stdcall *gpu_open_with_input())(uint32_t, uint32_t);

/**
 * \brief Reads a GPU data word from the plugin.
 *
 * \return The 32-bit data word read.
 */
int gpu_readData();

/**
 * \brief Reads the GPU status register from the plugin.
 *
 * \return The 32-bit status value.
 */
int gpu_readStatus();

/**
 * \brief Displays the savestate screenshot for the given slot.
 *
 * Loads "<sstates>\<name>.<slot>.pic" (or the raw savestate picture) and
 * shows it via the plugin's GPUshowScreenPic(); draws "NO SAVE PIC" or
 * "FREE SLOT" placeholder images when no picture file exists.
 *
 * \param slot Savestate slot number whose picture is shown.
 */
void gpu_show_screen_pic(uint8_t slot);

/**
 * \brief Restores the GPU plugin state from a gzip savestate.
 *
 * Reads the freeze buffer from the gzip file and calls the plugin's
 * GPUfreeze(0, buf) to restore the state.
 *
 * \param unused  Unused parameter kept for prototype compatibility.
 * \param ArgList File descriptor of the open gzip savestate.
 */
void gpu_unfreeze(int unused, uint32_t *ArgList);

/**
 * \brief Writes a GPU data word to the plugin.
 *
 * \param data 32-bit data word to write.
 * \return The result of the plugin's GPUwriteData() call.
 */
int gpu_writeData(int data);

/**
 * \brief Writes a GPU status/command register value to the plugin.
 *
 * \param data 32-bit status/command value to write.
 * \return The result of the plugin's GPUwriteStatus() call.
 */
int gpu_writeStatus(int data);
