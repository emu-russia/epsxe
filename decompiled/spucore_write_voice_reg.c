#include "pch.h"
int __cdecl spucore_write_voice_reg(int a1, int a2, unsigned __int16 a3)
{
  __int64 v3; // rax
  int v4; // ecx
  int v5; // ecx
  int v6; // esi
  double v7; // st7
  int v8; // esi
  int v9; // ecx
  uint32_t v10; // ecx
  int v11; // esi
  int v12; // ecx
  bool v13; // zf
  uint32_t v14; // ecx
  __int64 v16; // [esp+4h] [ebp-8h]

  LODWORD(v3) = a2;
  switch ( a2 )
  {
    case 0:
      v4 = a1;
      spu_voice_param[v4].volume_left = a3 & 0x3FFF;
      HIDWORD(v3) = (a3 >> 14) & 1;
      spu_voice_param[v4].adsr_lower = HIDWORD(v3);
      spu_voice_param[v4].current_adsr_vol = HIDWORD(v3);
      spu_voice_param[v4].adsr_attack_mode = (a3 >> 13) & 1;
      LODWORD(v3) = a3 & 0x7F;
      spu_voice_param[v4].adsr_attack_step = a3 >> 15;
      spu_voice_param[v4].pitch = v3;
      break;
    case 2:
      v5 = a1;
      spu_voice_param[v5].volume_right = a3 & 0x3FFF;
      HIDWORD(v3) = (a3 >> 14) & 1;
      spu_voice_param[v5].adsr_upper = HIDWORD(v3);
      spu_voice_param[v5].repeat_addr = HIDWORD(v3);
      spu_voice_param[v5].adsr_attack_shift = (a3 >> 13) & 1;
      LODWORD(v3) = a3 & 0x7F;
      spu_voice_param[v5].adsr_decay_shift = a3 >> 15;
      spu_voice_param[v5].start_addr = v3;
      break;
    case 4:
      v6 = a1;
      v16 = a3 & 0x3FFF;
      spu_voice_param[v6].adsr_sustain_mode = v16;
      v7 = (double)v16 * 0.000244140625;
      *(float *)(v6 * 296 + 4609456) = v7;
      v3 = (__int64)(v7 * 65536.0);
      spu_voice_param[v6].sample_history[0] = v3;
      break;
    case 6:
      spu_voice_param[a1].adsr_sustain_dir = a3;
      LODWORD(v3) = a3;
      break;
    case 8:
      LODWORD(v3) = 296 * a1;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_sustain_shift + v3) = a3 >> 15;
      HIDWORD(v3) = HIBYTE(a3) & 0x7F;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_sustain_step + v3) = HIDWORD(v3);
      v8 = (unsigned __int8)a3 >> 4;
      v9 = a3 & 0xF;
      *(int32_t *)((char *)&spu_voice_param[0].pitch_mod_param + v3) = dword_44F208[HIDWORD(v3)];
      HIDWORD(v3) = dword_44F408[v8];
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_release_mode + v3) = v9;
      v10 = dword_44F648[v9];
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_sustain_level + v3) = v8;
      *(int32_t *)((char *)&spu_voice_param[0].pitch_mod_param2 + v3) = -HIDWORD(v3);
      *(uint32_t *)((char *)&spu_voice_param[0].unknown47 + v3) = v10;
      break;
    case 10:
      LODWORD(v3) = 296 * a1;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_release_shift + v3) = a3 >> 15;
      HIDWORD(v3) = (a3 >> 14) & 1;
      v11 = (a3 >> 6) & 0x7F;
      v12 = a3 & 0x1F;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_envelope + v3) = HIDWORD(v3);
      *(uint32_t *)((char *)&spu_voice_param[0].voice_state + v3) = (a3 >> 5) & 1;
      v13 = HIDWORD(v3) == 0;
      HIDWORD(v3) = dword_44F448[v11];
      *(uint32_t *)((char *)&spu_voice_param[0].loop_start_addr + v3) = v11;
      *(uint32_t *)((char *)&spu_voice_param[0].pitch_mod_factor + v3) = v12;
      if ( !v13 )
        HIDWORD(v3) = -HIDWORD(v3);
      v14 = -dword_44F688[v12];
      spu_voice_param[a1].unknown48 = HIDWORD(v3);
      spu_voice_param[a1].unknown49 = v14;
      break;
    case 12:
      spu_voice_param[a1].unknown17 = a3 << 9;
      LODWORD(v3) = 296 * a1;
      break;
    case 14:
      spu_voice_param[a1].pitch_multiplier = a3;
      break;
    default:
      return v3;
  }
  return v3;
}
