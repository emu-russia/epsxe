#include "pch.h"
unsigned int zip_inflate_file()
{
  unsigned int v0; // esi
  unsigned int result; // eax
  int v2; // [esp+8h] [ebp-4h] BYREF

  dword_4F8324 = 0;
  dword_4F832C = 0;
  dword_4F8328 = 0;
  v0 = 0;
  while ( 1 )
  {
    dword_4F8340 = 0;
    result = zip_inflate_buffer(&v2);
    if ( result )
      break;
    if ( dword_4F8340 > v0 )
      v0 = dword_4F8340;
    if ( v2 )
    {
      zip_move_window(zip_sliding_window, dword_4F8324);
      return 0;
    }
  }
  return result;
}
