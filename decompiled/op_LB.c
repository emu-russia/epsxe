#include "pch.h"
int op_LB()
{
  unsigned int v0; // ecx
  int v1; // ecx
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    op_ofs = v0;
  }
  mem_hw_reg_read_byte(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  v1 = (unsigned __int8)op_rt;
  result = (unsigned __int8)result;
  cpu_gpr[(unsigned __int8)op_rt] = (unsigned __int8)result;
  if ( (result & 0x80u) != 0 )
  {
    result |= 0xFFFFFF00;
    cpu_gpr[v1] = result;
  }
  return result;
}
