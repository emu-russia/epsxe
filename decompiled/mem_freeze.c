#include "pch.h"
int __cdecl mem_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 2232320;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)ram, 0x200000u);
  gzwrite(a2, (unsigned __int8 *)pio_mem, 0x20000u);
  return gzwrite(a2, (unsigned __int8 *)dcache, 0x1000u);
}
