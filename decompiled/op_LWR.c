#include "pch.h"
unsigned int op_LWR()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  unsigned int result; // eax

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
  result = mem_read_word(v1 & 0xFFFFFFFC);
  if ( op_rt )
  {
    switch ( v1 & 3 )
    {
      case 0u:
        cpu_gpr[(unsigned __int8)op_rt] = result;
        break;
      case 1u:
        result >>= 8;
        cpu_gpr[(unsigned __int8)op_rt] = result | cpu_gpr[(unsigned __int8)op_rt] & 0xFF000000;
        break;
      case 2u:
        result >>= 16;
        cpu_gpr[(unsigned __int8)op_rt] = result | cpu_gpr[(unsigned __int8)op_rt] & 0xFFFF0000;
        break;
      case 3u:
        result >>= 24;
        cpu_gpr[(unsigned __int8)op_rt] = result | cpu_gpr[(unsigned __int8)op_rt] & 0xFFFFFF00;
        break;
    }
  }
  return result;
}
