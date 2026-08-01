#include "pch.h"
size_t __cdecl loader_pll_get_file_size(const char *a1)
{
  size_t result; // eax
  unsigned int v2; // edi
  const char *v3; // ebp
  size_t v4; // [esp+8h] [ebp-4h]

  result = 0x100000;
  v2 = 0;
  v4 = 0x100000;
  if ( zip_num_entries_loaded )
  {
    v3 = zip_entry_names;
    do
    {
      if ( !strcmp(v3, a1) )
        v4 = Size[v2];
      ++v2;
      v3 += 256;
    }
    while ( v2 < zip_num_entries_loaded );
    return v4;
  }
  return result;
}
