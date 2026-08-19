#include "pch.h"

/* ---------------------------------------------------------------------------
 * The decompiled MDEC code below used x86 MMX intrinsics (__m64, _m_paddw,
 * _m_pmulhw, ...).  They are reimplemented here as plain portable C helpers
 * operating on a 64-bit "vector": 16-bit lane i occupies bits [16*i, 16*i+16),
 * 8-bit lane i occupies bits [8*i, 8*i+8) -- the same lane layout the MMX
 * instructions used.  The helpers reproduce the exact MMX semantics (wrapping
 * adds/subs, saturating ops, signed pmulhw rounding, arithmetic shifts), so
 * the converted code behaves identically to the original, while being fully
 * portable -- modern compilers can auto-vectorize this scalar code.
 * ------------------------------------------------------------------------- */
typedef uint64_t mdec_v64;

/* load 4 consecutive 16-bit values (lane 0 = first element) */
static inline mdec_v64 md_load4(const unsigned short *p)
{
    mdec_v64 v = 0;
    int i;
    for (i = 0; i < 4; i++)
        v |= (mdec_v64)p[i] << (16 * i);
    return v;
}

/* store 8 bytes; byte i of the vector goes to address p+i */
static inline void md_store8(void *p, mdec_v64 v)
{
    unsigned char *d = (unsigned char *)p;
    int i;
    for (i = 0; i < 8; i++)
        d[i] = (unsigned char)(v >> (8 * i));
}

/* _m_from_int / _m_from_int64 */
static inline mdec_v64 md_from_int(unsigned int x)
{
    return (mdec_v64)x;
}

static inline mdec_v64 md_from_int64(mdec_v64 x)
{
    return x;
}

/* _m_paddb: 8-bit wrapping add */
static inline mdec_v64 md_paddb(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 8; i++)
        r |= (mdec_v64)(unsigned char)((unsigned char)(a >> (8 * i)) + (unsigned char)(b >> (8 * i))) << (8 * i);
    return r;
}

/* _m_paddw / _m_psubw: 16-bit wrapping add/sub */
static inline mdec_v64 md_paddw(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
        r |= (mdec_v64)(unsigned short)((unsigned short)(a >> (16 * i)) + (unsigned short)(b >> (16 * i))) << (16 * i);
    return r;
}

static inline mdec_v64 md_psubw(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
        r |= (mdec_v64)(unsigned short)((unsigned short)(a >> (16 * i)) - (unsigned short)(b >> (16 * i))) << (16 * i);
    return r;
}

/* _m_paddsw: saturating 16-bit add */
static inline mdec_v64 md_paddsw(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        long s = (long)(short)(a >> (16 * i)) + (long)(short)(b >> (16 * i));
        if (s > 32767) s = 32767;
        if (s < -32768) s = -32768;
        r |= (mdec_v64)(unsigned short)(short)s << (16 * i);
    }
    return r;
}

/* _m_pmulhw: high 16 bits of the signed 16x16 product */
static inline mdec_v64 md_pmulhw(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
        r |= (mdec_v64)(unsigned short)(((long)(short)(a >> (16 * i)) * (long)(short)(b >> (16 * i))) >> 16) << (16 * i);
    return r;
}

/* _m_psllwi / _m_psllqi / _m_psrlqi */
static inline mdec_v64 md_psllwi(mdec_v64 a, int count)
{
    mdec_v64 r = 0;
    int i;
    count &= 15;
    for (i = 0; i < 4; i++)
        r |= (mdec_v64)(unsigned short)((unsigned short)(a >> (16 * i)) << count) << (16 * i);
    return r;
}

static inline mdec_v64 md_psllqi(mdec_v64 a, int count)
{
    return a << (count & 63);
}

static inline mdec_v64 md_psrlqi(mdec_v64 a, int count)
{
    return a >> (count & 63);
}

/* _m_psrawi: per-lane arithmetic right shift (portable formulation) */
static inline mdec_v64 md_psrawi(mdec_v64 a, int count)
{
    mdec_v64 r = 0;
    int i;
    count &= 15;
    for (i = 0; i < 4; i++)
    {
        unsigned short x = (unsigned short)(a >> (16 * i));
        unsigned short s = (x & 0x8000u)
                         ? (unsigned short)~((unsigned short)~x >> count)
                         : (unsigned short)(x >> count);
        r |= (mdec_v64)(unsigned short)(short)s << (16 * i);
    }
    return r;
}

/* _m_pand / _m_por */
static inline mdec_v64 md_pand(mdec_v64 a, mdec_v64 b)
{
    return a & b;
}

static inline mdec_v64 md_por(mdec_v64 a, mdec_v64 b)
{
    return a | b;
}

/* _m_packsswb: saturate the 4 words of a into bytes 0-3 and the 4 words of b
 * into bytes 4-7 */
static inline mdec_v64 md_packsswb(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        long va = (long)(short)(a >> (16 * i));
        long vb = (long)(short)(b >> (16 * i));
        if (va > 127) va = 127;
        if (va < -128) va = -128;
        if (vb > 127) vb = 127;
        if (vb < -128) vb = -128;
        r |= (mdec_v64)(unsigned char)(signed char)va << (8 * i);
        r |= (mdec_v64)(unsigned char)(signed char)vb << (8 * (i + 4));
    }
    return r;
}

/* _m_packuswb: saturate the 4 words of a into bytes 0-3 and the 4 words of b
 * into bytes 4-7 (unsigned) */
static inline mdec_v64 md_packuswb(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        long va = (long)(short)(a >> (16 * i));
        long vb = (long)(short)(b >> (16 * i));
        if (va > 255) va = 255;
        if (va < 0) va = 0;
        if (vb > 255) vb = 255;
        if (vb < 0) vb = 0;
        r |= (mdec_v64)(unsigned char)va << (8 * i);
        r |= (mdec_v64)(unsigned char)vb << (8 * (i + 4));
    }
    return r;
}

