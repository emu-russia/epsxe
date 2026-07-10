#include "pch.h"
__int16 __cdecl sub_41CDF0(unsigned int a1)
{
  dword_50C270 -= 4;
  if ( (a1 & 0x1FC00000) != 0x1F800000 )
    return *(_WORD *)((unsigned __int16)a1 + ram[HIWORD(a1)]);
  if ( (unsigned __int16)a1 >= 0x1000u )
    return hw_reg_read_half(a1);
  return *(_WORD *)((char *)&dcache + (a1 & 0xFFF));
}
