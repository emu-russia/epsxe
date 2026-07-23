#include "pch.h"
int __cdecl irq_dma_assert_int(unsigned __int8 a1)
{
  int result; // eax

  result = a1;
  if ( ((1 << (a1 + 16)) & dword_50BFC8) != 0 )
  {
    result = *(_DWORD *)int_reg | 8;
    dword_50BFC8 |= 1 << (a1 + 24);
    *(_DWORD *)int_reg |= 8u;
  }
  return result;
}
