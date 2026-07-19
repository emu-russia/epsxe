#include "pch.h"
void __cdecl cdr_reg3_write(char a1)
{
  if ( byte_50BF66 )
  {
    if ( a1 == 32 )
      byte_50BF66 = 0;
  }
  else
  {
    byte_50AF07[65] |= 0x40u;
    if ( byte_50AF07[64] != 1 || (byte_50AF07[64] = 2, a1 != 7) )
      byte_50AF07[64] = 0;
    if ( byte_50AEC2 && a1 == 7 )
    {
      if ( byte_50AF07[62] == 1 && byte_50BF7D )
        --byte_50BF7D;
      byte_50AF07[62] = 0;
      if ( (unsigned __int8)byte_50AEC1 >= (unsigned __int8)byte_50AEC0 && byte_50AF07[63] )
      {
        if ( byte_50AF07[60] )
        {
          qmemcpy(dword_50AE80, &dword_50AF03, (unsigned __int8)byte_50AF07[60]);
          byte_50AEC0 = byte_50AF07[60];
          byte_50AEC1 = 0;
          byte_50AF07[60] = 0;
          byte_50AEC2 = 1;
        }
        byte_50AF07[62] = byte_50AF07[63];
        byte_50AF07[63] = 0;
        if ( byte_50BF84 != 24 )
          cdrom_assert_int();
        if ( byte_50BF6A )
        {
          if ( byte_50BF6B )
          {
            qmemcpy(&dword_50AF03, &dword_50BF6C, (unsigned __int8)byte_50BF6B);
            byte_50AF07[60] = byte_50BF6B;
            byte_50AEC2 = 1;
            byte_50BF6B = 0;
          }
          byte_50AF07[63] = byte_50BF6A;
          byte_50BF6A = 0;
        }
      }
    }
  }
}
