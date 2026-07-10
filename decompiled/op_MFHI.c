#include "pch.h"
char sub_41E4C0()
{
  char result; // al

  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DAD = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = HIDWORD(cpu_LO);
  return result;
}
