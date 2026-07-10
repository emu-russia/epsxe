#include "pch.h"
unsigned int op_ADDI()
{
  unsigned int v0; // esi
  unsigned int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA4 = v0;
  }
  result = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}
