#include "pch.h"
void __cdecl mdec_idct_blocks(int a1)
{
  int *v1; // edi
  int v2; // esi
  __m64 *i; // ebx
  int v4; // edx
  int v5; // eax
  char *v6; // [esp+10h] [ebp-8h]
  int *v7; // [esp+14h] [ebp-4h]

  v1 = mdec_idct_buffer;
  v2 = 0;
  v6 = mdec_idct_buffer_end;
  v7 = mdec_idct_buffer;
  for ( i = (__m64 *)byte_50C3E0; v2 < 6 * a1; v6 += 32 )
  {
    if ( mdec_nonzero_counts[v2] )
    {
      mdec_idct_sse(i, (int)v6);
    }
    else
    {
      v4 = (int)i->m64_u16[0] >> 5;
      BYTE1(v4) = v4;
      v5 = v4 << 16;
      LOWORD(v5) = v4;
      memset32(v1, v5, 0x10u);
    }
    v1 = v7 + 16;
    i += 16;
    ++v2;
    v7 += 16;
  }
  mdec_sse_m_empty();
}
