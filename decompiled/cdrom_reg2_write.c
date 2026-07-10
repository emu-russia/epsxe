#include "pch.h"
char __cdecl cdrom_reg2_write(char a1)
{
  char result; // al

  result = byte_50BF66;
  if ( !byte_50BF66 )
  {
    result = byte_50AF44[3];
    if ( byte_50AF44[3] == 2 )
    {
      if ( a1 == 7 && byte_50AF44[0] )
      {
        byte_50AEC2 = 1;
        byte_50AF44[0] = 0;
        byte_50AF44[3] = 0;
        return result;
      }
      goto LABEL_7;
    }
    if ( byte_50AF44[3] )
    {
LABEL_7:
      byte_50BF84 = a1;
      byte_50AF44[3] = 0;
      return result;
    }
    result = byte_50AF44[0];
    *((_BYTE *)&word_50AEC3 + (unsigned __int8)byte_50AF44[0]++) = a1;
    byte_50AF44[3] = 0;
  }
  return result;
}
