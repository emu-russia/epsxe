#include "pch.h"
char gte_ncds()
{
  int v0; // edi
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  GTE_REG v4; // eax
  GTE_REG v5; // ecx
  GTE_REG v6; // edx
  int v7; // esi
  int v8; // edi
  int v9; // eax
  int v10; // edx
  GTE_REG v11; // eax
  int32_t v12; // edx
  int v13; // eax

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
  v7 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v8 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v9 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v10 + ((gte_regs.data[8].s16.hi * v9) >> 12);
  gte_regs.data[26].u32 = v7 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v7)) >> 12);
  v11.u32 = v8 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v8)) >> 12);
  gte_regs.data[27] = v11;
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
  if ( v11.s32 >= 0 )
  {
    if ( v11.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v11;
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
  v12 = gte_regs.data[26].s32 >> 4;
  v13 = v11.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v13;
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
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
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
  if ( v13 >= 0 )
  {
    if ( v13 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v13;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v13) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v13) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v13;
}
