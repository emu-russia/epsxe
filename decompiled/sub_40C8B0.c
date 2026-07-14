#include "pch.h"
unsigned int sub_40C8B0()
{
  int v0; // ebp
  __int16 v1; // di
  int v2; // esi
  double v3; // st7
  char *v4; // ebx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  __int16 *i; // esi
  unsigned int result; // eax
  unsigned int v11; // ecx
  unsigned int v12; // edx
  int v13; // edi
  int v14; // edi
  int v15; // eax
  int v16; // eax
  bool v17; // zf
  int v18; // eax
  int v19; // ebp
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  char *v23; // edi
  unsigned int v24; // eax
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  int v29; // eax
  int v30; // [esp+10h] [ebp-8h]
  float v31; // [esp+14h] [ebp-4h]
  int v32; // [esp+14h] [ebp-4h]

  v0 = dword_4E7114;
  v1 = HIWORD(dword_4F75B0);
  v2 = SHIWORD(dword_4F75B0);
  v31 = (double)dword_44F7A0 * 0.00002267573696145125;
  if ( dword_4E7114 | SHIWORD(dword_4F75B0) )
  {
    v3 = flt_4F75AC;
    v4 = byte_4F7154;
    if ( dword_4E7110 )
    {
      do
      {
        LOWORD(dword_4F75B0) = (__int64)v3;
        if ( (unsigned __int16)dword_4F75B0 >= v2 && v1 > 0 )
        {
          if ( !v0 )
            dword_44F7A0 -= 250;
          if ( 2 * v0 > 0 )
            qmemcpy(word_4EF140, byte_4E7128, 4 * ((unsigned int)(2 * v0) >> 1));
          v3 = 0.0;
          v1 = v0;
          v0 = 0;
          dword_4E7114 = 0;
          LOWORD(dword_4F75B0) = 0;
        }
        v2 = v1;
        if ( (unsigned __int16)dword_4F75B0 >= v1 )
        {
          *((_DWORD *)v4 - 1) = 0;
          *(_DWORD *)v4 = 0;
        }
        else
        {
          v3 = v3 + v31;
          v5 = 2 * (dword_4F75B0 & 0x3FFE);
          v6 = word_4EF140[v5];
          v7 = byte_4EF142[v5];
          *((_DWORD *)v4 - 1) = v6;
          *(_DWORD *)v4 = v7;
        }
        v4 += 8;
      }
      while ( (int)v4 < (int)dword_4F7354 );
      flt_4F75AC = v3;
      HIWORD(dword_4F75B0) = v1;
    }
    else
    {
      do
      {
        LOWORD(dword_4F75B0) = (__int64)v3;
        if ( (unsigned __int16)dword_4F75B0 >= 2 * v2 && v1 > 0 )
        {
          if ( !v0 )
            dword_44F7A0 -= 250;
          if ( 2 * v0 > 0 )
            qmemcpy(word_4EF140, byte_4E7128, 4 * ((unsigned int)(2 * v0) >> 1));
          v3 = 0.0;
          v1 = v0;
          v0 = 0;
          dword_4E7114 = 0;
          LOWORD(dword_4F75B0) = 0;
        }
        v2 = v1;
        if ( (unsigned __int16)dword_4F75B0 >= 2 * v1 )
        {
          *((_DWORD *)v4 - 1) = 0;
          *(_DWORD *)v4 = 0;
        }
        else
        {
          v3 = v3 + v31;
          v8 = word_4EF140[dword_4F75B0 & 0x3FFF];
          *((_DWORD *)v4 - 1) = v8;
          *(_DWORD *)v4 = v8;
        }
        v4 += 8;
      }
      while ( (int)v4 < (int)dword_4F7354 );
      flt_4F75AC = v3;
      HIWORD(dword_4F75B0) = v1;
    }
  }
  else
  {
    memset(&byte_4F7150, 0, 0x200u);
  }
  v30 = 0;
  v32 = 0;
  for ( i = (_WORD *)(dword_46559C + 2); (int)i < 4616542; i += 148 )
  {
    result = *(_DWORD *)(i + 3);
    if ( result && (((unsigned int)spucore_pitchmod_enable >> (v30 + 1)) & 1) == 0 )
    {
      v11 = ((unsigned int)(unsigned __int16)spucore_mainvol_left * *(_DWORD *)(i - 47)) >> 20;
      v12 = ((unsigned int)(unsigned __int16)spucore_mainvol_right * *(_DWORD *)(i - 45)) >> 20;
      switch ( result )
      {
        case 1u:
          v13 = (*(_DWORD *)(i + 91) << 6) + *(_DWORD *)(i - 1);
          *(_DWORD *)(i - 1) = v13;
          if ( v13 >= 0xFFFFFF )
          {
            *(_DWORD *)(i - 1) = 0xFFFFFF;
            *(_DWORD *)(i + 3) = 2;
          }
          break;
        case 2u:
          v14 = (*(_DWORD *)(i + 93) << 6) + *(_DWORD *)(i - 1);
          v15 = *(_DWORD *)(i + 95);
          *(_DWORD *)(i - 1) = v14;
          if ( v14 <= v15 )
          {
            *(_DWORD *)(i - 1) = v15;
            *(_DWORD *)(i + 3) = 3;
          }
          break;
        case 3u:
          v16 = *(_DWORD *)(i - 1) + (*(_DWORD *)(i + 97) << 6);
          v17 = *(_DWORD *)(i - 9) == 1;
          *(_DWORD *)(i - 1) = v16;
          if ( v17 )
          {
            if ( v16 <= 0 )
            {
              *(_DWORD *)(i - 1) = 0;
              *(_DWORD *)(i + 3) = 0;
            }
          }
          else if ( v16 >= 0xFFFFFF )
          {
            *(_DWORD *)(i + 3) = 5;
            goto LABEL_41;
          }
          break;
        case 4u:
          v20 = (*(_DWORD *)(i + 99) << 6) + *(_DWORD *)(i - 1);
          *(_DWORD *)(i - 1) = v20;
          if ( v20 <= 0 )
          {
            *(_DWORD *)(i - 1) = 0;
            *(_DWORD *)(i + 3) = 0;
          }
          break;
        case 5u:
LABEL_41:
          *(_DWORD *)(i - 1) = 0xFFFFFF;
          break;
        default:
          break;
      }
      v18 = *i;
      if ( *(_DWORD *)(i - 39) )
        v19 = 0xFFFF - v11 * v18;
      else
        v19 = v11 * v18;
      v21 = v12 * v18;
      if ( *(_DWORD *)(i - 37) )
        v22 = 0xFFFF - v21;
      else
        v22 = v21;
      v23 = byte_4F7154;
      do
      {
        if ( !*(_DWORD *)(i + 77) )
        {
          do
          {
            v24 = *(_DWORD *)(i + 7);
            if ( v24 > 0x1BFFFF )
            {
              do
                v24 -= 1835008;
              while ( v24 > 0x1BFFFF );
              *(_DWORD *)(i + 77) = 0;
              *(_DWORD *)(i + 7) = v24;
            }
            sub_40C620(v30);
            v25 = *(_DWORD *)(i + 77);
            if ( v25 == 2 )
              *(_DWORD *)(i + 3) = 0;
          }
          while ( !v25 );
        }
        v26 = dword_4655C8[(unsigned __int16)i[8] + v32];
        v27 = ((v19 * v26) >> 16) + *((_DWORD *)v23 - 1);
        v28 = ((v22 * v26) >> 16) + *(_DWORD *)v23;
        v29 = *(_DWORD *)(i + 7);
        *((_DWORD *)v23 - 1) = v27;
        result = *(_DWORD *)(i + 11) + v29;
        *(_DWORD *)v23 = v28;
        *(_DWORD *)(i + 7) = result;
        if ( result > 0x1BFFFF )
        {
          result -= 0x1C0000;
          *(_DWORD *)(i + 77) = 0;
          *(_DWORD *)(i + 7) = result;
        }
        v23 += 8;
      }
      while ( (int)v23 < (int)dword_4F7354 );
    }
    if ( !*(_DWORD *)(i + 3) )
      *(_DWORD *)(i - 1) = 0;
    ++v30;
    v32 += 74;
  }
  return result;
}
