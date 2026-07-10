#include "pch.h"
int __cdecl dma_assert_int(unsigned __int8 a1)
{
  int result; // eax

  result = a1;
  if ( ((1 << (a1 + 16)) & dword_50BFC8) != 0 )
  {
    result = int_reg | 8;
    dword_50BFC8 |= 1 << (a1 + 24);
    int_reg |= 8u;
  }
  return result;
}
