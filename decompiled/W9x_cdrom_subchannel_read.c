#include "pch.h"
char sub_431C80()
{
  char result; // al
  char v1; // bp
  FILE *v2; // esi
  int v3; // esi
  int v4; // ebx
  int v5; // edi
  _QWORD *v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // esi
  _DWORD *v10; // eax
  FILE *v11; // eax
  FILE *v12; // esi
  int v13; // ebp
  unsigned __int8 i; // bl
  char *v15; // edi
  FILE *v16; // eax
  FILE *v17; // esi
  int v18; // ebx
  int v19; // eax
  int v20; // esi
  int v21; // ecx
  _DWORD *v22; // esi
  int v23; // ebp
  _DWORD *v24; // edx
  int v25; // eax
  bool v26; // cf
  FILE *v27; // esi
  int v28; // esi
  int v29; // eax
  _DWORD *v30; // ecx
  int v31; // edx
  _DWORD *v32; // esi
  int v33; // edi
  FILE *v34; // eax
  int v35; // ebp
  unsigned __int8 j; // bl
  char *v37; // edi
  FILE *v38; // esi
  char v39; // [esp-8h] [ebp-5220h]
  char v40; // [esp-8h] [ebp-5220h]
  char v41; // [esp-8h] [ebp-5220h]
  char v42; // [esp-8h] [ebp-5220h]
  char v43; // [esp-4h] [ebp-521Ch]
  char v44; // [esp-4h] [ebp-521Ch]
  char v45; // [esp-4h] [ebp-521Ch]
  char v46; // [esp-4h] [ebp-521Ch]
  char v47; // [esp+0h] [ebp-5218h]
  char v48; // [esp+0h] [ebp-5218h]
  char v49; // [esp+0h] [ebp-5218h]
  int v50; // [esp+10h] [ebp-5208h]
  unsigned __int8 v51; // [esp+10h] [ebp-5208h]
  unsigned __int8 v52; // [esp+10h] [ebp-5208h]
  unsigned __int8 v53; // [esp+10h] [ebp-5208h]
  unsigned __int8 v54; // [esp+10h] [ebp-5208h]
  int v55; // [esp+14h] [ebp-5204h]
  _QWORD v56[128]; // [esp+18h] [ebp-5200h] BYREF
  char Buffer[1024]; // [esp+418h] [ebp-4E00h] BYREF
  _DWORD v58[4736]; // [esp+818h] [ebp-4A00h] BYREF

  result = byte_456D70;
  dword_4FFF80 = -1;
  if ( byte_456D70 && dword_50C37C != 3 )
  {
    v1 = 1;
    if ( dword_504C8C != 7 && dword_504C8C != 1 )
    {
      result = dbg_print(aWarningCdromRe, v47);
      dword_504C8C = 1;
      return result;
    }
    result = use_subchannel;
    if ( use_subchannel )
    {
      sprintf(Buffer, "%s%s.SUB", aPatches, byte_8B3D80);
      Stream = fopen(Buffer, Mode);
      if ( Stream )
      {
        if ( dword_504C8C == 1 )
        {
          dword_504C8C = 5;
          result = dbg_print(aSubchannelSupp, v47);
          BYTE1(dword_455945) = 0;
        }
        else
        {
          if ( dword_504C8C == 7 )
            dword_504C8C = 9;
          result = dbg_print(aSubchannelSupp, v47);
          BYTE1(dword_455945) = 0;
        }
        return result;
      }
      sprintf(Buffer, "%s%s.M3S", aPatches, byte_8B3D80);
      v2 = fopen(Buffer, Mode);
      if ( v2 )
      {
        dword_504C84 = malloc(0x11940u);
        fread(dword_504C84, 1u, 0x11940u, v2);
        fclose(v2);
        if ( dword_504C8C == 1 )
        {
          dword_504C8C = 6;
          result = dbg_print(aSubchannelSupp_0, v47);
          BYTE1(dword_455945) = 0;
        }
        else
        {
          if ( dword_504C8C == 7 )
            dword_504C8C = 10;
          result = dbg_print(aSubchannelSupp_0, v47);
          BYTE1(dword_455945) = 0;
        }
        return result;
      }
      if ( SubchannelW9xCachingLG )
      {
        dbg_print(aCheckingSubcha, v47);
        dword_504C84 = malloc(0x11940u);
        v50 = 2;
        do
        {
          dbg_print(aCdromPrecachin, v1);
          v3 = 12600;
          v4 = 70;
          do
          {
            sub_431AB0(v3);
            v5 = 75;
            do
            {
              sub_431B00(v56);
              if ( BYTE1(v56[1]) % 10 + 16 * (BYTE1(v56[1]) / 10) == 3 && BYTE2(v56[1]) < 0x3Cu && BYTE3(v56[1]) < 0x4Bu )
              {
                v6 = (char *)dword_504C84 + 1200 * BYTE2(v56[1]) + 16 * BYTE3(v56[1]);
                *v6 = v56[0];
                v6[1] = v56[1];
              }
              --v5;
            }
            while ( v5 );
            v3 += 75;
            --v4;
          }
          while ( v4 );
          dbg_print(aOk_0, v48);
          ++v1;
          --v50;
        }
        while ( v50 );
        dbg_print(aFixatingSubcha, v48);
        v7 = 0;
        v8 = 60;
        do
        {
          v9 = 75;
          do
          {
            v10 = (char *)dword_504C84 + v7;
            v56[0] = *(_QWORD *)((char *)dword_504C84 + v7);
            v56[1] = *(_QWORD *)((char *)dword_504C84 + v7 + 8);
            *v10 = 0;
            v10[1] = 0;
            v10[2] = 0;
            v10[3] = 0;
            *((_BYTE *)dword_504C84 + v7) = 65;
            *(_WORD *)((char *)dword_504C84 + v7 + 1) = HIWORD(v56[0]);
            v7 += 16;
            *((char *)dword_504C84 + v7 - 13) = BYTE5(v56[1]) % 10 + 16 * (BYTE5(v56[1]) / 10);
            *((char *)dword_504C84 + v7 - 12) = BYTE6(v56[1]) % 10 + 16 * (BYTE6(v56[1]) / 10);
            *((char *)dword_504C84 + v7 - 11) = HIBYTE(v56[1]) % 10 + 16 * (HIBYTE(v56[1]) / 10);
            *((char *)dword_504C84 + v7 - 9) = BYTE1(v56[1]) % 10 + 16 * (BYTE1(v56[1]) / 10);
            *((char *)dword_504C84 + v7 - 8) = BYTE2(v56[1]) % 10 + 16 * (BYTE2(v56[1]) / 10);
            --v9;
            *((char *)dword_504C84 + v7 - 7) = BYTE3(v56[1]) % 10 + 16 * (BYTE3(v56[1]) / 10);
          }
          while ( v9 );
          --v8;
        }
        while ( v8 );
        dword_504C8C = 6;
        sprintf(Buffer, "%s%s.M3S", aPatches, byte_8B3D80);
        v11 = fopen(Buffer, aWb);
        v12 = v11;
        if ( v11 )
        {
          fwrite(dword_504C84, 1u, 0x11940u, v11);
          fclose(v12);
        }
        goto LABEL_36;
      }
      result = SubchannelW9xCdromEnabled;
      if ( !SubchannelW9xCdromEnabled )
        return result;
      dbg_print(aCheckingSubcha_0, v47);
      if ( dword_504C8C == 7 )
      {
        sub_431810(0, 2, 16, 2, v58, v56);
        result = HIBYTE(v56[0]);
        if ( HIBYTE(v56[0]) )
          return result;
        result = v56[1];
        if ( LOWORD(v56[1]) != 5634 )
          return result;
        result = HIBYTE(v56[2]);
        if ( *(_WORD *)((char *)&v56[2] + 7) != 512 || BYTE1(v56[3]) != 23 )
          return result;
        dword_504C8C = 8;
        dword_504C88 = 2352;
        if ( SubchannelW9xCaching )
        {
          dword_504C84 = malloc(0x11940u);
          dbg_print(aYes, v43);
          dbg_print(aCdromPrecachin_0, v39);
          v51 = 0;
          v13 = 0;
          do
          {
            for ( i = 0; i < 0x4Bu; i += 5 )
            {
              sub_431810(3, v51, i, 5, v58, v56);
              v15 = (char *)dword_504C84 + v13;
              v13 += 80;
              qmemcpy(v15, v56, 0x50u);
            }
            ++v51;
          }
          while ( v51 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", aPatches, byte_8B3D80);
          v16 = fopen(Buffer, aWb);
          v17 = v16;
          if ( v16 )
          {
            fwrite(dword_504C84, 1u, 0x11940u, v16);
            fclose(v17);
          }
          dword_504C8C = 10;
          goto LABEL_36;
        }
LABEL_101:
        result = dbg_print(aYes, v49);
        BYTE1(dword_455945) = 0;
        return result;
      }
      memset(v58, 0xAAu, 0x1F9Cu);
      sub_431990(0, 2, 16, 2, v58);
      if ( !LOBYTE(v58[3]) && *(_WORD *)((char *)&v58[3] + 1) == 5634 )
      {
        v18 = v58[590];
        if ( !(HIBYTE(v58[589]) % 10 + 16 * (HIBYTE(v58[589]) / 10))
          && LOBYTE(v58[590]) % 10 + 16 * (LOBYTE(v58[590]) / 10) == 2
          && BYTE1(v58[590]) % 10 + 16 * (BYTE1(v58[590]) / 10) == 22
          && !LOBYTE(v58[595])
          && *(_WORD *)((char *)&v58[595] + 1) == 5890
          && !(HIBYTE(v58[1181]) % 10 + 16 * (HIBYTE(v58[1181]) / 10))
          && LOBYTE(v58[1182]) % 10 + 16 * (LOBYTE(v58[1182]) / 10) == 2
          && BYTE1(v58[1182]) % 10 + 16 * (BYTE1(v58[1182]) / 10) == 23 )
        {
          dword_504C8C = 2;
          dword_504C88 = 2368;
          if ( !SubchannelW9xCaching )
            goto LABEL_101;
          dword_504C84 = malloc(0x11940u);
          dbg_print(aYes, v44);
          v19 = dbg_print(aCdromPrecachin_0, v40);
          v52 = 0;
          v20 = 0;
          do
          {
            LOBYTE(v19) = 0;
            LOBYTE(v55) = 0;
            do
            {
              sub_431990(3, v52, v19, 5, v58);
              v21 = v20;
              v22 = &v58[588];
              v23 = 5;
              do
              {
                v24 = (char *)dword_504C84 + v21;
                *v24 = *v22;
                v24[1] = v22[1];
                v24[2] = v22[2];
                v24[3] = v22[3];
                v25 = *((unsigned __int8 *)dword_504C84 + v21 + 3);
                v21 += 16;
                v22 += 592;
                *((char *)dword_504C84 + v21 - 13) = v25 % 10 + 16 * (v25 / 10);
                *((char *)dword_504C84 + v21 - 12) = (unsigned __int8)*((char *)dword_504C84 + v21 - 12) % 10
                                                   + 16 * ((unsigned __int8)*((char *)dword_504C84 + v21 - 12) / 10);
                *((char *)dword_504C84 + v21 - 11) = (unsigned __int8)*((char *)dword_504C84 + v21 - 11) % 10
                                                   + 16 * ((unsigned __int8)*((char *)dword_504C84 + v21 - 11) / 10);
                *((char *)dword_504C84 + v21 - 9) = (unsigned __int8)*((char *)dword_504C84 + v21 - 9) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v21 - 9) / 10);
                *((char *)dword_504C84 + v21 - 8) = (unsigned __int8)*((char *)dword_504C84 + v21 - 8) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v21 - 8) / 10);
                --v23;
                *((char *)dword_504C84 + v21 - 7) = (unsigned __int8)*((char *)dword_504C84 + v21 - 7) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v21 - 7) / 10);
              }
              while ( v23 );
              v19 = v55;
              LOBYTE(v19) = v55 + 5;
              v26 = (unsigned __int8)(v55 + 5) < 0x4Bu;
              LOBYTE(v55) = v55 + 5;
              v20 = v21;
            }
            while ( v26 );
            ++v52;
          }
          while ( v52 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", aPatches, byte_8B3D80);
          v27 = fopen(Buffer, aWb);
          if ( !v27 )
            goto LABEL_88;
          fwrite(dword_504C84, 1u, 0x11940u, v27);
          goto LABEL_87;
        }
        if ( !HIBYTE(v58[589])
          && LOWORD(v58[590]) == 5634
          && !LOBYTE(v58[595])
          && BYTE1(v58[595]) == LOBYTE(v58[590])
          && BYTE2(v58[595]) == 23
          && !HIBYTE(v58[1181])
          && LOBYTE(v58[1182]) == LOBYTE(v58[590])
          && BYTE1(v58[1182]) == 23 )
        {
          dword_504C8C = 3;
          dword_504C88 = 2368;
          if ( !SubchannelW9xCaching )
            goto LABEL_101;
          dword_504C84 = malloc(0x11940u);
          dbg_print(aYes, v45);
          dbg_print(aCdromPrecachin_0, v41);
          v53 = 0;
          v28 = 0;
          do
          {
            LOBYTE(v18) = 0;
            do
            {
              sub_431990(3, v53, v18, 5, v58);
              v29 = v28;
              v30 = &v58[588];
              v31 = 5;
              do
              {
                v32 = (char *)dword_504C84 + v29;
                *v32 = *v30;
                v32[1] = v30[1];
                v32[2] = v30[2];
                v33 = v30[3];
                v29 += 16;
                v30 += 592;
                --v31;
                v32[3] = v33;
              }
              while ( v31 );
              LOBYTE(v18) = v18 + 5;
              v28 = v29;
            }
            while ( (unsigned __int8)v18 < 0x4Bu );
            ++v53;
          }
          while ( v53 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", aPatches, byte_8B3D80);
          v34 = fopen(Buffer, aWb);
          v27 = v34;
          if ( !v34 )
            goto LABEL_88;
          fwrite(dword_504C84, 1u, 0x11940u, v34);
LABEL_87:
          fclose(v27);
LABEL_88:
          dword_504C88 = 2352;
          goto LABEL_100;
        }
      }
      memset(v58, 0xAAu, 0x1F9Cu);
      sub_431A20(0, 2, 16, 2, v58);
      if ( *(_WORD *)((char *)&v58[1] + 3) != 512
        || BYTE1(v58[2]) != 22
        || *(_WORD *)((char *)&v58[5] + 3) != 512
        || BYTE1(v58[6]) != 23 )
      {
        return dbg_print(aNo, v49);
      }
      dword_504C8C = 4;
      dword_504C88 = 2352;
      dword_504C84 = malloc(0x11940u);
      if ( !SubchannelW9xCaching )
        goto LABEL_101;
      dword_504C84 = malloc(0x11940u);
      dbg_print(aYes, v46);
      dbg_print(aCdromPrecachin_0, v42);
      v54 = 0;
      v35 = 0;
      do
      {
        for ( j = 0; j < 0x4Bu; j += 15 )
        {
          sub_431A20(3, v54, j, 15, v58);
          v37 = (char *)dword_504C84 + v35;
          v35 += 240;
          qmemcpy(v37, v58, 0xF0u);
        }
        ++v54;
      }
      while ( v54 < 0x3Cu );
      sprintf(Buffer, "%s%s.M3S", aPatches, byte_8B3D80);
      v38 = fopen(Buffer, aWb);
      if ( v38 )
      {
        fwrite(dword_504C84, 1u, 0x11940u, v38);
        fclose(v38);
      }
LABEL_100:
      dword_504C8C = 6;
LABEL_36:
      result = dbg_print(aOk_0, v49);
      BYTE1(dword_455945) = 0;
    }
  }
  return result;
}
