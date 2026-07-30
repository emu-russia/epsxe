#include "pch.h"
BOOL op_SLTIU()
{
  BOOL result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_imm = (unsigned __int16)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < (unsigned int)(unsigned __int16)cpu_opcode;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}
