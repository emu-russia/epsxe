#include "pch.h"
char __cdecl ext_CDR_track_to_msf(__int16 a1, _BYTE *a2, _BYTE *a3, _BYTE *a4)
{
  char result; // al

  if ( a1 <= (int)HIBYTE(first_last_tracks) )
  {
    if ( a1 )
    {
      *a2 = track_msf_table[3 * a1];
      *a3 = *((_BYTE *)&first_last_tracks + 3 * a1);
      result = *((_BYTE *)&first_last_tracks + 3 * a1 + 1);
      *a4 = result;
    }
    else
    {
      *a2 = track_msf_minutes[3 * HIBYTE(first_last_tracks)];
      *a3 = track_msf_seconds[3 * HIBYTE(first_last_tracks)];
      result = HIBYTE(first_last_tracks);
      *a4 = track_msf_sectors[3 * HIBYTE(first_last_tracks)];
    }
  }
  else
  {
    *a2 = 0;
    *a3 = 2;
    *a4 = 0;
    return (char)a2;
  }
  return result;
}
