#include "pch.h"
int __cdecl zip_inflate_buffer_sub2(
        _DWORD *a1,
        unsigned int a2,
        unsigned int a3,
        int a4,
        int a5,
        _DWORD *a6,
        unsigned int *a7)
{
  _DWORD *v7; // ecx
  unsigned int v8; // edx
  _DWORD *v9; // eax
  int result; // eax
  unsigned int i; // ecx
  unsigned int v12; // ebp
  signed int v13; // edx
  unsigned int v14; // eax
  int j; // esi
  int v16; // esi
  unsigned int v17; // ebx
  int v18; // ecx
  int v19; // esi
  int v20; // ecx
  unsigned int v21; // eax
  int v22; // esi
  int *v23; // edi
  unsigned int v24; // esi
  int v25; // eax
  int v26; // ecx
  unsigned int *v27; // ecx
  int v28; // esi
  unsigned int v29; // ebx
  unsigned int v30; // edi
  signed int v31; // eax
  unsigned int v32; // ebp
  unsigned int v33; // edx
  unsigned int v34; // ebx
  unsigned int v35; // eax
  _DWORD *v36; // edi
  unsigned int v37; // eax
  unsigned int v38; // ecx
  unsigned int v39; // eax
  _DWORD *v40; // eax
  char *v41; // ecx
  unsigned int v42; // eax
  unsigned int v43; // ebx
  int v44; // ecx
  unsigned int v45; // eax
  int v46; // edx
  unsigned int v47; // eax
  char *v48; // ecx
  unsigned int k; // eax
  int v50; // eax
  signed int v51; // [esp+10h] [ebp-5C4h]
  int v52; // [esp+14h] [ebp-5C0h]
  unsigned int *v53; // [esp+18h] [ebp-5BCh]
  int v54; // [esp+1Ch] [ebp-5B8h]
  char *v55; // [esp+20h] [ebp-5B4h]
  _DWORD *v56; // [esp+24h] [ebp-5B0h]
  unsigned int m; // [esp+28h] [ebp-5ACh]
  signed int v58; // [esp+2Ch] [ebp-5A8h]
  char v59; // [esp+34h] [ebp-5A0h]
  unsigned int v60; // [esp+38h] [ebp-59Ch]
  char *v61; // [esp+3Ch] [ebp-598h]
  int v62; // [esp+44h] [ebp-590h]
  _DWORD v63[17]; // [esp+48h] [ebp-58Ch] BYREF
  int v64; // [esp+8Ch] [ebp-548h]
  _DWORD v65[16]; // [esp+90h] [ebp-544h]
  _DWORD v66[17]; // [esp+D0h] [ebp-504h]
  int v67[16]; // [esp+114h] [ebp-4C0h]
  _DWORD v68[288]; // [esp+154h] [ebp-480h] BYREF
  int v69; // [esp+5DCh] [ebp+8h]

  if ( a2 <= 0x100 )
    v60 = 16;
  else
    v60 = a1[256];
  memset(v63, 0, sizeof(v63));
  v7 = a1;
  v8 = a2;
  do
  {
    v9 = &v63[*v7++];
    --v8;
    ++*v9;
  }
  while ( v8 );
  if ( v63[0] == a2 )
  {
    *a6 = 0;
    *a7 = 0;
    return 0;
  }
  for ( i = 1; i <= 0x10; ++i )
  {
    v12 = 0;
    if ( v63[i] )
      break;
  }
  v13 = i;
  v51 = i;
  if ( *a7 < i )
    *a7 = i;
  v14 = 16;
  do
  {
    if ( v63[v14] )
      break;
    --v14;
  }
  while ( v14 );
  v58 = v14;
  if ( *a7 > v14 )
    *a7 = v14;
  for ( j = 1 << i; i < v14; j = 2 * v16 )
  {
    v16 = j - v63[i];
    if ( v16 < 0 )
      return 2;
    ++i;
  }
  v17 = v14;
  v18 = v63[v14];
  v19 = j - v18;
  v62 = v19;
  if ( v19 < 0 )
    return 2;
  v63[v14] = v19 + v18;
  v20 = 0;
  v21 = v14 - 1;
  v66[1] = 0;
  if ( v21 )
  {
    v22 = 0;
    do
    {
      v20 += v63[v22 + 1];
      v66[v22 + 2] = v20;
      ++v22;
      --v21;
    }
    while ( v21 );
  }
  memset(v68, 0, sizeof(v68));
  v23 = a1;
  v24 = 0;
  do
  {
    v25 = *v23++;
    if ( v25 )
    {
      v26 = v66[v25];
      v68[v26] = v24;
      v66[v25] = v26 + 1;
    }
    ++v24;
  }
  while ( v24 < a2 );
  v69 = v66[v17];
  v27 = v68;
  v28 = -1;
  v29 = 0;
  v30 = 0;
  m = 0;
  v66[0] = 0;
  v53 = v68;
  v64 = 0;
  v67[0] = 0;
  v61 = nullptr;
  if ( v13 > v58 )
  {
LABEL_65:
    *a7 = v65[0];
    if ( !v62 )
      return 0;
    result = 1;
    if ( v58 == 1 )
      return 0;
  }
  else
  {
    v59 = v13 - 1;
    v56 = &v63[v13];
    while ( 1 )
    {
      v52 = *v56;
      if ( *v56 )
        break;
LABEL_64:
      ++v56;
      ++v13;
      ++v59;
      v51 = v13;
      if ( v13 > v58 )
        goto LABEL_65;
    }
    while ( 1 )
    {
      --v52;
      v31 = v29 + v65[v28];
      if ( v13 > v31 )
        break;
LABEL_49:
      if ( v27 < &v68[v69] )
      {
        v45 = *v27;
        if ( *v27 >= a3 )
        {
          v45 = 2 * (v45 - a3);
          LOBYTE(v54) = *(_BYTE *)(v45 + a5);
          LOWORD(v45) = *(_WORD *)(v45 + a4);
        }
        else
        {
          LOBYTE(v54) = (v45 < 0x100) + 15;
        }
        LOWORD(v55) = v45;
        v53 = v27 + 1;
      }
      else
      {
        LOBYTE(v54) = 99;
      }
      v46 = 1 << (v51 - v29);
      v47 = v12 >> v29;
      if ( v12 >> v29 < v30 )
      {
        v48 = &v61[8 * v47];
        do
        {
          BYTE1(v54) = v51 - v29;
          *(_DWORD *)v48 = v54;
          *((_DWORD *)v48 + 1) = v55;
          v47 += v46;
          v48 += 8 * v46;
        }
        while ( v47 < v30 );
        v12 = m;
      }
      for ( k = 1 << v59; (k & v12) != 0; k >>= 1 )
        v12 ^= k;
      v12 ^= k;
      for ( m = v12; (v12 & ((1 << v29) - 1)) != v66[v28]; v29 -= v50 )
        v50 = v65[--v28];
      v27 = v53;
      v13 = v51;
      if ( !v52 )
        goto LABEL_64;
    }
    while ( 1 )
    {
      v32 = v31;
      v33 = v58 - v31;
      ++v28;
      if ( v58 - v31 > *a7 )
        v33 = *a7;
      v34 = v51 - v31;
      v35 = 1 << (v51 - v31);
      if ( v35 > v52 + 1 )
      {
        v36 = v56;
        v37 = -1 - v52 + v35;
        if ( ++v34 < v33 )
        {
          do
          {
            v38 = v36[1];
            ++v36;
            v39 = 2 * v37;
            if ( v39 <= v38 )
              break;
            v37 = v39 - v38;
            ++v34;
          }
          while ( v34 < v33 );
        }
      }
      if ( v34 + v32 > v60 && v32 < v60 )
        v34 = v60 - v32;
      v30 = 1 << v34;
      v65[v28] = v34;
      v40 = malloc(8 * (1 << v34) + 8);
      if ( !v40 )
        break;
      dword_4F8340 += v30 + 1;
      v41 = (char *)(v40 + 2);
      *a6 = v40 + 2;
      a6 = v40 + 1;
      v40[1] = 0;
      v61 = (char *)(v40 + 2);
      v67[v28] = (int)(v40 + 2);
      if ( v28 )
      {
        LOBYTE(v54) = v34 + 16;
        BYTE1(v54) = v65[v28 - 1];
        v42 = v32;
        v66[v28] = m;
        v55 = v41;
        v43 = (m & ((1 << v32) - 1)) >> (v32 - LOBYTE(v65[v28 - 1]));
        v44 = v66[v28 + 16];
        *(_DWORD *)(v44 + 8 * v43) = v54;
        *(_DWORD *)(v44 + 8 * v43 + 4) = v55;
      }
      else
      {
        v42 = v32;
      }
      v31 = v65[v28] + v42;
      if ( v51 <= v31 )
      {
        v29 = v32;
        v12 = m;
        v27 = v53;
        goto LABEL_49;
      }
    }
    if ( v28 )
      zip_free(v67[0]);
    return 3;
  }
  return result;
}
