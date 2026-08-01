#include "pch.h"
unsigned int cdr_dma()
{
  int v0; // ecx
  unsigned int result; // eax
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
    v4 = g_cdr_data_bytes_transferred;
    result = v3 + g_cdr_data_bytes_transferred;
    g_cdr_data_bytes_transferred += v3;
    if ( dword_50C36C == 1 )
      result = dynarec_invalidate_range(dword_516504, v3 >> 2);
    if ( v3 + (v2 & 0x1FFFFF) <= 0x200000 )
    {
      result = mem_dma_read(v2);
      qmemcpy((void *)result, &g_cdr_data_buffer[v4], v3);
    }
    g_cdr_dma_active = 1;
  }
  return result;
}
