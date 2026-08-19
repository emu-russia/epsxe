#pragma once

/**
 * \file mdec.h
 * \brief Declarations for the MDEC (macroblock decoder) subsystem.
 *
 * Emulates the PlayStation MDEC, the hardware macroblock decoder used for
 * FMV playback. Decodes compressed (RL-coded, IDCT) video data into RGB or
 * monochrome frames in main RAM and handles the MDEC command, DMA and timer
 * interface.
 */

/* Decompiled globals (previously generated in src/_gen) */
/** \brief MDEC status register (decoding/busy state). */
extern unsigned int mdec_status;
/** \brief Timer count used by the MDEC decode timer. */
extern unsigned int mdec_timer_count;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Decodes one MDEC frame from the input buffer into RAM.
 *
 * Run-length decodes the compressed macroblocks, applies the IDCT, and
 * converts the result to RGB (or monochrome) in main RAM at the DMA
 * destination address. When the decode timer is enabled, sets the busy
 * status and arms the timer.
 *
 * \return The number of pixels (or, when the timer is enabled, the current
 *         timer value).
 */
int mdec_decode();
/**
 * \brief Handles an MDEC DMA-in transfer.
 *
 * When the DMA control word selects MDEC, reads the pending command and
 * prepares the input pointer / scale table for decoding.
 */
void mdec_dma_in_handler();
/**
 * \brief Writes the MDEC state into a save state file.
 *
 * Serializes the command buffer and scale table (plus padding) into the
 * gzip stream, prefixed with the \p filename tag.
 *
 * \param filename Save state section tag.
 * \param file     gzip file handle opened by the save state code.
 * \return The result of the final gzwrite() call.
 */
int mdec_freeze(const char *filename, int file);
/**
 * \brief Writes a reduced MDEC state into a save state file.
 *
 * Serializes only the command buffer into the gzip stream, prefixed with
 * the \p filename tag.
 *
 * \param filename Save state section tag.
 * \param file     gzip file handle opened by the save state code.
 * \return The result of the final gzwrite() call.
 */
int mdec_freeze2(const char *filename, int file);
/**
 * \brief Handles special MDEC commands.
 *
 * For command 0x80000000, points the input pointer at the current output
 * address.
 *
 * \param command The MDEC command word.
 * \return The current output address for command 0x80000000 (value
 *         undefined otherwise).
 */
int mdec_handle_special_command(int command);
/**
 * \brief Initializes the MDEC subsystem.
 *
 * Clears the command/parameter state and the decode timer, sets up the
 * block pointers and builds the color conversion tables.
 *
 * \return The result of initializing the color tables.
 */
int mdec_init();
/**
 * \brief Per-frame MDEC timer handler.
 *
 * Decrements the decode timer; when it reaches zero, clears the busy
 * status and asserts the DMA IRQ.
 *
 * \return The current timer value after the update.
 */
char mdec_timer_handler();
/**
 * \brief Restores the full MDEC state from a save state file.
 *
 * Reads back the command buffer and scale table from the gzip stream.
 *
 * \param unused Unused parameter.
 * \param file   gzip file handle opened by the save state code.
 * \return The result of the final gzread() call.
 */
int mdec_unfreeze(int unused, uint32_t *file);
/**
 * \brief Restores the reduced MDEC state from a save state file.
 *
 * Reads back only the command buffer from the gzip stream.
 *
 * \param unused Unused parameter.
 * \param file   gzip file handle opened by the save state code.
 * \return The result of the final gzread() call.
 */
int mdec_unfreeze2(int unused, uint32_t *file);
/**
 * \brief Stores an MDEC command word and extracts its bit-15 flag.
 *
 * \param command The MDEC command word to store.
 * \return The bit-15 flag extracted from the command (bit 15 of
 *         (command >> 10)).
 */
int16_t mdec_write_command(unsigned int command);