/* _m_punpcklbw / _m_punpckhbw / _m_punpcklwd / _m_punpckhwd /
 * _m_punpckldq / _m_punpckhdq */
static inline mdec_v64 md_punpcklbw(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        r |= (mdec_v64)(unsigned char)(a >> (8 * i)) << (16 * i);
        r |= (mdec_v64)(unsigned char)(b >> (8 * i)) << (16 * i + 8);
    }
    return r;
}

static inline mdec_v64 md_punpckhbw(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        r |= (mdec_v64)(unsigned char)(a >> (8 * (i + 4))) << (16 * i);
        r |= (mdec_v64)(unsigned char)(b >> (8 * (i + 4))) << (16 * i + 8);
    }
    return r;
}

static inline mdec_v64 md_punpcklwd(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 2; i++)
    {
        r |= (mdec_v64)(unsigned short)(a >> (16 * i)) << (32 * i);
        r |= (mdec_v64)(unsigned short)(b >> (16 * i)) << (32 * i + 16);
    }
    return r;
}

static inline mdec_v64 md_punpckhwd(mdec_v64 a, mdec_v64 b)
{
    mdec_v64 r = 0;
    int i;
    for (i = 0; i < 2; i++)
    {
        r |= (mdec_v64)(unsigned short)(a >> (16 * (i + 2))) << (32 * i);
        r |= (mdec_v64)(unsigned short)(b >> (16 * (i + 2))) << (32 * i + 16);
    }
    return r;
}

static inline mdec_v64 md_punpckldq(mdec_v64 a, mdec_v64 b)
{
    return (a & 0xFFFFFFFFu) | ((b & 0xFFFFFFFFu) << 32);
}

static inline mdec_v64 md_punpckhdq(mdec_v64 a, mdec_v64 b)
{
    return (a >> 32) | (b & 0xFFFFFFFF00000000ull);
}

/* static prototypes for internal functions */
static int mdec_set_scale_table(int a1);
static char * mdec_rl_decode(char *a1, int a2);
static void mdec_idct_blocks(int a1);
static int mdec_init_color_tables();
static uint16_t * mdec_yuv_to_rgb(char *a1, uint16_t *a2, uint16_t *a3);
static void mdec_idct_sse(const unsigned short *a1, int a2);
static void mdec_y_to_mono(unsigned int *a1, unsigned char *a2, int a3);

static char *mdec_init_pointers()
{
  char *v0;
  char *result;

  v0 = mdec_idct_buffer_end;
  result = (char *)mdec_idct_buffer;
  do
  {
    *(uint32_t *)v0 = result;
    result += 8;
    v0 += 4;
  }
  while ( (int)result < (int)mdec_idct_buffer_end );
  return result;
}

