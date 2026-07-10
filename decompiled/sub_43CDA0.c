#include "pch.h"
int __cdecl sub_43CDA0(int a1, int a2, int a3)
{
  int result; // eax
  int v4; // edx
  int v5; // ebp
  int v6; // ecx
  bool v7; // cc
  int v8; // esi
  int v9; // ebp
  unsigned __int16 v10; // dx
  unsigned __int16 v11; // bx
  int v12; // esi
  unsigned __int16 v13; // dx
  unsigned __int16 v14; // bx
  int v15; // edx
  int v16; // edx
  int v17; // [esp+14h] [ebp+4h]

  result = a1;
  v4 = *(_DWORD *)(a1 + 5192);
  v5 = *(_DWORD *)(a1 + 4 * a3 + 2900);
  v6 = 2 * a3;
  v7 = 2 * a3 < v4;
  v17 = v5;
  if ( 2 * a3 > v4 )
  {
    *(_DWORD *)(result + 4 * a3 + 2900) = v5;
  }
  else
  {
    while ( 1 )
    {
      if ( v7 )
      {
        v8 = *(_DWORD *)(result + 4 * v6 + 2904);
        v9 = *(_DWORD *)(result + 4 * v6 + 2900);
        v10 = *(_WORD *)(a2 + 4 * v8);
        v11 = *(_WORD *)(a2 + 4 * v9);
        if ( v10 < v11 || v10 == v11 && *(_BYTE *)(v8 + result + 5200) <= *(_BYTE *)(result + v9 + 5200) )
          ++v6;
        v5 = v17;
      }
      v12 = *(_DWORD *)(result + 4 * v6 + 2900);
      v13 = *(_WORD *)(a2 + 4 * v5);
      v14 = *(_WORD *)(a2 + 4 * v12);
      if ( v13 < v14 )
      {
LABEL_12:
        *(_DWORD *)(result + 4 * a3 + 2900) = v5;
        return result;
      }
      if ( v13 == v14 && *(_BYTE *)(result + v5 + 5200) <= *(_BYTE *)(v12 + result + 5200) )
        break;
      v15 = a3;
      a3 = v6;
      v6 *= 2;
      *(_DWORD *)(result + 4 * v15 + 2900) = v12;
      v16 = *(_DWORD *)(result + 5192);
      v7 = v6 < v16;
      if ( v6 > v16 )
        goto LABEL_12;
    }
    *(_DWORD *)(result + 4 * a3 + 2900) = v5;
  }
  return result;
}
