#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static unsigned char xa_stereo_nibble_offset_table = 0x0;
static unsigned char xa_prev_sample_rate[0x20];
static unsigned int xa_mono_nibble_offset_table[4] = {0x0, 0x2, 0x8, 0xa};
static unsigned int xa_mono_nibble_offset_table_end = 0x0;


/* static prototypes for internal functions */
static int xa_get_audio_mode(int hdr);
static int xa_setup_adpcm_decoder(uint32_t *out, int hdr, int soundbuf, int flag);
static int xa_decode_stereo_blocks(int out, int soundbuf);
static int xa_decode_mono_blocks(int out, int soundbuf, int unused);

static uint32_t * xa_clear_adpcm_state(uint32_t *state)
{
  *state = 0;
  state[1] = 0;
  return state;
}

static int * xa_decode_adpcm_block(int *state, uint8_t header, int16_t *src, uint16_t *dst, unsigned int step)
{
  int prev1;
  int shift;
  int s3;
  int s2;
  int s1;
  int s0;
  int prod1;
  int prod2;
  uint16_t *dst1;
  uint16_t *dst2;
  uint16_t *dst3;
  int16_t *next_src;
  int filter;
  int prev2;
  int count;

  filter = header >> 4;
  prev1 = *state;
  shift = header & 0xF;
  prev2 = state[1];
  count = 7;
  while ( 1 )
  {
    next_src = src + 1;
    s3 = 16 * ((int)(*src & 0xFFFFF000) >> shift);
    s2 = 16 * ((int16_t)(16 * (*src & 0xFF00)) >> shift);
    s1 = 16 * ((int16_t)(*src & 0xF000) >> shift);
    s0 = 16 * ((int16_t)(*src << 12) >> shift);
    switch ( filter )
    {
      case 0:
        goto LABEL_9;
      case 1:
        s0 -= (-960 * prev1) >> 10;
        s1 -= (-960 * s0) >> 10;
        s2 -= (-960 * s1) >> 10;
        s3 -= (-960 * s2) >> 10;
        goto LABEL_9;
      case 2:
        s0 -= (832 * prev2 - 1840 * prev1) >> 10;
        s1 -= (832 * prev1 - 1840 * s0) >> 10;
        s2 -= (832 * s0 - 1840 * s1) >> 10;
        prod1 = 1840 * s2;
        prod2 = 832 * s1;
        goto LABEL_8;
      case 3:
        s0 -= (880 * prev2 - 1568 * prev1) >> 10;
        s1 -= (880 * prev1 - 1568 * s0) >> 10;
        s2 -= (880 * s0 - 1568 * s1) >> 10;
        prod1 = 1568 * s2;
        prod2 = 880 * s1;
        goto LABEL_8;
      case 4:
        s0 -= (960 * prev2 - 1952 * prev1) >> 10;
        s1 -= (960 * prev1 - 1952 * s0) >> 10;
        s2 -= (960 * s0 - 1952 * s1) >> 10;
        prod1 = 1952 * s2;
        prod2 = 960 * s1;
LABEL_8:
        s3 -= (prod2 - prod1) >> 10;
LABEL_9:
        prev2 = s2;
        prev1 = s3;
        break;
      default:
        break;
    }
    if ( s0 >= -524288 )
    {
      if ( s0 > 524272 )
        s0 = 524272;
    }
    else
    {
      s0 = -524288;
    }
    *dst = s0 >> 4;
    dst1 = &dst[step];
    if ( s1 >= -524288 )
    {
      if ( s1 > 524272 )
        s1 = 524272;
    }
    else
    {
      s1 = -524288;
    }
    *dst1 = s1 >> 4;
    dst2 = &dst1[step];
    if ( s2 >= -524288 )
    {
      if ( s2 > 524272 )
        s2 = 524272;
    }
    else
    {
      s2 = -524288;
    }
    *dst2 = s2 >> 4;
    dst3 = &dst2[step];
    if ( s3 >= -524288 )
    {
      if ( s3 > 524272 )
        s3 = 524272;
    }
    else
    {
      s3 = -524288;
    }
    *dst3 = s3 >> 4;
    dst = &dst3[step];
    if ( !--count )
      break;
    src = next_src;
  }
  *state = prev1;
  state[1] = prev2;
  return state;
}

