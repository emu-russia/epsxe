#include "pch.h"
int __cdecl sub_43A460(int a1, __int16 a2)
{
  int v3; // esi
  int v4; // edx

  *(_BYTE *)(*(_DWORD *)(a1 + 8) + *(_DWORD *)(a1 + 20)) = HIBYTE(a2);
  v3 = *(_DWORD *)(a1 + 8);
  v4 = *(_DWORD *)(a1 + 20) + 1;
  *(_DWORD *)(a1 + 20) = v4;
  *(_BYTE *)(v3 + v4) = a2;
  ++*(_DWORD *)(a1 + 20);
  return a1;
}
