#include "pch.h"
int __cdecl sub_43A060(_DWORD *a1)
{
  _DWORD *v1; // esi
  int v2; // edx

  if ( !a1 )
    return -2;
  v1 = (_DWORD *)a1[7];
  if ( !v1 || !a1[8] || !a1[9] )
    return -2;
  a1[5] = 0;
  a1[2] = 0;
  a1[6] = 0;
  a1[11] = 2;
  v2 = v1[2];
  v1[5] = 0;
  v1[4] = v2;
  if ( (int)v1[6] < 0 )
    v1[6] = 0;
  v1[1] = v1[6] != 0 ? 113 : 42;
  a1[12] = 1;
  v1[8] = 0;
  sub_43C580(v1);
  sub_43A770(v1);
  return 0;
}
