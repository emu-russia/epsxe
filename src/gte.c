#include "pch.h"
/* --------------------------------------------------------------------------
 * Macros for the repeated decompiled fragments (issue #5).
 * The module is full of identical code blocks: the MMX matrix-vector core
 * of RTPS/RTPT, the saturating stores of the color/lighting commands and
 * the depth-queuing tail.  Each macro expands to exactly the statements of
 * the original code, with the differing pieces (register indices, FLAG bits,
 * temporaries, labels, offsets) passed as parameters.
 * -------------------------------------------------------------------------- */

/* Matrix * vector (three rows of the rotation matrix) with the MAC/IR/FLAG
 * computation, as done by gte_rtps()/gte_rtpt().  `extra` and `ir_stores`
 * are optional statement sequences (pass none when absent).
 *
 *   p        - GTE state pointer (local holding gte_regs_ptr)
 *   vec      - __m64 vertex vector (X,Y in the low word, Z in the high word)
 *   m0,m1,m2 - temporaries for the three row products
 *   acc_xy, acc_z - __m64 MAC accumulators (SXY row / SZ row)
 *   pk, ir_h, ir_l - __m64 pack / IR1|IR2 / IR3 temporaries
 *   cmp, flag - flag computation temporaries
 *   extra    - statements between the MAC sums and the pack (may be empty)
 *   ir_stores - statements storing IR1/IR2/IR3 after the FLAG update
 */
#define GTE_MMX_MV(p, vec, m0, m1, m2, acc_xy, acc_z, pk, ir_h, ir_l, cmp, flag, extra, ir_stores) \
  do \
  { \
    (m0) = _m_psradi(_m_pmaddwd(*(__m64 *)((p) + 134), (vec)), 1u); \
    (m1) = _m_psradi(_m_pmaddwd(*(__m64 *)((p) + 140), (vec)), 1u); \
    (m2) = _m_psradi(_m_pmaddwd(*(__m64 *)((p) + 128), (vec)), 1u); \
    (acc_z) = _m_paddd(_m_psradi(_m_paddd((m1), _m_psrlqi((m1), 0x20u)), 0xBu), *(__m64 *)((p) + 156)); \
    (acc_xy) = _m_paddd(_m_psradi(_m_paddd(_m_punpckldq((m2), (m0)), _m_punpckhdq((m2), (m0))), 0xBu), *(__m64 *)((p) + 148)); \
    extra \
    (pk) = _m_packssdw((acc_xy), (acc_z)); \
    (ir_h) = _m_psradi(_m_psrlqi((pk), 0x10u), 0x10u); \
    (ir_l) = _m_psradi(_m_punpcklwd((pk), (pk)), 0x10u); \
    (cmp) = _m_pandn(_m_pcmpeqd((acc_xy), (ir_l)), _m_from_int64(qword_44F958)); \
    (flag) = _m_to_int(_m_por(_m_pandn(_m_pcmpeqd((acc_z), (ir_h)), _m_from_int64(qword_44F960)), _m_por((cmp), _m_psrlqi((cmp), 0x20u)))); \
    *(uint32_t *)((p) + 252) |= (flag); \
    ir_stores \
  } \
  while (0)

/* Perspective divide of the transformed Z (clamp to 0..0xFFFF) and the
 * ratio H*2^16/Z, as done by gte_rtps()/gte_rtpt().  `lab_small`/`lab_done`
 * are the labels of the original code; `zoff` is the byte offset of the
 * SZ register that receives the clamped Z. */
#define GTE_RTPS_DIVIDE(p, z, ratio, hreg, sign, zoff, lab_small, lab_done) \
  do \
  { \
    if ( (unsigned int)(z) > 0xFFFF ) \
    { \
      *(uint32_t *)((p) + 252) |= 0x80040000; \
      (sign) = (z) < 0; \
      (z) = 0xFFFF; \
      if ( (sign) ) \
      { \
        (z) = 0; \
        (ratio) = 0x20000; \
        *(uint32_t *)((p) + (zoff)) = 0; \
        goto lab_small; \
      } \
    } \
    else \
    { \
      (ratio) = 0x20000; \
      if ( !(z) ) \
      { \
      lab_small: \
        *(uint32_t *)((p) + (zoff)) = (z); \
        *(uint32_t *)((p) + 252) |= 0x80020000; \
        goto lab_done; \
      } \
    } \
    *(uint32_t *)((p) + (zoff)) = (z); \
    (hreg) = *(uint32_t *)((p) + 232); \
    if ( 2 * (z) < (hreg) ) \
      goto lab_small; \
    (ratio) = ((hreg) << 16) / (unsigned int)(z); \
  lab_done: \
    ; \
  } \
  while (0)

/* Screen-XY computation with saturation to -400..+3FF, as done by
 * gte_rtps()/gte_rtpt().  `store` is the statement sequence that writes the
 * packed SXY word(s). */
#define GTE_RTPS_SXY(p, ratio, ir_l, sx, sy, sx2, sy2, packed, store) \
  do \
  { \
    (sx) = ((uint64_t)(_m_to_int(ir_l) * (int64_t)(ratio)) >> 16) + (*(int *)((p) + 224) >> 16); \
    (sy) = (*(int *)((p) + 228) >> 16) + ((uint64_t)((ratio) * (int64_t)_m_to_int(_m_psrlqi(ir_l, 0x20u))) >> 16); \
    (sx2) = (sx) + 1024; \
    (sy2) = (sy) + 1024; \
    if ( (unsigned int)((sx) + 1024) > 0x7FF ) \
    { \
      *(uint32_t *)((p) + 252) |= 0x80004000; \
      (sx) = 1023; \
      if ( (sx2) < 0 ) \
        (sx) = -1024; \
    } \
    if ( (unsigned int)(sy2) > 0x7FF ) \
    { \
      *(uint32_t *)((p) + 252) |= 0x80002000; \
      (sy) = 1023; \
      if ( (sy2) < 0 ) \
        (sy) = -1024; \
    } \
    LODWORD(packed) = (sx) << 16; \
    HIDWORD(packed) = (sy); \
    store \
  } \
  while (0)

/* Depth queuing (MAC0 = ratio*DQB + DQB, IR0 clamped to 0..0x1000) with the
 * FLAG/result tail, as done by gte_rtps()/gte_rtpt(). */
#define GTE_RTPS_DEPTH(p, ratio, mac0, ir0, sign) \
  do \
  { \
    (mac0) = *(uint32_t *)((p) + 240); \
    (ir0) = (uint64_t)((ratio) * (int64_t)*(int *)((p) + 236)) >> 12; \
    *(uint32_t *)((p) + 96) = (ratio) * *(uint32_t *)((p) + 236) + (mac0); \
    (ir0) = ((mac0) >> 12) + (ir0); \
    if ( (unsigned int)(ir0) > 0x1000 ) \
    { \
      *(uint32_t *)((p) + 252) |= 0x1000u; \
      (sign) = (ir0) < 0; \
      (ir0) = 4096; \
      if ( (sign) ) \
        (ir0) = 0; \
    } \
    *(uint32_t *)((p) + 32) = (ir0); \
  } \
  while (0)

/* Saturate an integer to signed 16-bit [lo, 0x7FFF] and store it into the
 * GTE data register `ir`, setting `flag` bits in FLAG (ctrl[31]) on
 * saturation.  `x` is read several times like the original code, so pass a
 * plain local variable. */
#define GTE_SAT16(ir, flag, lo, x) \
  do \
  { \
    if ( (x) >= (lo) ) \
    { \
      if ( (x) <= 0x7FFF ) \
      { \
        gte_regs.data[(ir)].u32 = (x); \
      } \
      else \
      { \
        gte_regs.ctrl[31].u32 |= (flag); \
        gte_regs.data[(ir)].u32 = 0x7FFF; \
      } \
    } \
    else \
    { \
      gte_regs.ctrl[31].u32 |= (flag); \
      gte_regs.data[(ir)].u32 = (lo); \
    } \
  } \
  while (0)

/* Saturate a 0..255 color component into one byte of the RGB2 FIFO register
 * (data[22]), setting `flag` bits in FLAG on saturation.  `dst` is the
 * byte-lvalue accessor (LOBYTE/HIBYTE of data[22]); `x` the component. */
#define GTE_RGB_SAT(dst, flag, x) \
  do \
  { \
    if ( (x) >= 0 ) \
    { \
      if ( (x) <= 255 ) \
      { \
        (dst) = (x); \
      } \
      else \
      { \
        gte_regs.ctrl[31].u32 |= (flag); \
        (dst) = -1; \
      } \
    } \
    else \
    { \
      gte_regs.ctrl[31].u32 |= (flag); \
      (dst) = 0; \
    } \
  } \
  while (0)

/* Blue-component variant that also clobbers the low byte of the function
 * result (decompiler artifact) and copies the CODE byte into RGB2, as in
 * gte_dcpl()/gte_dpcs()/gte_ncds()/gte_ncdt()/gte_cdp(). */
#define GTE_RGB_B_SAT_DCPL(ret, x) \
  do \
  { \
    if ( (x) >= 0 ) \
    { \
      if ( (x) <= 255 ) \
      { \
        LOBYTE(gte_regs.data[22].s16.lo) = (x); \
      } \
      else \
      { \
        gte_regs.ctrl[31].u32 |= 0x80000u; \
        LOBYTE(ret) = HIBYTE(gte_regs.data[6].u32); \
        LOBYTE(gte_regs.data[22].s16.lo) = -1; \
      } \
      HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32); \
    } \
    else \
    { \
      LOBYTE(ret) = gte_regs.ctrl[31].u16.hi; \
      LOBYTE(gte_regs.data[22].s16.lo) = 0; \
      gte_regs.ctrl[31].u32 |= 0x80000u; \
      HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32); \
    } \
  } \
  while (0)

/* Blue-component variant used by gte_ncs()/gte_nccs()/gte_cc(). */
#define GTE_RGB_B_SAT_NCS(ret, x) \
  do \
  { \
    if ( (x) >= 0 ) \
    { \
      if ( (x) <= 255 ) \
      { \
        LOBYTE(gte_regs.data[22].s16.lo) = (x); \
      } \
      else \
      { \
        LOBYTE(ret) = gte_regs.ctrl[31].u16.hi; \
        LOBYTE(gte_regs.data[22].s16.lo) = -1; \
        gte_regs.ctrl[31].u32 |= 0x80000u; \
      } \
      HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32); \
    } \
    else \
    { \
      gte_regs.ctrl[31].u32 |= 0x80000u; \
      LOBYTE(gte_regs.data[22].s16.lo) = 0; \
      HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32); \
      LOBYTE(ret) = HIBYTE(gte_regs.data[6].u32); \
    } \
  } \
  while (0)

/* Blue-component variant that stashes the FLAG value into the function
 * result, as in gte_nct()/gte_ncct(). */
#define GTE_RGB_B_SAT_RESULT(ret, x) \
  do \
  { \
    if ( (x) >= 0 ) \
    { \
      if ( (x) <= 255 ) \
      { \
        (ret) = HIBYTE(gte_regs.data[6].u32); \
        LOBYTE(gte_regs.data[22].s16.lo) = (x); \
      } \
      else \
      { \
        (ret) = gte_regs.ctrl[31].s32; \
        LOBYTE(gte_regs.data[22].s16.lo) = -1; \
        gte_regs.ctrl[31].u32 |= 0x80000u; \
      } \
      HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32); \
    } \
    else \
    { \
      (ret) = gte_regs.ctrl[31].s32; \
      gte_regs.ctrl[31].u32 |= 0x80000u; \
      LOBYTE(gte_regs.data[22].s16.lo) = 0; \
      HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32); \
    } \
  } \
  while (0)

int gte_rtps()
{
  int p;
  int64_t sz12;
  int sz3;
  __m64 m0;
  __m64 m1;
  __m64 m2;
  __m64 acc_z;
  __m64 acc_xy;
  __m64 pk;
  __m64 ir_h;
  __m64 ir_l;
  __m64 cmp;
  int ratio;
  int z;
  int hreg;
  int ratio_saved;
  int sx;
  int sy;
  int sx2;
  int sy2;
  int sx_store;
  uint64_t packed;
  int mac0;
  int ir0;
  int error_flag;
  bool sign;

  p = gte_regs_ptr;
  *(uint32_t *)(gte_regs_ptr + 252) = 0;
  sz12 = *(uint64_t *)(p + 68);
  sz3 = *(uint32_t *)(p + 76);
  *(uint64_t *)(p + 48) = *(uint64_t *)(p + 52);
  *(uint64_t *)(p + 64) = sz12;
  *(uint32_t *)(p + 72) = sz3;
  GTE_MMX_MV(p,
             _m_psrlqi(_m_psllqi(*(__m64 *)p, 0x10u), 0x10u),
             m0, m1, m2, acc_xy, acc_z,
             pk, ir_h, ir_l, cmp, ratio,
             *(uint32_t *)(p + 108) = _m_to_int(acc_z);
             *(__m64 *)(p + 100) = acc_xy;
             ,
             *(__m64 *)(p + 36) = ir_l;
             *(uint32_t *)(p + 44) = _m_to_int(ir_h););
  z = _m_to_int(acc_z);
  GTE_RTPS_DIVIDE(p, z, ratio, hreg, sign, 76, LABEL_5, LABEL_6);
  ratio_saved = ratio;
  GTE_RTPS_SXY(p, ratio, ir_l, sx, sy, sx2, sy2, packed,
               sx_store = packed >> 16;
               *(uint32_t *)(p + 56) = sx_store;
               *(uint32_t *)(p + 60) = sx_store;);
  GTE_RTPS_DEPTH(p, ratio_saved, mac0, ir0, sign);
  error_flag = (*(uint32_t *)(p + 252) & 0x20000) << 14;
  *(uint32_t *)(p + 252) |= error_flag;
  _m_empty();
  return error_flag;
}

int gte_rtpt()
{
  int p;
  __m64 m0_a;
  __m64 m1_a;
  __m64 m2_a;
  __m64 acc_z_a;
  __m64 acc_xy_a;
  __m64 pk_a;
  __m64 ir_h_a;
  __m64 ir_l_a;
  __m64 cmp_a;
  int ratio_a;
  int z_a;
  int hreg_a;
  int sx_a;
  int sy_a;
  int sx2_a;
  int sy2_a;
  uint64_t packed_a;
  __m64 m0_b;
  __m64 m1_b;
  __m64 m2_b;
  __m64 acc_z_b;
  __m64 acc_xy_b;
  __m64 pk_b;
  __m64 ir_h_b;
  __m64 ir_l_b;
  __m64 cmp_b;
  int ratio_b;
  int z_b;
  int hreg_b;
  int sx_b;
  int sy_b;
  int sx2_b;
  int sy2_b;
  uint64_t packed_b;
  __m64 m0_c;
  __m64 m1_c;
  __m64 m2_c;
  __m64 acc_z_c;
  __m64 acc_xy_c;
  __m64 pk_c;
  __m64 ir_h_c;
  __m64 ir_l_c;
  __m64 cmp_c;
  int ratio_c;
  int z_c;
  int hreg_c;
  int ratio_saved;
  int sx_c;
  int sy_c;
  int sx2_c;
  int sy2_c;
  int sx_store;
  uint64_t packed_c;
  int mac0;
  int ir0;
  int error_flag;
  bool sign;

  p = gte_regs_ptr;
  *(uint32_t *)(gte_regs_ptr + 252) = 0;
  *(uint32_t *)(p + 64) = *(uint32_t *)(p + 76);
  GTE_MMX_MV(p,
             _m_psrlqi(_m_psllqi(*(__m64 *)p, 0x10u), 0x10u),
             m0_a, m1_a, m2_a, acc_xy_a, acc_z_a,
             pk_a, ir_h_a, ir_l_a, cmp_a, ratio_a,
             /* none */,
             /* none */);
  z_a = _m_to_int(acc_z_a);
  GTE_RTPS_DIVIDE(p, z_a, ratio_a, hreg_a, sign, 68, LABEL_5, LABEL_6);
  GTE_RTPS_SXY(p, ratio_a, ir_l_a, sx_a, sy_a, sx2_a, sy2_a, packed_a,
               *(uint32_t *)(p + 48) = packed_a >> 16;);
  GTE_MMX_MV(p,
             _m_psrlqi(*(__m64 *)(p + 6), 0x10u),
             m0_b, m1_b, m2_b, acc_xy_b, acc_z_b,
             pk_b, ir_h_b, ir_l_b, cmp_b, ratio_b,
             /* none */,
             /* none */);
  z_b = _m_to_int(acc_z_b);
  GTE_RTPS_DIVIDE(p, z_b, ratio_b, hreg_b, sign, 72, LABEL_12, LABEL_13);
  GTE_RTPS_SXY(p, ratio_b, ir_l_b, sx_b, sy_b, sx2_b, sy2_b, packed_b,
               *(uint32_t *)(p + 52) = packed_b >> 16;);
  GTE_MMX_MV(p,
             _m_psrlqi(*(__m64 *)(p + 14), 0x10u),
             m0_c, m1_c, m2_c, acc_xy_c, acc_z_c,
             pk_c, ir_h_c, ir_l_c, cmp_c, ratio_c,
             *(uint32_t *)(p + 108) = _m_to_int(acc_z_c);
             *(__m64 *)(p + 100) = acc_xy_c;
             ,
             *(__m64 *)(p + 36) = ir_l_c;
             *(uint32_t *)(p + 44) = _m_to_int(ir_h_c););
  z_c = _m_to_int(acc_z_c);
  GTE_RTPS_DIVIDE(p, z_c, ratio_c, hreg_c, sign, 76, LABEL_19, LABEL_20);
  ratio_saved = ratio_c;
  GTE_RTPS_SXY(p, ratio_c, ir_l_c, sx_c, sy_c, sx2_c, sy2_c, packed_c,
               sx_store = packed_c >> 16;
               *(uint32_t *)(p + 56) = sx_store;
               *(uint32_t *)(p + 60) = sx_store;);
  GTE_RTPS_DEPTH(p, ratio_saved, mac0, ir0, sign);
  error_flag = (*(uint32_t *)(p + 252) & 0x20000) << 14;
  *(uint32_t *)(p + 252) |= error_flag;
  _m_empty();
  return error_flag;
}

