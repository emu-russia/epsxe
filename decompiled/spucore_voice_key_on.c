#include "pch.h"
int __cdecl spucore_voice_key_on(int a1)
{
  int result; // eax
  uint32_t adsr_sustain_dir; // edx

  result = a1;
  adsr_sustain_dir = spu_voice_param[a1].adsr_sustain_dir;
  spu_voice_param[result].current_block_addr = 1;
  spu_voice_param[result].sample_history[1] = 0;
  spu_voice_param[result].sample_history[2] = adsr_sustain_dir;
  spu_voice_param[result].adpcm_s0 = 0;
  spu_voice_param[result].unknown3E = 0;
  return result * 296;
}
