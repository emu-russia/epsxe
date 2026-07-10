#include "pch.h"
int __cdecl gpu_dma_read(unsigned int a1)
{
  if ( (a1 & 0xFF800000) != 0x1F800000 )
    return *(_DWORD *)((unsigned __int16)a1 + mem_read_hooks[HIWORD(a1)]);
  if ( a1 >= 0x1F801000 )
    return hw_reg_read_word(a1);
  return *(_DWORD *)&dcache[a1 & 0xFFF];
}