static int gte_clamp(int flag, int value)
{
  int clamped;

  clamped = value;
  if ( value >= -32768 )
  {
    if ( value > 0x7FFF )
    {
      gte_regs.ctrl[31].u32 |= flag;
      return 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= flag;
    return -32768;
  }
  return clamped;
}

static char gte_convert_to_5bit(int value)
{
  int result_5bit;

  if ( (value & 0x8000u) == 0 )
  {
    if ( (int16_t)value <= 3968 )
      return value >> 7;
    else
      LOBYTE(result_5bit) = 31;
  }
  else
  {
    LOBYTE(result_5bit) = 0;
  }
  return result_5bit;
}

static char gte_dcpl()
{
  int g_base;
  int b_base;
  int r_clamped;
  int mac1_prev;
  GTE_REG mac3;
  int32_t green;
  int blue;

  g_base = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 8;
  b_base = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 8;
  r_clamped = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 8));
  gte_regs.data[25].u32 = mac1_prev + ((gte_regs.data[8].s16.hi * r_clamped) >> 12);
  gte_regs.data[26].u32 = g_base + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base)) >> 12);
  mac3.u32 = b_base + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base)) >> 12);
  gte_regs.data[27] = mac3;
  GTE_SAT16(9, 0x81000000, -32768, gte_regs.data[25].s32);
  GTE_SAT16(10, 0x80800000, -32768, gte_regs.data[26].s32);
  GTE_SAT16(11, 0x400000u, -32768, mac3.s32);
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = gte_regs.data[26].s32 >> 4;
  blue = mac3.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = gte_regs.data[25].s32 >> 4;
  gte_color_g = gte_regs.data[26].s32 >> 4;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, gte_regs.data[25].s32 >> 4);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_DCPL(blue, blue);
  return blue;
}

static char gte_dpcs()
{
  int g_base;
  int b_base;
  int r_clamped;
  int mac1_prev;
  GTE_REG mac3;
  int32_t green;
  int blue;

  g_base = 16 * HIBYTE(gte_regs.data[6].u16.hi);
  b_base = 16 * LOBYTE(gte_regs.data[6].s16.lo);
  r_clamped = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - 16 * LOBYTE(gte_regs.data[6].u32));
  gte_regs.data[25].u32 = mac1_prev + ((gte_regs.data[8].s16.hi * r_clamped) >> 12);
  gte_regs.data[26].u32 = g_base + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base)) >> 12);
  mac3.u32 = b_base + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base)) >> 12);
  gte_regs.data[27] = mac3;
  GTE_SAT16(9, 0x81000000, -32768, gte_regs.data[25].s32);
  GTE_SAT16(10, 0x80800000, -32768, gte_regs.data[26].s32);
  GTE_SAT16(11, 0x400000u, -32768, mac3.s32);
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = gte_regs.data[26].s32 >> 4;
  blue = mac3.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = gte_regs.data[25].s32 >> 4;
  gte_color_g = gte_regs.data[26].s32 >> 4;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, gte_regs.data[25].s32 >> 4);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_DCPL(blue, blue);
  return blue;
}

static char gte_ncs()
{
  int z_part;
  int ir1;
  int ir2;
  int ir3;
  GTE_REG mac1;
  GTE_REG mac2;
  GTE_REG mac3;
  int red;
  int green;
  int blue;

  z_part = gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
  ir1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3 = (z_part + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1);
  GTE_SAT16(10, 0x80800000, 0, ir2);
  GTE_SAT16(11, 0x400000u, 0, ir3);
  mac1.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = mac1;
  gte_regs.data[26] = mac2;
  gte_regs.data[27] = mac3;
  GTE_SAT16(9, 0x81000000, 0, mac1.s32);
  GTE_SAT16(10, 0x80800000, 0, mac2.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3.s32);
  red = mac1.s32 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = mac2.s32 >> 4;
  blue = mac3.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = red;
  gte_color_g = green;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, red);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_NCS(red, blue);
  return red;
}

static char gte_nct()
{
  int part_a;
  int ir1_a;
  int ir2_a;
  int ir3_a;
  signed int mac1_a;
  signed int mac2_a;
  signed int mac3_a;
  int red_a;
  int green_a;
  int blue_a;
  int part_b;
  int ir1_b;
  int ir2_b;
  int ir3_b;
  signed int mac1_b;
  signed int mac2_b;
  signed int mac3_b;
  int red_b;
  int green_b;
  int blue_b;
  int part_c;
  int ir1_c;
  int ir2_c;
  int ir3_c;
  GTE_REG mac1_c;
  GTE_REG mac2_c;
  GTE_REG mac3_c;
  int red_c;
  int green_c;
  int blue_c;
  char code;

  part_a = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
  ir1_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi + part_a + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_a);
  GTE_SAT16(10, 0x80800000, 0, ir2_a);
  GTE_SAT16(11, 0x400000u, 0, ir3_a);
  mac1_a = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_a = gte_regs.ctrl[14].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_a = gte_regs.ctrl[15].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( (unsigned int)mac1_a >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x81000000;
  if ( (unsigned int)mac2_a >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x80800000;
  if ( (unsigned int)mac3_a >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x400000u;
  red_a = mac1_a >> 4;
  green_a = mac2_a >> 4;
  blue_a = mac3_a >> 4;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, red_a);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green_a);
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].s16.lo), 0x80000u, blue_a);
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  part_b = gte_regs.ctrl[10].s16.lo * gte_regs.data[3].s16.hi;
  ir1_b = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  ir2_b = (part_b + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
  ir3_b = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_b);
  GTE_SAT16(10, 0x80800000, 0, ir2_b);
  GTE_SAT16(11, 0x400000u, 0, ir3_b);
  mac1_b = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_b = gte_regs.ctrl[14].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_b = gte_regs.ctrl[15].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( (unsigned int)mac1_b >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x81000000;
  if ( (unsigned int)mac2_b >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x80800000;
  if ( (unsigned int)mac3_b >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x400000u;
  red_b = mac1_b >> 4;
  green_b = mac2_b >> 4;
  blue_b = mac3_b >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, red_b);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green_b);
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].s16.lo), 0x80000u, blue_b);
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  part_c = gte_regs.ctrl[10].s16.lo * gte_regs.data[5].s16.hi;
  ir1_c = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  ir2_c = (part_c + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
  ir3_c = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_c);
  GTE_SAT16(10, 0x80800000, 0, ir2_c);
  GTE_SAT16(11, 0x400000u, 0, ir3_c);
  mac1_c.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_c.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_c.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = mac1_c;
  gte_regs.data[26] = mac2_c;
  gte_regs.data[27] = mac3_c;
  GTE_SAT16(9, 0x81000000, 0, mac1_c.s32);
  GTE_SAT16(10, 0x80800000, 0, mac2_c.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_c.s32);
  red_c = mac1_c.s32 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green_c = mac2_c.s32 >> 4;
  blue_c = mac3_c.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = red_c;
  gte_color_g = green_c;
  gte_color_b = blue_c;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, red_c);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green_c);
  GTE_RGB_B_SAT_RESULT(code, blue_c);
  return code;
}

static char gte_ncds()
{
  int z_part;
  int ir1;
  int ir2;
  int ir3;
  GTE_REG mac1;
  GTE_REG mac2;
  GTE_REG mac3;
  int g_base;
  int b_base;
  int r_clamped;
  int mac1_prev;
  GTE_REG mac3_rgb;
  int32_t green;
  int blue;

  z_part = gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
  ir1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3 = (z_part + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1);
  GTE_SAT16(10, 0x80800000, 0, ir2);
  GTE_SAT16(11, 0x400000u, 0, ir3);
  mac1.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = mac1;
  gte_regs.data[26] = mac2;
  gte_regs.data[27] = mac3;
  GTE_SAT16(9, 0x81000000, 0, mac1.s32);
  GTE_SAT16(10, 0x80800000, 0, mac2.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3.s32);
  g_base = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  b_base = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  r_clamped = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = mac1_prev + ((gte_regs.data[8].s16.hi * r_clamped) >> 12);
  gte_regs.data[26].u32 = g_base + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base)) >> 12);
  mac3_rgb.u32 = b_base + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base)) >> 12);
  gte_regs.data[27] = mac3_rgb;
  GTE_SAT16(9, 0x81000000, 0, gte_regs.data[25].s32);
  GTE_SAT16(10, 0x80800000, 0, gte_regs.data[26].s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_rgb.s32);
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = gte_regs.data[26].s32 >> 4;
  blue = mac3_rgb.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = gte_regs.data[25].s32 >> 4;
  gte_color_g = gte_regs.data[26].s32 >> 4;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, gte_regs.data[25].s32 >> 4);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_DCPL(blue, blue);
  return blue;
}

static char gte_ncdt()
{
  int ir1_a;
  int ir2_a;
  int ir3_a;
  GTE_REG mac1_a;
  GTE_REG mac2_a;
  GTE_REG mac3_a;
  int g_base_a;
  int b_base_a;
  int r_clamped_a;
  int mac1_prev_a;
  int b_clamped_a;
  GTE_REG rgb_fifo_a;
  int32_t green_a;
  int blue_a;
  int x_part_b;
  int z_part_b;
  int ir1_b;
  int ir2_b;
  int ir3_b;
  GTE_REG mac1_b;
  GTE_REG mac2_b;
  GTE_REG mac3_b;
  int g_base_b;
  int b_base_b;
  int r_clamped_b;
  int mac1_prev_b;
  int b_clamped_b;
  GTE_REG rgb_fifo_b;
  int32_t green_b;
  int blue_b;
  int x_part_c;
  int z_part_c;
  int ir1_c;
  int ir2_c;
  int ir3_c;
  GTE_REG mac1_c;
  GTE_REG mac2_c;
  GTE_REG mac3_c;
  int g_base_c;
  int b_base_c;
  int r_clamped_c;
  int mac1_prev_c;
  GTE_REG mac3_rgb_c;
  int32_t green_c;
  int blue_c;

  ir1_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_a);
  GTE_SAT16(10, 0x80800000, 0, ir2_a);
  GTE_SAT16(11, 0x400000u, 0, ir3_a);
  mac1_a.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_a.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_a.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = mac1_a;
  gte_regs.data[26] = mac2_a;
  gte_regs.data[27] = mac3_a;
  GTE_SAT16(9, 0x81000000, 0, mac1_a.s32);
  GTE_SAT16(10, 0x80800000, 0, mac2_a.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_a.s32);
  g_base_a = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  b_base_a = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  r_clamped_a = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = mac1_prev_a + ((gte_regs.data[8].s16.hi * r_clamped_a) >> 12);
  gte_regs.data[26].u32 = g_base_a + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base_a)) >> 12);
  b_clamped_a = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base_a);
  rgb_fifo_a = gte_regs.data[21];
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_regs.data[20] = rgb_fifo_a;
  green_a = gte_regs.data[26].s32 >> 4;
  blue_a = (b_base_a + ((gte_regs.data[8].s16.hi * b_clamped_a) >> 12)) >> 4;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, gte_regs.data[25].s32 >> 4);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green_a);
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].s16.lo), 0x80000u, blue_a);
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  x_part_b = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
  z_part_b = gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
  ir1_b = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
       + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
       + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2_b = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
       + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
       + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3_b = (z_part_b + x_part_b + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_b);
  GTE_SAT16(10, 0x80800000, 0, ir2_b);
  GTE_SAT16(11, 0x400000u, 0, ir3_b);
  mac1_b.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_b.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_b.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = mac1_b;
  gte_regs.data[26] = mac2_b;
  gte_regs.data[27] = mac3_b;
  GTE_SAT16(9, 0x81000000, 0, mac1_b.s32);
  GTE_SAT16(10, 0x80800000, 0, mac2_b.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_b.s32);
  g_base_b = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  b_base_b = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  r_clamped_b = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = mac1_prev_b + ((gte_regs.data[8].s16.hi * r_clamped_b) >> 12);
  gte_regs.data[26].u32 = g_base_b + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base_b)) >> 12);
  b_clamped_b = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base_b);
  rgb_fifo_b = gte_regs.data[21];
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_regs.data[20] = rgb_fifo_b;
  green_b = gte_regs.data[26].s32 >> 4;
  blue_b = (b_base_b + ((gte_regs.data[8].s16.hi * b_clamped_b) >> 12)) >> 4;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, gte_regs.data[25].s32 >> 4);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green_b);
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].s16.lo), 0x80000u, blue_b);
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  x_part_c = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
  z_part_c = gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
  ir1_c = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
       + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
       + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2_c = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
       + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
       + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3_c = (z_part_c + x_part_c + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_c);
  GTE_SAT16(10, 0x80800000, 0, ir2_c);
  GTE_SAT16(11, 0x400000u, 0, ir3_c);
  mac1_c.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_c.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_c.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = mac1_c;
  gte_regs.data[26] = mac2_c;
  gte_regs.data[27] = mac3_c;
  GTE_SAT16(9, 0x81000000, 0, mac1_c.s32);
  GTE_SAT16(10, 0x80800000, 0, mac2_c.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_c.s32);
  g_base_c = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  b_base_c = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  r_clamped_c = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = mac1_prev_c + ((gte_regs.data[8].s16.hi * r_clamped_c) >> 12);
  gte_regs.data[26].u32 = g_base_c + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base_c)) >> 12);
  mac3_rgb_c.u32 = b_base_c + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base_c)) >> 12);
  gte_regs.data[27] = mac3_rgb_c;
  GTE_SAT16(9, 0x81000000, 0, gte_regs.data[25].s32);
  GTE_SAT16(10, 0x80800000, 0, gte_regs.data[26].s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_rgb_c.s32);
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green_c = gte_regs.data[26].s32 >> 4;
  blue_c = mac3_rgb_c.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = gte_regs.data[25].s32 >> 4;
  gte_color_g = gte_regs.data[26].s32 >> 4;
  gte_color_b = blue_c;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, gte_regs.data[25].s32 >> 4);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green_c);
  GTE_RGB_B_SAT_DCPL(blue_c, blue_c);
  return blue_c;
}

static GTE_REG gte_dpct()
{
  GTE_REG rgb_fifo;
  int g_base;
  int b_base;
  int r_clamped;
  int mac1_prev;
  int b_clamped;
  GTE_REG mac3;
  int32_t green;
  int32_t blue;
  int r_diff;
  int count;

  LOBYTE(rgb_fifo.u16.hi) = gte_regs.data[20].u16.hi;
  count = 3;
  do
  {
    r_diff = gte_regs.ctrl[21].u32 - 16 * LOBYTE(rgb_fifo.u32);
    g_base = 16 * HIBYTE(gte_regs.data[20].u16.hi);
    b_base = 16 * LOBYTE(gte_regs.data[20].s16.lo);
    r_clamped = gte_clamp(-2130706432, r_diff);
    gte_regs.data[25].u32 = mac1_prev + ((gte_regs.data[8].s16.hi * r_clamped) >> 12);
    gte_regs.data[26].u32 = g_base + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base)) >> 12);
    b_clamped = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base);
    rgb_fifo = gte_regs.data[21];
    mac3.u32 = b_base + ((gte_regs.data[8].s16.hi * b_clamped) >> 12);
    gte_regs.data[21].u32 = gte_regs.data[22].u32;
    green = gte_regs.data[26].s32 >> 4;
    blue = mac3.s32 >> 4;
    gte_regs.data[27] = mac3;
    gte_regs.data[20] = rgb_fifo;
    gte_color_r = gte_regs.data[25].s32 >> 4;
    gte_color_g = gte_regs.data[26].s32 >> 4;
    gte_color_b = mac3.s32 >> 4;
    if ( gte_regs.data[25].s32 >> 4 >= 0 )
    {
      if ( gte_regs.data[25].s32 >> 4 <= 255 )
      {
        LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
      }
      else
      {
        gte_regs.ctrl[31].u32 |= 0x200000u;
        LOBYTE(gte_regs.data[22].u16.hi) = -1;
      }
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = 0;
    }
    if ( green >= 0 )
    {
      if ( green <= 255 )
      {
        HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
      }
      else
      {
        gte_regs.ctrl[31].u32 |= 0x100000u;
        HIBYTE(gte_regs.data[22].u16.hi) = -1;
      }
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = 0;
    }
    if ( blue >= 0 )
    {
      if ( blue <= 255 )
      {
        LOBYTE(gte_regs.data[22].s16.lo) = mac3.s32 >> 4;
      }
      else
      {
        gte_regs.ctrl[31].u32 |= 0x80000u;
        LOBYTE(gte_regs.data[22].s16.lo) = -1;
      }
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = 0;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
    --count;
  }
  while ( count );
  GTE_SAT16(9, 0x81000000, -32768, gte_regs.data[25].s32);
  GTE_SAT16(10, 0x80800000, -32768, gte_regs.data[26].s32);
  GTE_SAT16(11, 0x400000u, -32768, mac3.s32);
  return mac3;
}

static char gte_nccs()
{
  int z_part;
  int ir1;
  int ir2;
  int ir3;
  signed int mac1;
  GTE_REG mac2;
  GTE_REG mac3;
  int r_base;
  int g_base;
  int b_base;
  int red;
  int green;
  int blue;

  z_part = gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
  ir1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3 = (z_part + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1);
  GTE_SAT16(10, 0x80800000, 0, ir2);
  GTE_SAT16(11, 0x400000u, 0, ir3);
  mac1 = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  GTE_SAT16(9, 0x81000000, 0, mac1);
  GTE_SAT16(10, 0x80800000, 0, mac2.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3.s32);
  r_base = (gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8;
  gte_regs.data[25].u32 = r_base;
  g_base = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  gte_regs.data[26].u32 = g_base;
  b_base = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  gte_regs.data[27].u32 = b_base;
  GTE_SAT16(9, 0x81000000, 0, r_base);
  GTE_SAT16(10, 0x80800000, 0, g_base);
  GTE_SAT16(11, 0x400000u, 0, b_base);
  red = r_base >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = g_base >> 4;
  blue = b_base >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = red;
  gte_color_g = green;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, red);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_NCS(red, blue);
  return red;
}

