#include "pch.h"
char __cdecl sub_41BD60(int a1, int a2)
{
  unsigned __int8 v2; // cl
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  v2 = 0;
  v4 = 0;
  if ( !(_BYTE)dword_4F831C )
    return 0;
  while ( a1 != dword_5B6DC4[2 * v4] || a2 != *(_DWORD *)&mini_cheat_db[24 * v4 + 20] )
  {
    v4 = ++v2;
    if ( v2 >= (unsigned __int8)dword_4F831C )
      return 0;
  }
  return 1;
}
