#include "pch.h"
char __cdecl sub_41BC30(int a1, int a2)
{
  unsigned __int8 v2; // cl
  int v3; // eax

  v2 = 0;
  if ( mini_cheat_count <= 0 )
    return 0;
  v3 = 0;
  while ( a1 != dword_5B6DC4[2 * v3] || a2 != *(_DWORD *)&mini_cheat_db[24 * v3 + 20] )
  {
    v3 = ++v2;
    if ( v2 >= mini_cheat_count )
      return 0;
  }
  return 1;
}
