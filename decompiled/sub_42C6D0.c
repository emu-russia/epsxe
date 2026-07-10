#include "pch.h"
int __cdecl sub_42C6D0(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
  int v3; // ecx
  int v4; // eax

  v3 = a2 - 2;
  v4 = a1;
  if ( v3 < 0 )
  {
    v3 += 60;
    v4 = a1 - 1;
  }
  return a3 + 75 * (v3 + 60 * v4);
}
