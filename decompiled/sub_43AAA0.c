#include "pch.h"
unsigned int __cdecl sub_43AAA0(int *a1, void *a2, unsigned int a3)
{
  unsigned int v3; // ebx
  int v5; // eax

  v3 = a1[1];
  if ( v3 > a3 )
    v3 = a3;
  if ( !v3 )
    return 0;
  a1[1] -= v3;
  if ( !*(_DWORD *)(a1[7] + 24) )
    a1[12] = sub_43C450(a1[12], *a1, v3);
  qmemcpy(a2, (const void *)*a1, v3);
  v5 = a1[2];
  *a1 += v3;
  a1[2] = v3 + v5;
  return v3;
}
