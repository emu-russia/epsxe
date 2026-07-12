#include "pch.h"
char __cdecl spu_play_adpcm(int a1)
{
  int v1; // eax

  LOBYTE(v1) = sound_enabled;
  if ( sound_enabled )
  {
    LOBYTE(v1) = sound_use_xa;
    if ( sound_use_xa )
    {
      v1 = xa_decode_wrapper(dword_4E7108, a1, spu_adpcm_flag);
      if ( !v1 && (dword_4E7114 || (LOBYTE(v1) = spu_use_external_plugin) == 0) )
        LOBYTE(v1) = SPUplayADPCMchannel(dword_4E7108);
      spu_adpcm_flag = 0;
    }
  }
  return v1;
}
