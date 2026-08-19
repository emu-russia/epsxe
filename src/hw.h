#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char hw_regs[0x10000];
extern unsigned int sio_irq_pending;
extern unsigned int dma_int_ctrl;
extern unsigned int rcnt_counter[1];
extern unsigned int rcnt_mode[1];
extern unsigned int dma_channel_status[1];
extern unsigned int g_cdr_dma_channel_control;
extern unsigned int hw_saved_state;
extern unsigned int gpu_dma6_status;
extern unsigned int hw_update_counter;
extern unsigned int mdec_dma_control[1];
extern unsigned int mdec_dma_src[1];
extern unsigned int mdec_dma_status;
extern unsigned int mdec_param_count;

/* Function prototypes (previously generated in src/_gen) */
int hw_reg_freeze(const char *name, int gzf);
int16_t hw_reg_read_half(unsigned int addr);
int hw_reg_read_word(unsigned int addr);
int hw_reg_unfreeze(int unused, uint32_t *gzf);
void hw_reg_write_word(unsigned int addr, unsigned int value);
