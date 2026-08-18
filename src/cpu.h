#pragma once

extern uint32_t cpu_opcode;
extern uint32_t cpu_gpr[32];
extern uint32_t cpu_HI;
extern uint32_t cpu_LO;
extern unsigned char *reg_pc;
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int dword_4FC4EC;
extern unsigned int dword_4FD868;
extern unsigned int dword_50BFE0;
extern unsigned int dword_50BFE4;
extern unsigned int dword_50BFEC;
extern unsigned int dword_50BFF0;
extern unsigned int dword_50C000;
extern unsigned int dword_50C210;
extern unsigned int dword_50C360;
extern unsigned int dword_50C364;

/* Function prototypes (previously generated in src/_gen) */
int cpu_clear_regs();
int cpu_execute();
unsigned int cpu_load_bios_shell();
