#include "pch.h"
char gte_dpcs()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  int v3; // edx
  GTE_REG v4; // eax
  int32_t v5; // edx
  int v6; // eax

  v0 = 16 * HIBYTE(gte_regs.data[6].u16.hi);
  v1 = 16 * LOBYTE(gte_regs.data[6].s16.lo);
  v2 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - 16 * LOBYTE(gte_regs.data[6].u32));
  gte_regs.data[25].u32 = v3 + ((gte_regs.data[8].s16.hi * v2) >> 12);
  gte_regs.data[26].u32 = v0 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v0)) >> 12);
  v4.u32 = v1 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v1)) >> 12);
  gte_regs.data[27] = v4;
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
  if ( v4.s32 >= -32768 )
  {
    if ( v4.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v4;
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
  v5 = gte_regs.data[26].s32 >> 4;
  v6 = v4.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v6;
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
  if ( v5 >= 0 )
  {
    if ( v5 <= 255 )
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
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v6) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v6) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v6;
}
