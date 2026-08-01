#include "pch.h"
char __cdecl loader_mini_cheat_find_by_id(int a1, int a2)
{
  unsigned __int8 v2; // cl
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  v2 = 0;
  v4 = 0;
  if ( !active_mini_cheat_count )
    return 0;
  while ( a1 != mini_cheat_id_array[2 * v4] || a2 != *(_DWORD *)&mini_cheat_db[24 * v4 + 20] )
  {
    v4 = ++v2;
    if ( v2 >= (unsigned __int8)active_mini_cheat_count )
      return 0;
  }
  return 1;
}
