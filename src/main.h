#pragma once

extern uint8_t cd_savefake_flag;
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char memcard_enabled;
extern unsigned char current_dir_path;
extern unsigned char cpu_overclock_setting;
extern unsigned int dynarec_enabled;
extern unsigned char extsubchanhle;
extern unsigned char fastboot;
extern unsigned int forcepad;
extern unsigned char forcespu;
extern unsigned char gtrace;
extern unsigned int loaded_file_type;
extern unsigned int mdectiming;
extern unsigned char nocd;
extern unsigned int reset_flag;
extern unsigned char xa_read_enable;

/* Function prototypes (previously generated in src/_gen) */
void memset32(void* dst, unsigned int value, unsigned int count);
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
