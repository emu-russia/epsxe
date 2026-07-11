#include "pch.h"
int __cdecl mem_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, (char *)ram, 0x200000);
  gzread(a2, pio_mem, 0x20000);
  return gzread(a2, dcache, 4096);
}
