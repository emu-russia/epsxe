#include "pch.h"
int op_SWL()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  unsigned int v2; // edi
  int word; // eax
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
  v1 = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  v2 = v1 & 0xFFFFFFFC;
  word = mem_read_word(v1 & 0xFFFFFFFC);
  switch ( v1 & 3 )
  {
    case 0u:
      result = mem_write_word(v2, HIBYTE(cpu_gpr[(unsigned __int8)op_rt]) | word & 0xFFFFFF00);
      break;
    case 1u:
      result = mem_write_word(v2, HIWORD(cpu_gpr[(unsigned __int8)op_rt]) | word & 0xFFFF0000);
      break;
    case 2u:
      result = mem_write_word(v2, ((unsigned int)cpu_gpr[(unsigned __int8)op_rt] >> 8) | word & 0xFF000000);
      break;
    case 3u:
      result = mem_write_word(v2, cpu_gpr[(unsigned __int8)op_rt]);
      break;
  }
  return result;
}
