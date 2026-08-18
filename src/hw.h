#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char byte_516600[0x10000];
extern unsigned int dword_4FD878;
extern unsigned int dword_50BFC8;
extern unsigned int dword_50BFD0[1];
extern unsigned int dword_50BFD4[1];
extern unsigned int dword_5164D0[1];
extern unsigned int dword_5164E4[1];
extern unsigned int dword_51650C;
extern unsigned int dword_516524;
extern unsigned int dword_516528;
extern unsigned int dword_51652C;
extern unsigned int dword_566964;
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
