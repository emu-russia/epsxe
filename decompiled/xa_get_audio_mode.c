#include "pch.h"
int __cdecl xa_get_audio_mode(int a1)
{
  if ( (*(_BYTE *)(a1 + 2) & 0x24) == 0x24 )
    return 2;
  else
    return (*(_BYTE *)(a1 + 2) & 2) == 2;
}
