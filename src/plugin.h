#pragma once

/**
 * \file plugin.h
 * \brief Central function-pointer table for the CD-ROM and SPU backends.
 *
 * Declares the cdrom_*_cb / spu_*_cb callbacks that the emulator core calls
 * for CD-ROM and sound access, and the backend-selection entry points.
 * select_plugins_backend() fills the pointers with either the built-in
 * cores (SPUCORE, W9XCDRCORE, W2KCDRCORE) or the external plugin wrappers.
 */

/* Decompiled globals (previously generated in src/_gen) */

/** CD-ROM callback: reports the first and last track numbers of the inserted disc (CDRgetTN equivalent). */
extern int ( *cdrom_get_first_last_TN_cb)();

/** CD-ROM callback: initializes the selected CD-ROM backend. */
extern int ( *cdrom_init_cb)();

/** CD-ROM callback: converts an LBA position to MSF (minute/second/frame) coordinates. */
extern int ( *cdrom_lba_to_msf_cb)();

/** CD-ROM callback: starts playback of a CDDA audio track (CDRplay equivalent). */
extern int ( *cdrom_play_cdda_cb)();

/** CD-ROM callback: reads data sectors from the disc into the supplied buffer (CDRreadTrack equivalent). */
extern int ( *cdrom_read_data_cb)();

/** CD-ROM callback: resets the CD-ROM state (seek/playback state). */
extern int ( *cdrom_reset_cb)();

/** CD-ROM callback: stops CDDA playback / disc access. */
extern int ( *cdrom_stop_cb)();

/** CD-ROM callback: reads the Q subchannel data of the current position (CDRgetBufferSub equivalent). */
extern int ( *cdrom_subchannel_read_cb)();

/** CD-ROM callback: converts a track number to its starting MSF position (CDRgetTD equivalent). */
extern int ( *cdrom_track_to_msf)();

/** CD-ROM callback: verifies the subchannel (Q) data of a read sector. */
extern int ( *cdrom_verify_sub_cb)();

/** SPU callback: periodic asynchronous update, called from the CPU/dynarec loops with the cycles executed. */
extern int ( *spu_async_update_cb)();

/** SPU callback: performs an SPU (DMA channel 4) transfer; called from hw.c on DMA writes. */
extern int ( *spu_dma_cb)();

/** SPU callback: saves the SPU state into a gzip savestate; called from sstates.c. */
extern int ( *spu_freeze_cb)();

/** SPU callback: initializes the SPU backend (internal core or external plugin). */
extern int ( *spu_init_cb)();

/** SPU callback: feeds decoded XA/ADPCM data for playback; called from the CD-ROM handler. */
extern int ( *spu_play_adpcm_cb)();

/** SPU callback: reads an SPU register; called from hw.c and mem.c on SPU register reads. */
extern int ( *spu_read_register_cb)();

/** SPU callback: marks a pending ADPCM (XA) playback request; called from the XA/CD-ROM paths. */
extern int ( *spu_set_adpcm_flag_cb)();

/** SPU callback: restores the SPU state from a gzip savestate; called from sstates.c. */
extern int ( *spu_unfreeze_cb)();

/** SPU callback: periodic sound update; called from the main window message loop. */
extern int ( *spu_update_cb)();

/** SPU callback: writes an SPU register; called from hw.c and mem.c on SPU register writes. */
extern int ( *spu_write_register_cb)();

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Selects a built-in CD-ROM core when no external CD-ROM plugin is configured.
 *
 * When the CdromPlugin configuration is "NULL", picks "W2KCDRCORE" on the
 * Windows NT platform or the Win9x ASPI core ("W9XCDRCORE") otherwise, and
 * writes the chosen core name back into CdromPlugin.
 *
 * \return Non-zero when a core was selected, 0 otherwise.
 */
char select_cdrom_core();

/**
 * \brief Fills the SPU and CD-ROM callback tables with the configured backends.
 *
 * Assigns the spu_*_cb pointers to the internal SPU core (spucore.c) when the
 * SoundPlugin configuration is "SPUCORE", or to the external plugin wrappers
 * (spu_plugin.c) otherwise; assigns the cdrom_*_cb pointers based on the
 * CdromPlugin configuration (W9XCDRCORE, W2KCDRCORE or an external DLL).
 * Also clears some emulated hardware state.
 *
 * \return 0 on success.
 */
int select_plugins_backend();
