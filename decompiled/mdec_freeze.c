#include "pch.h"
int __cdecl mdec_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+8h] [ebp-440h] BYREF
  int v4; // [esp+Bh] [ebp-43Dh]
  unsigned __int8 v5[1024]; // [esp+48h] [ebp-400h] BYREF

  memset(v5, 0, sizeof(v5));
  sprintf(Buffer, "%s", a1);
  v4 = 1248;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)mdec_command, 0x60u);
  gzwrite(a2, (unsigned __int8 *)mdec_scale_table, 0x80u);
  return gzwrite(a2, v5, 0x400u);
}
