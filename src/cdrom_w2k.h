#pragma once

/**
 * \file cdrom_w2k.h
 * \brief Windows 2000+ CD-ROM backend using SCSI pass-through (SPTI).
 *
 * Talks to the CD-ROM drive through SCSI pass-through to read sectors
 * and subchannel data, play CDDA audio and query the TOC. Also owns the
 * subchannel Q-subcode decode caches (the sub_q_* globals) used to
 * present Q-subchannel data to the emulated CD controller.
 */
/* Decompiled globals (previously generated in src/_gen) */

/** \brief Config flag: when non-zero, subchannel data is precached from the CD into a .M3S file. */
extern unsigned char SubchannelW2kCaching;

/** \brief CD-ROM drive speed setting (5 by default); influences the CD controller read-ahead timing. */
extern unsigned char cd_speed;

/** \brief Flag tracking whether subchannel/TOC read mode has been enabled on the drive. */
extern unsigned char subchannel_mode_enabled;

/** \brief Number of tracks reported by the drive TOC. */
extern unsigned char track_count;

/** \brief Base of the 8-sector data cache buffer (one sector = 2352 bytes). */
extern unsigned char cd_sector_cache[1];

/** \brief Continuation of the 8-sector data cache buffer beyond the first sector. */
extern unsigned char cd_sector_cache_cont[0x924];

/** \brief Raw Q-subchannel bytes cache (one 16-byte entry per cached sector). */
extern unsigned char sub_q_cache[1];

/** \brief Cached Q-subchannel absolute-minute (BCD) value. */
extern unsigned char sub_q_minute;

/** \brief Detected CD-ROM drive letter (e.g. 'E'). */
extern unsigned char cdrom_letter;

/** \brief Cached Q-subchannel second/frame value. */
extern unsigned int sub_q_sec_frame;

/** \brief Cached Q-subchannel absolute second/frame value. */
extern unsigned int sub_q_asec_aframe;

/** \brief Cache for the remaining Q-subchannel words (decompiled-size array). */
extern unsigned int sub_q_rest[0x10d1];

/** \brief Q-subchannel block cache holding 8 sectors x 16 bytes of Q data. */
extern unsigned int sub_q_block_cache[1];

/** \brief Second 32-bit word of the current Q-subchannel block entry (alias of sub_q_block_cache[1]). */
extern unsigned int sub_q_block_cache1;

/** \brief Third 32-bit word of the current Q-subchannel block entry (alias of sub_q_block_cache[2]). */
extern unsigned int sub_q_block_cache2;

/** \brief Fourth and subsequent 32-bit words of the Q-subchannel block cache. */
extern unsigned int sub_q_block_cache3[0x1d];

/** \brief Heap buffer holding the .M3S subchannel Q-cache (one 16-byte entry per sector). */
extern unsigned int m3s_q_cache;

/** \brief Byte stride between cached sectors in cd_sector_cache (2352 or 2368). */
extern unsigned int sector_stride;

/** \brief Current CD read mode (1..10) selected during init/subchannel setup. */
extern unsigned int cd_read_mode;

/** \brief First 32-bit word of the current sector's Q-subchannel entry. */
extern unsigned int sub_q_cur0;

/** \brief Second 32-bit word of the current sector's Q-subchannel entry. */
extern unsigned int sub_q_cur1;

/** \brief Third 32-bit word of the current sector's Q-subchannel entry. */
extern unsigned int sub_q_cur2;

/** \brief Fourth 32-bit word of the current sector's Q-subchannel entry. */
extern unsigned int sub_q_cur3;

/** \brief Snapshot of the emulated CPU's COP0 breakpoint-control register values; the CD code tests the bit pattern of element [0] to decide whether Q-subchannel data must be captured. */
extern unsigned int cop0_bpc_value[0x9];

/** \brief When non-zero, CDDA audio playback is enabled (cleared when the drive handle cannot be opened or an ISO image is used). */
extern unsigned char sound_use_cdda;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Shuts down the Windows 2000+ CD-ROM backend.
 *
 * Writes the fake file, closes the ISO image, frees the .M3S cache,
 * stops CDDA playback and closes the drive device handle.
 *
 * \return The drive handle (or the close result).
 */