int mdec_init()
{
  *(uint32_t *)mdec_command = 0;
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

int16_t mdec_write_command(unsigned int a1)
{
  int16_t result;

  *(uint32_t *)mdec_command = a1;
  if ( (a1 & 0xF5FF0000) == 0x30000000 )
    mdec_param_word = (uint16_t)a1;
  result = (a1 >> 10) & 0x8000;
  mdec_bit15_flag = result;
  return result;
}

int mdec_handle_special_command(int a1)
{
  int result;

  if ( a1 == 0x80000000 )
  {
    mdec_in_ptr = mdec_out_addr;
    return mdec_out_addr;
  }
  return result;
}

char mdec_timer_handler()
{
  char result;

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
  int v0;
  int v1;

  v0 = mdec_dma_src[0];
  if ( mdec_dma_control[0] == 0x1000201 )
  {
    if ( mdec_disable )
      LOBYTE(mdec_disable_flag[0]) = 1;
    v1 = *(uint32_t *)mdec_command;
    if ( *(uint32_t *)mdec_command == 0x40000001 )
    {
      mdec_set_scale_table((int)ram + (mdec_dma_src[0] & 0x1FFFFF));
      v1 = *(uint32_t *)mdec_command;
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
  int result;
  char *v1;
  unsigned char *v2;
  int v3;
  int v4;
  int v5;
  int v6;
  bool v7;
  int v8;

  result = HIWORD(mdec_image_size) * (uint16_t)mdec_image_size;
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
      v2 = (unsigned char *)ram + (mdec_dma_dest & 0x1FFFFF);
      v3 = *(uint32_t *)mdec_command & 0x8000000;
      v4 = 3 * result;
      if ( (*(uint32_t *)mdec_command & 0x8000000) == 0 )
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
            mdec_yuv_to_rgb((char *)mdec_idct_buffer, (uint16_t *)v2, (uint16_t *)0x1E);
            v2 += 15360;
          }
          else
          {
            mdec_y_to_mono((unsigned int *)mdec_idct_buffer, v2, 30);
            v2 += 23040;
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
          mdec_yuv_to_rgb((char *)mdec_idct_buffer, (uint16_t *)v2, (uint16_t *)v5);
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

static int mdec_set_scale_table(int a1)
{
  int result;
  int16_t *v2;
  int v3;
  uint32_t v4[63];
  uint32_t v5[65];

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
    *v2++ = (v5[++result] * *(uint8_t *)(v3 + a1) + 2048) >> 12;
  }
  while ( (int)v2 < (int)mdec_idct_buffer );
  return result * 4;
}

static char * mdec_rl_decode(char *a1, int a2)
{
  int v2;
  char *v3;
  uint16_t v4;
  int v5;
  uint16_t i;
  uint16_t *v8;
  int v9;

  v8 = (uint16_t *)mdec_coeff_buffer;
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
    v4 = *(uint16_t *)v3;
    v5 = 0;
    v3 += 4;
    *v8 = mdec_scale_table[0] * ((int16_t)(v4 << 6) >> 6);
    for ( i = *((uint16_t *)v3 - 1); i != 0xFE00; v3 += 2 )
    {
      v5 += (i >> 10) + 1;
      if ( v5 > 63 )
        break;
      v8[mdec_zigzag[v5]] = (v4 >> 10) * (i << 22 >> 22) * mdec_scale_table[mdec_zigzag[v5]] / 8;
      i = *(uint16_t *)v3;
    }
    mdec_nonzero_counts[v9] = v5;
    v8 += 64;
    ++v9;
  }
  while ( v9 < v2 );
  return v3;
}

static void mdec_idct_blocks(int a1)
{
  int *v1;
  int v2;
  const unsigned short *i;
  int v4;
  int v5;
  char *v6;
  int *v7;

  v1 = mdec_idct_buffer;
  v2 = 0;
  v6 = mdec_idct_buffer_end;
  v7 = mdec_idct_buffer;
  for ( i = (const unsigned short *)mdec_coeff_buffer; v2 < 6 * a1; v6 += 32 )
  {
    if ( mdec_nonzero_counts[v2] )
    {
      mdec_idct_sse(i, (int)v6);
    }
    else
    {
      v4 = (int)i[0] >> 5;
      BYTE1(v4) = v4;
      v5 = v4 << 16;
      LOWORD(v5) = v4;
      memset32(v1, v5, 0x10u);
    }
    v1 = v7 + 16;
    i += 64;
    ++v2;
    v7 += 16;
  }
}

static int mdec_init_color_tables()
{
  int v0;
  int v1;
  int v2;
  int v3;
  int v4;
  int v5;
  int v6;
  int v7;
  int v8;
  int v9;
  int result;

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

static uint16_t * mdec_yuv_to_rgb(char *a1, uint16_t *a2, uint16_t *a3)
{
  uint16_t *result;
  char *v4;
  char *v5;
  char *v6;
  int v7;
  int v8;
  int v9;
  int v10;
  int v11;
  int v12;
  int v13;
  int v14;
  bool v15;
  bool v16;
  int v17;
  int v18;
  uint16_t *v19;
  int v20;
  int v21;
  int v22;
  int v23;

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
                  | ((uint8_t)mdec_color_lookup[*v5 + v22] >> 3)
                  | (4 * (mdec_color_lookup[*v5 + v20] & 0xF8 | (32 * (mdec_color_lookup[*v5 + v10] & 0xF8))));
          result[1] = mdec_bit15_flag
                    | ((uint8_t)mdec_color_lookup[v5[1] + v22] >> 3)
                    | (4 * (mdec_color_lookup[v5[1] + v20] & 0xF8 | (32 * (mdec_color_lookup[v5[1] + v10] & 0xF8))));
          result[16] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[v5[8] + v22] >> 3)
                     | (4 * (mdec_color_lookup[v5[8] + v20] & 0xF8 | (32 * (mdec_color_lookup[v5[8] + v10] & 0xF8))));
          result[17] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[v5[9] + v22] >> 3)
                     | (4 * (mdec_color_lookup[v5[9] + v20] & 0xF8 | (32 * (mdec_color_lookup[v5[9] + v10] & 0xF8))));
          v11 = a1[68];
          v12 = a1[4];
          v21 = ((-1408 * v12) >> 12) + ((-2925 * v11) >> 12);
          v23 = (7258 * v12) >> 12;
          v13 = (5743 * v11) >> 12;
          result[8] = mdec_bit15_flag
                    | ((uint8_t)mdec_color_lookup[*v6 + v23] >> 3)
                    | (4 * (mdec_color_lookup[*v6 + v21] & 0xF8 | (32 * (mdec_color_lookup[*v6 + v13] & 0xF8))));
          result[9] = mdec_bit15_flag
                    | ((uint8_t)mdec_color_lookup[v6[1] + v23] >> 3)
                    | (4 * (mdec_color_lookup[v6[1] + v21] & 0xF8 | (32 * (mdec_color_lookup[v6[1] + v13] & 0xF8))));
          result[24] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[v6[8] + v23] >> 3)
                     | (4 * (mdec_color_lookup[v6[8] + v21] & 0xF8 | (32 * (mdec_color_lookup[v6[8] + v13] & 0xF8))));
          v14 = v6[9];
          v5 += 2;
          v6 += 2;
          result += 2;
          result[23] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[v14 + v23] >> 3)
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
      v15 = v19 == (uint16_t *)1;
      a1 = v4;
      v19 = (uint16_t *)((char *)v19 - 1);
    }
    while ( !v15 );
  }
  return result;
}

int mdec_freeze(const char *a1, int a2)
{
  char Buffer[3];
  int v4;
  uint8_t v5[1024];

  memset(v5, 0, sizeof(v5));
  sprintf(Buffer, "%s", a1);
  v4 = 1248;
  gzwrite(a2, (uint8_t *)Buffer, 7u);
  gzwrite(a2, (uint8_t *)mdec_command, 0x60u);
  gzwrite(a2, (uint8_t *)mdec_scale_table, 0x80u);
  return gzwrite(a2, v5, 0x400u);
}

int mdec_freeze2(const char *a1, int a2)
{
  char Buffer[3];
  int v4;

  sprintf(Buffer, "%s", a1);
  v4 = 96;
  gzwrite(a2, (uint8_t *)Buffer, 7u);
  return gzwrite(a2, (uint8_t *)mdec_command, 0x60u);
}

int mdec_unfreeze(int a1, uint32_t *a2)
{
  char v3[64];
  char v4[1024];

  gzread(a2, v3, 7);
  gzread(a2, mdec_command, 96);
  gzread(a2, (char *)mdec_scale_table, 128);
  return gzread(a2, v4, 1024);
}

int mdec_unfreeze2(int a1, uint32_t *a2)
{
  char v3[64];

  gzread(a2, v3, 7);
  return gzread(a2, mdec_command, 96);
}

