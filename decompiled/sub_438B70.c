#include "pch.h"
int __cdecl sub_438B70(int a1)
{
  int result; // eax
  size_t v2; // eax
  int v3; // edx

  if ( *(_DWORD *)(a1 + 60) )
    return -1;
  if ( *(_DWORD *)(a1 + 4) )
    goto LABEL_8;
  dword_4FFA10 = 0;
  v2 = fread(*(void **)(a1 + 68), 1u, 0x4000u, *(FILE **)(a1 + 64));
  *(_DWORD *)(a1 + 4) = v2;
  if ( v2 )
  {
    *(_DWORD *)a1 = *(_DWORD *)(a1 + 68);
LABEL_8:
    --*(_DWORD *)(a1 + 4);
    return *(unsigned __int8 *)(*(_DWORD *)a1)++;
  }
  v3 = *(_DWORD *)(a1 + 64);
  *(_DWORD *)(a1 + 60) = 1;
  result = -1;
  if ( (*(_BYTE *)(v3 + 12) & 0x20) != 0 )
    *(_DWORD *)(a1 + 56) = -1;
  return result;
}
