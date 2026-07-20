#include "pch.h"
_WORD *__cdecl mdec_yuv_to_rgb(char *a1, _WORD *a2, _WORD *a3)
{
  _WORD *result; // eax
  char *v4; // esi
  char *v5; // edi
  char *v6; // ebp
  int v7; // ecx
  int v8; // ecx
  int v9; // ebx
  int v10; // ecx
  int v11; // ecx
  int v12; // ebx
  int v13; // ecx
  int v14; // edx
  bool v15; // zf
  bool v16; // cc
  int v17; // [esp+Ch] [ebp-Ch]
  int v18; // [esp+10h] [ebp-8h]
  _WORD *v19; // [esp+14h] [ebp-4h]
  int v20; // [esp+20h] [ebp+8h]
  int v21; // [esp+20h] [ebp+8h]
  int v22; // [esp+24h] [ebp+Ch]
  int v23; // [esp+24h] [ebp+Ch]

  result = a3;
  v4 = a1;
  v5 = a1 + 128;
  v6 = a1 + 192;
  if ( (int)a3 > 0 )
  {
    v19 = a3;
    result = a2;
    do
    {
      v7 = 0;
      v18 = 0;
      do
      {
        if ( v7 == 4 )
        {
          v5 += 64;
          v6 += 64;
        }
        v17 = 4;
        do
        {
          v8 = v4[64];
          v9 = *v4;
          v20 = ((-1408 * v9) >> 12) + ((-2925 * v8) >> 12);
          v22 = (7258 * v9) >> 12;
          v10 = (5743 * v8) >> 12;
          *result = mdec_bit15_flag
                  | ((unsigned __int8)mdec_color_lookup[*v5 + v22] >> 3)
                  | (4 * (mdec_color_lookup[*v5 + v20] & 0xF8 | (32 * (mdec_color_lookup[*v5 + v10] & 0xF8))));
          result[1] = mdec_bit15_flag
                    | ((unsigned __int8)mdec_color_lookup[v5[1] + v22] >> 3)
                    | (4 * (mdec_color_lookup[v5[1] + v20] & 0xF8 | (32 * (mdec_color_lookup[v5[1] + v10] & 0xF8))));
          result[16] = mdec_bit15_flag
                     | ((unsigned __int8)mdec_color_lookup[v5[8] + v22] >> 3)
                     | (4 * (mdec_color_lookup[v5[8] + v20] & 0xF8 | (32 * (mdec_color_lookup[v5[8] + v10] & 0xF8))));
          result[17] = mdec_bit15_flag
                     | ((unsigned __int8)mdec_color_lookup[v5[9] + v22] >> 3)
                     | (4 * (mdec_color_lookup[v5[9] + v20] & 0xF8 | (32 * (mdec_color_lookup[v5[9] + v10] & 0xF8))));
          v11 = a1[68];
          v12 = a1[4];
          v21 = ((-1408 * v12) >> 12) + ((-2925 * v11) >> 12);
          v23 = (7258 * v12) >> 12;
          v13 = (5743 * v11) >> 12;
          result[8] = mdec_bit15_flag
                    | ((unsigned __int8)mdec_color_lookup[*v6 + v23] >> 3)
                    | (4 * (mdec_color_lookup[*v6 + v21] & 0xF8 | (32 * (mdec_color_lookup[*v6 + v13] & 0xF8))));
          result[9] = mdec_bit15_flag
                    | ((unsigned __int8)mdec_color_lookup[v6[1] + v23] >> 3)
                    | (4 * (mdec_color_lookup[v6[1] + v21] & 0xF8 | (32 * (mdec_color_lookup[v6[1] + v13] & 0xF8))));
          result[24] = mdec_bit15_flag
                     | ((unsigned __int8)mdec_color_lookup[v6[8] + v23] >> 3)
                     | (4 * (mdec_color_lookup[v6[8] + v21] & 0xF8 | (32 * (mdec_color_lookup[v6[8] + v13] & 0xF8))));
          v14 = v6[9];
          v5 += 2;
          v6 += 2;
          result += 2;
          result[23] = mdec_bit15_flag
                     | ((unsigned __int8)mdec_color_lookup[v14 + v23] >> 3)
                     | (4 * (mdec_color_lookup[v14 + v21] & 0xF8 | (32 * (mdec_color_lookup[v14 + v13] & 0xF8))));
          v4 = a1 + 1;
          v15 = v17 == 1;
          ++a1;
          --v17;
        }
        while ( !v15 );
        v7 = v18 + 1;
        v4 += 4;
        v5 += 8;
        v6 += 8;
        result += 24;
        v16 = ++v18 < 8;
        a1 = v4;
      }
      while ( v16 );
      v4 += 320;
      v5 += 192;
      v6 += 192;
      v15 = v19 == (_WORD *)1;
      a1 = v4;
      v19 = (_WORD *)((char *)v19 - 1);
    }
    while ( !v15 );
  }
  return result;
}
