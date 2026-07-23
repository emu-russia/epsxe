#include "pch.h"
void sub_42CDE0()
{
  byte_50AF07[68] = 0;
  byte_50AF07[69] = 2;
  dword_50BF58 = 0;
  if ( byte_50AF07[62] )
  {
    byte_50AF07[63] = 2;
    LOBYTE(dword_50AF03) = 16;
    byte_50AF07[60] = 1;
  }
  else
  {
    byte_50AF07[62] = 2;
    dword_50AE80[0] = 16;
    byte_50AEC0 = 1;
    byte_50AEC1 = 0;
    byte_50AEC2 = 1;
    irq_cdrom_assert_int();
  }
}
