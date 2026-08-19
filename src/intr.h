#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int sio_irq_timeout;
extern unsigned int sio_irq_delay_time;
extern unsigned int rcnt_target[1];
extern unsigned int rcnt_compare[1];
extern unsigned int irq_hw_regs_a[1];
extern unsigned int irq_hw_regs_b[1];
extern unsigned int irq_hw_regs_c[1];
extern unsigned int irq_hw_regs_d[0x4d];
extern unsigned int irq_hw_regs_e[1];
extern unsigned int irq_hw_regs_f[1];
extern unsigned int irq_hw_regs_g[0x2e];
extern unsigned int sio_transfer_timeout_saved;
extern unsigned int sio_pending_time_saved;
extern unsigned int sio_transfer_pending_saved[0x10];

/* Function prototypes (previously generated in src/_gen) */
char irq_clear_hw_regs();
unsigned int irq_cpu_interrupt();
int __cdecl irq_dma_assert_int(unsigned __int8 a1);
int irq_sio_update();
void irq_spu_registered_callback();
int __cdecl irq_unfreeze(int a1, _DWORD *a2);
