#include "pch.h"
int __cdecl sub_43E0A0(int a1)
{
  int result; // eax
  int v2; // edx
  int v3; // esi
  int v4; // edx

  result = a1;
  v2 = *(_DWORD *)(a1 + 5812);
  if ( v2 <= 8 )
  {
    if ( v2 > 0 )
      *(_BYTE *)(*(_DWORD *)(a1 + 8) + (*(_DWORD *)(a1 + 20))++) = *(_BYTE *)(a1 + 5808);
    *(_WORD *)(a1 + 5808) = 0;
    *(_DWORD *)(a1 + 5812) = 0;
  }
  else
  {
    *(_BYTE *)(*(_DWORD *)(a1 + 8) + *(_DWORD *)(a1 + 20)) = *(_BYTE *)(a1 + 5808);
    v3 = *(_DWORD *)(a1 + 8);
    v4 = *(_DWORD *)(a1 + 20) + 1;
    *(_DWORD *)(a1 + 20) = v4;
    *(_BYTE *)(v3 + v4) = *(_BYTE *)(a1 + 5809);
    ++*(_DWORD *)(a1 + 20);
    *(_WORD *)(a1 + 5808) = 0;
    *(_DWORD *)(a1 + 5812) = 0;
  }
  return result;
}
