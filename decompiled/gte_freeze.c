#include "pch.h"
int __cdecl sub_41BBB0(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 256;
  sub_438F70(a2, Buffer, 7);
  return sub_438F70(a2, unk_8A7F00, 256);
}
