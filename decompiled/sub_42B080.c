#include "pch.h"
int __cdecl sub_42B080(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-40h] BYREF
  int v4; // [esp+7h] [ebp-3Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 668;
  sub_438F70(a2, (int)Buffer, 7);
  sub_438F70(a2, (int)&dword_4FD870, 4);
  sub_438F70(a2, (int)&dword_4FD874, 4);
  sub_438F70(a2, (int)&dword_4FD878, 4);
  dword_50C218 = dword_4FD864;
  dword_50C21C = dword_4FD868;
  dword_50C220 = dword_4FD86C;
  return sub_438F70(a2, (int)&int_reg, 656);
}
