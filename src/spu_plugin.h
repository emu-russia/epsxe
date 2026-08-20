#pragma once

/**
 * \file spu_plugin.h
 * \brief Emulator-side wrapper around the external SPU (sound) plugin.
 *
 * Loads the user-selected SPU DLL ("plugins\..."), forwards SPU register,
 * DMA and ADPCM/XA operations to it, and manages the shared SPU DMA and
 * sound state used by the emulator core.
 */

/* Decompiled globals (previously generated in src/_gen) */

/** Uncompressed sizes of the ZIP entries loaded by the PLL loader, indexed by entry slot (filled in zip.c, read in loader.c). */
extern unsigned int Size[0x100];

/** Pointer to the SPU DMA channel (channel 4) CHCR register slot; read to determine the active DMA transfer mode. */
extern unsigned int *spu_dma_chcr_ptr;

/** Master sound enable flag (1 = sound enabled); gates all SPU plugin and DMA activity. */
extern unsigned char sound_enabled;

/** Pending ADPCM (XA) playback flag; set by spu_set_adpcm_flag() and cleared once the XA data has been processed. */
extern unsigned int spu_adpcm_flag;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Forwards a periodic asynchronous update to the SPU plugin.
 *
 * Calls the plugin's SPUasync with the given number of cycles executed since
 * the last update; falls back to SPUupdate() when SPUasync is unavailable.
 *
 * \return The plugin's new update function pointer (or the SPUupdate pointer).
 */
int (* spu_async_update(int cycles))(void);

/**
 * \brief Closes the SPU plugin.
 *
 * Calls the plugin's SPUclose() when sound is enabled, the plugin was loaded
 * and still needs to be closed, and marks the plugin as closed.
 *
 * \return The result of the plugin call, or the sound_enabled flag when the plugin was not used.
 */
char spu_close();

/**
 * \brief Shuts down and releases the SPU plugin.
 *
 * Calls SPUclose() once (unless already closed) followed by SPUshutdown(),
 * then clears the module handle so the loaded DLL can be released.
 *
 * \return The result of the plugin call, or the sound_enabled flag when the plugin was not used.
 */
char spu_destroy();

/**
 * \brief Performs an SPU (DMA channel 4) transfer.
 *
 * Reads the DMA address, block count and size from the shared SPU DMA state
 * and routes the transfer to the plugin's SPUreadDMAMem/SPUreadDMA or
 * SPUwriteDMAMem/SPUwriteDMA entry points (or to the internal
 * SPUgetOne/SPUputOne transfer functions). Invalidates the affected dynarec
 * range when the dynarec is enabled.
 */
void spu_dma();

/**
 * \brief Saves the SPU plugin state into a gzip savestate.
 *
 * Writes the id string, queries the plugin's freeze size via SPUfreeze(2),
 * then calls SPUfreeze(1, buf) and writes the saved data to the gzip file.
 *
 * \param id     Savestate identifier string written to the file.
 * \param gzfile File descriptor of the open gzip savestate.
 */
void spu_freeze(const char *id, int gzfile);

/**
 * \brief Loads and initializes the external SPU plugin DLL.
 *
 * Builds the plugin path from the SoundPlugin configuration, loads the DLL,
 * resolves all SPU exports via GetProcAddress, calls SPUinit() and
 * SPUopen(hOutputWnd) and registers the emulator's IRQ callback. When sound
 * is disabled the external plugin is not used.
 *
 * \return The result of the plugin's register-callback call, or the sound_enabled flag when the callback is unavailable.
 */
char spu_load_plugin();

/**
 * \brief Opens the SPU plugin with the emulator output window.
 *
 * Calls the plugin's SPUopen(hOutputWnd) and clears the closed flag.
 *
 * \return The result of the plugin call, or the sound_enabled flag when the plugin was not used.
 */
char spu_open();

/**
 * \brief Feeds decoded XA/ADPCM data to the SPU plugin for playback.
 *
 * When sound and XA playback are enabled, decodes the ADPCM header via
 * xa_decode_wrapper() into the shared XA buffer and hands it to the plugin's
 * SPUplayADPCMchannel(); clears the pending ADPCM flag afterwards.
 *
 * \param hdr ADPCM header/flags word of the XA data to play.
 * \return Status of the operation (0 = success, non-zero = failure).
 */
char spu_play_adpcm(int hdr);

/**
 * \brief Reads an SPU register value.
 *
 * For an external plugin, forwards to SPUreadRegister(). Otherwise serves the
 * read from the internal register cache, with special cases for the transfer
 * FIFO, transfer address and counter registers.
 *
 * \param reg SPU register address to read.
 * \return The 16-bit register value.
 */
int16_t spu_read_register(unsigned int reg);

/**
 * \brief Marks a pending ADPCM (XA) playback request.
 *
 * Simply sets the spu_adpcm_flag global to 1.
 */
void spu_set_adpcm_flag();

/**
 * \brief Restores the SPU plugin state from a gzip savestate.
 *
 * Reads the id header, allocates a buffer of the saved size, reconstructs the
 * freeze header and calls the plugin's SPUfreeze(0, buf) to restore the state.
 *
 * \param unused Unused parameter kept for prototype compatibility.
 * \param gzfile File descriptor of the open gzip savestate.
 */
void spu_unfreeze(int unused, uint32_t *gzfile);

/**
 * \brief Calls the SPU plugin's periodic update routine.
 *
 * Invokes the plugin's SPUupdate() and returns the function pointer it yields.
 *
 * \return The plugin's update function pointer.
 */
int (*spu_update())(void);

/**
 * \brief Writes an SPU register value.
 *
 * For an external plugin, forwards to SPUwriteRegister(). Otherwise dispatches
 * the write to the per-register plugin calls (SPUsetVolumeL/R, SPUsetPitch,
 * SPUsetAddr, SPUstartChannels1/2, SPUstopChannels1/2, SPUputOne) or caches
 * the value in the internal register cache.
 *
 * \param reg   SPU register address to write.
 * \param value 16-bit value to write.
 * \return The result of the plugin call, or the register address when the value was cached.
 */
char spu_write_register(unsigned int reg, int16_t value);
