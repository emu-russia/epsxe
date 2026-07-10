#include "pch.h"
void __cdecl cdrom_reg1_write(unsigned __int8 a1)
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

  v1 = dword_50C37C;
  if ( dword_50C37C != 4 && !byte_50BF66 )
  {
    BYTE1(dword_50BF60) = a1;
    byte_50AF44[0] = 0;
    switch ( a1 )
    {
      case 0u:
        goto LABEL_93;
      case 1u:
        v2 = byte_50AF4B == 0 ? 0 : 2;
        byte_50AF49 = v2;
        if ( byte_50AF4C )
        {
          v2 |= 0x10u;
          byte_50AF49 = v2;
        }
        if ( byte_50AF44[2] )
        {
          byte_50BF6A = 3;
          LOBYTE(dword_50BF6C) = v2 | byte_50AF4A | byte_50AF4D;
          byte_50BF6B = 1;
        }
        else
        {
          byte_50AF44[2] = 3;
          LOBYTE(dword_50AF03) = v2 | byte_50AF4A | byte_50AF4D;
LABEL_8:
          byte_50AF43 = 1;
        }
        goto LABEL_9;
      case 2u:
        byte_50AF4B = 1;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        byte_50AF49 = 2;
        LOBYTE(dword_50AF50) = sub_42B6A0(word_50AEC3);
        BYTE1(dword_50AF50) = sub_42B6A0(HIBYTE(word_50AEC3));
        BYTE2(dword_50AF50) = sub_42B6A0(byte_50AEC5);
        if ( !(_WORD)dword_50AF50 )
          BYTE1(dword_50AF50) = v3;
        dword_5053E0 = 0;
        dword_5053E4 = 0;
        dword_5053E8 = 0;
        byte_50AF44[1] = 0;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = v3;
        byte_50AF43 = 1;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        dword_5053EC = 0;
        word_455FA6 = 200;
        return;
      case 3u:
        if ( !byte_50AF4D )
        {
          v10 = (unsigned __int8)sub_42B680(BYTE1(dword_50AF50));
          v4 = sub_42B680(dword_50AF50);
          dword_4FC4D4(v4, v10, 0, &word_50BF7A, (char *)&word_50BF7A + 1, &unk_50BF7C);
          v5 = BYTE1(dword_50AF50);
          if ( word_50BF7A == (_WORD)dword_50AF50 )
          {
            v6 = BYTE1(dword_50AF50) + 2;
            BYTE1(dword_50AF50) = v6;
            if ( v6 >= 0x3Cu )
            {
              v6 -= 60;
              BYTE1(dword_50AF50) = v6;
              LOBYTE(dword_50AF50) = dword_50AF50 + 1;
            }
            v11 = (unsigned __int8)sub_42B680(v6);
            v7 = sub_42B680(dword_50AF50);
            dword_4FC4D4(v7, v11, 0, &word_50BF7A, (char *)&word_50BF7A + 1, &unk_50BF7C);
            v5 = BYTE1(dword_50AF50);
          }
          cdrom_play_cdda_cb((unsigned __int8)dword_50AF50, v5, BYTE2(dword_50AF50));
        }
        byte_50AF4B = 1;
        byte_50AF4A = 0;
        byte_50AF4D = 0x80;
        byte_50AF49 = -126;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = -126;
        byte_50AF43 = 1;
        sub_42CA00();
        goto LABEL_9;
      case 4u:
      case 5u:
        byte_50AF4B = 1;
        goto LABEL_93;
      case 6u:
        cdrom_stop_cb();
        byte_50AF49 = 34;
        LOBYTE(dword_50AF03) = 34;
        byte_50AF4B = 1;
        byte_50AF48 |= 0x40u;
        byte_50AF4A = 32;
        byte_50AF4D = 0;
        byte_50AF44[1] = 0;
        byte_50AF44[2] = 3;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF43 = 1;
        byte_50BF7D = 0;
        if ( (byte_50AF4F & 0x40) != 0 )
          spu_set_adpcm_flag_cb();
        goto LABEL_27;
      case 7u:
        cdrom_stop_cb();
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        byte_50AF44[1] = 0;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF4B = 1;
        byte_50AF48 &= 0x3Fu;
        byte_50AF49 = 2;
        byte_50AF44[2] = 2;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF43 = 1;
        return;
      case 8u:
        cdrom_stop_cb();
        byte_50AF4B = 0;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        byte_50AF49 = 0;
        byte_50AF44[1] = 2;
        LOBYTE(dword_50AE80) = 0;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        goto LABEL_10;
      case 9u:
        cdrom_stop_cb();
        byte_50AF4B = 1;
        byte_50AF48 &= 0x3Fu;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        byte_50AF49 = 2;
        byte_50AF44[1] = 0;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF43 = 1;
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
        byte_50AF48 &= 0x3Fu;
        byte_50AF4F = 0;
        dword_50BF5C = 0;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        goto LABEL_34;
      case 0xBu:
        byte_50AF4B = 1;
        byte_50AF49 = byte_50AF4A | 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = byte_50AF4A | 2;
        goto LABEL_8;
      case 0xCu:
        byte_50AF4B = 1;
        byte_50AF49 = 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = 2;
        goto LABEL_8;
      case 0xDu:
        byte_50AF44[1] = 0;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF4B = 1;
        byte_50AF49 = 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF43 = 1;
        word_50AF54 = word_50AEC3;
        LOBYTE(dword_50AE80) = 2;
        return;
      case 0xEu:
        byte_50AF4B = 1;
        byte_50AF48 |= 0x40u;
        byte_50AF49 = byte_50AF4A | 2;
        byte_50AF4F = word_50AEC3;
        byte_50AF44[1] = 3;
        LOBYTE(dword_50AE80) = byte_50AF4A | 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        goto LABEL_10;
      case 0xFu:
        byte_50AF49 = 2;
        byte_50AF44[1] = 2;
        LOBYTE(dword_50AE80) = 2;
        byte_50AF4B = 1;
        BYTE1(dword_50AE80) = byte_50AF4F;
        HIWORD(dword_50AE80) = word_50AF54;
        LOWORD(dword_50AE84) = 0;
        byte_50AEC0 = 6;
        byte_50AEC1 = 0;
        goto LABEL_10;
      case 0x10u:
        byte_50AF4B = 1;
        byte_50AF49 = byte_50AF4A | 2;
        if ( word_50BF7E != word_50BF80 && byte_50AF4A )
          sub_42C710();
        if ( byte_50AF44[1] )
        {
          if ( byte_50AF44[2] )
          {
            dword_50BF6C = dword_50AF62;
            dword_50BF70 = dword_50AF66;
            byte_50BF6A = 3;
            byte_50BF6B = 8;
            if ( byte_4FD881 )
              LOBYTE(dword_50BF6C) = rand();
          }
          else
          {
            dword_50AF03 = dword_50AF62;
            dword_50AF07 = dword_50AF66;
            byte_50AF44[2] = 3;
            byte_50AF43 = 8;
            if ( byte_4FD881 )
              LOBYTE(dword_50AF03) = rand();
          }
        }
        else
        {
          dword_50AE84 = dword_50AF66;
          dword_50AE80 = dword_50AF62;
          byte_50AF44[1] = 3;
          byte_50AEC0 = 8;
          byte_50AEC1 = 0;
          if ( !byte_4FD881 )
            goto LABEL_10;
          LOBYTE(dword_50AE80) = rand();
        }
        goto LABEL_9;
      case 0x11u:
        byte_50AF4B = 1;
        byte_50AF49 = byte_50AF4A | byte_50AF4D | 2;
        if ( word_50BF7E != word_50BF80 && byte_50AF4A )
        {
          sub_42C710();
          v1 = dword_50C37C;
        }
        if ( !byte_50AF44[1] )
        {
          if ( v1 == 3 )
          {
            sub_42FCB0(dword_50AF50, BYTE1(dword_50AF50), SBYTE2(dword_50AF50), (int)&dword_50AE80);
          }
          else
          {
            dword_4FC4D8((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50), &dword_50AE80);
            BYTE1(dword_50AE80) = byte_50AF4D != 0;
          }
          byte_50AEC0 = 8;
          byte_50AEC1 = 0;
          byte_50AF44[1] = 3;
          goto LABEL_10;
        }
        v8 = 0;
        if ( byte_50AF44[2] )
        {
          LOBYTE(v8) = BYTE2(dword_50AF50);
          if ( v1 == 3 )
          {
            sub_42FCB0(dword_50AF50, BYTE1(dword_50AF50), SBYTE2(dword_50AF50), (int)&dword_50BF6C);
          }
          else
          {
            dword_4FC4D8((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), v8, &dword_50BF6C);
            BYTE1(dword_50BF6C) = byte_50AF4D != 0;
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
            BYTE1(dword_50AF03) = byte_50AF4D != 0;
          }
          byte_50AF43 = 8;
          byte_50AF44[2] = 3;
        }
        goto LABEL_9;
      case 0x13u:
        dword_4FC4B8(&a1, &v12);
        if ( dword_50C37C == 3 )
        {
          a1 = 1;
          LOBYTE(v12) = 1;
        }
        byte_50AF49 = 2;
        byte_50AF4B = 1;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = byte_50AF4A | 2;
        BYTE1(dword_50AF03) = sub_42B680(a1);
        BYTE2(dword_50AF03) = sub_42B680(v12);
        byte_50AF43 = 3;
        goto LABEL_9;
      case 0x14u:
        v9 = sub_42B6A0(word_50AEC3);
        dword_4FC4BC(v9, &a1, &v12, &v13);
        byte_50AF4B = 1;
        byte_50AF49 = byte_50AF4A | 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = byte_50AF4A | 2;
        BYTE1(dword_50AF03) = sub_42B680(a1);
        BYTE2(dword_50AF03) = sub_42B680(v12);
        HIBYTE(dword_50AF03) = sub_42B680(v13);
        byte_50AF43 = 4;
        goto LABEL_9;
      case 0x15u:
      case 0x16u:
        byte_50AF4B = 1;
        byte_50AF49 = 2;
        byte_50AF44[1] = 3;
        byte_50BF6A = 2;
        LOBYTE(dword_50AE80) = 66;
        LOBYTE(dword_50BF6C) = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        byte_50BF6B = 1;
        goto LABEL_10;
      case 0x18u:
        goto LABEL_9;
      case 0x19u:
        byte_50AF4B = 1;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = byte_50AF49;
        byte_50AF43 = 1;
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
            dword_50BF6C = *(_DWORD *)aForScea;
          else
LABEL_78:
            dword_50BF6C = *(_DWORD *)aForScea;
          byte_50BF6B = 4;
        }
        byte_50AF49 = 2;
        byte_50BF6A = 2;
        goto LABEL_9;
      case 0x1Au:
        dword_50BF70 = *(_DWORD *)&aForScea[4];
        byte_50AF4B = 1;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        byte_50AF49 = 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF43 = 1;
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
        if ( byte_50AF44[1] )
        {
LABEL_10:
          byte_50AEC2 = 1;
          if ( byte_50BF84 != 24 )
            cdrom_assert_int();
        }
        break;
      case 0x1Bu:
        byte_50AF49 = 34;
        LOBYTE(dword_50AF03) = 34;
        byte_50AF4B = 1;
        byte_50AF48 |= 0x40u;
        dword_50BF5C = 255;
        byte_50AF4A = 32;
        byte_50AF4D = 0;
        byte_50AF44[1] = 0;
        byte_50AF44[2] = 3;
        byte_50AEC0 = 0;
        byte_50AEC1 = 0;
        byte_50AF43 = 1;
        if ( adjust_timing )
          dword_455945 = 0;
        byte_50BF7D = 0;
        if ( (byte_50AF4F & 0x40) != 0 )
          spu_set_adpcm_flag_cb();
LABEL_27:
        sub_42CA00();
        goto LABEL_9;
      case 0x1Cu:
        cdrom_stop_cb();
        byte_50AF4B = 1;
        byte_50AF49 = 2;
        byte_50AF44[1] = 2;
        LOBYTE(dword_50AE80) = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        goto LABEL_10;
      case 0x1Eu:
LABEL_34:
        byte_50AF4B = 1;
        byte_50AF49 = 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = 2;
        byte_50AF43 = 1;
        byte_50BF6A = 2;
        LOBYTE(dword_50BF6C) = 2;
        byte_50BF6B = 1;
        goto LABEL_9;
      default:
        if ( a1 > 0x1Du )
          return;
LABEL_93:
        byte_50AF49 = 2;
        byte_50AF44[1] = 2;
        LOBYTE(dword_50AE80) = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        goto LABEL_10;
    }
  }
}
