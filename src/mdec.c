#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static unsigned char mdec_coeff_buffer[0x5a00];
static unsigned int mdec_mono_expand_value;
static unsigned short mdec_bit15_flag;
static unsigned char mdec_color_lookup[0x80];
static unsigned int mdec_color_table_0[0x80];
static unsigned int mdec_color_table_1[0x80];
static unsigned int mdec_color_table_2[0x80];
static unsigned int mdec_color_table_3[0x80];
static unsigned int mdec_color_table_4[0x80];
static unsigned int mdec_color_table_5[0x80];
static unsigned int mdec_color_table_6[0x80];
static unsigned int mdec_color_table_7[0x80];
static unsigned int mdec_command;
static unsigned int mdec_dma_dest;
static unsigned int mdec_idct_buffer[0xb40];
static unsigned char mdec_idct_buffer_end[0x1680];
static unsigned int mdec_image_size;
static unsigned int mdec_in_ptr;
static unsigned char mdec_mono_table_0[0x100];
static unsigned char mdec_mono_table_1[0x80];
static unsigned char mdec_mono_table_2[0x100];
static unsigned int mdec_nonzero_counts[0xb8];
static unsigned int mdec_out_addr;
static unsigned int mdec_param_word;
static unsigned int mdec_scale_table[0x20];
unsigned int mdec_status;
static unsigned char mdec_timer;
unsigned int mdec_timer_count;
static unsigned int mdec_zigzag[13] = {0x0, 0x1, 0x8, 0x10, 0x9, 0x2, 0x3, 0xa, 0x11, 0x18, 0x20, 0x19, 0x12};
static uint64_t qword_455C20 = 0x5a825a825a825a82;
static uint64_t qword_455C28 = 0xcf04cf04cf04cf04;
static uint64_t qword_455C30 = 0x7641764176417641;
static uint64_t qword_455C38 = 0x896f896f896f896f;
static uint64_t qword_455C40 = 0xcf04cf04cf04cf04;
static uint64_t qword_455C50 = 0x59ba0000d24e59ba;
static uint64_t qword_455C58 = 0x7168ea0c0000;
static uint64_t qword_455C60 = 0xd24e59ba0000;
static uint64_t qword_455C68 = 0x7168ea0c00007168;
static uint64_t qword_455C70 = 0x80808080;
static uint64_t qword_455C78 = 0xffffffff0000;


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
static int mdec_set_scale_table(int quant);
static char * mdec_rl_decode(char *data, int blocks);
static void mdec_idct_blocks(int blocks);
static int mdec_init_color_tables();
static uint16_t * mdec_yuv_to_rgb(char *src, uint16_t *dst, uint16_t *blocks);
static void mdec_idct_sse(const unsigned short *coeff, int dst_rows);
static void mdec_y_to_mono(unsigned int *src, unsigned char *dst, int blocks);

