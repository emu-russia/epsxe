#pragma once

/**
 * \file cdr_plugin.h
 * \brief Emulator-side wrappers around the loaded CD-ROM plugin DLL.
 *
 * The ext_CDR* functions call into the CDR plugin entry points
 * (CDRreadTrack, CDRgetBuffer, CDRplay, CDRstop, ...) resolved by
 * ext_cdrom_load_plugin(), and transparently handle the fake-file and
 * ISO-image paths when no plugin is used.
 */
/* Decompiled globals (previously generated in src/_gen) */

/** \brief Path of the fake-CD file (set from the command line; used by the cdrom_fake_* functions). */
extern unsigned char cdrom_fake_filename[0x100];

/** \brief Handle of the loaded CD-ROM plugin DLL (or of WNASPI32.DLL for the Win9x ASPI backend). */
extern unsigned int hCdrModule;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Returns the first and last track numbers from the plugin TOC.
 *
 * \param first_track Receives the first track number.
 * \param last_track  Receives the last track number.
 * \return The last track number.
 */
char ext_CDR_get_first_last_track(uint8_t *first_track, uint8_t *last_track);

/**
 * \brief Converts a BCD MSF position to the track-relative MSF.
 *
 * Computes the track containing the given absolute BCD MSF position from
 * the cached TOC and writes the track-relative minute/second/frame.
 *
 * \param min       BCD minute of the absolute position.
 * \param sec       BCD second of the absolute position.
 * \param frame     BCD frame of the absolute position.
 * \param out_min   Receives the track-relative minute.
 * \param out_sec   Receives the track-relative second.
 * \param out_frame Receives the track-relative frame.
 * \return A value derived from the track lookup (decompiled return semantics).
 */
uint8_t ext_CDR_lba_to_msf( uint8_t min, uint8_t sec, uint8_t frame, uint8_t *out_min, uint8_t *out_sec, uint8_t *out_frame);

/**
 * \brief Reads one 2352-byte sector from the CD.
 *
 * In fake/ISO modes the data is read from the fake file or the ISO image;
 * otherwise CDRreadTrack + CDRgetBuffer of the plugin are used. Applies
 * PPF patches and optionally appends the sector to the fake file.
 *
 * \param min    BCD minute of the sector.
 * \param sec    BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param Buffer Destination buffer (2352 bytes).
 * \return 0 on success.
 */
int ext_CDR_read(uint8_t min, uint8_t sec, uint8_t frame, char *Buffer);

/**
 * \brief Resets the CD-ROM state by spinning up the drive motor.
 */
void ext_CDR_reset_state();

/**
 * \brief Converts a track number to its start position in MSF.
 *
 * \param track Track number (0 = lead-out area).
 * \param min   Receives the start minute.
 * \param sec   Receives the start second.
 * \param frame Receives the start frame.
 * \return The start frame (or 0 when the track is out of range).
 */
char ext_CDR_track_to_msf(int16_t track, uint8_t *min, uint8_t *sec, uint8_t *frame);

/**
 * \brief Verifies and assembles the Q-subchannel data for a sector.
 *
 * Uses the plugin's CDRgetBufferSub when available (and enabled) to
 * fetch the raw subchannel data, comparing the BCD fields against the
 * requested position and counting mismatches; otherwise synthesizes the
 * Q entry from the TOC. Writes 8 bytes into buffer.
 *
 * \param min    BCD minute of the sector.
 * \param sec    BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param buffer Output buffer for the Q-subchannel data (8 bytes).
 * \return The BCD frame, or 0 when at least two mismatches were detected.
 */
char ext_CDR_verify_subchannel_data(uint8_t min, uint8_t sec, uint8_t frame, int buffer);

/**
 * \brief Starts CDDA playback through the plugin.
 *
 * \param track_msf BCD minute of the start position (the second and frame
 *                  bytes are filled in from the other argument).
 * \param sec       BCD seconds; used together with track_msf to resolve
 *                  the start frame.
 * \return The playback status (only meaningful when CDDA is enabled).
 */
char ext_CDRplay(int track_msf, char sec);

/**
 * \brief Stops CDDA playback through the plugin.
 *
 * \return The previous playback status (only meaningful when CDDA is enabled).
 */
char ext_CDRstop();

/**
 * \brief Shuts down the CD subsystem.
 *
 * Writes the fake file, closes the ISO image, stops CDDA playback and
 * calls the plugin's CDRclose/CDRshutdown entry points.
 *
 * \return The plugin's CDRshutdown function pointer (or its result).
 */
int (*ext_cdrom_deinit())(void);

/**
 * \brief Loads the CD-ROM plugin DLL and resolves its entry points.
 *
 * Builds the plugin path from CdromPlugin, loads the DLL and resolves
 * all CDR* functions (CDRtest, CDRinit, CDRshutdown, CDRopen, CDRclose,
 * CDRgetTN, CDRgetTD, CDRreadTrack, CDRgetBuffer, CDRplay, CDRstop,
 * CDRgetBufferSub), then reads the TOC. In save-fake mode a fake file is
 * created/loaded instead of a plugin.
 *
 * \return A status byte (non-zero on success).
 */
char ext_cdrom_load_plugin();
