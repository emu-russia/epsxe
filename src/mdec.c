#include "pch.h"

/* static prototypes for internal functions */
static int __cdecl mdec_set_scale_table(int a1);
static char *__cdecl mdec_rl_decode(char *a1, int a2);
static void __cdecl mdec_idct_blocks(int a1);
static int mdec_init_color_tables();
static _WORD *__cdecl mdec_yuv_to_rgb(char *a1, _WORD *a2, _WORD *a3);
static int __cdecl mdec_idct_sse(__m64 *a1, int a2);
static void mdec_sse_m_empty();
static void __cdecl mdec_y_to_mono(unsigned int *a1, __m64 *a2, int a3);

static char *mdec_init_pointers()
{
  char *v0; // ecx
  char *result; // eax

  v0 = mdec_idct_buffer_end;
  result = (char *)mdec_idct_buffer;
  do
  {
    *(_DWORD *)v0 = result;
    result += 8;
    v0 += 4;
  }
  while ( (int)result < (int)mdec_idct_buffer_end );
  return result;
}

int mdec_init()
{
  *(_DWORD *)mdec_command = 0;
  mdec_param_count = 0;
  mdec_timer_count = 0;
  mdec_out_addr = 0;
  mdec_in_ptr = 0;
  mdec_status = 0;
  mdec_timer = -1;
  mdec_param_word = 0;
  mdec_bit15_flag = 0;
  mdec_init_pointers();
  return mdec_init_color_tables();
}

__int16 __cdecl mdec_write_command(unsigned int a1)
{
  __int16 result; // ax

  *(_DWORD *)mdec_command = a1;
  if ( (a1 & 0xF5FF0000) == 0x30000000 )
    mdec_param_word = (unsigned __int16)a1;
  result = (a1 >> 10) & 0x8000;
  mdec_bit15_flag = result;
  return result;
}

int __cdecl mdec_handle_special_command(int a1)
{
  int result; // eax

  if ( a1 == 0x80000000 )
  {
    mdec_in_ptr = mdec_out_addr;
    return mdec_out_addr;
  }
  return result;
}

char mdec_timer_handler()
{
  char result; // al

  result = mdectiming;
  if ( mdectiming )
  {
    result = mdec_timer;
    if ( mdec_timer <= 0 )
    {
      if ( !mdec_timer )
      {
        mdec_status = 0;
        mdec_dma_status &= ~0x1000000u;
        mdec_timer = -1;
        irq_dma_assert_int(1u);
        result = mdec_timer;
      }
    }
    else
    {
      result = --mdec_timer;
    }
    if ( result < 0 )
    {
      if ( result <= -10 )
        mdec_timer_count = 0;
      else
        mdec_timer = --result;
    }
  }
  return result;
}

void mdec_dma_in_handler()
{
  int v0; // esi
  int v1; // eax

  v0 = mdec_dma_src[0];
  if ( mdec_dma_control[0] == 0x1000201 )
  {
    if ( mdec_disable )
      LOBYTE(mdec_disable_flag[0]) = 1;
    v1 = *(_DWORD *)mdec_command;
    if ( *(_DWORD *)mdec_command == 0x40000001 )
    {
      mdec_set_scale_table((int)ram + (mdec_dma_src[0] & 0x1FFFFF));
      v1 = *(_DWORD *)mdec_command;
    }
    if ( (v1 & 0xF5FF0000) == 0x30000000 )
    {
      mdec_in_ptr = (int)ram + (v0 & 0x1FFFFF);
      mdec_out_addr = (int)ram + (v0 & 0x1FFFFF);
    }
  }
}

int mdec_decode()
{
  int result; // eax
  char *v1; // ebx
  __m64 *v2; // esi
  int v3; // ebp
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  bool v7; // cc
  int v8; // [esp+0h] [ebp-4h]

  result = HIWORD(mdec_image_size) * (unsigned __int16)mdec_image_size;
  if ( mdec_dma_status == 0x1000200 )
  {
    v1 = (char *)mdec_in_ptr;
    if ( mdec_in_ptr )
    {
      if ( mdec_disable )
      {
        LOBYTE(mdec_disable_flag[0]) = 1;
        return result;
      }
      v2 = (__m64 *)((char *)ram + (mdec_dma_dest & 0x1FFFFF));
      v3 = *(_DWORD *)mdec_command & 0x8000000;
      v4 = 3 * result;
      if ( (*(_DWORD *)mdec_command & 0x8000000) == 0 )
        v4 = 2 * result;
      v5 = v4 / 384;
      if ( v4 / 384 < 31 )
        goto LABEL_15;
      v6 = v5 / 30;
      v7 = v5 / 30 <= 0;
      v5 %= 30;
      if ( !v7 )
      {
        v8 = v6;
        do
        {
          mdec_in_ptr = (int)mdec_rl_decode(v1, 30);
          mdec_idct_blocks(30);
          if ( v3 )
          {
            mdec_yuv_to_rgb((char *)mdec_idct_buffer, v2, (_WORD *)0x1E);
            v2 += 1920;
          }
          else
          {
            mdec_y_to_mono((unsigned int *)mdec_idct_buffer, v2, 30);
            v2 += 2880;
          }
          v1 = (char *)mdec_in_ptr;
          --v8;
        }
        while ( v8 );
      }
      if ( v5 )
      {
LABEL_15:
        mdec_in_ptr = (int)mdec_rl_decode(v1, v5);
        mdec_idct_blocks(v5);
        if ( v3 )
          mdec_yuv_to_rgb((char *)mdec_idct_buffer, v2, (_WORD *)v5);
        else
          mdec_y_to_mono((unsigned int *)mdec_idct_buffer, v2, v5);
      }
    }
    result = mdectiming;
    if ( mdectiming )
    {
      mdec_status = 0x44000000;
      mdec_timer_count = -65536;
      mdec_timer = 1;
    }
  }
  return result;
}

