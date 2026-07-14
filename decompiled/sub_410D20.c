#include "pch.h"
char sub_410D20()
{
  int v0; // edi
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  GTE_REG v4; // eax
  GTE_REG v5; // ecx
  GTE_REG v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx

  v0 = gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v3 = (v0 + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
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
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
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
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v0
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
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
  v4.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v5.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v6.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v4;
  gte_regs.data[26] = v5;
  gte_regs.data[27] = v6;
  if ( v4.s32 >= 0 )
  {
    if ( v4.s32 <= 0x7FFF )
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
  if ( v5.s32 >= 0 )
  {
    if ( v5.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v5;
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
  if ( v6.s32 >= 0 )
  {
    if ( v6.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v6;
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
  v7 = v4.s32 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v8 = v5.s32 >> 4;
  v9 = v6.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v7;
  dword_8A8008 = v8;
  dword_8A800C = v9;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v7;
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
      HIBYTE(gte_regs.data[22].u16.hi) = v8;
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
      LOBYTE(v7) = gte_regs.ctrl[31].u16.hi;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
      gte_regs.ctrl[31].u32 |= 0x80000u;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
    LOBYTE(v7) = HIBYTE(gte_regs.data[6].u32);
  }
  return v7;
}
