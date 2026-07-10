#include "pch.h"
unsigned int sub_40C8B0()
{
  int v0; // ebp
  __int16 v1; // di
  int v2; // esi
  double v3; // st7
  int *v4; // ebx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  __int16 *v9; // esi
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
  int *v23; // edi
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
    v4 = (int *)&byte_4F7154;
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
            qmemcpy(word_4EF140, &byte_4E7128, 4 * ((unsigned int)(2 * v0) >> 1));
          v3 = 0.0;
          v1 = v0;
          v0 = 0;
          dword_4E7114 = 0;
          LOWORD(dword_4F75B0) = 0;
        }
        v2 = v1;
        if ( (unsigned __int16)dword_4F75B0 >= v1 )
        {
          *(v4 - 1) = 0;
          *v4 = 0;
        }
        else
        {
          v3 = v3 + v31;
          v5 = 2 * (dword_4F75B0 & 0x3FFE);
          v6 = word_4EF140[v5];
          v7 = byte_4EF142[v5];
          *(v4 - 1) = v6;
          *v4 = v7;
        }
        v4 += 2;
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
            qmemcpy(word_4EF140, &byte_4E7128, 4 * ((unsigned int)(2 * v0) >> 1));
          v3 = 0.0;
          v1 = v0;
          v0 = 0;
          dword_4E7114 = 0;
          LOWORD(dword_4F75B0) = 0;
        }
        v2 = v1;
        if ( (unsigned __int16)dword_4F75B0 >= 2 * v1 )
        {
          *(v4 - 1) = 0;
          *v4 = 0;
        }
        else
        {
          v3 = v3 + v31;
          v8 = word_4EF140[dword_4F75B0 & 0x3FFF];
          *(v4 - 1) = v8;
          *v4 = v8;
        }
        v4 += 2;
      }
      while ( (int)v4 < (int)dword_4F7354 );
      flt_4F75AC = v3;
      HIWORD(dword_4F75B0) = v1;
    }
  }
  else
  {
    memset(&unk_4F7150, 0, 0x200u);
  }
  v30 = 0;
  v32 = 0;
  v9 = (_WORD *)(dword_46559C + 2);
  do
  {
    result = *(_DWORD *)(v9 + 3);
    if ( result && (((unsigned int)dword_4F7558 >> (v30 + 1)) & 1) == 0 )
    {
      v11 = ((unsigned int)(unsigned __int16)word_4F7586 * *(_DWORD *)(v9 - 47)) >> 20;
      v12 = ((unsigned int)(unsigned __int16)dword_4F7588 * *(_DWORD *)(v9 - 45)) >> 20;
      switch ( result )
      {
        case 1u:
          v13 = (*(_DWORD *)(v9 + 91) << 6) + *(_DWORD *)(v9 - 1);
          *(_DWORD *)(v9 - 1) = v13;
          if ( v13 >= 0xFFFFFF )
          {
            *(_DWORD *)(v9 - 1) = 0xFFFFFF;
            *(_DWORD *)(v9 + 3) = 2;
          }
          break;
        case 2u:
          v14 = (*(_DWORD *)(v9 + 93) << 6) + *(_DWORD *)(v9 - 1);
          v15 = *(_DWORD *)(v9 + 95);
          *(_DWORD *)(v9 - 1) = v14;
          if ( v14 <= v15 )
          {
            *(_DWORD *)(v9 - 1) = v15;
            *(_DWORD *)(v9 + 3) = 3;
          }
          break;
        case 3u:
          v16 = *(_DWORD *)(v9 - 1) + (*(_DWORD *)(v9 + 97) << 6);
          v17 = *(_DWORD *)(v9 - 9) == 1;
          *(_DWORD *)(v9 - 1) = v16;
          if ( v17 )
          {
            if ( v16 <= 0 )
            {
              *(_DWORD *)(v9 - 1) = 0;
              *(_DWORD *)(v9 + 3) = 0;
            }
          }
          else if ( v16 >= 0xFFFFFF )
          {
            *(_DWORD *)(v9 + 3) = 5;
            goto LABEL_41;
          }
          break;
        case 4u:
          v20 = (*(_DWORD *)(v9 + 99) << 6) + *(_DWORD *)(v9 - 1);
          *(_DWORD *)(v9 - 1) = v20;
          if ( v20 <= 0 )
          {
            *(_DWORD *)(v9 - 1) = 0;
            *(_DWORD *)(v9 + 3) = 0;
          }
          break;
        case 5u:
LABEL_41:
          *(_DWORD *)(v9 - 1) = 0xFFFFFF;
          break;
        default:
          break;
      }
      v18 = *v9;
      if ( *(_DWORD *)(v9 - 39) )
        v19 = 0xFFFF - v11 * v18;
      else
        v19 = v11 * v18;
      v21 = v12 * v18;
      if ( *(_DWORD *)(v9 - 37) )
        v22 = 0xFFFF - v21;
      else
        v22 = v21;
      v23 = (int *)&byte_4F7154;
      do
      {
        if ( !*(_DWORD *)(v9 + 77) )
        {
          do
          {
            v24 = *(_DWORD *)(v9 + 7);
            if ( v24 > 0x1BFFFF )
            {
              do
                v24 -= 1835008;
              while ( v24 > 0x1BFFFF );
              *(_DWORD *)(v9 + 77) = 0;
              *(_DWORD *)(v9 + 7) = v24;
            }
            sub_40C620(v30);
            v25 = *(_DWORD *)(v9 + 77);
            if ( v25 == 2 )
              *(_DWORD *)(v9 + 3) = 0;
          }
          while ( !v25 );
        }
        v26 = dword_4655C8[(unsigned __int16)v9[8] + v32];
        v27 = ((v19 * v26) >> 16) + *(v23 - 1);
        v28 = ((v22 * v26) >> 16) + *v23;
        v29 = *(_DWORD *)(v9 + 7);
        *(v23 - 1) = v27;
        result = *(_DWORD *)(v9 + 11) + v29;
        *v23 = v28;
        *(_DWORD *)(v9 + 7) = result;
        if ( result > 0x1BFFFF )
        {
          result -= 1835008;
          *(_DWORD *)(v9 + 77) = 0;
          *(_DWORD *)(v9 + 7) = result;
        }
        v23 += 2;
      }
      while ( (int)v23 < (int)dword_4F7354 );
    }
    if ( !*(_DWORD *)(v9 + 3) )
      *(_DWORD *)(v9 - 1) = 0;
    v9 += 148;
    ++v30;
    v32 += 74;
  }
  while ( (int)v9 < (int)MEMORY[0x46715E] );
  return result;
}
