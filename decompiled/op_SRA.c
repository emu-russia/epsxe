#include "pch.h"
char sub_41E260()
{
  int v0; // edx
  char result; // al

  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAE = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> byte_576DAE;
  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DAD = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = v0;
  return result;
}
