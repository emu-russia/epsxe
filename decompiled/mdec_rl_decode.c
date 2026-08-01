#include "pch.h"
char *__cdecl mdec_rl_decode(char *a1, int a2)
{
  int v2; // edx
  char *v3; // edi
  unsigned __int16 v4; // ax
  int v5; // ebx
  unsigned __int16 i; // cx
  _WORD *v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+20h] [ebp+8h]

  v8 = (_WORD *)byte_50C3E0;
  memset(byte_50C3E0, 0, 4 * ((unsigned int)(768 * a2) >> 2));
  v2 = 6 * a2;
  v9 = 0;
  if ( v2 <= 0 )
    return a1;
  v3 = a1;
  do
  {
    if ( v3 - (char *)ram >= 0x1FFF00 )
      break;
    v4 = *(_WORD *)v3;
    v5 = 0;
    v3 += 4;
    *v8 = mdec_scale_table[0] * ((__int16)(v4 << 6) >> 6);
    for ( i = *((_WORD *)v3 - 1); i != 0xFE00; v3 += 2 )
    {
      v5 += (i >> 10) + 1;
      if ( v5 > 63 )
        break;
      v8[mdec_zigzag[v5]] = (v4 >> 10) * (i << 22 >> 22) * mdec_scale_table[mdec_zigzag[v5]] / 8;
      i = *(_WORD *)v3;
    }
    mdec_nonzero_counts[v9] = v5;
    v8 += 64;
    ++v9;
  }
  while ( v9 < v2 );
  return v3;
}
