#include "pch.h"
int __cdecl xa_decode_wrapper(_DWORD *a1, int a2, int a3)
{
  if ( xa_get_audio_mode(a2) == 2 )
    return -(xa_setup_adpcm_decoder(a1, a2, a2 + 8, a3) != 0);
  else
    return -1;
}
