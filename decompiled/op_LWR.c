#include "pch.h"
unsigned int sub_41D750()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  unsigned int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  byte_576DAC = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  result = mem_read_word(v1 & 0xFFFFFFFC);
  if ( byte_576DB0 )
  {
    switch ( v1 & 3 )
    {
      case 0u:
        cpu_gpr[(unsigned __int8)byte_576DB0] = result;
        break;
      case 1u:
        result >>= 8;
        cpu_gpr[(unsigned __int8)byte_576DB0] = result | cpu_gpr[(unsigned __int8)byte_576DB0] & 0xFF000000;
        break;
      case 2u:
        result >>= 16;
        cpu_gpr[(unsigned __int8)byte_576DB0] = result | cpu_gpr[(unsigned __int8)byte_576DB0] & 0xFFFF0000;
        break;
      case 3u:
        result >>= 24;
        cpu_gpr[(unsigned __int8)byte_576DB0] = result | cpu_gpr[(unsigned __int8)byte_576DB0] & 0xFFFFFF00;
        break;
    }
  }
  return result;
}
