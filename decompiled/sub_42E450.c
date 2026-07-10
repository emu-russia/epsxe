#include "pch.h"
char sub_42E450()
{
  char result; // al

  if ( byte_50C216 > -2 && byte_50C216 != 1 )
    --byte_50C216;
  result = byte_50C214;
  if ( byte_50C214 <= 0 )
  {
    if ( !byte_50C214 )
    {
      *(_DWORD *)dword_516500 &= ~0x1000000u;
      byte_50C214 = -1;
      result = dma_assert_int(2u);
      byte_50C216 = -2;
    }
  }
  else
  {
    return --byte_50C214;
  }
  return result;
}
