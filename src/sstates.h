#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int gpu_freeze_counter;
extern unsigned char save_state_ver;
extern unsigned char state_file_from_cmdline[0x400];

/* Function prototypes (previously generated in src/_gen) */
char __cdecl check_state_exists(unsigned __int8 a1);
char get_gpu_freeze_counter();
char gpu_freeze_with_counter();
char __cdecl set_gpu_freeze_counter(char a1);
_DWORD *state_load();
_DWORD *state_save();
