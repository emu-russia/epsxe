#include "pch.h"
__int16 __cdecl spucore_read_register(__int16 a1)
{
  unsigned int v1; // eax
  unsigned int v2; // eax

  v1 = (a1 & 0xFFF) - 3072;
  dword_4F75A0 = 0;
  if ( v1 >= 0x180 )
  {
    switch ( a1 & 0xFFF )
    {
      case 0xD80:
        LOWORD(v2) = spucore_mainvol_left;
        break;
      case 0xD82:
        LOWORD(v2) = spucore_mainvol_right;
        break;
      case 0xD84:
        LOWORD(v2) = spucore_reverb_vol_left;
        break;
      case 0xD86:
        LOWORD(v2) = spucore_reverb_vol_right;
        break;
      case 0xD90:
        LOWORD(v2) = spucore_pitchmod_enable;
        break;
      case 0xD92:
        LOWORD(v2) = HIWORD(spucore_pitchmod_enable);
        break;
      case 0xD94:
        LOWORD(v2) = spucore_noise_mode;
        break;
      case 0xD96:
        LOWORD(v2) = HIWORD(spucore_noise_mode);
        break;
      case 0xD98:
        LOWORD(v2) = dword_4E7100;
        break;
      case 0xD9A:
        LOWORD(v2) = HIWORD(dword_4E7100);
        break;
      case 0xD9C:
        LOWORD(v2) = dword_4EF138;
        break;
      case 0xD9E:
        LOWORD(v2) = HIWORD(dword_4EF138);
        break;
      case 0xDA2:
        LOWORD(v2) = byte_4EF142[0x3FFF];
        break;
      case 0xDA4:
        LOWORD(v2) = dword_463904;
        break;
      case 0xDA6:
        v2 = (unsigned int)dword_4F7554 >> 3;
        break;
      case 0xDA8:
        LOWORD(v2) = spucore_dma_read_fifo();
        break;
      case 0xDAA:
        LOWORD(v2) = spucore_read_cnt();
        break;
      case 0xDAC:
        LOWORD(v2) = spucore_read_dma_ctrl();
        break;
      case 0xDAE:
        LOWORD(v2) = spucore_read_status_hi();
        break;
      case 0xDB0:
        LOWORD(v2) = word_4E7104;
        break;
      case 0xDB2:
        LOWORD(v2) = word_4E7106;
        break;
      case 0xDB4:
        LOWORD(v2) = word_4F755C;
        break;
      case 0xDB6:
        LOWORD(v2) = word_4F7584;
        break;
      default:
        LOWORD(v2) = 0;
        break;
    }
  }
  else
  {
    LOWORD(v2) = spucore_read_voice_reg(v1 >> 4, a1 & 0xF);
  }
  return v2;
}