static char *mdec_init_pointers()
{
  char *dst;
  char *src;

  dst = mdec_idct_buffer_end;
  src = (char *)mdec_idct_buffer;
  do
  {
    *(uint32_t *)dst = src;
    src += 8;
    dst += 4;
  }
  while ( (int)src < (int)mdec_idct_buffer_end );
  return src;
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

int16_t mdec_write_command(unsigned int command)
{
  int16_t bit15;

  *(uint32_t *)mdec_command = command;
  if ( (command & 0xF5FF0000) == 0x30000000 )
    mdec_param_word = (uint16_t)command;
  bit15 = (command >> 10) & 0x8000;
  mdec_bit15_flag = bit15;
  return bit15;
}

int mdec_handle_special_command(int command)
{
  int result;

  if ( command == 0x80000000 )
  {
    mdec_in_ptr = mdec_out_addr;
    return mdec_out_addr;
  }
  return result;
}

char mdec_timer_handler()
{
  char timer_value;

  timer_value = mdectiming;
  if ( mdectiming )
  {
    timer_value = mdec_timer;
    if ( mdec_timer <= 0 )
    {
      if ( !mdec_timer )
      {
        mdec_status = 0;
        mdec_dma_status &= ~0x1000000u;
        mdec_timer = -1;
        irq_dma_assert_int(1u);
        timer_value = mdec_timer;
      }
    }
    else
    {
      timer_value = --mdec_timer;
    }
    if ( timer_value < 0 )
    {
      if ( timer_value <= -10 )
        mdec_timer_count = 0;
      else
        mdec_timer = --timer_value;
    }
  }
  return timer_value;
}

void mdec_dma_in_handler()
{
  int src;
  int command;

  src = mdec_dma_src[0];
  if ( mdec_dma_control[0] == 0x1000201 )
  {
    if ( mdec_disable )
      LOBYTE(mdec_disable_flag[0]) = 1;
    command = *(uint32_t *)mdec_command;
    if ( *(uint32_t *)mdec_command == 0x40000001 )
    {
      mdec_set_scale_table((int)ram + (mdec_dma_src[0] & 0x1FFFFF));
      command = *(uint32_t *)mdec_command;
    }
    if ( (command & 0xF5FF0000) == 0x30000000 )
    {
      mdec_in_ptr = (int)ram + (src & 0x1FFFFF);
      mdec_out_addr = (int)ram + (src & 0x1FFFFF);
    }
  }
}

int mdec_decode()
{
  int pixels;
  char *src;
  unsigned char *dst;
  int color_mode;
  int frame_bytes;
  int blocks;
  int groups;
  bool no_groups;
  int remaining;

  pixels = HIWORD(mdec_image_size) * (uint16_t)mdec_image_size;
  if ( mdec_dma_status == 0x1000200 )
  {
    src = (char *)mdec_in_ptr;
    if ( mdec_in_ptr )
    {
      if ( mdec_disable )
      {
        LOBYTE(mdec_disable_flag[0]) = 1;
        return pixels;
      }
      dst = (unsigned char *)ram + (mdec_dma_dest & 0x1FFFFF);
      color_mode = *(uint32_t *)mdec_command & 0x8000000;
      frame_bytes = 3 * pixels;
      if ( (*(uint32_t *)mdec_command & 0x8000000) == 0 )
        frame_bytes = 2 * pixels;
      blocks = frame_bytes / 384;
      if ( frame_bytes / 384 < 31 )
        goto LABEL_15;
      groups = blocks / 30;
      no_groups = blocks / 30 <= 0;
      blocks %= 30;
      if ( !no_groups )
      {
        remaining = groups;
        do
        {
          mdec_in_ptr = (int)mdec_rl_decode(src, 30);
          mdec_idct_blocks(30);
          if ( color_mode )
          {
            mdec_yuv_to_rgb((char *)mdec_idct_buffer, (uint16_t *)dst, (uint16_t *)0x1E);
            dst += 15360;
          }
          else
          {
            mdec_y_to_mono((unsigned int *)mdec_idct_buffer, dst, 30);
            dst += 23040;
          }
          src = (char *)mdec_in_ptr;
          --remaining;
        }
        while ( remaining );
      }
      if ( blocks )
      {
LABEL_15:
        mdec_in_ptr = (int)mdec_rl_decode(src, blocks);
        mdec_idct_blocks(blocks);
        if ( color_mode )
          mdec_yuv_to_rgb((char *)mdec_idct_buffer, (uint16_t *)dst, (uint16_t *)blocks);
        else
          mdec_y_to_mono((unsigned int *)mdec_idct_buffer, dst, blocks);
      }
    }
    pixels = mdectiming;
    if ( mdectiming )
    {
      mdec_status = 0x44000000;
      mdec_timer_count = -65536;
      mdec_timer = 1;
    }
  }
  return pixels;
}

static int mdec_set_scale_table(int quant)
{
  int index;
  int16_t *dst;
  int zigzag_idx;
  uint32_t zigzag_order[63];
  uint32_t scale[65];

  scale[4] = 19266;
  scale[6] = 12873;
  scale[7] = 8867;
  scale[8] = 4520;
  scale[25] = 19266;
  scale[29] = 19266;
  scale[36] = 19266;
  scale[38] = 12873;
  scale[39] = 8867;
  scale[40] = 4520;
  scale[41] = 12873;
  scale[45] = 12873;
  scale[49] = 8867;
  scale[53] = 8867;
  scale[57] = 4520;
  scale[61] = 4520;
  index = 0;
  scale[1] = 0x4000;
  scale[2] = 22725;
  scale[3] = 21407;
  scale[5] = 0x4000;
  scale[9] = 22725;
  scale[10] = 31521;
  scale[11] = 29692;
  scale[12] = 26722;
  scale[13] = 22725;
  scale[14] = 17855;
  scale[15] = 12299;
  scale[16] = 6270;
  scale[17] = 21407;
  scale[18] = 29692;
  scale[19] = 27969;
  scale[20] = 25172;
  scale[21] = 21407;
  scale[22] = 16819;
  scale[23] = 11585;
  scale[24] = 5906;
  scale[26] = 26722;
  scale[27] = 25172;
  scale[28] = 22654;
  scale[30] = 15137;
  scale[31] = 10426;
  scale[32] = 5315;
  scale[33] = 0x4000;
  scale[34] = 22725;
  scale[35] = 21407;
  scale[37] = 0x4000;
  scale[42] = 17855;
  scale[43] = 16819;
  scale[44] = 15137;
  scale[46] = 10114;
  scale[47] = 6967;
  scale[48] = 3552;
  scale[50] = 12299;
  scale[51] = 11585;
  scale[52] = 10426;
  scale[54] = 6967;
  scale[55] = 4799;
  scale[56] = 2446;
  scale[58] = 6270;
  scale[59] = 5906;
  scale[60] = 5315;
  scale[62] = 3552;
  scale[63] = 2446;
  scale[64] = 1247;
  zigzag_order[0] = 0;
  zigzag_order[1] = 1;
  zigzag_order[2] = 5;
  zigzag_order[3] = 6;
  zigzag_order[4] = 14;
  zigzag_order[5] = 15;
  zigzag_order[6] = 27;
  zigzag_order[7] = 28;
  zigzag_order[8] = 2;
  zigzag_order[9] = 4;
  zigzag_order[10] = 7;
  zigzag_order[11] = 13;
  zigzag_order[12] = 16;
  zigzag_order[13] = 26;
  zigzag_order[14] = 29;
  zigzag_order[15] = 42;
  zigzag_order[16] = 3;
  zigzag_order[17] = 8;
  zigzag_order[18] = 12;
  zigzag_order[19] = 17;
  zigzag_order[20] = 25;
  zigzag_order[21] = 30;
  zigzag_order[22] = 41;
  zigzag_order[23] = 43;
  zigzag_order[24] = 9;
  zigzag_order[25] = 11;
  zigzag_order[26] = 18;
  zigzag_order[27] = 24;
  zigzag_order[28] = 31;
  zigzag_order[29] = 40;
  zigzag_order[30] = 44;
  zigzag_order[31] = 53;
  zigzag_order[32] = 10;
  zigzag_order[33] = 19;
  zigzag_order[34] = 23;
  zigzag_order[35] = 32;
  zigzag_order[36] = 39;
  zigzag_order[37] = 45;
  zigzag_order[38] = 52;
  zigzag_order[39] = 54;
  zigzag_order[40] = 20;
  zigzag_order[41] = 22;
  zigzag_order[42] = 33;
  zigzag_order[43] = 38;
  zigzag_order[44] = 46;
  zigzag_order[45] = 51;
  zigzag_order[46] = 55;
  zigzag_order[47] = 60;
  zigzag_order[48] = 21;
  zigzag_order[49] = 34;
  zigzag_order[50] = 37;
  zigzag_order[51] = 47;
  zigzag_order[52] = 50;
  zigzag_order[53] = 56;
  zigzag_order[54] = 59;
  zigzag_order[55] = 61;
  zigzag_order[56] = 35;
  zigzag_order[57] = 36;
  zigzag_order[58] = 48;
  zigzag_order[59] = 49;
  zigzag_order[60] = 57;
  zigzag_order[61] = 58;
  zigzag_order[62] = 62;
  scale[0] = 63;
  dst = mdec_scale_table;
  do
  {
    zigzag_idx = zigzag_order[index];
    *dst++ = (scale[++index] * *(uint8_t *)(zigzag_idx + quant) + 2048) >> 12;
  }
  while ( (int)dst < (int)mdec_idct_buffer );
  return index * 4;
}

static char * mdec_rl_decode(char *data, int blocks)
{
  int block_count;
  char *src;
  uint16_t header;
  int coeff_count;
  uint16_t rl;
  uint16_t *dst;
  int block_idx;

  dst = (uint16_t *)mdec_coeff_buffer;
  memset(mdec_coeff_buffer, 0, 4 * ((unsigned int)(768 * blocks) >> 2));
  block_count = 6 * blocks;
  block_idx = 0;
  if ( block_count <= 0 )
    return data;
  src = data;
  do
  {
    if ( src - (char *)ram >= 0x1FFF00 )
      break;
    header = *(uint16_t *)src;
    coeff_count = 0;
    src += 4;
    *dst = mdec_scale_table[0] * ((int16_t)(header << 6) >> 6);
    for ( rl = *((uint16_t *)src - 1); rl != 0xFE00; src += 2 )
    {
      coeff_count += (rl >> 10) + 1;
      if ( coeff_count > 63 )
        break;
      dst[mdec_zigzag[coeff_count]] = (header >> 10) * (rl << 22 >> 22) * mdec_scale_table[mdec_zigzag[coeff_count]] / 8;
      rl = *(uint16_t *)src;
    }
    mdec_nonzero_counts[block_idx] = coeff_count;
    dst += 64;
    ++block_idx;
  }
  while ( block_idx < block_count );
  return src;
}

static void mdec_idct_blocks(int blocks)
{
  int *dst;
  int index;
  const unsigned short *coeff;
  int dc;
  int pattern;
  char *out;
  int *base;

  dst = mdec_idct_buffer;
  index = 0;
  out = mdec_idct_buffer_end;
  base = mdec_idct_buffer;
  for ( coeff = (const unsigned short *)mdec_coeff_buffer; index < 6 * blocks; out += 32 )
  {
    if ( mdec_nonzero_counts[index] )
    {
      mdec_idct_sse(coeff, (int)out);
    }
    else
    {
      dc = (int)coeff[0] >> 5;
      BYTE1(dc) = dc;
      pattern = dc << 16;
      LOWORD(pattern) = dc;
      memset32(dst, pattern, 0x10u);
    }
    dst = base + 16;
    coeff += 64;
    ++index;
    base += 16;
  }
}

static int mdec_init_color_tables()
{
  int b;
  int g_v;
  int g_u;
  int r;
  int index;
  int b2;
  int r2;
  int g_v2;
  int g_u2;
  int index2;
  int i;

  b = 0;
  g_v = 0;
  g_u = 0;
  r = 0;
  index = 0;
  do
  {
    mdec_color_table_0[index] = r >> 12;
    mdec_color_table_1[index] = g_u >> 12;
    mdec_color_table_2[index] = g_v >> 12;
    mdec_color_table_3[index] = b >> 12;
    r += 5743;
    g_u -= 1408;
    g_v -= 2925;
    b += 7258;
    ++index;
  }
  while ( r < 735104 );
  b2 = -929024;
  r2 = -735104;
  g_v2 = 374400;
  g_u2 = 180224;
  index2 = 0;
  do
  {
    mdec_color_table_4[index2] = r2 >> 12;
    mdec_color_table_5[index2] = g_u2 >> 12;
    mdec_color_table_6[index2] = g_v2 >> 12;
    mdec_color_table_7[index2] = b2 >> 12;
    g_u2 -= 1408;
    r2 += 5743;
    b2 += 7258;
    g_v2 -= 2925;
    ++index2;
  }
  while ( g_u2 > 0 );
  for ( i = 0; i < 256; ++i )
  {
    mdec_mono_table_0[i] = 0;
    mdec_mono_table_1[i] = i;
    mdec_mono_table_2[i] = -1;
  }
  return i;
}

static uint16_t * mdec_yuv_to_rgb(char *src, uint16_t *dst, uint16_t *blocks)
{
  uint16_t *out;
  char *y;
  char *cb;
  char *cr;
  int next_row;
  int y1;
  int y0;
  int r_off;
  int y3;
  int y2;
  int r2_off;
  int cr3;
  bool last;
  bool more;
  int pixels;
  int row;
  uint16_t *remaining;
  int g_off;
  int g2_off;
  int b_off;
  int b2_off;

  out = blocks;
  y = src;
  cb = src + 128;
  cr = src + 192;
  if ( (int)blocks > 0 )
  {
    remaining = blocks;
    out = dst;
    do
    {
      next_row = 0;
      row = 0;
      do
      {
        if ( next_row == 4 )
        {
          cb += 64;
          cr += 64;
        }
        pixels = 4;
        do
        {
          y1 = y[64];
          y0 = *y;
          g_off = ((-1408 * y0) >> 12) + ((-2925 * y1) >> 12);
          b_off = (7258 * y0) >> 12;
          r_off = (5743 * y1) >> 12;
          *out = mdec_bit15_flag
                  | ((uint8_t)mdec_color_lookup[*cb + b_off] >> 3)
                  | (4 * (mdec_color_lookup[*cb + g_off] & 0xF8 | (32 * (mdec_color_lookup[*cb + r_off] & 0xF8))));
          out[1] = mdec_bit15_flag
                    | ((uint8_t)mdec_color_lookup[cb[1] + b_off] >> 3)
                    | (4 * (mdec_color_lookup[cb[1] + g_off] & 0xF8 | (32 * (mdec_color_lookup[cb[1] + r_off] & 0xF8))));
          out[16] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[cb[8] + b_off] >> 3)
                     | (4 * (mdec_color_lookup[cb[8] + g_off] & 0xF8 | (32 * (mdec_color_lookup[cb[8] + r_off] & 0xF8))));
          out[17] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[cb[9] + b_off] >> 3)
                     | (4 * (mdec_color_lookup[cb[9] + g_off] & 0xF8 | (32 * (mdec_color_lookup[cb[9] + r_off] & 0xF8))));
          y3 = src[68];
          y2 = src[4];
          g2_off = ((-1408 * y2) >> 12) + ((-2925 * y3) >> 12);
          b2_off = (7258 * y2) >> 12;
          r2_off = (5743 * y3) >> 12;
          out[8] = mdec_bit15_flag
                    | ((uint8_t)mdec_color_lookup[*cr + b2_off] >> 3)
                    | (4 * (mdec_color_lookup[*cr + g2_off] & 0xF8 | (32 * (mdec_color_lookup[*cr + r2_off] & 0xF8))));
          out[9] = mdec_bit15_flag
                    | ((uint8_t)mdec_color_lookup[cr[1] + b2_off] >> 3)
                    | (4 * (mdec_color_lookup[cr[1] + g2_off] & 0xF8 | (32 * (mdec_color_lookup[cr[1] + r2_off] & 0xF8))));
          out[24] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[cr[8] + b2_off] >> 3)
                     | (4 * (mdec_color_lookup[cr[8] + g2_off] & 0xF8 | (32 * (mdec_color_lookup[cr[8] + r2_off] & 0xF8))));
          cr3 = cr[9];
          cb += 2;
          cr += 2;
          out += 2;
          out[23] = mdec_bit15_flag
                     | ((uint8_t)mdec_color_lookup[cr3 + b2_off] >> 3)
                     | (4 * (mdec_color_lookup[cr3 + g2_off] & 0xF8 | (32 * (mdec_color_lookup[cr3 + r2_off] & 0xF8))));
          y = src + 1;
          last = pixels == 1;
          ++src;
          --pixels;
        }
        while ( !last );
        next_row = row + 1;
        y += 4;
        cb += 8;
        cr += 8;
        out += 24;
        more = ++row < 8;
        src = y;
      }
      while ( more );
      y += 320;
      cb += 192;
      cr += 192;
      last = remaining == (uint16_t *)1;
      src = y;
      remaining = (uint16_t *)((char *)remaining - 1);
    }
    while ( !last );
  }
  return out;
}

