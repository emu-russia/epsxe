#include "pch.h"
int __cdecl spucore_set_dma_address(unsigned __int16 a1)
{
  int result; // eax

  result = 8 * a1;
  dword_4F7554 = result;
  return result;
}
