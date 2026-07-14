#include "pch.h"
GTE_REG sub_412B10()
{
  GTE_REG v0; // esi
  int v1; // esi
  int v2; // edi
  int v3; // eax
  int v4; // edx
  int v5; // eax
  GTE_REG result; // eax
  int32_t v7; // edx
  int32_t v8; // ebx
  int v9; // [esp-4h] [ebp-18h]
  int v10; // [esp+10h] [ebp-4h]

  LOBYTE(v0.u16.hi) = gte_regs.data[20].u16.hi;
  v10 = 3;
  do
  {
    v9 = gte_regs.ctrl[21].u32 - 16 * LOBYTE(v0.u32);
    v1 = 16 * HIBYTE(gte_regs.data[20].u16.hi);
    v2 = 16 * LOBYTE(gte_regs.data[20].s16.lo);
    v3 = gte_clamp(-2130706432, v9);
    gte_regs.data[25].u32 = v4 + ((gte_regs.data[8].s16.hi * v3) >> 12);
    gte_regs.data[26].u32 = v1 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v1)) >> 12);
    v5 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v2);
    v0 = gte_regs.data[21];
    result.u32 = v2 + ((gte_regs.data[8].s16.hi * v5) >> 12);
    gte_regs.data[21].u32 = gte_regs.data[22].u32;
    v7 = gte_regs.data[26].s32 >> 4;
    v8 = result.s32 >> 4;
    gte_regs.data[27] = result;
    gte_regs.data[20] = v0;
    dword_8A8004 = gte_regs.data[25].s32 >> 4;
    dword_8A8008 = gte_regs.data[26].s32 >> 4;
    dword_8A800C = result.s32 >> 4;
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
    if ( v7 >= 0 )
    {
      if ( v7 <= 255 )
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
    if ( v8 >= 0 )
    {
      if ( v8 <= 255 )
      {
        LOBYTE(gte_regs.data[22].s16.lo) = result.s32 >> 4;
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
    --v10;
  }
  while ( v10 );
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
  if ( result.s32 >= -32768 )
  {
    if ( result.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = result;
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
  return result;
}