int mdec_freeze(const char *filename, int file)
{
  char Buffer[3];
  uint8_t zeros[1024];

  memset(zeros, 0, sizeof(zeros));
  sprintf(Buffer, "%s", filename);
  gzwrite(file, (uint8_t *)Buffer, 7u);
  gzwrite(file, (uint8_t *)mdec_command, 0x60u);
  gzwrite(file, (uint8_t *)mdec_scale_table, 0x80u);
  return gzwrite(file, zeros, 0x400u);
}

int mdec_freeze2(const char *filename, int file)
{
  char Buffer[3];

  sprintf(Buffer, "%s", filename);
  gzwrite(file, (uint8_t *)Buffer, 7u);
  return gzwrite(file, (uint8_t *)mdec_command, 0x60u);
}

int mdec_unfreeze(int unused, uint32_t *file)
{
  char magic[64];
  char data[1024];

  gzread(file, magic, 7);
  gzread(file, mdec_command, 96);
  gzread(file, (char *)mdec_scale_table, 128);
  return gzread(file, data, 1024);
}

int mdec_unfreeze2(int unused, uint32_t *file)
{
  char magic[64];

  gzread(file, magic, 7);
  return gzread(file, mdec_command, 96);
}

static void mdec_idct_sse(const unsigned short *coeff, int dst_rows)
{
  mdec_v64 t2;
  mdec_v64 t3;
  mdec_v64 t4;
  mdec_v64 t5;
  mdec_v64 t6;
  mdec_v64 t7;
  mdec_v64 t8;
  mdec_v64 t9;
  mdec_v64 t10;
  mdec_v64 t11;
  mdec_v64 t12;
  mdec_v64 t13;
  mdec_v64 t14;
  mdec_v64 t15;
  mdec_v64 t16;
  mdec_v64 t17;
  mdec_v64 t18;
  mdec_v64 t19;
  mdec_v64 t20;
  mdec_v64 t21;
  mdec_v64 t22;
  mdec_v64 t23;
  mdec_v64 t24;
  mdec_v64 t25;
  mdec_v64 t26;
  mdec_v64 t27;
  mdec_v64 t28;
  mdec_v64 t29;
  mdec_v64 t30;
  mdec_v64 t31;
  mdec_v64 t32;
  mdec_v64 t33;
  mdec_v64 t34;
  mdec_v64 t35;
  mdec_v64 t36;
  mdec_v64 t37;
  mdec_v64 t38;
  mdec_v64 t39;
  mdec_v64 t40;
  mdec_v64 t41;
  mdec_v64 t42;
  mdec_v64 t43;
  mdec_v64 t44;
  mdec_v64 t45;
  mdec_v64 t46;
  mdec_v64 t47;
  mdec_v64 t48;
  mdec_v64 t49;
  mdec_v64 t50;
  mdec_v64 t51;
  mdec_v64 t52;
  mdec_v64 t53;
  mdec_v64 t54;
  mdec_v64 t55;
  mdec_v64 t56;
  mdec_v64 t57;
  mdec_v64 t58;
  mdec_v64 t59;
  mdec_v64 t60;
  mdec_v64 t61;
  mdec_v64 t62;
  mdec_v64 t63;
  mdec_v64 t64;
  mdec_v64 t65;
  mdec_v64 t66;
  mdec_v64 t67;
  mdec_v64 t68;
  mdec_v64 t69;
  mdec_v64 t70;
  mdec_v64 t71;
  mdec_v64 t72;
  mdec_v64 t73;
  mdec_v64 t74;
  mdec_v64 t75;
  mdec_v64 t76;
  mdec_v64 t77;
  mdec_v64 t78;
  mdec_v64 t79;
  mdec_v64 t80;
  mdec_v64 t81;
  mdec_v64 t82;
  mdec_v64 t83;
  mdec_v64 t84;
  mdec_v64 t85;
  mdec_v64 t86;
  mdec_v64 t87;
  mdec_v64 t88;
  mdec_v64 t89;
  mdec_v64 t90;
  mdec_v64 t91;
  mdec_v64 t92;
  mdec_v64 t93;
  mdec_v64 t94;
  mdec_v64 t95;
  mdec_v64 t96;
  mdec_v64 t97;
  mdec_v64 t98;
  mdec_v64 t99;
  mdec_v64 t100;
  mdec_v64 t101;
  mdec_v64 t102;
  mdec_v64 t103;
  mdec_v64 t104;
  mdec_v64 t105;
  mdec_v64 t106;
  mdec_v64 t107;
  mdec_v64 t108;
  mdec_v64 t109;
  mdec_v64 t110;
  mdec_v64 t111;
  mdec_v64 t112;
  mdec_v64 t113;
  mdec_v64 t114;
  mdec_v64 t115;
  void *dst1;
  mdec_v64 t117;
  mdec_v64 t118;
  void *dst2;
  void *dst3;
  mdec_v64 t121;
  mdec_v64 t122;
  mdec_v64 t123;
  mdec_v64 t124;
  mdec_v64 t125;
  mdec_v64 t126;
  mdec_v64 t127;
  mdec_v64 t128;
  mdec_v64 t129;
  mdec_v64 t130;
  mdec_v64 t131;
  mdec_v64 t132;
  mdec_v64 t133;
  mdec_v64 t134;
  mdec_v64 t135;
  mdec_v64 t136;
  mdec_v64 t137;
  mdec_v64 t138;
  mdec_v64 t139;
  mdec_v64 t140;
  mdec_v64 t141;
  mdec_v64 t142;
  mdec_v64 t143;
  mdec_v64 t144;
  mdec_v64 t145;
  mdec_v64 t146;
  mdec_v64 t147;
  mdec_v64 t148;
  mdec_v64 t149;
  mdec_v64 t150;
  mdec_v64 t151;
  mdec_v64 t152;
  mdec_v64 t153;
  mdec_v64 t154;
  mdec_v64 t155;
  mdec_v64 t156;
  mdec_v64 t157;
  mdec_v64 t158;
  mdec_v64 t159;
  mdec_v64 t160;
  mdec_v64 t161;
  mdec_v64 t162;
  mdec_v64 t163;
  mdec_v64 t164;
  mdec_v64 t165;
  mdec_v64 t166;
  mdec_v64 t167;
  mdec_v64 t168;
  mdec_v64 t169;
  mdec_v64 t170;
  mdec_v64 t171;
  mdec_v64 t172;
  mdec_v64 t173;
  mdec_v64 t174;
  mdec_v64 t175;
  mdec_v64 t176;
  mdec_v64 t177;
  mdec_v64 t178;
  mdec_v64 t179;
  mdec_v64 t180;
  mdec_v64 t181;
  mdec_v64 t182;
  mdec_v64 t183;
  void *dst4;
  mdec_v64 t185;
  mdec_v64 t186;
  void *dst5;
  void *dst6;
  mdec_v64 t190;
  mdec_v64 t191;
  mdec_v64 t192;
  mdec_v64 t193;
  mdec_v64 t194;
  mdec_v64 t195;
  mdec_v64 t196;
  mdec_v64 t197;
  mdec_v64 t198;
  mdec_v64 t199;
  mdec_v64 t200;
  mdec_v64 t201;
  mdec_v64 t202;
  mdec_v64 t203;
  mdec_v64 t204;
  mdec_v64 t205;
  mdec_v64 t206;
  mdec_v64 t207;
  mdec_v64 t208;
  mdec_v64 t209;
  mdec_v64 t210;
  mdec_v64 t211;
  mdec_v64 t212;
  mdec_v64 t213;
  mdec_v64 t214;
  mdec_v64 t215;
  mdec_v64 t216;
  mdec_v64 t217;
  mdec_v64 t218;
  mdec_v64 t219;

  t2 = md_load4(coeff + 24);              /* a1[6] */
  t3 = md_load4(coeff + 40);              /* a1[10] */
  t4 = md_load4(coeff + 56);              /* a1[14] */
  t5 = md_paddw(t3, t2);
  t6 = md_psllwi(md_psubw(t3, t2), 2u);
  t7 = md_pmulhw(t6, md_from_int64(qword_455C28));
  t8 = md_load4(coeff + 8);               /* a1[2] */
  t9 = md_paddw(t8, t4);
  t10 = md_psubw(t9, t5);
  t11 = md_psllwi(md_psubw(t8, t4), 2u);
  t12 = md_load4(coeff + 48);             /* a1[12] */
  t13 = md_paddw(t9, t5);
  t14 = md_paddw(md_pmulhw(t6, md_from_int64(qword_455C38)), md_pmulhw(t11, md_from_int64(qword_455C40)));
  t15 = md_psubw(md_paddw(t7, md_pmulhw(t11, md_from_int64(qword_455C30))), t13);
  t16 = md_load4(coeff + 16);             /* a1[4] */
  t17 = md_psubw(md_pmulhw(md_psllwi(t10, 2u), md_from_int64(qword_455C20)), t15);
  t190 = md_paddw(t16, t12);
  t18 = md_pmulhw(md_psllwi(md_psubw(t16, t12), 2u), md_from_int64(qword_455C20));
  t19 = md_load4(coeff + 32);             /* a1[8] */
  t202 = md_paddw(t14, t17);
  t196 = md_psubw(t18, t190);
  t20 = md_psubw(md_load4(coeff), t19);
  t21 = md_paddw(md_load4(coeff), t19);
  t22 = md_paddw(t21, t190);
  t23 = md_psubw(t21, t190);
  t24 = md_psubw(t20, t196);
  t25 = md_psubw(t22, t13);
  t191 = md_paddw(t22, t13);
  t26 = md_paddw(t20, t196);
  t218 = t25;
  t197 = md_paddw(t26, t15);
  t216 = md_psubw(t26, t15);
  t208 = md_paddw(t23, t202);
  t206 = md_psubw(t23, t202);
  t203 = md_paddw(t24, t17);
  t212 = md_psubw(t24, t17);
  t27 = md_load4(coeff + 28);             /* a1[7] */
  t28 = md_load4(coeff + 44);             /* a1[11] */
  t29 = md_load4(coeff + 60);             /* a1[15] */
  t30 = md_paddw(t28, t27);
  t31 = md_psllwi(md_psubw(t28, t27), 2u);
  t32 = md_pmulhw(t31, md_from_int64(qword_455C28));
  t33 = md_load4(coeff + 12);             /* a1[3] */
  t34 = md_paddw(t33, t29);
  t35 = md_psubw(t34, t30);
  t36 = md_psllwi(md_psubw(t33, t29), 2u);
  t37 = md_load4(coeff + 52);             /* a1[13] */
  t38 = md_paddw(t34, t30);
  t39 = md_paddw(md_pmulhw(t31, md_from_int64(qword_455C38)), md_pmulhw(t36, md_from_int64(qword_455C40)));
  t40 = md_psubw(md_paddw(t32, md_pmulhw(t36, md_from_int64(qword_455C30))), t38);
  t41 = md_load4(coeff + 20);             /* a1[5] */
  t42 = md_psubw(md_pmulhw(md_psllwi(t35, 2u), md_from_int64(qword_455C20)), t40);
  t193 = md_paddw(t41, t37);
  t43 = md_load4(coeff + 4);              /* a1[1] */
  t44 = md_pmulhw(md_psllwi(md_psubw(t41, t37), 2u), md_from_int64(qword_455C20));
  t45 = md_load4(coeff + 36);             /* a1[9] */
  t204 = md_paddw(t39, t42);
  t199 = md_psubw(t44, t193);
  t46 = md_psubw(t43, t45);
  t47 = md_paddw(t43, t45);
  t48 = md_paddw(t47, t193);
  t49 = md_psubw(t47, t193);
  t50 = md_psubw(t46, t199);
  t51 = md_psubw(t48, t38);
  t194 = md_paddw(t48, t38);
  t52 = md_paddw(t46, t199);
  t219 = t51;
  t200 = md_paddw(t52, t40);
  t217 = md_psubw(t52, t40);
  t210 = md_paddw(t49, t204);
  t207 = md_psubw(t49, t204);
  t205 = md_paddw(t50, t42);
  t214 = md_psubw(t50, t42);
  t53 = md_psubw(t191, t194);
  t54 = md_paddw(t191, t194);
  t55 = md_paddw(t197, t200);
  t56 = md_psubw(t197, t200);
  t57 = md_punpckldq(md_punpcklwd(t54, t55), md_punpckhwd(t54, t55));
  t58 = md_punpckldq(md_punpcklwd(t53, t56), md_punpckhwd(t53, t56));
  t59 = md_paddw(t206, t207);
  t60 = md_paddw(t203, t205);
  t61 = md_psubw(t206, t207);
  t62 = md_psubw(t203, t205);
  t63 = md_punpckldq(md_punpcklwd(t60, t59), md_punpckhwd(t60, t59));
  t64 = md_punpckldq(md_punpcklwd(t62, t61), md_punpckhwd(t62, t61));
  t65 = md_punpckhdq(t57, t63);
  t66 = md_punpckldq(t57, t63);
  t67 = md_paddw(t66, t65);
  t68 = md_psubw(t66, t65);
  t69 = md_psubw(md_pmulhw(md_psllwi(md_punpckhdq(t58, t64), 2u), md_from_int64(qword_455C20)), t65);
  t70 = md_punpckldq(t58, t64);
  t71 = md_paddw(t70, t69);
  t72 = md_psubw(t70, t69);
  t73 = md_punpckldq(t191, t194);
  t74 = md_punpckhdq(t194, t191);
  t192 = t67;
  t75 = md_paddw(t73, t74);
  t76 = md_psubw(t73, t74);
  t195 = t71;
  t77 = md_punpckhdq(t200, t197);
  t78 = md_punpckldq(t197, t200);
  t79 = md_paddw(t78, t77);
  t198 = t72;
  t80 = md_psubw(t78, t77);
  t201 = t68;
  t81 = md_punpckhdq(md_punpckhwd(t76, t80), md_punpcklwd(t75, t79));
  t82 = md_punpckhdq(md_punpcklwd(t76, t80), md_punpckhwd(t75, t79));
  t83 = md_punpckhdq(t205, t203);
  t84 = md_punpckldq(t203, t205);
  t85 = md_paddw(t84, t83);
  t86 = md_psubw(t84, t83);
  t87 = md_punpckhdq(t207, t206);
  t88 = md_punpckldq(t206, t207);
  t89 = md_paddw(t88, t87);
  t90 = md_psubw(t88, t87);
  t91 = md_punpckhdq(md_punpckhwd(t86, t90), md_punpcklwd(t85, t89));
  t92 = md_punpckhdq(md_punpcklwd(t86, t90), md_punpckhwd(t85, t89));
  t93 = t81;
  t94 = md_punpckldq(t81, t91);
  t95 = md_punpckhdq(t93, t91);
  t96 = md_punpckhdq(t82, t92);
  t97 = md_psubw(t95, t96);
  t98 = md_paddw(t95, t96);
  t99 = md_psllwi(t94, 2u);
  t100 = md_psllwi(md_punpckldq(t82, t92), 2u);
  t101 = md_pmulhw(t99, md_from_int64(qword_455C38));
  t102 = md_pmulhw(t100, md_from_int64(qword_455C40));
  t103 = md_psubw(md_paddw(md_pmulhw(t100, md_from_int64(qword_455C30)), md_pmulhw(t99, md_from_int64(qword_455C28))), t98);
  t104 = md_psubw(md_pmulhw(md_psllwi(t97, 2u), md_from_int64(qword_455C20)), t103);
  t105 = md_packsswb(md_psrawi(md_paddw(t195, t103), 5u), md_psrawi(md_psubw(t192, t98), 5u));
  t106 = md_packsswb(md_psrawi(md_paddw(t192, t98), 5u), md_psrawi(md_psubw(t195, t103), 5u));
  t107 = md_paddw(md_paddw(t101, t102), t104);
  t108 = md_packsswb(md_psrawi(md_psubw(t201, t107), 5u), md_psrawi(md_psubw(t198, t104), 5u));
  t109 = md_packsswb(md_psrawi(md_paddw(t198, t104), 5u), md_psrawi(md_paddw(t201, t107), 5u));
  t110 = md_punpckhbw(t106, t105);
  t111 = md_punpcklbw(t106, t105);
  t112 = md_punpcklbw(t109, t108);
  t113 = md_punpckhbw(t109, t108);
  t114 = md_punpcklwd(t111, t112);
  t115 = md_punpcklwd(t113, t110);
  dst1 = (void *)*(unsigned int *)(dst_rows + 4);       /* was *(__m64 **)(a2 + 4) */
  t117 = md_punpckhwd(t111, t112);
  t118 = md_punpckhwd(t113, t110);
  md_store8((void *)*(unsigned int *)dst_rows, md_punpckldq(t114, t115));
  dst2 = (void *)*(unsigned int *)(dst_rows + 8);       /* was *(__m64 **)(a2 + 8) */
  md_store8(dst1, md_punpckhdq(t114, t115));
  dst3 = (void *)*(unsigned int *)(dst_rows + 12);      /* was *(__m64 **)(a2 + 12) */
  md_store8(dst2, md_punpckldq(t117, t118));
  md_store8(dst3, md_punpckhdq(t117, t118));
  t121 = md_psubw(t208, t210);
  t122 = md_paddw(t208, t210);
  t123 = md_paddw(t212, t214);
  t124 = md_psubw(t212, t214);
  t125 = md_punpckldq(md_punpcklwd(t122, t123), md_punpckhwd(t122, t123));
  t126 = md_punpckldq(md_punpcklwd(t121, t124), md_punpckhwd(t121, t124));
  t127 = md_paddw(t218, t219);
  t128 = md_paddw(t216, t217);
  t129 = md_psubw(t218, t219);
  t130 = md_psubw(t216, t217);
  t131 = md_punpckldq(md_punpcklwd(t128, t127), md_punpckhwd(t128, t127));
  t132 = md_punpckldq(md_punpcklwd(t130, t129), md_punpckhwd(t130, t129));
  t133 = md_punpckhdq(t125, t131);
  t134 = md_punpckldq(t125, t131);
  t135 = md_paddw(t134, t133);
  t136 = md_psubw(t134, t133);
  t137 = md_psubw(md_pmulhw(md_psllwi(md_punpckhdq(t126, t132), 2u), md_from_int64(qword_455C20)), t133);
  t138 = md_punpckldq(t126, t132);
  t139 = md_paddw(t138, t137);
  t140 = md_psubw(t138, t137);
  t141 = md_punpckldq(t208, t210);
  t142 = md_punpckhdq(t210, t208);
  t209 = t135;
  t143 = md_paddw(t141, t142);
  t144 = md_psubw(t141, t142);
  t211 = t139;
  t145 = md_punpckhdq(t214, t212);
  t146 = md_punpckldq(t212, t214);
  t147 = md_paddw(t146, t145);
  t213 = t140;
  t148 = md_psubw(t146, t145);
  t215 = t136;
  t149 = md_punpckhdq(md_punpckhwd(t144, t148), md_punpcklwd(t143, t147));
  t150 = md_punpckhdq(md_punpcklwd(t144, t148), md_punpckhwd(t143, t147));
  t151 = md_punpckhdq(t217, t216);
  t152 = md_punpckldq(t216, t217);
  t153 = md_paddw(t152, t151);
  t154 = md_psubw(t152, t151);
  t155 = md_punpckhdq(t219, t218);
  t156 = md_punpckldq(t218, t219);
  t157 = md_paddw(t156, t155);
  t158 = md_psubw(t156, t155);
  t159 = md_punpckhdq(md_punpckhwd(t154, t158), md_punpcklwd(t153, t157));
  t160 = md_punpckhdq(md_punpcklwd(t154, t158), md_punpckhwd(t153, t157));
  t161 = t149;
  t162 = md_punpckldq(t149, t159);
  t163 = md_punpckhdq(t161, t159);
  t164 = md_punpckhdq(t150, t160);
  t165 = md_psubw(t163, t164);
  t166 = md_paddw(t163, t164);
  t167 = md_psllwi(t162, 2u);
  t168 = md_psllwi(md_punpckldq(t150, t160), 2u);
  t169 = md_pmulhw(t167, md_from_int64(qword_455C38));
  t170 = md_pmulhw(t168, md_from_int64(qword_455C40));
  t171 = md_psubw(md_paddw(md_pmulhw(t168, md_from_int64(qword_455C30)), md_pmulhw(t167, md_from_int64(qword_455C28))), t166);
  t172 = md_psubw(md_pmulhw(md_psllwi(t165, 2u), md_from_int64(qword_455C20)), t171);
  t173 = md_packsswb(md_psrawi(md_paddw(t211, t171), 5u), md_psrawi(md_psubw(t209, t166), 5u));
  t174 = md_packsswb(md_psrawi(md_paddw(t209, t166), 5u), md_psrawi(md_psubw(t211, t171), 5u));
  t175 = md_paddw(md_paddw(t169, t170), t172);
  t176 = md_packsswb(md_psrawi(md_psubw(t215, t175), 5u), md_psrawi(md_psubw(t213, t172), 5u));
  t177 = md_packsswb(md_psrawi(md_paddw(t213, t172), 5u), md_psrawi(md_paddw(t215, t175), 5u));
  t178 = md_punpckhbw(t174, t173);
  t179 = md_punpcklbw(t174, t173);
  t180 = md_punpcklbw(t177, t176);
  t181 = md_punpckhbw(t177, t176);
  t182 = md_punpcklwd(t179, t180);
  t183 = md_punpcklwd(t181, t178);
  dst4 = (void *)*(unsigned int *)(dst_rows + 20);      /* was *(__m64 **)(a2 + 20) */
  t185 = md_punpckhwd(t179, t180);
  t186 = md_punpckhwd(t181, t178);
  md_store8((void *)*(unsigned int *)(dst_rows + 16), md_punpckldq(t182, t183));
  dst5 = (void *)*(unsigned int *)(dst_rows + 24);      /* was *(__m64 **)(a2 + 24) */
  md_store8(dst4, md_punpckhdq(t182, t183));
  dst6 = (void *)*(unsigned int *)(dst_rows + 28);      /* was *(__m64 **)(a2 + 28) */
  md_store8(dst5, md_punpckldq(t185, t186));
  md_store8(dst6, md_punpckhdq(t185, t186));
}


