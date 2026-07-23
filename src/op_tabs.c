#include "pch.h"
void __noreturn op_SPECIAL()
{
  cpu_special_opcode_table[cpu_opcode & 0x3F]();
}

void __noreturn op_BCONDZ()
{
  cpu_bcond_opcode_table[BYTE2(cpu_opcode) & 0x1F]();
}

void __noreturn op_COP0()
{
  cpu_cop0_table[((unsigned int)cpu_opcode >> 21) & 0x1F]();
}

