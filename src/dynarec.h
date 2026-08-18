#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char byte_4558BC[16];
extern unsigned char byte_4558CC[16];
extern unsigned char byte_4558DC[16];
extern unsigned char byte_4558EC[16];
extern unsigned char byte_4558FC[12];
extern unsigned char byte_45590C[16];
extern unsigned char byte_45591C[15];
extern unsigned char byte_45592C[16];
extern unsigned char byte_455948;
extern unsigned char byte_455986;
extern unsigned char cd_extra_setting;
extern uint8_t *code_ptr;
extern unsigned int cpu_speed_scale;
extern unsigned int dword_45594F;
extern unsigned int dword_455958;
extern unsigned int dword_455960;
extern unsigned int dword_455968;
extern unsigned int dword_455972;
extern unsigned int dword_4FF9E8;
extern unsigned int dword_50BFF4;
extern unsigned int dword_50BFFC;
extern unsigned int dword_50C2B4[0xb];
extern unsigned int int_mask;
extern unsigned int int_reg[1];
extern unsigned int patch_offset_ptr;
extern unsigned int recomp_buffer;
extern unsigned int recomp_code_base;
extern unsigned int recomp_metadata;
extern unsigned short word_455984;

/* Function prototypes (previously generated in src/_gen) */
int __cdecl dynarec_compile(unsigned int ArgList, int a2);
void dynarec_deinit();
__int64 dynarec_execute();
char *dynarec_hw_update();
uint8_t *dynarec_init();
char *dynarec_invalidate();
unsigned int __cdecl dynarec_invalidate_range(int a1, int a2);
char *__cdecl dynarec_recompile_block(int a1);
void nullsub_1();
