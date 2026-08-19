#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char cd_extra_setting;
extern unsigned int cpu_speed_scale;
extern unsigned int rcnt2_mode;
extern unsigned int rcnt2_compare;
extern unsigned int int_mask;
extern unsigned int int_reg[1];
extern unsigned int recomp_buffer;
extern unsigned int recomp_code_base;
extern unsigned int recomp_metadata;

/* Function prototypes (previously generated in src/_gen) */
void dynarec_deinit();
int64_t dynarec_execute();
uint8_t *dynarec_init();
char *dynarec_invalidate();
unsigned int dynarec_invalidate_range(int addr, int count);
void nullsub_1();
