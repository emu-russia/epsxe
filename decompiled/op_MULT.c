#include "pch.h"
__int64 op_MULT()
{
  __int64 result; // rax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] * (__int64)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  __SET_PAIR__(cpu_HI, cpu_LO, result);
  return result;
}
