#include "pch.h"
char op_J()
{
  int v0; // ecx
  char result; // al

  dword_576DA0 = cpu_opcode & 0x3FFFFFF;
  v0 = 4 * (cpu_opcode & 0x3FFFFFF);
  cpu_opcode = *(_DWORD *)((unsigned __int16)reg_pc + ram[HIWORD(reg_pc)]);
  reg_pc = v0 | reg_pc & 0xF0000000;
  result = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --dword_50C270;
  return result;
}
