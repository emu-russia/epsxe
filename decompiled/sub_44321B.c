#include "pch.h"
unsigned int __cdecl sub_44321B(unsigned int a1, _DWORD *a2, unsigned int *a3)
{
  _UNKNOWN **v3; // ecx

  v3 = &off_458EC0;
  while ( a1 <= (unsigned int)v3[4] || a1 >= (unsigned int)v3[5] )
  {
    v3 = (_UNKNOWN **)*v3;
    if ( v3 == &off_458EC0 )
      return 0;
  }
  if ( (a1 & 0xF) == 0 && (a1 & 0xFFF) >= 0x100 )
  {
    *a2 = v3;
    *a3 = a1 & 0xFFFFF000;
    return ((int)(a1 - (a1 & 0xFFFFF000) - 256) >> 4) + (a1 & 0xFFFFF000) + 8;
  }
  return 0;
}
