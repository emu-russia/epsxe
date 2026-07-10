#include "pch.h"
__int16 __cdecl sub_43CE80(_DWORD *a1, int *a2)
{
  int v2; // ebx
  int *v3; // eax
  int v4; // ebp
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // ecx
  int v11; // eax
  int v12; // edi
  int v13; // esi
  bool v14; // zf
  int v15; // edi
  _WORD *i; // ecx
  int v17; // edi
  _WORD *v18; // ebp
  int v19; // ebp
  int v20; // ecx
  _WORD *v21; // esi
  int v22; // eax
  int v24; // [esp+10h] [ebp-1Ch]
  int v25; // [esp+14h] [ebp-18h]
  int v26; // [esp+18h] [ebp-14h]
  _WORD *v27; // [esp+18h] [ebp-14h]
  int v28; // [esp+1Ch] [ebp-10h]
  int v29; // [esp+20h] [ebp-Ch]
  int v30; // [esp+24h] [ebp-8h]
  int v31; // [esp+28h] [ebp-4h]
  int *v32; // [esp+30h] [ebp+4h]
  int v33; // [esp+30h] [ebp+4h]
  int v34; // [esp+34h] [ebp+8h]

  v2 = *a2;
  v3 = (int *)a2[2];
  v28 = a2[1];
  v4 = v3[4];
  v25 = *v3;
  v30 = v3[1];
  v29 = v3[2];
  v24 = 0;
  memset(a1 + 717, 0, 0x20u);
  v6 = a1[1299];
  v31 = v4;
  *(_WORD *)(v2 + 4 * a1[v6 + 725] + 2) = 0;
  v7 = a1[1299] + 1;
  if ( v7 < 573 )
  {
    v32 = &a1[v7 + 725];
    v8 = 573 - v7;
    v9 = 573;
    v26 = v8;
    v34 = 573;
    do
    {
      v10 = *v32;
      v11 = *(unsigned __int16 *)(v2 + 4 * *(unsigned __int16 *)(v2 + 4 * *v32 + 2) + 2) + 1;
      if ( v11 > v4 )
      {
        v11 = v4;
        ++v24;
      }
      *(_WORD *)(v2 + 4 * v10 + 2) = v11;
      if ( v10 <= v28 )
      {
        ++*((_WORD *)a1 + v11 + 1434);
        v12 = 0;
        if ( v10 >= v29 )
          v12 = *(_DWORD *)(v30 + 4 * (v10 - v29));
        v13 = *(unsigned __int16 *)(v2 + 4 * v10);
        a1[1448] += v13 * (v12 + v11);
        if ( v25 )
        {
          v4 = v31;
          a1[1449] += v13 * (v12 + *(unsigned __int16 *)(v25 + 4 * v10 + 2));
        }
        v9 = 573;
      }
      LOWORD(v6) = v26 - 1;
      v14 = v26 == 1;
      ++v32;
      --v26;
    }
    while ( !v14 );
    v15 = v24;
    if ( v24 )
    {
      do
      {
        v6 = v4 - 1;
        for ( i = (_WORD *)a1 + v4 + 1433; !*i; --v6 )
          --i;
        --*((_WORD *)a1 + v6 + 1434);
        *((_WORD *)a1 + v6 + 1435) += 2;
        --*((_WORD *)a1 + v4 + 1434);
        v15 -= 2;
      }
      while ( v15 > 0 );
      v17 = v4;
      if ( v4 )
      {
        v18 = (_WORD *)a1 + v4 + 1434;
        v27 = v18;
        do
        {
          v6 = (unsigned __int16)*v18;
          v33 = v6;
          if ( *v18 )
          {
            v19 = (int)&a1[v9 + 725];
            do
            {
              v20 = *(_DWORD *)(v19 - 4);
              v19 -= 4;
              --v34;
              if ( v20 <= v28 )
              {
                v21 = (_WORD *)(v2 + 4 * v20 + 2);
                HIWORD(v22) = 0;
                if ( (unsigned __int16)*v21 != v17 )
                {
                  LOWORD(v22) = *v21;
                  a1[1448] += *(unsigned __int16 *)(v2 + 4 * v20) * (v17 - v22);
                  *v21 = v17;
                }
                v6 = --v33;
              }
            }
            while ( v6 );
            v9 = v34;
          }
          --v17;
          v18 = --v27;
        }
        while ( v17 );
      }
    }
  }
  return v6;
}
