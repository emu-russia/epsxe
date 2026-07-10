#include "pch.h"
int __cdecl sub_42B020(unsigned __int8 a1)
{
  int result; // eax

  result = a1;
  if ( ((1 << (a1 + 16)) & dword_50BFC8) != 0 )
  {
    result = int_reg | 8;
    dword_50BFC8 |= 1 << (a1 + 24);
    int_reg |= 8u;
  }
  return result;
}