int xa_decode_wrapper(uint32_t *out, int hdr, int flag)
{
  if ( xa_get_audio_mode(hdr) == 2 )
    return -(xa_setup_adpcm_decoder(out, hdr, hdr + 8, flag) != 0);
  else
    return -1;
}

static int xa_get_audio_mode(int hdr)
{
  if ( (*(uint8_t *)(hdr + 2) & 0x24) == 0x24 )
    return 2;
  else
    return (*(uint8_t *)(hdr + 2) & 2) == 2;
}

static int xa_setup_adpcm_decoder(uint32_t *out, int hdr, int soundbuf, int flag)
{
  int stereo;
  int bits;
  int tmp1;
  char rate;
  int tmp2;
  int tmp3;

  stereo = 1;
  if ( flag )
  {
    xa_prev_sample_rate[0] = (*(uint8_t *)(hdr + 3) >> 2) & 3;
    if ( xa_prev_sample_rate[0] )
    {
      if ( xa_prev_sample_rate[0] == 1 )
        *out = 18900;
      else
        *out = 0;
    }
    else
    {
      *out = 37800;
    }
    bits = (*(uint8_t *)(hdr + 3) >> 4) & 3;
    if ( bits )
    {
      if ( bits == 1 )
        out[1] = 8;
      else
        out[1] = 0;
    }
    else
    {
      out[1] = 4;
    }
    out[2] = (*(uint8_t *)(hdr + 3) & 3) != 0 && (*(uint8_t *)(hdr + 3) & 3) == 1;
    if ( !*out )
      return -1;
    if ( !out[2] )
    {
      xa_clear_adpcm_state(out + 4);
      out[3] = 4032;
      xa_decode_mono_blocks((int)out, soundbuf, tmp2);
      return 0;
    }
    xa_clear_adpcm_state(out + 4);
    xa_clear_adpcm_state(out + 6);
    if ( out[1] != tmp1 || *out != 37800 && *out != 18900 )
      return -1;
    out[3] = 2016;
  }
  if ( (*(uint8_t *)(hdr + 3) & 3) == (uint8_t)stereo )
  {
    out[2] = stereo;
    out[3] = 2016;
  }
  else
  {
    out[2] = 0;
    out[3] = 4032;
  }
  if ( out[2] )
    xa_decode_stereo_blocks((int)out, soundbuf);
  else
    xa_decode_mono_blocks((int)out, soundbuf, tmp3);
  if ( spu_adpcm_flag )
    return 0;
  rate = (*(uint8_t *)(hdr + 3) >> 2) & 3;
  if ( xa_prev_sample_rate[0] == rate )
    return 0;
  xa_prev_sample_rate[0] = (*(uint8_t *)(hdr + 3) >> 2) & 3;
  if ( !rate )
  {
    *out = 37800;
    spu_set_adpcm_flag_cb();
    return 0;
  }
  if ( rate == 1 )
    *out = 18900;
  else
    *out = 0;
  spu_set_adpcm_flag_cb();
  return 0;
}

