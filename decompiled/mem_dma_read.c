#include "pch.h"
int __cdecl mem_dma_read(unsigned int a1)
{
  return mem_read_hooks[HIWORD(a1)] + (unsigned __int16)a1;
}
