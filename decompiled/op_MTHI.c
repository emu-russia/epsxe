#include "pch.h"
unsigned int sub_41E520()
{
  unsigned int result; // eax

  result = (unsigned int)cpu_opcode >> 21;
  LOBYTE(result) = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  unk_576DAF = result;
  HIDWORD(cpu_LO) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  return result;
}
