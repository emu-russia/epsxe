#pragma once

/**
 * \file dynarec.h
 * \brief Dynamic recompiler (dynarec): code-cache state and entry points.
 *
 * Declares the recompiler buffers (code buffer, code cache and
 * metadata), the timing/interrupt globals it shares with the
 * interpreter, and the functions that initialize, run and invalidate
 * the dynamically recompiled code.
 */

/* Decompiled globals (previously generated in src/_gen) */

/** \brief "CD extra" flag from the cheat database that adjusts scanline timing in the recompiler. */
extern unsigned char cd_extra_setting;

/** \brief CPU speed scale: number of timing ticks per scanline (the base timing unit). */
extern unsigned int cpu_speed_scale;

/** \brief Mode register of root counter 2 (PSX timer). */
extern unsigned int rcnt2_mode;

/** \brief Compare/target value of root counter 2. */
extern unsigned int rcnt2_compare;

/** \brief Interrupt mask register (I_MASK). */
extern unsigned int int_mask;

/** \brief Interrupt status register (I_STAT), accessed through this pointer. */
extern unsigned int int_reg[1];

/** \brief Start of the recompiler's code buffer, where generated x86 code is written. */
extern unsigned int recomp_buffer;

/** \brief Base of the recompiled-code cache / block lookup table. */
extern unsigned int recomp_code_base;

/** \brief Metadata table kept in parallel with the recompiled-code cache. */
extern unsigned int recomp_metadata;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Frees all buffers allocated by the dynamic recompiler.
 *
 * Releases recomp_buffer, recomp_code_base and recomp_metadata
 * (if they were allocated).
 */
void dynarec_deinit();

/**
 * \brief Builds a small x86 trampoline and jumps into the recompiled code.
 *
 * Emits a prologue that loads the CPU speed scale and the GPR array,
 * computes the offset of the recompiled block for the current PC,
 * resets spu_async_update_counter and calls into the recompiled code
 * entry point.
 *
 * \return The address of the recompiled block for the current PC
 *         (packed together with the code write pointer).
 */
int64_t dynarec_execute();

/**
 * \brief Allocates and initializes the dynamic recompiler.
 *
 * Allocates the recompiler buffers (code buffer, code cache and
 * metadata), fills the code cache with an invalid marker, and writes
 * the initial x86 entry stubs into the code buffer.
 *
 * \return Pointer past the generated entry stubs.
 */
uint8_t *dynarec_init();

/**
 * \brief Invalidates the entire recompiled-code cache.
 *
 * Fills the code cache with the invalid marker and resets the code
 * write pointer to the start of the code region.
 *
 * \return Pointer to the start of the code region.
 */
char *dynarec_invalidate();

/**
 * \brief Invalidates the recompiled blocks covering a range of CPU addresses.
 *
 * Marks the code-cache entries for the given address range as invalid
 * (back-filling until the previous entry or the cache start is reached)
 * and clears the corresponding range.
 *
 * \param addr  Starting CPU address of the range.
 * \param count Number of instructions in the range.
 * \return The final offset written in the code cache.
 */
unsigned int dynarec_invalidate_range(int addr, int count);

/** \brief Empty stub function (does nothing). */
void nullsub_1();
