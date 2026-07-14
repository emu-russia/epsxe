#include "pch.h"
int __cdecl sub_40CCF0(unsigned int a1)
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 24; ++i )
  {
    if ( (a1 & 1) != 0 )
      result = sub_40C5B0(i);
    a1 >>= 1;
  }
  return result;
}
