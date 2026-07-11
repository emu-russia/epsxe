#include "pch.h"
unsigned int op_SRLV()
{
  char v0; // cl
  unsigned int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}
