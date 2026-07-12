#include "pch.h"
bool __cdecl sub_4350E0(_DWORD *a1)
{
  _DWORD v2[2]; // [esp+0h] [ebp-Ch] BYREF
  char v3[4]; // [esp+8h] [ebp-4h]

  v2[1] = 0;
  v3[1] = 0;
  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  v2[0] = 0x1400242;
  v3[0] = 16;
  return sub_434AC0(v2, 0xAu, (DWORD)a1, 0x10u);
}
