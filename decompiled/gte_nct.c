#include "pch.h"
char gte_nct()
{
  int v0; // ebp
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  signed int v4; // eax
  signed int v5; // ecx
  signed int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  signed int v14; // eax
  signed int v15; // ecx
  signed int v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // edx
  int v20; // ebp
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  GTE_REG v24; // eax
  GTE_REG v25; // ecx
  GTE_REG v26; // edx
  int v27; // eax
  int v28; // ecx
  int v29; // edx
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
  v5 = gte_regs.ctrl[14].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v6 = gte_regs.ctrl[15].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( (unsigned int)v4 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x81000000;
  if ( (unsigned int)v5 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x80800000;
  if ( (unsigned int)v6 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x400000u;
  v7 = v4 >> 4;
  v8 = v5 >> 4;
  v9 = v6 >> 4;
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
  v15 = gte_regs.ctrl[14].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v16 = gte_regs.ctrl[15].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( (unsigned int)v14 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x81000000;
  if ( (unsigned int)v15 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x80800000;
  if ( (unsigned int)v16 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x400000u;
  v17 = v14 >> 4;
  v18 = v15 >> 4;
  v19 = v16 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  if ( v17 >= 0 )
  {
    if ( v17 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v17;
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
      HIBYTE(gte_regs.data[22].u16.hi) = v18;
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
      LOBYTE(gte_regs.data[22].s16.lo) = v19;
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
  v24.u32 = gte_regs.ctrl[13].u32
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
  gte_regs.data[25] = v24;
  gte_regs.data[26] = v25;
  gte_regs.data[27] = v26;
  if ( v24.s32 >= 0 )
  {
    if ( v24.s32 <= 0x7FFF )
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
  v27 = v24.s32 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v28 = v25.s32 >> 4;
  v29 = v26.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v27;
  dword_8A8008 = v28;
  dword_8A800C = v29;
  if ( v27 >= 0 )
  {
    if ( v27 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v27;
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
  if ( v28 >= 0 )
  {
    if ( v28 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v28;
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
  if ( v29 >= 0 )
  {
    if ( v29 <= 255 )
    {
      result = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = v29;
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
