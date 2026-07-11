#include "pch.h"
int op_SWC2()
{
  int v0; // eax

  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
    dword_576DA8 = cpu_opcode | 0xFFFF0000;
  v0 = sub_41BA80(BYTE2(cpu_opcode) & 0x1F);
  return mem_write_word(dword_576DA8 + cpu_gpr[(unsigned __int8)op_rs], v0);
}
