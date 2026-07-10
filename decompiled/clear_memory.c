#include "pch.h"
int clear_memory()
{
  memset(ram, 0, 0x200000u);
  memset(byte_876EA0, 0xFFu, 0x20000u);
  memset(dcache, 0, sizeof(dcache));
  return 0;
}
