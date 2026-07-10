#include "pch.h"
char op_SLL()
{
  char result; // al

  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = result;
  byte_576DAE = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  if ( result )
    cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] << (((unsigned int)cpu_opcode >> 6)
                                                                                      & 0x1F);
  return result;
}
