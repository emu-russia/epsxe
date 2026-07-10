#include "pch.h"
bool __cdecl sub_434F70(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, DWORD a5)
{
  char v6; // [esp+0h] [ebp-Ch] BYREF
  __int16 v7; // [esp+1h] [ebp-Bh]
  char v8; // [esp+3h] [ebp-9h]
  char v9; // [esp+4h] [ebp-8h]
  __int16 v10; // [esp+5h] [ebp-7h]
  char v11; // [esp+7h] [ebp-5h]
  unsigned __int8 v12; // [esp+8h] [ebp-4h]
  char v13; // [esp+9h] [ebp-3h]
  __int16 v14; // [esp+Ah] [ebp-2h]

  v11 = 0;
  v10 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v9 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = -8;
  v14 = 2;
  return sub_434AC0(&v6, 0xCu, a5, 2368 * a4);
}
