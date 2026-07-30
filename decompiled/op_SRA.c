#include "pch.h"
char op_SRA()
{
  int v0; // edx
  char result; // al

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_sa = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> op_sa;
  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  op_rd = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = v0;
  return result;
}
