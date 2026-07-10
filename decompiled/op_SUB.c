#include "pch.h"
int op_SUB()
{
  int result; // eax

  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] - cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}
