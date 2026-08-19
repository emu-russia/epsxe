#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int sio_irq_timeout;
extern unsigned int sio_irq_delay_time;
extern unsigned int rcnt_target[1];
extern unsigned int rcnt_compare[1];

/* Function prototypes (previously generated in src/_gen) */
char irq_clear_hw_regs();
unsigned int irq_cpu_interrupt();
int irq_dma_assert_int(uint8_t channel);
int irq_sio_update();
void irq_spu_registered_callback();
int irq_unfreeze(int magic, uint32_t *fp);
void irq_cdrom_assert_int();
void irq_sio_assert_int();
char irq_rcnt_write_reg(uint16_t reg, int value);
int irq_freeze(const char* magic, int fp);