static int xa_decode_stereo_blocks(int out, int soundbuf)
{
  int tmp;
  int sample;
  int block;
  char *table;
  int16_t *dst;
  int p;
  int count;
  int tmp1;
  int tmp2;
  int sample2;
  int16_t *dst2;
  int p2;
  int count2;
  int tmp3;
  int tmp4;
  bool done;
  int remaining;
  uint16_t *outp;
  int src;
  int blocks;
  int16_t samples[4096];

  tmp = soundbuf;
  sample = out + 16;
  outp = (uint16_t *)(out + 32);
  src = soundbuf;
  blocks = 18;
  do
  {
    block = tmp + 16;
    table = &xa_stereo_nibble_offset_table;
    do
    {
      dst = samples;
      p = block;
      count = 7;
      do
      {
        LOWORD(tmp) = *(uint8_t *)(p + 12);
        LOWORD(sample) = *(uint8_t *)(p + 8) & 0xF;
        ++dst;
        p += 16;
        tmp *= 16;
        tmp1 = tmp | sample;
        LOWORD(tmp) = *(uint8_t *)(p - 12) & 0xF;
        tmp2 = tmp | (16 * tmp1);
        LOWORD(tmp) = *(uint8_t *)(p - 16) & 0xF;
        sample = tmp | (16 * tmp2);
        --count;
        *(dst - 1) = sample;
      }
      while ( count );
      xa_decode_adpcm_block((int *)(out + 16), *(uint8_t *)(src + *(uint32_t *)table), samples, outp, 2u);
      dst2 = samples;
      p2 = block;
      count2 = 7;
      do
      {
        LOWORD(tmp) = *(uint8_t *)(p2 + 8) >> 4;
        LOWORD(sample2) = *(uint8_t *)(p2 + 12) >> 4;
        ++dst2;
        p2 += 16;
        tmp3 = tmp | (16 * sample2);
        LOWORD(tmp) = *(uint8_t *)(p2 - 12) >> 4;
        tmp4 = tmp | (16 * tmp3);
        LOWORD(tmp) = *(uint8_t *)(p2 - 16) >> 4;
        sample2 = tmp | (16 * tmp4);
        --count2;
        *(dst2 - 1) = sample2;
      }
      while ( count2 );
      HIWORD(tmp) = HIWORD(src);
      xa_decode_adpcm_block((int *)(out + 24), *(uint8_t *)(src + *(uint32_t *)table + 1), samples, outp + 1, 2u);
      table += 4;
      ++block;
      outp += 56;
    }
    while ( (int)table < (int)xa_mono_nibble_offset_table );
    tmp = src + 128;
    remaining = blocks - 1;
    done = blocks == 1;
    src += 128;
    --blocks;
  }
  while ( !done );
  return remaining;
}

static int xa_decode_mono_blocks(int out, int soundbuf, int unused)
{
  int sample;
  int tmp;
  int block;
  uint32_t *table;
  int16_t *dst;
  int p;
  int count;
  int tmp1;
  int tmp2;
  int sample2;
  int16_t *dst2;
  int p2;
  int count2;
  int tmp3;
  int tmp4;
  bool done;
  int remaining;
  uint16_t *outp;
  int src;
  int *state;
  int blocks;
  int16_t samples[4096];

  tmp = soundbuf;
  outp = (uint16_t *)(out + 32);
  state = (int *)(out + 16);
  src = soundbuf;
  blocks = 18;
  do
  {
    block = tmp + 16;
    table = xa_mono_nibble_offset_table;
    do
    {
      dst = samples;
      p = block;
      count = 7;
      do
      {
        LOWORD(tmp) = *(uint8_t *)(p + 12);
        LOWORD(sample) = *(uint8_t *)(p + 8) & 0xF;
        ++dst;
        p += 16;
        tmp *= 16;
        tmp1 = tmp | sample;
        LOWORD(tmp) = *(uint8_t *)(p - 12) & 0xF;
        tmp2 = tmp | (16 * tmp1);
        LOWORD(tmp) = *(uint8_t *)(p - 16) & 0xF;
        sample = tmp | (16 * tmp2);
        --count;
        *(dst - 1) = sample;
      }
      while ( count );
      xa_decode_adpcm_block(state, *(uint8_t *)(src + *table), samples, outp, 1u);
      dst2 = samples;
      p2 = block;
      count2 = 7;
      do
      {
        LOWORD(tmp) = *(uint8_t *)(p2 + 8) >> 4;
        LOWORD(sample2) = *(uint8_t *)(p2 + 12) >> 4;
        ++dst2;
        p2 += 16;
        tmp3 = tmp | (16 * sample2);
        LOWORD(tmp) = *(uint8_t *)(p2 - 12) >> 4;
        tmp4 = tmp | (16 * tmp3);
        LOWORD(tmp) = *(uint8_t *)(p2 - 16) >> 4;
        sample2 = tmp | (16 * tmp4);
        --count2;
        *(dst2 - 1) = sample2;
      }
      while ( count2 );
      HIWORD(tmp) = HIWORD(src);
      xa_decode_adpcm_block(state, *(uint8_t *)(src + *table++ + 1), samples, outp + 28, 1u);
      ++block;
      outp += 56;
    }
    while ( (int)table < (int)&xa_mono_nibble_offset_table_end );
    tmp = src + 128;
    remaining = blocks - 1;
    done = blocks == 1;
    src += 128;
    --blocks;
  }
  while ( !done );
  return remaining;
}
