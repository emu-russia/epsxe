#include "pch.h"
void __cdecl mem_gpu_dma_write(unsigned int a1, unsigned int a2)
{
  if ( (dword_50C2A4 & 0x10000) == 0 )
  {
    if ( (a1 & 0xFF800000) == 0x1F800000 )
    {
      if ( a1 >= 0x1F801000 )
        hw_reg_write_word(a1, a2);
      else
        *(_DWORD *)&dcache[a1 & 0xFFF] = a2;
    }
    else
    {
      *(_DWORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    }
  }
}