static void mdec_idct_sse(const unsigned short *a1, int a2)
{
  mdec_v64 v2;
  mdec_v64 v3;
  mdec_v64 v4;
  mdec_v64 v5;
  mdec_v64 v6;
  mdec_v64 v7;
  mdec_v64 v8;
  mdec_v64 v9;
  mdec_v64 v10;
  mdec_v64 v11;
  mdec_v64 v12;
  mdec_v64 v13;
  mdec_v64 v14;
  mdec_v64 v15;
  mdec_v64 v16;
  mdec_v64 v17;
  mdec_v64 v18;
  mdec_v64 v19;
  mdec_v64 v20;
  mdec_v64 v21;
  mdec_v64 v22;
  mdec_v64 v23;
  mdec_v64 v24;
  mdec_v64 v25;
  mdec_v64 v26;
  mdec_v64 v27;
  mdec_v64 v28;
  mdec_v64 v29;
  mdec_v64 v30;
  mdec_v64 v31;
  mdec_v64 v32;
  mdec_v64 v33;
  mdec_v64 v34;
  mdec_v64 v35;
  mdec_v64 v36;
  mdec_v64 v37;
  mdec_v64 v38;
  mdec_v64 v39;
  mdec_v64 v40;
  mdec_v64 v41;
  mdec_v64 v42;
  mdec_v64 v43;
  mdec_v64 v44;
  mdec_v64 v45;
  mdec_v64 v46;
  mdec_v64 v47;
  mdec_v64 v48;
  mdec_v64 v49;
  mdec_v64 v50;
  mdec_v64 v51;
  mdec_v64 v52;
  mdec_v64 v53;
  mdec_v64 v54;
  mdec_v64 v55;
  mdec_v64 v56;
  mdec_v64 v57;
  mdec_v64 v58;
  mdec_v64 v59;
  mdec_v64 v60;
  mdec_v64 v61;
  mdec_v64 v62;
  mdec_v64 v63;
  mdec_v64 v64;
  mdec_v64 v65;
  mdec_v64 v66;
  mdec_v64 v67;
  mdec_v64 v68;
  mdec_v64 v69;
  mdec_v64 v70;
  mdec_v64 v71;
  mdec_v64 v72;
  mdec_v64 v73;
  mdec_v64 v74;
  mdec_v64 v75;
  mdec_v64 v76;
  mdec_v64 v77;
  mdec_v64 v78;
  mdec_v64 v79;
  mdec_v64 v80;
  mdec_v64 v81;
  mdec_v64 v82;
  mdec_v64 v83;
  mdec_v64 v84;
  mdec_v64 v85;
  mdec_v64 v86;
  mdec_v64 v87;
  mdec_v64 v88;
  mdec_v64 v89;
  mdec_v64 v90;
  mdec_v64 v91;
  mdec_v64 v92;
  mdec_v64 v93;
  mdec_v64 v94;
  mdec_v64 v95;
  mdec_v64 v96;
  mdec_v64 v97;
  mdec_v64 v98;
  mdec_v64 v99;
  mdec_v64 v100;
  mdec_v64 v101;
  mdec_v64 v102;
  mdec_v64 v103;
  mdec_v64 v104;
  mdec_v64 v105;
  mdec_v64 v106;
  mdec_v64 v107;
  mdec_v64 v108;
  mdec_v64 v109;
  mdec_v64 v110;
  mdec_v64 v111;
  mdec_v64 v112;
  mdec_v64 v113;
  mdec_v64 v114;
  mdec_v64 v115;
  void *v116;
  mdec_v64 v117;
  mdec_v64 v118;
  void *v119;
  void *v120;
  mdec_v64 v121;
  mdec_v64 v122;
  mdec_v64 v123;
  mdec_v64 v124;
  mdec_v64 v125;
  mdec_v64 v126;
  mdec_v64 v127;
  mdec_v64 v128;
  mdec_v64 v129;
  mdec_v64 v130;
  mdec_v64 v131;
  mdec_v64 v132;
  mdec_v64 v133;
  mdec_v64 v134;
  mdec_v64 v135;
  mdec_v64 v136;
  mdec_v64 v137;
  mdec_v64 v138;
  mdec_v64 v139;
  mdec_v64 v140;
  mdec_v64 v141;
  mdec_v64 v142;
  mdec_v64 v143;
  mdec_v64 v144;
  mdec_v64 v145;
  mdec_v64 v146;
  mdec_v64 v147;
  mdec_v64 v148;
  mdec_v64 v149;
  mdec_v64 v150;
  mdec_v64 v151;
  mdec_v64 v152;
  mdec_v64 v153;
  mdec_v64 v154;
  mdec_v64 v155;
  mdec_v64 v156;
  mdec_v64 v157;
  mdec_v64 v158;
  mdec_v64 v159;
  mdec_v64 v160;
  mdec_v64 v161;
  mdec_v64 v162;
  mdec_v64 v163;
  mdec_v64 v164;
  mdec_v64 v165;
  mdec_v64 v166;
  mdec_v64 v167;
  mdec_v64 v168;
  mdec_v64 v169;
  mdec_v64 v170;
  mdec_v64 v171;
  mdec_v64 v172;
  mdec_v64 v173;
  mdec_v64 v174;
  mdec_v64 v175;
  mdec_v64 v176;
  mdec_v64 v177;
  mdec_v64 v178;
  mdec_v64 v179;
  mdec_v64 v180;
  mdec_v64 v181;
  mdec_v64 v182;
  mdec_v64 v183;
  void *v184;
  mdec_v64 v185;
  mdec_v64 v186;
  void *v187;
  void *v189;
  mdec_v64 v190;
  mdec_v64 v191;
  mdec_v64 v192;
  mdec_v64 v193;
  mdec_v64 v194;
  mdec_v64 v195;
  mdec_v64 v196;
  mdec_v64 v197;
  mdec_v64 v198;
  mdec_v64 v199;
  mdec_v64 v200;
  mdec_v64 v201;
  mdec_v64 v202;
  mdec_v64 v203;
  mdec_v64 v204;
  mdec_v64 v205;
  mdec_v64 v206;
  mdec_v64 v207;
  mdec_v64 v208;
  mdec_v64 v209;
  mdec_v64 v210;
  mdec_v64 v211;
  mdec_v64 v212;
  mdec_v64 v213;
  mdec_v64 v214;
  mdec_v64 v215;
  mdec_v64 v216;
  mdec_v64 v217;
  mdec_v64 v218;
  mdec_v64 v219;

  v2 = md_load4(a1 + 24);              /* a1[6] */
  v3 = md_load4(a1 + 40);              /* a1[10] */
  v4 = md_load4(a1 + 56);              /* a1[14] */
  v5 = md_paddw(v3, v2);
  v6 = md_psllwi(md_psubw(v3, v2), 2u);
  v7 = md_pmulhw(v6, md_from_int64(qword_455C28));
  v8 = md_load4(a1 + 8);               /* a1[2] */
  v9 = md_paddw(v8, v4);
  v10 = md_psubw(v9, v5);
  v11 = md_psllwi(md_psubw(v8, v4), 2u);
  v12 = md_load4(a1 + 48);             /* a1[12] */
  v13 = md_paddw(v9, v5);
  v14 = md_paddw(md_pmulhw(v6, md_from_int64(qword_455C38)), md_pmulhw(v11, md_from_int64(qword_455C40)));
  v15 = md_psubw(md_paddw(v7, md_pmulhw(v11, md_from_int64(qword_455C30))), v13);
  v16 = md_load4(a1 + 16);             /* a1[4] */
  v17 = md_psubw(md_pmulhw(md_psllwi(v10, 2u), md_from_int64(qword_455C20)), v15);
  v190 = md_paddw(v16, v12);
  v18 = md_pmulhw(md_psllwi(md_psubw(v16, v12), 2u), md_from_int64(qword_455C20));
  v19 = md_load4(a1 + 32);             /* a1[8] */
  v202 = md_paddw(v14, v17);
  v196 = md_psubw(v18, v190);
  v20 = md_psubw(md_load4(a1), v19);
  v21 = md_paddw(md_load4(a1), v19);
  v22 = md_paddw(v21, v190);
  v23 = md_psubw(v21, v190);
  v24 = md_psubw(v20, v196);
  v25 = md_psubw(v22, v13);
  v191 = md_paddw(v22, v13);
  v26 = md_paddw(v20, v196);
  v218 = v25;
  v197 = md_paddw(v26, v15);
  v216 = md_psubw(v26, v15);
  v208 = md_paddw(v23, v202);
  v206 = md_psubw(v23, v202);
  v203 = md_paddw(v24, v17);
  v212 = md_psubw(v24, v17);
  v27 = md_load4(a1 + 28);             /* a1[7] */
  v28 = md_load4(a1 + 44);             /* a1[11] */
  v29 = md_load4(a1 + 60);             /* a1[15] */
  v30 = md_paddw(v28, v27);
  v31 = md_psllwi(md_psubw(v28, v27), 2u);
  v32 = md_pmulhw(v31, md_from_int64(qword_455C28));
  v33 = md_load4(a1 + 12);             /* a1[3] */
  v34 = md_paddw(v33, v29);
  v35 = md_psubw(v34, v30);
  v36 = md_psllwi(md_psubw(v33, v29), 2u);
  v37 = md_load4(a1 + 52);             /* a1[13] */
  v38 = md_paddw(v34, v30);
  v39 = md_paddw(md_pmulhw(v31, md_from_int64(qword_455C38)), md_pmulhw(v36, md_from_int64(qword_455C40)));
  v40 = md_psubw(md_paddw(v32, md_pmulhw(v36, md_from_int64(qword_455C30))), v38);
  v41 = md_load4(a1 + 20);             /* a1[5] */
  v42 = md_psubw(md_pmulhw(md_psllwi(v35, 2u), md_from_int64(qword_455C20)), v40);
  v193 = md_paddw(v41, v37);
  v43 = md_load4(a1 + 4);              /* a1[1] */
  v44 = md_pmulhw(md_psllwi(md_psubw(v41, v37), 2u), md_from_int64(qword_455C20));
  v45 = md_load4(a1 + 36);             /* a1[9] */
  v204 = md_paddw(v39, v42);
  v199 = md_psubw(v44, v193);
  v46 = md_psubw(v43, v45);
  v47 = md_paddw(v43, v45);
  v48 = md_paddw(v47, v193);
  v49 = md_psubw(v47, v193);
  v50 = md_psubw(v46, v199);
  v51 = md_psubw(v48, v38);
  v194 = md_paddw(v48, v38);
  v52 = md_paddw(v46, v199);
  v219 = v51;
  v200 = md_paddw(v52, v40);
  v217 = md_psubw(v52, v40);
  v210 = md_paddw(v49, v204);
  v207 = md_psubw(v49, v204);
  v205 = md_paddw(v50, v42);
  v214 = md_psubw(v50, v42);
  v53 = md_psubw(v191, v194);
  v54 = md_paddw(v191, v194);
  v55 = md_paddw(v197, v200);
  v56 = md_psubw(v197, v200);
  v57 = md_punpckldq(md_punpcklwd(v54, v55), md_punpckhwd(v54, v55));
  v58 = md_punpckldq(md_punpcklwd(v53, v56), md_punpckhwd(v53, v56));
  v59 = md_paddw(v206, v207);
  v60 = md_paddw(v203, v205);
  v61 = md_psubw(v206, v207);
  v62 = md_psubw(v203, v205);
  v63 = md_punpckldq(md_punpcklwd(v60, v59), md_punpckhwd(v60, v59));
  v64 = md_punpckldq(md_punpcklwd(v62, v61), md_punpckhwd(v62, v61));
  v65 = md_punpckhdq(v57, v63);
  v66 = md_punpckldq(v57, v63);
  v67 = md_paddw(v66, v65);
  v68 = md_psubw(v66, v65);
  v69 = md_psubw(md_pmulhw(md_psllwi(md_punpckhdq(v58, v64), 2u), md_from_int64(qword_455C20)), v65);
  v70 = md_punpckldq(v58, v64);
  v71 = md_paddw(v70, v69);
  v72 = md_psubw(v70, v69);
  v73 = md_punpckldq(v191, v194);
  v74 = md_punpckhdq(v194, v191);
  v192 = v67;
  v75 = md_paddw(v73, v74);
  v76 = md_psubw(v73, v74);
  v195 = v71;
  v77 = md_punpckhdq(v200, v197);
  v78 = md_punpckldq(v197, v200);
  v79 = md_paddw(v78, v77);
  v198 = v72;
  v80 = md_psubw(v78, v77);
  v201 = v68;
  v81 = md_punpckhdq(md_punpckhwd(v76, v80), md_punpcklwd(v75, v79));
  v82 = md_punpckhdq(md_punpcklwd(v76, v80), md_punpckhwd(v75, v79));
  v83 = md_punpckhdq(v205, v203);
  v84 = md_punpckldq(v203, v205);
  v85 = md_paddw(v84, v83);
  v86 = md_psubw(v84, v83);
  v87 = md_punpckhdq(v207, v206);
  v88 = md_punpckldq(v206, v207);
  v89 = md_paddw(v88, v87);
  v90 = md_psubw(v88, v87);
  v91 = md_punpckhdq(md_punpckhwd(v86, v90), md_punpcklwd(v85, v89));
  v92 = md_punpckhdq(md_punpcklwd(v86, v90), md_punpckhwd(v85, v89));
  v93 = v81;
  v94 = md_punpckldq(v81, v91);
  v95 = md_punpckhdq(v93, v91);
  v96 = md_punpckhdq(v82, v92);
  v97 = md_psubw(v95, v96);
  v98 = md_paddw(v95, v96);
  v99 = md_psllwi(v94, 2u);
  v100 = md_psllwi(md_punpckldq(v82, v92), 2u);
  v101 = md_pmulhw(v99, md_from_int64(qword_455C38));
  v102 = md_pmulhw(v100, md_from_int64(qword_455C40));
  v103 = md_psubw(md_paddw(md_pmulhw(v100, md_from_int64(qword_455C30)), md_pmulhw(v99, md_from_int64(qword_455C28))), v98);
  v104 = md_psubw(md_pmulhw(md_psllwi(v97, 2u), md_from_int64(qword_455C20)), v103);
  v105 = md_packsswb(md_psrawi(md_paddw(v195, v103), 5u), md_psrawi(md_psubw(v192, v98), 5u));
  v106 = md_packsswb(md_psrawi(md_paddw(v192, v98), 5u), md_psrawi(md_psubw(v195, v103), 5u));
  v107 = md_paddw(md_paddw(v101, v102), v104);
  v108 = md_packsswb(md_psrawi(md_psubw(v201, v107), 5u), md_psrawi(md_psubw(v198, v104), 5u));
  v109 = md_packsswb(md_psrawi(md_paddw(v198, v104), 5u), md_psrawi(md_paddw(v201, v107), 5u));
  v110 = md_punpckhbw(v106, v105);
  v111 = md_punpcklbw(v106, v105);
  v112 = md_punpcklbw(v109, v108);
  v113 = md_punpckhbw(v109, v108);
  v114 = md_punpcklwd(v111, v112);
  v115 = md_punpcklwd(v113, v110);
  v116 = (void *)*(unsigned int *)(a2 + 4);       /* was *(__m64 **)(a2 + 4) */
  v117 = md_punpckhwd(v111, v112);
  v118 = md_punpckhwd(v113, v110);
  md_store8((void *)*(unsigned int *)a2, md_punpckldq(v114, v115));
  v119 = (void *)*(unsigned int *)(a2 + 8);       /* was *(__m64 **)(a2 + 8) */
  md_store8(v116, md_punpckhdq(v114, v115));
  v120 = (void *)*(unsigned int *)(a2 + 12);      /* was *(__m64 **)(a2 + 12) */
  md_store8(v119, md_punpckldq(v117, v118));
  md_store8(v120, md_punpckhdq(v117, v118));
  v121 = md_psubw(v208, v210);
  v122 = md_paddw(v208, v210);
  v123 = md_paddw(v212, v214);
  v124 = md_psubw(v212, v214);
  v125 = md_punpckldq(md_punpcklwd(v122, v123), md_punpckhwd(v122, v123));
  v126 = md_punpckldq(md_punpcklwd(v121, v124), md_punpckhwd(v121, v124));
  v127 = md_paddw(v218, v219);
  v128 = md_paddw(v216, v217);
  v129 = md_psubw(v218, v219);
  v130 = md_psubw(v216, v217);
  v131 = md_punpckldq(md_punpcklwd(v128, v127), md_punpckhwd(v128, v127));
  v132 = md_punpckldq(md_punpcklwd(v130, v129), md_punpckhwd(v130, v129));
  v133 = md_punpckhdq(v125, v131);
  v134 = md_punpckldq(v125, v131);
  v135 = md_paddw(v134, v133);
  v136 = md_psubw(v134, v133);
  v137 = md_psubw(md_pmulhw(md_psllwi(md_punpckhdq(v126, v132), 2u), md_from_int64(qword_455C20)), v133);
  v138 = md_punpckldq(v126, v132);
  v139 = md_paddw(v138, v137);
  v140 = md_psubw(v138, v137);
  v141 = md_punpckldq(v208, v210);
  v142 = md_punpckhdq(v210, v208);
  v209 = v135;
  v143 = md_paddw(v141, v142);
  v144 = md_psubw(v141, v142);
  v211 = v139;
  v145 = md_punpckhdq(v214, v212);
  v146 = md_punpckldq(v212, v214);
  v147 = md_paddw(v146, v145);
  v213 = v140;
  v148 = md_psubw(v146, v145);
  v215 = v136;
  v149 = md_punpckhdq(md_punpckhwd(v144, v148), md_punpcklwd(v143, v147));
  v150 = md_punpckhdq(md_punpcklwd(v144, v148), md_punpckhwd(v143, v147));
  v151 = md_punpckhdq(v217, v216);
  v152 = md_punpckldq(v216, v217);
  v153 = md_paddw(v152, v151);
  v154 = md_psubw(v152, v151);
  v155 = md_punpckhdq(v219, v218);
  v156 = md_punpckldq(v218, v219);
  v157 = md_paddw(v156, v155);
  v158 = md_psubw(v156, v155);
  v159 = md_punpckhdq(md_punpckhwd(v154, v158), md_punpcklwd(v153, v157));
  v160 = md_punpckhdq(md_punpcklwd(v154, v158), md_punpckhwd(v153, v157));
  v161 = v149;
  v162 = md_punpckldq(v149, v159);
  v163 = md_punpckhdq(v161, v159);
  v164 = md_punpckhdq(v150, v160);
  v165 = md_psubw(v163, v164);
  v166 = md_paddw(v163, v164);
  v167 = md_psllwi(v162, 2u);
  v168 = md_psllwi(md_punpckldq(v150, v160), 2u);
  v169 = md_pmulhw(v167, md_from_int64(qword_455C38));
  v170 = md_pmulhw(v168, md_from_int64(qword_455C40));
  v171 = md_psubw(md_paddw(md_pmulhw(v168, md_from_int64(qword_455C30)), md_pmulhw(v167, md_from_int64(qword_455C28))), v166);
  v172 = md_psubw(md_pmulhw(md_psllwi(v165, 2u), md_from_int64(qword_455C20)), v171);
  v173 = md_packsswb(md_psrawi(md_paddw(v211, v171), 5u), md_psrawi(md_psubw(v209, v166), 5u));
  v174 = md_packsswb(md_psrawi(md_paddw(v209, v166), 5u), md_psrawi(md_psubw(v211, v171), 5u));
  v175 = md_paddw(md_paddw(v169, v170), v172);
  v176 = md_packsswb(md_psrawi(md_psubw(v215, v175), 5u), md_psrawi(md_psubw(v213, v172), 5u));
  v177 = md_packsswb(md_psrawi(md_paddw(v213, v172), 5u), md_psrawi(md_paddw(v215, v175), 5u));
  v178 = md_punpckhbw(v174, v173);
  v179 = md_punpcklbw(v174, v173);
  v180 = md_punpcklbw(v177, v176);
  v181 = md_punpckhbw(v177, v176);
  v182 = md_punpcklwd(v179, v180);
  v183 = md_punpcklwd(v181, v178);
  v184 = (void *)*(unsigned int *)(a2 + 20);      /* was *(__m64 **)(a2 + 20) */
  v185 = md_punpckhwd(v179, v180);
  v186 = md_punpckhwd(v181, v178);
  md_store8((void *)*(unsigned int *)(a2 + 16), md_punpckldq(v182, v183));
  v187 = (void *)*(unsigned int *)(a2 + 24);      /* was *(__m64 **)(a2 + 24) */
  md_store8(v184, md_punpckhdq(v182, v183));
  v189 = (void *)*(unsigned int *)(a2 + 28);      /* was *(__m64 **)(a2 + 28) */
  md_store8(v187, md_punpckldq(v185, v186));
  md_store8(v189, md_punpckhdq(v185, v186));
}


