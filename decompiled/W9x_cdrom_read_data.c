#include "pch.h"
int __cdecl W9x_cdrom_read_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, char *Buffer)
{
  unsigned __int8 v4; // dl
  unsigned __int8 v6; // bl
  int v7; // edi
  int v9; // eax
  char *v10; // ebp
  unsigned int v11; // eax
  int *v12; // eax
  int *v13; // edx
  int v14; // ecx
  int v15; // esi
  __int64 v16; // rax
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  int *v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int *v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int *v29; // ecx
  int *v30; // ecx
  char *v31; // eax
  int *v32; // eax
  int *v33; // ecx
  char *v34; // eax
  int v35; // eax
  int v36; // [esp+18h] [ebp-4h]
  int v37; // [esp+18h] [ebp-4h]
  unsigned int v38; // [esp+28h] [ebp+Ch]

  v4 = a1;
  v6 = a2;
  v7 = a3;
  v38 = 75 * (a2 + 60 * a1) + a3 - 150;
  if ( cd_savefake_flag )
  {
    if ( loaded_file_type == 3 )
    {
      sub_42FF60(a1, a2, v7, (int)Buffer);
      if ( auto_ppf_load )
      {
        v9 = sub_42C6D0(a1, a2, v7);
        sub_436F60(v9, (int)Buffer);
      }
      if ( cd_savefake_flag == 1 )
        sub_42F8F0(a1, a2, v7, Buffer);
    }
    else
    {
      if ( v38 < dword_4FFF80 || v38 >= dword_4FFF80 + 8 )
      {
        if ( dword_4FD9C4 )
        {
          sub_433530();
          v4 = a1;
          dword_4FD9C4 = 0;
        }
        switch ( dword_504C8C )
        {
          case 1:
            if ( sub_431900(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            v28 = 0;
            dword_5053E0 = 0;
            dword_5053E4 = 0;
            dword_5053E8 = 0;
            goto LABEL_65;
          case 2:
            if ( sub_431990(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            dword_5053EC = dword_5008C0;
            dword_5053E0 = *(_DWORD *)byte_5008B4;
            dword_5053E4 = dword_5008B8;
            dword_5053E8 = dword_5008BC;
            HIBYTE(dword_5053E0) = (unsigned __int8)byte_5008B7 % 10 + 16 * ((unsigned __int8)byte_5008B7 / 10);
            LOBYTE(dword_5053E4) = (unsigned __int8)dword_5008B8 % 10 + 16 * ((unsigned __int8)dword_5008B8 / 10);
            BYTE1(dword_5053E4) = BYTE1(dword_5008B8) % 10 + 16 * (BYTE1(dword_5008B8) / 10);
            HIBYTE(dword_5053E4) = HIBYTE(dword_5008B8) % 10 + 16 * (HIBYTE(dword_5008B8) / 10);
            LOBYTE(dword_5053E8) = (unsigned __int8)dword_5008BC % 10 + 16 * ((unsigned __int8)dword_5008BC / 10);
            BYTE1(dword_5053E8) = BYTE1(dword_5008BC) % 10 + 16 * (BYTE1(dword_5008BC) / 10);
            goto LABEL_66;
          case 3:
            if ( sub_431990(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            dword_5053E0 = *(_DWORD *)byte_5008B4;
            dword_5053E4 = dword_5008B8;
            dword_5053E8 = dword_5008BC;
            dword_5053EC = dword_5008C0;
            goto LABEL_66;
          case 4:
            if ( sub_431900(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            memset(dword_504C04, 0, 0x80u);
            if ( a1 == 3 && (dword_50C280 & 0x1F000000) == 0x1F000000 && sub_431A20(3u, a2, a3, 8u, (int)dword_504C04) )
              dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, a2, v7);
            goto LABEL_64;
          case 5:
            fseek(Stream, 96 * v38, 0);
            fread(byte_4FFF84, 1u, 0x300u, Stream);
            v30 = dword_504C04;
            v31 = byte_4FFF90;
            v36 = 8;
            do
            {
              *v30 = *(_DWORD *)v31;
              v30[1] = *((_DWORD *)v31 + 1);
              v30[2] = *((_DWORD *)v31 + 2);
              v30[3] = *((_DWORD *)v31 + 3);
              v31 += 96;
              v30 += 4;
              --v36;
            }
            while ( v36 );
            v6 = a2;
            if ( !sub_431900(a1, a2, a3, 8u, (int)byte_4FFF84) )
              goto LABEL_56;
            dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            dword_5053E0 = dword_504C04[0];
            dword_5053E4 = dword_504C08;
            dword_5053E8 = dword_504C0C;
            dword_5053EC = dword_504C10;
            goto LABEL_66;
          case 6:
            if ( sub_431900(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            if ( a1 != 3 )
              goto LABEL_46;
            v29 = (int *)((char *)dword_504C84 + 1200 * a2 + 16 * v7);
            dword_5053E0 = *v29;
            dword_5053E4 = v29[1];
            dword_5053E8 = v29[2];
            dword_5053EC = v29[3];
            goto LABEL_66;
          case 7:
            if ( sub_431760(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_46:
            dword_5053E0 = 0;
            dword_5053E4 = 0;
            dword_5053E8 = 0;
            dword_5053EC = 0;
            goto LABEL_66;
          case 8:
            memset(dword_504C04, 0, 0x80u);
            if ( v4 == 3 && (dword_50C280 & 0x1F000000) == 0x1F000000 )
            {
              if ( sub_431810(3u, a2, a3, 8u, (int)byte_4FFF84, dword_504C04) )
                dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, a2, v7);
              v4 = a1;
            }
            if ( sub_431760(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_64:
            dword_5053E0 = dword_504C04[0];
            v28 = dword_504C10;
            dword_5053E4 = dword_504C08;
            dword_5053E8 = dword_504C0C;
            goto LABEL_65;
          case 9:
            fseek(Stream, 96 * v38, 0);
            fread(byte_4FFF84, 1u, 0x300u, Stream);
            v33 = dword_504C04;
            v34 = byte_4FFF90;
            v37 = 8;
            do
            {
              *v33 = *(_DWORD *)v34;
              v33[1] = *((_DWORD *)v34 + 1);
              v33[2] = *((_DWORD *)v34 + 2);
              v33[3] = *((_DWORD *)v34 + 3);
              v34 += 96;
              v33 += 4;
              --v37;
            }
            while ( v37 );
            v6 = a2;
            if ( sub_431760(a1, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_56:
            dword_5053E0 = dword_504C04[0];
            dword_5053E4 = dword_504C08;
            dword_5053E8 = dword_504C0C;
            dword_5053EC = dword_504C10;
            goto LABEL_66;
          case 10:
            if ( sub_431760(v4, a2, a3, 8u, (int)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            if ( a1 == 3 )
            {
              v32 = (int *)((char *)dword_504C84 + 1200 * a2 + 16 * v7);
              dword_5053E0 = *v32;
              dword_5053E4 = v32[1];
              dword_5053E8 = v32[2];
              v28 = v32[3];
LABEL_65:
              dword_5053EC = v28;
            }
            else
            {
              dword_5053E0 = 0;
              dword_5053E4 = 0;
              dword_5053E8 = 0;
              dword_5053EC = 0;
            }
LABEL_66:
            v10 = Buffer;
            dword_4FFF80 = v38;
            qmemcpy(Buffer, byte_4FFF84, 0x930u);
            break;
          default:
            goto LABEL_66;
        }
      }
      else
      {
        v10 = Buffer;
        v11 = v38 - dword_4FFF80;
        qmemcpy(Buffer, &byte_4FFF84[(v38 - dword_4FFF80) * dword_504C88], 0x930u);
        switch ( dword_504C8C )
        {
          case 1:
          case 7:
            dword_5053E0 = 0;
            dword_5053E4 = 0;
            dword_5053E8 = 0;
            dword_5053EC = 0;
            break;
          case 2:
            v13 = (int *)&byte_5008B4[v11 * dword_504C88];
            v14 = v13[1];
            v15 = v13[2];
            dword_5053E0 = *v13;
            dword_5053EC = v13[3];
            dword_5053E4 = v14;
            dword_5053E8 = v15;
            HIBYTE(dword_5053E0) = HIBYTE(dword_5053E0) % 10 + 16 * (HIBYTE(dword_5053E0) / 10);
            LOBYTE(dword_5053E4) = (unsigned __int8)v14 % 10 + 16 * ((unsigned __int8)v14 / 10);
            v16 = (unsigned __int8)(16 * (BYTE1(v14) / 10));
            BYTE1(dword_5053E4) = BYTE4(v16) + v16;
            v17 = (unsigned __int8)(16 * (HIBYTE(v14) / 10));
            HIBYTE(dword_5053E4) = BYTE4(v17) + v17;
            v18 = (unsigned __int8)(16 * ((unsigned __int8)v15 / 10));
            LOBYTE(dword_5053E8) = BYTE4(v18) + v18;
            v19 = (unsigned __int8)(16 * (BYTE1(v15) / 10));
            BYTE1(dword_5053E8) = BYTE4(v19) + v19;
            break;
          case 3:
            v20 = (int *)&byte_5008B4[v11 * dword_504C88];
            v21 = v20[1];
            dword_5053E0 = *v20;
            v22 = v20[2];
            dword_5053E4 = v21;
            v23 = v20[3];
            dword_5053E8 = v22;
            dword_5053EC = v23;
            break;
          case 4:
          case 5:
          case 8:
          case 9:
            v24 = &dword_504C04[4 * v11];
            v25 = v24[1];
            dword_5053E0 = *v24;
            v26 = v24[2];
            v27 = v24[3];
            dword_5053E4 = v25;
            dword_5053E8 = v26;
            dword_5053EC = v27;
            break;
          case 6:
          case 10:
            if ( a1 == 3 )
            {
              v12 = (int *)((char *)dword_504C84 + 1200 * a2 + 16 * v7);
              dword_5053E0 = *v12;
              dword_5053E4 = v12[1];
              dword_5053E8 = v12[2];
              dword_5053EC = v12[3];
            }
            else
            {
              dword_5053E0 = 0;
              dword_5053E4 = 0;
              dword_5053E8 = 0;
              dword_5053EC = 0;
            }
            break;
          default:
            break;
        }
      }
      if ( auto_ppf_load )
      {
        v35 = sub_42C6D0(a1, v6, v7);
        sub_436F60(v35, (int)v10);
      }
      if ( cd_savefake_flag == 1 )
        sub_42F8F0(a1, v6, v7, v10);
    }
    return 0;
  }
  else
  {
    sub_42F990(a1, a2, v7, Buffer);
    return 0;
  }
}