static char gte_ncct()
{
  int part_a;
  int ir1_a;
  int ir2_a;
  int ir3_a;
  signed int mac1_a;
  GTE_REG mac2_a;
  GTE_REG mac3_a;
  int r_base_a;
  int g_base_a;
  int b_base_a;
  int part_b;
  int ir1_b;
  int ir2_b;
  int ir3_b;
  signed int mac1_b;
  GTE_REG mac2_b;
  GTE_REG mac3_b;
  int r_base_b;
  int g_base_b;
  int b_base_b;
  int part_c;
  int ir1_c;
  int ir2_c;
  int ir3_c;
  signed int mac1_c;
  GTE_REG mac2_c;
  GTE_REG mac3_c;
  int r_base_c;
  int g_base_c;
  int b_base_c;
  int red;
  int green;
  int blue;
  char code;

  part_a = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
  ir1_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  ir2_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  ir3_a = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi + part_a + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_a);
  GTE_SAT16(10, 0x80800000, 0, ir2_a);
  GTE_SAT16(11, 0x400000u, 0, ir3_a);
  mac1_a = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_a.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_a.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  GTE_SAT16(9, 0x81000000, 0, mac1_a);
  GTE_SAT16(10, 0x80800000, 0, mac2_a.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_a.s32);
  r_base_a = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
  g_base_a = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
  b_base_a = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, r_base_a);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, g_base_a);
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].s16.lo), 0x80000u, b_base_a);
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  part_b = gte_regs.ctrl[10].s16.lo * gte_regs.data[3].s16.hi;
  ir1_b = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  ir2_b = (part_b + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
  ir3_b = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_b);
  GTE_SAT16(10, 0x80800000, 0, ir2_b);
  GTE_SAT16(11, 0x400000u, 0, ir3_b);
  mac1_b = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_b.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_b.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  GTE_SAT16(9, 0x81000000, 0, mac1_b);
  GTE_SAT16(10, 0x80800000, 0, mac2_b.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_b.s32);
  r_base_b = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
  g_base_b = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
  b_base_b = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, r_base_b);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, g_base_b);
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].s16.lo), 0x80000u, b_base_b);
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  part_c = gte_regs.ctrl[10].s16.lo * gte_regs.data[5].s16.hi;
  ir1_c = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  ir2_c = (part_c + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
  ir3_c = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  GTE_SAT16(9, 0x81000000, 0, ir1_c);
  GTE_SAT16(10, 0x80800000, 0, ir2_c);
  GTE_SAT16(11, 0x400000u, 0, ir3_c);
  mac1_c = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2_c.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3_c.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  GTE_SAT16(9, 0x81000000, 0, mac1_c);
  GTE_SAT16(10, 0x80800000, 0, mac2_c.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_c.s32);
  r_base_c = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 8;
  g_base_c = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 8;
  b_base_c = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 8;
  gte_regs.data[25].u32 = r_base_c;
  gte_regs.data[26].u32 = g_base_c;
  gte_regs.data[27].u32 = b_base_c;
  if ( r_base_c >= 0 )
  {
    if ( r_base_c <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 8;
    }
    else
    {
      HIBYTE(gte_regs.ctrl[31].u32) |= 0x81u;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    HIBYTE(gte_regs.ctrl[31].u32) |= 0x81u;
    gte_regs.data[9].u32 = 0;
  }
  GTE_SAT16(10, 0x80800000, 0, g_base_c);
  GTE_SAT16(11, 0x400000u, 0, b_base_c);
  red = r_base_c >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = g_base_c >> 4;
  blue = b_base_c >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = red;
  gte_color_g = green;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, red);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_RESULT(code, blue);
  return code;
}

static char gte_cdp()
{
  GTE_REG mac1;
  GTE_REG mac2;
  GTE_REG mac3;
  int g_base;
  int b_base;
  int r_clamped;
  int mac1_prev;
  GTE_REG mac3_rgb;
  int32_t green;
  int blue;

  mac1.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = mac1;
  gte_regs.data[26] = mac2;
  gte_regs.data[27] = mac3;
  GTE_SAT16(9, 0x81000000, 0, mac1.s32);
  GTE_SAT16(10, 0x80800000, 0, mac2.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3.s32);
  g_base = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  b_base = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  r_clamped = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = mac1_prev + ((gte_regs.data[8].s16.hi * r_clamped) >> 12);
  gte_regs.data[26].u32 = g_base + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - g_base)) >> 12);
  mac3_rgb.u32 = b_base + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - b_base)) >> 12);
  gte_regs.data[27] = mac3_rgb;
  GTE_SAT16(9, 0x81000000, 0, gte_regs.data[25].s32);
  GTE_SAT16(10, 0x80800000, 0, gte_regs.data[26].s32);
  GTE_SAT16(11, 0x400000u, 0, mac3_rgb.s32);
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = gte_regs.data[26].s32 >> 4;
  blue = mac3_rgb.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = gte_regs.data[25].s32 >> 4;
  gte_color_g = gte_regs.data[26].s32 >> 4;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, gte_regs.data[25].s32 >> 4);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_DCPL(blue, blue);
  return blue;
}

