#pragma once

/**
 * \file intr.h
 * \brief Interrupt (IRQ) handling for the emulated PlayStation.
 *
 * Declares the interrupt status/timing globals (SIO IRQ scheduling
 * and root counter target/compare registers) and the functions that
 * raise, service and save/restore interrupts and timer state.
 */

/* Decompiled globals (previously generated in src/_gen) */

/* sio_irq_timeout, sio_irq_delay_time, sio_irq_pending and int_reg are now
 * pointers into the irq_registers context declared in regctx.h. */

/** \brief Target register values of the root counters (PSX timers). */
extern unsigned int rcnt_target[16];

/** \brief Compare register values of the root counters (PSX timers). */
extern unsigned int rcnt_compare[16];

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Clears all interrupt and timer state.
 *
 * Zeroes the IRQ shadow register arrays and the root counter
 * registers, and resets the SPU IRQ count, the DMA/GPU delay
 * counters and the SIO transfer/IRQ state.
 *
 * \return -1.
 */
char irq_clear_hw_regs();

/**
 * \brief Services a pending CPU interrupt, taking the exception if enabled.
 *
 * If any bit of int_reg is set in int_mask and interrupts are enabled
 * (cop0_sr IE bit and exception level 0), saves the PC into cop0_epc,
 * sets cop0_cause, jumps to the exception vector 0x80000080 and
 * updates cop0_sr to the kernel mode.
 *
 * \return The status value: int_reg when no exception was taken,
 *         otherwise the updated cop0_sr.
 */
unsigned int irq_cpu_interrupt();

/**
 * \brief Raises the DMA interrupt bit (0x8) in I_STAT.
 *
 * If the DMA interrupt for the given channel is enabled in dma_int_ctrl,
 * sets the DMA interrupt flag and the pending DMA bit in int_reg.
 *
 * \param channel DMA channel number.
 * \return The channel number, or the updated I_STAT value when the
 *         interrupt was raised.
 */
int irq_dma_assert_int(uint8_t channel);

/**
 * \brief Schedules the SIO interrupt.
 *
 * Depending on the current cycle count, either sets the SIO IRQ delay
 * time (clearing any pending SIO IRQ) or sets the SIO IRQ timeout and
 * marks the SIO IRQ pending.
 *
 * \return The delay/timeout value that was set.
 */
int irq_sio_update();

/**
 * \brief Registers a pending SPU interrupt.
 *
 * Increments the pending SPU IRQ count; called from the SPU plugin
 * callback when an SPU IRQ occurs.
 */
void irq_spu_registered_callback();

/**
 * \brief Restores the interrupt state from a gzip save-state file.
 *
 * Reads back the chunk tag, SIO IRQ timeout/delay/pending values and
 * the interrupt registers, and restores the saved SIO transfer state.
 *
 * \param magic Chunk tag read from the save-state file.
 * \param fp    gzip file handle of the save-state file.
 * \return The restored SIO transfer-pending flag.
 */
int irq_unfreeze(int magic, uint32_t *fp);

/**
 * \brief Sets the CD-ROM interrupt bit (0x4) in I_STAT.
 */
void irq_cdrom_assert_int();

/**
 * \brief Sets the SIO interrupt bit (0x80) in I_STAT.
 */
void irq_sio_assert_int();

/**
 * \brief Handles a write to a root counter (timer) register.
 *
 * Applies the write to the count, mode or target registers of the
 * root counters (including the legacy "timer 3"), updating the
 * compare value and applying the Parasite Eve cheat workaround.
 *
 * \param reg   Address of the root counter register.
 * \param value Value being written.
 * \return The computed register offset.
 */
char irq_rcnt_write_reg(uint16_t reg, int value);

/**
 * \brief Saves the interrupt state to a gzip save-state file.
 *
 * Writes a chunk tag, the SIO IRQ timeout/delay/pending values and
 * the interrupt register block, saving the SIO transfer state along
 * the way.
 *
 * \param magic Chunk tag written to the save-state file.
 * \param fp    gzip file handle of the save-state file.
 * \return The result of the last gzwrite() call.
 */
int irq_freeze(const char* magic, int fp);
