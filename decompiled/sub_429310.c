#include "pch.h"
char sub_429310()
{
  char result; // al

  result = mdectiming;
  if ( mdectiming )
  {
    result = byte_4FC508;
    if ( byte_4FC508 <= 0 )
    {
      if ( !byte_4FC508 )
      {
        dword_4FC504 = 0;
        dword_5164F4 &= ~0x1000000u;
        byte_4FC508 = -1;
        dma_assert_int(1u);
        result = byte_4FC508;
      }
    }
    else
    {
      result = --byte_4FC508;
    }
    if ( result < 0 )
    {
      if ( result <= -10 )
        dword_4FC4F8 = 0;
      else
        byte_4FC508 = --result;
    }
  }
  return result;
}
