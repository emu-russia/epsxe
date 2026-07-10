#include "pch.h"
int __cdecl dma_mem_read(unsigned int a1)
{
  return ram[HIWORD(a1)] + (unsigned __int16)a1;
}
