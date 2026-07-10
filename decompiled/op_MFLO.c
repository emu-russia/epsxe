#include "pch.h"
char op_MFLO()
{
  char result; // al

  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DAD = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = cpu_LO;
  return result;
}
