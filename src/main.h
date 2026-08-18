#pragma once

extern uint8_t cd_savefake_flag;
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char byte_4557A8;
extern unsigned char byte_45B8CC;
extern unsigned char byte_4F831D;
extern unsigned char byte_8B2580[0x400];
extern unsigned char cheat_file_from_cmdline[0x400];
extern unsigned char cpu_overclock_setting;
extern unsigned int dword_50C370;
extern unsigned int dynarec_enabled;
extern unsigned char extsubchanhle;
extern unsigned char fastboot;
extern unsigned int forcepad;
extern unsigned char forcespu;
extern unsigned char gtrace;
extern unsigned char ignore_cmd;
extern unsigned int loaded_file_type;
extern unsigned int mdectiming;
extern unsigned char nocd;
extern unsigned char old_auto_ppf_load;
extern unsigned int reset_flag;
extern unsigned char xa_read_enable;

/* Function prototypes (previously generated in src/_gen) */
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
void epsxe_main_loop_runner();
int __cdecl parse_command_line_options(int a1, int a2);
void print_develop_options();
void print_usage();
void print_version();
