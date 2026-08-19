#include "pch.h"

/* static prototypes for internal functions */
static int xa_get_audio_mode(int a1);
static int xa_setup_adpcm_decoder(uint32_t *a1, int a2, int a3, int a4);
static int xa_decode_stereo_blocks(int a1, int a2);
static int xa_decode_mono_blocks(int a1, int a2, int a3);

static uint32_t * xa_clear_adpcm_state(uint32_t *a1)
{
  *a1 = 0;
  a1[1] = 0;
  return a1;
}

static int * xa_decode_adpcm_block(int *a1, uint8_t a2, int16_t *a3, uint16_t *a4, unsigned int a5)
{
  int v6;
  char v7;
  int v8;
  int v9;
  int v10;
  int v11;
  int v12;
  int v13;
  uint16_t *v14;
  uint16_t *v15;
  uint16_t *v16;
  int16_t *v18;
  int v19;
  unsigned int v20;
  char v21;
  int v22;
  int v23;

  v19 = a2 >> 4;
  v6 = *a1;
  v7 = a2 & 0xF;
  v22 = a1[1];
  v21 = a2 & 0xF;
  v20 = a5;
  v23 = 7;
  while ( 1 )
  {
    v18 = a3 + 1;
    v8 = 16 * ((int)(*a3 & 0xFFFFF000) >> v7);
    v9 = 16 * ((int16_t)(16 * (*a3 & 0xFF00)) >> v7);
    v10 = 16 * ((int16_t)(*a3 & 0xF000) >> v21);
    v11 = 16 * ((int16_t)(*a3 << 12) >> v21);
    switch ( v19 )
    {
      case 0:
        goto LABEL_9;
      case 1:
        v11 -= (-960 * v6) >> 10;
        v10 -= (-960 * v11) >> 10;
        v9 -= (-960 * v10) >> 10;
        v8 -= (-960 * v9) >> 10;
        goto LABEL_9;
      case 2:
        v11 -= (832 * v22 - 1840 * v6) >> 10;
        v10 -= (832 * v6 - 1840 * v11) >> 10;
        v9 -= (832 * v11 - 1840 * v10) >> 10;
        v12 = 1840 * v9;
        v13 = 832 * v10;
        goto LABEL_8;
      case 3:
        v11 -= (880 * v22 - 1568 * v6) >> 10;
        v10 -= (880 * v6 - 1568 * v11) >> 10;
        v9 -= (880 * v11 - 1568 * v10) >> 10;
        v12 = 1568 * v9;
        v13 = 880 * v10;
        goto LABEL_8;
      case 4:
        v11 -= (960 * v22 - 1952 * v6) >> 10;
        v10 -= (960 * v6 - 1952 * v11) >> 10;
        v9 -= (960 * v11 - 1952 * v10) >> 10;
        v12 = 1952 * v9;
        v13 = 960 * v10;
LABEL_8:
        v8 -= (v13 - v12) >> 10;
LABEL_9:
        v22 = v9;
        v6 = v8;
        break;
      default:
        break;
    }
    if ( v11 >= -524288 )
    {
      if ( v11 > 524272 )
        v11 = 524272;
    }
    else
    {
      v11 = -524288;
    }
    *a4 = v11 >> 4;
    v14 = &a4[v20];
    if ( v10 >= -524288 )
    {
      if ( v10 > 524272 )
        v10 = 524272;
    }
    else
    {
      v10 = -524288;
    }
    *v14 = v10 >> 4;
    v15 = &v14[v20];
    if ( v9 >= -524288 )
    {
      if ( v9 > 524272 )
        v9 = 524272;
    }
    else
    {
      v9 = -524288;
    }
    *v15 = v9 >> 4;
    v16 = &v15[v20];
    if ( v8 >= -524288 )
    {
      if ( v8 > 524272 )
        v8 = 524272;
    }
    else
    {
      v8 = -524288;
    }
    *v16 = v8 >> 4;
    a4 = &v16[v20];
    if ( !--v23 )
      break;
    a3 = v18;
    v7 = v21;
  }
  *a1 = v6;
  a1[1] = v22;
  return a1;
}

int xa_decode_wrapper(uint32_t *a1, int a2, int a3)
{
  if ( xa_get_audio_mode(a2) == 2 )
    return -(xa_setup_adpcm_decoder(a1, a2, a2 + 8, a3) != 0);
  else
    return -1;
}

