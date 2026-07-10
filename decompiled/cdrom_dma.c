#include "pch.h"
int sub_42CD30()
{
  int v0; // ecx
  int result; // eax
  unsigned int v2; // edi
  unsigned int v3; // ebp
  int v4; // esi

  v0 = HIWORD(dword_516508);
  result = (unsigned __int16)dword_516508;
  v2 = dword_516504;
  if ( (dword_51650C & 0x11000000) == 0x11000000 )
  {
    if ( !HIWORD(dword_516508) )
      v0 = 1;
    if ( !(_WORD)dword_516508 )
      result = 512;
    v3 = 4 * v0 * result;
    v4 = dword_50BF5C;
    result = v3 + dword_50BF5C;
    dword_50BF5C += v3;
    if ( dword_50C36C == 1 )
      result = sub_4281B0(dword_516504, v3 >> 2);
    if ( v3 + (v2 & 0x1FFFFF) <= 0x200000 )
    {
      result = dma_mem_read(v2);
      qmemcpy((void *)result, &byte_50AF56[v4], v3);
    }
    byte_50BF64 = 1;
  }
  return result;
}
