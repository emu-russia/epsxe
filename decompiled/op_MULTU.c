#include "pch.h"
unsigned __int64 op_MULTU()
{
  unsigned __int64 result; // rax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  result = (unsigned int)cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]
         * (unsigned __int64)(unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  __SET_PAIR__(cpu_HI, cpu_LO, result);
  return result;
}
