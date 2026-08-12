#include "pch.h"
int __cdecl spucore_voice_key_off(int a1)
{
  int result; // eax

  result = 296 * a1;
  if ( spu_voice_param[a1].current_block_addr )
  {
    spu_voice_param[a1].current_block_addr = 4;
  }
  else
  {
    spu_voice_param[a1].unknown17 = 0;
    spu_voice_param[a1].sample_history[1] = 0;
  }
  return result;
}
