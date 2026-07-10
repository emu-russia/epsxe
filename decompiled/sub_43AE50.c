#include "pch.h"
unsigned int __cdecl sub_43AE50(_DWORD *a1, int a2)
{
  int v3; // esi
  unsigned int v4; // edx
  unsigned int v5; // ebp
  unsigned int v6; // eax
  _BYTE *v7; // ecx
  _BYTE *v8; // ebx
  _BYTE *v10; // edx
  char v11; // al
  _BYTE *v12; // edx
  _BYTE *v13; // ecx
  _BYTE *v14; // edx
  char v15; // al
  _BYTE *v16; // edx
  char v17; // al
  _BYTE *v18; // edx
  char v19; // al
  _BYTE *v20; // edx
  char v21; // al
  _BYTE *v22; // edx
  char v23; // al
  _BYTE *v24; // edx
  char v25; // al
  _BYTE *v26; // edx
  char v27; // al
  _BYTE *v28; // edx
  char v29; // al
  _BYTE *v30; // edx
  int v31; // edx
  unsigned int result; // eax
  char v33; // [esp+13h] [ebp-11h]
  unsigned int v34; // [esp+14h] [ebp-10h]
  int v35; // [esp+18h] [ebp-Ch]
  unsigned int v36; // [esp+1Ch] [ebp-8h]
  unsigned int v37; // [esp+20h] [ebp-4h]
  char v38; // [esp+28h] [ebp+4h]

  v3 = a1[9];
  v4 = a1[25];
  v5 = a1[28];
  v34 = a1[29];
  v6 = a1[34];
  v7 = (_BYTE *)(v4 + a1[12]);
  v35 = v6;
  if ( v4 <= v3 - 262 )
    v36 = 0;
  else
    v36 = v4 - v3 + 262;
  v8 = v7 + 258;
  v38 = v7[v5 - 1];
  v33 = v7[v5];
  if ( v5 >= a1[33] )
    v34 >>= 2;
  v37 = a1[27];
  if ( v6 > v37 )
    v35 = a1[27];
  do
  {
    v10 = (_BYTE *)(a2 + a1[12]);
    if ( v10[v5] == v33 && v10[v5 - 1] == v38 && *v10 == *v7 )
    {
      v11 = v10[1];
      v12 = v10 + 1;
      if ( v11 == v7[1] )
      {
        v13 = v7 + 2;
        v14 = v12 + 1;
        do
        {
          v15 = *++v13;
          v16 = v14 + 1;
          if ( v15 != *v16 )
            break;
          v17 = *++v13;
          v18 = v16 + 1;
          if ( v17 != *v18 )
            break;
          v19 = *++v13;
          v20 = v18 + 1;
          if ( v19 != *v20 )
            break;
          v21 = *++v13;
          v22 = v20 + 1;
          if ( v21 != *v22 )
            break;
          v23 = *++v13;
          v24 = v22 + 1;
          if ( v23 != *v24 )
            break;
          v25 = *++v13;
          v26 = v24 + 1;
          if ( v25 != *v26 )
            break;
          v27 = *++v13;
          v28 = v26 + 1;
          if ( v27 != *v28 )
            break;
          v29 = *++v13;
          v14 = v28 + 1;
          if ( v29 != *v14 )
            break;
        }
        while ( v13 < v8 );
        v30 = v13;
        v7 = v8 - 258;
        v31 = v30 - v8 + 258;
        if ( v31 > (int)v5 )
        {
          a1[26] = a2;
          v5 = v31;
          if ( v31 >= v35 )
            break;
          v38 = v7[v31 - 1];
          v33 = v7[v31];
        }
      }
    }
    a2 = *(unsigned __int16 *)(a1[14] + 2 * (a2 & a1[11]));
    if ( (unsigned __int16)a2 <= v36 )
      break;
    --v34;
  }
  while ( v34 );
  result = v37;
  if ( v5 <= v37 )
    return v5;
  return result;
}
