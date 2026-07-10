#include "pch.h"
char __cdecl sub_42B6C0(char a1)
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
        HIBYTE(byte_50AF44) = a1 & 1;
        return result;
      }
    }
    HIBYTE(byte_50AF44) = a1 & 1;
  }
  return result;
}
