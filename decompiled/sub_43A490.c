#include "pch.h"
_DWORD *__cdecl sub_43A490(int a1)
{
  _DWORD *result; // eax
  int v2; // esi
  unsigned int v3; // edx
  int v4; // ecx
  int v5; // ecx
  unsigned int v6; // edi

  result = (_DWORD *)a1;
  v2 = *(_DWORD *)(a1 + 28);
  v3 = *(_DWORD *)(v2 + 20);
  if ( v3 > *(_DWORD *)(a1 + 16) )
    v3 = *(_DWORD *)(a1 + 16);
  if ( v3 )
  {
    qmemcpy(*(void **)(a1 + 12), *(const void **)(v2 + 16), v3);
    v4 = *(_DWORD *)(a1 + 28);
    *(_DWORD *)(a1 + 12) += v3;
    *(_DWORD *)(v4 + 16) += v3;
    v5 = *(_DWORD *)(a1 + 28);
    v6 = *(_DWORD *)(a1 + 16) - v3;
    *(_DWORD *)(a1 + 20) += v3;
    *(_DWORD *)(a1 + 16) = v6;
    *(_DWORD *)(v5 + 20) -= v3;
    result = *(_DWORD **)(a1 + 28);
    if ( !result[5] )
      result[4] = result[2];
  }
  return result;
}
