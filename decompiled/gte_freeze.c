#include "pch.h"
int __cdecl gte_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 256;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  return gzwrite(a2, (unsigned __int8 *)word_8A7F00, 0x100u);
}