static void mdec_y_to_mono(unsigned int *a1, unsigned char *a2, int a3)
{
  unsigned int *v3;
  unsigned int *v4;
  unsigned int *v5;
  unsigned int *v6;
  unsigned char *v7;
  unsigned char *v8;
  mdec_v64 v9;
  mdec_v64 v10;
  mdec_v64 v11;
  mdec_v64 v12;
  mdec_v64 v13;
  mdec_v64 v14;
  mdec_v64 v15;
  mdec_v64 v16;
  mdec_v64 v17;
  mdec_v64 v18;
  mdec_v64 v19;
  mdec_v64 v20;
  mdec_v64 v21;
  mdec_v64 v22;
  mdec_v64 v23;
  mdec_v64 v24;
  mdec_v64 v25;
  mdec_v64 v26;
  mdec_v64 v27;
  mdec_v64 v28;
  mdec_v64 v29;
  mdec_v64 v30;
  mdec_v64 v31;
  mdec_v64 v32;
  mdec_v64 v33;
  mdec_v64 v34;
  mdec_v64 v35;
  mdec_v64 v36;
  mdec_v64 v37;
  mdec_v64 v38;
  mdec_v64 v39;
  mdec_v64 v40;
  mdec_v64 v41;
  mdec_v64 v42;
  mdec_v64 v43;
  mdec_v64 v44;
  mdec_v64 v45;
  mdec_v64 v46;
  mdec_v64 v47;
  int v48;
  int v49;
  int v50;

  v3 = a1 + 32;
  v4 = a1 + 34;
  v5 = a1;
  v6 = a1 + 16;
  v7 = a2;
  v8 = a2 + 48;                       /* was a2 + 6 (__m64) */
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
          v9 = md_from_int(*v5);
          v10 = md_punpcklbw(v9, v9);
          v11 = md_punpcklwd(v10, v10);
          v12 = md_from_int(*v6);
          v13 = md_punpcklbw(v12, v12);
          v14 = md_punpcklwd(v13, v13);
          v15 = md_paddb(md_from_int(*v3), md_from_int64(qword_455C70));
          v16 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckldq(v11, v11), 6u), md_from_int64(qword_455C50)),
                  md_pmulhw(md_psrawi(md_punpckldq(v14, v14), 6u), md_from_int64(qword_455C58)));
          v17 = md_punpcklbw(v15, v15);
          v18 = md_punpcklwd(v17, v15);
          v19 = md_psrlqi(v17, 0x10u);
          v20 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckhdq(v11, v11), 6u), md_from_int64(qword_455C60)),
                  md_pmulhw(md_psrawi(md_punpckhdq(v14, v14), 6u), md_from_int64(qword_455C68)));
          v21 = md_por(
                  md_psrlqi(md_pand(v16, md_from_int64(qword_455C78)), 0x10u),
                  md_psllqi(md_pand(v20, md_from_int64(qword_455C78)), 0x10u));
          v22 = md_paddb(md_from_int(*v4), md_from_int64(qword_455C70));
          md_store8(v7, md_packuswb(
                          md_paddsw(md_punpcklbw(v18, md_from_int(mdec_mono_expand_value)), v16),
                          md_paddsw(md_punpcklbw(v19, md_from_int(mdec_mono_expand_value)), v21)));
          v23 = md_punpcklbw(v22, v22);
          v24 = md_punpcklbw(md_punpcklwd(v23, v22), md_from_int(mdec_mono_expand_value));
          v25 = md_psrlqi(v23, 0x10u);
          md_store8(v8, md_packuswb(
                          md_paddsw(v24, v16),
                          md_paddsw(
                            md_punpcklbw(md_punpckldq(v25, v25), md_from_int(mdec_mono_expand_value)),
                            v21)));
          v26 = md_psrlqi(md_from_int(*v5), 0x10u);
          v27 = md_paddsw(
                  md_punpcklbw(
                    md_punpcklwd(md_psrlqi(v19, 0x18u), md_psrlqi(v19, 0x20u)),
                    md_from_int(mdec_mono_expand_value)),
                  v20);
          v28 = md_punpcklbw(v26, v26);
          v29 = md_paddsw(
                  md_punpcklbw(
                    md_punpcklwd(md_psrlqi(v25, 0x18u), md_psrlqi(v25, 0x20u)),
                    md_from_int(mdec_mono_expand_value)),
                  v20);
          v30 = md_punpcklwd(v28, v28);
          v31 = md_psrlqi(md_from_int(*v6), 0x10u);
          v32 = md_punpcklbw(v31, v31);
          v33 = md_punpcklwd(v32, v32);
          v34 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckldq(v30, v30), 6u), md_from_int64(qword_455C50)),
                  md_pmulhw(md_psrawi(md_punpckldq(v33, v33), 6u), md_from_int64(qword_455C58)));
          v35 = md_paddb(md_from_int(v3[1]), md_from_int64(qword_455C70));
          v36 = md_psrlqi(md_pand(v34, md_from_int64(qword_455C78)), 0x10u);
          v37 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckhdq(v30, v30), 6u), md_from_int64(qword_455C60)),
                  md_pmulhw(md_psrawi(md_punpckhdq(v33, v33), 6u), md_from_int64(qword_455C68)));
          v38 = md_paddb(md_from_int(v4[1]), md_from_int64(qword_455C70));
          v39 = md_psllqi(md_pand(v37, md_from_int64(qword_455C78)), 0x10u);
          md_store8(v7 + 8, md_packuswb(
                              v27,
                              md_paddsw(
                                md_punpcklbw(
                                  md_punpcklwd(md_punpcklbw(v35, v35), v35),
                                  md_from_int(mdec_mono_expand_value)),
                                v34)));
          v40 = md_por(v36, v39);
          v41 = v38;
          v42 = md_paddsw(md_punpcklbw(md_punpcklwd(md_punpcklbw(v38, v38), v38), md_from_int(0)), v34);
          v43 = md_psrlqi(v41, 8u);
          md_store8(v8 + 8, md_packuswb(v29, v42));
          v44 = md_psrlqi(v35, 8u);
          v45 = md_psrlqi(v44, 8u);
          v3 += 4;
          v4 += 4;
          v46 = md_psrlqi(v43, 8u);
          v7 += 96;                   /* was v7 += 12 (__m64) */
          v8 += 96;
          v5 += 2;
          v47 = md_paddsw(
                  md_punpcklbw(
                    md_punpcklwd(v46, md_psrlqi(md_punpcklbw(v46, v46), 0x10u)),
                    md_from_int(mdec_mono_expand_value)),
                  v37);
          md_store8(v7 - 80, md_packuswb(        /* was v7[-10] */
                                            md_paddsw(md_punpcklbw(md_punpcklbw(v44, v44), md_from_int(0)), v40),
                                            md_paddsw(
                                              md_punpcklbw(
                                                md_punpcklwd(v45, md_psrlqi(md_punpcklbw(v45, v45), 0x10u)),
                                                md_from_int(mdec_mono_expand_value)),
                                              v37)));
          v6 += 2;
          md_store8(v8 - 80, md_packuswb(md_paddsw(md_punpcklbw(md_punpcklbw(v43, v43), md_from_int(0)), v40), v47));  /* was v8[-10] */
          --v50;
        }
        while ( v50 );
        v5 -= 7;
        v6 -= 7;
        v7 -= 360;                  /* was v7 -= 45 (__m64) */
        v8 -= 360;
        --v49;
      }
      while ( v49 );
      v5 += 6;
      v6 += 6;
      v7 += 336;                    /* was v7 += 42 (__m64) */
      v8 += 336;
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
uint64_t qword_455C20 = 0x5a825a825a825a82;
uint64_t qword_455C28 = 0xcf04cf04cf04cf04;
uint64_t qword_455C30 = 0x7641764176417641;
uint64_t qword_455C38 = 0x896f896f896f896f;
uint64_t qword_455C40 = 0xcf04cf04cf04cf04;
uint64_t qword_455C50 = 0x59ba0000d24e59ba;
uint64_t qword_455C58 = 0x7168ea0c0000;
uint64_t qword_455C60 = 0xd24e59ba0000;
uint64_t qword_455C68 = 0x7168ea0c00007168;
uint64_t qword_455C70 = 0x80808080;
uint64_t qword_455C78 = 0xffffffff0000;
