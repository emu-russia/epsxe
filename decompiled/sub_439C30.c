#include "pch.h"
int __cdecl sub_439C30(_DWORD *a1)
{
  _DWORD *v1; // eax
  int v2; // ebp
  int v4; // ebx
  _BYTE *v5; // edi
  _BYTE *v6; // ecx
  unsigned int v7; // eax
  int v8; // edi
  int v9; // edi
  int v10; // ebx
  _DWORD *v11; // eax

  if ( !a1 )
    return -2;
  v1 = (_DWORD *)a1[7];
  if ( !v1 )
    return -2;
  if ( *v1 != 13 )
  {
    *v1 = 13;
    *(_DWORD *)(a1[7] + 4) = 0;
  }
  v2 = a1[1];
  if ( !v2 )
    return -5;
  v4 = a1[7];
  v5 = (_BYTE *)*a1;
  v6 = (_BYTE *)*a1;
  v7 = *(_DWORD *)(v4 + 4);
  do
  {
    if ( v7 >= 4 )
      break;
    if ( *v6 == byte_448770[v7] )
      ++v7;
    else
      v7 = *v6 ? 0 : 4 - v7;
    ++v6;
    --v2;
  }
  while ( v2 );
  *a1 = v6;
  v8 = v6 - v5 + a1[2];
  a1[1] = v2;
  a1[2] = v8;
  *(_DWORD *)(v4 + 4) = v7;
  if ( v7 != 4 )
    return -3;
  v9 = a1[2];
  v10 = a1[5];
  sub_4395A0(a1);
  v11 = (_DWORD *)a1[7];
  a1[2] = v9;
  a1[5] = v10;
  *v11 = 7;
  return 0;
}
