#include "pch.h"
int __cdecl sub_42A0D0(const char *a1, int a2)
{
  char Buffer[3]; // [esp+8h] [ebp-440h] BYREF
  int v4; // [esp+Bh] [ebp-43Dh]
  _BYTE v5[1024]; // [esp+48h] [ebp-400h] BYREF

  memset(v5, 0, sizeof(v5));
  sprintf(Buffer, "%s", a1);
  v4 = 1248;
  sub_438F70(a2, Buffer, 7);
  sub_438F70(a2, &dword_4FC4F0, 96);
  sub_438F70(a2, &dword_5120C0, 128);
  return sub_438F70(a2, v5, 1024);
}
