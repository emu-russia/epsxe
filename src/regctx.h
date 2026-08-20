#pragma once

/**
 * \file regctx.h
 * \brief Reconstructed CPU / IRQ / MDEC register contexts.
 *
 * In the original binary the emulated CPU and peripheral register state
 * lived in contiguous context blocks that the savestate code saves/restores
 * as whole chunks ("PSX" = 0x16C bytes from the PC, "IRQ" = 0x290 bytes from
 * the interrupt status register, MDEC = 0x60 bytes from the command register).
 *
 * The decompiler split those blocks into unrelated named globals and, for
 * the PC, left a bare pointer (`reg_pc`) that was never initialized, so
 * cpu_clear_regs() dereferenced NULL and crashed at startup (issue #28).
 *
 * These structs restore the original layout: the PC register is the first
 * member of the CPU context, and the former "pointer" globals (reg_pc,
 * int_reg, sio_irq_timeout, sio_irq_delay_time, sio_irq_pending, mdec_command,
 * hw_saved_state, gpu_dma6_status, spu_dma_chcr_ptr) now point into the
 * reconstructed contexts instead of being raw integers that got dereferenced.
 */

/*--- CPU context (0x16C bytes, the original "PSX" savestate chunk) ---*/

/**
 * \brief CPU register file: PC first, then GPRs, LO/HI, COP0 and status regs.
 *
 * The size is padded to 0x16C bytes to match the CPU block that
 * state_save()/state_load() read and write through reg_pc.
 */
typedef struct {
    uint32_t reg_pc;        /* 0x00: program counter (first member) */
    uint32_t gpr[32];       /* 0x04: general purpose registers */
    uint32_t lo;            /* 0x84: multiply/divide low word */
    uint32_t hi;            /* 0x88: multiply/divide high word */
    uint32_t cop0[16];      /* 0x8C: COP0 register file */
    uint32_t cop0_sr;       /* 0xCC: COP0 status register (r12) */
    uint32_t cop0_cause;    /* 0xD0: COP0 cause register (r13) */
    uint32_t cop0_epc;      /* 0xD4: COP0 exception PC (r14) */
    uint32_t reserved[37];  /* 0xD8..0x16B: remainder of the 0x16C-byte chunk */
} cpu_registers;

extern cpu_registers cpu_regs;

/** \brief Pointer to the CPU context (== &cpu_regs.reg_pc, the PC is the first member). */
extern unsigned char *reg_pc;

#define cpu_gpr      (cpu_regs.gpr)
#define cpu_LO       (cpu_regs.lo)
#define cpu_HI       (cpu_regs.hi)
#define cop0_regs    (cpu_regs.cop0)
#define cop0_sr      (cpu_regs.cop0_sr)
#define cop0_cause   (cpu_regs.cop0_cause)
#define cop0_epc     (cpu_regs.cop0_epc)

/*--- IRQ / SIO interrupt context (0x290 bytes from int_reg) ---*/

/**
 * \brief Interrupt and SIO IRQ state.
 *
 * Padded to 0x290 bytes to match the "IRQ" savestate chunk that is read and
 * written through int_reg. int_reg[1] aliases int_mask (I_STAT/I_MASK are
 * adjacent in the original layout, hw_regs[1F801070h/74h]).
 */
typedef struct {
    uint32_t int_reg;           /* 0x00: I_STAT (1F801070h) */
    uint32_t int_mask;          /* 0x04: I_MASK (1F801074h) */
    uint32_t sio_irq_timeout;   /* 0x08: SIO IRQ timeout tick */
    uint32_t sio_irq_delay_time;/* 0x0C: SIO IRQ delay tick */
    uint32_t sio_irq_pending;   /* 0x10: pending SIO IRQ bits */
    uint8_t  reserved[0x290 - 0x14]; /* 0x14..0x28F: remainder of the chunk */
} irq_registers;

extern irq_registers irq_state;

extern unsigned int *int_reg;   /* == &irq_state.int_reg; int_reg[1] == int_mask */
extern unsigned int *sio_irq_timeout;    /* == &irq_state.sio_irq_timeout */
extern unsigned int *sio_irq_delay_time; /* == &irq_state.sio_irq_delay_time */
extern unsigned int *sio_irq_pending;    /* == &irq_state.sio_irq_pending */

#define int_mask           (irq_state.int_mask)

/*--- MDEC command context (0x60 bytes from mdec_command) ---*/

/**
 * \brief MDEC command/state block (0x60 bytes, the "MDE" savestate chunk).
 */
typedef struct {
    uint32_t command;           /* 0x00: MDEC command register */
    uint8_t  reserved[0x60 - 4];/* 0x04..0x5F: remainder of the chunk */
} mdec_registers;

extern mdec_registers mdec_regs;
