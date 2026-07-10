#include "pch.h"
int __cdecl sub_43C710(int a1)
{
  int v1; // ecx
  int v2; // edx
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ebx
  int v11; // edi
  int v12; // edi
  int result; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // ecx
  int v23; // ebx
  int v24; // edi
  int v25; // edi

  v1 = *(_DWORD *)(a1 + 5812);
  if ( v1 <= 13 )
  {
    *(_WORD *)(a1 + 5808) |= 2 << v1;
    *(_DWORD *)(a1 + 5812) = v1 + 3;
  }
  else
  {
    v2 = *(_DWORD *)(a1 + 20);
    v3 = 2 << v1;
    v4 = *(_DWORD *)(a1 + 8);
    *(_WORD *)(a1 + 5808) |= v3;
    *(_BYTE *)(v4 + v2) = *(_BYTE *)(a1 + 5808);
    v5 = *(_DWORD *)(a1 + 8);
    v6 = *(_DWORD *)(a1 + 20) + 1;
    *(_DWORD *)(a1 + 20) = v6;
    *(_BYTE *)(v5 + v6) = *(_BYTE *)(a1 + 5809);
    ++*(_DWORD *)(a1 + 20);
    v7 = *(_DWORD *)(a1 + 5812);
    *(_DWORD *)(a1 + 5812) = v7 - 13;
    *(_WORD *)(a1 + 5808) = 2u >> (16 - v7);
  }
  v8 = *(_DWORD *)(a1 + 5812);
  if ( v8 <= 9 )
  {
    *(_WORD *)(a1 + 5808) |= 458752 << v8;
    *(_DWORD *)(a1 + 5812) = v8 + 7;
  }
  else
  {
    v9 = *(_DWORD *)(a1 + 8);
    *(_WORD *)(a1 + 5808) = *(_WORD *)(a1 + 5808);
    *(_BYTE *)(v9 + *(_DWORD *)(a1 + 20)) = *(_BYTE *)(a1 + 5808);
    v10 = *(_DWORD *)(a1 + 8);
    LOBYTE(v9) = *(_BYTE *)(a1 + 5809);
    v11 = *(_DWORD *)(a1 + 20) + 1;
    *(_DWORD *)(a1 + 20) = v11;
    *(_BYTE *)(v10 + v11) = v9;
    v12 = *(_DWORD *)(a1 + 5812);
    ++*(_DWORD *)(a1 + 20);
    *(_DWORD *)(a1 + 5812) = v12 - 9;
    *(_WORD *)(a1 + 5808) = 0;
  }
  result = sub_43E010(a1);
  v14 = *(_DWORD *)(a1 + 5812);
  if ( *(_DWORD *)(a1 + 5804) - v14 + 11 < 9 )
  {
    if ( v14 <= 13 )
    {
      *(_WORD *)(a1 + 5808) |= 2 << v14;
      *(_DWORD *)(a1 + 5812) = v14 + 3;
    }
    else
    {
      v15 = *(_DWORD *)(a1 + 20);
      v16 = 2 << v14;
      v17 = *(_DWORD *)(a1 + 8);
      *(_WORD *)(a1 + 5808) |= v16;
      *(_BYTE *)(v17 + v15) = *(_BYTE *)(a1 + 5808);
      v18 = *(_DWORD *)(a1 + 8);
      v19 = *(_DWORD *)(a1 + 20) + 1;
      *(_DWORD *)(a1 + 20) = v19;
      *(_BYTE *)(v18 + v19) = *(_BYTE *)(a1 + 5809);
      ++*(_DWORD *)(a1 + 20);
      v20 = *(_DWORD *)(a1 + 5812);
      *(_DWORD *)(a1 + 5812) = v20 - 13;
      *(_WORD *)(a1 + 5808) = 2u >> (16 - v20);
    }
    v21 = *(_DWORD *)(a1 + 5812);
    if ( v21 <= 9 )
    {
      *(_WORD *)(a1 + 5808) |= 458752 << v21;
      *(_DWORD *)(a1 + 5812) = v21 + 7;
    }
    else
    {
      v22 = *(_DWORD *)(a1 + 8);
      *(_WORD *)(a1 + 5808) = *(_WORD *)(a1 + 5808);
      *(_BYTE *)(v22 + *(_DWORD *)(a1 + 20)) = *(_BYTE *)(a1 + 5808);
      v23 = *(_DWORD *)(a1 + 8);
      LOBYTE(v22) = *(_BYTE *)(a1 + 5809);
      v24 = *(_DWORD *)(a1 + 20) + 1;
      *(_DWORD *)(a1 + 20) = v24;
      *(_BYTE *)(v23 + v24) = v22;
      v25 = *(_DWORD *)(a1 + 5812);
      ++*(_DWORD *)(a1 + 20);
      *(_DWORD *)(a1 + 5812) = v25 - 9;
      *(_WORD *)(a1 + 5808) = 0;
    }
    result = sub_43E010(a1);
  }
  *(_DWORD *)(a1 + 5804) = 7;
  return result;
}
