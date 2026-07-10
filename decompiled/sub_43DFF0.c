#include "pch.h"
unsigned int __cdecl sub_43DFF0(unsigned int a1, int a2)
{
  unsigned int v4; // eax
  int v5; // esi

  v4 = 0;
  do
  {
    v5 = a1 & 1;
    a1 >>= 1;
    v4 = 2 * (v5 | v4);
    --a2;
  }
  while ( a2 > 0 );
  return v4 >> 1;
}
