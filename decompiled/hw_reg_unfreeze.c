#include "pch.h"
int __cdecl hw_reg_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dword_5164D0, 4);
  gzread(a2, dword_566964, 4);
  gzread(a2, (char *)mdec_dma_src, 96);
  return gzread(a2, byte_516600, 0x10000);
}
