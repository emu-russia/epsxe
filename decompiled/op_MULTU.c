#include "pch.h"
unsigned __int64 op_MULTU()
{
  unsigned __int64 result; // rax

  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  result = (unsigned int)cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]
         * (unsigned __int64)(unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  __SET_PAIR__(cpu_HI, cpu_LO, result);
  return result;
}
