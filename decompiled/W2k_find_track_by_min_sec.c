#include "pch.h"
char __cdecl W2k_find_track_by_min_sec(unsigned int a1, char a2)
{
  char v2; // bl
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  v4 = 0;
  if ( !byte_4FD9E3 )
    return 0;
  v2 = a1;
  while ( 1 )
  {
    W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * v4 + 5241928));
    a1 += 150;
    if ( (unsigned __int8)(a1 / 0x4B / 0x3C) == v2 && a1 / 0x4B % 0x3C == a2 )
      break;
    if ( ++v4 >= (unsigned __int8)byte_4FD9E3 )
      return 0;
  }
  return a1 % 0x4B;
}
