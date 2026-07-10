#include "pch.h"
int __cdecl sub_42B120(int a1, int a2)
{
  char v3[64]; // [esp+4h] [ebp-40h] BYREF

  sub_438CA0(a2, v3, 7);
  sub_438CA0(a2, (char *)&dword_4FD870, 4);
  sub_438CA0(a2, (char *)&dword_4FD874, 4);
  sub_438CA0(a2, (char *)&dword_4FD878, 4);
  sub_438CA0(a2, (char *)&int_reg, 656);
  dword_4FD864 = dword_50C218;
  dword_4FD868 = dword_50C21C;
  dword_4FD86C = dword_50C220;
  return dword_50C220;
}
