#include "pch.h"
int gte_op()
{
  int result; // eax
  GTE_REG v1; // ecx
  GTE_REG v2; // edx

  result = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi;
  v1.u32 = gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.hi - gte_regs.ctrl[2].s16.hi * gte_regs.data[9].s16.hi;
  v2.u32 = gte_regs.ctrl[4].s16.hi * gte_regs.data[9].s16.hi - gte_regs.data[11].s16.hi * gte_regs.ctrl[0].s16.hi;
  gte_regs.data[25].u32 = result;
  gte_regs.data[26] = v2;
  gte_regs.data[27] = v1;
  if ( result >= (int)-0x8000u )
  {
    if ( result <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi
                           - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi;
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
    gte_regs.data[9].u32 = -0x8000u;
  }
  if ( v2.s32 >= (int)-0x8000u )
  {
    if ( v2.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v2;
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
    gte_regs.data[10].u32 = -0x8000u;
  }
  if ( v1.s32 >= (int)-0x8000u )
  {
    if ( v1.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v1;
    }
    else
    {
      gte_regs.data[11].u32 = 0x7FFF;
      result = gte_regs.ctrl[31].u32 | 0x400000;
      gte_regs.ctrl[31].u32 |= 0x400000u;
    }
  }
  else
  {
    gte_regs.data[11].u32 = -0x8000u;
    result = gte_regs.ctrl[31].u32 | 0x400000;
    gte_regs.ctrl[31].u32 |= 0x400000u;
  }
  return result;
}
