#include "pch.h"
_WORD *__cdecl sub_43C970(int a1, int a2, int a3, int a4)
{
  int v4; // eax
  unsigned int v5; // edx
  unsigned int v6; // ecx
  int v7; // edi
  bool v8; // zf
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // ebx
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // ebp
  int v18; // ebp
  int v19; // ebx
  int v20; // ebx
  _WORD *result; // eax

  v4 = 0;
  if ( *(int *)(a1 + 124) <= 0 )
  {
    v6 = a3 + 5;
LABEL_7:
    v5 = v6;
    goto LABEL_8;
  }
  if ( *(_BYTE *)(a1 + 28) == 2 )
    sub_43DF70(a1);
  sub_43CB60(a1, a1 + 2832);
  sub_43CB60(a1, a1 + 2844);
  v4 = sub_43D130(a1);
  v5 = (unsigned int)(*(_DWORD *)(a1 + 5792) + 10) >> 3;
  v6 = (unsigned int)(*(_DWORD *)(a1 + 5796) + 10) >> 3;
  if ( v6 <= v5 )
    goto LABEL_7;
LABEL_8:
  if ( a3 + 4 <= v5 && a2 )
  {
    v7 = a4;
    sub_43C670(a1, a2, a3, a4);
  }
  else
  {
    v8 = v6 == v5;
    v9 = *(_DWORD *)(a1 + 5812);
    if ( v8 )
    {
      v7 = a4;
      v10 = a4 + 2;
      if ( v9 <= 13 )
      {
        *(_WORD *)(a1 + 5808) |= v10 << v9;
        *(_DWORD *)(a1 + 5812) = v9 + 3;
      }
      else
      {
        v11 = v10 << v9;
        v12 = *(_DWORD *)(a1 + 8);
        *(_WORD *)(a1 + 5808) |= v11;
        *(_BYTE *)(v12 + *(_DWORD *)(a1 + 20)) = *(_BYTE *)(a1 + 5808);
        v13 = *(_DWORD *)(a1 + 8);
        v14 = *(_DWORD *)(a1 + 20) + 1;
        *(_DWORD *)(a1 + 20) = v14;
        *(_BYTE *)(v13 + v14) = *(_BYTE *)(a1 + 5809);
        v15 = *(_DWORD *)(a1 + 5812);
        ++*(_DWORD *)(a1 + 20);
        *(_DWORD *)(a1 + 5812) = v15 - 13;
        *(_WORD *)(a1 + 5808) = (unsigned __int16)v10 >> (16 - v15);
      }
      sub_43DB30(a1, &unk_448DC0, &unk_449240);
    }
    else
    {
      v7 = a4;
      v16 = a4 + 4;
      if ( v9 <= 13 )
      {
        *(_WORD *)(a1 + 5808) |= v16 << v9;
        *(_DWORD *)(a1 + 5812) = v9 + 3;
      }
      else
      {
        v17 = *(_DWORD *)(a1 + 8);
        *(_WORD *)(a1 + 5808) |= v16 << v9;
        *(_BYTE *)(*(_DWORD *)(a1 + 20) + v17) = *(_BYTE *)(a1 + 5808);
        v18 = *(_DWORD *)(a1 + 8);
        v19 = *(_DWORD *)(a1 + 20) + 1;
        *(_DWORD *)(a1 + 20) = v19;
        *(_BYTE *)(v19 + v18) = *(_BYTE *)(a1 + 5809);
        v20 = *(_DWORD *)(a1 + 5812);
        ++*(_DWORD *)(a1 + 20);
        *(_DWORD *)(a1 + 5812) = v20 - 13;
        *(_WORD *)(a1 + 5808) = (unsigned __int16)v16 >> (16 - v20);
      }
      sub_43D290(a1, *(_DWORD *)(a1 + 2836) + 1, *(_DWORD *)(a1 + 2848) + 1, v4 + 1);
      sub_43DB30(a1, a1 + 140, a1 + 2432);
    }
  }
  result = sub_43C600(a1);
  if ( v7 )
    return (_WORD *)sub_43E0A0(a1);
  return result;
}