static char gte_cc()
{
  signed int mac1;
  GTE_REG mac2;
  GTE_REG mac3;
  int r_base;
  int g_base;
  int b_base;
  int red;
  int green;
  int blue;

  mac1 = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  mac2.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  mac3.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  GTE_SAT16(9, 0x81000000, 0, mac1);
  GTE_SAT16(10, 0x80800000, 0, mac2.s32);
  GTE_SAT16(11, 0x400000u, 0, mac3.s32);
  r_base = (gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8;
  gte_regs.data[25].u32 = r_base;
  g_base = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  gte_regs.data[26].u32 = g_base;
  b_base = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  gte_regs.data[27].u32 = b_base;
  GTE_SAT16(9, 0x81000000, 0, r_base);
  GTE_SAT16(10, 0x80800000, 0, g_base);
  GTE_SAT16(11, 0x400000u, 0, b_base);
  red = r_base >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  green = g_base >> 4;
  blue = b_base >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_color_r = red;
  gte_color_g = green;
  gte_color_b = blue;
  GTE_RGB_SAT(LOBYTE(gte_regs.data[22].u16.hi), 0x200000u, red);
  GTE_RGB_SAT(HIBYTE(gte_regs.data[22].u16.hi), 0x100000u, green);
  GTE_RGB_B_SAT_NCS(red, blue);
  return red;
}

static int gte_op()
{
  int mac1;
  GTE_REG mac3;
  GTE_REG mac2;

  mac1 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi;
  mac3.u32 = gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.hi - gte_regs.ctrl[2].s16.hi * gte_regs.data[9].s16.hi;
  mac2.u32 = gte_regs.ctrl[4].s16.hi * gte_regs.data[9].s16.hi - gte_regs.data[11].s16.hi * gte_regs.ctrl[0].s16.hi;
  gte_regs.data[25].u32 = mac1;
  gte_regs.data[26] = mac2;
  gte_regs.data[27] = mac3;
  GTE_SAT16(9, 0x81000000, -32768, mac1);
  GTE_SAT16(10, 0x80800000, -32768, mac2.s32);
  if ( mac3.s32 >= (int)-0x8000u )
  {
    if ( mac3.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = mac3;
    }
    else
    {
      gte_regs.data[11].u32 = 0x7FFF;
      mac1 = gte_regs.ctrl[31].u32 | 0x400000;
      gte_regs.ctrl[31].u32 |= 0x400000u;
    }
  }
  else
  {
    gte_regs.data[11].u32 = -0x8000u;
    mac1 = gte_regs.ctrl[31].u32 | 0x400000;
    gte_regs.ctrl[31].u32 |= 0x400000u;
  }
  return mac1;
}

static GTE_REG gte_op_shifted()
{
  GTE_REG mac1;
  int mac2;
  int mac3;

  mac1.u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi) >> 12;
  mac2 = (gte_regs.ctrl[4].s16.hi * gte_regs.data[9].s16.hi - gte_regs.data[11].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
  mac3 = (gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.hi - gte_regs.ctrl[2].s16.hi * gte_regs.data[9].s16.hi) >> 12;
  gte_regs.data[25] = mac1;
  gte_regs.data[26].u32 = mac2;
  gte_regs.data[27].u32 = mac3;
  GTE_SAT16(9, 0x81000000, -32768, mac1.s32);
  GTE_SAT16(10, 0x80800000, -32768, mac2);
  if ( mac3 >= -32768 )
  {
    if ( mac3 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = mac3;
    }
    else
    {
      gte_regs.data[11].u32 = 0x7FFF;
      mac1.u32 = gte_regs.ctrl[31].u32 | 0x400000;
      gte_regs.ctrl[31].u32 |= 0x400000u;
    }
  }
  else
  {
    gte_regs.data[11].u32 = -32768;
    mac1.u32 = gte_regs.ctrl[31].u32 | 0x400000;
    gte_regs.ctrl[31].u32 |= 0x400000u;
  }
  return mac1;
}

static int gte_count_leading_bits(int value)
{
  int abs_value;
  int bit_pos;

  abs_value = value;
  if ( value < 0 )
    abs_value = ~value;
  bit_pos = 31;
  if ( !abs_value )
    return 32;
  if ( abs_value >= 0 )
  {
    do
      --bit_pos;
    while ( ((1 << bit_pos) & abs_value) == 0 );
  }
  return 31 - bit_pos;
}

void gte_exec_opcode()
{
  int b_clamped;
  int flag;
  GTE_REG mac3_intpl;
  int32_t green_intpl;
  GTE_REG mac2_sqrs;
  GTE_REG mac3_sqrs;
  int mac2_sqr;
  int mac3_sqr;
  GTE_REG mac1_gpf;
  GTE_REG mac2_gpf;
  GTE_REG mac3_gpf;
  int green_gpf;
  int blue_gpf;
  int mac1_gpfs;
  int mac2_gpfs;
  int mac3_gpfs;
  int green_gpfs;
  int blue_gpfs;
  GTE_REG mac2_gpl;
  GTE_REG mac3_gpl;
  int green_gpl;
  int blue_gpl;
  GTE_REG mac2_gpls;
  GTE_REG mac3_gpls;
  int green_gpls;
  int blue_gpls;
  unsigned int value;
  uint8_t gpr_index;
  uint8_t data_index;
  uint8_t five_bit;
  int irgb_bits;
  GTE_REG data_value;
  GTE_REG ctrl_value;
  int vz_33;
  int vx_34;
  int vy_35;
  uint32_t mac2a_36;
  int mac2b_37;
  int mac2c_38;
  int mac2;
  GTE_REG trz_40;
  int mac3;
  GTE_REG lm;
  int vz_43;
  int vx_44;
  int vy_45;
  uint32_t mac2a_46;
  int mac2b_47;
  int mac2c_48;
  GTE_REG trz_49;
  int mac3a_50;
  int mac3b_51;
  int mac3c_52;
  int vz_53;
  int vx_54;
  int vy_55;
  int mac2a_56;
  int mac2b_57;
  int vz_58;
  int vx_59;
  int vy_60;
  int mac2a_61;
  int mac2b_62;
  int mac2_s;
  int mac3a_64;
  int mac3b_65;
  int mac3c_66;
  int mac3s_67;
  GTE_REG trz_68;
  int vx_69;
  int vy_70;
  int vz_71;
  int vx_72;
  int vy_73;
  int vz_74;
  GTE_REG trz_75;
  int vx_76;
  int vy_77;
  uint32_t mac2a_78;
  int mac2b_79;
  int mac2c_80;
  int vx_81;
  int vy_82;
  int vz_83;
  uint32_t mac2a_84;
  int mac2b_85;
  int mac2c_86;
  uint32_t mac2a_87;
  int mac2b_88;
  int mac2c_89;
  int vx_90;
  int vy_91;
  int mac2a_92;
  int mac2b_93;
  int vx_94;
  int vy_95;
  int vz_96;
  int mac2a_97;
  int mac2b_98;
  int vx_99;
  int vy_100;
  int vz_101;
  int mac1s_102;
  int mac2a_103;
  int mac2b_104;
  int mac3a_105;
  int mac3b_106;
  int mac3c_107;
  GTE_REG trz_108;
  int vz_109;
  int vx_110;
  int vy_111;
  int mac2a_112;
  int mac2b_113;
  int mac3a_114;
  int mac3b_115;
  int mac3c_116;
  int mac3s_117;
  int vz_118;
  int lo;
  int hi;
  int mac2a_121;
  int mac2b_122;
  int mac3a_123;
  int mac3b_124;
  int mac3c_125;
  int mac3s_126;
  int vz_127;
  int vx_128;
  int vy_129;
  int mac2a_130;
  int mac2b_131;
  int vz_132;
  int vx_133;
  int vy_134;
  int mac2a_135;
  int mac2b_136;
  int mac2s_137;
  int mac3a_138;
  int mac3b_139;
  int mac3c_140;
  int vz_141;
  int vx_142;
  int vy_143;
  int mac2a_144;
  int mac2b_145;
  int mac3a_146;
  int mac3b_147;
  int mac3c_148;
  int mac3s_149;
  int vx_150;
  int vy_151;
  int mac2a_152;
  int mac2b_153;
  int vx_154;
  int vy_155;
  int mac2a_156;
  int mac2b_157;
  int vx_158;
  int vy_159;
  int mac2a_160;
  int mac2b_161;
  int vx_162;
  int vy_163;
  int mac2a_164;
  int mac2b_165;
  int vx_166;
  int vy_167;
  int mac2a_168;
  int mac2b_169;
  int vx_170;
  int vy_171;
  int vz_172;
  int mac2a_173;
  int mac2b_174;
  int vx_175;
  int vy_176;
  int mac2a_177;
  int mac2b_178;
  int vx_179;
  int vy_180;
  int mac2a_181;
  int mac2b_182;
  int mac2_s2;
  int mac2_s3;

  LOBYTE(value) = cpu_opcode;
  switch ( ((unsigned int)cpu_opcode >> 21) & 0x1F )
  {
    case 0u:
      gpr_index = BYTE2(cpu_opcode) & 0x1F;
      data_index = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      gte_cpu_gpr_index = BYTE2(cpu_opcode) & 0x1F;
      gte_data_reg_index = data_index;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        if ( data_index == 31 )
        {
          value = (uint8_t)gte_count_leading_bits(gte_regs.data[30].s32);
          cpu_gpr[gpr_index] = value;
        }
        else
        {
          if ( data_index == 29 )
          {
            gte_convert_to_5bit(gte_regs.data[11].u16.hi);
            gte_convert_to_5bit(gte_regs.data[10].u16.hi);
            five_bit = gte_convert_to_5bit(gte_regs.data[9].u16.hi);
            gpr_index = gte_cpu_gpr_index;
            gte_regs.data[29].u32 = five_bit | irgb_bits;
          }
          LOBYTE(value) = gpr_index;
          cpu_gpr[gpr_index] = gte_regs.data[data_index].s32;
        }
      }
      return;
    case 2u:
      LOBYTE(value) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      gte_cpu_gpr_index = BYTE2(cpu_opcode) & 0x1F;
      gte_control_reg_index = value;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        value = BYTE2(cpu_opcode) & 0x1F;
        cpu_gpr[value] = gte_regs.ctrl[(uint16_t)cpu_opcode >> 11].s32;
      }
      return;
    case 4u:
      LOBYTE(value) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      gte_cpu_gpr_index = BYTE2(cpu_opcode) & 0x1F;
      gte_data_reg_index = value;
      data_value.u32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      gte_regs.data[(uint8_t)value] = data_value;
      if ( (uint8_t)value >= 0x10u && (uint8_t)value <= 0x13u )
        gte_regs.data[(uint8_t)value].u32 = data_value.u16.hi;
      switch ( (uint8_t)value )
      {
        case 0xE:
          gte_regs.data[15] = data_value;
          break;
        case 0xF:
          LOBYTE(value) = gte_regs.data[13].u16.hi;
          gte_regs.data[12].u32 = gte_regs.data[13].u32;
          gte_regs.data[13].u32 = gte_regs.data[14].u32;
          gte_regs.data[14] = data_value;
          break;
        case 0x1C:
          value = (gte_regs.data[28].u16.hi >> 3) & 0xF80;
          gte_regs.data[9].u32 = (gte_regs.data[28].u16.hi & 0x1F) << 7;
          gte_regs.data[10].u32 = 4 * (gte_regs.data[28].u16.hi & 0x3E0);
          gte_regs.data[11].u32 = value;
          break;
      }
      return;
    case 6u:
      LOBYTE(value) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      gte_cpu_gpr_index = BYTE2(cpu_opcode) & 0x1F;
      ctrl_value.u32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      gte_control_reg_index = value;
      gte_regs.ctrl[(uint8_t)value] = ctrl_value;
      return;
    default:
      value = cpu_opcode & 0x1FFFFFF;
      gte_regs.ctrl[31].u32 = 0;
      if ( (cpu_opcode & 0x1FFFFFFu) <= 0x48A412 )
      {
        if ( value == 4760594 )
        {
          lo = gte_regs.data[2].s16.lo;
          hi = gte_regs.data[2].s16.hi;
          vz_118 = gte_regs.data[3].s16.hi;
          value = gte_regs.ctrl[13].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          mac2a_121 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          mac2b_122 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_314;
        }
        if ( value <= 0x432012 )
        {
          if ( value == 4399122 )
          {
            value = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
            mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
            mac3 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[15].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
            lm.u32 = -32768;
            goto LABEL_56;
          }
          if ( value <= 0x416012 )
          {
            if ( value == 4284434 )
            {
              vx_59 = gte_regs.data[4].s16.lo;
              vy_60 = gte_regs.data[4].s16.hi;
              vz_58 = gte_regs.data[5].s16.hi;
              value = gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi;
              mac2a_61 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
              mac2b_62 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_80;
            }
            if ( value <= 0x408012 )
            {
              if ( value == 4227090 )
              {
                vx_34 = gte_regs.data[2].s16.lo;
                vy_35 = gte_regs.data[2].s16.hi;
                vz_33 = gte_regs.data[3].s16.hi;
                value = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                mac2a_36 = gte_regs.ctrl[6].u32 + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi;
                mac2b_37 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                mac2c_38 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_43;
              }
              if ( value <= 0x400412 )
              {
                if ( value != 0x400412 )
                {
                  if ( value <= 0x198001 )
                  {
                    if ( value == 0x198001 )
                      goto LABEL_37;
                    if ( value != 0x140006 )
                    {
                      if ( value != 0x180001 )
                      {
                        if ( value != 0x18041B )
                          goto LABEL_630;
LABEL_602:
                        LOBYTE(value) = gte_nccs();
                        return;
                      }
LABEL_37:
                      LOBYTE(value) = gte_rtps();
                      return;
                    }
LABEL_612:
                    value = gte_regs.data[14].s16.hi * (gte_regs.data[12].s16.lo - gte_regs.data[13].s16.lo);
                    gte_regs.data[24].u32 = value
                                          + gte_regs.data[13].s16.hi
                                          * (gte_regs.data[14].s16.lo - gte_regs.data[12].s16.lo)
                                          + gte_regs.data[12].s16.hi
                                          * (gte_regs.data[13].s16.lo - gte_regs.data[14].s16.lo);
                    return;
                  }
                  if ( value == 0x280030 )
                  {
                    LOBYTE(value) = gte_rtpt();
                    return;
                  }
                  if ( value == 0x400006 )
                    goto LABEL_612;
                  if ( value != 0x400012 )
                    goto LABEL_630;
                  vz_33 = gte_regs.data[1].s16.hi;
                  vx_34 = gte_regs.data[0].s16.lo;
                  vy_35 = gte_regs.data[0].s16.hi;
                  goto LABEL_42;
                }
                vz_43 = gte_regs.data[1].s16.hi;
                vx_44 = gte_regs.data[0].s16.lo;
                vy_45 = gte_regs.data[0].s16.hi;
LABEL_52:
                value = vy_45 * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + vx_44 * gte_regs.ctrl[0].s16.lo
                    + vz_43 * gte_regs.ctrl[1].s16.hi;
                mac2a_46 = gte_regs.ctrl[6].u32 + vy_45 * gte_regs.ctrl[1].s16.lo;
                mac2b_47 = vz_43 * gte_regs.ctrl[2].s16.lo;
                mac2c_48 = vx_44 * gte_regs.ctrl[2].s16.hi;
LABEL_53:
                mac2 = mac2b_47 + mac2a_46 + mac2c_48;
                trz_49 = gte_regs.ctrl[7];
LABEL_54:
                mac3a_50 = vy_45 * gte_regs.ctrl[3].s16.hi;
                mac3b_51 = vx_44 * gte_regs.ctrl[3].s16.lo;
                mac3c_52 = gte_regs.ctrl[4].s16.hi;
LABEL_55:
                mac3 = mac3a_50 + trz_49.u32 + mac3b_51 + vz_43 * mac3c_52;
                lm.u32 = 0;
                goto LABEL_56;
              }
              if ( value <= 0x404412 )
              {
                if ( value != 0x404412 )
                {
                  if ( value == 0x402012 )
                  {
                    vx_34 = gte_regs.data[0].s16.lo;
                    vy_35 = gte_regs.data[0].s16.hi;
                    vz_33 = gte_regs.data[1].s16.hi;
                    value = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                    mac2 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                    trz_40 = gte_regs.ctrl[15];
                    goto LABEL_44;
                  }
                  if ( value != 4203538 )
                  {
                    if ( value != 4210706 )
                      goto LABEL_630;
                    vx_34 = gte_regs.data[0].s16.lo;
                    vy_35 = gte_regs.data[0].s16.hi;
                    vz_33 = gte_regs.data[1].s16.hi;
                    value = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                    mac2 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                    trz_40 = gte_regs.ctrl[23];
                    goto LABEL_44;
                  }
                  vx_44 = gte_regs.data[0].s16.lo;
                  vy_45 = gte_regs.data[0].s16.hi;
                  vz_43 = gte_regs.data[1].s16.hi;
                  value = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                  mac2 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                  trz_49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                vz_43 = gte_regs.data[1].s16.hi;
                vx_44 = gte_regs.data[0].s16.lo;
                vy_45 = gte_regs.data[0].s16.hi;
                goto LABEL_138;
              }
              if ( value != 4218898 )
              {
                if ( value != 4219922 )
                  goto LABEL_630;
                vz_53 = gte_regs.data[1].s16.hi;
                vx_54 = gte_regs.data[0].s16.lo;
                vy_55 = gte_regs.data[0].s16.hi;
                goto LABEL_72;
              }
              vz_58 = gte_regs.data[1].s16.hi;
              vx_59 = gte_regs.data[0].s16.lo;
              vy_60 = gte_regs.data[0].s16.hi;
              goto LABEL_79;
            }
            if ( value > 0x40E412 )
            {
              if ( value > 0x412412 )
              {
                if ( value == 4276242 )
                {
                  vx_34 = gte_regs.data[4].s16.lo;
                  vy_35 = gte_regs.data[4].s16.hi;
                  vz_33 = gte_regs.data[5].s16.hi;
                  value = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                  mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  trz_40 = gte_regs.ctrl[23];
                  goto LABEL_44;
                }
                if ( value != 4277266 )
                  goto LABEL_630;
                vx_44 = gte_regs.data[4].s16.lo;
                vy_45 = gte_regs.data[4].s16.hi;
                vz_43 = gte_regs.data[5].s16.hi;
                value = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[22].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                trz_49 = gte_regs.ctrl[23];
                goto LABEL_54;
              }
              if ( value == 4269074 )
              {
                vx_44 = gte_regs.data[4].s16.lo;
                vy_45 = gte_regs.data[4].s16.hi;
                vz_43 = gte_regs.data[5].s16.hi;
                value = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                trz_49 = gte_regs.ctrl[15];
                goto LABEL_54;
              }
              if ( value == 4259858 )
              {
                vx_34 = gte_regs.data[4].s16.lo;
                vy_35 = gte_regs.data[4].s16.hi;
                vz_33 = gte_regs.data[5].s16.hi;
                value = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                mac2a_36 = gte_regs.ctrl[6].u32 + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi;
                mac2b_37 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                mac2c_38 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_43;
              }
              if ( value != 4260882 )
              {
                if ( value != 4268050 )
                  goto LABEL_630;
                vx_34 = gte_regs.data[4].s16.lo;
                vy_35 = gte_regs.data[4].s16.hi;
                vz_33 = gte_regs.data[5].s16.hi;
                value = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                trz_40 = gte_regs.ctrl[15];
                goto LABEL_44;
              }
              vx_44 = gte_regs.data[4].s16.lo;
              vy_45 = gte_regs.data[4].s16.hi;
              vz_43 = gte_regs.data[5].s16.hi;
              value = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
              mac2a_46 = gte_regs.ctrl[6].u32 + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi;
              mac2b_47 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
              mac2c_48 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_53;
            }
            if ( value != 4252690 )
            {
              if ( value <= 0x40C012 )
              {
                if ( value == 4243474 )
                {
                  vx_34 = gte_regs.data[2].s16.lo;
                  vy_35 = gte_regs.data[2].s16.hi;
                  vz_33 = gte_regs.data[3].s16.hi;
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                  mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  trz_40 = gte_regs.ctrl[23];
                  goto LABEL_44;
                }
                if ( value != 4228114 )
                {
                  if ( value == 4235282 )
                  {
                    vx_34 = gte_regs.data[2].s16.lo;
                    vy_35 = gte_regs.data[2].s16.hi;
                    vz_33 = gte_regs.data[3].s16.hi;
                    value = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                    mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                    trz_40 = gte_regs.ctrl[15];
                    goto LABEL_44;
                  }
                  if ( value != 4236306 )
                    goto LABEL_630;
                  vx_44 = gte_regs.data[2].s16.lo;
                  vy_45 = gte_regs.data[2].s16.hi;
                  vz_43 = gte_regs.data[3].s16.hi;
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                  mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  trz_49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                vx_44 = gte_regs.data[2].s16.lo;
                vy_45 = gte_regs.data[2].s16.hi;
                vz_43 = gte_regs.data[3].s16.hi;
                value = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                mac2a_46 = gte_regs.ctrl[6].u32 + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi;
                mac2b_47 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                mac2c_48 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_53;
              }
              if ( value == 4244498 )
              {
                vx_44 = gte_regs.data[2].s16.lo;
                vy_45 = gte_regs.data[2].s16.hi;
                vz_43 = gte_regs.data[3].s16.hi;
                value = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[22].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                trz_49 = gte_regs.ctrl[23];
                goto LABEL_54;
              }
              if ( value != 4251666 )
                goto LABEL_630;
              vx_59 = gte_regs.data[2].s16.lo;
              vy_60 = gte_regs.data[2].s16.hi;
              vz_58 = gte_regs.data[3].s16.hi;
              value = gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi;
              mac2a_61 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
              mac2b_62 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_80;
            }
            vz_53 = gte_regs.data[3].s16.hi;
            vx_54 = gte_regs.data[2].s16.lo;
            vy_55 = gte_regs.data[2].s16.hi;
LABEL_98:
            value = vz_53 * gte_regs.ctrl[1].s16.hi + vx_54 * gte_regs.ctrl[0].s16.lo + vy_55 * gte_regs.ctrl[0].s16.hi;
            mac2a_56 = vx_54 * gte_regs.ctrl[2].s16.hi + vy_55 * gte_regs.ctrl[1].s16.lo;
            mac2b_57 = vz_53 * gte_regs.ctrl[2].s16.lo;
            goto LABEL_99;
          }
          if ( value <= 0x424012 )
          {
            if ( value == 4341778 )
            {
              value = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
              mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[22].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
              mac3 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                  + gte_regs.ctrl[23].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
              lm.u32 = -32768;
            }
            else
            {
              if ( value <= 0x41C412 )
              {
                if ( value == 4310034 )
                {
                  vz_43 = gte_regs.data[11].s16.hi;
                  vx_44 = gte_regs.data[10].s16.hi;
                  vy_45 = gte_regs.data[9].s16.hi;
LABEL_138:
                  value = vy_45 * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + vx_44 * gte_regs.ctrl[0].s16.lo
                      + vz_43 * gte_regs.ctrl[1].s16.hi;
                  mac2 = vz_43 * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[22].u32
                      + vy_45 * gte_regs.ctrl[1].s16.lo
                      + vx_44 * gte_regs.ctrl[2].s16.hi;
                  trz_49 = gte_regs.ctrl[23];
                  goto LABEL_54;
                }
                if ( value > 0x41A012 )
                {
                  if ( value != 4301842 )
                  {
                    if ( value != 4309010 )
                      goto LABEL_630;
                    vx_34 = gte_regs.data[10].s16.hi;
                    vy_35 = gte_regs.data[9].s16.hi;
                    vz_33 = gte_regs.data[11].s16.hi;
                    value = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                    mac2 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                    trz_40 = gte_regs.ctrl[23];
                    goto LABEL_44;
                  }
                  vx_44 = gte_regs.data[10].s16.hi;
                  vy_45 = gte_regs.data[9].s16.hi;
                  vz_43 = gte_regs.data[11].s16.hi;
                  value = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                  mac2 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                  trz_49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                if ( value == 4300818 )
                {
                  vx_34 = gte_regs.data[10].s16.hi;
                  vy_35 = gte_regs.data[9].s16.hi;
                  vz_33 = gte_regs.data[11].s16.hi;
                  value = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                  mac2 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                  trz_40 = gte_regs.ctrl[15];
                  goto LABEL_44;
                }
                if ( value != 4285458 )
                {
                  if ( value == 4292626 )
                  {
                    vz_33 = gte_regs.data[11].s16.hi;
                    vx_34 = gte_regs.data[10].s16.hi;
                    vy_35 = gte_regs.data[9].s16.hi;
LABEL_42:
                    value = vy_35 * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[5].u32
                        + vx_34 * gte_regs.ctrl[0].s16.lo
                        + vz_33 * gte_regs.ctrl[1].s16.hi;
                    mac2a_36 = gte_regs.ctrl[6].u32 + vy_35 * gte_regs.ctrl[1].s16.lo;
                    mac2b_37 = vz_33 * gte_regs.ctrl[2].s16.lo;
                    mac2c_38 = vx_34 * gte_regs.ctrl[2].s16.hi;
LABEL_43:
                    mac2 = mac2b_37 + mac2a_36 + mac2c_38;
                    trz_40 = gte_regs.ctrl[7];
LABEL_44:
                    mac3 = vy_35 * gte_regs.ctrl[3].s16.hi
                        + trz_40.u32
                        + vx_34 * gte_regs.ctrl[3].s16.lo
                        + vz_33 * gte_regs.ctrl[4].s16.hi;
                    lm.u32 = -32768;
                    goto LABEL_56;
                  }
                  if ( value != 4293650 )
                    goto LABEL_630;
                  vz_43 = gte_regs.data[11].s16.hi;
                  vx_44 = gte_regs.data[10].s16.hi;
                  vy_45 = gte_regs.data[9].s16.hi;
                  goto LABEL_52;
                }
                vz_53 = gte_regs.data[5].s16.hi;
                vx_54 = gte_regs.data[4].s16.lo;
                vy_55 = gte_regs.data[4].s16.hi;
                goto LABEL_98;
              }
              if ( value > 0x420412 )
              {
                if ( value != 4333586 )
                {
                  if ( value != 4334610 )
                    goto LABEL_630;
                  vz_43 = gte_regs.data[1].s16.hi;
                  value = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                  mac3a_50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                  mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                  mac3b_51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                  trz_49 = gte_regs.ctrl[15];
                  mac3c_52 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_55;
                }
                value = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                mac3 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                    + gte_regs.ctrl[15].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
                lm.u32 = -32768;
              }
              else
              {
                switch ( value )
                {
                  case 0x420412u:
                    vz_43 = gte_regs.data[1].s16.hi;
                    value = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[5].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                    mac3a_50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                    mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[6].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                    mac3b_51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                    trz_49 = gte_regs.ctrl[7];
                    mac3c_52 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_55;
                  case 0x41E012u:
                    vz_58 = gte_regs.data[11].s16.hi;
                    vx_59 = gte_regs.data[10].s16.hi;
                    vy_60 = gte_regs.data[9].s16.hi;
LABEL_79:
                    value = vz_58 * gte_regs.ctrl[1].s16.hi + vx_59 * gte_regs.ctrl[0].s16.lo + vy_60 * gte_regs.ctrl[0].s16.hi;
                    mac2a_61 = vy_60 * gte_regs.ctrl[1].s16.lo + vz_58 * gte_regs.ctrl[2].s16.lo;
                    mac2b_62 = vx_59 * gte_regs.ctrl[2].s16.hi;
LABEL_80:
                    mac2 = mac2b_62 + mac2a_61;
                    mac3 = vz_58 * gte_regs.ctrl[4].s16.hi + vx_59 * gte_regs.ctrl[3].s16.lo + vy_60 * gte_regs.ctrl[3].s16.hi;
                    lm.u32 = -32768;
                    goto LABEL_56;
                  case 0x41E412u:
                    vz_53 = gte_regs.data[11].s16.hi;
                    vx_54 = gte_regs.data[10].s16.hi;
                    vy_55 = gte_regs.data[9].s16.hi;
LABEL_72:
                    value = vz_53 * gte_regs.ctrl[1].s16.hi + vx_54 * gte_regs.ctrl[0].s16.lo + vy_55 * gte_regs.ctrl[0].s16.hi;
                    mac2a_56 = vy_55 * gte_regs.ctrl[1].s16.lo + vz_53 * gte_regs.ctrl[2].s16.lo;
                    mac2b_57 = vx_54 * gte_regs.ctrl[2].s16.hi;
LABEL_99:
                    mac2_s = mac2b_57 + mac2a_56;
                    mac3a_64 = vy_55 * gte_regs.ctrl[3].s16.hi;
                    mac3b_65 = vx_54 * gte_regs.ctrl[3].s16.lo;
                    mac3c_66 = gte_regs.ctrl[4].s16.hi;
LABEL_100:
                    mac3s_67 = mac3b_65 + mac3a_64;
                    trz_68.u32 = vz_53 * mac3c_66;
LABEL_101:
                    mac3 = trz_68.u32 + mac3s_67;
                    goto LABEL_102;
                }
                if ( value != 4325394 )
                  goto LABEL_630;
                value = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                mac3 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
                lm.u32 = -32768;
              }
            }
LABEL_56:
            gte_regs.data[25].u32 = value;
            gte_regs.data[26].u32 = mac2;
            gte_regs.data[27].u32 = mac3;
            if ( (int)value >= lm.s32 )
            {
              if ( (int)value <= 0x7FFF )
              {
                gte_regs.data[9].u32 = value;
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9] = lm;
            }
            if ( mac2 >= lm.s32 )
            {
              if ( mac2 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = mac2;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10] = lm;
            }
            if ( mac3 >= lm.s32 )
            {
LABEL_541:
              if ( mac3 <= 0x7FFF )
              {
                gte_regs.data[11].u32 = mac3;
              }
              else
              {
                gte_regs.data[11].u32 = 0x7FFF;
                LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
                gte_regs.ctrl[31].u32 |= 0x400000u;
              }
              return;
            }
LABEL_558:
            gte_regs.data[11] = lm;
            LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
            gte_regs.ctrl[31].u32 |= 0x400000u;
            return;
          }
          if ( value > 0x42A412 )
          {
            if ( value > 0x42E412 )
            {
              if ( value != 4390930 )
              {
                if ( value != 4391954 )
                  goto LABEL_630;
                vz_43 = gte_regs.data[5].s16.hi;
                value = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                mac3a_50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                mac3b_51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                trz_49 = gte_regs.ctrl[7];
                mac3c_52 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_55;
              }
              value = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
              mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
              mac3 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                  + gte_regs.ctrl[7].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
              lm.u32 = -32768;
            }
            else
            {
              switch ( value )
              {
                case 0x42E412u:
                  vz_53 = gte_regs.data[3].s16.hi;
                  value = gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi;
                  mac2_s = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                  mac3a_64 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  mac3b_65 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                  mac3c_66 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_100;
                case 0x42C012u:
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
                  mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
                  mac3 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                      + gte_regs.ctrl[23].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
                  lm.u32 = -32768;
                  break;
                case 0x42C412u:
                  vz_43 = gte_regs.data[3].s16.hi;
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
                  mac3a_50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
                  mac3b_51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                  trz_49 = gte_regs.ctrl[23];
                  mac3c_52 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_55;
                case 0x42E012u:
                  value = gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi;
                  mac2 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                  mac3 = gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  lm.u32 = -32768;
                  break;
                default:
                  goto LABEL_630;
              }
            }
            goto LABEL_56;
          }
          if ( value == 4367378 )
          {
            vz_43 = gte_regs.data[3].s16.hi;
            value = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            mac3a_50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
            mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            mac3b_51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
            trz_49 = gte_regs.ctrl[15];
            mac3c_52 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_55;
          }
          if ( value > 0x428012 )
          {
            if ( value == 4359186 )
            {
              vz_43 = gte_regs.data[3].s16.hi;
              value = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
              mac3a_50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
              mac3b_51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              trz_49 = gte_regs.ctrl[7];
              mac3c_52 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_55;
            }
            if ( value != 4366354 )
              goto LABEL_630;
            value = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            mac3 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[15].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
            lm.u32 = -32768;
            goto LABEL_56;
          }
          if ( value == 4358162 )
          {
            value = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[5].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            mac2 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[6].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            mac3 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[7].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
            lm.u32 = -32768;
            goto LABEL_56;
          }
          if ( value == 4342802 )
          {
            vz_43 = gte_regs.data[1].s16.hi;
            value = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[21].u32
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
            mac3a_50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
            mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[22].u32
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
            mac3b_51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
            trz_49 = gte_regs.ctrl[23];
            mac3c_52 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_55;
          }
          if ( value != 4349970 )
          {
            if ( value != 4350994 )
              goto LABEL_630;
            vz_53 = gte_regs.data[1].s16.hi;
            value = gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi;
            mac2_s = gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo;
            mac3a_64 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
            mac3b_65 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
            mac3c_66 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_100;
          }
          vx_69 = gte_regs.data[0].s16.lo;
          vy_70 = gte_regs.data[0].s16.hi;
          vz_71 = gte_regs.data[1].s16.hi;
          value = gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
              + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
              + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi;
LABEL_214:
          mac2 = vz_71 * gte_regs.ctrl[10].s16.lo + vx_69 * gte_regs.ctrl[10].s16.hi + vy_70 * gte_regs.ctrl[9].s16.lo;
          mac3 = vz_71 * gte_regs.ctrl[12].s16.hi + vx_69 * gte_regs.ctrl[11].s16.lo + vy_70 * gte_regs.ctrl[11].s16.hi;
          lm.u32 = -32768;
          goto LABEL_56;
        }
        if ( value <= 0x44E412 )
        {
          if ( value != 4514834 )
          {
            if ( value <= 0x440412 )
            {
              if ( value != 4457490 )
              {
                if ( value <= 0x43A012 )
                {
                  if ( value == 4431890 )
                  {
                    value = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    mac2 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    mac3 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[15].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    lm.u32 = -32768;
                  }
                  else if ( value > 0x436012 )
                  {
                    if ( value == 4416530 )
                    {
                      vz_53 = gte_regs.data[5].s16.hi;
                      value = gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi;
                      mac2_s = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
                      mac3a_64 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                      mac3b_65 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                      mac3c_66 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_100;
                    }
                    if ( value != 4423698 )
                    {
                      if ( value != 4424722 )
                        goto LABEL_630;
                      vz_43 = gte_regs.data[11].s16.hi;
                      value = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[5].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      mac3a_50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      mac2 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[6].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      mac3b_51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      trz_49 = gte_regs.ctrl[7];
                      mac3c_52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    value = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[5].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    mac2 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[6].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    mac3 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[7].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    lm.u32 = -32768;
                  }
                  else
                  {
                    switch ( value )
                    {
                      case 0x436012u:
                        value = gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi;
                        mac2 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
                        mac3 = gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        lm.u32 = -32768;
                        break;
                      case 0x432412u:
                        vz_43 = gte_regs.data[5].s16.hi;
                        value = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[13].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        mac3a_50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[14].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        mac3b_51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                        trz_49 = gte_regs.ctrl[15];
                        mac3c_52 = gte_regs.ctrl[12].s16.hi;
                        goto LABEL_55;
                      case 0x434012u:
                        value = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[21].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[22].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        mac3 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                            + gte_regs.ctrl[23].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
                        lm.u32 = -32768;
                        break;
                      case 0x434412u:
                        vz_43 = gte_regs.data[5].s16.hi;
                        value = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[21].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        mac3a_50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        mac2 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[22].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        mac3b_51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                        trz_49 = gte_regs.ctrl[23];
                        mac3c_52 = gte_regs.ctrl[12].s16.hi;
                        goto LABEL_55;
                      default:
                        goto LABEL_630;
                    }
                  }
                  goto LABEL_56;
                }
                if ( value <= 0x43E012 )
                {
                  if ( value != 4448274 )
                  {
                    if ( value == 4432914 )
                    {
                      vz_43 = gte_regs.data[11].s16.hi;
                      value = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[13].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      mac3a_50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      mac2 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[14].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      mac3b_51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      trz_49 = gte_regs.ctrl[15];
                      mac3c_52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    if ( value != 4440082 )
                    {
                      if ( value != 4441106 )
                        goto LABEL_630;
                      vz_43 = gte_regs.data[11].s16.hi;
                      value = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[21].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      mac3a_50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      mac2 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[22].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      mac3b_51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      trz_49 = gte_regs.ctrl[23];
                      mac3c_52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    value = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    mac2 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    mac3 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[23].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    lm.u32 = -32768;
                    goto LABEL_56;
                  }
                  vx_69 = gte_regs.data[10].s16.hi;
                  vy_70 = gte_regs.data[9].s16.hi;
                  vz_71 = gte_regs.data[11].s16.hi;
                  value = gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi;
                  goto LABEL_214;
                }
                if ( value == 4449298 )
                {
                  vz_53 = gte_regs.data[11].s16.hi;
                  value = gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi;
                  mac2_s = gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo;
                  mac3a_64 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                  mac3b_65 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                  mac3c_66 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_100;
                }
                if ( value != 4456466 )
                  goto LABEL_630;
                vx_72 = gte_regs.data[0].s16.lo;
                vy_73 = gte_regs.data[0].s16.hi;
                vz_74 = gte_regs.data[1].s16.hi;
                value = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                trz_75 = gte_regs.ctrl[7];
LABEL_282:
                mac3 = vy_73 * gte_regs.ctrl[19].s16.hi
                    + trz_75.u32
                    + vx_72 * gte_regs.ctrl[19].s16.lo
                    + vz_74 * gte_regs.ctrl[20].s16.hi;
                lm.u32 = -32768;
                goto LABEL_56;
              }
              vx_76 = gte_regs.data[0].s16.lo;
              vy_77 = gte_regs.data[0].s16.hi;
              vz_43 = gte_regs.data[1].s16.hi;
              value = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
              mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
              trz_49 = gte_regs.ctrl[7];
LABEL_287:
              mac3a_50 = vy_77 * gte_regs.ctrl[19].s16.hi;
              mac3b_51 = vx_76 * gte_regs.ctrl[19].s16.lo;
              mac3c_52 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_55;
            }
            if ( value <= 0x448012 )
            {
              if ( value == 4489234 )
              {
                value = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                mac2 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                mac3 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                lm.u32 = -32768;
                goto LABEL_56;
              }
              if ( value <= 0x444412 )
              {
                if ( value != 4473874 )
                {
                  if ( value != 4464658 )
                  {
                    if ( value == 4465682 )
                    {
                      vx_76 = gte_regs.data[0].s16.lo;
                      vy_77 = gte_regs.data[0].s16.hi;
                      vz_43 = gte_regs.data[1].s16.hi;
                      value = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                          + gte_regs.ctrl[13].u32
                          + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                          + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                      mac2 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                          + gte_regs.ctrl[14].u32
                          + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                          + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                      trz_49 = gte_regs.ctrl[15];
                      goto LABEL_287;
                    }
                    if ( value != 4472850 )
                      goto LABEL_630;
                    vx_72 = gte_regs.data[0].s16.lo;
                    vy_73 = gte_regs.data[0].s16.hi;
                    vz_74 = gte_regs.data[1].s16.hi;
                    value = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                    mac2a_78 = gte_regs.ctrl[22].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                    mac2b_79 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                    mac2c_80 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_281:
                    mac2 = mac2b_79 + mac2a_78 + mac2c_80;
                    trz_75 = gte_regs.ctrl[23];
                    goto LABEL_282;
                  }
                  vx_81 = gte_regs.data[0].s16.lo;
                  vy_82 = gte_regs.data[0].s16.hi;
                  vz_83 = gte_regs.data[1].s16.hi;
                  value = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2a_84 = gte_regs.ctrl[14].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                  mac2b_85 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                  mac2c_86 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_277:
                  mac2 = mac2b_85 + mac2a_84 + mac2c_86;
                  mac3 = vy_82 * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + vx_81 * gte_regs.ctrl[19].s16.lo
                      + vz_83 * gte_regs.ctrl[20].s16.hi;
                  lm.u32 = -32768;
                  goto LABEL_56;
                }
                vx_76 = gte_regs.data[0].s16.lo;
                vy_77 = gte_regs.data[0].s16.hi;
                vz_43 = gte_regs.data[1].s16.hi;
                value = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                mac2a_87 = gte_regs.ctrl[22].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                mac2b_88 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                mac2c_89 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_286:
                mac2 = mac2b_88 + mac2a_87 + mac2c_89;
                trz_49 = gte_regs.ctrl[23];
                goto LABEL_287;
              }
              if ( value != 4481042 )
              {
                if ( value != 4482066 )
                  goto LABEL_630;
                vx_90 = gte_regs.data[0].s16.lo;
                vy_91 = gte_regs.data[0].s16.hi;
                vz_53 = gte_regs.data[1].s16.hi;
                value = gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi;
                mac2a_92 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                mac2b_93 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                goto LABEL_302;
              }
              vx_94 = gte_regs.data[0].s16.lo;
              vy_95 = gte_regs.data[0].s16.hi;
              vz_96 = gte_regs.data[1].s16.hi;
              value = gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi;
              mac2a_97 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              mac2b_98 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_305:
              mac2 = mac2b_98 + mac2a_97;
              mac3 = vz_96 * gte_regs.ctrl[20].s16.hi + vx_94 * gte_regs.ctrl[19].s16.lo + vy_95 * gte_regs.ctrl[19].s16.hi;
              lm.u32 = -32768;
              goto LABEL_56;
            }
            if ( value <= 0x44C012 )
            {
              switch ( value )
              {
                case 0x44C012u:
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  mac3 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[23].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                  lm.u32 = -32768;
                  goto LABEL_56;
                case 0x448412u:
                  vx_76 = gte_regs.data[2].s16.lo;
                  vy_77 = gte_regs.data[2].s16.hi;
                  vz_43 = gte_regs.data[3].s16.hi;
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  trz_49 = gte_regs.ctrl[7];
                  break;
                case 0x44A012u:
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  mac3 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                  lm.u32 = -32768;
                  goto LABEL_56;
                case 0x44A412u:
                  vx_76 = gte_regs.data[2].s16.lo;
                  vy_77 = gte_regs.data[2].s16.hi;
                  vz_43 = gte_regs.data[3].s16.hi;
                  value = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  trz_49 = gte_regs.ctrl[15];
                  break;
                default:
                  goto LABEL_630;
              }
              goto LABEL_287;
            }
            if ( value != 4506642 )
            {
              if ( value != 4513810 )
                goto LABEL_630;
              vx_94 = gte_regs.data[2].s16.lo;
              vy_95 = gte_regs.data[2].s16.hi;
              vz_96 = gte_regs.data[3].s16.hi;
              value = gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi;
              goto LABEL_304;
            }
            vz_43 = gte_regs.data[3].s16.hi;
            vx_76 = gte_regs.data[2].s16.lo;
            vy_77 = gte_regs.data[2].s16.hi;
LABEL_285:
            value = vy_77 * gte_regs.ctrl[16].s16.hi
                + gte_regs.ctrl[21].u32
                + vx_76 * gte_regs.ctrl[16].s16.lo
                + vz_43 * gte_regs.ctrl[17].s16.hi;
            mac2a_87 = gte_regs.ctrl[22].u32 + vz_43 * gte_regs.ctrl[18].s16.lo;
            mac2b_88 = vx_76 * gte_regs.ctrl[18].s16.hi;
            mac2c_89 = vy_77 * gte_regs.ctrl[17].s16.lo;
            goto LABEL_286;
          }
          vx_90 = gte_regs.data[2].s16.lo;
          vy_91 = gte_regs.data[2].s16.hi;
          vz_53 = gte_regs.data[3].s16.hi;
          value = gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi;
LABEL_301:
          mac2a_92 = vz_53 * gte_regs.ctrl[18].s16.lo + vx_90 * gte_regs.ctrl[18].s16.hi;
          mac2b_93 = vy_91 * gte_regs.ctrl[17].s16.lo;
LABEL_302:
          mac2_s = mac2b_93 + mac2a_92;
          mac3a_64 = vy_91 * gte_regs.ctrl[19].s16.hi;
          mac3b_65 = vx_90 * gte_regs.ctrl[19].s16.lo;
          mac3c_66 = gte_regs.ctrl[20].s16.hi;
          goto LABEL_100;
        }
        if ( value <= 0x45C412 )
        {
          if ( value == 4572178 )
          {
            vz_43 = gte_regs.data[11].s16.hi;
            vx_76 = gte_regs.data[10].s16.hi;
            vy_77 = gte_regs.data[9].s16.hi;
            goto LABEL_285;
          }
          if ( value > 0x456012 )
          {
            if ( value > 0x45A012 )
            {
              if ( value == 4563986 )
              {
                vx_76 = gte_regs.data[10].s16.hi;
                vy_77 = gte_regs.data[9].s16.hi;
                vz_43 = gte_regs.data[11].s16.hi;
                value = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
                mac2 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
                trz_49 = gte_regs.ctrl[15];
                goto LABEL_287;
              }
              if ( value != 4571154 )
                goto LABEL_630;
              vx_72 = gte_regs.data[10].s16.hi;
              vy_73 = gte_regs.data[9].s16.hi;
              vz_74 = gte_regs.data[11].s16.hi;
              value = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              mac2a_78 = gte_regs.ctrl[22].u32 + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo;
              mac2b_79 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              mac2c_80 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_281;
            }
            if ( value == 4562962 )
            {
              vx_81 = gte_regs.data[10].s16.hi;
              vy_82 = gte_regs.data[9].s16.hi;
              vz_83 = gte_regs.data[11].s16.hi;
              value = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[13].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              mac2a_84 = gte_regs.ctrl[14].u32 + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo;
              mac2b_85 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              mac2c_86 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_277;
            }
            if ( value != 4547602 )
            {
              if ( value == 4554770 )
              {
                value = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
                mac2 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
                mac3 = gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi;
                lm.u32 = -32768;
                goto LABEL_56;
              }
              if ( value != 4555794 )
                goto LABEL_630;
              vx_76 = gte_regs.data[10].s16.hi;
              vy_77 = gte_regs.data[9].s16.hi;
              vz_43 = gte_regs.data[11].s16.hi;
              value = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              mac2 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              trz_49 = gte_regs.ctrl[7];
              goto LABEL_287;
            }
            vx_90 = gte_regs.data[4].s16.lo;
            vy_91 = gte_regs.data[4].s16.hi;
            vz_53 = gte_regs.data[5].s16.hi;
            value = gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi;
            goto LABEL_301;
          }
          if ( value != 4546578 )
          {
            if ( value <= 0x452412 )
            {
              switch ( value )
              {
                case 0x452412u:
                  vx_76 = gte_regs.data[4].s16.lo;
                  vy_77 = gte_regs.data[4].s16.hi;
                  vz_43 = gte_regs.data[5].s16.hi;
                  value = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  trz_49 = gte_regs.ctrl[15];
                  break;
                case 0x450012u:
                  value = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  mac3 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[7].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
                  lm.u32 = -32768;
                  goto LABEL_56;
                case 0x450412u:
                  vx_76 = gte_regs.data[4].s16.lo;
                  vy_77 = gte_regs.data[4].s16.hi;
                  vz_43 = gte_regs.data[5].s16.hi;
                  value = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  trz_49 = gte_regs.ctrl[7];
                  break;
                case 0x452012u:
                  value = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  mac2 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  mac3 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
                  lm.u32 = -32768;
                  goto LABEL_56;
                default:
                  goto LABEL_630;
              }
              goto LABEL_287;
            }
            if ( value == 4538386 )
            {
              value = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
              mac2 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.ctrl[22].u32
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
              mac3 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                  + gte_regs.ctrl[23].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
              lm.u32 = -32768;
              goto LABEL_56;
            }
            if ( value != 4539410 )
              goto LABEL_630;
            vz_43 = gte_regs.data[5].s16.hi;
            vx_76 = gte_regs.data[4].s16.lo;
            vy_77 = gte_regs.data[4].s16.hi;
            goto LABEL_285;
          }
          vx_94 = gte_regs.data[4].s16.lo;
          vy_95 = gte_regs.data[4].s16.hi;
          vz_96 = gte_regs.data[5].s16.hi;
          value = gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi;
LABEL_304:
          mac2a_97 = vz_96 * gte_regs.ctrl[18].s16.lo + vx_94 * gte_regs.ctrl[18].s16.hi;
          mac2b_98 = vy_95 * gte_regs.ctrl[17].s16.lo;
          goto LABEL_305;
        }
        if ( value <= 0x484012 )
        {
          if ( value == 4734994 )
          {
            value = gte_regs.ctrl[21].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            mac2 = gte_regs.ctrl[22].u32
                + ((gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
            mac3 = gte_regs.ctrl[23].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[4].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[3].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[3].s16.hi) >> 12);
            lm.u32 = -32768;
            goto LABEL_56;
          }
          if ( value <= 0x480412 )
          {
            if ( value != 4719634 )
            {
              if ( value == 4579346 )
              {
                vx_94 = gte_regs.data[10].s16.hi;
                vy_95 = gte_regs.data[9].s16.hi;
                vz_96 = gte_regs.data[11].s16.hi;
                value = gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi;
                goto LABEL_304;
              }
              if ( value == 4580370 )
              {
                vx_90 = gte_regs.data[10].s16.hi;
                vy_91 = gte_regs.data[9].s16.hi;
                vz_53 = gte_regs.data[11].s16.hi;
                value = gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi;
                goto LABEL_301;
              }
              if ( value != 4718610 )
                goto LABEL_630;
              vx_99 = gte_regs.data[0].s16.lo;
              vy_100 = gte_regs.data[0].s16.hi;
              vz_101 = gte_regs.data[1].s16.hi;
              mac1s_102 = gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi;
              goto LABEL_296;
            }
            vz_109 = gte_regs.data[1].s16.hi;
            vx_110 = gte_regs.data[0].s16.lo;
            vy_111 = gte_regs.data[0].s16.hi;
LABEL_307:
            value = gte_regs.ctrl[5].u32
                + ((vz_109 * gte_regs.ctrl[1].s16.hi + vx_110 * gte_regs.ctrl[0].s16.lo + vy_111 * gte_regs.ctrl[0].s16.hi) >> 12);
            mac2a_112 = vy_111 * gte_regs.ctrl[1].s16.lo + vz_109 * gte_regs.ctrl[2].s16.lo;
            mac2b_113 = vx_110 * gte_regs.ctrl[2].s16.hi;
LABEL_308:
            mac2_s = gte_regs.ctrl[6].u32 + ((mac2b_113 + mac2a_112) >> 12);
            mac3a_114 = vy_111 * gte_regs.ctrl[3].s16.hi;
            mac3b_115 = vx_110 * gte_regs.ctrl[3].s16.lo;
            mac3c_116 = gte_regs.ctrl[4].s16.hi;
            goto LABEL_309;
          }
          if ( value == 4726802 )
          {
            value = gte_regs.ctrl[13].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            mac2 = gte_regs.ctrl[14].u32
                + ((gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
            mac3 = gte_regs.ctrl[15].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[4].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[3].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[3].s16.hi) >> 12);
            lm.u32 = -32768;
            goto LABEL_56;
          }
          if ( value != 4727826 )
            goto LABEL_630;
          vz_118 = gte_regs.data[1].s16.hi;
          lo = gte_regs.data[0].s16.lo;
          hi = gte_regs.data[0].s16.hi;
          goto LABEL_313;
        }
        if ( value > 0x488012 )
        {
          if ( value != 4752402 )
          {
            if ( value != 4759570 )
              goto LABEL_630;
            vz_101 = gte_regs.data[3].s16.hi;
            value = gte_regs.ctrl[13].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            trz_108 = gte_regs.ctrl[15];
            mac2 = gte_regs.ctrl[14].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
            mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[3].s16.hi;
            mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[3].s16.lo;
            mac3c_107 = gte_regs.ctrl[4].s16.hi;
            goto LABEL_299;
          }
          vx_110 = gte_regs.data[2].s16.lo;
          vy_111 = gte_regs.data[2].s16.hi;
          vz_109 = gte_regs.data[3].s16.hi;
          value = gte_regs.ctrl[5].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          mac2a_112 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          mac2b_113 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_308;
        }
        if ( value == 4751378 )
        {
          vx_99 = gte_regs.data[2].s16.lo;
          vy_100 = gte_regs.data[2].s16.hi;
          vz_101 = gte_regs.data[3].s16.hi;
          value = gte_regs.ctrl[5].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          mac2a_103 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          mac2b_104 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_297;
        }
        if ( value != 4736018 )
        {
          if ( value != 4743186 )
          {
            if ( value != 4744210 )
              goto LABEL_630;
            vz_127 = gte_regs.data[1].s16.hi;
            vx_128 = gte_regs.data[0].s16.lo;
            vy_129 = gte_regs.data[0].s16.hi;
LABEL_324:
            mac2a_130 = vy_129 * gte_regs.ctrl[1].s16.lo + vz_127 * gte_regs.ctrl[2].s16.lo;
            value = (vz_127 * gte_regs.ctrl[1].s16.hi + vx_128 * gte_regs.ctrl[0].s16.lo + vy_129 * gte_regs.ctrl[0].s16.hi) >> 12;
            mac2b_131 = vx_128 * gte_regs.ctrl[2].s16.hi;
LABEL_325:
            mac2_s = (mac2b_131 + mac2a_130) >> 12;
            mac3 = (vz_127 * gte_regs.ctrl[4].s16.hi + vx_128 * gte_regs.ctrl[3].s16.lo + vy_129 * gte_regs.ctrl[3].s16.hi) >> 12;
            goto LABEL_102;
          }
          vz_132 = gte_regs.data[1].s16.hi;
          vx_133 = gte_regs.data[0].s16.lo;
          vy_134 = gte_regs.data[0].s16.hi;
          goto LABEL_327;
        }
        vz_141 = gte_regs.data[1].s16.hi;
        vx_142 = gte_regs.data[0].s16.lo;
        vy_143 = gte_regs.data[0].s16.hi;
LABEL_331:
        value = gte_regs.ctrl[21].u32
            + ((vz_141 * gte_regs.ctrl[1].s16.hi + vx_142 * gte_regs.ctrl[0].s16.lo + vy_143 * gte_regs.ctrl[0].s16.hi) >> 12);
        mac2a_144 = vy_143 * gte_regs.ctrl[1].s16.lo + vz_141 * gte_regs.ctrl[2].s16.lo;
        mac2b_145 = vx_142 * gte_regs.ctrl[2].s16.hi;
LABEL_332:
        mac2_s = gte_regs.ctrl[22].u32 + ((mac2b_145 + mac2a_144) >> 12);
        mac3a_146 = vy_143 * gte_regs.ctrl[3].s16.hi;
        mac3b_147 = vx_142 * gte_regs.ctrl[3].s16.lo;
        mac3c_148 = gte_regs.ctrl[4].s16.hi;
        goto LABEL_333;
      }
      if ( value <= 0x4C4012 )
      {
        if ( value != 4997138 )
        {
          if ( value <= 0x4A8012 )
          {
            if ( value == 4882450 )
            {
              vz_101 = gte_regs.data[3].s16.hi;
              value = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_298;
            }
            if ( value <= 0x49A012 )
            {
              if ( value == 4825106 )
              {
                vz_101 = gte_regs.data[11].s16.hi;
                value = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                trz_108 = gte_regs.ctrl[15];
                mac2 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
                mac3a_105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[3].s16.hi;
                mac3b_106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[3].s16.lo;
                mac3c_107 = gte_regs.ctrl[4].s16.hi;
                goto LABEL_299;
              }
              if ( value > 0x492412 )
              {
                if ( value > 0x496412 )
                {
                  if ( value == 4816914 )
                  {
                    vx_99 = gte_regs.data[10].s16.hi;
                    vy_100 = gte_regs.data[9].s16.hi;
                    vz_101 = gte_regs.data[11].s16.hi;
                    mac1s_102 = gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                         + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                         + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi;
LABEL_296:
                    value = gte_regs.ctrl[5].u32 + (mac1s_102 >> 12);
                    mac2a_103 = vy_100 * gte_regs.ctrl[1].s16.lo + vz_101 * gte_regs.ctrl[2].s16.lo;
                    mac2b_104 = vx_99 * gte_regs.ctrl[2].s16.hi;
LABEL_297:
                    mac2 = gte_regs.ctrl[6].u32 + ((mac2b_104 + mac2a_103) >> 12);
                    mac3a_105 = vy_100 * gte_regs.ctrl[3].s16.hi;
                    mac3b_106 = vx_99 * gte_regs.ctrl[3].s16.lo;
                    mac3c_107 = gte_regs.ctrl[4].s16.hi;
LABEL_298:
                    trz_108 = gte_regs.ctrl[7];
LABEL_299:
                    mac3 = trz_108.u32 + ((vz_101 * mac3c_107 + mac3b_106 + mac3a_105) >> 12);
                    lm.u32 = -32768;
                    goto LABEL_56;
                  }
                  if ( value != 4817938 )
                    goto LABEL_630;
                  vz_109 = gte_regs.data[11].s16.hi;
                  vx_110 = gte_regs.data[10].s16.hi;
                  vy_111 = gte_regs.data[9].s16.hi;
                  goto LABEL_307;
                }
                if ( value == 4809746 )
                {
                  vx_128 = gte_regs.data[4].s16.lo;
                  vy_129 = gte_regs.data[4].s16.hi;
                  vz_127 = gte_regs.data[5].s16.hi;
                  mac2a_130 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  value = (gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  mac2b_131 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_325;
                }
                if ( value == 4800530 )
                {
                  vz_101 = gte_regs.data[5].s16.hi;
                  value = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  trz_108 = gte_regs.ctrl[23];
                  mac2 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                  mac3a_105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[3].s16.hi;
                  mac3b_106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[3].s16.lo;
                  mac3c_107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
                }
                if ( value != 4801554 )
                {
                  if ( value != 4808722 )
                    goto LABEL_630;
                  vx_133 = gte_regs.data[4].s16.lo;
                  vy_134 = gte_regs.data[4].s16.hi;
                  vz_132 = gte_regs.data[5].s16.hi;
                  mac2a_135 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  value = (gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  mac2b_136 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_328;
                }
                vx_142 = gte_regs.data[4].s16.lo;
                vy_143 = gte_regs.data[4].s16.hi;
                vz_141 = gte_regs.data[5].s16.hi;
                value = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                mac2a_144 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                mac2b_145 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              }
              else
              {
                if ( value == 4793362 )
                {
                  lo = gte_regs.data[4].s16.lo;
                  hi = gte_regs.data[4].s16.hi;
                  vz_118 = gte_regs.data[5].s16.hi;
                  value = gte_regs.ctrl[13].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  mac2a_121 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  mac2b_122 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_314;
                }
                if ( value > 0x48E412 )
                {
                  if ( value == 4784146 )
                  {
                    vx_99 = gte_regs.data[4].s16.lo;
                    vy_100 = gte_regs.data[4].s16.hi;
                    vz_101 = gte_regs.data[5].s16.hi;
                    value = gte_regs.ctrl[5].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                    mac2a_103 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                         + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                    mac2b_104 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                    goto LABEL_297;
                  }
                  if ( value != 4785170 )
                  {
                    if ( value != 4792338 )
                      goto LABEL_630;
                    vz_101 = gte_regs.data[5].s16.hi;
                    value = gte_regs.ctrl[13].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                    trz_108 = gte_regs.ctrl[15];
                    mac2 = gte_regs.ctrl[14].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                    mac3a_105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[3].s16.hi;
                    mac3b_106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[3].s16.lo;
                    mac3c_107 = gte_regs.ctrl[4].s16.hi;
                    goto LABEL_299;
                  }
                  vx_110 = gte_regs.data[4].s16.lo;
                  vy_111 = gte_regs.data[4].s16.hi;
                  vz_109 = gte_regs.data[5].s16.hi;
                  value = gte_regs.ctrl[5].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  mac2a_112 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  mac2b_113 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_308;
                }
                if ( value == 4776978 )
                {
                  vx_128 = gte_regs.data[2].s16.lo;
                  vy_129 = gte_regs.data[2].s16.hi;
                  vz_127 = gte_regs.data[3].s16.hi;
                  mac2a_130 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                  value = (gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  mac2b_131 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_325;
                }
                if ( value == 4767762 )
                {
                  vz_101 = gte_regs.data[3].s16.hi;
                  value = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  trz_108 = gte_regs.ctrl[23];
                  mac2 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                  mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[3].s16.hi;
                  mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[3].s16.lo;
                  mac3c_107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
                }
                if ( value != 4768786 )
                {
                  if ( value != 4775954 )
                    goto LABEL_630;
                  vx_133 = gte_regs.data[2].s16.lo;
                  vy_134 = gte_regs.data[2].s16.hi;
                  vz_132 = gte_regs.data[3].s16.hi;
                  mac2a_135 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                  value = (gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  mac2b_136 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_328;
                }
                vx_142 = gte_regs.data[2].s16.lo;
                vy_143 = gte_regs.data[2].s16.hi;
                vz_141 = gte_regs.data[3].s16.hi;
                value = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                mac2a_144 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                mac2b_145 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
              }
              goto LABEL_332;
            }
            if ( value <= 0x4A0412 )
            {
              if ( value == 4850706 )
              {
                vz_109 = gte_regs.data[1].s16.hi;
                value = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                mac2_s = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_114 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_115 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                mac3c_116 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_309;
              }
              if ( value > 0x49E012 )
              {
                if ( value != 4842514 )
                {
                  if ( value != 4849682 )
                    goto LABEL_630;
                  vz_101 = gte_regs.data[1].s16.hi;
                  value = gte_regs.ctrl[5].u32
                      + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                  mac2 = gte_regs.ctrl[6].u32
                      + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                  mac3a_105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                  mac3b_106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                  mac3c_107 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_298;
                }
                vz_127 = gte_regs.data[11].s16.hi;
                vx_128 = gte_regs.data[10].s16.hi;
                vy_129 = gte_regs.data[9].s16.hi;
                goto LABEL_324;
              }
              switch ( value )
              {
                case 0x49E012u:
                  vz_132 = gte_regs.data[11].s16.hi;
                  vx_133 = gte_regs.data[10].s16.hi;
                  vy_134 = gte_regs.data[9].s16.hi;
LABEL_327:
                  mac2a_135 = vy_134 * gte_regs.ctrl[1].s16.lo + vz_132 * gte_regs.ctrl[2].s16.lo;
                  value = (vz_132 * gte_regs.ctrl[1].s16.hi + vx_133 * gte_regs.ctrl[0].s16.lo
                                                        + vy_134 * gte_regs.ctrl[0].s16.hi) >> 12;
                  mac2b_136 = vx_133 * gte_regs.ctrl[2].s16.hi;
LABEL_328:
                  mac2s_137 = mac2b_136 + mac2a_135;
                  mac3a_138 = vy_134 * gte_regs.ctrl[3].s16.hi;
                  mac3b_139 = vx_133 * gte_regs.ctrl[3].s16.lo;
                  mac3c_140 = gte_regs.ctrl[4].s16.hi;
LABEL_329:
                  mac2 = mac2s_137 >> 12;
                  mac3 = (vz_132 * mac3c_140 + mac3b_139 + mac3a_138) >> 12;
                  lm.u32 = -32768;
                  goto LABEL_56;
                case 0x49A412u:
                  vz_118 = gte_regs.data[11].s16.hi;
                  lo = gte_regs.data[10].s16.hi;
                  hi = gte_regs.data[9].s16.hi;
LABEL_313:
                  value = gte_regs.ctrl[13].u32
                      + ((vz_118 * gte_regs.ctrl[1].s16.hi + lo * gte_regs.ctrl[0].s16.lo + hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  mac2a_121 = hi * gte_regs.ctrl[1].s16.lo + vz_118 * gte_regs.ctrl[2].s16.lo;
                  mac2b_122 = lo * gte_regs.ctrl[2].s16.hi;
LABEL_314:
                  mac2_s = gte_regs.ctrl[14].u32 + ((mac2b_122 + mac2a_121) >> 12);
                  mac3a_123 = hi * gte_regs.ctrl[3].s16.hi;
                  mac3b_124 = lo * gte_regs.ctrl[3].s16.lo;
                  mac3c_125 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_315;
                case 0x49C012u:
                  vz_101 = gte_regs.data[11].s16.hi;
                  value = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  trz_108 = gte_regs.ctrl[23];
                  mac2 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
                  mac3a_105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[3].s16.hi;
                  mac3b_106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[3].s16.lo;
                  mac3c_107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
              }
              if ( value != 4834322 )
                goto LABEL_630;
              vz_141 = gte_regs.data[11].s16.hi;
              vx_142 = gte_regs.data[10].s16.hi;
              vy_143 = gte_regs.data[9].s16.hi;
              goto LABEL_331;
            }
            if ( value <= 0x4A4412 )
            {
              if ( value == 4867090 )
              {
                vz_141 = gte_regs.data[1].s16.hi;
                value = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                mac2_s = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_146 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_147 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                mac3c_148 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_333;
              }
              if ( value == 4857874 )
              {
                vz_101 = gte_regs.data[1].s16.hi;
                value = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                trz_108 = gte_regs.ctrl[15];
                mac2 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                mac3c_107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              if ( value != 4858898 )
              {
                if ( value != 4866066 )
                  goto LABEL_630;
                vz_101 = gte_regs.data[1].s16.hi;
                value = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                trz_108 = gte_regs.ctrl[23];
                mac2 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                mac3c_107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              vz_118 = gte_regs.data[1].s16.hi;
              value = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_123 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_124 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_125 = gte_regs.ctrl[12].s16.hi;
LABEL_315:
              mac3s_126 = vz_118 * mac3c_125 + mac3b_124 + mac3a_123;
              trz_68 = gte_regs.ctrl[15];
              mac3s_67 = mac3s_126 >> 12;
              goto LABEL_101;
            }
            if ( value == 4874258 )
            {
              vz_132 = gte_regs.data[1].s16.hi;
              mac2s_137 = gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo;
              mac3a_138 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
              value = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
              mac3b_139 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_140 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_329;
            }
            if ( value != 4875282 )
              goto LABEL_630;
            value = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
            mac2_s = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
            mac3 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
LABEL_102:
            gte_regs.data[25].u32 = value;
            gte_regs.data[26].u32 = mac2_s;
            gte_regs.data[27].u32 = mac3;
            if ( (value & 0x80000000) == 0 )
            {
              if ( (int)value <= 0x7FFF )
              {
                gte_regs.data[9].u32 = value;
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9].u32 = 0;
            }
            if ( mac2_s >= 0 )
            {
              if ( mac2_s <= 0x7FFF )
              {
                gte_regs.data[10].u32 = mac2_s;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0;
            }
            if ( mac3 >= 0 )
              goto LABEL_541;
LABEL_573:
            LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
            gte_regs.data[11].u32 = 0;
            gte_regs.ctrl[31].u32 |= 0x400000u;
            return;
          }
          if ( value <= 0x4B6012 )
          {
            if ( value == 4939794 )
            {
              vz_132 = gte_regs.data[5].s16.hi;
              mac2s_137 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                   + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
              mac3a_138 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              value = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                   + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
              mac3b_139 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_140 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_329;
            }
            if ( value <= 0x4AE412 )
            {
              if ( value == 4908050 )
              {
                value = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                mac2_s = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                mac3 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              }
              if ( value <= 0x4AC012 )
              {
                switch ( value )
                {
                  case 0x4AC012u:
                    vz_101 = gte_regs.data[3].s16.hi;
                    value = gte_regs.ctrl[21].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    trz_108 = gte_regs.ctrl[23];
                    mac2 = gte_regs.ctrl[22].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    mac3c_107 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_299;
                  case 0x4A8412u:
                    vz_109 = gte_regs.data[3].s16.hi;
                    value = gte_regs.ctrl[5].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    mac2_s = gte_regs.ctrl[6].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    mac3a_114 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    mac3b_115 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    mac3c_116 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_309;
                  case 0x4AA012u:
                    vz_101 = gte_regs.data[3].s16.hi;
                    value = gte_regs.ctrl[13].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    trz_108 = gte_regs.ctrl[15];
                    mac2 = gte_regs.ctrl[14].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    mac3c_107 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_299;
                }
                if ( value != 4891666 )
                  goto LABEL_630;
                vz_118 = gte_regs.data[3].s16.hi;
                value = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                mac2_s = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_123 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_124 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                mac3c_125 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_315;
              }
              if ( value != 4899858 )
              {
                if ( value != 4907026 )
                  goto LABEL_630;
                vz_132 = gte_regs.data[3].s16.hi;
                mac2s_137 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                mac3a_138 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                value = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                mac3b_139 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                mac3c_140 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_329;
              }
              vz_141 = gte_regs.data[3].s16.hi;
              value = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_146 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_147 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_148 = gte_regs.ctrl[12].s16.hi;
LABEL_333:
              mac3s_149 = vz_141 * mac3c_148 + mac3b_147 + mac3a_146;
              trz_68 = gte_regs.ctrl[23];
              mac3s_67 = mac3s_149 >> 12;
              goto LABEL_101;
            }
            if ( value > 0x4B2412 )
            {
              if ( value == 4931602 )
              {
                vz_101 = gte_regs.data[5].s16.hi;
                value = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                trz_108 = gte_regs.ctrl[23];
                mac2 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                mac3c_107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              if ( value != 4932626 )
                goto LABEL_630;
              vz_141 = gte_regs.data[5].s16.hi;
              value = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_146 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_147 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_148 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_333;
            }
            if ( value == 4924434 )
            {
              vz_118 = gte_regs.data[5].s16.hi;
              value = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_123 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_124 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_125 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_315;
            }
            if ( value == 4915218 )
            {
              vz_101 = gte_regs.data[5].s16.hi;
              value = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_298;
            }
            if ( value != 4916242 )
            {
              if ( value != 4923410 )
                goto LABEL_630;
              vz_101 = gte_regs.data[5].s16.hi;
              value = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              trz_108 = gte_regs.ctrl[15];
              mac2 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              mac3c_107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_299;
            }
            vz_109 = gte_regs.data[5].s16.hi;
            value = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
            mac2_s = gte_regs.ctrl[6].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
            mac3a_114 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
            mac3b_115 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
            mac3c_116 = gte_regs.ctrl[12].s16.hi;
LABEL_309:
            mac3s_117 = vz_109 * mac3c_116 + mac3b_115 + mac3a_114;
            trz_68 = gte_regs.ctrl[7];
            mac3s_67 = mac3s_117 >> 12;
            goto LABEL_101;
          }
          if ( value <= 0x4BC412 )
          {
            if ( value == 4965394 )
            {
              vz_141 = gte_regs.data[11].s16.hi;
              value = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_146 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_147 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
              mac3c_148 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_333;
            }
            if ( value > 0x4BA012 )
            {
              if ( value != 4957202 )
              {
                if ( value != 4964370 )
                  goto LABEL_630;
                vz_101 = gte_regs.data[11].s16.hi;
                value = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                trz_108 = gte_regs.ctrl[23];
                mac2 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                mac3c_107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              vz_118 = gte_regs.data[11].s16.hi;
              value = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              mac3a_123 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
              mac3b_124 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
              mac3c_125 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_315;
            }
            switch ( value )
            {
              case 0x4BA012u:
                vz_101 = gte_regs.data[11].s16.hi;
                value = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                trz_108 = gte_regs.ctrl[15];
                mac2 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                mac3c_107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              case 0x4B6412u:
                value = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                mac2_s = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                mac3 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              case 0x4B8012u:
                vz_101 = gte_regs.data[11].s16.hi;
                value = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                mac2 = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                mac3a_105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                mac3b_106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                mac3c_107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_298;
            }
            if ( value != 4949010 )
              goto LABEL_630;
            vz_109 = gte_regs.data[11].s16.hi;
            value = gte_regs.ctrl[5].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
            mac2_s = gte_regs.ctrl[6].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
            mac3a_114 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
            mac3b_115 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
            mac3c_116 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_309;
          }
          if ( value <= 0x4C0412 )
          {
            if ( value != 4981778 )
            {
              if ( value == 4972562 )
              {
                vz_132 = gte_regs.data[11].s16.hi;
                mac2s_137 = gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo;
                mac3a_138 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                value = (gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                mac3b_139 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                mac3c_140 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_329;
              }
              if ( value == 4973586 )
              {
                value = (gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                mac2_s = (gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                mac3 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              }
              if ( value != 4980754 )
                goto LABEL_630;
              vx_150 = gte_regs.data[0].s16.lo;
              vy_151 = gte_regs.data[0].s16.hi;
              vz_101 = gte_regs.data[1].s16.hi;
              value = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2a_152 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              mac2b_153 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_528:
              mac2 = gte_regs.ctrl[6].u32 + ((mac2b_153 + mac2a_152) >> 12);
              mac3a_105 = vy_151 * gte_regs.ctrl[19].s16.hi;
              mac3b_106 = vx_150 * gte_regs.ctrl[19].s16.lo;
              mac3c_107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_298;
            }
            vx_154 = gte_regs.data[0].s16.lo;
            vy_155 = gte_regs.data[0].s16.hi;
            vz_109 = gte_regs.data[1].s16.hi;
            value = gte_regs.ctrl[5].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2a_156 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            mac2b_157 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
            goto LABEL_526;
          }
          if ( (int *)value != (int *)((char *)&spu_ram[93124] + 2) )
          {
            if ( (int *)value != (int *)((char *)&spu_ram[93380] + 2) )
              goto LABEL_630;
            vx_158 = gte_regs.data[0].s16.lo;
            vy_159 = gte_regs.data[0].s16.hi;
            vz_118 = gte_regs.data[1].s16.hi;
            value = gte_regs.ctrl[13].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2a_160 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            mac2b_161 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
            goto LABEL_506;
          }
          vx_162 = gte_regs.data[0].s16.lo;
          vy_163 = gte_regs.data[0].s16.hi;
          vz_101 = gte_regs.data[1].s16.hi;
          value = gte_regs.ctrl[13].u32
              + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
          mac2a_164 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
          mac2b_165 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_530:
          trz_108 = gte_regs.ctrl[15];
          mac2 = gte_regs.ctrl[14].u32 + ((mac2b_165 + mac2a_164) >> 12);
          mac3a_105 = vy_163 * gte_regs.ctrl[19].s16.hi;
          mac3b_106 = vx_162 * gte_regs.ctrl[19].s16.lo;
          mac3c_107 = gte_regs.ctrl[20].s16.hi;
          goto LABEL_299;
        }
        vx_166 = gte_regs.data[0].s16.lo;
        vy_167 = gte_regs.data[0].s16.hi;
        vz_101 = gte_regs.data[1].s16.hi;
        value = gte_regs.ctrl[21].u32
            + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
        mac2a_168 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
        mac2b_169 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_519:
        trz_108 = gte_regs.ctrl[23];
        mac2 = gte_regs.ctrl[22].u32 + ((mac2b_169 + mac2a_168) >> 12);
        mac3a_105 = vy_167 * gte_regs.ctrl[19].s16.hi;
        mac3b_106 = vx_166 * gte_regs.ctrl[19].s16.lo;
        mac3c_107 = gte_regs.ctrl[20].s16.hi;
        goto LABEL_299;
      }
      if ( value <= 0x680029 )
      {
        if ( value == 6815785 )
        {
          LOBYTE(value) = gte_dcpl();
          return;
        }
        if ( value <= 0x4D2412 )
        {
          if ( value == 5055506 )
          {
            vx_158 = gte_regs.data[4].s16.lo;
            vy_159 = gte_regs.data[4].s16.hi;
            vz_118 = gte_regs.data[5].s16.hi;
            value = gte_regs.ctrl[13].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2a_160 = gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi;
            mac2b_161 = gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
LABEL_506:
            mac2_s = gte_regs.ctrl[14].u32 + ((mac2b_161 + mac2a_160) >> 12);
            mac3a_123 = vy_159 * gte_regs.ctrl[19].s16.hi;
            mac3b_124 = vx_158 * gte_regs.ctrl[19].s16.lo;
            mac3c_125 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_315;
          }
          if ( value <= 0x4CC012 )
          {
            if ( value == 5029906 )
            {
              vz_101 = gte_regs.data[3].s16.hi;
              value = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              trz_108 = gte_regs.ctrl[23];
              mac2 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              mac3c_107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_299;
            }
            if ( value > 0x4C8012 )
            {
              if ( value == 5014546 )
              {
                vz_109 = gte_regs.data[3].s16.hi;
                value = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
                mac2_s = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
                mac3a_114 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
                mac3b_115 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
                mac3c_116 = gte_regs.ctrl[20].s16.hi;
                goto LABEL_309;
              }
              if ( value == 5021714 )
              {
                vz_101 = gte_regs.data[3].s16.hi;
                value = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
                trz_108 = gte_regs.ctrl[15];
                mac2 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
                mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
                mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
                mac3c_107 = gte_regs.ctrl[20].s16.hi;
                goto LABEL_299;
              }
              if ( value != 5022738 )
                goto LABEL_630;
              vz_118 = gte_regs.data[3].s16.hi;
              value = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              mac3a_123 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              mac3b_124 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              mac3c_125 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_315;
            }
            if ( value == 5013522 )
            {
              vz_101 = gte_regs.data[3].s16.hi;
              value = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              mac3a_105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              mac3b_106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              mac3c_107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_298;
            }
            if ( value != 4998162 )
            {
              if ( value != 5005330 )
              {
                if ( value != 5006354 )
                  goto LABEL_630;
                vx_170 = gte_regs.data[0].s16.lo;
                vy_171 = gte_regs.data[0].s16.hi;
                vz_172 = gte_regs.data[1].s16.hi;
                mac2a_173 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                     + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                value = (gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                     + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                     + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
                mac2b_174 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                goto LABEL_522;
              }
              vx_175 = gte_regs.data[0].s16.lo;
              vy_176 = gte_regs.data[0].s16.hi;
              vz_132 = gte_regs.data[1].s16.hi;
              mac2a_177 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              value = (gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
              mac2b_178 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_516:
              mac2s_137 = mac2b_178 + mac2a_177;
              mac3a_138 = vy_176 * gte_regs.ctrl[19].s16.hi;
              mac3b_139 = vx_175 * gte_regs.ctrl[19].s16.lo;
              mac3c_140 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_329;
            }
            vx_179 = gte_regs.data[0].s16.lo;
            vy_180 = gte_regs.data[0].s16.hi;
            vz_141 = gte_regs.data[1].s16.hi;
            value = gte_regs.ctrl[21].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2a_181 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            mac2b_182 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_537:
            mac2_s = gte_regs.ctrl[22].u32 + ((mac2b_182 + mac2a_181) >> 12);
            mac3a_146 = vy_180 * gte_regs.ctrl[19].s16.hi;
            mac3b_147 = vx_179 * gte_regs.ctrl[19].s16.lo;
            mac3c_148 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_333;
          }
          if ( value > 0x4D0012 )
          {
            if ( value != 5047314 )
            {
              if ( value != 5054482 )
                goto LABEL_630;
              vz_101 = gte_regs.data[5].s16.hi;
              value = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              trz_108 = gte_regs.ctrl[15];
              mac2 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              mac3a_105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
              mac3b_106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
              mac3c_107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_299;
            }
            vz_109 = gte_regs.data[5].s16.hi;
            value = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2_s = gte_regs.ctrl[6].u32
                + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            mac3a_114 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
            mac3b_115 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
            mac3c_116 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_309;
          }
          if ( value == 5046290 )
          {
            vz_101 = gte_regs.data[5].s16.hi;
            value = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            mac3a_105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
            mac3b_106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
            mac3c_107 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_298;
          }
          if ( value == 5030930 )
          {
            vz_141 = gte_regs.data[3].s16.hi;
            value = gte_regs.ctrl[21].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2_s = gte_regs.ctrl[22].u32
                + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            mac3a_146 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
            mac3b_147 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
            mac3c_148 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_333;
          }
          if ( value != 5038098 )
          {
            if ( value != 5039122 )
              goto LABEL_630;
            vz_172 = gte_regs.data[3].s16.hi;
            vx_170 = gte_regs.data[2].s16.lo;
            vy_171 = gte_regs.data[2].s16.hi;
            goto LABEL_521;
          }
          vz_132 = gte_regs.data[3].s16.hi;
          vx_175 = gte_regs.data[2].s16.lo;
          vy_176 = gte_regs.data[2].s16.hi;
          goto LABEL_515;
        }
        if ( value <= 0x4DA012 )
        {
          if ( value == 5087250 )
          {
            vx_162 = gte_regs.data[10].s16.hi;
            vy_163 = gte_regs.data[9].s16.hi;
            vz_101 = gte_regs.data[11].s16.hi;
            value = gte_regs.ctrl[13].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2a_164 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
            mac2b_165 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
            goto LABEL_530;
          }
          if ( value > 0x4D6412 )
          {
            if ( value == 5079058 )
            {
              vx_150 = gte_regs.data[10].s16.hi;
              vy_151 = gte_regs.data[9].s16.hi;
              vz_101 = gte_regs.data[11].s16.hi;
              value = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2a_152 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              mac2b_153 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_528;
            }
            if ( value != 5080082 )
              goto LABEL_630;
            vx_154 = gte_regs.data[10].s16.hi;
            vy_155 = gte_regs.data[9].s16.hi;
            vz_109 = gte_regs.data[11].s16.hi;
            value = gte_regs.ctrl[5].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            mac2a_156 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
            mac2b_157 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
LABEL_526:
            mac2_s = gte_regs.ctrl[6].u32 + ((mac2b_157 + mac2a_156) >> 12);
            mac3a_114 = vy_155 * gte_regs.ctrl[19].s16.hi;
            mac3b_115 = vx_154 * gte_regs.ctrl[19].s16.lo;
            mac3c_116 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_309;
          }
          switch ( value )
          {
            case 0x4D6412u:
              vz_172 = gte_regs.data[5].s16.hi;
              vx_170 = gte_regs.data[4].s16.lo;
              vy_171 = gte_regs.data[4].s16.hi;
LABEL_521:
              mac2a_173 = vz_172 * gte_regs.ctrl[18].s16.lo + vx_170 * gte_regs.ctrl[18].s16.hi;
              value = (vz_172 * gte_regs.ctrl[17].s16.hi + vx_170 * gte_regs.ctrl[16].s16.lo + vy_171 * gte_regs.ctrl[16].s16.hi) >> 12;
              mac2b_174 = vy_171 * gte_regs.ctrl[17].s16.lo;
LABEL_522:
              mac2_s = (mac2b_174 + mac2a_173) >> 12;
              mac3 = (vz_172 * gte_regs.ctrl[20].s16.hi + vx_170 * gte_regs.ctrl[19].s16.lo + vy_171 * gte_regs.ctrl[19].s16.hi) >> 12;
              goto LABEL_102;
            case 0x4D4012u:
              vx_166 = gte_regs.data[4].s16.lo;
              vy_167 = gte_regs.data[4].s16.hi;
              vz_101 = gte_regs.data[5].s16.hi;
              value = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2a_168 = gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi;
              mac2b_169 = gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_519;
            case 0x4D4412u:
              vz_141 = gte_regs.data[5].s16.hi;
              value = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              mac3a_146 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
              mac3b_147 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
              mac3c_148 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_333;
          }
          if ( value != 5070866 )
            goto LABEL_630;
          vz_132 = gte_regs.data[5].s16.hi;
          vx_175 = gte_regs.data[4].s16.lo;
          vy_176 = gte_regs.data[4].s16.hi;
LABEL_515:
          mac2a_177 = vz_132 * gte_regs.ctrl[18].s16.lo + vx_175 * gte_regs.ctrl[18].s16.hi;
          value = (vz_132 * gte_regs.ctrl[17].s16.hi + vx_175 * gte_regs.ctrl[16].s16.lo + vy_176 * gte_regs.ctrl[16].s16.hi) >> 12;
          mac2b_178 = vy_176 * gte_regs.ctrl[17].s16.lo;
          goto LABEL_516;
        }
        if ( value <= 0x4DE012 )
        {
          switch ( value )
          {
            case 0x4DE012u:
              value = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
              mac2_s2 = (gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12;
              mac3 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
              lm.u32 = -32768;
              gte_regs.data[25].u32 = value;
              gte_regs.data[26].u32 = mac2_s2;
              gte_regs.data[27].u32 = mac3;
              if ( (int)value >= -32768 )
              {
                if ( (int)value <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
                }
                else
                {
                  gte_regs.ctrl[31].u32 = -2130706432;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = -32768;
              }
              if ( mac2_s2 >= -32768 )
              {
                if ( mac2_s2 <= 0x7FFF )
                {
                  gte_regs.data[10].u32 = mac2_s2;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( mac3 >= -32768 )
                goto LABEL_541;
              goto LABEL_558;
            case 0x4DA412u:
              value = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2_s = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12);
              trz_68 = gte_regs.ctrl[15];
              mac3s_67 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
              goto LABEL_101;
            case 0x4DC012u:
              value = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              mac2 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12);
              mac3 = gte_regs.ctrl[23].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
              lm.u32 = -32768;
              goto LABEL_56;
          }
          if ( value != 5096466 )
            goto LABEL_630;
          vx_179 = gte_regs.data[10].s16.hi;
          vy_180 = gte_regs.data[9].s16.hi;
          vz_141 = gte_regs.data[11].s16.hi;
          value = gte_regs.ctrl[21].u32
              + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
          mac2a_181 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
          mac2b_182 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
          goto LABEL_537;
        }
        if ( value == 5104658 )
        {
          value = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
               + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
          mac2_s3 = (gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12;
          mac3 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
               + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
          gte_regs.data[25].u32 = value;
          gte_regs.data[26].u32 = mac2_s3;
          gte_regs.data[27].u32 = mac3;
          if ( (value & 0x80000000) == 0 )
          {
            if ( (int)value <= 0x7FFF )
            {
              gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 = -2130706432;
            gte_regs.data[9].u32 = 0;
          }
          if ( mac2_s3 >= 0 )
          {
            if ( mac2_s3 <= 0x7FFF )
            {
              gte_regs.data[10].u32 = mac2_s3;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0;
          }
          if ( mac3 >= 0 )
            goto LABEL_541;
          goto LABEL_573;
        }
        if ( value != 5767213 )
          goto LABEL_630;
LABEL_694:
        gte_regs.data[24].u32 = gte_regs.ctrl[29].s16.hi
                              * (gte_regs.data[17].u16.hi + gte_regs.data[18].u16.hi + gte_regs.data[19].u16.hi);
        value = gte_regs.data[24].s32 >> 12;
        if ( gte_regs.data[24].s32 >> 12 >= 0 )
        {
          if ( (int)value <= 0xFFFF )
          {
            gte_regs.data[7].u16.hi = gte_regs.data[24].s32 >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80040000;
            gte_regs.data[7].u16.hi = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80040000;
          gte_regs.data[7].u16.hi = 0;
        }
        return;
      }
      if ( value > 0x118043F )
      {
        if ( value <= 0x178000C )
        {
          if ( value == 24641548 )
          {
            LOBYTE(value) = gte_op_shifted().u32;
            return;
          }
          if ( value <= 0x158002D )
          {
            if ( value != 22544429 )
            {
              if ( value == 19399700 )
              {
                LOBYTE(value) = gte_cdp();
                return;
              }
              if ( value == 20448284 )
              {
                LOBYTE(value) = gte_cc();
                return;
              }
              if ( value != 20971526 )
                goto LABEL_630;
              goto LABEL_612;
            }
            goto LABEL_694;
          }
          if ( value != 23593006 )
          {
            if ( value == 24117260 )
            {
              LOBYTE(value) = gte_op();
              return;
            }
            goto LABEL_630;
          }
          goto LABEL_699;
        }
        if ( value > 0x198003D )
        {
          if ( value != 0x1A0003E )
          {
            if ( value == 0x1A8003E )
            {
              mac2_gpls.u32 = ((gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12) + gte_regs.data[26].u32;
              mac3_gpls.u32 = ((gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12) + gte_regs.data[27].u32;
              gte_regs.data[25].u32 += (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
              gte_regs.data[26] = mac2_gpls;
              gte_regs.data[27] = mac3_gpls;
              if ( gte_regs.data[25].s32 >= -32768 )
              {
                if ( gte_regs.data[25].s32 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = gte_regs.data[25].u32;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x81000000;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = -32768;
              }
              if ( mac2_gpls.s32 >= -32768 )
              {
                if ( mac2_gpls.s32 <= 0x7FFF )
                {
                  gte_regs.data[10] = mac2_gpls;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( mac3_gpls.s32 >= -32768 )
              {
                if ( mac3_gpls.s32 <= 0x7FFF )
                {
                  gte_regs.data[11] = mac3_gpls;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x400000u;
                  gte_regs.data[11].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = -32768;
              }
              gte_regs.data[20].u32 = gte_regs.data[21].u32;
              value = gte_regs.data[25].s32 >> 4;
              gte_regs.data[21].u32 = gte_regs.data[22].u32;
              green_gpls = mac2_gpls.s32 >> 4;
              blue_gpls = mac3_gpls.s32 >> 4;
              gte_color_r = gte_regs.data[25].s32 >> 4;
              gte_color_g = green_gpls;
              gte_color_b = blue_gpls;
              if ( gte_regs.data[25].s32 >> 4 >= 0 )
              {
                if ( (int)value <= 255 )
                {
                  LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x200000u;
                  LOBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( green_gpls >= 0 )
              {
                if ( green_gpls <= 255 )
                {
                  HIBYTE(gte_regs.data[22].u16.hi) = green_gpls;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x100000u;
                  HIBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( blue_gpls >= 0 )
              {
                if ( blue_gpls <= 255 )
                {
                  LOBYTE(gte_regs.data[22].s16.lo) = blue_gpls;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80000u;
                  LOBYTE(value) = HIBYTE(gte_regs.data[6].u32);
                  LOBYTE(gte_regs.data[22].s16.lo) = -1;
                }
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              else
              {
                LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(gte_regs.data[22].s16.lo) = 0;
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              return;
            }
            goto LABEL_630;
          }
        }
        else
        {
          switch ( value )
          {
            case 0x198003Du:
              goto LABEL_735;
            case 0x1780010u:
              goto LABEL_626;
            case 0x190003Du:
              goto LABEL_704;
          }
          if ( value != 26214462 )
            goto LABEL_630;
        }
        mac2_gpl.u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi + gte_regs.data[26].u32;
        mac3_gpl.u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi + gte_regs.data[27].u32;
        gte_regs.data[25].u32 += gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
        gte_regs.data[26] = mac2_gpl;
        gte_regs.data[27] = mac3_gpl;
        if ( gte_regs.data[25].s32 >= -32768 )
        {
          if ( gte_regs.data[25].s32 <= 0x7FFF )
          {
            gte_regs.data[9].u32 = gte_regs.data[25].u32;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x81000000;
          gte_regs.data[9].u32 = -32768;
        }
        if ( mac2_gpl.s32 >= -32768 )
        {
          if ( mac2_gpl.s32 <= 0x7FFF )
          {
            gte_regs.data[10] = mac2_gpl;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80800000;
          gte_regs.data[10].u32 = -32768;
        }
        if ( mac3_gpl.s32 >= -32768 )
        {
          if ( mac3_gpl.s32 <= 0x7FFF )
          {
            gte_regs.data[11] = mac3_gpl;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x400000u;
          gte_regs.data[11].u32 = -32768;
        }
        gte_regs.data[20].u32 = gte_regs.data[21].u32;
        value = gte_regs.data[25].s32 >> 4;
        gte_regs.data[21].u32 = gte_regs.data[22].u32;
        green_gpl = mac2_gpl.s32 >> 4;
        blue_gpl = mac3_gpl.s32 >> 4;
        gte_color_r = gte_regs.data[25].s32 >> 4;
        gte_color_g = green_gpl;
        gte_color_b = blue_gpl;
        if ( gte_regs.data[25].s32 >> 4 >= 0 )
        {
          if ( (int)value <= 255 )
          {
            LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x200000u;
            LOBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x200000u;
          LOBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( green_gpl >= 0 )
        {
          if ( green_gpl <= 255 )
          {
            HIBYTE(gte_regs.data[22].u16.hi) = green_gpl;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x100000u;
            HIBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x100000u;
          HIBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( blue_gpl >= 0 )
        {
          if ( blue_gpl <= 255 )
          {
            LOBYTE(gte_regs.data[22].s16.lo) = blue_gpl;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80000u;
            LOBYTE(value) = HIBYTE(gte_regs.data[6].u32);
            LOBYTE(gte_regs.data[22].s16.lo) = -1;
          }
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        else
        {
          LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
          gte_regs.ctrl[31].u32 |= 0x80000u;
          LOBYTE(gte_regs.data[22].s16.lo) = 0;
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        return;
      }
      if ( value == 18351167 )
      {
        LOBYTE(value) = gte_ncct();
        return;
      }
      if ( value <= 0xA80428 )
      {
        if ( value == 11011112 )
        {
          value = (gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi) >> 12;
          mac2_sqr = (gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi) >> 12;
          mac3_sqr = (gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi) >> 12;
          gte_regs.data[25].u32 = value;
          gte_regs.data[26].u32 = mac2_sqr;
          gte_regs.data[27].u32 = mac3_sqr;
          if ( (value & 0x80000000) == 0 )
          {
            if ( (int)value <= 0x7FFF )
            {
              gte_regs.data[9].u32 = (gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x81000000;
              gte_regs.data[9].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0;
          }
          if ( mac2_sqr >= 0 )
          {
            if ( mac2_sqr <= 0x7FFF )
            {
              gte_regs.data[10].u32 = (gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0;
          }
          if ( mac3_sqr >= 0 )
          {
            if ( mac3_sqr <= 0x7FFF )
            {
              gte_regs.data[11].u32 = (gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0;
          }
          return;
        }
        if ( value <= 0x980011 )
        {
          if ( value == 9961489 )
          {
            gte_regs.data[25].u32 = gte_regs.data[9].s16.hi
                                  + ((gte_regs.data[8].s16.hi
                                    * gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - gte_regs.data[9].s16.hi)) >> 12);
            gte_regs.data[26].u32 = gte_regs.data[10].s16.hi
                                  + ((gte_regs.data[8].s16.hi
                                    * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - gte_regs.data[10].s16.hi)) >> 12);
            b_clamped = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - gte_regs.data[11].s16.hi);
            mac3_intpl.u32 = gte_regs.data[11].s16.hi + ((gte_regs.data[8].s16.hi * b_clamped) >> 12);
            gte_regs.data[27] = mac3_intpl;
            if ( gte_regs.data[25].s32 >= -32768 )
            {
              if ( gte_regs.data[25].s32 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = gte_regs.data[25].u32;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= flag;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= flag;
              gte_regs.data[9].u32 = -32768;
            }
            if ( gte_regs.data[26].s32 >= -32768 )
            {
              if ( gte_regs.data[26].s32 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = gte_regs.data[26].u32;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = -32768;
            }
            if ( mac3_intpl.s32 >= -32768 )
            {
              if ( mac3_intpl.s32 <= 0x7FFF )
              {
                gte_regs.data[11] = mac3_intpl;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = -32768;
            }
            gte_regs.data[20].u32 = gte_regs.data[21].u32;
            green_intpl = gte_regs.data[26].s32 >> 4;
            value = mac3_intpl.s32 >> 4;
            gte_regs.data[21].u32 = gte_regs.data[22].u32;
            gte_color_r = gte_regs.data[25].s32 >> 4;
            gte_color_g = gte_regs.data[26].s32 >> 4;
            gte_color_b = value;
            if ( gte_regs.data[25].s32 >> 4 >= 0 )
            {
              if ( gte_regs.data[25].s32 >> 4 <= 255 )
              {
                LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = -1;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x200000u;
              LOBYTE(gte_regs.data[22].u16.hi) = 0;
            }
            if ( green_intpl >= 0 )
            {
              if ( green_intpl <= 255 )
              {
                HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = -1;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x100000u;
              HIBYTE(gte_regs.data[22].u16.hi) = 0;
            }
            if ( (value & 0x80000000) == 0 )
            {
              if ( (int)value <= 255 )
              {
                LOBYTE(gte_regs.data[22].s16.lo) = value;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(value) = HIBYTE(gte_regs.data[6].u32);
                LOBYTE(gte_regs.data[22].s16.lo) = -1;
              }
              HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
            }
            else
            {
              LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
              gte_regs.ctrl[31].u32 |= 0x80000u;
              LOBYTE(gte_regs.data[22].s16.lo) = 0;
              HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
            }
            return;
          }
          if ( (int *)value != (int *)((char *)&ram[205947] + 2) )
          {
            if ( (int *)value != &ram[468084] )
            {
              if ( value != 9437245 )
                goto LABEL_630;
LABEL_704:
              mac1_gpf.u32 = gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
              mac2_gpf.u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi;
              mac3_gpf.u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi;
              gte_regs.data[25] = mac1_gpf;
              gte_regs.data[26] = mac2_gpf;
              gte_regs.data[27] = mac3_gpf;
              if ( mac1_gpf.s32 >= -32768 )
              {
                if ( mac1_gpf.s32 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x81000000;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = -32768;
              }
              if ( mac2_gpf.s32 >= -32768 )
              {
                if ( mac2_gpf.s32 <= 0x7FFF )
                {
                  gte_regs.data[10].u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( mac3_gpf.s32 >= -32768 )
              {
                if ( mac3_gpf.s32 <= 0x7FFF )
                {
                  gte_regs.data[11].u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x400000u;
                  gte_regs.data[11].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = -32768;
              }
              gte_regs.data[20].u32 = gte_regs.data[21].u32;
              value = mac1_gpf.s32 >> 4;
              gte_regs.data[21].u32 = gte_regs.data[22].u32;
              green_gpf = mac2_gpf.s32 >> 4;
              blue_gpf = mac3_gpf.s32 >> 4;
              gte_color_r = value;
              gte_color_g = green_gpf;
              gte_color_b = blue_gpf;
              if ( (value & 0x80000000) == 0 )
              {
                if ( (int)value <= 255 )
                {
                  LOBYTE(gte_regs.data[22].u16.hi) = value;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x200000u;
                  LOBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( green_gpf >= 0 )
              {
                if ( green_gpf <= 255 )
                {
                  HIBYTE(gte_regs.data[22].u16.hi) = green_gpf;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x100000u;
                  HIBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( blue_gpf >= 0 )
              {
                if ( blue_gpf <= 255 )
                {
                  LOBYTE(gte_regs.data[22].s16.lo) = blue_gpf;
                }
                else
                {
                  LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
                  gte_regs.ctrl[31].u32 |= 0x80000u;
                  LOBYTE(gte_regs.data[22].s16.lo) = -1;
                }
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(gte_regs.data[22].s16.lo) = 0;
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
                LOBYTE(value) = HIBYTE(gte_regs.data[6].u32);
              }
              return;
            }
LABEL_626:
            LOBYTE(value) = gte_dpcs();
            return;
          }
LABEL_699:
          gte_regs.data[24].u32 = gte_regs.ctrl[30].s16.hi
                                * (gte_regs.data[16].u16.hi
                                 + gte_regs.data[17].u16.hi
                                 + gte_regs.data[18].u16.hi
                                 + gte_regs.data[19].u16.hi);
          value = gte_regs.data[24].s32 >> 12;
          if ( gte_regs.data[24].s32 >> 12 >= 0 )
          {
            if ( (int)value <= 0xFFFF )
            {
              gte_regs.data[7].u16.hi = gte_regs.data[24].s32 >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80040000;
              gte_regs.data[7].u16.hi = -1;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80040000;
            gte_regs.data[7].u16.hi = 0;
          }
          return;
        }
        if ( value != 9961533 )
        {
          if ( value == 10486824 )
          {
            value = gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi;
            mac2_sqrs.u32 = gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi;
            mac3_sqrs.u32 = gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi;
            gte_regs.data[25].u32 = value;
            gte_regs.data[26] = mac2_sqrs;
            gte_regs.data[27] = mac3_sqrs;
            if ( (value & 0x80000000) == 0 )
            {
              if ( (int)value <= 0x7FFF )
              {
                gte_regs.data[9].u32 = gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x81000000;
              gte_regs.data[9].u32 = 0;
            }
            if ( mac2_sqrs.s32 >= 0 )
            {
              if ( mac2_sqrs.s32 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0;
            }
            if ( mac3_sqrs.s32 >= 0 )
            {
              if ( mac3_sqrs.s32 <= 0x7FFF )
              {
                gte_regs.data[11].u32 = gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = 0;
            }
            return;
          }
          goto LABEL_630;
        }
LABEL_735:
        mac1_gpfs = (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
        mac2_gpfs = (gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12;
        mac3_gpfs = (gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12;
        gte_regs.data[25].u32 = mac1_gpfs;
        gte_regs.data[26].u32 = mac2_gpfs;
        gte_regs.data[27].u32 = mac3_gpfs;
        if ( mac1_gpfs >= -32768 )
        {
          if ( mac1_gpfs <= 0x7FFF )
          {
            gte_regs.data[9].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x81000000;
          gte_regs.data[9].u32 = -32768;
        }
        if ( mac2_gpfs >= -32768 )
        {
          if ( mac2_gpfs <= 0x7FFF )
          {
            gte_regs.data[10].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80800000;
          gte_regs.data[10].u32 = -32768;
        }
        if ( mac3_gpfs >= -32768 )
        {
          if ( mac3_gpfs <= 0x7FFF )
          {
            gte_regs.data[11].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x400000u;
          gte_regs.data[11].u32 = -32768;
        }
        gte_regs.data[20].u32 = gte_regs.data[21].u32;
        value = mac1_gpfs >> 4;
        gte_regs.data[21].u32 = gte_regs.data[22].u32;
        green_gpfs = mac2_gpfs >> 4;
        blue_gpfs = mac3_gpfs >> 4;
        gte_color_r = value;
        gte_color_g = green_gpfs;
        gte_color_b = blue_gpfs;
        if ( (value & 0x80000000) == 0 )
        {
          if ( (int)value <= 255 )
          {
            LOBYTE(gte_regs.data[22].u16.hi) = value;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x200000u;
            LOBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x200000u;
          LOBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( green_gpfs >= 0 )
        {
          if ( green_gpfs <= 255 )
          {
            HIBYTE(gte_regs.data[22].u16.hi) = green_gpfs;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x100000u;
            HIBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x100000u;
          HIBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( blue_gpfs >= 0 )
        {
          if ( blue_gpfs <= 255 )
          {
            LOBYTE(gte_regs.data[22].s16.lo) = blue_gpfs;
          }
          else
          {
            LOBYTE(value) = gte_regs.ctrl[31].u16.hi;
            gte_regs.ctrl[31].u32 |= 0x80000u;
            LOBYTE(gte_regs.data[22].s16.lo) = -1;
          }
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80000u;
          LOBYTE(gte_regs.data[22].s16.lo) = 0;
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
          LOBYTE(value) = HIBYTE(gte_regs.data[6].u32);
        }
        return;
      }
      if ( value <= 0xF8002A )
      {
        switch ( value )
        {
          case 0xF8002Au:
            LOBYTE(value) = gte_dpct().u32;
            return;
          case 0xC8041Eu:
            LOBYTE(value) = gte_ncs();
            return;
          case 0xD80420u:
            LOBYTE(value) = gte_nct();
            return;
          case 0xE80413u:
            LOBYTE(value) = gte_ncds();
            return;
        }
        goto LABEL_630;
      }
      if ( value == 0xF80416 )
      {
        LOBYTE(value) = gte_ncdt();
        return;
      }
      if ( value == 0x108041B )
        goto LABEL_602;
LABEL_630:
      if ( gtrace )
        LOBYTE(value) = dbg_print("CODE [%07x]\n", value);
      return;
  }
}

int gte_read_data_register(uint8_t index)
{
  uint8_t five_bit;
  int result_bits;

  if ( index == 31 )
    return (uint8_t)gte_count_leading_bits(gte_regs.data[30].s32);
  if ( index != 29 )
    return gte_regs.data[index].s32;
  gte_convert_to_5bit(gte_regs.data[11].u16.hi);
  gte_convert_to_5bit(gte_regs.data[10].u16.hi);
  five_bit = gte_convert_to_5bit(gte_regs.data[9].u16.hi);
  return result_bits | five_bit;
}

GTE_REG gte_write_data_register(uint8_t index, GTE_REG value)
{
  GTE_REG result_reg;

  result_reg = value;
  gte_regs.data[index] = value;
  if ( index >= 0x10u && index <= 0x13u )
    gte_regs.data[index].u32 = value.u16.hi;
  switch ( index )
  {
    case 0xEu:
      gte_regs.data[15] = value;
      break;
    case 0xFu:
      gte_regs.data[12].u32 = gte_regs.data[13].u32;
      gte_regs.data[13].u32 = gte_regs.data[14].u32;
      gte_regs.data[14] = value;
      break;
    case 0x1Cu:
      result_reg.u32 = ((value.u32 >> 10) & 0x1F) << 7;
      gte_regs.data[9].u32 = (value.u16.hi & 0x1F) << 7;
      gte_regs.data[10].u32 = ((value.u32 >> 5) & 0x1F) << 7;
      gte_regs.data[11] = result_reg;
      break;
  }
  return result_reg;
}

int gte_clear_regs()
{
  memset(&gte_regs, 0, sizeof(gte_regs));
  return 0;
}

int gte_freeze(const char *filename, int gz_file)
{
  char Buffer[3];

  sprintf(Buffer, "%s", filename);
  gzwrite(gz_file, (uint8_t *)Buffer, 7u);
  return gzwrite(gz_file, (uint8_t *)&gte_regs, 0x100u);
}

int gte_unfreeze(int unused, uint32_t *gz_file)
{
  char header[16];

  gzread(gz_file, header, 7);
  return gzread(gz_file, (char *)&gte_regs, 256);
}





/* Decompiled globals (previously generated in src/_gen) */
unsigned char gte_cpu_gpr_index;
unsigned char gte_control_reg_index;
unsigned char gte_data_reg_index;
unsigned int gte_regs_ptr = 0x8a7f00;
unsigned int gte_color_r;
unsigned int gte_color_g;
unsigned int gte_color_b;
GTE_REGS gte_regs;
uint64_t qword_44F958 = 0x8080000081000000;
uint64_t qword_44F960 = 0x400000;
