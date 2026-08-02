#include "pch.h"
unsigned __int8 __cdecl ext_CDR_lba_to_msf(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 *a4,
        unsigned __int8 *a5,
        unsigned __int8 *a6)
{
  unsigned __int8 v6; // bl
  unsigned int v7; // ecx
  unsigned __int8 result; // al
  unsigned int v9; // eax
  unsigned __int8 v10; // [esp+8h] [ebp-8h]

  v6 = 0;
  v7 = (a3 & 0xF) + 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4);
  v10 = 0;
  if ( 75
     * ((unsigned __int8)track_msf_seconds[3 * HIBYTE(first_last_tracks)]
      + 60 * (unsigned __int8)track_msf_minutes[3 * HIBYTE(first_last_tracks)])
     + (unsigned int)(unsigned __int8)track_msf_sectors[3 * HIBYTE(first_last_tracks)]
     - 150 > v7 )
  {
    result = HIBYTE(first_last_tracks);
    if ( HIBYTE(first_last_tracks) )
    {
      while ( 1 )
      {
        v9 = 75 * ((unsigned __int8)track_seconds_table[3 * v10] + 60 * (unsigned __int8)track_minutes_table[3 * v10])
           + (unsigned __int8)track_sectors_table[3 * v10]
           - 150;
        if ( v9 > v7 )
          break;
        result = HIBYTE(first_last_tracks);
        v10 = ++v6;
        if ( v6 >= HIBYTE(first_last_tracks) )
          return result;
      }
      *a4 = v9 / 0x4B / 0x3C;
      *a5 = v9 / 0x4B % 0x3C;
      *a6 = v9 % 0x4B;
      return (unsigned __int8)a5;
    }
  }
  else
  {
    *a4 = a1;
    *a5 = a2;
    *a6 = a3;
    return a2;
  }
  return result;
}
