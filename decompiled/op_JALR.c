#include "pch.h"
int op_JALR()
{
  int v0; // esi
  int v1; // ebx
  unsigned int v2; // ecx

  v0 = mem_read_hooks[HIWORD(reg_pc)];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  v1 = (unsigned __int16)cpu_opcode >> 11;
  v2 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  cpu_opcode = *(_DWORD *)((unsigned __int16)reg_pc + v0);
  cpu_gpr[v1] = reg_pc + 4;
  reg_pc = cpu_gpr[v2];
  cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  return --dword_50C270;
}
