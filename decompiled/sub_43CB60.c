#include "pch.h"
int __cdecl sub_43CB60(_DWORD *a1, _DWORD *a2)
{
  _WORD *v3; // edi
  int *v4; // eax
  int v5; // ebp
  int v6; // ebx
  int v7; // ecx
  int v8; // eax
  _WORD *v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int i; // ebx
  int v15; // eax
  int v16; // ebx
  int v17; // ebp
  int v18; // edx
  int v19; // ecx
  char v20; // al
  int v21; // ecx
  int v22; // edx
  int v24; // [esp+10h] [ebp-8h]
  int v25; // [esp+14h] [ebp-4h]
  _WORD *v26; // [esp+1Ch] [ebp+4h]

  v3 = (_WORD *)*a2;
  v4 = (int *)a2[2];
  v5 = -1;
  v6 = *v4;
  v7 = v4[3];
  v8 = 0;
  v25 = v7;
  v24 = -1;
  a1[1298] = 0;
  a1[1299] = 573;
  if ( v7 > 0 )
  {
    v9 = v3;
    do
    {
      if ( *v9 )
      {
        v24 = v8;
        v10 = a1[1298] + 1;
        v5 = v8;
        a1[1298] = v10;
        a1[v10 + 725] = v8;
        *((_BYTE *)a1 + v8 + 5200) = 0;
      }
      else
      {
        v9[1] = 0;
      }
      ++v8;
      v9 += 2;
    }
    while ( v8 < v25 );
  }
  v11 = a1[1298];
  if ( v11 < 2 )
  {
    do
    {
      if ( v5 >= 2 )
        v12 = 0;
      else
        v12 = ++v5;
      v13 = v11 + 1;
      a1[1298] = v13;
      a1[v13 + 725] = v12;
      v3[2 * v12] = 1;
      *((_BYTE *)a1 + v12 + 5200) = 0;
      --a1[1448];
      if ( v6 )
        a1[1449] -= *(unsigned __int16 *)(v6 + 4 * v12 + 2);
      v11 = a1[1298];
    }
    while ( v11 < 2 );
    v24 = v5;
  }
  a2[1] = v5;
  for ( i = a1[1298] / 2; i >= 1; --i )
    sub_43CDA0(a1, v3, i);
  v26 = &v3[2 * v25];
  do
  {
    v15 = a1[1298];
    v16 = a1[726];
    a1[726] = a1[v15 + 725];
    a1[1298] = v15 - 1;
    sub_43CDA0(a1, v3, 1);
    v17 = a1[726];
    v18 = a1[1299] - 1;
    a1[1299] = v18;
    a1[v18 + 725] = v16;
    v19 = a1[1299] - 1;
    a1[1299] = v19;
    a1[v19 + 725] = v17;
    *v26 = v3[2 * v16] + v3[2 * v17];
    if ( *((_BYTE *)a1 + v16 + 5200) < *((_BYTE *)a1 + v17 + 5200) )
      v20 = *((_BYTE *)a1 + v17 + 5200);
    else
      v20 = *((_BYTE *)a1 + v16 + 5200);
    *((_BYTE *)a1 + v25 + 5200) = v20 + 1;
    v3[2 * v17 + 1] = v25;
    v3[2 * v16 + 1] = v25;
    a1[726] = v25++;
    v26 += 2;
    sub_43CDA0(a1, v3, 1);
  }
  while ( (int)a1[1298] >= 2 );
  v21 = a1[726];
  v22 = a1[1299] - 1;
  a1[1299] = v22;
  a1[v22 + 725] = v21;
  sub_43CE80(a1, a2);
  return sub_43D0B0(v3, v24, a1 + 717);
}
