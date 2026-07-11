#include "pch.h"
void op_LBU()
{
  unsigned int v0; // ecx
  unsigned __int8 v1; // al

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  if ( (cpu_opcode & 0x1F0000) != 0 )
  {
    hw_reg_read_byte(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
    cpu_gpr[(unsigned __int8)op_rt] = v1;
  }
  else
  {
    hw_reg_read_byte(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  }
}
