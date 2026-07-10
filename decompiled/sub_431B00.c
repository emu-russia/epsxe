#include "pch.h"
char __cdecl sub_431B00(_DWORD *a1)
{
  _DWORD v2[2]; // [esp+0h] [ebp-Ch] BYREF
  char v3; // [esp+8h] [ebp-4h]
  char v4; // [esp+9h] [ebp-3h]

  v2[1] = 0;
  v4 = 0;
  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  v2[0] = 20972098;
  v3 = 16;
  return sub_430D70(v2, 0xAu, (int)a1, 16);
}
