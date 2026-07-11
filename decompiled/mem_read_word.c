#include "pch.h"
int __cdecl mem_read_word(unsigned int a1)
{
  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) != 0x1F800000 )
    return *(_DWORD *)((unsigned __int16)a1 + mem_read_hooks[HIWORD(a1)]);
  if ( (unsigned __int16)a1 >= 0x1000u )
    return hw_reg_read_word(a1);
  return *(_DWORD *)&dcache[a1 & 0xFFF];
}
