#include "pch.h"
int __cdecl sub_429B90(int a1)
{
  int *v1; // edi
  int v2; // esi
  unsigned __int16 *i; // ebx
  int v4; // edx
  int v5; // eax
  char *v7; // [esp+10h] [ebp-8h]
  int *v8; // [esp+14h] [ebp-4h]

  v1 = dword_512140;
  v2 = 0;
  v7 = byte_514E40;
  v8 = dword_512140;
  for ( i = (unsigned __int16 *)&unk_50C3E0; v2 < 6 * a1; v7 += 32 )
  {
    if ( dword_511DE0[v2] )
    {
      mdec_idct_sse(i, v7);
    }
    else
    {
      v4 = (int)*i >> 5;
      BYTE1(v4) = v4;
      v5 = v4 << 16;
      LOWORD(v5) = v4;
      memset32(v1, v5, 0x10u);
    }
    v1 = v8 + 16;
    i += 64;
    ++v2;
    v8 += 16;
  }
  return sse_m_empty();
}
