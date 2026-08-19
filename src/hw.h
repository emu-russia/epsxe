#pragma once

/**
 * \file hw.h
 * \brief PlayStation hardware register (HW) emulation.
 *
 * Declares the 64 KB hardware register mirror and the DMA, MDEC and
 * root-counter state owned by the hardware emulation, plus the
 * register read/write and save-state entry points.
 */

/* Decompiled globals (previously generated in src/_gen) */

/** \brief 64 KB mirror of the PlayStation hardware register space. */
extern unsigned char hw_regs[0x10000];

/** \brief Flag indicating a pending SIO interrupt. */
extern unsigned int sio_irq_pending;

/** \brief DMA interrupt control register (DICR). */
extern unsigned int dma_int_ctrl;

/** \brief Current count values of the root counters (PSX timers). */
extern unsigned int rcnt_counter[1];

/** \brief Mode registers of the root counters (PSX timers). */
extern unsigned int rcnt_mode[1];

/** \brief DMA channel status/control register values (DPCR/CHCR). */
extern unsigned int dma_channel_status[1];

/** \brief Control register of the CD-ROM DMA channel (CD CHCR). */
extern unsigned int g_cdr_dma_channel_control;

/** \brief Pointer (stored as an unsigned int) to the saved-state buffer for the hardware registers. */
extern unsigned int hw_saved_state;

/** \brief Status value of DMA channel 6 (GPU DMA). */
extern unsigned int gpu_dma6_status;

/** \brief Counter of emulated timing ticks since the last frame; used for timer and IRQ timing. */
extern unsigned int hw_update_counter;

/** \brief MDEC DMA control register values (CHCR). */
extern unsigned int mdec_dma_control[1];

/** \brief MDEC DMA source address register values (MADR). */
extern unsigned int mdec_dma_src[1];

/** \brief Status of the MDEC DMA. */
extern unsigned int mdec_dma_status;

/** \brief Number of MDEC parameters currently pending. */
extern unsigned int mdec_param_count;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Saves the hardware register state to a gzip save-state file.
 *
 * Writes a chunk tag, the DMA channel status, the saved-state value,
 * the MDEC DMA source registers and the whole 64 KB hw_regs mirror
 * to the gzip stream.
 *
 * \param name Chunk tag written to the save-state file.
 * \param gzf  gzip file handle of the save-state file.
 * \return The result of the last gzwrite() call.
 */
int hw_reg_freeze(const char *name, int gzf);

/**
 * \brief Reads a 16-bit value from a hardware register.
 *
 * Emulates the root counter (timer) registers, the SIO/controller
 * registers, the interrupt status/mask registers and the SPU
 * register space.
 *
 * \param addr Address of the hardware register.
 * \return The 16-bit register value.
 */
int16_t hw_reg_read_half(unsigned int addr);

/**
 * \brief Reads a 32-bit value from a hardware register.
 *
 * Emulates the GPU, MDEC, DMA, root counter, SIO and SPU register
 * spaces, returning the appropriate emulated value for each address.
 *
 * \param addr Address of the hardware register.
 * \return The 32-bit register value.
 */
int hw_reg_read_word(unsigned int addr);

/**
 * \brief Restores the hardware register state from a gzip save-state file.
 *
 * Reads back the chunk tag, DMA channel status, saved-state value,
 * MDEC DMA source registers and the hw_regs mirror written by
 * hw_reg_freeze().
 *
 * \param unused Unused parameter.
 * \param gzf    gzip file handle of the save-state file.
 * \return The result of the last gzread() call.
 */
int hw_reg_unfreeze(int unused, uint32_t *gzf);

/**
 * \brief Writes a 32-bit value to a hardware register.
 *
 * Dispatches the write to the appropriate subsystem: the raw hw_regs
 * mirror, the root counters (via irq_rcnt_write_reg), the SPU registers,
 * the CD-ROM DMA channel, SIO data/status or the DMA/GPU control
 * registers.
 *
 * \param addr  Address of the hardware register.
 * \param value 32-bit value to write.
 */
void hw_reg_write_word(unsigned int addr, unsigned int value);
