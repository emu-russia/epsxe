#include "pch.h"
unsigned int op_MTHI()
{
  unsigned int result; // eax

  result = (unsigned int)cpu_opcode >> 21;
  LOBYTE(result) = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  unk_576DAF = result;
  cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  return result;
}
