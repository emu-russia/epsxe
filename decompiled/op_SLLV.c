#include "pch.h"
int op_SLLV()
{
  char v0; // cl
  int result; // eax

  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] << v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}
