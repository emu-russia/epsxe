#include "pch.h"
int __cdecl sub_41BA80(unsigned __int8 a1)
{
  unsigned __int8 v2; // al
  int v3; // edx

  if ( a1 == 31 )
    return (unsigned __int8)sub_414EE0(gte_regs.data[30].s32);
  if ( a1 != 29 )
    return gte_regs.data[a1].s32;
  sub_410400(gte_regs.data[11].u16.hi);
  sub_410400(gte_regs.data[10].u16.hi);
  v2 = sub_410400(gte_regs.data[9].u16.hi);
  return v3 | v2;
}
