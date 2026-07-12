#include "pch.h"
unsigned int __cdecl sub_40E510(_DWORD *a1, int a2)
{
  int v3; // [esp+0h] [ebp-20h] BYREF
  int v4; // [esp+8h] [ebp-18h] BYREF
  _DWORD v5[4]; // [esp+10h] [ebp-10h] BYREF

  if ( !a1 || !a2 )
    return E_FAIL;
  a1[5] = 0;
  a1[8] = 0;
  a1[17] = 0;
  a1[18] = 0;
  a1[19] = 0;
  v5[1] = 0;
  v5[2] = 0;
  v3 = 0;
  v4 = 0;
  a1[10] = &v3;
  a1[12] = a1 + 16;
  a1[7] = -1;
  a1[11] = &v4;
  a1[20] = 1000000;
  v5[0] = 10000;
  v5[3] = 100000;
  a1[3] = 18;
  a1[4] = 20000;
  a1[9] = 1;
  a1[13] = 16;
  a1[14] = v5;
  a1[1] = 3;
  return (sub_40E3F0(a2, a1) & 0x80000000) == 0 ? 0 : E_FAIL;
}