static int __cdecl mdec_set_scale_table(int a1)
{
  int result; // eax
  __int16 *v2; // ecx
  int v3; // edx
  _DWORD v4[63]; // [esp+10h] [ebp-200h]
  _DWORD v5[65]; // [esp+10Ch] [ebp-104h]

  v5[4] = 19266;
  v5[6] = 12873;
  v5[7] = 8867;
  v5[8] = 4520;
  v5[25] = 19266;
  v5[29] = 19266;
  v5[36] = 19266;
  v5[38] = 12873;
  v5[39] = 8867;
  v5[40] = 4520;
  v5[41] = 12873;
  v5[45] = 12873;
  v5[49] = 8867;
  v5[53] = 8867;
  v5[57] = 4520;
  v5[61] = 4520;
  result = 0;
  v5[1] = 0x4000;
  v5[2] = 22725;
  v5[3] = 21407;
  v5[5] = 0x4000;
  v5[9] = 22725;
  v5[10] = 31521;
  v5[11] = 29692;
  v5[12] = 26722;
  v5[13] = 22725;
  v5[14] = 17855;
  v5[15] = 12299;
  v5[16] = 6270;
  v5[17] = 21407;
  v5[18] = 29692;
  v5[19] = 27969;
  v5[20] = 25172;
  v5[21] = 21407;
  v5[22] = 16819;
  v5[23] = 11585;
  v5[24] = 5906;
  v5[26] = 26722;
  v5[27] = 25172;
  v5[28] = 22654;
  v5[30] = 15137;
  v5[31] = 10426;
  v5[32] = 5315;
  v5[33] = 0x4000;
  v5[34] = 22725;
  v5[35] = 21407;
  v5[37] = 0x4000;
  v5[42] = 17855;
  v5[43] = 16819;
  v5[44] = 15137;
  v5[46] = 10114;
  v5[47] = 6967;
  v5[48] = 3552;
  v5[50] = 12299;
  v5[51] = 11585;
  v5[52] = 10426;
  v5[54] = 6967;
  v5[55] = 4799;
  v5[56] = 2446;
  v5[58] = 6270;
  v5[59] = 5906;
  v5[60] = 5315;
  v5[62] = 3552;
  v5[63] = 2446;
  v5[64] = 1247;
  v4[0] = 0;
  v4[1] = 1;
  v4[2] = 5;
  v4[3] = 6;
  v4[4] = 14;
  v4[5] = 15;
  v4[6] = 27;
  v4[7] = 28;
  v4[8] = 2;
  v4[9] = 4;
  v4[10] = 7;
  v4[11] = 13;
  v4[12] = 16;
  v4[13] = 26;
  v4[14] = 29;
  v4[15] = 42;
  v4[16] = 3;
  v4[17] = 8;
  v4[18] = 12;
  v4[19] = 17;
  v4[20] = 25;
  v4[21] = 30;
  v4[22] = 41;
  v4[23] = 43;
  v4[24] = 9;
  v4[25] = 11;
  v4[26] = 18;
  v4[27] = 24;
  v4[28] = 31;
  v4[29] = 40;
  v4[30] = 44;
  v4[31] = 53;
  v4[32] = 10;
  v4[33] = 19;
  v4[34] = 23;
  v4[35] = 32;
  v4[36] = 39;
  v4[37] = 45;
  v4[38] = 52;
  v4[39] = 54;
  v4[40] = 20;
  v4[41] = 22;
  v4[42] = 33;
  v4[43] = 38;
  v4[44] = 46;
  v4[45] = 51;
  v4[46] = 55;
  v4[47] = 60;
  v4[48] = 21;
  v4[49] = 34;
  v4[50] = 37;
  v4[51] = 47;
  v4[52] = 50;
  v4[53] = 56;
  v4[54] = 59;
  v4[55] = 61;
  v4[56] = 35;
  v4[57] = 36;
  v4[58] = 48;
  v4[59] = 49;
  v4[60] = 57;
  v4[61] = 58;
  v4[62] = 62;
  v5[0] = 63;
  v2 = mdec_scale_table;
  do
  {
    v3 = v4[result];
    *v2++ = (v5[++result] * *(unsigned __int8 *)(v3 + a1) + 2048) >> 12;
  }
  while ( (int)v2 < (int)mdec_idct_buffer );
  return result * 4;
}

static char *__cdecl mdec_rl_decode(char *a1, int a2)
{
  int v2; // edx
  char *v3; // edi
  unsigned __int16 v4; // ax
  int v5; // ebx
  unsigned __int16 i; // cx
  _WORD *v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+20h] [ebp+8h]

  v8 = (_WORD *)mdec_coeff_buffer;
  memset(mdec_coeff_buffer, 0, 4 * ((unsigned int)(768 * a2) >> 2));
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

static void __cdecl mdec_idct_blocks(int a1)
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
  for ( i = (__m64 *)mdec_coeff_buffer; v2 < 6 * a1; v6 += 32 )
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

static int mdec_init_color_tables()
{
  int v0; // edi
  int v1; // esi
  int v2; // edx
  int v3; // ecx
  int v4; // eax
  int v5; // esi
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int result; // eax

  v0 = 0;
  v1 = 0;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  do
  {
    mdec_color_table_0[v4] = v3 >> 12;
    mdec_color_table_1[v4] = v2 >> 12;
    mdec_color_table_2[v4] = v1 >> 12;
    mdec_color_table_3[v4] = v0 >> 12;
    v3 += 5743;
    v2 -= 1408;
    v1 -= 2925;
    v0 += 7258;
    ++v4;
  }
  while ( v3 < 735104 );
  v5 = -929024;
  v6 = -735104;
  v7 = 374400;
  v8 = 180224;
  v9 = 0;
  do
  {
    mdec_color_table_4[v9] = v6 >> 12;
    mdec_color_table_5[v9] = v8 >> 12;
    mdec_color_table_6[v9] = v7 >> 12;
    mdec_color_table_7[v9] = v5 >> 12;
    v8 -= 1408;
    v6 += 5743;
    v5 += 7258;
    v7 -= 2925;
    ++v9;
  }
  while ( v8 > 0 );
  for ( result = 0; result < 256; ++result )
  {
    mdec_mono_table_0[result] = 0;
    mdec_mono_table_1[result] = result;
    mdec_mono_table_2[result] = -1;
  }
  return result;
}

