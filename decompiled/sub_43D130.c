#include "pch.h"
int __cdecl sub_43D130(_DWORD *a1)
{
  int result; // eax

  sub_43D1A0(a1, a1 + 35, a1[709]);
  sub_43D1A0(a1, a1 + 608, a1[712]);
  sub_43CB60(a1, a1 + 714);
  for ( result = 18; result >= 3; --result )
  {
    if ( HIWORD(a1[(unsigned __int8)byte_448DAC[result] + 669]) )
      break;
  }
  a1[1448] += 3 * result + 17;
  return result;
}
