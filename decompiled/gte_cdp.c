#include "pch.h"
char gte_cdp()
{
  GTE_REG v0; // eax
  GTE_REG v1; // ecx
  GTE_REG v2; // edx
  int v3; // esi
  int v4; // edi
  int v5; // eax
  int v6; // edx
  GTE_REG v7; // eax
  int32_t v8; // edx
  int v9; // eax

  v0.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v1.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v2.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v0;
  gte_regs.data[26] = v1;
  gte_regs.data[27] = v2;
  if ( v0.s32 >= 0 )
  {
    if ( v0.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
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
  if ( v1.s32 >= 0 )
  {
    if ( v1.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v1;
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
  if ( v2.s32 >= 0 )
  {
    if ( v2.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v2;
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
  v3 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v4 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v5 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v6 + ((gte_regs.data[8].s16.hi * v5) >> 12);
  gte_regs.data[26].u32 = v3 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v3)) >> 12);
  v7.u32 = v4 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v4)) >> 12);
  gte_regs.data[27] = v7;
  if ( gte_regs.data[25].s32 >= 0 )
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
    gte_regs.data[9].u32 = 0;
  }
  if ( gte_regs.data[26].s32 >= 0 )
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
    gte_regs.data[10].u32 = 0;
  }
  if ( v7.s32 >= 0 )
  {
    if ( v7.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v7;
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
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v8 = gte_regs.data[26].s32 >> 4;
  v9 = v7.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v9;
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
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
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
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v9;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v9) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v9) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v9;
}