static _WORD *__cdecl mdec_yuv_to_rgb(char *a1, _WORD *a2, _WORD *a3)
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

int __cdecl mdec_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+8h] [ebp-440h] BYREF
  int v4; // [esp+Bh] [ebp-43Dh]
  unsigned __int8 v5[1024]; // [esp+48h] [ebp-400h] BYREF

  memset(v5, 0, sizeof(v5));
  sprintf(Buffer, "%s", a1);
  v4 = 1248;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)mdec_command, 0x60u);
  gzwrite(a2, (unsigned __int8 *)mdec_scale_table, 0x80u);
  return gzwrite(a2, v5, 0x400u);
}

int __cdecl mdec_freeze2(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-40h] BYREF
  int v4; // [esp+7h] [ebp-3Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 96;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  return gzwrite(a2, (unsigned __int8 *)mdec_command, 0x60u);
}

int __cdecl mdec_unfreeze(int a1, _DWORD *a2)
{
  char v3[64]; // [esp+4h] [ebp-440h] BYREF
  char v4[1024]; // [esp+44h] [ebp-400h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, mdec_command, 96);
  gzread(a2, (char *)mdec_scale_table, 128);
  return gzread(a2, v4, 1024);
}

int __cdecl mdec_unfreeze2(int a1, _DWORD *a2)
{
  char v3[64]; // [esp+4h] [ebp-40h] BYREF

  gzread(a2, v3, 7);
  return gzread(a2, mdec_command, 96);
}

