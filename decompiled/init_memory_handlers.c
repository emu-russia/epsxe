#include "pch.h"
void init_memory_handlers()
{
  int i; // eax
  int *v1; // ecx
  char *v2; // ecx

  for ( i = 0; i < 0x10000; ++i )
  {
    ram[i] = (int)byte_896EC0;
    mem_hooks[i] = (int)byte_896EC0;
    if ( (unsigned int)i < 0x80
      || i >= 0x8000 && i <= 0x807F
      || i >= 0xA000 && i <= 0xA07F
      || i >= 0x3C00 && i <= 0x3C7F )
    {
      v1 = &ram_0[0x4000 * (i & 0x1F)];
      ram[i] = (int)v1;
      mem_hooks[i] = (int)v1;
    }
    if ( i >= 0x1F00 && i <= 0x1F01 )
    {
      v2 = &byte_876EA0[0x10000 * (unsigned __int8)i];
      ram[i] = (int)v2;
      mem_hooks[i] = (int)v2;
    }
    if ( i >= 0x1FC0 && i <= 0x1FC7 || i >= 0x9FC0 && i <= 0x9FC7 || i >= 0xBFC0 && i <= 0xBFC7 )
    {
      ram[i] = (int)&byte_7F6E80[0x10000 * (i & 7)];
      mem_hooks[i] = (int)byte_896EC0;
    }
  }
  byte_454CC0 = 1;
  dbg_print_no_flush(aMemoryHandlers);
}
