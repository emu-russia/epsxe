#include "pch.h"
unsigned int op_MTLO()
{
  unsigned int result; // eax

  result = (unsigned int)cpu_opcode >> 21;
  LOBYTE(result) = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rs_0 = result;
  cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  return result;
}
