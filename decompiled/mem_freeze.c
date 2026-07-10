#include "pch.h"
int __cdecl mem_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 2232320;
  sub_438F70(a2, (int)Buffer, 7);
  sub_438F70(a2, (int)ram, 0x200000);
  sub_438F70(a2, (int)byte_876EA0, 0x20000);
  return sub_438F70(a2, (int)dcache, 4096);
}
