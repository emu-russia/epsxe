#include "pch.h"
GTE_REG op_LWC2()
{
  unsigned int v0; // ecx
  int word; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    op_ofs = v0;
  }
  word = mem_read_word(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  return gte_write_data_register(op_rt, (GTE_REG)word);
}
