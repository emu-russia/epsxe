#include "pch.h"
char __cdecl sub_42C4D0(char a1)
{
  char result; // al

  result = byte_50BF66;
  if ( byte_50BF66 )
  {
    if ( a1 == 32 )
      byte_50BF66 = 0;
  }
  else
  {
    result = a1;
    byte_50AF48 |= 0x40u;
    if ( HIBYTE(byte_50AF44) != 1 || (HIBYTE(byte_50AF44) = 2, a1 != 7) )
      HIBYTE(byte_50AF44) = 0;
    if ( byte_50AEC2 && a1 == 7 )
    {
      if ( BYTE1(byte_50AF44) == 1 && byte_50BF7D )
        --byte_50BF7D;
      result = byte_50AEC1;
      BYTE1(byte_50AF44) = 0;
      if ( (unsigned __int8)byte_50AEC1 >= (unsigned __int8)byte_50AEC0 && BYTE2(byte_50AF44) )
      {
        result = byte_50AF43;
        if ( byte_50AF43 )
        {
          qmemcpy(dword_50AE80, &dword_50AF03, (unsigned __int8)byte_50AF43);
          result = byte_50AF43;
          byte_50AEC0 = byte_50AF43;
          byte_50AEC1 = 0;
          byte_50AF43 = 0;
          byte_50AEC2 = 1;
        }
        *(_WORD *)((char *)&byte_50AF44 + 1) = BYTE2(byte_50AF44);
        if ( byte_50BF84 != 24 )
          result = cdrom_assert_int();
        if ( byte_50BF6A )
        {
          result = byte_50BF6B;
          if ( byte_50BF6B )
          {
            qmemcpy(&dword_50AF03, &dword_50BF6C, (unsigned __int8)byte_50BF6B);
            result = byte_50BF6B;
            byte_50AF43 = byte_50BF6B;
            byte_50AEC2 = 1;
            byte_50BF6B = 0;
          }
          BYTE2(byte_50AF44) = byte_50BF6A;
          byte_50BF6A = 0;
        }
      }
    }
  }
  return result;
}