static int __cdecl mdec_idct_sse(__m64 *a1, int a2)
{
  __m64 v2; // mm0
  __m64 v3; // mm2
  __m64 v4; // mm4
  __m64 v5; // mm1
  __m64 v6; // mm0
  __m64 v7; // mm2
  __m64 v8; // mm5
  __m64 v9; // mm3
  __m64 v10; // mm6
  __m64 v11; // mm5
  __m64 v12; // mm4
  __m64 v13; // mm3
  __m64 v14; // mm0
  __m64 v15; // mm2
  __m64 v16; // mm5
  __m64 v17; // mm6
  __m64 v18; // mm5
  __m64 v19; // mm4
  __m64 v20; // mm1
  __m64 v21; // mm4
  __m64 v22; // mm7
  __m64 v23; // mm4
  __m64 v24; // mm5
  __m64 v25; // mm0
  __m64 v26; // mm3
  __m64 v27; // mm0
  __m64 v28; // mm2
  __m64 v29; // mm4
  __m64 v30; // mm1
  __m64 v31; // mm0
  __m64 v32; // mm2
  __m64 v33; // mm5
  __m64 v34; // mm3
  __m64 v35; // mm6
  __m64 v36; // mm5
  __m64 v37; // mm4
  __m64 v38; // mm3
  __m64 v39; // mm0
  __m64 v40; // mm2
  __m64 v41; // mm5
  __m64 v42; // mm6
  __m64 v43; // mm7
  __m64 v44; // mm5
  __m64 v45; // mm4
  __m64 v46; // mm1
  __m64 v47; // mm4
  __m64 v48; // mm7
  __m64 v49; // mm4
  __m64 v50; // mm5
  __m64 v51; // mm0
  __m64 v52; // mm3
  __m64 v53; // mm2
  __m64 v54; // mm6
  __m64 v55; // mm3
  __m64 v56; // mm5
  __m64 v57; // mm0
  __m64 v58; // mm1
  __m64 v59; // mm6
  __m64 v60; // mm5
  __m64 v61; // mm2
  __m64 v62; // mm7
  __m64 v63; // mm3
  __m64 v64; // mm4
  __m64 v65; // mm2
  __m64 v66; // mm7
  __m64 v67; // mm0
  __m64 v68; // mm7
  __m64 v69; // mm6
  __m64 v70; // mm5
  __m64 v71; // mm1
  __m64 v72; // mm5
  __m64 v73; // mm3
  __m64 v74; // mm4
  __m64 v75; // mm2
  __m64 v76; // mm3
  __m64 v77; // mm0
  __m64 v78; // mm1
  __m64 v79; // mm6
  __m64 v80; // mm1
  __m64 v81; // mm0
  __m64 v82; // mm3
  __m64 v83; // mm7
  __m64 v84; // mm2
  __m64 v85; // mm6
  __m64 v86; // mm2
  __m64 v87; // mm4
  __m64 v88; // mm7
  __m64 v89; // mm1
  __m64 v90; // mm7
  __m64 v91; // mm4
  __m64 v92; // mm2
  __m64 v93; // mm5
  __m64 v94; // mm0
  __m64 v95; // mm5
  __m64 v96; // mm4
  __m64 v97; // mm1
  __m64 v98; // mm5
  __m64 v99; // mm0
  __m64 v100; // mm3
  __m64 v101; // mm7
  __m64 v102; // mm6
  __m64 v103; // mm3
  __m64 v104; // mm1
  __m64 v105; // mm0
  __m64 v106; // mm2
  __m64 v107; // mm7
  __m64 v108; // mm6
  __m64 v109; // mm7
  __m64 v110; // mm4
  __m64 v111; // mm1
  __m64 v112; // mm5
  __m64 v113; // mm7
  __m64 v114; // mm2
  __m64 v115; // mm6
  __m64 *v116; // ebx
  __m64 v117; // mm3
  __m64 v118; // mm7
  __m64 *v119; // ecx
  __m64 *v120; // ebx
  __m64 v121; // mm2
  __m64 v122; // mm6
  __m64 v123; // mm3
  __m64 v124; // mm5
  __m64 v125; // mm0
  __m64 v126; // mm1
  __m64 v127; // mm6
  __m64 v128; // mm5
  __m64 v129; // mm2
  __m64 v130; // mm7
  __m64 v131; // mm3
  __m64 v132; // mm4
  __m64 v133; // mm2
  __m64 v134; // mm7
  __m64 v135; // mm0
  __m64 v136; // mm7
  __m64 v137; // mm6
  __m64 v138; // mm5
  __m64 v139; // mm1
  __m64 v140; // mm5
  __m64 v141; // mm3
  __m64 v142; // mm4
  __m64 v143; // mm2
  __m64 v144; // mm3
  __m64 v145; // mm0
  __m64 v146; // mm1
  __m64 v147; // mm6
  __m64 v148; // mm1
  __m64 v149; // mm0
  __m64 v150; // mm3
  __m64 v151; // mm7
  __m64 v152; // mm2
  __m64 v153; // mm6
  __m64 v154; // mm2
  __m64 v155; // mm4
  __m64 v156; // mm7
  __m64 v157; // mm1
  __m64 v158; // mm7
  __m64 v159; // mm4
  __m64 v160; // mm2
  __m64 v161; // mm5
  __m64 v162; // mm0
  __m64 v163; // mm5
  __m64 v164; // mm4
  __m64 v165; // mm1
  __m64 v166; // mm5
  __m64 v167; // mm0
  __m64 v168; // mm3
  __m64 v169; // mm7
  __m64 v170; // mm6
  __m64 v171; // mm3
  __m64 v172; // mm1
  __m64 v173; // mm0
  __m64 v174; // mm2
  __m64 v175; // mm7
  __m64 v176; // mm6
  __m64 v177; // mm7
  __m64 v178; // mm4
  __m64 v179; // mm1
  __m64 v180; // mm5
  __m64 v181; // mm7
  __m64 v182; // mm2
  __m64 v183; // mm6
  __m64 *v184; // ebx
  __m64 v185; // mm3
  __m64 v186; // mm7
  __m64 *v187; // ecx
  __m64 *v189; // ebx
  __m64 v190; // [esp+10h] [ebp-84h]
  __m64 v191; // [esp+10h] [ebp-84h]
  __m64 v192; // [esp+10h] [ebp-84h]
  __m64 v193; // [esp+18h] [ebp-7Ch]
  __m64 v194; // [esp+18h] [ebp-7Ch]
  __m64 v195; // [esp+18h] [ebp-7Ch]
  __m64 v196; // [esp+20h] [ebp-74h]
  __m64 v197; // [esp+20h] [ebp-74h]
  __m64 v198; // [esp+20h] [ebp-74h]
  __m64 v199; // [esp+28h] [ebp-6Ch]
  __m64 v200; // [esp+28h] [ebp-6Ch]
  __m64 v201; // [esp+28h] [ebp-6Ch]
  __m64 v202; // [esp+30h] [ebp-64h]
  __m64 v203; // [esp+30h] [ebp-64h]
  __m64 v204; // [esp+38h] [ebp-5Ch]
  __m64 v205; // [esp+38h] [ebp-5Ch]
  __m64 v206; // [esp+40h] [ebp-54h]
  __m64 v207; // [esp+48h] [ebp-4Ch]
  __m64 v208; // [esp+50h] [ebp-44h]
  __m64 v209; // [esp+50h] [ebp-44h]
  __m64 v210; // [esp+58h] [ebp-3Ch]
  __m64 v211; // [esp+58h] [ebp-3Ch]
  __m64 v212; // [esp+60h] [ebp-34h]
  __m64 v213; // [esp+60h] [ebp-34h]
  __m64 v214; // [esp+68h] [ebp-2Ch]
  __m64 v215; // [esp+68h] [ebp-2Ch]
  __m64 v216; // [esp+70h] [ebp-24h]
  __m64 v217; // [esp+78h] [ebp-1Ch]
  __m64 v218; // [esp+80h] [ebp-14h]
  __m64 v219; // [esp+88h] [ebp-Ch]

  v2 = a1[6];
  v3 = a1[10];
  v4 = a1[14];
  v5 = _m_paddw(v3, v2);
  v6 = _m_psllwi(_m_psubw(v3, v2), 2u);
  v7 = _m_pmulhw(v6, _m_from_int64(qword_455C28));
  v8 = a1[2];
  v9 = _m_paddw(v8, v4);
  v10 = _m_psubw(v9, v5);
  v11 = _m_psllwi(_m_psubw(v8, v4), 2u);
  v12 = a1[12];
  v13 = _m_paddw(v9, v5);
  v14 = _m_paddw(_m_pmulhw(v6, _m_from_int64(qword_455C38)), _m_pmulhw(v11, _m_from_int64(qword_455C40)));
  v15 = _m_psubw(_m_paddw(v7, _m_pmulhw(v11, _m_from_int64(qword_455C30))), v13);
  v16 = a1[4];
  v17 = _m_psubw(_m_pmulhw(_m_psllwi(v10, 2u), _m_from_int64(qword_455C20)), v15);
  v190 = _m_paddw(v16, v12);
  v18 = _m_pmulhw(_m_psllwi(_m_psubw(v16, v12), 2u), _m_from_int64(qword_455C20));
  v19 = a1[8];
  v202 = _m_paddw(v14, v17);
  v196 = _m_psubw(v18, v190);
  v20 = _m_psubw(*a1, v19);
  v21 = _m_paddw(*a1, v19);
  v22 = _m_paddw(v21, v190);
  v23 = _m_psubw(v21, v190);
  v24 = _m_psubw(v20, v196);
  v25 = _m_psubw(v22, v13);
  v191 = _m_paddw(v22, v13);
  v26 = _m_paddw(v20, v196);
  v218 = v25;
  v197 = _m_paddw(v26, v15);
  v216 = _m_psubw(v26, v15);
  v208 = _m_paddw(v23, v202);
  v206 = _m_psubw(v23, v202);
  v203 = _m_paddw(v24, v17);
  v212 = _m_psubw(v24, v17);
  v27 = a1[7];
  v28 = a1[11];
  v29 = a1[15];
  v30 = _m_paddw(v28, v27);
  v31 = _m_psllwi(_m_psubw(v28, v27), 2u);
  v32 = _m_pmulhw(v31, _m_from_int64(qword_455C28));
  v33 = a1[3];
  v34 = _m_paddw(v33, v29);
  v35 = _m_psubw(v34, v30);
  v36 = _m_psllwi(_m_psubw(v33, v29), 2u);
  v37 = a1[13];
  v38 = _m_paddw(v34, v30);
  v39 = _m_paddw(_m_pmulhw(v31, _m_from_int64(qword_455C38)), _m_pmulhw(v36, _m_from_int64(qword_455C40)));
  v40 = _m_psubw(_m_paddw(v32, _m_pmulhw(v36, _m_from_int64(qword_455C30))), v38);
  v41 = a1[5];
  v42 = _m_psubw(_m_pmulhw(_m_psllwi(v35, 2u), _m_from_int64(qword_455C20)), v40);
  v193 = _m_paddw(v41, v37);
  v43 = a1[1];
  v44 = _m_pmulhw(_m_psllwi(_m_psubw(v41, v37), 2u), _m_from_int64(qword_455C20));
  v45 = a1[9];
  v204 = _m_paddw(v39, v42);
  v199 = _m_psubw(v44, v193);
  v46 = _m_psubw(v43, v45);
  v47 = _m_paddw(v43, v45);
  v48 = _m_paddw(v47, v193);
  v49 = _m_psubw(v47, v193);
  v50 = _m_psubw(v46, v199);
  v51 = _m_psubw(v48, v38);
  v194 = _m_paddw(v48, v38);
  v52 = _m_paddw(v46, v199);
  v219 = v51;
  v200 = _m_paddw(v52, v40);
  v217 = _m_psubw(v52, v40);
  v210 = _m_paddw(v49, v204);
  v207 = _m_psubw(v49, v204);
  v205 = _m_paddw(v50, v42);
  v214 = _m_psubw(v50, v42);
  v53 = _m_psubw(v191, v194);
  v54 = _m_paddw(v191, v194);
  v55 = _m_paddw(v197, v200);
  v56 = _m_psubw(v197, v200);
  v57 = _m_punpckldq(_m_punpcklwd(v54, v55), _m_punpckhwd(v54, v55));
  v58 = _m_punpckldq(_m_punpcklwd(v53, v56), _m_punpckhwd(v53, v56));
  v59 = _m_paddw(v206, v207);
  v60 = _m_paddw(v203, v205);
  v61 = _m_psubw(v206, v207);
  v62 = _m_psubw(v203, v205);
  v63 = _m_punpckldq(_m_punpcklwd(v60, v59), _m_punpckhwd(v60, v59));
  v64 = _m_punpckldq(_m_punpcklwd(v62, v61), _m_punpckhwd(v62, v61));
  v65 = _m_punpckhdq(v57, v63);
  v66 = _m_punpckldq(v57, v63);
  v67 = _m_paddw(v66, v65);
  v68 = _m_psubw(v66, v65);
  v69 = _m_psubw(_m_pmulhw(_m_psllwi(_m_punpckhdq(v58, v64), 2u), _m_from_int64(qword_455C20)), v65);
  v70 = _m_punpckldq(v58, v64);
  v71 = _m_paddw(v70, v69);
  v72 = _m_psubw(v70, v69);
  v73 = _m_punpckldq(v191, v194);
  v74 = _m_punpckhdq(v194, v191);
  v192 = v67;
  v75 = _m_paddw(v73, v74);
  v76 = _m_psubw(v73, v74);
  v195 = v71;
  v77 = _m_punpckhdq(v200, v197);
  v78 = _m_punpckldq(v197, v200);
  v79 = _m_paddw(v78, v77);
  v198 = v72;
  v80 = _m_psubw(v78, v77);
  v201 = v68;
  v81 = _m_punpckhdq(_m_punpckhwd(v76, v80), _m_punpcklwd(v75, v79));
  v82 = _m_punpckhdq(_m_punpcklwd(v76, v80), _m_punpckhwd(v75, v79));
  v83 = _m_punpckhdq(v205, v203);
  v84 = _m_punpckldq(v203, v205);
  v85 = _m_paddw(v84, v83);
  v86 = _m_psubw(v84, v83);
  v87 = _m_punpckhdq(v207, v206);
  v88 = _m_punpckldq(v206, v207);
  v89 = _m_paddw(v88, v87);
  v90 = _m_psubw(v88, v87);
  v91 = _m_punpckhdq(_m_punpckhwd(v86, v90), _m_punpcklwd(v85, v89));
  v92 = _m_punpckhdq(_m_punpcklwd(v86, v90), _m_punpckhwd(v85, v89));
  v93 = v81;
  v94 = _m_punpckldq(v81, v91);
  v95 = _m_punpckhdq(v93, v91);
  v96 = _m_punpckhdq(v82, v92);
  v97 = _m_psubw(v95, v96);
  v98 = _m_paddw(v95, v96);
  v99 = _m_psllwi(v94, 2u);
  v100 = _m_psllwi(_m_punpckldq(v82, v92), 2u);
  v101 = _m_pmulhw(v99, _m_from_int64(qword_455C38));
  v102 = _m_pmulhw(v100, _m_from_int64(qword_455C40));
  v103 = _m_psubw(_m_paddw(_m_pmulhw(v100, _m_from_int64(qword_455C30)), _m_pmulhw(v99, _m_from_int64(qword_455C28))), v98);
  v104 = _m_psubw(_m_pmulhw(_m_psllwi(v97, 2u), _m_from_int64(qword_455C20)), v103);
  v105 = _m_packsswb(_m_psrawi(_m_paddw(v195, v103), 5u), _m_psrawi(_m_psubw(v192, v98), 5u));
  v106 = _m_packsswb(_m_psrawi(_m_paddw(v192, v98), 5u), _m_psrawi(_m_psubw(v195, v103), 5u));
  v107 = _m_paddw(_m_paddw(v101, v102), v104);
  v108 = _m_packsswb(_m_psrawi(_m_psubw(v201, v107), 5u), _m_psrawi(_m_psubw(v198, v104), 5u));
  v109 = _m_packsswb(_m_psrawi(_m_paddw(v198, v104), 5u), _m_psrawi(_m_paddw(v201, v107), 5u));
  v110 = _m_punpckhbw(v106, v105);
  v111 = _m_punpcklbw(v106, v105);
  v112 = _m_punpcklbw(v109, v108);
  v113 = _m_punpckhbw(v109, v108);
  v114 = _m_punpcklwd(v111, v112);
  v115 = _m_punpcklwd(v113, v110);
  v116 = *(__m64 **)(a2 + 4);
  v117 = _m_punpckhwd(v111, v112);
  v118 = _m_punpckhwd(v113, v110);
  *(__m64 *)*(_DWORD *)a2 = _m_punpckldq(v114, v115);
  v119 = *(__m64 **)(a2 + 8);
  v116->m64_u64 = _m_punpckhdq(v114, v115).m64_u64;
  v120 = *(__m64 **)(a2 + 12);
  v119->m64_u64 = _m_punpckldq(v117, v118).m64_u64;
  v120->m64_u64 = _m_punpckhdq(v117, v118).m64_u64;
  v121 = _m_psubw(v208, v210);
  v122 = _m_paddw(v208, v210);
  v123 = _m_paddw(v212, v214);
  v124 = _m_psubw(v212, v214);
  v125 = _m_punpckldq(_m_punpcklwd(v122, v123), _m_punpckhwd(v122, v123));
  v126 = _m_punpckldq(_m_punpcklwd(v121, v124), _m_punpckhwd(v121, v124));
  v127 = _m_paddw(v218, v219);
  v128 = _m_paddw(v216, v217);
  v129 = _m_psubw(v218, v219);
  v130 = _m_psubw(v216, v217);
  v131 = _m_punpckldq(_m_punpcklwd(v128, v127), _m_punpckhwd(v128, v127));
  v132 = _m_punpckldq(_m_punpcklwd(v130, v129), _m_punpckhwd(v130, v129));
  v133 = _m_punpckhdq(v125, v131);
  v134 = _m_punpckldq(v125, v131);
  v135 = _m_paddw(v134, v133);
  v136 = _m_psubw(v134, v133);
  v137 = _m_psubw(_m_pmulhw(_m_psllwi(_m_punpckhdq(v126, v132), 2u), _m_from_int64(qword_455C20)), v133);
  v138 = _m_punpckldq(v126, v132);
  v139 = _m_paddw(v138, v137);
  v140 = _m_psubw(v138, v137);
  v141 = _m_punpckldq(v208, v210);
  v142 = _m_punpckhdq(v210, v208);
  v209 = v135;
  v143 = _m_paddw(v141, v142);
  v144 = _m_psubw(v141, v142);
  v211 = v139;
  v145 = _m_punpckhdq(v214, v212);
  v146 = _m_punpckldq(v212, v214);
  v147 = _m_paddw(v146, v145);
  v213 = v140;
  v148 = _m_psubw(v146, v145);
  v215 = v136;
  v149 = _m_punpckhdq(_m_punpckhwd(v144, v148), _m_punpcklwd(v143, v147));
  v150 = _m_punpckhdq(_m_punpcklwd(v144, v148), _m_punpckhwd(v143, v147));
  v151 = _m_punpckhdq(v217, v216);
  v152 = _m_punpckldq(v216, v217);
  v153 = _m_paddw(v152, v151);
  v154 = _m_psubw(v152, v151);
  v155 = _m_punpckhdq(v219, v218);
  v156 = _m_punpckldq(v218, v219);
  v157 = _m_paddw(v156, v155);
  v158 = _m_psubw(v156, v155);
  v159 = _m_punpckhdq(_m_punpckhwd(v154, v158), _m_punpcklwd(v153, v157));
  v160 = _m_punpckhdq(_m_punpcklwd(v154, v158), _m_punpckhwd(v153, v157));
  v161 = v149;
  v162 = _m_punpckldq(v149, v159);
  v163 = _m_punpckhdq(v161, v159);
  v164 = _m_punpckhdq(v150, v160);
  v165 = _m_psubw(v163, v164);
  v166 = _m_paddw(v163, v164);
  v167 = _m_psllwi(v162, 2u);
  v168 = _m_psllwi(_m_punpckldq(v150, v160), 2u);
  v169 = _m_pmulhw(v167, _m_from_int64(qword_455C38));
  v170 = _m_pmulhw(v168, _m_from_int64(qword_455C40));
  v171 = _m_psubw(_m_paddw(_m_pmulhw(v168, _m_from_int64(qword_455C30)), _m_pmulhw(v167, _m_from_int64(qword_455C28))), v166);
  v172 = _m_psubw(_m_pmulhw(_m_psllwi(v165, 2u), _m_from_int64(qword_455C20)), v171);
  v173 = _m_packsswb(_m_psrawi(_m_paddw(v211, v171), 5u), _m_psrawi(_m_psubw(v209, v166), 5u));
  v174 = _m_packsswb(_m_psrawi(_m_paddw(v209, v166), 5u), _m_psrawi(_m_psubw(v211, v171), 5u));
  v175 = _m_paddw(_m_paddw(v169, v170), v172);
  v176 = _m_packsswb(_m_psrawi(_m_psubw(v215, v175), 5u), _m_psrawi(_m_psubw(v213, v172), 5u));
  v177 = _m_packsswb(_m_psrawi(_m_paddw(v213, v172), 5u), _m_psrawi(_m_paddw(v215, v175), 5u));
  v178 = _m_punpckhbw(v174, v173);
  v179 = _m_punpcklbw(v174, v173);
  v180 = _m_punpcklbw(v177, v176);
  v181 = _m_punpckhbw(v177, v176);
  v182 = _m_punpcklwd(v179, v180);
  v183 = _m_punpcklwd(v181, v178);
  v184 = *(__m64 **)(a2 + 20);
  v185 = _m_punpckhwd(v179, v180);
  v186 = _m_punpckhwd(v181, v178);
  *(__m64 *)*(_DWORD *)(a2 + 16) = _m_punpckldq(v182, v183);
  v187 = *(__m64 **)(a2 + 24);
  v184->m64_u64 = _m_punpckhdq(v182, v183).m64_u64;
  v189 = *(__m64 **)(a2 + 28);
  v187->m64_u64 = _m_punpckldq(v185, v186).m64_u64;
  v189->m64_u64 = _m_punpckhdq(v185, v186).m64_u64;
  return a2 + 28;
}

