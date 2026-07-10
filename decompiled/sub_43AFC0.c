#include "pch.h"
int __cdecl sub_43AFC0(_DWORD *a1, int a2)
{
  int v3; // edi
  unsigned int v4; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // eax
  unsigned int v9; // edx
  int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  unsigned int v13; // ebp
  __int16 v14; // ax
  unsigned __int16 v15; // ax
  int v16; // eax
  int v17; // eax
  BOOL v18; // ebx
  unsigned int v19; // edx
  int v20; // ecx
  int v21; // eax
  int v22; // eax
  int v23; // ecx
  int v24; // edx
  int v25; // eax
  unsigned __int8 v26; // al
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  int v36; // eax
  int v37; // [esp-14h] [ebp-28h]
  int v38; // [esp-14h] [ebp-28h]
  int v39; // [esp-14h] [ebp-28h]
  unsigned __int8 v40; // [esp+18h] [ebp+4h]
  unsigned __int8 v41; // [esp+1Ch] [ebp+8h]

  v3 = 0;
  while ( 1 )
  {
    v4 = a1[27];
    if ( v4 < 0x106 )
    {
      sub_43A970((int)a1);
      v4 = a1[27];
      if ( v4 < 0x106 && !a2 )
        return 0;
      if ( !v4 )
        break;
    }
    if ( v4 >= 3 )
    {
      v6 = a1[25];
      v7 = a1[15];
      v8 = a1[19] & (*(unsigned __int8 *)(a1[12] + v6 + 2) ^ (a1[16] << a1[20]));
      HIWORD(v3) = 0;
      a1[16] = v8;
      LOWORD(v3) = *(_WORD *)(v7 + 2 * v8);
      *(_WORD *)(a1[14] + 2 * (v6 & a1[11])) = v3;
      *(_WORD *)(a1[15] + 2 * a1[16]) = *((_WORD *)a1 + 50);
    }
    v9 = a1[22];
    v10 = a1[26];
    a1[28] = v9;
    a1[23] = v10;
    a1[22] = 2;
    if ( v3 && v9 < a1[30] && a1[25] - v3 <= (unsigned int)(a1[9] - 262) )
    {
      if ( a1[32] != 2 )
        a1[22] = sub_43AE50(a1, v3);
      v11 = a1[22];
      if ( v11 <= 5 && (a1[32] == 1 || v11 == 3 && (unsigned int)(a1[25] - a1[26]) > 0x1000) )
        a1[22] = 2;
    }
    v12 = a1[28];
    if ( v12 < 3 || a1[22] > v12 )
    {
      if ( a1[24] )
      {
        v26 = *(_BYTE *)(a1[25] + a1[12] - 1);
        *(_WORD *)(a1[1447] + 2 * a1[1446]) = 0;
        *(_BYTE *)(a1[1444] + a1[1446]++) = v26;
        ++LOWORD(a1[v26 + 35]);
        if ( a1[1446] == a1[1445] - 1 )
        {
          v27 = a1[21];
          if ( v27 < 0 )
            v28 = 0;
          else
            v28 = a1[12] + v27;
          sub_43C970(a1, v28, a1[25] - v27, 0);
          v38 = *a1;
          a1[21] = a1[25];
          sub_43A490(v38);
        }
        v29 = a1[27] - 1;
        ++a1[25];
        v30 = *a1;
        a1[27] = v29;
        if ( !*(_DWORD *)(v30 + 16) )
          return 0;
      }
      else
      {
        v31 = a1[25] + 1;
        v32 = a1[27] - 1;
        a1[24] = 1;
        a1[25] = v31;
        a1[27] = v32;
      }
    }
    else
    {
      v13 = a1[25] + a1[27] - 3;
      v14 = a1[25] - *((_WORD *)a1 + 46) - 1;
      v40 = *((_BYTE *)a1 + 112) - 3;
      *(_WORD *)(a1[1447] + 2 * a1[1446]) = v14;
      v15 = v14 - 1;
      *(_BYTE *)(a1[1444] + a1[1446]++) = v40;
      ++LOWORD(a1[(unsigned __int8)byte_4494B8[v40] + 292]);
      if ( v15 >= 0x100u )
        v16 = (unsigned __int8)byte_4493B8[v15 >> 7];
      else
        v16 = (unsigned __int8)byte_4492B8[v15];
      ++LOWORD(a1[v16 + 608]);
      v17 = a1[28];
      v18 = a1[1446] == a1[1445] - 1;
      a1[27] += 1 - v17;
      a1[28] = v17 - 2;
      do
      {
        v19 = a1[25] + 1;
        a1[25] = v19;
        if ( v19 <= v13 )
        {
          v20 = a1[15];
          v21 = a1[19] & (*(unsigned __int8 *)(a1[12] + v19 + 2) ^ (a1[16] << a1[20]));
          HIWORD(v3) = 0;
          a1[16] = v21;
          LOWORD(v3) = *(_WORD *)(v20 + 2 * v21);
          *(_WORD *)(a1[14] + 2 * (v19 & a1[11])) = v3;
          *(_WORD *)(a1[15] + 2 * a1[16]) = *((_WORD *)a1 + 50);
        }
        v22 = a1[28] - 1;
        a1[28] = v22;
      }
      while ( v22 );
      v23 = a1[25] + 1;
      a1[24] = 0;
      a1[22] = 2;
      a1[25] = v23;
      if ( v18 )
      {
        v24 = a1[21];
        v25 = v24 < 0 ? 0 : v24 + a1[12];
        sub_43C970(a1, v25, v23 - v24, 0);
        v37 = *a1;
        a1[21] = a1[25];
        sub_43A490(v37);
        if ( !*(_DWORD *)(*a1 + 16) )
          return 0;
      }
    }
  }
  if ( a1[24] )
  {
    v41 = *(_BYTE *)(a1[25] + a1[12] - 1);
    *(_WORD *)(a1[1447] + 2 * a1[1446]) = 0;
    *(_BYTE *)(a1[1444] + a1[1446]++) = v41;
    ++LOWORD(a1[v41 + 35]);
    a1[24] = 0;
  }
  v33 = a1[21];
  if ( v33 < 0 )
    v34 = 0;
  else
    v34 = v33 + a1[12];
  sub_43C970(a1, v34, a1[25] - v33, a2 == 4);
  v39 = *a1;
  a1[21] = a1[25];
  sub_43A490(v39);
  if ( !*(_DWORD *)(*a1 + 16) )
    return a2 != 4 ? 0 : 2;
  v36 = -(a2 != 4);
  LOBYTE(v36) = v36 & 0xFE;
  return v36 + 3;
}
