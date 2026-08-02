#include "pch.h"
char __cdecl ext_CDR_bcd_to_binary(char a1, char a2)
{
  unsigned __int8 v3; // [esp+4h] [ebp-4h]

  v3 = 0;
  if ( !HIBYTE(first_last_tracks) )
    return 0;
  while ( a1 != track_msf_minutes[3 * v3] || a2 != track_msf_seconds[3 * v3] )
  {
    if ( ++v3 >= HIBYTE(first_last_tracks) )
      return 0;
  }
  return track_msf_sectors[3 * v3];
}
