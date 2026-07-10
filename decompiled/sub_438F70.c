#include "pch.h"
int __cdecl sub_438F70(int a1, int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  const void *v7; // [esp-18h] [ebp-1Ch]
  FILE *v8; // [esp-Ch] [ebp-10h]

  if ( !a1 || *(_BYTE *)(a1 + 92) != 119 )
    return -2;
  *(_DWORD *)a1 = a2;
  *(_DWORD *)(a1 + 4) = a3;
  if ( !a3 )
    goto LABEL_11;
  while ( 1 )
  {
    if ( *(_DWORD *)(a1 + 16) )
      goto LABEL_7;
    v8 = *(FILE **)(a1 + 64);
    v7 = *(const void **)(a1 + 72);
    *(_DWORD *)(a1 + 12) = v7;
    if ( fwrite(v7, 1u, 0x4000u, v8) != 0x4000 )
      break;
    *(_DWORD *)(a1 + 16) = 0x4000;
LABEL_7:
    v3 = sub_43A1B0(a1, 0);
    *(_DWORD *)(a1 + 56) = v3;
    if ( v3 || !*(_DWORD *)(a1 + 4) )
      goto LABEL_11;
  }
  *(_DWORD *)(a1 + 56) = -1;
LABEL_11:
  v4 = crc32_calc(*(_DWORD *)(a1 + 76), a2, a3);
  v5 = *(_DWORD *)(a1 + 4);
  *(_DWORD *)(a1 + 76) = v4;
  return a3 - v5;
}