static int xa_get_audio_mode(int a1)
{
  if ( (*(uint8_t *)(a1 + 2) & 0x24) == 0x24 )
    return 2;
  else
    return (*(uint8_t *)(a1 + 2) & 2) == 2;
}

static int xa_setup_adpcm_decoder(uint32_t *a1, int a2, int a3, int a4)
{
  int v4;
  int v5;
  int v7;
  char v8;
  int v9;
  int v10;

  v4 = 1;
  if ( a4 )
  {
    xa_prev_sample_rate[0] = (*(uint8_t *)(a2 + 3) >> 2) & 3;
    if ( xa_prev_sample_rate[0] )
    {
      if ( xa_prev_sample_rate[0] == 1 )
        *a1 = 18900;
      else
        *a1 = 0;
    }
    else
    {
      *a1 = 37800;
    }
    v5 = (*(uint8_t *)(a2 + 3) >> 4) & 3;
    if ( v5 )
    {
      if ( v5 == 1 )
        a1[1] = 8;
      else
        a1[1] = 0;
    }
    else
    {
      a1[1] = 4;
    }
    a1[2] = (*(uint8_t *)(a2 + 3) & 3) != 0 && (*(uint8_t *)(a2 + 3) & 3) == 1;
    if ( !*a1 )
      return -1;
    if ( !a1[2] )
    {
      xa_clear_adpcm_state(a1 + 4);
      a1[3] = 4032;
      xa_decode_mono_blocks((int)a1, a3, v9);
      return 0;
    }
    xa_clear_adpcm_state(a1 + 4);
    xa_clear_adpcm_state(a1 + 6);
    if ( a1[1] != v7 || *a1 != 37800 && *a1 != 18900 )
      return -1;
    a1[3] = 2016;
  }
  if ( (*(uint8_t *)(a2 + 3) & 3) == (uint8_t)v4 )
  {
    a1[2] = v4;
    a1[3] = 2016;
  }
  else
  {
    a1[2] = 0;
    a1[3] = 4032;
  }
  if ( a1[2] )
    xa_decode_stereo_blocks((int)a1, a3);
  else
    xa_decode_mono_blocks((int)a1, a3, v10);
  if ( spu_adpcm_flag )
    return 0;
  v8 = (*(uint8_t *)(a2 + 3) >> 2) & 3;
  if ( xa_prev_sample_rate[0] == v8 )
    return 0;
  xa_prev_sample_rate[0] = (*(uint8_t *)(a2 + 3) >> 2) & 3;
  if ( !v8 )
  {
    *a1 = 37800;
    spu_set_adpcm_flag_cb();
    return 0;
  }
  if ( v8 == 1 )
    *a1 = 18900;
  else
    *a1 = 0;
  spu_set_adpcm_flag_cb();
  return 0;
}

static int xa_decode_stereo_blocks(int a1, int a2)
{
  int v2;
  int v3;
  int v4;
  char *v5;
  int16_t *v6;
  int v7;
  int v8;
  int v9;
  int v10;
  int v11;
  int16_t *v12;
  int v13;
  int v14;
  int v15;
  int v16;
  bool v17;
  int result;
  uint16_t *v19;
  int v20;
  int v21;
  int16_t v22[4096];

  v2 = a2;
  v3 = a1 + 16;
  v19 = (uint16_t *)(a1 + 32);
  v20 = a2;
  v21 = 18;
  do
  {
    v4 = v2 + 16;
    v5 = &xa_stereo_nibble_offset_table;
    do
    {
      v6 = v22;
      v7 = v4;
      v8 = 7;
      do
      {
        LOWORD(v2) = *(uint8_t *)(v7 + 12);
        LOWORD(v3) = *(uint8_t *)(v7 + 8) & 0xF;
        ++v6;
        v7 += 16;
        v2 *= 16;
        v9 = v2 | v3;
        LOWORD(v2) = *(uint8_t *)(v7 - 12) & 0xF;
        v10 = v2 | (16 * v9);
        LOWORD(v2) = *(uint8_t *)(v7 - 16) & 0xF;
        v3 = v2 | (16 * v10);
        --v8;
        *(v6 - 1) = v3;
      }
      while ( v8 );
      xa_decode_adpcm_block((int *)(a1 + 16), *(uint8_t *)(v20 + *(uint32_t *)v5), v22, v19, 2u);
      v12 = v22;
      v13 = v4;
      v14 = 7;
      do
      {
        LOWORD(v2) = *(uint8_t *)(v13 + 8) >> 4;
        LOWORD(v11) = *(uint8_t *)(v13 + 12) >> 4;
        ++v12;
        v13 += 16;
        v15 = v2 | (16 * v11);
        LOWORD(v2) = *(uint8_t *)(v13 - 12) >> 4;
        v16 = v2 | (16 * v15);
        LOWORD(v2) = *(uint8_t *)(v13 - 16) >> 4;
        v11 = v2 | (16 * v16);
        --v14;
        *(v12 - 1) = v11;
      }
      while ( v14 );
      HIWORD(v2) = HIWORD(v20);
      xa_decode_adpcm_block((int *)(a1 + 24), *(uint8_t *)(v20 + *(uint32_t *)v5 + 1), v22, v19 + 1, 2u);
      v5 += 4;
      ++v4;
      v19 += 56;
    }
    while ( (int)v5 < (int)xa_mono_nibble_offset_table );
    v2 = v20 + 128;
    result = v21 - 1;
    v17 = v21 == 1;
    v20 += 128;
    --v21;
  }
  while ( !v17 );
  return result;
}

