#include "pch.h"
int __cdecl sub_407FA0(int a1, int a2)
{
  unsigned __int16 v2; // si
  int v3; // ebp
  unsigned __int8 *v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // ecx

  v2 = 0;
  v3 = 0;
  if ( a2 > 0 )
  {
    v4 = (unsigned __int8 *)(a1 + 1);
    do
    {
      v5 = *(v4 - 1);
      v6 = *v4;
      v4 += 2;
      v7 = v6 + (v5 << 8);
      v3 += v7;
      v2 ^= v7;
    }
    while ( (int)&v4[-1 - a1] < a2 );
  }
  return v2 ^ (v3 << 16);
}
