#include "pch.h"
int __cdecl sub_43A970(int a1)
{
  unsigned int v1; // ebp
  unsigned int v2; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  unsigned int v6; // ecx
  int v7; // esi
  int v8; // ecx
  _WORD *v9; // ecx
  __int16 v10; // ax
  unsigned int v11; // esi
  _WORD *v12; // ecx
  __int16 v13; // ax
  int result; // eax
  unsigned int v15; // esi
  int v16; // ecx
  unsigned __int8 *v17; // edi
  int v18; // eax

  v1 = *(_DWORD *)(a1 + 36);
  do
  {
    v2 = *(_DWORD *)(a1 + 100);
    v3 = *(_DWORD *)(a1 + 108);
    v4 = *(_DWORD *)(a1 + 52) - v2 - v3;
    if ( v4 )
    {
      if ( v4 == -1 )
      {
        v4 = -2;
        goto LABEL_20;
      }
    }
    else if ( !v2 && !v3 )
    {
      v4 = v1;
      goto LABEL_20;
    }
    if ( v2 >= *(_DWORD *)(a1 + 36) + v1 - 262 )
    {
      qmemcpy(*(void **)(a1 + 48), (const void *)(*(_DWORD *)(a1 + 48) + v1), v1);
      v5 = *(_DWORD *)(a1 + 84);
      v6 = *(_DWORD *)(a1 + 100) - v1;
      *(_DWORD *)(a1 + 104) -= v1;
      v7 = *(_DWORD *)(a1 + 68);
      *(_DWORD *)(a1 + 100) = v6;
      v8 = *(_DWORD *)(a1 + 60);
      *(_DWORD *)(a1 + 84) = v5 - v1;
      v9 = (_WORD *)(v8 + 2 * v7);
      do
      {
        if ( (unsigned __int16)*--v9 < v1 )
          v10 = 0;
        else
          v10 = *v9 - v1;
        --v7;
        *v9 = v10;
      }
      while ( v7 );
      v11 = v1;
      v12 = (_WORD *)(*(_DWORD *)(a1 + 56) + 2 * v1);
      do
      {
        if ( (unsigned __int16)*--v12 < v1 )
          v13 = 0;
        else
          v13 = *v12 - v1;
        --v11;
        *v12 = v13;
      }
      while ( v11 );
      v4 += v1;
    }
LABEL_20:
    result = *(_DWORD *)a1;
    if ( !*(_DWORD *)(*(_DWORD *)a1 + 4) )
      break;
    result = sub_43AAA0(result, *(_DWORD *)(a1 + 48) + *(_DWORD *)(a1 + 100) + *(_DWORD *)(a1 + 108), v4);
    v15 = result + *(_DWORD *)(a1 + 108);
    *(_DWORD *)(a1 + 108) = v15;
    if ( v15 >= 3 )
    {
      v16 = *(_DWORD *)(a1 + 80);
      v17 = (unsigned __int8 *)(*(_DWORD *)(a1 + 100) + *(_DWORD *)(a1 + 48));
      v18 = *v17;
      *(_DWORD *)(a1 + 64) = v18;
      result = *(_DWORD *)(a1 + 76) & (v17[1] ^ (v18 << v16));
      *(_DWORD *)(a1 + 64) = result;
    }
    if ( v15 >= 0x106 )
      break;
    result = *(_DWORD *)(*(_DWORD *)a1 + 4);
  }
  while ( result );
  return result;
}
