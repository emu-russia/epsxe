#include "pch.h"
unsigned int sub_42B1E0()
{
  int v0; // ecx
  unsigned int result; // eax
  int v2; // eax

  v0 = reg_pc;
  result = *(_DWORD *)((unsigned __int16)reg_pc + mem_read_hooks[HIWORD(reg_pc)]);
  for ( cpu_opcode = result; reg_pc != 0x80030000; cpu_opcode = result )
  {
    reg_pc = v0 + 4;
    cpu_main_table[result >> 26]();
    v2 = --dword_50C270;
    if ( dword_50C270 < 0 )
    {
      dword_50C270 = dword_455940 + v2;
      if ( ++dword_50C364 >= (unsigned int)dword_45593C )
      {
        dword_50C364 = 0;
        ++dword_50C360;
      }
    }
    v0 = reg_pc;
    result = *(_DWORD *)((unsigned __int16)reg_pc + mem_read_hooks[HIWORD(reg_pc)]);
  }
  return result;
}
