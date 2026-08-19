#pragma once

/**
 * \file cdrom_w9x.h
 * \brief Windows 9x CD-ROM backend using ASPI.
 *
 * Uses the ASPI layer (WNASPI32.DLL) to enumerate CD-ROM devices, read
 * sectors and subchannel data, play CDDA audio and query the TOC on
 * Windows 9x systems.
 */
/* Decompiled globals (previously generated in src/_gen) */

/** \brief Config flag: when non-zero, subchannel data is precached from the CD into a .M3S file. */
extern unsigned char SubchannelW9xCaching;

/** \brief Table of CD-ROM device product-name strings (from SCSI INQUIRY), one entry per detected device. */
extern unsigned char cd_device_product[0x10];

/** \brief Selected ASPI host adapter ID (default 0xffffffff = none). */
extern unsigned int cdrom_haid;

/** \brief Selected ASPI LUN (default 0xffffffff = none). */
extern unsigned int cdrom_lun;

/** \brief Selected ASPI target ID (default 0xffffffff = none). */
extern unsigned int cdrom_target;

/** \brief Packed ASPI/CD info: LOBYTE = track count, BYTE1 = adapter count, BYTE2 = max targets, HIBYTE = number of CD-ROM devices found. */
extern unsigned int w9x_cdrom_info;

/** \brief LBA of the first sector currently held in the 8-sector cache. */
extern unsigned int cached_sector_lba;

/** \brief Per-device ASPI host adapter IDs table (one entry per detected device). */
extern unsigned int cd_device_haid;

/** \brief Per-device ASPI target IDs table (one entry per detected device). */
extern unsigned int cd_device_target;

/** \brief Per-device ASPI LUN table (one entry per detected device). */
extern unsigned int cd_device_lun[0xf1];

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Copies four bytes from src to dest in reversed byte order.
 *
 * Used to fetch big-endian BCD MSF/track values from ASPI TOC buffers
 * into native dword variables.
 *
 * \param dest Destination dword.
 * \param src  Source bytes (big-endian).
 * \return The dest pointer.
 */
uint32_t * W9x_bcd_to_dword(uint32_t *dest, uint8_t *src);

/**
 * \brief Shuts down the Windows 9x CD-ROM backend.
 *
 * Writes the fake file, closes the ISO image, frees the .M3S cache,
 * disables subchannel mode, stops CDDA playback and unloads WNASPI32.DLL.
 *
 * \return The unloaded WNASPI32.DLL module handle.
 */
HMODULE W9x_cdrom_deinit();

/**
 * \brief Initializes the Windows 9x CD-ROM backend.
 *
 * Loads WNASPI32.DLL, enumerates ASPI devices, reads the TOC and probes
 * the sector read mode (mode1 or raw) by reading the lead-in. Also
 * handles the fake-file and ISO-image paths.
 *
 * \return A probe result byte (sector header value or status).
 */
char W9x_cdrom_init();

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
int W9x_cdrom_read_data(uint8_t minute, uint8_t second, uint8_t frame, char *Buffer);

/**
 * \brief Stops CDDA playback through the ASPI stop command.
 *
 * \return The previous CDDA playback state.
 */
char W9x_cdrom_stop();

/**
 * \brief Detects subchannel support and precaches subchannel data.
 *
 * Tries a .SUB file, then a .M3S file, then live subchannel reads from
 * the drive (precached into a .M3S file when SubchannelW9xCaching is
 * enabled), selecting the matching cd_read_mode for each source.
 *
 * \return A status value (debug print or mode result).
 */
char W9x_cdrom_subchannel_read();

/**
 * \brief Unloads WNASPI32.DLL and clears the ASPI entry points.
 *
 * \return The previous module handle (or the SendASPI32Command pointer).
 */
HMODULE W9x_free_winaspi_dll();

/**
 * \brief Returns the first and last track numbers from the TOC.
 *
 * \param first_track Receives the first track number.
 * \param last_track  Receives the last track number.
 * \return The last track number.
 */
char W9x_get_first_last_track(uint8_t *first_track, uint8_t *last_track);

/**
 * \brief Converts a BCD MSF position to the start LBA of its track.
 *
 * Computes the track containing the given absolute BCD MSF position from
 * the cached TOC and writes the track start position as MSF.
 *
 * \param minute      BCD minute of the position.
 * \param second      BCD second of the position.
 * \param frame       BCD frame of the position.
 * \param minute_out  Receives the track start minute.
 * \param second_out  Receives the track start second.
 * \param frame_out   Receives the track start frame.
 * \return A value derived from the track lookup (decompiled return semantics).
 */
uint8_t W9x_get_track_start_lba( uint8_t minute, uint8_t second, uint8_t frame, uint8_t *minute_out, uint8_t *second_out, uint8_t *frame_out);

/**
 * \brief Initializes the ASPI layer and enumerates CD-ROM devices.
 *
 * Calls GetASPI32SupportInfo, scans all adapters/targets/LUNs and
 * registers every CD-ROM device (via SCSI INQUIRY) in the device tables.
 *
 * \return The adapter count (or a status value).
 */
char W9x_init_aspi();

/**
 * \brief Loads WNASPI32.DLL and resolves its entry points without error dialogs.
 *
 * \return 0 on success, -1 when the DLL or an entry point is missing.
 */
int W9x_load_win_aspi_silent();

/**
 * \brief Loads WNASPI32.DLL and resolves its entry points.
 *
 * Shows a fatal error message box when the DLL or an entry point cannot
 * be loaded.
 *
 * \return The SendASPI32Command function pointer.
 */
int ( *W9x_load_winaspi_dll())(LPSRB);

/**
 * \brief Starts CDDA playback from the given MSF position.
 *
 * \param minute BCD minute of the start position.
 * \param second BCD second of the start position.
 * \param track  Receives the resolved start frame (the incoming value is
 *               unused by the decompiled code).
 * \return The playback status (only meaningful when CDDA is enabled).
 */
char W9x_play_cdda(unsigned int minute, int second, uint8_t track);

/**
 * \brief Resets the CDDA state and the sector cache, then spins up the motor.
 */
void W9x_reset_cdrom_state();

/**
 * \brief Converts a track number to its start position in MSF.
 *
 * \param track  Track number (0 = lead-out area).
 * \param minute Receives the start minute.
 * \param second Receives the start second.
 * \param frame  Receives the start frame.
 * \return The start minute (or the track count when out of range).
 */
unsigned int W9x_track_to_msf(int16_t track, uint8_t *minute, uint8_t *second, uint8_t *frame);

/**
 * \brief Verifies and assembles the Q-subchannel data for a sector.
 *
 * When subchannel data is available (sub_q_cur0 non-zero), compares the
 * cached Q fields against the expected MSF and counts mismatches;
 * otherwise synthesizes the Q entry from the TOC. Writes 8 bytes into
 * buffer.
 *
 * \param minute BCD minute of the sector.
 * \param second BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param buffer Output buffer for the Q-subchannel data (8 bytes).
 * \return The BCD frame, or 0 when at least two mismatches were detected.
 */
char W9x_verify_subchannel_data(unsigned int minute, uint8_t second, uint8_t frame, int buffer);
