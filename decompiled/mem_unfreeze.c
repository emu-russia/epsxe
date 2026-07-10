#include "pch.h"
int __cdecl mem_unfreeze(int a1, int a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  sub_438CA0(a2, v3, 7);
  sub_438CA0(a2, (char *)ram, 0x200000);
  sub_438CA0(a2, pio_mem, 0x20000);
  return sub_438CA0(a2, dcache, 4096);
}
