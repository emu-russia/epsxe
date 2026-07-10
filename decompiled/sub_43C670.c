#include "pch.h"
int __cdecl sub_43C670(int a1, int a2, int a3, int a4)
{
  int v4; // ecx
  int v5; // esi
  int v6; // ecx
  int v7; // edi
  int v8; // esi
  int v9; // esi

  v4 = *(_DWORD *)(a1 + 5812);
  if ( v4 <= 13 )
  {
    *(_WORD *)(a1 + 5808) |= a4 << v4;
    *(_DWORD *)(a1 + 5812) = v4 + 3;
  }
  else
  {
    v5 = a4 << v4;
    v6 = *(_DWORD *)(a1 + 8);
    *(_WORD *)(a1 + 5808) |= v5;
    *(_BYTE *)(v6 + *(_DWORD *)(a1 + 20)) = *(_BYTE *)(a1 + 5808);
    v7 = *(_DWORD *)(a1 + 8);
    LOBYTE(v6) = *(_BYTE *)(a1 + 5809);
    v8 = *(_DWORD *)(a1 + 20) + 1;
    *(_DWORD *)(a1 + 20) = v8;
    *(_BYTE *)(v7 + v8) = v6;
    v9 = *(_DWORD *)(a1 + 5812);
    ++*(_DWORD *)(a1 + 20);
    *(_DWORD *)(a1 + 5812) = v9 - 13;
    *(_WORD *)(a1 + 5808) = (unsigned __int16)a4 >> (16 - v9);
  }
  return sub_43E120(a1, a2, a3, 1);
}
