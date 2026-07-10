#include "pch.h"
int __cdecl sub_43D290(int a1, int a2, int a3, int a4)
{
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  int v7; // edi
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edi
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // edi
  int v21; // edx
  int v22; // edx
  int i; // edi
  int v24; // ecx
  unsigned __int16 v25; // ax
  int v26; // edx
  int v27; // ecx
  int v28; // ebx
  int v29; // edx
  int v30; // edx

  v4 = *(_DWORD *)(a1 + 5812);
  if ( v4 <= 11 )
  {
    *(_WORD *)(a1 + 5808) |= (a2 - 257) << v4;
    *(_DWORD *)(a1 + 5812) = v4 + 5;
  }
  else
  {
    v5 = (a2 - 257) << v4;
    v6 = *(_DWORD *)(a1 + 20);
    *(_WORD *)(a1 + 5808) |= v5;
    *(_BYTE *)(v6 + *(_DWORD *)(a1 + 8)) = *(_BYTE *)(a1 + 5808);
    v7 = *(_DWORD *)(a1 + 8);
    LOBYTE(v5) = *(_BYTE *)(a1 + 5809);
    v8 = *(_DWORD *)(a1 + 20) + 1;
    *(_DWORD *)(a1 + 20) = v8;
    *(_BYTE *)(v8 + v7) = v5;
    v9 = *(_DWORD *)(a1 + 5812);
    ++*(_DWORD *)(a1 + 20);
    *(_DWORD *)(a1 + 5812) = v9 - 11;
    *(_WORD *)(a1 + 5808) = (unsigned __int16)(a2 - 257) >> (16 - v9);
  }
  v10 = *(_DWORD *)(a1 + 5812);
  if ( v10 <= 11 )
  {
    *(_WORD *)(a1 + 5808) |= (a3 - 1) << v10;
    *(_DWORD *)(a1 + 5812) = v10 + 5;
  }
  else
  {
    v11 = (a3 - 1) << v10;
    v12 = *(_DWORD *)(a1 + 20);
    *(_WORD *)(a1 + 5808) |= v11;
    *(_BYTE *)(v12 + *(_DWORD *)(a1 + 8)) = *(_BYTE *)(a1 + 5808);
    v13 = *(_DWORD *)(a1 + 8);
    LOBYTE(v11) = *(_BYTE *)(a1 + 5809);
    v14 = *(_DWORD *)(a1 + 20) + 1;
    *(_DWORD *)(a1 + 20) = v14;
    *(_BYTE *)(v14 + v13) = v11;
    v15 = *(_DWORD *)(a1 + 5812);
    ++*(_DWORD *)(a1 + 20);
    *(_DWORD *)(a1 + 5812) = v15 - 11;
    *(_WORD *)(a1 + 5808) = (unsigned __int16)(a3 - 1) >> (16 - v15);
  }
  v16 = *(_DWORD *)(a1 + 5812);
  v17 = a4 - 4;
  if ( v16 <= 12 )
  {
    *(_WORD *)(a1 + 5808) |= v17 << v16;
    *(_DWORD *)(a1 + 5812) = v16 + 4;
  }
  else
  {
    v18 = v17 << v16;
    v19 = *(_DWORD *)(a1 + 20);
    *(_WORD *)(a1 + 5808) |= v18;
    *(_BYTE *)(v19 + *(_DWORD *)(a1 + 8)) = *(_BYTE *)(a1 + 5808);
    v20 = *(_DWORD *)(a1 + 8);
    v21 = *(_DWORD *)(a1 + 20) + 1;
    *(_DWORD *)(a1 + 20) = v21;
    *(_BYTE *)(v21 + v20) = *(_BYTE *)(a1 + 5809);
    v22 = *(_DWORD *)(a1 + 5812);
    ++*(_DWORD *)(a1 + 20);
    *(_DWORD *)(a1 + 5812) = v22 - 12;
    *(_WORD *)(a1 + 5808) = (unsigned __int16)v17 >> (16 - v22);
  }
  for ( i = 0; i < a4; ++i )
  {
    v24 = *(_DWORD *)(a1 + 5812);
    if ( v24 <= 13 )
    {
      *(_WORD *)(a1 + 5808) |= *(_WORD *)(a1 + 4 * (unsigned __int8)byte_448DAC[i] + 2678) << v24;
      *(_DWORD *)(a1 + 5812) = v24 + 3;
    }
    else
    {
      v25 = *(_WORD *)(a1 + 4 * (unsigned __int8)byte_448DAC[i] + 2678);
      v26 = v25 << v24;
      v27 = *(_DWORD *)(a1 + 20);
      *(_WORD *)(a1 + 5808) |= v26;
      *(_BYTE *)(v27 + *(_DWORD *)(a1 + 8)) = *(_BYTE *)(a1 + 5808);
      v28 = *(_DWORD *)(a1 + 8);
      v29 = *(_DWORD *)(a1 + 20) + 1;
      *(_DWORD *)(a1 + 20) = v29;
      *(_BYTE *)(v29 + v28) = *(_BYTE *)(a1 + 5809);
      v30 = *(_DWORD *)(a1 + 5812);
      ++*(_DWORD *)(a1 + 20);
      *(_DWORD *)(a1 + 5812) = v30 - 13;
      *(_WORD *)(a1 + 5808) = v25 >> (16 - v30);
    }
  }
  sub_43D500(a1, a1 + 140, a2 - 1);
  return sub_43D500(a1, a1 + 2432, a3 - 1);
}
