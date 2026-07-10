#include "pch.h"
int __cdecl sub_438CA0(int a1, char *a2, int a3)
{
  char *v4; // edi
  int v5; // eax
  int v7; // esi
  unsigned int v8; // eax
  size_t v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // esi
  int v13; // edi
  unsigned __int8 *v14; // esi
  int v15; // edx
  unsigned int v16; // ecx
  size_t v17; // eax
  int v18; // esi
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  char *Buffer; // [esp+Ch] [ebp-4h]
  char *v23; // [esp+14h] [ebp+4h]

  v4 = a2;
  if ( !a1 || *(_BYTE *)(a1 + 92) != 114 )
    return -2;
  v5 = *(_DWORD *)(a1 + 56);
  if ( v5 == -3 || v5 == -1 )
    return -1;
  if ( v5 == 1 )
    return 0;
  v7 = a3;
  Buffer = a2;
  *(_DWORD *)(a1 + 12) = a2;
  *(_DWORD *)(a1 + 16) = a3;
  if ( !a3 )
  {
LABEL_34:
    v20 = crc32_calc(*(_DWORD *)(a1 + 76), v4, *(_DWORD *)(a1 + 12) - (_DWORD)v4);
    v21 = *(_DWORD *)(a1 + 16);
    *(_DWORD *)(a1 + 76) = v20;
    return v7 - v21;
  }
  while ( 1 )
  {
    v8 = *(_DWORD *)(a1 + 4);
    if ( *(_DWORD *)(a1 + 88) )
      break;
    if ( !v8 && !*(_DWORD *)(a1 + 60) )
    {
      dword_4FFA10 = 0;
      v9 = fread(*(void **)(a1 + 68), 1u, 0x4000u, *(FILE **)(a1 + 64));
      *(_DWORD *)(a1 + 4) = v9;
      if ( !v9 )
      {
        v10 = *(_DWORD *)(a1 + 64);
        *(_DWORD *)(a1 + 60) = 1;
        if ( (*(_BYTE *)(v10 + 12) & 0x20) != 0 )
        {
          *(_DWORD *)(a1 + 56) = -1;
          goto LABEL_34;
        }
      }
      *(_DWORD *)a1 = *(_DWORD *)(a1 + 68);
    }
    v11 = sub_439770((unsigned __int8 **)a1, 0);
    *(_DWORD *)(a1 + 56) = v11;
    if ( v11 == 1 )
    {
      *(_DWORD *)(a1 + 76) = crc32_calc(*(_DWORD *)(a1 + 76), v4, *(_DWORD *)(a1 + 12) - (_DWORD)v4);
      v23 = *(char **)(a1 + 12);
      if ( sub_4393D0(a1) != *(_DWORD *)(a1 + 76) )
      {
        *(_DWORD *)(a1 + 56) = -3;
LABEL_17:
        v4 = v23;
        goto LABEL_18;
      }
      sub_4393D0(a1);
      sub_438A20(a1);
      if ( *(_DWORD *)(a1 + 56) )
        goto LABEL_17;
      v12 = *(_DWORD *)(a1 + 8);
      v13 = *(_DWORD *)(a1 + 20);
      sub_4395A0(a1);
      *(_DWORD *)(a1 + 8) = v12;
      *(_DWORD *)(a1 + 20) = v13;
      v4 = v23;
      v7 = a3;
      *(_DWORD *)(a1 + 76) = crc32_calc(0, 0, 0);
    }
LABEL_18:
    if ( *(_DWORD *)(a1 + 56) || *(_DWORD *)(a1 + 60) || !*(_DWORD *)(a1 + 16) )
      goto LABEL_34;
  }
  if ( v8 > *(_DWORD *)(a1 + 16) )
    v8 = *(_DWORD *)(a1 + 16);
  if ( v8 )
  {
    qmemcpy(*(void **)(a1 + 12), *(const void **)a1, v8);
    v14 = *(unsigned __int8 **)a1;
    v15 = *(_DWORD *)(a1 + 16);
    Buffer = &a2[v8];
    *(_DWORD *)(a1 + 12) = &a2[v8];
    v16 = *(_DWORD *)(a1 + 4) - v8;
    *(_DWORD *)a1 = &v14[v8];
    v7 = a3;
    *(_DWORD *)(a1 + 16) = v15 - v8;
    *(_DWORD *)(a1 + 4) = v16;
  }
  v17 = *(_DWORD *)(a1 + 16);
  if ( v17 )
    *(_DWORD *)(a1 + 16) -= fread(Buffer, 1u, v17, *(FILE **)(a1 + 64));
  v18 = v7 - *(_DWORD *)(a1 + 16);
  v19 = v18 + *(_DWORD *)(a1 + 20);
  *(_DWORD *)(a1 + 8) += v18;
  *(_DWORD *)(a1 + 20) = v19;
  if ( !v18 )
    *(_DWORD *)(a1 + 60) = 1;
  return v18;
}
