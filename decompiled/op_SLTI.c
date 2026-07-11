#include "pch.h"
BOOL op_SLTI()
{
  signed int v0; // esi
  BOOL result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA4 = v0;
  }
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < v0;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}
