#include "pch.h"
char __cdecl cdr_reg2_write(char a1)
{
  char result; // al

  result = byte_50BF66;
  if ( !byte_50BF66 )
  {
    result = byte_50AF07[64];
    if ( byte_50AF07[64] == 2 )
    {
      if ( a1 == 7 && byte_50AF07[61] )
      {
        byte_50AEC2 = 1;
        byte_50AF07[61] = 0;
        byte_50AF07[64] = 0;
        return result;
      }
      goto LABEL_7;
    }
    if ( byte_50AF07[64] )
    {
LABEL_7:
      byte_50BF84 = a1;
      byte_50AF07[64] = 0;
      return result;
    }
    result = byte_50AF07[61];
    *((_BYTE *)&word_50AEC3 + (unsigned __int8)byte_50AF07[61]++) = a1;
    byte_50AF07[64] = 0;
  }
  return result;
}
