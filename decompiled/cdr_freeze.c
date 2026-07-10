#include "pch.h"
int __cdecl sub_42CE70(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 4396;
  byte_50BF69 = word_4FD87C;
  byte_50BF67 = word_50BF82;
  sub_438F70(a2, Buffer, 7);
  return sub_438F70(a2, &dword_50AE80, 4396);
}
