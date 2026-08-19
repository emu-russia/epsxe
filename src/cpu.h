#pragma once

extern uint32_t cpu_opcode;
extern uint32_t cpu_gpr[32];
extern uint32_t cpu_HI;
extern uint32_t cpu_LO;
extern unsigned char *reg_pc;
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int spu_async_update_counter;
extern unsigned int sio_scheduled_transfer_timeout;
extern unsigned int rcnt1_counter;
extern unsigned int rcnt1_mode;
extern unsigned int rcnt1_compare;
extern unsigned int rcnt2_counter;
extern unsigned int rcnt3_counter;
extern unsigned int spu_irq_pending_count;
extern unsigned int frame_counter;
extern unsigned int scanline_counter;

/* Function prototypes (previously generated in src/_gen) */
int cpu_clear_regs();
int cpu_execute();
unsigned int cpu_load_bios_shell();
