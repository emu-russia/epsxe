#include "pch.h"
char __cdecl ext_CDR_lba_to_msf_with_track(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        _BYTE *a5,
        _BYTE *a6,
        _BYTE *a7)
{
  unsigned int v7; // ebp
  unsigned __int8 v8; // dl
  int v9; // eax
  unsigned int v10; // edi
  unsigned int v11; // esi
  unsigned __int8 v13; // [esp+Ch] [ebp-4h]

  v7 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4) + (a3 & 0xF) - 150;
  v8 = HIBYTE(first_last_tracks);
  v13 = 0;
  v9 = (unsigned __int8)track_msf_sectors[3 * HIBYTE(first_last_tracks)];
  if ( 75
     * ((unsigned __int8)track_msf_seconds[3 * HIBYTE(first_last_tracks)]
      + 60 * (unsigned int)(unsigned __int8)track_msf_minutes[3 * HIBYTE(first_last_tracks)])
     + v9
     - 150 > v7 )
  {
    if ( HIBYTE(first_last_tracks) )
    {
      while ( 1 )
      {
        v10 = 75 * ((unsigned __int8)track_seconds_table[3 * v13] + 60 * (unsigned __int8)track_minutes_table[3 * v13])
            + (unsigned __int8)track_sectors_table[3 * v13]
            - 150;
        if ( v13 + 1 < HIBYTE(first_last_tracks) )
        {
          v10 -= v10 % 0x4B;
          v8 = HIBYTE(first_last_tracks);
        }
        if ( v10 > v7 )
          break;
        if ( ++v13 >= v8 )
          goto LABEL_8;
      }
      v11 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4))))
          + 10 * (a3 >> 4)
          + (a3 & 0xF)
          + (75 * ((unsigned __int8)track_msf_seconds[3 * v13] + 60 * (unsigned __int8)track_msf_minutes[3 * v13])
           + (unsigned int)(unsigned __int8)track_msf_sectors[3 * v13]
           - 150)
          % 0x4B
          - (75 * ((unsigned __int8)track_msf_seconds[3 * v13] + 60 * (unsigned __int8)track_msf_minutes[3 * v13])
           + (unsigned __int8)track_msf_sectors[3 * v13]);
      *a4 = (v13 + 1) % 10 + 16 * ((v13 + 1) / 10);
      *a5 = v11 / 0x4B / 0x3C % 0xA + 16 * (v11 / 0x4B / 0x3C / 0xA);
      *a6 = v11 / 0x4B % 0x3C % 0xA + 16 * (v11 / 0x4B % 0x3C / 0xA);
      LOBYTE(v9) = v11 % 0x4B % 0xA + 16 * (v11 % 0x4B / 0xA);
      *a7 = v9;
    }
    else
    {
LABEL_8:
      *a4 = -86;
      LOBYTE(v9) = (_BYTE)a4;
    }
  }
  else
  {
    *a4 = -86;
  }
  return v9;
}
