#include "pch.h"
int __cdecl sub_436B50(int a1, int a2, unsigned int a3)
{
  unsigned int i; // eax
  unsigned int v4; // edi
  bool v5; // cf
  int v6; // ebp
  unsigned int v7; // esi
  int v8; // eax
  unsigned int v9; // ebx
  unsigned int v10; // eax
  int v11; // edx
  int v12; // ebp
  int j; // eax
  _DWORD *v14; // eax
  unsigned __int8 *v15; // ecx
  int v16; // eax
  int v17; // esi
  int k; // eax
  _DWORD *v19; // eax
  unsigned int v21; // [esp+4h] [ebp+4h]
  unsigned __int8 v22; // [esp+Ch] [ebp+Ch]

  dword_4FFC24 = malloc(0x145320u);
  for ( i = 0; i < 0x145320; i += 4 )
    *(_DWORD *)((char *)dword_4FFC24 + i) = 0;
  v4 = a3;
  v5 = a3 < a1 + a3;
  v21 = a1 + a3;
  if ( v5 )
  {
    do
    {
      v6 = a2;
      v7 = *(_DWORD *)(v4 + a2) / 0x930u;
      v8 = *((_DWORD *)dword_4FFC24 + v7);
      v9 = 2352 - *(_DWORD *)(v4 + a2) % 0x930u;
      v22 = *(_BYTE *)(v4 + a2 + 4);
      if ( v8 )
      {
        v12 = *((_DWORD *)dword_4FFC24 + v7);
        for ( j = *(_DWORD *)(v8 + 8); j; j = *(_DWORD *)(j + 8) )
          v12 = j;
        v14 = malloc(8u);
        *(_DWORD *)(v12 + 8) = v14;
        v14[1] = v4 + 5;
        *(_WORD *)(*(_DWORD *)(v12 + 8) + 2) = *(_DWORD *)(v4 + a2) % 0x930u;
        v15 = *(unsigned __int8 **)(v12 + 8);
        v10 = v22;
        if ( v22 > v9 )
          *v15 = v9;
        else
          *v15 = v22;
        v11 = *(_DWORD *)(v12 + 8);
        v6 = a2;
      }
      else
      {
        *((_DWORD *)dword_4FFC24 + v7) = malloc(8u);
        *(_DWORD *)(*((_DWORD *)dword_4FFC24 + v7) + 4) = v4 + 5;
        v10 = v22;
        *(_WORD *)(*((_DWORD *)dword_4FFC24 + v7) + 2) = *(_DWORD *)(v4 + a2) % 0x930u;
        if ( v22 > v9 )
          **((_BYTE **)dword_4FFC24 + v7) = v9;
        else
          **((_BYTE **)dword_4FFC24 + v7) = *(_BYTE *)(v4 + a2 + 4);
        v11 = *((_DWORD *)dword_4FFC24 + v7);
      }
      *(_DWORD *)(v11 + 8) = 0;
      if ( v10 > v9 )
      {
        v16 = *((_DWORD *)dword_4FFC24 + v7 + 1);
        if ( v16 )
        {
          v17 = *((_DWORD *)dword_4FFC24 + v7 + 1);
          for ( k = *(_DWORD *)(v16 + 8); k; k = *(_DWORD *)(k + 8) )
            v17 = k;
          v19 = malloc(8u);
          *(_DWORD *)(v17 + 8) = v19;
          v19[1] = v9 + v4 + 5;
          *(_WORD *)(*(_DWORD *)(v17 + 8) + 2) = 0;
          **(_BYTE **)(v17 + 8) = v22 - v9;
          *(_DWORD *)(*(_DWORD *)(v17 + 8) + 8) = 0;
        }
        else
        {
          *((_DWORD *)dword_4FFC24 + v7 + 1) = malloc(8u);
          *(_DWORD *)(*((_DWORD *)dword_4FFC24 + v7 + 1) + 4) = v9 + v4 + 5;
          *(_WORD *)(*((_DWORD *)dword_4FFC24 + v7 + 1) + 2) = 0;
          **((_BYTE **)dword_4FFC24 + v7 + 1) = v22 - v9;
          *(_DWORD *)(*((_DWORD *)dword_4FFC24 + v7 + 1) + 8) = 0;
        }
      }
      v4 += *(unsigned __int8 *)(v4 + v6 + 4) + 5;
    }
    while ( v4 < v21 );
  }
  return dbg_print(aDone);
}
