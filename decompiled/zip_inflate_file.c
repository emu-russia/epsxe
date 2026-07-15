#include "pch.h"
int zip_inflate_file()
{
  unsigned int v0; // esi
  int result; // eax
  int v2; // [esp+8h] [ebp-4h] BYREF

  zip_inflate_window_pos = 0;
  zip_inflate_bit_count = 0;
  zip_inflate_bit_buffer = 0;
  v0 = 0;
  while ( 1 )
  {
    zip_inflate_max_memory_used = 0;
    result = zip_inflate_block(&v2);
    if ( result )
      break;
    if ( zip_inflate_max_memory_used > v0 )
      v0 = zip_inflate_max_memory_used;
    if ( v2 )
    {
      zip_copy_sliding_window_to_output(zip_sliding_window, zip_inflate_window_pos);
      return 0;
    }
  }
  return result;
}
