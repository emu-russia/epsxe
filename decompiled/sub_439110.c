#include "pch.h"
int __cdecl sub_439110(int a1, int a2)
{
  BOOL v2; // ebx
  int v3; // eax
  size_t v4; // edi
  int v5; // edx
  int v6; // eax

  v2 = 0;
  if ( !a1 || *(_BYTE *)(a1 + 92) != 119 )
    return -2;
  *(_DWORD *)(a1 + 4) = 0;
  do
  {
    v3 = *(_DWORD *)(a1 + 16);
    v4 = 0x4000 - v3;
    if ( v3 != 0x4000 )
    {
      if ( fwrite(*(const void **)(a1 + 72), 1u, v4, *(FILE **)(a1 + 64)) != v4 )
      {
        *(_DWORD *)(a1 + 56) = -1;
        return -1;
      }
      v5 = *(_DWORD *)(a1 + 72);
      *(_DWORD *)(a1 + 16) = 0x4000;
      *(_DWORD *)(a1 + 12) = v5;
    }
    if ( v2 )
      break;
    v6 = sub_43A1B0(a1, a2);
    *(_DWORD *)(a1 + 56) = v6;
    if ( !v4 && v6 == -5 )
      *(_DWORD *)(a1 + 56) = 0;
    v2 = *(_DWORD *)(a1 + 16) || *(_DWORD *)(a1 + 56) == 1;
  }
  while ( *(_DWORD *)(a1 + 56) <= 1u );
  return *(_DWORD *)(a1 + 56) != 1 ? *(_DWORD *)(a1 + 56) : 0;
}