HANDLE W2k_cdrom_deinit();

/**
 * \brief Initializes the Windows 2000+ CD-ROM backend.
 *
 * Finds the CD-ROM drive letter, opens the device, reads the TOC and
 * probes the sector read mode (mode1 or raw) by reading the lead-in.
 * Also handles the fake-file and ISO-image paths.
 *
 * \return A probe result byte (sector header value or status).
 */
char W2k_cdrom_init();

/**
 * \brief Starts CDDA playback from the given MSF position.
 *
 * \param minute BCD minute of the start position.
 * \param second BCD second of the start position.
 * \param frame  BCD frame of the start position.
 * \return The playback status (only meaningful when CDDA is enabled).
 */
char W2k_cdrom_play_cdda(unsigned int minute, int second, uint8_t frame);

/**
 * \brief Reads one 2352-byte sector from the CD.
 *
 * Uses an 8-sector cache; for each read also assembles the current
 * Q-subchannel entry (sub_q_cur0..3) according to the active read mode.
 * Applies PPF patches and optionally appends the sector to the fake file.
 *
 * \param minute BCD minute of the sector.
 * \param second BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param Buffer Destination buffer (2352 bytes).
 * \return 0 on success.
 */
int W2k_cdrom_read_data(uint8_t minute, uint8_t second, uint8_t frame, char *Buffer);

/**
 * \brief Stops CDDA playback through the SCSI stop command.
 *
 * \return The previous CDDA playback state.
 */
char W2k_cdrom_stop();

/**
 * \brief Detects subchannel support and precaches subchannel data.
 *
 * Tries a .SUB file, then a .M3S file, then live subchannel reads from
 * the drive (precached into a .M3S file when SubchannelW2kCaching is
 * enabled), selecting the matching cd_read_mode for each source.
 *
 * \return A status value (debug print or mode result).
 */
char W2k_cdrom_subchannel_read();

/**
 * \brief Verifies and assembles the Q-subchannel data for a sector.
 *
 * When subchannel data is available (sub_q_cur0 non-zero), compares the
 * cached Q fields against the expected MSF and counts mismatches;
 * otherwise synthesizes the Q entry from the TOC. Writes 8 bytes into
 * out.
 *
 * \param minute BCD minute of the sector.
 * \param second BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param out    Output buffer for the Q-subchannel data (8 bytes).
 * \return The BCD frame, or 0 when at least two mismatches were detected.
 */
uint8_t W2k_check_subchannel_data(unsigned int minute, uint8_t second, uint8_t frame, int out);

/**
 * \brief Returns the first and last track numbers from the TOC.
 *
 * \param first_track Receives the first track number.
 * \param last_track  Receives the last track number.
 * \return The last track number.
 */
char W2k_get_first_last_track(uint8_t *first_track, uint8_t *last_track);

/**
 * \brief Converts a BCD MSF position to the track-relative MSF.
 *
 * Computes the track containing the given absolute BCD MSF position from
 * the cached TOC and writes the track-relative minute/second/frame.
 *
 * \param minute      BCD minute of the absolute position.
 * \param second      BCD second of the absolute position.
 * \param frame       BCD frame of the absolute position.
 * \param out_minute  Receives the track-relative minute.
 * \param out_second  Receives the track-relative second.
 * \param out_frame   Receives the track-relative frame.
 * \return A value derived from the track lookup (decompiled return semantics).
 */
char W2k_lba_to_msf( unsigned int minute, uint8_t second, uint8_t frame, uint8_t *out_minute, uint8_t *out_second, uint8_t *out_frame);

/**
 * \brief Resets the CDDA state and spins up the drive motor.
 */
void W2k_reset_cdda_state();

/**
 * \brief Converts a track number to its start position in MSF.
 *
 * \param track  Track number (0 = lead-out area).
 * \param minute Receives the start minute.
 * \param second Receives the start second.
 * \param frame  Receives the start frame.
 * \return The start minute (or the track count when out of range).
 */
unsigned int W2k_track_to_msf(int track, uint8_t *minute, uint8_t *second, uint8_t *frame);
