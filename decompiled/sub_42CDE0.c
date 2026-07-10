#include "pch.h"
int sub_42CDE0()
{
  int result; // eax

  result = 0;
  byte_50AF4B = 0;
  byte_50AF4C = 2;
  dword_50BF58 = 0;
  if ( BYTE1(byte_50AF44) )
  {
    BYTE2(byte_50AF44) = 2;
    dword_50AF03 = 16;
    byte_50AF43 = 1;
  }
  else
  {
    BYTE1(byte_50AF44) = 2;
    dword_50AE80[0] = 16;
    byte_50AEC0 = 1;
    byte_50AEC1 = 0;
    byte_50AEC2 = 1;
    return cdrom_assert_int();
  }
  return result;
}
