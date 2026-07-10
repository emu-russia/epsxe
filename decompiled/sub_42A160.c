#include "pch.h"
int __cdecl sub_42A160(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-40h] BYREF
  int v4; // [esp+7h] [ebp-3Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 96;
  sub_438F70(a2, Buffer, 7);
  return sub_438F70(a2, &dword_4FC4F0, 96);
}
