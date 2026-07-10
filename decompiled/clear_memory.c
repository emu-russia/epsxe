#include "pch.h"
int clear_memory()
{
  memset(ram, 0, 0x200000u);
  memset(pio_mem, 0xFFu, 0x20000u);
  memset(dcache, 0, sizeof(dcache));
  return 0;
}
