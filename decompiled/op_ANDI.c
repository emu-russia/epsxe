#include "pch.h"
int op_ANDI()
{
  int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  result = (unsigned __int16)cpu_opcode & cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}
