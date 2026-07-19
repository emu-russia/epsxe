#include "pch.h"
void __cdecl cdr_reg1_write(unsigned __int8 a1)
{
  int v1; // esi
  char v2; // al
  char v3; // dl
  unsigned __int8 v4; // al
  unsigned __int8 v5; // al
  unsigned __int8 v6; // al
  unsigned __int8 v7; // al
  int v8; // ecx
  unsigned __int8 v9; // al
  int v10; // [esp-14h] [ebp-24h]
  int v11; // [esp-14h] [ebp-24h]
  int v12; // [esp+8h] [ebp-8h] BYREF
  int v13; // [esp+Ch] [ebp-4h] BYREF

  v1 = loaded_file_type;
  if ( loaded_file_type != 4 && !byte_50BF66 )
  {
    BYTE1(dword_50BF60) = a1;
    byte_50AF07[61] = 0;
    switch ( a1 )
    {
      case 0u:
        goto LABEL_93;
      case 1u:
        v2 = byte_50AF07[68] == 0 ? 0 : 2;
        byte_50AF07[66] = v2;
        if ( byte_50AF07[69] )
        {
          v2 |= 0x10u;
          byte_50AF07[66] = v2;
        }
        if ( byte_50AF07[63] )
        {
          byte_50BF6A = 3;
          LOBYTE(dword_50BF6C) = v2 | byte_50AF07[67] | byte_50AF07[70];
          byte_50BF6B = 1;
        }
        else
        {
          byte_50AF07[63] = 3;
          LOBYTE(dword_50AF03) = v2 | byte_50AF07[67] | byte_50AF07[70];
LABEL_8:
          byte_50AF07[60] = 1;
        }
        goto LABEL_9;
      case 2u:
        byte_50AF07[68] = 1;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
        byte_50AF07[66] = 2;
        LOBYTE(dword_50AF50) = sub_42B6A0(word_50AEC3);
        BYTE1(dword_50AF50) = sub_42B6A0(HIBYTE(word_50AEC3));
        BYTE2(dword_50AF50) = sub_42B6A0(byte_50AEC5[0]);
        if ( !(_WORD)dword_50AF50 )
          BYTE1(dword_50AF50) = v3;
        dword_5053E0 = 0;
        dword_5053E4 = 0;
        dword_5053E8 = 0;
        byte_50AF07[62] = 0;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = v3;
        byte_50AF07[60] = 1;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        dword_5053EC = 0;
        word_455FA6 = 200;
        return;
      case 3u:
        if ( !byte_50AF07[70] )
        {
          v10 = (unsigned __int8)cdr_sub_42B680(BYTE1(dword_50AF50));
          v4 = cdr_sub_42B680(dword_50AF50);
          dword_4FC4D4(v4, v10, 0, &unk_50BF7A, (char *)&unk_50BF7A + 1, &MEMORY[0x50BF7C]);
          v5 = BYTE1(dword_50AF50);
          if ( unk_50BF7A == (_WORD)dword_50AF50 )
          {
            v6 = BYTE1(dword_50AF50) + 2;
            BYTE1(dword_50AF50) = v6;
            if ( v6 >= 0x3Cu )
            {
              v6 -= 60;
              BYTE1(dword_50AF50) = v6;
              LOBYTE(dword_50AF50) = dword_50AF50 + 1;
            }
            v11 = (unsigned __int8)cdr_sub_42B680(v6);
            v7 = cdr_sub_42B680(dword_50AF50);
            dword_4FC4D4(v7, v11, 0, &unk_50BF7A, (char *)&unk_50BF7A + 1, &MEMORY[0x50BF7C]);
            v5 = BYTE1(dword_50AF50);
          }
          cdrom_play_cdda_cb((unsigned __int8)dword_50AF50, v5, BYTE2(dword_50AF50));
        }
        byte_50AF07[68] = 1;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0x80;
        byte_50AF07[66] = -126;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = -126;
        byte_50AF07[60] = 1;
        sub_42CA00();
        goto LABEL_9;
      case 4u:
      case 5u:
        byte_50AF07[68] = 1;
        goto LABEL_93;
      case 6u:
        cdrom_stop_cb();
        byte_50AF07[66] = 34;
        LOBYTE(dword_50AF03) = 34;
        byte_50AF07[68] = 1;
        byte_50AF07[65] |= 0x40u;
        byte_50AF07[67] = 32;
        byte_50AF07[70] = 0;
        byte_50AF07[62] = 0;
        byte_50AF07[63] = 3;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF07[60] = 1;
        byte_50BF7D = 0;
        if ( (byte_50AF07[72] & 0x40) != 0 )
          spu_set_adpcm_flag_cb();
        goto LABEL_27;
      case 7u:
        cdrom_stop_cb();
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
        byte_50AF07[62] = 0;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF07[68] = 1;
        byte_50AF07[65] &= 0x3Fu;
        byte_50AF07[66] = 2;
        byte_50AF07[63] = 2;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF07[60] = 1;
        return;
      case 8u:
        cdrom_stop_cb();
        byte_50AF07[68] = 0;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
        byte_50AF07[66] = 0;
        byte_50AF07[62] = 2;
        dword_50AE80[0] = 0;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        goto LABEL_10;
      case 9u:
        cdrom_stop_cb();
        byte_50AF07[68] = 1;
        byte_50AF07[65] &= 0x3Fu;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
        byte_50AF07[66] = 2;
        byte_50AF07[62] = 0;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF07[60] = 1;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50BF6A = 2;
        LOBYTE(dword_50BF6C) = 2;
        byte_50BF6B = 1;
        if ( adjust_timing )
          dword_455945 = 5;
        word_455FA6 = 550;
        return;
      case 0xAu:
        cdrom_stop_cb();
        byte_50AF07[65] &= 0x3Fu;
        byte_50AF07[72] = 0;
        dword_50BF5C = 0;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
        goto LABEL_34;
      case 0xBu:
        byte_50AF07[68] = 1;
        byte_50AF07[66] = byte_50AF07[67] | 2;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = byte_50AF07[67] | 2;
        goto LABEL_8;
      case 0xCu:
        byte_50AF07[68] = 1;
        byte_50AF07[66] = 2;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = 2;
        goto LABEL_8;
      case 0xDu:
        byte_50AF07[62] = 0;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF07[68] = 1;
        byte_50AF07[66] = 2;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF07[60] = 1;
        word_50AF54 = word_50AEC3;
        dword_50AE80[0] = 2;
        return;
      case 0xEu:
        byte_50AF07[68] = 1;
        byte_50AF07[65] |= 0x40u;
        byte_50AF07[66] = byte_50AF07[67] | 2;
        byte_50AF07[72] = word_50AEC3;
        byte_50AF07[62] = 3;
        dword_50AE80[0] = byte_50AF07[67] | 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        goto LABEL_10;
      case 0xFu:
        byte_50AF07[66] = 2;
        byte_50AF07[62] = 2;
        dword_50AE80[0] = 2;
        byte_50AF07[68] = 1;
        dword_50AE80[1] = byte_50AF07[72];
        *(_WORD *)&dword_50AE80[2] = word_50AF54;
        LOWORD(dword_50AE84) = 0;
        byte_50AEC0 = 6;
        byte_50AEC1 = 0;
        goto LABEL_10;
      case 0x10u:
        byte_50AF07[68] = 1;
        byte_50AF07[66] = byte_50AF07[67] | 2;
        if ( word_50BF7E != word_50BF80 && byte_50AF07[67] )
          sub_42C710();
        if ( byte_50AF07[62] )
        {
          if ( byte_50AF07[63] )
          {
            dword_50BF6C = dword_50AF62;
            dword_50BF70 = *(_DWORD *)byte_50AF66;
            byte_50BF6A = 3;
            byte_50BF6B = 8;
            if ( byte_4FD881 )
              LOBYTE(dword_50BF6C) = rand();
          }
          else
          {
            dword_50AF03 = dword_50AF62;
            byte_50AF07[1] = byte_50AF66[1];
            byte_50AF07[0] = byte_50AF66[0];
            byte_50AF07[63] = 3;
            byte_50AF07[2] = byte_50AF66[2];
            byte_50AF07[3] = byte_50AF66[3];
            byte_50AF07[60] = 8;
            if ( byte_4FD881 )
              LOBYTE(dword_50AF03) = rand();
          }
        }
        else
        {
          dword_50AE84 = *(_DWORD *)byte_50AF66;
          *(_DWORD *)dword_50AE80 = dword_50AF62;
          byte_50AF07[62] = 3;
          byte_50AEC0 = 8;
          byte_50AEC1 = 0;
          if ( !byte_4FD881 )
            goto LABEL_10;
          dword_50AE80[0] = rand();
        }
        goto LABEL_9;
      case 0x11u:
        byte_50AF07[68] = 1;
        byte_50AF07[66] = byte_50AF07[67] | byte_50AF07[70] | 2;
        if ( word_50BF7E != word_50BF80 && byte_50AF07[67] )
        {
          sub_42C710();
          v1 = loaded_file_type;
        }
        if ( !byte_50AF07[62] )
        {
          if ( v1 == 3 )
          {
            sub_42FCB0(dword_50AF50, BYTE1(dword_50AF50), SBYTE2(dword_50AF50), (int)dword_50AE80);
          }
          else
          {
            dword_4FC4D8((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50), dword_50AE80);
            dword_50AE80[1] = byte_50AF07[70] != 0;
          }
          byte_50AEC0 = 8;
          byte_50AEC1 = 0;
          byte_50AF07[62] = 3;
          goto LABEL_10;
        }
        v8 = 0;
        if ( byte_50AF07[63] )
        {
          LOBYTE(v8) = BYTE2(dword_50AF50);
          if ( v1 == 3 )
          {
            sub_42FCB0(dword_50AF50, BYTE1(dword_50AF50), SBYTE2(dword_50AF50), (int)&dword_50BF6C);
          }
          else
          {
            dword_4FC4D8((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), v8, &dword_50BF6C);
            BYTE1(dword_50BF6C) = byte_50AF07[70] != 0;
          }
          byte_50BF6B = 8;
          byte_50BF6A = 3;
        }
        else
        {
          LOBYTE(v8) = BYTE1(dword_50AF50);
          if ( v1 == 3 )
          {
            sub_42FCB0(dword_50AF50, BYTE1(dword_50AF50), SBYTE2(dword_50AF50), (int)&dword_50AF03);
          }
          else
          {
            dword_4FC4D8((unsigned __int8)dword_50AF50, v8, BYTE2(dword_50AF50), &dword_50AF03);
            BYTE1(dword_50AF03) = byte_50AF07[70] != 0;
          }
          byte_50AF07[60] = 8;
          byte_50AF07[63] = 3;
        }
        goto LABEL_9;
      case 0x13u:
        dword_4FC4B8(&a1, &v12);
        if ( loaded_file_type == 3 )
        {
          a1 = 1;
          LOBYTE(v12) = 1;
        }
        byte_50AF07[66] = 2;
        byte_50AF07[68] = 1;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = byte_50AF07[67] | 2;
        BYTE1(dword_50AF03) = cdr_sub_42B680(a1);
        BYTE2(dword_50AF03) = cdr_sub_42B680(v12);
        byte_50AF07[60] = 3;
        goto LABEL_9;
      case 0x14u:
        v9 = sub_42B6A0(word_50AEC3);
        dword_4FC4BC(v9, &a1, &v12, &v13);
        byte_50AF07[68] = 1;
        byte_50AF07[66] = byte_50AF07[67] | 2;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = byte_50AF07[67] | 2;
        BYTE1(dword_50AF03) = cdr_sub_42B680(a1);
        BYTE2(dword_50AF03) = cdr_sub_42B680(v12);
        HIBYTE(dword_50AF03) = cdr_sub_42B680(v13);
        byte_50AF07[60] = 4;
        goto LABEL_9;
      case 0x15u:
      case 0x16u:
        byte_50AF07[68] = 1;
        byte_50AF07[66] = 2;
        byte_50AF07[62] = 3;
        byte_50BF6A = 2;
        dword_50AE80[0] = 66;
        LOBYTE(dword_50BF6C) = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        byte_50BF6B = 1;
        goto LABEL_10;
      case 0x18u:
        goto LABEL_9;
      case 0x19u:
        byte_50AF07[68] = 1;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = byte_50AF07[66];
        byte_50AF07[60] = 1;
        if ( (unsigned __int8)word_50AEC3 < 4u )
          goto LABEL_78;
        if ( (unsigned __int8)word_50AEC3 <= 5u )
        {
          byte_50BF6B = 1;
          LOBYTE(dword_50BF6C) = 0;
        }
        else
        {
          if ( (_BYTE)word_50AEC3 == 32 )
            dword_50BF6C = *(_DWORD *)"for SCEA";
          else
LABEL_78:
            dword_50BF6C = *(_DWORD *)"for SCEA";
          byte_50BF6B = 4;
        }
        byte_50AF07[66] = 2;
        byte_50BF6A = 2;
        goto LABEL_9;
      case 0x1Au:
        dword_50BF70 = *(_DWORD *)"SCEA";
        byte_50AF07[68] = 1;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
        byte_50AF07[66] = 2;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF07[60] = 1;
        byte_50BF6A = 2;
        dword_50BF6C = 0;
        if ( (_BYTE)dword_50BF60 )
        {
          if ( (unsigned __int8)dword_50BF60 == 2 )
          {
            LOWORD(dword_50BF6C) = -4088;
            byte_50BF6B = 8;
            goto LABEL_9;
          }
        }
        else
        {
          BYTE1(dword_50BF6C) = 0x80;
        }
        byte_50BF6B = 8;
LABEL_9:
        if ( byte_50AF07[62] )
        {
LABEL_10:
          byte_50AEC2 = 1;
          if ( byte_50BF84 != 24 )
            cdrom_assert_int();
        }
        break;
      case 0x1Bu:
        byte_50AF07[66] = 34;
        LOBYTE(dword_50AF03) = 34;
        byte_50AF07[68] = 1;
        byte_50AF07[65] |= 0x40u;
        dword_50BF5C = 255;
        byte_50AF07[67] = 32;
        byte_50AF07[70] = 0;
        byte_50AF07[62] = 0;
        byte_50AF07[63] = 3;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF07[60] = 1;
        if ( adjust_timing )
          dword_455945 = 0;
        byte_50BF7D = 0;
        if ( (byte_50AF07[72] & 0x40) != 0 )
          spu_set_adpcm_flag_cb();
LABEL_27:
        sub_42CA00();
        goto LABEL_9;
      case 0x1Cu:
        cdrom_stop_cb();
        byte_50AF07[68] = 1;
        byte_50AF07[66] = 2;
        byte_50AF07[62] = 2;
        dword_50AE80[0] = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
        goto LABEL_10;
      case 0x1Eu:
LABEL_34:
        byte_50AF07[68] = 1;
        byte_50AF07[66] = 2;
        byte_50AF07[63] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF07[60] = 1;
        byte_50BF6A = 2;
        LOBYTE(dword_50BF6C) = 2;
        byte_50BF6B = 1;
        goto LABEL_9;
      default:
        if ( a1 > 0x1Du )
          return;
LABEL_93:
        byte_50AF07[66] = 2;
        byte_50AF07[62] = 2;
        dword_50AE80[0] = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        goto LABEL_10;
    }
  }
}
