#include "pch.h"
int op_MFC0()
{
  int result; // eax

  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = BYTE2(cpu_opcode) & 0x1F;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  cpu_gpr[result] = dword_50C274[(unsigned __int16)cpu_opcode >> 11];
  return result;
}
