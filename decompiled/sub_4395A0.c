#include "pch.h"
int __cdecl sub_4395A0(_DWORD *a1)
{
  _DWORD *v1; // ecx

  if ( !a1 )
    return -2;
  v1 = (_DWORD *)a1[7];
  if ( !v1 )
    return -2;
  a1[5] = 0;
  a1[2] = 0;
  a1[6] = 0;
  *v1 = v1[3] != 0 ? 7 : 0;
  sub_43B5A0(*(_DWORD *)(a1[7] + 20), a1, 0);
  return 0;
}
