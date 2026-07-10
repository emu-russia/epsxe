#include "pch.h"
int __cdecl sub_40CD20(unsigned int a1)
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 24; ++i )
  {
    if ( (a1 & 1) != 0 )
      result = sub_40C5F0(i);
    a1 >>= 1;
  }
  return result;
}
