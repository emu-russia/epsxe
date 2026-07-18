#include "pch.h"
int __cdecl gte_read_data_register(unsigned __int8 a1)
{
  unsigned __int8 v2; // al
  int v3; // edx

  if ( a1 == 31 )
    return (unsigned __int8)gte_count_leading_bits(gte_regs.data[30].s32);
  if ( a1 != 29 )
    return gte_regs.data[a1].s32;
  gte_convert_to_5bit(gte_regs.data[11].u16.hi);
  gte_convert_to_5bit(gte_regs.data[10].u16.hi);
  v2 = gte_convert_to_5bit(gte_regs.data[9].u16.hi);
  return v3 | v2;
}
