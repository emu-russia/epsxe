#include "pch.h"
int __cdecl spucore_unfreeze(int a1, _DWORD *a2)
{
  char *v2; // edi
  int *v3; // esi
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
  v3 = dword_465550;
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
            *v3 = v6;
            v3[2] = v6;
            *(v3 - 4) = v7;
            v3[4] = (v5 >> 13) & 1;
            v3[6] = v5 >> 15;
            *(v3 - 2) = v5 & 0x7F;
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
            *(v3 - 3) = v8 & 0x3FFF;
            v9 = (v8 >> 14) & 1;
            v3[1] = v9;
            v3[3] = v9;
            v3[5] = (v8 >> 13) & 1;
            v3[7] = v8 >> 15;
            *(v3 - 1) = v8 & 0x7F;
            break;
          case 4u:
            v10 = (double)(*((_WORD *)v2 + 2) & 0x3FFF);
            v3[8] = *((_WORD *)v2 + 2) & 0x3FFF;
            v11 = v10 * 0.000244140625;
            *((float *)v3 + 24) = v11;
            v3[25] = (__int64)(v11 * 65536.0);
            break;
          case 6u:
            v3[9] = *((unsigned __int16 *)v2 + 3);
            break;
          case 8u:
            v12 = *((_WORD *)v2 + 4);
            v13 = v2[9];
            v3[10] = v12 >> 15;
            v14 = v13 & 0x7F;
            v15 = (unsigned __int8)v12 >> 4;
            v3[11] = v14;
            v16 = dword_44F208[v14];
            v3[12] = v15;
            v17 = dword_44F408[v15];
            v18 = v12 & 0xF;
            v3[65] = v16;
            v19 = dword_44F648[v18];
            v3[13] = v18;
            v3[66] = -v17;
            v3[67] = v19;
            break;
          case 0xAu:
            v20 = *((_WORD *)v2 + 5);
            v3[14] = v20 >> 15;
            v21 = (v20 >> 14) & 1;
            v22 = (v20 >> 6) & 0x7F;
            v23 = (v20 >> 5) & 1;
            v24 = v20 & 0x1F;
            v3[15] = v21;
            v3[16] = v22;
            v3[17] = v23;
            v3[18] = v24;
            if ( v21 )
            {
              v26 = -dword_44F448[v22];
              v25 = -dword_44F688[v24];
              v3[68] = v26;
            }
            else
            {
              v3[68] = dword_44F448[v22];
              v25 = -dword_44F688[v24];
            }
            v3[69] = v25;
            break;
          case 0xCu:
            v37 = *((unsigned __int16 *)v2 + 6) << 9;
            v3[19] = v37;
            *((float *)v3 + 26) = (double)v37 * 0.000030517578125;
            break;
          case 0xEu:
            v3[20] = *((unsigned __int16 *)v2 + 7);
            break;
        }
      }
      v4 += 2;
      --v36;
    }
    while ( v36 );
    v2 += 16;
    v3 += 74;
    --v34;
  }
  while ( v34 );
  v27 = dword_4F7558;
  v28 = dword_463900;
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
        word_4F7586 = *v31;
        break;
      case 2:
        LOWORD(dword_4F7588) = *v31;
        break;
      case 4:
        word_4EF130 = *v31;
        break;
      case 6:
        word_4EF132 = *v31;
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
        sub_40CD50(*v31);
        break;
      case 44:
        sub_40CD60(*v31);
        break;
      case 46:
        sub_40CD70(*v31);
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
  dword_463900 = v28;
  dword_4F7558 = v27;
  gzread(a2, (char *)spu_ram, 0x80000);
  gzread(a2, dword_4E7108, 32800);
  dword_44F7A0 = *(_DWORD *)dword_4E7108;
  if ( dword_4E7114 > 4096 )
    dword_4E7114 = 0;
  result = strncmp(Str1, "ISPU", 4u);
  if ( !result )
    return gzread(a2, (char *)dword_465540, 7104);
  return result;
}
