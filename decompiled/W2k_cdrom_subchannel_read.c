#include "pch.h"
char W2k_cdrom_subchannel_read()
{
  char result; // al
  int v1; // ebp
  FILE *v2; // esi
  int v3; // esi
  int v4; // ebx
  int v5; // edi
  _DWORD *v6; // eax
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
  int v18; // esi
  unsigned __int8 v19; // al
  int v20; // ecx
  _DWORD *v21; // esi
  int v22; // ebp
  _DWORD *v23; // edx
  int v24; // eax
  bool v25; // cf
  FILE *v26; // esi
  int v27; // esi
  unsigned __int8 j; // bl
  int v29; // eax
  _DWORD *v30; // ecx
  int v31; // edx
  _DWORD *v32; // esi
  int v33; // edi
  FILE *v34; // eax
  int v35; // ebp
  unsigned __int8 k; // bl
  char *v37; // edi
  FILE *v38; // esi
  int v39; // [esp+10h] [ebp-5208h]
  unsigned __int8 v40; // [esp+10h] [ebp-5208h]
  unsigned __int8 v41; // [esp+10h] [ebp-5208h]
  unsigned __int8 v42; // [esp+10h] [ebp-5208h]
  unsigned __int8 v43; // [esp+10h] [ebp-5208h]
  char v44; // [esp+14h] [ebp-5204h]
  _DWORD v45[256]; // [esp+18h] [ebp-5200h] BYREF
  char Buffer[1024]; // [esp+418h] [ebp-4E00h] BYREF
  _WORD v47[9472]; // [esp+818h] [ebp-4A00h] BYREF

  result = cd_savefake_flag;
  dword_4FFF80 = -1;
  if ( cd_savefake_flag && loaded_file_type != 3 )
  {
    v1 = 1;
    if ( dword_504C8C != 7 && dword_504C8C != 1 )
    {
      result = dbg_print(" * Warning: cdrom read mode unknown. \n");
      dword_504C8C = 1;
      return result;
    }
    result = use_subchannel;
    if ( use_subchannel )
    {
      sprintf(Buffer, "%s%s.SUB", "patches\\", byte_8B3D80);
      Stream = fopen(Buffer, "rb");
      if ( Stream )
      {
        if ( dword_504C8C == 1 )
        {
          dword_504C8C = 5;
          result = dbg_print(" * Subchannel support from clonecd .sub file. \n");
          BYTE1(dword_455945) = 0;
        }
        else
        {
          if ( dword_504C8C == 7 )
            dword_504C8C = 9;
          result = dbg_print(" * Subchannel support from clonecd .sub file. \n");
          BYTE1(dword_455945) = 0;
        }
        return result;
      }
      sprintf(Buffer, "%s%s.M3S", "patches\\", byte_8B3D80);
      v2 = fopen(Buffer, "rb");
      if ( v2 )
      {
        dword_504C84 = malloc(0x11940u);
        fread(dword_504C84, 1u, 0x11940u, v2);
        fclose(v2);
        if ( dword_504C8C == 1 )
        {
          dword_504C8C = 6;
          result = dbg_print(" * Subchannel support from .m3s file. \n");
          BYTE1(dword_455945) = 0;
        }
        else
        {
          if ( dword_504C8C == 7 )
            dword_504C8C = 10;
          result = dbg_print(" * Subchannel support from .m3s file. \n");
          BYTE1(dword_455945) = 0;
        }
        return result;
      }
      if ( SubchannelW2kCaching )
      {
        dbg_print(" * Checking subchannel read standard ... \n");
        dword_504C84 = malloc(0x11940u);
        v39 = 2;
        do
        {
          dbg_print(" * Cdrom precaching subchannel ... (step %d/2) ", v1);
          v3 = 12600;
          v4 = 70;
          do
          {
            sub_435090(v3);
            v5 = 75;
            do
            {
              sub_4350E0(v45);
              if ( BYTE1(v45[2]) % 10 + 16 * (BYTE1(v45[2]) / 10) == 3
                && BYTE2(v45[2]) < 0x3Cu
                && HIBYTE(v45[2]) < 0x4Bu )
              {
                v6 = (char *)dword_504C84 + 1200 * BYTE2(v45[2]) + 16 * HIBYTE(v45[2]);
                *v6 = v45[0];
                v6[1] = v45[1];
                v6[2] = v45[2];
                v6[3] = v45[3];
              }
              --v5;
            }
            while ( v5 );
            v3 += 75;
            --v4;
          }
          while ( v4 );
          dbg_print("ok\n");
          ++v1;
          --v39;
        }
        while ( v39 );
        dbg_print(" * Fixating subchanel ... ");
        v7 = 0;
        v8 = 60;
        do
        {
          v9 = 75;
          do
          {
            v10 = (char *)dword_504C84 + v7;
            v45[0] = *(_DWORD *)((char *)dword_504C84 + v7);
            v45[1] = *(_DWORD *)((char *)dword_504C84 + v7 + 4);
            v45[2] = *(_DWORD *)((char *)dword_504C84 + v7 + 8);
            v45[3] = *(_DWORD *)((char *)dword_504C84 + v7 + 12);
            *v10 = 0;
            v10[1] = 0;
            v10[2] = 0;
            v10[3] = 0;
            *((_BYTE *)dword_504C84 + v7) = 65;
            *(_WORD *)((char *)dword_504C84 + v7 + 1) = HIWORD(v45[1]);
            v7 += 16;
            *((char *)dword_504C84 + v7 - 13) = BYTE1(v45[3]) % 10 + 16 * (BYTE1(v45[3]) / 10);
            *((char *)dword_504C84 + v7 - 12) = BYTE2(v45[3]) % 10 + 16 * (BYTE2(v45[3]) / 10);
            *((char *)dword_504C84 + v7 - 11) = HIBYTE(v45[3]) % 10 + 16 * (HIBYTE(v45[3]) / 10);
            *((char *)dword_504C84 + v7 - 9) = BYTE1(v45[2]) % 10 + 16 * (BYTE1(v45[2]) / 10);
            *((char *)dword_504C84 + v7 - 8) = BYTE2(v45[2]) % 10 + 16 * (BYTE2(v45[2]) / 10);
            --v9;
            *((char *)dword_504C84 + v7 - 7) = HIBYTE(v45[2]) % 10 + 16 * (HIBYTE(v45[2]) / 10);
          }
          while ( v9 );
          --v8;
        }
        while ( v8 );
        dword_504C8C = 6;
        sprintf(Buffer, "%s%s.M3S", "patches\\", byte_8B3D80);
        v11 = fopen(Buffer, "wb");
        v12 = v11;
        if ( v11 )
        {
          fwrite(dword_504C84, 1u, 0x11940u, v11);
          fclose(v12);
        }
        goto LABEL_36;
      }
      result = SubchannelW2kCdromEnabled;
      if ( !SubchannelW2kCdromEnabled )
        return result;
      dbg_print(" * Checking subchannel read from cdrom ... ");
      if ( dword_504C8C == 7 )
      {
        sub_434DF0(0, 2u, 0x10u, 2u, (DWORD)v47, v45);
        result = HIBYTE(v45[1]);
        if ( HIBYTE(v45[1]) )
          return result;
        result = v45[2];
        if ( LOWORD(v45[2]) != 5634 )
          return result;
        result = HIBYTE(v45[5]);
        if ( *(_WORD *)((char *)&v45[5] + 3) != 512 || BYTE1(v45[6]) != 23 )
          return result;
        dword_504C8C = 8;
        dword_504C88 = 2352;
        if ( SubchannelW2kCaching )
        {
          dword_504C84 = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          v40 = 0;
          v13 = 0;
          do
          {
            for ( i = 0; i < 0x4Bu; i += 5 )
            {
              sub_434DF0(3u, v40, i, 5u, (DWORD)v47, v45);
              v15 = (char *)dword_504C84 + v13;
              v13 += 80;
              qmemcpy(v15, v45, 0x50u);
            }
            ++v40;
          }
          while ( v40 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", byte_8B3D80);
          v16 = fopen(Buffer, "wb");
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
        result = dbg_print(" YES.\n");
        BYTE1(dword_455945) = 0;
        return result;
      }
      memset(v47, 0xAAu, 0x1F9Cu);
      sub_434F70(0, 2u, 0x10u, 2u, (DWORD)v47);
      if ( !LOBYTE(v47[6]) && *(_WORD *)((char *)&v47[6] + 1) == 5634 )
      {
        if ( !(HIBYTE(v47[1179]) % 10 + 16 * (HIBYTE(v47[1179]) / 10))
          && LOBYTE(v47[1180]) % 10 + 16 * (LOBYTE(v47[1180]) / 10) == 2
          && HIBYTE(v47[1180]) % 10 + 16 * (HIBYTE(v47[1180]) / 10) == 22
          && !LOBYTE(v47[1190])
          && *(_WORD *)((char *)&v47[1190] + 1) == 5890
          && !(HIBYTE(v47[2363]) % 10 + 16 * (HIBYTE(v47[2363]) / 10))
          && LOBYTE(v47[2364]) % 10 + 16 * (LOBYTE(v47[2364]) / 10) == 2
          && HIBYTE(v47[2364]) % 10 + 16 * (HIBYTE(v47[2364]) / 10) == 23 )
        {
          dword_504C8C = 2;
          dword_504C88 = 2368;
          if ( !SubchannelW2kCaching )
            goto LABEL_101;
          dword_504C84 = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          v41 = 0;
          v18 = 0;
          do
          {
            v19 = 0;
            v44 = 0;
            do
            {
              sub_434F70(3u, v41, v19, 5u, (DWORD)v47);
              v20 = v18;
              v21 = &v47[1176];
              v22 = 5;
              do
              {
                v23 = (char *)dword_504C84 + v20;
                *v23 = *v21;
                v23[1] = v21[1];
                v23[2] = v21[2];
                v23[3] = v21[3];
                v24 = *((unsigned __int8 *)dword_504C84 + v20 + 3);
                v20 += 16;
                v21 += 592;
                *((char *)dword_504C84 + v20 - 13) = v24 % 10 + 16 * (v24 / 10);
                *((char *)dword_504C84 + v20 - 12) = (unsigned __int8)*((char *)dword_504C84 + v20 - 12) % 10
                                                   + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 12) / 10);
                *((char *)dword_504C84 + v20 - 11) = (unsigned __int8)*((char *)dword_504C84 + v20 - 11) % 10
                                                   + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 11) / 10);
                *((char *)dword_504C84 + v20 - 9) = (unsigned __int8)*((char *)dword_504C84 + v20 - 9) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 9) / 10);
                *((char *)dword_504C84 + v20 - 8) = (unsigned __int8)*((char *)dword_504C84 + v20 - 8) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 8) / 10);
                --v22;
                *((char *)dword_504C84 + v20 - 7) = (unsigned __int8)*((char *)dword_504C84 + v20 - 7) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 7) / 10);
              }
              while ( v22 );
              v19 = v44 + 5;
              v25 = (unsigned __int8)(v44 + 5) < 0x4Bu;
              v44 += 5;
              v18 = v20;
            }
            while ( v25 );
            ++v41;
          }
          while ( v41 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", byte_8B3D80);
          v26 = fopen(Buffer, "wb");
          if ( !v26 )
            goto LABEL_88;
          fwrite(dword_504C84, 1u, 0x11940u, v26);
          goto LABEL_87;
        }
        if ( !HIBYTE(v47[1179])
          && v47[1180] == 5634
          && !LOBYTE(v47[1190])
          && HIBYTE(v47[1190]) == LOBYTE(v47[1180])
          && LOBYTE(v47[1191]) == 23
          && !HIBYTE(v47[2363])
          && LOBYTE(v47[2364]) == LOBYTE(v47[1180])
          && HIBYTE(v47[2364]) == 23 )
        {
          dword_504C8C = 3;
          dword_504C88 = 2368;
          if ( !SubchannelW2kCaching )
            goto LABEL_101;
          dword_504C84 = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          v42 = 0;
          v27 = 0;
          do
          {
            for ( j = 0; j < 0x4Bu; j += 5 )
            {
              sub_434F70(3u, v42, j, 5u, (DWORD)v47);
              v29 = v27;
              v30 = &v47[1176];
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
              v27 = v29;
            }
            ++v42;
          }
          while ( v42 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", byte_8B3D80);
          v34 = fopen(Buffer, "wb");
          v26 = v34;
          if ( !v34 )
            goto LABEL_88;
          fwrite(dword_504C84, 1u, 0x11940u, v34);
LABEL_87:
          fclose(v26);
LABEL_88:
          dword_504C88 = 2352;
          goto LABEL_100;
        }
      }
      memset(v47, 0xAAu, 0x1F9Cu);
      sub_435000(0, 2u, 0x10u, 2u, (DWORD)v47);
      if ( *(_WORD *)((char *)&v47[3] + 1) != 512
        || HIBYTE(v47[4]) != 22
        || *(_WORD *)((char *)&v47[11] + 1) != 512
        || HIBYTE(v47[12]) != 23 )
      {
        return dbg_print(" NO.\n");
      }
      dword_504C8C = 4;
      dword_504C88 = 2352;
      dword_504C84 = malloc(0x11940u);
      if ( !SubchannelW2kCaching )
        goto LABEL_101;
      dword_504C84 = malloc(0x11940u);
      dbg_print(" YES.\n");
      dbg_print(" * Cdrom precaching subchannel ... ");
      v43 = 0;
      v35 = 0;
      do
      {
        for ( k = 0; k < 0x4Bu; k += 15 )
        {
          sub_435000(3u, v43, k, 0xFu, (DWORD)v47);
          v37 = (char *)dword_504C84 + v35;
          v35 += 240;
          qmemcpy(v37, v47, 0xF0u);
        }
        ++v43;
      }
      while ( v43 < 0x3Cu );
      sprintf(Buffer, "%s%s.M3S", "patches\\", byte_8B3D80);
      v38 = fopen(Buffer, "wb");
      if ( v38 )
      {
        fwrite(dword_504C84, 1u, 0x11940u, v38);
        fclose(v38);
      }
LABEL_100:
      dword_504C8C = 6;
LABEL_36:
      result = dbg_print("ok\n");
      BYTE1(dword_455945) = 0;
    }
  }
  return result;
}
