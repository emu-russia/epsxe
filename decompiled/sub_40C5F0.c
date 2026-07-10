#include "pch.h"
int __cdecl sub_40C5F0(int a1)
{
  int result; // eax

  result = 296 * a1;
  if ( dword_4655A4[74 * a1] )
  {
    dword_4655A4[74 * a1] = 4;
  }
  else
  {
    dword_46559C[74 * a1] = 0;
    dword_4655B8[74 * a1] = 0;
  }
  return result;
}
