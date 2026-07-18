#include "pch.h"
unsigned int __cdecl diSetupConstantForceEffect(int a1, int a2)
{
  _DWORD *v2; // eax
  int v3; // edx
  _DWORD v5[2]; // [esp+0h] [ebp-10h] BYREF
  _DWORD v6[2]; // [esp+8h] [ebp-8h] BYREF

  v2 = (_DWORD *)a1;
  if ( !a1 )
    return E_FAIL;
  v3 = a2;
  if ( !a2 )
    return E_FAIL;
  *(_DWORD *)(a1 + 40) = v5;
  v2[5] = 0;
  v2[8] = 0;
  v2[11] = v6;
  v5[0] = 0;
  v6[0] = 0;
  v6[1] = 0;
  v2[12] = 0;
  v2[7] = -1;
  a1 = 10000;
  v5[1] = 4;
  v2[3] = 34;
  v2[4] = 20000;
  v2[9] = 2;
  v2[13] = 4;
  v2[14] = &a1;
  v2[1] = 1;
  return (diCreateEffectHelper(v3, v2) & 0x80000000) == 0 ? 0 : 0x80004005;
}
