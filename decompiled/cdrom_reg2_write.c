#include "pch.h"
char __cdecl sub_42C460(char a1)
{
  char result; // al

  result = byte_50BF66;
  if ( !byte_50BF66 )
  {
    result = HIBYTE(byte_50AF44);
    if ( HIBYTE(byte_50AF44) == 2 )
    {
      if ( a1 == 7 && (_BYTE)byte_50AF44 )
      {
        byte_50AEC2 = 1;
        LOBYTE(byte_50AF44) = 0;
        HIBYTE(byte_50AF44) = 0;
        return result;
      }
      goto LABEL_7;
    }
    if ( HIBYTE(byte_50AF44) )
    {
LABEL_7:
      byte_50BF84 = a1;
      HIBYTE(byte_50AF44) = 0;
      return result;
    }
    result = byte_50AF44;
    word_50AEC3[(unsigned __int8)byte_50AF44] = a1;
    LOBYTE(byte_50AF44) = byte_50AF44 + 1;
    HIBYTE(byte_50AF44) = 0;
  }
  return result;
}
