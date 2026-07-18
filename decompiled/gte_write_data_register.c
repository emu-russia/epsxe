#include "pch.h"
GTE_REG __cdecl gte_write_data_register(unsigned __int8 a1, GTE_REG a2)
{
  GTE_REG result; // eax

  result = a2;
  gte_regs.data[a1] = a2;
  if ( a1 >= 0x10u && a1 <= 0x13u )
    gte_regs.data[a1].u32 = a2.u16.hi;
  switch ( a1 )
  {
    case 0xEu:
      gte_regs.data[15] = a2;
      break;
    case 0xFu:
      gte_regs.data[12].u32 = gte_regs.data[13].u32;
      gte_regs.data[13].u32 = gte_regs.data[14].u32;
      gte_regs.data[14] = a2;
      break;
    case 0x1Cu:
      result.u32 = ((a2.u32 >> 10) & 0x1F) << 7;
      gte_regs.data[9].u32 = (a2.u16.hi & 0x1F) << 7;
      gte_regs.data[10].u32 = ((a2.u32 >> 5) & 0x1F) << 7;
      gte_regs.data[11] = result;
      break;
  }
  return result;
}
