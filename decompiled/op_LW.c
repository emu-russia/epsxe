#include "pch.h"
int op_LW()
{
  unsigned int v0; // ecx
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  if ( (cpu_opcode & 0x1F0000) == 0 )
    return mem_read_word(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  result = mem_read_word(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  cpu_gpr[(unsigned __int8)op_rt] = result;
  return result;
}
