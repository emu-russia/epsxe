#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char lwl_mask_table[16];
extern unsigned char lwl_shift_table[16];
extern unsigned char lwr_mask_table[16];
extern unsigned char lwr_shift_table[16];
extern unsigned char swl_mask_table[12];
extern unsigned char swl_shift_table[16];
extern unsigned char swr_mask_table[15];
extern unsigned char swr_shift_table[16];
extern unsigned char recomp_hw_write_template;
extern unsigned char recomp_hw_write_tail_byte;
extern unsigned char cd_extra_setting;
extern uint8_t *code_ptr;
extern unsigned int cpu_speed_scale;
extern unsigned int recomp_code_base_addr;
extern unsigned int recomp_buffer_addr;
extern unsigned int recomp_buffer_addr_2;
extern unsigned int recomp_metadata_addr;
extern unsigned int recomp_buffer_addr_3;
extern unsigned int recomp_special_flags;
extern unsigned int rcnt2_mode;
extern unsigned int rcnt2_compare;
extern unsigned int cpu_recomp_state[0xb];
extern unsigned int int_mask;
extern unsigned int int_reg[1];
extern unsigned int patch_offset_ptr;
extern unsigned int recomp_buffer;
extern unsigned int recomp_code_base;
extern unsigned int recomp_metadata;
extern unsigned short recomp_hw_write_tail_word;

/* Function prototypes (previously generated in src/_gen) */
void dynarec_deinit();
__int64 dynarec_execute();
uint8_t *dynarec_init();
char *dynarec_invalidate();
unsigned int __cdecl dynarec_invalidate_range(int a1, int a2);
void nullsub_1();
