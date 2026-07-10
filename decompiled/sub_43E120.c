#include "pch.h"
_BYTE *__cdecl sub_43E120(_DWORD *a1, _BYTE *a2, int a3, int a4)
{
  int v4; // edi
  int v5; // edx
  int v6; // edi
  int v7; // ecx
  int v8; // edi
  int v9; // ecx
  _BYTE *result; // eax
  int v11; // ecx

  sub_43E0A0((int)a1);
  a1[1451] = 8;
  if ( a4 )
  {
    *(_BYTE *)(a1[5] + a1[2]) = a3;
    v4 = a1[2];
    v5 = a1[5] + 1;
    a1[5] = v5;
    *(_BYTE *)(v5 + v4) = BYTE1(a3);
    v6 = a1[2];
    v7 = a1[5] + 1;
    a1[5] = v7;
    *(_BYTE *)(v7 + v6) = ~(_BYTE)a3;
    v8 = a1[5] + 1;
    v9 = a1[2];
    a1[5] = v8;
    *(_BYTE *)(v8 + v9) = ~BYTE1(a3);
    ++a1[5];
  }
  result = (_BYTE *)(a3 - 1);
  if ( a3 )
  {
    v11 = a3;
    result = a2;
    do
    {
      *(_BYTE *)(a1[5] + a1[2]) = *result++;
      --v11;
      ++a1[5];
    }
    while ( v11 );
  }
  return result;
}
