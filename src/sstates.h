#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int gpu_freeze_counter;
extern unsigned char save_state_ver;
extern unsigned char state_file_from_cmdline[0x400];

/* Function prototypes (previously generated in src/_gen) */
char check_state_exists(uint8_t a1);
char get_gpu_freeze_counter();
char gpu_freeze_with_counter();
char set_gpu_freeze_counter(char a1);
uint32_t *state_load();
uint32_t *state_save();
