#include "pch.h"
void op_SWR()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  unsigned int v2; // edi
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
  v1 = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  v2 = v1 & 0xFFFFFFFC;
  word = mem_read_word(v1 & 0xFFFFFFFC);
  switch ( v1 & 3 )
  {
    case 0u:
      mem_write_word(v2, cpu_gpr[(unsigned __int8)op_rt]);
      break;
    case 1u:
      mem_write_word(v2, (cpu_gpr[(unsigned __int8)op_rt] << 8) | (unsigned __int8)word);
      break;
    case 2u:
      mem_write_word(v2, (cpu_gpr[(unsigned __int8)op_rt] << 16) | (unsigned __int16)word);
      break;
    case 3u:
      mem_write_word(v2, (cpu_gpr[(unsigned __int8)op_rt] << 24) | word & 0xFFFFFF);
      break;
  }
}
