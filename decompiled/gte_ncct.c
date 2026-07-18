#include "pch.h"
char gte_ncct()
{
  int v0; // ebp
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  signed int v4; // eax
  GTE_REG v5; // ecx
  GTE_REG v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  signed int v14; // eax
  GTE_REG v15; // ecx
  GTE_REG v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // edx
  int v20; // ebp
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  signed int v24; // eax
  GTE_REG v25; // ecx
  GTE_REG v26; // edx
  int v27; // eax
  int v28; // ecx
  int v29; // edx
  int v30; // eax
  int v31; // ecx
  int v32; // edx
  char result; // al

  v0 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v3 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi + v0 + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
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
      gte_regs.data[11].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
                             + v0
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
  v4 = gte_regs.ctrl[13].u32
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
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
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
  v7 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
  v8 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
  v9 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
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
      HIBYTE(gte_regs.data[22].u16.hi) = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
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
      LOBYTE(gte_regs.data[22].s16.lo) = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
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
  v10 = gte_regs.ctrl[10].s16.lo * gte_regs.data[3].s16.hi;
  v11 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  v12 = (v10 + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
  v13 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  if ( v11 >= 0 )
  {
    if ( v11 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
                            + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
                            + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
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
  if ( v12 >= 0 )
  {
    if ( v12 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (v10
                             + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo
                             + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
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
  if ( v13 >= 0 )
  {
    if ( v13 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
                             + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
                             + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
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
  v14 = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v15.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v16.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( v14 >= 0 )
  {
    if ( v14 <= 0x7FFF )
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
  if ( v15.s32 >= 0 )
  {
    if ( v15.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v15;
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
  if ( v16.s32 >= 0 )
  {
    if ( v16.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v16;
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
  v17 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
  v18 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
  v19 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  if ( v17 >= 0 )
  {
    if ( v17 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
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
  if ( v18 >= 0 )
  {
    if ( v18 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
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
  if ( v19 >= 0 )
  {
    if ( v19 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
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
  v20 = gte_regs.ctrl[10].s16.lo * gte_regs.data[5].s16.hi;
  v21 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  v22 = (v20 + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
  v23 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  if ( v21 >= 0 )
  {
    if ( v21 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
                            + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
                            + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
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
  if ( v22 >= 0 )
  {
    if ( v22 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (v20
                             + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo
                             + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
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
  if ( v23 >= 0 )
  {
    if ( v23 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
                             + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
                             + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
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
  v24 = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v25.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v26.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( v24 >= 0 )
  {
    if ( v24 <= 0x7FFF )
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
  if ( v25.s32 >= 0 )
  {
    if ( v25.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v25;
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
  if ( v26.s32 >= 0 )
  {
    if ( v26.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v26;
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
  v27 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 8;
  v28 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 8;
  v29 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 8;
  gte_regs.data[25].u32 = v27;
  gte_regs.data[26].u32 = v28;
  gte_regs.data[27].u32 = v29;
  if ( v27 >= 0 )
  {
    if ( v27 <= 0x7FFF )
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
  if ( v28 >= 0 )
  {
    if ( v28 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 8;
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
  if ( v29 >= 0 )
  {
    if ( v29 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 8;
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
  v30 = v27 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v31 = v28 >> 4;
  v32 = v29 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v30;
  dword_8A8008 = v31;
  dword_8A800C = v32;
  if ( v30 >= 0 )
  {
    if ( v30 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v30;
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
  if ( v31 >= 0 )
  {
    if ( v31 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v31;
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
  if ( v32 >= 0 )
  {
    if ( v32 <= 255 )
    {
      result = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = v32;
    }
    else
    {
      result = gte_regs.ctrl[31].s32;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
      gte_regs.ctrl[31].u32 |= 0x80000u;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    result = gte_regs.ctrl[31].s32;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return result;
}
