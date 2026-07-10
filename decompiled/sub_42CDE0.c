#include "pch.h"
void sub_42CDE0()
{
  byte_50AF4B = 0;
  byte_50AF4C = 2;
  dword_50BF58 = 0;
  if ( byte_50AF44[1] )
  {
    byte_50AF44[2] = 2;
    LOBYTE(dword_50AF03) = 16;
    byte_50AF43 = 1;
  }
  else
  {
    byte_50AF44[1] = 2;
    LOBYTE(dword_50AE80) = 16;
    byte_50AEC0 = 1;
    byte_50AEC1 = 0;
    byte_50AEC2 = 1;
    cdrom_assert_int();
  }
}
