#include "pch.h"
int op_MFC0()
{
  int result; // eax

  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = BYTE2(cpu_opcode) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  cpu_gpr[result] = cop0_regs[(unsigned __int16)cpu_opcode >> 11];
  return result;
}
