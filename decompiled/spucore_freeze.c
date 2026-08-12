#include "pch.h"
int __cdecl spucore_freeze(const char *a1, int a2)
{
  int v2; // edx
  char *v3; // esi
  uint32_t *p_adsr_lower; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // ebp
  int v8; // kr08_4
  int v9; // edx
  int v10; // edx
  int v11; // edx
  __int16 v12; // bx
  __int16 v13; // di
  __int16 v14; // bp
  unsigned __int8 v15; // bl
  __int16 *v16; // ecx
  int v17; // edx
  int v18; // esi
  uint32_t *v19; // kr10_4
  char Buffer[384]; // [esp+10h] [ebp-200h] BYREF
  char v22; // [esp+190h] [ebp-80h] BYREF

  sprintf(Buffer, "%s", a1);
  *(_DWORD *)&Buffer[3] = 564744;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  sprintf(Buffer, "ISPU");
  gzwrite(a2, (unsigned __int8 *)Buffer, 8u);
  *(_QWORD *)Buffer = 0x89DF800000002LL;
  gzwrite(a2, (unsigned __int8 *)Buffer, 8u);
  v3 = &Buffer[2];
  p_adsr_lower = &spu_voice_param[0].adsr_lower;
  v5 = 24;
  do
  {
    v6 = 0;
    v7 = 8;
    do
    {
      v8 = v2;
      v2 = 0;
      switch ( v6 )
      {
        case 0:
          v9 = 2 * (unsigned __int16)(*(_WORD *)p_adsr_lower | (2 * *((_WORD *)p_adsr_lower + 12)));
          LOWORD(v9) = *((_WORD *)p_adsr_lower + 8) | v9;
          v2 = v9 << 13;
          LOWORD(v2) = *((_WORD *)p_adsr_lower - 8) | v2;
          *((_WORD *)v3 - 1) = v2;
          break;
        case 2:
          v10 = 2 * (unsigned __int16)(*((_WORD *)p_adsr_lower + 2) | (2 * *((_WORD *)p_adsr_lower + 14)));
          LOWORD(v10) = *((_WORD *)p_adsr_lower + 10) | v10;
          v2 = v10 << 13;
          LOWORD(v2) = *((_WORD *)p_adsr_lower - 6) | v2;
          *(_WORD *)v3 = v2;
          break;
        case 4:
          LOWORD(v2) = *((_WORD *)p_adsr_lower + 16);
          *((_WORD *)v3 + 1) = v2;
          break;
        case 6:
          LOWORD(v2) = *((_WORD *)p_adsr_lower + 18);
          *((_WORD *)v3 + 2) = v2;
          break;
        case 8:
          v11 = 16 * (unsigned __int16)(*((_WORD *)p_adsr_lower + 22) | (*((_WORD *)p_adsr_lower + 20) << 7));
          LOWORD(v11) = *((_WORD *)p_adsr_lower + 24) | v11;
          v2 = 16 * v11;
          LOWORD(v2) = *((_WORD *)p_adsr_lower + 26) | v2;
          *((_WORD *)v3 + 3) = v2;
          break;
        case 10:
          LOBYTE(v2) = *((_BYTE *)p_adsr_lower + 60) | (2 * *((_BYTE *)p_adsr_lower + 56));
          LOBYTE(v12) = 0;
          HIBYTE(v12) = v2;
          *((_WORD *)v3 + 4) = *((_WORD *)p_adsr_lower + 36)
                             | (32 * (*((_WORD *)p_adsr_lower + 34) | (2 * (*((_WORD *)p_adsr_lower + 32) | v12))));
          break;
        case 12:
          v2 = (int)p_adsr_lower[19] >> 9;
          *((_WORD *)v3 + 5) = v2;
          break;
        case 14:
          LOWORD(v2) = *((_WORD *)p_adsr_lower + 40);
          *((_WORD *)v3 + 6) = v2;
          break;
        default:
          v2 = v8;
          break;
      }
      v6 += 2;
      --v7;
    }
    while ( v7 );
    p_adsr_lower += 74;
    v3 += 16;
    --v5;
  }
  while ( v5 );
  v13 = spucore_mainvol_left;
  v14 = spucore_mainvol_right;
  v15 = BYTE2(spucore_pitchmod_enable);
  v16 = (__int16 *)&v22;
  v17 = 0;
  v18 = 64;
  do
  {
    v19 = p_adsr_lower;
    p_adsr_lower = nullptr;
    switch ( v17 )
    {
      case 0:
        *v16 = v13;
        break;
      case 2:
        *v16 = v14;
        break;
      case 4:
        LOWORD(p_adsr_lower) = spucore_reverb_vol_left;
        goto LABEL_37;
      case 6:
        LOWORD(p_adsr_lower) = spucore_reverb_vol_right;
        goto LABEL_37;
      case 16:
        LOWORD(p_adsr_lower) = spucore_pitchmod_enable;
        goto LABEL_37;
      case 18:
        p_adsr_lower = (uint32_t *)v15;
        goto LABEL_37;
      case 20:
        LOWORD(p_adsr_lower) = spucore_noise_mode;
        goto LABEL_37;
      case 22:
        p_adsr_lower = (uint32_t *)BYTE2(spucore_noise_mode);
        goto LABEL_37;
      case 24:
        LOWORD(p_adsr_lower) = dword_4E7100;
        goto LABEL_37;
      case 26:
        p_adsr_lower = (uint32_t *)BYTE2(dword_4E7100);
        goto LABEL_37;
      case 28:
        LOWORD(p_adsr_lower) = dword_4EF138;
        goto LABEL_37;
      case 30:
        p_adsr_lower = (uint32_t *)BYTE2(dword_4EF138);
        goto LABEL_37;
      case 34:
        LOWORD(p_adsr_lower) = byte_4EF142[0x3FFF];
        goto LABEL_37;
      case 36:
        LOWORD(p_adsr_lower) = dword_463904;
        goto LABEL_37;
      case 42:
        LOWORD(p_adsr_lower) = spucore_read_cnt();
        goto LABEL_37;
      case 44:
        LOWORD(p_adsr_lower) = spucore_read_dma_ctrl();
        goto LABEL_37;
      case 46:
        LOWORD(p_adsr_lower) = spucore_read_status_hi();
        goto LABEL_37;
      case 48:
        LOWORD(p_adsr_lower) = word_4E7104;
        goto LABEL_37;
      case 50:
        LOWORD(p_adsr_lower) = word_4E7106;
        goto LABEL_37;
      case 52:
        LOWORD(p_adsr_lower) = word_4F755C;
        goto LABEL_37;
      case 54:
        LOWORD(p_adsr_lower) = word_4F7584;
LABEL_37:
        *v16 = (__int16)p_adsr_lower;
        break;
      default:
        p_adsr_lower = v19;
        break;
    }
    v17 += 2;
    ++v16;
    --v18;
  }
  while ( v18 );
  gzwrite(a2, (unsigned __int8 *)Buffer, 0x200u);
  gzwrite(a2, (unsigned __int8 *)spu_ram, 0x80000u);
  gzwrite(a2, (unsigned __int8 *)dword_4E7108, 0x8020u);
  return gzwrite(a2, (unsigned __int8 *)spu_voice_param, 0x1BC0u);
}
