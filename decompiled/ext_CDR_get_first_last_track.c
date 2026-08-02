#include "pch.h"
char __cdecl ext_CDR_get_first_last_track(_BYTE *a1, _BYTE *a2)
{
  char result; // al

  *a1 = first_last_tracks;
  result = HIBYTE(first_last_tracks);
  *a2 = HIBYTE(first_last_tracks);
  return result;
}
