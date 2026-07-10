#include "pch.h"
int op_LHU()
{
  unsigned int v0; // ecx
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  byte_576DAC = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  result = (unsigned __int16)mem_read_half(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  cpu_gpr[(unsigned __int8)byte_576DB0] = result;
  return result;
}
