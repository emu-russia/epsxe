#include "pch.h"
void sub_42C8D0()
{
  if ( byte_50AF44[2] )
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
  }
  if ( byte_50BF6A )
  {
    if ( byte_50BF6B )
    {
      qmemcpy(&dword_50AF03, &dword_50BF6C, (unsigned __int8)byte_50BF6B);
      byte_50AF43 = byte_50BF6B;
      byte_50BF6B = 0;
    }
    byte_50AF44[2] = byte_50BF6A;
    byte_50BF6A = 0;
  }
}
