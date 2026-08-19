#pragma once

/**
 * \file cdrom_iso.h
 * \brief ISO image CD backend.
 *
 * Reads sectors from a CD image (BIN/IMG 2352, NRG 2352/2336, CDI 2336)
 * using an 8-sector cache, and optionally loads the matching .sub
 * subchannel file to provide Q-subchannel data.
 */
/* Decompiled globals (previously generated in src/_gen) */

/** \brief When non-zero, subchannel (.sub) data is loaded and used for Q-subchannel verification. */
extern unsigned char use_subchannel;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Closes the ISO image and the optional subchannel file.
 *
 * \return The result of the debug print call.
 */
int iso_close();

/**
 * \brief Opens an ISO image and detects its format.
 *
 * Probes the file for the known image formats (BIN/IMG 2352, NRG,
 * CDI 2336), sets the sector size/start offset accordingly, and opens
 * the matching .sub subchannel file when use_subchannel is set.
 *
 * \param FileName Path of the ISO image.
 * \return A status value (subchannel flag or debug print result).
 */
char iso_load(char *FileName);

/**
 * \brief Reads one 2352-byte sector from the ISO image.
 *
 * Uses an 8-sector cache; reads the subchannel (.sub) entry for the
 * sector when available and synthesizes the sector header (MSF) when the
 * image data has none.
 *
 * \param minute BCD minute of the sector.
 * \param second BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param buffer Destination buffer (2352 bytes).
 * \return The sector header value.
 */
char iso_read_data(uint8_t minute, uint8_t second, uint8_t frame, int buffer);

/**
 * \brief Builds or verifies the Q-subchannel data for a sector.
 *
 * When subchannel data is available, compares the cached Q fields against
 * the expected MSF and counts mismatches; otherwise synthesizes the Q
 * entry from the MSF. Writes 8 bytes into buffer.
 *
 * \param minute BCD minute of the sector.
 * \param second BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param buffer Output buffer for the Q-subchannel data (8 bytes).
 * \return The BCD frame, or 0 when at least two mismatches were detected.
 */
char iso_verify_sub(uint8_t minute, uint8_t second, char frame, int buffer);
