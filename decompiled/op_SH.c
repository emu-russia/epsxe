#include "pch.h"
char op_SH()
{
  unsigned int v0; // esi

  v0 = (unsigned __int16)cpu_opcode;
  byte_576DAC = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  return mem_write_half(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F], cpu_gpr[BYTE2(cpu_opcode) & 0x1F]);
}
