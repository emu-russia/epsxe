#include "pch.h"
GTE_REG sub_4145C0()
{
  GTE_REG result; // eax
  int v1; // edx
  int v2; // ecx

  result.u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi) >> 12;
  v1 = (gte_regs.ctrl[4].s16.hi * gte_regs.data[9].s16.hi - gte_regs.data[11].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
  v2 = (gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.hi - gte_regs.ctrl[2].s16.hi * gte_regs.data[9].s16.hi) >> 12;
  gte_regs.data[25] = result;
  gte_regs.data[26].u32 = v1;
  gte_regs.data[27].u32 = v2;
  if ( result.s32 >= -32768 )
  {
    if ( result.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi
                            - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi) >> 12;
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
  if ( v1 >= -32768 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = v1;
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
  if ( v2 >= -32768 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = v2;
    }
    else
    {
      gte_regs.data[11].u32 = 0x7FFF;
      result.u32 = gte_regs.ctrl[31].u32 | 0x400000;
      gte_regs.ctrl[31].u32 |= 0x400000u;
    }
  }
  else
  {
    gte_regs.data[11].u32 = -32768;
    result.u32 = gte_regs.ctrl[31].u32 | 0x400000;
    gte_regs.ctrl[31].u32 |= 0x400000u;
  }
  return result;
}
