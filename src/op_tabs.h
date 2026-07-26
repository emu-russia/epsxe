#pragma once

typedef void (*OPCODE)();

extern OPCODE cpu_special_opcode_table[64];
extern OPCODE cpu_cop0_table[32];
extern OPCODE cpu_bcond_opcode_table[32];
extern OPCODE cpu_main_table[64];

void op_SPECIAL();
void op_BCONDZ();
void op_COP0();
