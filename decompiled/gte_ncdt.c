#include "pch.h"
char gte_ncdt()
{
  int v0; // eax
  int v1; // ecx
  int v2; // edx
  GTE_REG v3; // eax
  GTE_REG v4; // ecx
  GTE_REG v5; // edx
  int v6; // esi
  int v7; // edi
  int v8; // eax
  int v9; // edx
  int v10; // eax
  GTE_REG v11; // edx
  int32_t v12; // edx
  int v13; // eax
  int v14; // ebp
  int v15; // edi
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  GTE_REG v19; // eax
  GTE_REG v20; // ecx
  GTE_REG v21; // edx
  int v22; // esi
  int v23; // edi
  int v24; // eax
  int v25; // edx
  int v26; // eax
  GTE_REG v27; // edx
  int32_t v28; // edx
  int v29; // eax
  int v30; // ebp
  int v31; // edi
  int v32; // eax
  int v33; // ecx
  int v34; // edx
  GTE_REG v35; // eax
  GTE_REG v36; // ecx
  GTE_REG v37; // edx
  int v38; // esi
  int v39; // edi
  int v40; // eax
  int v41; // edx
  GTE_REG v42; // eax
  int32_t v43; // edx
  int v44; // eax

  v0 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
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
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
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
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
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
  v3.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v4.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v5.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v3;
  gte_regs.data[26] = v4;
  gte_regs.data[27] = v5;
  if ( v3.s32 >= 0 )
  {
    if ( v3.s32 <= 0x7FFF )
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
  if ( v4.s32 >= 0 )
  {
    if ( v4.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v4;
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
  if ( v5.s32 >= 0 )
  {
    if ( v5.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v5;
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
  v6 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v7 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v8 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v9 + ((gte_regs.data[8].s16.hi * v8) >> 12);
  gte_regs.data[26].u32 = v6 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v6)) >> 12);
  v10 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v7);
  v11 = gte_regs.data[21];
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_regs.data[20] = v11;
  v12 = gte_regs.data[26].s32 >> 4;
  v13 = (v7 + ((gte_regs.data[8].s16.hi * v10) >> 12)) >> 4;
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
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
  }
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  v14 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
  v15 = gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
  v16 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
       + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
       + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v17 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
       + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
       + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v18 = (v15 + v14 + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v16 >= 0 )
  {
    if ( v16 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
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
  if ( v17 >= 0 )
  {
    if ( v17 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
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
  if ( v18 >= 0 )
  {
    if ( v18 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v15 + v14 + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
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
  v19.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v20.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v21.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v19;
  gte_regs.data[26] = v20;
  gte_regs.data[27] = v21;
  if ( v19.s32 >= 0 )
  {
    if ( v19.s32 <= 0x7FFF )
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
  if ( v20.s32 >= 0 )
  {
    if ( v20.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v20;
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
  if ( v21.s32 >= 0 )
  {
    if ( v21.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v21;
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
  v22 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v23 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v24 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v25 + ((gte_regs.data[8].s16.hi * v24) >> 12);
  gte_regs.data[26].u32 = v22 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v22)) >> 12);
  v26 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v23);
  v27 = gte_regs.data[21];
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_regs.data[20] = v27;
  v28 = gte_regs.data[26].s32 >> 4;
  v29 = (v23 + ((gte_regs.data[8].s16.hi * v26) >> 12)) >> 4;
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
  if ( v28 >= 0 )
  {
    if ( v28 <= 255 )
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
  if ( v29 >= 0 )
  {
    if ( v29 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v29;
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
  v30 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
  v31 = gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
  v32 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
       + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
       + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v33 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
       + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
       + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v34 = (v31 + v30 + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v32 >= 0 )
  {
    if ( v32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
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
  if ( v33 >= 0 )
  {
    if ( v33 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
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
  if ( v34 >= 0 )
  {
    if ( v34 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v31 + v30 + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
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
  v35.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v36.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v37.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v35;
  gte_regs.data[26] = v36;
  gte_regs.data[27] = v37;
  if ( v35.s32 >= 0 )
  {
    if ( v35.s32 <= 0x7FFF )
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
  if ( v36.s32 >= 0 )
  {
    if ( v36.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v36;
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
  if ( v37.s32 >= 0 )
  {
    if ( v37.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v37;
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
  v38 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v39 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v40 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v41 + ((gte_regs.data[8].s16.hi * v40) >> 12);
  gte_regs.data[26].u32 = v38 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v38)) >> 12);
  v42.u32 = v39 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v39)) >> 12);
  gte_regs.data[27] = v42;
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
  if ( v42.s32 >= 0 )
  {
    if ( v42.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v42;
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
  v43 = gte_regs.data[26].s32 >> 4;
  v44 = v42.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v44;
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
  if ( v43 >= 0 )
  {
    if ( v43 <= 255 )
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
  if ( v44 >= 0 )
  {
    if ( v44 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v44;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v44) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v44) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v44;
}
