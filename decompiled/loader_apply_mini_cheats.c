#include "pch.h"
char __cdecl loader_apply_mini_cheats(const char *a1)
{
  char result; // al
  int *v2; // ebp
  int v3; // edi
  int v4; // ebp
  int v5; // esi
  char v6; // al
  bool v7; // zf
  const char *v8; // [esp+0h] [ebp-8h]
  int v9; // [esp+4h] [ebp-4h]

  result = noauto;
  if ( !noauto )
  {
    result = mini_cheat_count;
    if ( mini_cheat_count )
    {
      v2 = (int *)&mini_cheat_db[20];
      v8 = &mini_cheat_db[20];
      v9 = mini_cheat_count;
      do
      {
        if ( !strcmp(a1, (const char *)v2 - 20) && (unsigned __int8)active_mini_cheat_count < 0x10u )
        {
          v3 = *v2;
          v4 = *(v2 - 1);
          v5 = 2 * (unsigned __int8)active_mini_cheat_count;
          mini_cheat_attr_array[v5] = v3;
          mini_cheat_id_array[v5] = v4;
          if ( !loader_mini_cheat_find_by_id(v4, v3) )
          {
            v6 = active_mini_cheat_count + 1;
            mini_cheat_attr_array[v5] = v3;
            mini_cheat_id_array[v5] = v4;
            active_mini_cheat_count = v6;
          }
          v2 = (int *)v8;
        }
        v2 += 6;
        result = v9 - 1;
        v7 = v9 == 1;
        v8 = (const char *)v2;
        --v9;
      }
      while ( !v7 );
    }
  }
  return result;
}