static void mdec_y_to_mono(unsigned int *src, unsigned char *dst, int blocks)
{
  unsigned int *cb;
  unsigned int *cr;
  unsigned int *y0;
  unsigned int *y1;
  unsigned char *out;
  unsigned char *out2;
  mdec_v64 t9;
  mdec_v64 t10;
  mdec_v64 t11;
  mdec_v64 t12;
  mdec_v64 t13;
  mdec_v64 t14;
  mdec_v64 t15;
  mdec_v64 t16;
  mdec_v64 t17;
  mdec_v64 t18;
  mdec_v64 t19;
  mdec_v64 t20;
  mdec_v64 t21;
  mdec_v64 t22;
  mdec_v64 t23;
  mdec_v64 t24;
  mdec_v64 t25;
  mdec_v64 t26;
  mdec_v64 t27;
  mdec_v64 t28;
  mdec_v64 t29;
  mdec_v64 t30;
  mdec_v64 t31;
  mdec_v64 t32;
  mdec_v64 t33;
  mdec_v64 t34;
  mdec_v64 t35;
  mdec_v64 t36;
  mdec_v64 t37;
  mdec_v64 t38;
  mdec_v64 t39;
  mdec_v64 t40;
  mdec_v64 t41;
  mdec_v64 t42;
  mdec_v64 t43;
  mdec_v64 t44;
  mdec_v64 t45;
  mdec_v64 t46;
  mdec_v64 t47;
  int outer;
  int mid;
  int inner;

  cb = src + 32;
  cr = src + 34;
  y0 = src;
  y1 = src + 16;
  out = dst;
  out2 = dst + 48;                       /* was a2 + 6 (__m64) */
  do
  {
    outer = 2;
    do
    {
      mid = 2;
      do
      {
        inner = 4;
        do
        {
          t9 = md_from_int(*y0);
          t10 = md_punpcklbw(t9, t9);
          t11 = md_punpcklwd(t10, t10);
          t12 = md_from_int(*y1);
          t13 = md_punpcklbw(t12, t12);
          t14 = md_punpcklwd(t13, t13);
          t15 = md_paddb(md_from_int(*cb), md_from_int64(qword_455C70));
          t16 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckldq(t11, t11), 6u), md_from_int64(qword_455C50)),
                  md_pmulhw(md_psrawi(md_punpckldq(t14, t14), 6u), md_from_int64(qword_455C58)));
          t17 = md_punpcklbw(t15, t15);
          t18 = md_punpcklwd(t17, t15);
          t19 = md_psrlqi(t17, 0x10u);
          t20 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckhdq(t11, t11), 6u), md_from_int64(qword_455C60)),
                  md_pmulhw(md_psrawi(md_punpckhdq(t14, t14), 6u), md_from_int64(qword_455C68)));
          t21 = md_por(
                  md_psrlqi(md_pand(t16, md_from_int64(qword_455C78)), 0x10u),
                  md_psllqi(md_pand(t20, md_from_int64(qword_455C78)), 0x10u));
          t22 = md_paddb(md_from_int(*cr), md_from_int64(qword_455C70));
          md_store8(out, md_packuswb(
                          md_paddsw(md_punpcklbw(t18, md_from_int(mdec_mono_expand_value)), t16),
                          md_paddsw(md_punpcklbw(t19, md_from_int(mdec_mono_expand_value)), t21)));
          t23 = md_punpcklbw(t22, t22);
          t24 = md_punpcklbw(md_punpcklwd(t23, t22), md_from_int(mdec_mono_expand_value));
          t25 = md_psrlqi(t23, 0x10u);
          md_store8(out2, md_packuswb(
                          md_paddsw(t24, t16),
                          md_paddsw(
                            md_punpcklbw(md_punpckldq(t25, t25), md_from_int(mdec_mono_expand_value)),
                            t21)));
          t26 = md_psrlqi(md_from_int(*y0), 0x10u);
          t27 = md_paddsw(
                  md_punpcklbw(
                    md_punpcklwd(md_psrlqi(t19, 0x18u), md_psrlqi(t19, 0x20u)),
                    md_from_int(mdec_mono_expand_value)),
                  t20);
          t28 = md_punpcklbw(t26, t26);
          t29 = md_paddsw(
                  md_punpcklbw(
                    md_punpcklwd(md_psrlqi(t25, 0x18u), md_psrlqi(t25, 0x20u)),
                    md_from_int(mdec_mono_expand_value)),
                  t20);
          t30 = md_punpcklwd(t28, t28);
          t31 = md_psrlqi(md_from_int(*y1), 0x10u);
          t32 = md_punpcklbw(t31, t31);
          t33 = md_punpcklwd(t32, t32);
          t34 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckldq(t30, t30), 6u), md_from_int64(qword_455C50)),
                  md_pmulhw(md_psrawi(md_punpckldq(t33, t33), 6u), md_from_int64(qword_455C58)));
          t35 = md_paddb(md_from_int(cb[1]), md_from_int64(qword_455C70));
          t36 = md_psrlqi(md_pand(t34, md_from_int64(qword_455C78)), 0x10u);
          t37 = md_paddsw(
                  md_pmulhw(md_psrawi(md_punpckhdq(t30, t30), 6u), md_from_int64(qword_455C60)),
                  md_pmulhw(md_psrawi(md_punpckhdq(t33, t33), 6u), md_from_int64(qword_455C68)));
          t38 = md_paddb(md_from_int(cr[1]), md_from_int64(qword_455C70));
          t39 = md_psllqi(md_pand(t37, md_from_int64(qword_455C78)), 0x10u);
          md_store8(out + 8, md_packuswb(
                              t27,
                              md_paddsw(
                                md_punpcklbw(
                                  md_punpcklwd(md_punpcklbw(t35, t35), t35),
                                  md_from_int(mdec_mono_expand_value)),
                                t34)));
          t40 = md_por(t36, t39);
          t41 = t38;
          t42 = md_paddsw(md_punpcklbw(md_punpcklwd(md_punpcklbw(t38, t38), t38), md_from_int(0)), t34);
          t43 = md_psrlqi(t41, 8u);
          md_store8(out2 + 8, md_packuswb(t29, t42));
          t44 = md_psrlqi(t35, 8u);
          t45 = md_psrlqi(t44, 8u);
          cb += 4;
          cr += 4;
          t46 = md_psrlqi(t43, 8u);
          out += 96;                   /* was v7 += 12 (__m64) */
          out2 += 96;
          y0 += 2;
          t47 = md_paddsw(
                  md_punpcklbw(
                    md_punpcklwd(t46, md_psrlqi(md_punpcklbw(t46, t46), 0x10u)),
                    md_from_int(mdec_mono_expand_value)),
                  t37);
          md_store8(out - 80, md_packuswb(        /* was v7[-10] */
                                            md_paddsw(md_punpcklbw(md_punpcklbw(t44, t44), md_from_int(0)), t40),
                                            md_paddsw(
                                              md_punpcklbw(
                                                md_punpcklwd(t45, md_psrlqi(md_punpcklbw(t45, t45), 0x10u)),
                                                md_from_int(mdec_mono_expand_value)),
                                              t37)));
          y1 += 2;
          md_store8(out2 - 80, md_packuswb(md_paddsw(md_punpcklbw(md_punpcklbw(t43, t43), md_from_int(0)), t40), t47));  /* was v8[-10] */
          --inner;
        }
        while ( inner );
        y0 -= 7;
        y1 -= 7;
        out -= 360;                  /* was v7 -= 45 (__m64) */
        out2 -= 360;
        --mid;
      }
      while ( mid );
      y0 += 6;
      y1 += 6;
      out += 336;                    /* was v7 += 42 (__m64) */
      out2 += 336;
      --outer;
    }
    while ( outer );
    y0 += 80;
    y1 += 80;
    cb += 32;
    cr += 32;
    --blocks;
  }
  while ( blocks );
}
