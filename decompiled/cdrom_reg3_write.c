#include "pch.h"
void __cdecl cdrom_reg3_write(char a1)
{
  if ( byte_50BF66 )
  {
    if ( a1 == 32 )
      byte_50BF66 = 0;
  }
  else
  {
    byte_50AF48 |= 0x40u;
    if ( byte_50AF44[3] != 1 || (byte_50AF44[3] = 2, a1 != 7) )
      byte_50AF44[3] = 0;
    if ( byte_50AEC2 && a1 == 7 )
    {
      if ( byte_50AF44[1] == 1 && byte_50BF7D )
        --byte_50BF7D;
      byte_50AF44[1] = 0;
      if ( (unsigned __int8)byte_50AEC1 >= (unsigned __int8)byte_50AEC0 && byte_50AF44[2] )
      {
        if ( byte_50AF43 )
        {
          qmemcpy(&dword_50AE80, &dword_50AF03, (unsigned __int8)byte_50AF43);
          byte_50AEC0 = byte_50AF43;
          byte_50AEC1 = 0;
          byte_50AF43 = 0;
          byte_50AEC2 = 1;
        }
        byte_50AF44[1] = byte_50AF44[2];
        byte_50AF44[2] = 0;
        if ( byte_50BF84 != 24 )
          cdrom_assert_int();
        if ( byte_50BF6A )
        {
          if ( byte_50BF6B )
          {
            qmemcpy(&dword_50AF03, &dword_50BF6C, (unsigned __int8)byte_50BF6B);
            byte_50AF43 = byte_50BF6B;
            byte_50AEC2 = 1;
            byte_50BF6B = 0;
          }
          byte_50AF44[2] = byte_50BF6A;
          byte_50BF6A = 0;
        }
      }
    }
  }
}
