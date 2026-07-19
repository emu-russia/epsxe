#include "pch.h"
char __cdecl cdr_reg0_write(char a1)
{
  char result; // al

  result = byte_50BF66;
  if ( !byte_50BF66 )
  {
    result = a1 - 1;
    if ( a1 == 1 )
    {
      byte_50AEC2 = 1;
    }
    else
    {
      result = a1 - 2;
      if ( a1 == 2 )
      {
        byte_50BF66 = 1;
        byte_50AF07[64] = a1 & 1;
        return result;
      }
    }
    byte_50AF07[64] = a1 & 1;
  }
  return result;
}
