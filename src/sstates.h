#pragma once

/**
 * \file sstates.h
 * \brief Declarations for the save state subsystem.
 *
 * Saves and restores the full emulator state (CPU, memory, hardware
 * registers, IRQ, GTE, CD-ROM, SIO, MDEC, GPU and SPU) to/from gzip
 * compressed files in the "sstates" directory, and manages the GPU freeze
 * slot counter.
 */

/* Decompiled globals (previously generated in src/_gen) */
/** \brief Current save state slot counter (0-4), used in the state file name. */
extern unsigned int gpu_freeze_counter;
/** \brief Save state version number (0xFF selects the current version). */
extern unsigned char save_state_ver;
/** \brief Save state file path given on the command line ("NULL" when none). */
extern unsigned char state_file_from_cmdline[0x400];

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Checks whether a save state file exists for the given slot.
 *
 * \param slot Save state slot number (0-4).
 * \return 0 if the file exists, -1 otherwise.
 */
char check_state_exists(uint8_t slot);
/**
 * \brief Returns the current GPU freeze slot counter.
 *
 * \return The value of gpu_freeze_counter.
 */
char get_gpu_freeze_counter();
/**
 * \brief Advances the GPU freeze slot counter and freezes the GPU state.
 *
 * Increments gpu_freeze_counter modulo 5 and calls gpu_do_freeze() with the
 * new value, which lets the GPU plugin manage per-slot state.
 *
 * \return The new counter value.
 */
char gpu_freeze_with_counter();
/**
 * \brief Sets the GPU freeze slot counter.
 *
 * \param value The new counter value.
 * \return The value that was set.
 */
char set_gpu_freeze_counter(char value);
/**
 * \brief Loads a save state from disk and restores the emulator state.
 *
 * Opens "sstates\\<game>.NNN" (or the command-line file) and feeds it to
 * the mem/hw_reg/irq/gte/cdr/sio/mdec/gpu/spu unfreeze routines, honoring
 * the version stored in the file header.
 *
 * \return The result of the final gzclose() call (NULL if the file could
 *         not be opened).
 */
uint32_t *state_load();
/**
 * \brief Saves the current emulator state to disk.
 *
 * Opens "sstates\\<game>.NNN" (NNN = gpu_freeze_counter) and feeds the
 * current state through the mem/hw_reg/irq/gte/cdr/sio/mdec/gpu/spu freeze
 * routines, writing a header with the save state version.
 *
 * \return The result of the final gzclose() call (NULL if the file could
 *         not be opened).
 */
uint32_t *state_save();
