#include "pch.h"
char op_JR()
{
  unsigned int v0; // edx
  char result; // al

  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  cpu_opcode = *(_DWORD *)((unsigned __int16)reg_pc + mem_read_hooks[HIWORD(reg_pc)]);
  reg_pc = cpu_gpr[v0];
  result = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --dword_50C270;
  return result;
}
