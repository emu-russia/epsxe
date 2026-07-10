#include "pch.h"
int __cdecl sub_43E010(int a1)
{
  int result; // eax
  int v2; // ecx
  int v3; // esi
  int v4; // edx
  unsigned __int8 v5; // cl

  result = a1;
  v2 = *(_DWORD *)(a1 + 5812);
  if ( v2 == 16 )
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
  else if ( v2 >= 8 )
  {
    *(_BYTE *)(*(_DWORD *)(a1 + 8) + *(_DWORD *)(a1 + 20)) = *(_BYTE *)(a1 + 5808);
    v5 = *(_BYTE *)(a1 + 5809);
    ++*(_DWORD *)(a1 + 20);
    *(_WORD *)(a1 + 5808) = v5;
    *(_DWORD *)(a1 + 5812) -= 8;
  }
  return result;
}