static int xa_decode_mono_blocks(int a1, int a2, int a3)
{
  int v3;
  int v4;
  int v5;
  uint32_t *v6;
  int16_t *v7;
  int v8;
  int v9;
  int v10;
  int v11;
  int v12;
  int16_t *v13;
  int v14;
  int v15;
  int v16;
  int v17;
  bool v18;
  int result;
  uint16_t *v20;
  int v21;
  int *v22;
  int v23;
  int16_t v24[4096];

  v4 = a2;
  v20 = (uint16_t *)(a1 + 32);
  v22 = (int *)(a1 + 16);
  v21 = a2;
  v23 = 18;
  do
  {
    v5 = v4 + 16;
    v6 = xa_mono_nibble_offset_table;
    do
    {
      v7 = v24;
      v8 = v5;
      v9 = 7;
      do
      {
        LOWORD(v4) = *(uint8_t *)(v8 + 12);
        LOWORD(v3) = *(uint8_t *)(v8 + 8) & 0xF;
        ++v7;
        v8 += 16;
        v4 *= 16;
        v10 = v4 | v3;
        LOWORD(v4) = *(uint8_t *)(v8 - 12) & 0xF;
        v11 = v4 | (16 * v10);
        LOWORD(v4) = *(uint8_t *)(v8 - 16) & 0xF;
        v3 = v4 | (16 * v11);
        --v9;
        *(v7 - 1) = v3;
      }
      while ( v9 );
      xa_decode_adpcm_block(v22, *(uint8_t *)(v21 + *v6), v24, v20, 1u);
      v13 = v24;
      v14 = v5;
      v15 = 7;
      do
      {
        LOWORD(v4) = *(uint8_t *)(v14 + 8) >> 4;
        LOWORD(v12) = *(uint8_t *)(v14 + 12) >> 4;
        ++v13;
        v14 += 16;
        v16 = v4 | (16 * v12);
        LOWORD(v4) = *(uint8_t *)(v14 - 12) >> 4;
        v17 = v4 | (16 * v16);
        LOWORD(v4) = *(uint8_t *)(v14 - 16) >> 4;
        v12 = v4 | (16 * v17);
        --v15;
        *(v13 - 1) = v12;
      }
      while ( v15 );
      HIWORD(v4) = HIWORD(v21);
      xa_decode_adpcm_block(v22, *(uint8_t *)(v21 + *v6++ + 1), v24, v20 + 28, 1u);
      ++v5;
      v20 += 56;
    }
    while ( (int)v6 < (int)&xa_mono_nibble_offset_table_end );
    v4 = v21 + 128;
    result = v23 - 1;
    v18 = v23 == 1;
    v21 += 128;
    --v23;
  }
  while ( !v18 );
  return result;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char xa_stereo_nibble_offset_table = 0x0;
unsigned char xa_prev_sample_rate[0x20];
unsigned int xa_mono_nibble_offset_table[4] = {0x0, 0x2, 0x8, 0xa};
unsigned int xa_mono_nibble_offset_table_end = 0x0;
