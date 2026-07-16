#include "pch.h"
int __cdecl spucore_set_pitchmod(unsigned int a1)
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 24; ++i )
  {
    if ( (a1 & 1) != 0 )
      result = spucore_voice_key_off(i);
    a1 >>= 1;
  }
  return result;
}
