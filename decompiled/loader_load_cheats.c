#include "pch.h"
FILE *loader_load_cheats()
{
  FILE *v0; // eax
  FILE *v1; // edi
  int v2; // esi
  FILE *result; // eax
  FILE *v4; // esi
  int v5; // eax

  v0 = fopen("cheats\\database.dat", "rb");
  v1 = v0;
  if ( v0 )
  {
    if ( (v0->_flag & 0x10) == 0 )
    {
      v2 = mini_cheat_count;
      do
      {
        if ( v2 >= 200 )
          break;
        fread((void *)(24 * v2 + 4520368), 1u, 0x18u, v1);
        v2 = mini_cheat_count;
        if ( !sub_41BC30(
                *(_DWORD *)&mini_cheat_db[24 * mini_cheat_count + 16],
                *(_DWORD *)&mini_cheat_db[24 * mini_cheat_count + 20]) )
          mini_cheat_count = ++v2;
      }
      while ( (v1->_flag & 0x10) == 0 );
    }
    fclose(v1);
  }
  result = fopen("cheats\\dataconf.dat", "rb");
  v4 = result;
  if ( result )
  {
    if ( (result->_flag & 0x10) == 0 )
    {
      v5 = cheat_entries_count;
      do
      {
        if ( v5 >= 200 )
          break;
        fread(&cheat_db[v5], 1u, 81u, v4);
        v5 = ++cheat_entries_count;
      }
      while ( (v4->_flag & 0x10) == 0 );
    }
    return (FILE *)fclose(v4);
  }
  return result;
}
