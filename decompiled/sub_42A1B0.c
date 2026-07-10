#include "pch.h"
int __cdecl sub_42A1B0(int a1, int a2)
{
  char v3[64]; // [esp+4h] [ebp-440h] BYREF
  char v4[1024]; // [esp+44h] [ebp-400h] BYREF

  sub_438CA0(a2, v3, 7);
  sub_438CA0(a2, (char *)&dword_4FC4F0, 96);
  sub_438CA0(a2, (char *)dword_5120C0, 128);
  return sub_438CA0(a2, v4, 1024);
}
