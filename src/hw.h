#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char hw_regs[0x10000];
extern unsigned int sio_irq_pending;
extern unsigned int dma_int_ctrl;
extern unsigned int rcnt_counter[1];
extern unsigned int rcnt_mode[1];
extern unsigned int dma_channel_status[1];
extern unsigned int mdec_dma_bcr[1];
extern unsigned int g_cdr_dma_channel_control;
extern unsigned int pio_dma_chcr;
extern unsigned int dma6_madr;
extern unsigned int dma6_bcr;
extern unsigned int hw_saved_state;
extern unsigned int gpu_dma6_status;
extern unsigned int hw_update_counter;
extern unsigned int mdec_dma_control[1];
extern unsigned int mdec_dma_src[1];
extern unsigned int mdec_dma_status;
extern unsigned int mdec_param_count;

/* Function prototypes (previously generated in src/_gen) */
int __cdecl hw_reg_freeze(const char *a1, int a2);
__int16 __cdecl hw_reg_read_half(unsigned int a1);
int __cdecl hw_reg_read_word(unsigned int a1);
int __cdecl hw_reg_unfreeze(int a1, _DWORD *a2);
void __cdecl hw_reg_write_word(unsigned int a1, unsigned int a2);
