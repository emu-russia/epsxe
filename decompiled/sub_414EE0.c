#include "pch.h"
int __cdecl sub_414EE0(int a1)
{
  int v1; // eax
  int v2; // ecx

  v1 = a1;
  if ( a1 < 0 )
    v1 = ~a1;
  v2 = 31;
  if ( !v1 )
    return 32;
  if ( v1 >= 0 )
  {
    do
      --v2;
    while ( ((1 << v2) & v1) == 0 );
  }
  return 31 - v2;
}
