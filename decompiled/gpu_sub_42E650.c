#include "pch.h"
char gpu_sub_42E650()
{
  char result; // al

  result = byte_50C215;
  if ( byte_50C215 <= 0 )
  {
    if ( !byte_50C215 )
    {
      *(_DWORD *)dword_516530 &= ~0x1000000u;
      byte_50C215 = -1;
      return irq_dma_assert_int(6u);
    }
  }
  else
  {
    return --byte_50C215;
  }
  return result;
}
