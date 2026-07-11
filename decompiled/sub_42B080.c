#include "pch.h"
int __cdecl sub_42B080(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-40h] BYREF
  int v4; // [esp+7h] [ebp-3Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 668;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)dword_4FD870, 4u);
  gzwrite(a2, (unsigned __int8 *)dword_4FD874, 4u);
  gzwrite(a2, (unsigned __int8 *)dword_4FD878, 4u);
  dword_50C218 = dword_4FD864;
  dword_50C21C = dword_4FD868;
  dword_50C220 = dword_4FD86C;
  return gzwrite(a2, (unsigned __int8 *)int_reg, 0x290u);
}
