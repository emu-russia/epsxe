#include "pch.h"
void init_memory_handlers()
{
  int i; // eax
  int *v1; // ecx
  char *v2; // ecx

  for ( i = 0; i < 0x10000; ++i )
  {
    mem_read_hooks[i] = (int)dummy_page;
    mem_write_hooks[i] = (int)dummy_page;
    if ( (unsigned int)i < 0x80
      || i >= 0x8000 && i <= 0x807F
      || i >= 0xA000 && i <= 0xA07F
      || i >= 0x3C00 && i <= 0x3C7F )
    {
      v1 = &ram[0x4000 * (i & 0x1F)];
      mem_read_hooks[i] = (int)v1;
      mem_write_hooks[i] = (int)v1;
    }
    if ( i >= 0x1F00 && i <= 0x1F01 )
    {
      v2 = &pio_mem[0x10000 * (unsigned __int8)i];
      mem_read_hooks[i] = (int)v2;
      mem_write_hooks[i] = (int)v2;
    }
    if ( i >= 0x1FC0 && i <= 0x1FC7 || i >= 0x9FC0 && i <= 0x9FC7 || i >= 0xBFC0 && i <= 0xBFC7 )
    {
      mem_read_hooks[i] = (int)&bios_image[0x10000 * (i & 7)];
      mem_write_hooks[i] = (int)dummy_page;
    }
  }
  byte_454CC0 = 1;
  dbg_print_no_flush(" * Memory handlers init. \n");
}