static void mdec_sse_m_empty()
{
  _m_empty();
}

static void __cdecl mdec_y_to_mono(unsigned int *a1, __m64 *a2, int a3)
{
  unsigned int *v3; // esi
  unsigned int *v4; // eax
  unsigned int *v5; // ebx
  unsigned int *v6; // ecx
  __m64 *v7; // edi
  __m64 *v8; // edx
  __m64 v9; // mm0
  __m64 v10; // mm0
  __m64 v11; // mm4
  __m64 v12; // mm1
  __m64 v13; // mm1
  __m64 v14; // mm5
  __m64 v15; // mm6
  __m64 v16; // mm0
  __m64 v17; // mm1
  __m64 v18; // mm7
  __m64 v19; // mm1
  __m64 v20; // mm4
  __m64 v21; // mm2
  __m64 v22; // mm6
  __m64 v23; // mm5
  __m64 v24; // mm3
  __m64 v25; // mm5
  __m64 v26; // mm0
  __m64 v27; // mm1
  __m64 v28; // mm0
  __m64 v29; // mm5
  __m64 v30; // mm4
  __m64 v31; // mm3
  __m64 v32; // mm3
  __m64 v33; // mm7
  __m64 v34; // mm0
  __m64 v35; // mm6
  __m64 v36; // mm2
  __m64 v37; // mm4
  __m64 v38; // mm3
  __m64 v39; // mm7
  __m64 v40; // mm2
  __m64 v41; // mm7
  __m64 v42; // mm3
  __m64 v43; // mm0
  __m64 v44; // mm3
  __m64 v45; // mm1
  __m64 v46; // mm5
  __m64 v47; // mm5
  int v48; // [esp+Ch] [ebp-1Ch]
  int v49; // [esp+10h] [ebp-18h]
  int v50; // [esp+14h] [ebp-14h]

  v3 = a1 + 32;
  v4 = a1 + 34;
  v5 = a1;
  v6 = a1 + 16;
  v7 = a2;
  v8 = a2 + 6;
  do
  {
    v48 = 2;
    do
    {
      v49 = 2;
      do
      {
        v50 = 4;
        do
        {
          v9 = _m_from_int(*v5);
          v10 = _m_punpcklbw(v9, v9);
          v11 = _m_punpcklwd(v10, v10);
          v12 = _m_from_int(*v6);
          v13 = _m_punpcklbw(v12, v12);
          v14 = _m_punpcklwd(v13, v13);
          v15 = _m_paddb(_m_from_int(*v3), _m_from_int64(qword_455C70));
          v16 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v11, v11), 6u), _m_from_int64(qword_455C50)),
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v14, v14), 6u), _m_from_int64(qword_455C58)));
          v17 = _m_punpcklbw(v15, v15);
          v18 = _m_punpcklwd(v17, v15);
          v19 = _m_psrlqi(v17, 0x10u);
          v20 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v11, v11), 6u), _m_from_int64(qword_455C60)),
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v14, v14), 6u), _m_from_int64(qword_455C68)));
          v21 = _m_por(
                  _m_psrlqi(_m_pand(v16, _m_from_int64(qword_455C78)), 0x10u),
                  _m_psllqi(_m_pand(v20, _m_from_int64(qword_455C78)), 0x10u));
          v22 = _m_paddb(_m_from_int(*v4), _m_from_int64(qword_455C70));
          v7->m64_u64 = _m_packuswb(
                                            _m_paddsw(_m_punpcklbw(v18, _m_from_int((int)mdec_mono_expand_value)), v16),
                                            _m_paddsw(_m_punpcklbw(v19, _m_from_int((int)mdec_mono_expand_value)), v21)).m64_u64;
          v23 = _m_punpcklbw(v22, v22);
          v24 = _m_punpcklbw(_m_punpcklwd(v23, v22), _m_from_int((int)mdec_mono_expand_value));
          v25 = _m_psrlqi(v23, 0x10u);
          v8->m64_u64 = _m_packuswb(
                                            _m_paddsw(v24, v16),
                                            _m_paddsw(
                                              _m_punpcklbw(_m_punpckldq(v25, v25), _m_from_int((int)mdec_mono_expand_value)),
                                              v21)).m64_u64;
          v26 = _m_psrlqi(_m_from_int(*v5), 0x10u);
          v27 = _m_paddsw(
                  _m_punpcklbw(
                    _m_punpcklwd(_m_psrlqi(v19, 0x18u), _m_psrlqi(v19, 0x20u)),
                    _m_from_int((int)mdec_mono_expand_value)),
                  v20);
          v28 = _m_punpcklbw(v26, v26);
          v29 = _m_paddsw(
                  _m_punpcklbw(
                    _m_punpcklwd(_m_psrlqi(v25, 0x18u), _m_psrlqi(v25, 0x20u)),
                    _m_from_int((int)mdec_mono_expand_value)),
                  v20);
          v30 = _m_punpcklwd(v28, v28);
          v31 = _m_psrlqi(_m_from_int(*v6), 0x10u);
          v32 = _m_punpcklbw(v31, v31);
          v33 = _m_punpcklwd(v32, v32);
          v34 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v30, v30), 6u), _m_from_int64(qword_455C50)),
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v33, v33), 6u), _m_from_int64(qword_455C58)));
          v35 = _m_paddb(_m_from_int(v3[1]), _m_from_int64(qword_455C70));
          v36 = _m_psrlqi(_m_pand(v34, _m_from_int64(qword_455C78)), 0x10u);
          v37 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v30, v30), 6u), _m_from_int64(qword_455C60)),
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v33, v33), 6u), _m_from_int64(qword_455C68)));
          v38 = _m_paddb(_m_from_int(v4[1]), _m_from_int64(qword_455C70));
          v39 = _m_psllqi(_m_pand(v37, _m_from_int64(qword_455C78)), 0x10u);
          v7[1].m64_u64 = _m_packuswb(
                                              v27,
                                              _m_paddsw(
                                                _m_punpcklbw(
                                                  _m_punpcklwd(_m_punpcklbw(v35, v35), v35),
                                                  _m_from_int((int)mdec_mono_expand_value)),
                                                v34)).m64_u64;
          v40 = _m_por(v36, v39);
          v41 = v38;
          v42 = _m_paddsw(_m_punpcklbw(_m_punpcklwd(_m_punpcklbw(v38, v38), v38), _m_from_int(0)), v34);
          v43 = _m_psrlqi(v41, 8u);
          v8[1].m64_u64 = _m_packuswb(v29, v42).m64_u64;
          v44 = _m_psrlqi(v35, 8u);
          v45 = _m_psrlqi(v44, 8u);
          v3 += 4;
          v4 += 4;
          v46 = _m_psrlqi(v43, 8u);
          v7 += 12;
          v8 += 12;
          v5 += 2;
          v47 = _m_paddsw(
                  _m_punpcklbw(
                    _m_punpcklwd(v46, _m_psrlqi(_m_punpcklbw(v46, v46), 0x10u)),
                    _m_from_int((int)mdec_mono_expand_value)),
                  v37);
          v7[-10].m64_u64 = _m_packuswb(
                                                _m_paddsw(_m_punpcklbw(_m_punpcklbw(v44, v44), _m_from_int(0)), v40),
                                                _m_paddsw(
                                                  _m_punpcklbw(
                                                    _m_punpcklwd(v45, _m_psrlqi(_m_punpcklbw(v45, v45), 0x10u)),
                                                    _m_from_int((int)mdec_mono_expand_value)),
                                                  v37)).m64_u64;
          v6 += 2;
          v8[-10].m64_u64 = _m_packuswb(_m_paddsw(_m_punpcklbw(_m_punpcklbw(v43, v43), _m_from_int(0)), v40), v47).m64_u64;
          --v50;
        }
        while ( v50 );
        v5 -= 7;
        v6 -= 7;
        v7 -= 45;
        v8 -= 45;
        --v49;
      }
      while ( v49 );
      v5 += 6;
      v6 += 6;
      v7 += 42;
      v8 += 42;
      --v48;
    }
    while ( v48 );
    v5 += 80;
    v6 += 80;
    v3 += 32;
    v4 += 32;
    --a3;
  }
  while ( a3 );
  mdec_sse_m_empty();
}





