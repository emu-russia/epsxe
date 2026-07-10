#include "pch.h"
char __cdecl sub_410400(int a1)
{
  int v1; // eax

  if ( (a1 & 0x8000u) == 0 )
  {
    if ( (__int16)a1 <= 3968 )
      return a1 >> 7;
    else
      LOBYTE(v1) = 31;
  }
  else
  {
    LOBYTE(v1) = 0;
  }
  return v1;
}
