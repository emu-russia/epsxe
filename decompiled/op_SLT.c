#include "pch.h"
int op_SLT()
{
  int v0; // esi
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = (unsigned __int16)cpu_opcode >> 11;
  cpu_gpr[result] = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < v0;
  return result;
}