/* Decompiled globals (previously generated in src/_gen) */
unsigned char mdec_coeff_buffer[0x5a00];
unsigned int mdec_mono_expand_value;
unsigned short mdec_bit15_flag;
unsigned char mdec_color_lookup[0x80];
unsigned int mdec_color_table_0[0x80];
unsigned int mdec_color_table_1[0x80];
unsigned int mdec_color_table_2[0x80];
unsigned int mdec_color_table_3[0x80];
unsigned int mdec_color_table_4[0x80];
unsigned int mdec_color_table_5[0x80];
unsigned int mdec_color_table_6[0x80];
unsigned int mdec_color_table_7[0x80];
unsigned int mdec_command;
unsigned int mdec_dma_dest;
unsigned int mdec_idct_buffer[0xb40];
unsigned char mdec_idct_buffer_end[0x1680];
unsigned int mdec_image_size;
unsigned int mdec_in_ptr;
unsigned char mdec_mono_table_0[0x100];
unsigned char mdec_mono_table_1[0x80];
unsigned char mdec_mono_table_2[0x100];
unsigned int mdec_nonzero_counts[0xb8];
unsigned int mdec_out_addr;
unsigned int mdec_param_word;
unsigned int mdec_scale_table[0x20];
unsigned int mdec_status;
unsigned char mdec_timer;
unsigned int mdec_timer_count;
unsigned int mdec_zigzag[13] = {0x0, 0x1, 0x8, 0x10, 0x9, 0x2, 0x3, 0xa, 0x11, 0x18, 0x20, 0x19, 0x12};
unsigned __int64 qword_455C20 = 0x5a825a825a825a82;
unsigned __int64 qword_455C28 = 0xcf04cf04cf04cf04;
unsigned __int64 qword_455C30 = 0x7641764176417641;
unsigned __int64 qword_455C38 = 0x896f896f896f896f;
unsigned __int64 qword_455C40 = 0xcf04cf04cf04cf04;
unsigned __int64 qword_455C50 = 0x59ba0000d24e59ba;
unsigned __int64 qword_455C58 = 0x7168ea0c0000;
unsigned __int64 qword_455C60 = 0xd24e59ba0000;
unsigned __int64 qword_455C68 = 0x7168ea0c00007168;
unsigned __int64 qword_455C70 = 0x80808080;
unsigned __int64 qword_455C78 = 0xffffffff0000;
