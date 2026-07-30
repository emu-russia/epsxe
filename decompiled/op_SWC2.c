#include "pch.h"
void op_SWC2()
{
  unsigned int data_register; // eax

  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
    op_ofs = cpu_opcode | 0xFFFF0000;
  data_register = gte_read_data_register(BYTE2(cpu_opcode) & 0x1F);
  mem_write_word(op_ofs + cpu_gpr[(unsigned __int8)op_rs], data_register);
}
