#include "pch.h"
int __cdecl spucore_unfreeze(int a1, _DWORD *a2)
{
  char *v2; // edi
  uint32_t *p_adsr_lower; // esi
  unsigned int v4; // ebp
  unsigned __int16 v5; // ax
  int v6; // ecx
  int v7; // edx
  unsigned __int16 v8; // ax
  int v9; // ecx
  double v10; // st7
  double v11; // st7
  unsigned __int16 v12; // ax
  char v13; // dl
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // eax
  int v19; // edx
  unsigned __int16 v20; // ax
  int v21; // ecx
  int v22; // edx
  int v23; // ebx
  int v24; // eax
  int v25; // edx
  int v26; // ecx
  int v27; // ebp
  int v28; // edi
  int v29; // esi
  int v30; // edx
  __int16 *v31; // ecx
  int v32; // ebx
  int result; // eax
  int v34; // [esp+10h] [ebp-220h]
  int v35; // [esp+10h] [ebp-220h]
  int v36; // [esp+14h] [ebp-21Ch]
  int v37; // [esp+18h] [ebp-218h]
  char Str1[12]; // [esp+24h] [ebp-20Ch] BYREF
  char v39[384]; // [esp+30h] [ebp-200h] BYREF
  char v40; // [esp+1B0h] [ebp-80h] BYREF

  gzread(a2, v39, 7);
  gzread(a2, Str1, 8);
  gzread(a2, v39, 8);
  gzread(a2, v39, 512);
  v2 = v39;
  p_adsr_lower = &spu_voice_param[0].adsr_lower;
  v34 = 24;
  do
  {
    v4 = 0;
    v36 = 8;
    do
    {
      if ( v4 <= 0xE )
      {
        switch ( v4 )
        {
          case 0u:
            v5 = *(_WORD *)v2;
            v6 = (*(unsigned __int16 *)v2 >> 14) & 1;
            v7 = *(_WORD *)v2 & 0x3FFF;
            *p_adsr_lower = v6;
            p_adsr_lower[2] = v6;
            *(p_adsr_lower - 4) = v7;
            p_adsr_lower[4] = (v5 >> 13) & 1;
            p_adsr_lower[6] = v5 >> 15;
            *(p_adsr_lower - 2) = v5 & 0x7F;
            break;
          case 1u:
          case 3u:
          case 5u:
          case 7u:
          case 9u:
          case 0xBu:
          case 0xDu:
            break;
          case 2u:
            v8 = *((_WORD *)v2 + 1);
            *(p_adsr_lower - 3) = v8 & 0x3FFF;
            v9 = (v8 >> 14) & 1;
            p_adsr_lower[1] = v9;
            p_adsr_lower[3] = v9;
            p_adsr_lower[5] = (v8 >> 13) & 1;
            p_adsr_lower[7] = v8 >> 15;
            *(p_adsr_lower - 1) = v8 & 0x7F;
            break;
          case 4u:
            v10 = (double)(*((_WORD *)v2 + 2) & 0x3FFF);
            p_adsr_lower[8] = *((_WORD *)v2 + 2) & 0x3FFF;
            v11 = v10 * 0.000244140625;
            *((float *)p_adsr_lower + 24) = v11;
            p_adsr_lower[25] = (__int64)(v11 * 65536.0);
            break;
          case 6u:
            p_adsr_lower[9] = *((unsigned __int16 *)v2 + 3);
            break;
          case 8u:
            v12 = *((_WORD *)v2 + 4);
            v13 = v2[9];
            p_adsr_lower[10] = v12 >> 15;
            v14 = v13 & 0x7F;
            v15 = (unsigned __int8)v12 >> 4;
            p_adsr_lower[11] = v14;
            v16 = dword_44F208[v14];
            p_adsr_lower[12] = v15;
            v17 = dword_44F408[v15];
            v18 = v12 & 0xF;
            p_adsr_lower[65] = v16;
            v19 = dword_44F648[v18];
            p_adsr_lower[13] = v18;
            p_adsr_lower[66] = -v17;
            p_adsr_lower[67] = v19;
            break;
          case 0xAu:
            v20 = *((_WORD *)v2 + 5);
            p_adsr_lower[14] = v20 >> 15;
            v21 = (v20 >> 14) & 1;
            v22 = (v20 >> 6) & 0x7F;
            v23 = (v20 >> 5) & 1;
            v24 = v20 & 0x1F;
            p_adsr_lower[15] = v21;
            p_adsr_lower[16] = v22;
            p_adsr_lower[17] = v23;
            p_adsr_lower[18] = v24;
            if ( v21 )
            {
              v26 = -dword_44F448[v22];
              v25 = -dword_44F688[v24];
              p_adsr_lower[68] = v26;
            }
            else
            {
              p_adsr_lower[68] = dword_44F448[v22];
              v25 = -dword_44F688[v24];
            }
            p_adsr_lower[69] = v25;
            break;
          case 0xCu:
            v37 = *((unsigned __int16 *)v2 + 6) << 9;
            p_adsr_lower[19] = v37;
            *((float *)p_adsr_lower + 26) = (double)v37 * 0.000030517578125;
            break;
          case 0xEu:
            p_adsr_lower[20] = *((unsigned __int16 *)v2 + 7);
            break;
        }
      }
      v4 += 2;
      --v36;
    }
    while ( v36 );
    v2 += 16;
    p_adsr_lower += 74;
    --v34;
  }
  while ( v34 );
  v27 = spucore_pitchmod_enable;
  v28 = spucore_noise_mode;
  v29 = dword_4E7100;
  v30 = dword_4EF138;
  v31 = (__int16 *)&v40;
  v32 = 0;
  v35 = 64;
  do
  {
    switch ( v32 )
    {
      case 0:
        spucore_mainvol_left = *v31;
        break;
      case 2:
        LOWORD(spucore_mainvol_right) = *v31;
        break;
      case 4:
        spucore_reverb_vol_left = *v31;
        break;
      case 6:
        spucore_reverb_vol_right = *v31;
        break;
      case 16:
        v27 = (unsigned __int16)*v31;
        break;
      case 18:
        v27 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v27;
        break;
      case 20:
        v28 = (unsigned __int16)*v31;
        break;
      case 22:
        v28 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v28;
        break;
      case 24:
        v29 = (unsigned __int16)*v31;
        break;
      case 26:
        v29 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v29;
        break;
      case 28:
        v30 = (unsigned __int16)*v31;
        break;
      case 30:
        v30 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v30;
        break;
      case 34:
        byte_4EF142[0x3FFF] = *v31;
        break;
      case 36:
        LOWORD(dword_463904) = *v31;
        break;
      case 42:
        spucore_write_cnt(*v31);
        break;
      case 44:
        spucore_write_dma_ctrl(*v31);
        break;
      case 46:
        spucore_write_status_hi(*v31);
        break;
      case 48:
        word_4E7104 = *v31;
        break;
      case 50:
        word_4E7106 = *v31;
        break;
      case 52:
        word_4F755C = *v31;
        break;
      case 54:
        word_4F7584 = *v31;
        break;
      default:
        break;
    }
    v32 += 2;
    ++v31;
    --v35;
  }
  while ( v35 );
  dword_4E7100 = v29;
  dword_4EF138 = v30;
  spucore_noise_mode = v28;
  spucore_pitchmod_enable = v27;
  gzread(a2, (char *)spu_ram, 0x80000);
  gzread(a2, dword_4E7108, 32800);
  dword_44F7A0 = *(_DWORD *)dword_4E7108;
  if ( dword_4E7114 > 4096 )
    dword_4E7114 = 0;
  result = strncmp(Str1, "ISPU", 4u);
  if ( !result )
    return gzread(a2, (char *)spu_voice_param, 7104);
  return result;
}
