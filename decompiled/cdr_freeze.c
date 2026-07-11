#include "pch.h"
int __cdecl cdr_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 4396;
  byte_50BF69 = word_4FD87C;
  byte_50BF67 = word_50BF82;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  return gzwrite(a2, (unsigned __int8 *)dword_50AE80, 0x112Cu);
}
