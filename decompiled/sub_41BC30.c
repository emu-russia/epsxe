#include "pch.h"
char __cdecl sub_41BC30(int a1, int a2)
{
  unsigned __int8 v2; // cl
  int v3; // eax

  v2 = 0;
  if ( dword_44F9A8 <= 0 )
    return 0;
  v3 = 0;
  while ( a1 != dword_5B6DC4[2 * v3] || a2 != dword_44F9C4[6 * v3] )
  {
    v3 = ++v2;
    if ( v2 >= dword_44F9A8 )
      return 0;
  }
  return 1;
}
