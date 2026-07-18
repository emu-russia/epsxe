#include "pch.h"
__int16 __cdecl spucore_write_register(__int16 a1, unsigned __int16 a2)
{
  unsigned int v2; // eax
  __int16 result; // ax

  v2 = (a1 & 0xFFF) - 3072;
  dword_4F75A0 = 0;
  if ( v2 < 0x180 )
    return spucore_write_voice_reg(v2 >> 4, a1 & 0xF, a2);
  result = (a1 & 0xFFF) - 3456;
  switch ( a1 & 0xFFF )
  {
    case 0xD80:
      spucore_mainvol_left = a2 & 0x3FFF;
      break;
    case 0xD82:
      LOWORD(spucore_mainvol_right) = a2 & 0x3FFF;
      result = a2 & 0x3FFF;
      break;
    case 0xD84:
      spucore_reverb_vol_left = a2;
      break;
    case 0xD86:
      spucore_reverb_vol_right = a2;
      break;
    case 0xD88:
      result = spucore_set_voiceon(a2);
      break;
    case 0xD8A:
      result = spucore_set_voiceon(a2 << 16);
      break;
    case 0xD8C:
      result = spucore_set_pitchmod(a2);
      break;
    case 0xD8E:
      result = spucore_set_pitchmod(a2 << 16);
      break;
    case 0xD90:
      spucore_pitchmod_enable = a2 + (spucore_pitchmod_enable & 0xFF0000);
      break;
    case 0xD92:
      result = spucore_pitchmod_enable;
      spucore_pitchmod_enable = (unsigned __int16)spucore_pitchmod_enable + (a2 << 16);
      break;
    case 0xD94:
      spucore_noise_mode = a2 + (spucore_noise_mode & 0xFF0000);
      result = a2;
      break;
    case 0xD96:
      spucore_noise_mode = (unsigned __int16)spucore_noise_mode + (a2 << 16);
      break;
    case 0xD98:
      dword_4E7100 = a2 + (dword_4E7100 & 0xFF0000);
      result = a2;
      break;
    case 0xD9A:
      result = dword_4E7100;
      dword_4E7100 = (unsigned __int16)dword_4E7100 + (a2 << 16);
      break;
    case 0xD9C:
      dword_4EF138 = a2 + (dword_4EF138 & 0xFF0000);
      break;
    case 0xD9E:
      result = dword_4EF138;
      dword_4EF138 = (unsigned __int16)dword_4EF138 + (a2 << 16);
      break;
    case 0xDA2:
      byte_4EF142[0x3FFF] = a2;
      break;
    case 0xDA4:
      LOWORD(dword_463904) = a2;
      result = a2;
      break;
    case 0xDA6:
      result = spucore_set_dma_address(a2);
      break;
    case 0xDA8:
      result = spucore_dma_write_fifo(a2);
      break;
    case 0xDAA:
      result = spucore_write_cnt(a2);
      break;
    case 0xDAC:
      result = spucore_write_dma_ctrl(a2);
      break;
    case 0xDAE:
      result = spucore_write_status_hi(a2);
      break;
    case 0xDB0:
      word_4E7104 = a2;
      result = a2;
      break;
    case 0xDB2:
      word_4E7106 = a2;
      break;
    case 0xDB4:
      word_4F755C = a2;
      break;
    case 0xDB6:
      word_4F7584 = a2;
      result = a2;
      break;
    default:
      return result;
  }
  return result;
}
