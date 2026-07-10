#include "pch.h"
bool __cdecl sub_434DF0(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5,
        _DWORD *a6)
{
  bool result; // al
  int v7; // esi
  _DWORD *v9; // ecx
  _DWORD *v10; // ebx
  int v11; // edi
  char v12; // [esp+4h] [ebp-Ch] BYREF
  __int16 v13; // [esp+5h] [ebp-Bh]
  char v14; // [esp+7h] [ebp-9h]
  char v15; // [esp+8h] [ebp-8h]
  __int16 v16; // [esp+9h] [ebp-7h]
  char v17; // [esp+Bh] [ebp-5h]
  int v18; // [esp+Ch] [ebp-4h]

  if ( !byte_4FD9C8 )
  {
    if ( sub_434B80() != 1 )
      return 1;
    byte_4FD9C8 = 1;
  }
  v17 = 0;
  v16 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  v18 = 0x10000;
  v13 = 0;
  v7 = a4;
  v14 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v12 = -40;
  v15 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  BYTE1(v18) = a4;
  result = sub_434AC0(&v12, 0xCu, a5, 2368 * a4);
  if ( a4 )
  {
    v9 = (_DWORD *)(a5 + 2352);
    do
    {
      v10 = a6;
      *a6 = *v9;
      a6[1] = v9[1];
      a6[2] = v9[2];
      v11 = v9[3];
      v9 += 592;
      a6 += 4;
      --v7;
      v10[3] = v11;
    }
    while ( v7 );
  }
  return result;
}
