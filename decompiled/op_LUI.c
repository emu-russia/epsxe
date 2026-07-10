#include "pch.h"
int op_LUI()
{
  int result; // eax

  dword_576DA4 = (unsigned __int16)cpu_opcode;
  result = (unsigned __int16)cpu_opcode << 16;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}
