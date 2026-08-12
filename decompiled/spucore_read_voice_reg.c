#include "pch.h"
__int16 __cdecl spucore_read_voice_reg(int a1, int a2)
{
  int v2; // eax
  signed int unknown17; // ecx
  uint32_t *p_unknown17; // eax

  switch ( a2 )
  {
    case 4:
      LOWORD(v2) = (__int64)(*(float *)&spu_voice_param[a1].adpcm_s1 * 4096.0) & 0x3FFF;
      break;
    case 6:
      LOWORD(v2) = spu_voice_param[a1].adsr_sustain_dir;
      break;
    case 12:
      if ( unknown_cd_setting )
      {
        LOWORD(v2) = rand() & 1;
      }
      else
      {
        unknown17 = spu_voice_param[a1].unknown17;
        p_unknown17 = &spu_voice_param[a1].unknown17;
        if ( unknown17 <= 0xFFFFFF )
        {
          if ( unknown17 < 0 )
            *p_unknown17 = 0;
          return (int)*p_unknown17 >> 9;
        }
        else
        {
          *p_unknown17 = 0xFFFFFF;
          return (int)*p_unknown17 >> 9;
        }
      }
      break;
    default:
      LOWORD(v2) = 0;
      break;
  }
  return v2;
}
