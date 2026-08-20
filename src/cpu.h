#pragma once

/**
 * \file cpu.h
 * \brief MIPS R3000 CPU core: register state and interpreter entry points.
 *
 * Declares the emulated CPU state (GPRs, HI/LO, PC, COP0, timing counters)
 * and the interpreter loop used to execute the BIOS shell and the main
 * program, including cheat handling, IRQ servicing and per-scanline
 * timing updates.
 */

/** \brief The opcode currently being decoded/executed by the interpreter. */
extern uint32_t cpu_opcode;

/* Note: the CPU register state (cpu_gpr, cpu_HI, cpu_LO, cop0_regs, cop0_sr,
 * cop0_cause, cop0_epc, reg_pc) now lives in the cpu_registers context
 * declared in regctx.h; cpu_gpr/cpu_HI/cpu_LO/cop0_* are macros for the
 * corresponding struct members there. */

/* Decompiled globals (previously generated in src/_gen) */

/** \brief Counts scanline updates to pace the SPU async update callback (fired every 32 updates). */
extern unsigned int spu_async_update_counter;

/** \brief Scheduled timeout (in timing ticks) for the next SIO transfer. */
extern unsigned int sio_scheduled_transfer_timeout;

/** \brief Current count of root counter 1 (PSX timer). */
extern unsigned int rcnt1_counter;

/** \brief Mode register of root counter 1. */
extern unsigned int rcnt1_mode;

/** \brief Compare/target value of root counter 1. */
extern unsigned int rcnt1_compare;

/** \brief Current count of root counter 2 (PSX timer). */
extern unsigned int rcnt2_counter;

/** \brief Current count of root counter 3 (incremented once per frame). */
extern unsigned int rcnt3_counter;

/** \brief Number of SPU IRQs currently pending delivery. */
extern unsigned int spu_irq_pending_count;

/** \brief Number of completed frames since emulation start. */
extern unsigned int frame_counter;

/** \brief Scanline counter within the current frame. */
extern unsigned int scanline_counter;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Resets the CPU register state and timing counters.
 *
 * Sets the PC to the BIOS uncached base, zeroes the GPRs, the COP0
 * registers, HI/LO and the frame/scanline timing counters.
 *
 * \return 0.
 */
int cpu_clear_regs();

/**
 * \brief Runs the CPU interpreter loop until a reset is requested.
 *
 * Fetches and dispatches one instruction per iteration (with cheat
 * patching applied), services interrupts and updates the scanline/frame
 * timing counters, invoking the per-scanline hardware updates (SPU,
 * MDEC, GPU DMA, CD-ROM, SIO, root counters) and calling the frame
 * update at the end of each frame.
 *
 * \return Non-zero if emulation was reset, 0 otherwise.
 */
int cpu_execute();

/**
 * \brief Runs the BIOS shell code from the boot location.
 *
 * Executes instructions from the current PC through the main dispatch
 * table until the PC reaches 0x80030000, at which point control passes
 * to the loaded game.
 *
 * \return The opcode of the last instruction fetched before the shell
 *         end address was reached.
 */
unsigned int cpu_load_bios_shell();
