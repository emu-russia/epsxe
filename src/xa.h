#pragma once

/**
 * \file xa.h
 * \brief Declarations for the XA-ADPCM audio decoding subsystem.
 *
 * Decodes CD-ROM XA sound sectors (stereo XA-ADPCM) into 16-bit PCM
 * samples, following the XA header to determine the audio mode, sample
 * rate and bit depth, and reports the result through the SPU.
 */

/* Decompiled globals (previously generated in src/_gen) */

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Decodes one XA-ADPCM sound sector.
 *
 * Checks the audio mode of the XA header; for stereo sectors, sets up the
 * ADPCM decoder, which writes the decoded samples (and sample rate / depth
 * information) into \p out and reports the new rate to the SPU.
 *
 * \param out  Output buffer: [0] sample rate, [1] bit depth, [2] stereo
 *             flag, [3] block size, then the decoded PCM samples.
 * \param hdr  Pointer to the XA sector header.
 * \param flag Non-zero on the first sector of a block (resets decoder state).
 * \return 0 on success, -1 on failure or for non-stereo sectors.
 */
int xa_decode_wrapper(uint32_t *out, int hdr, int flag);
