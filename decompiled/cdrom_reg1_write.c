#include "pch.h"
void __cdecl cdrom_reg1_write(int a1)
{
  int v1; // esi
  char v2; // al
  char v3; // dl
  unsigned __int8 v4; // al
  int v5; // eax
  unsigned __int8 v6; // al
  int v7; // ecx
  unsigned __int8 v8; // al
  int v9; // [esp-14h] [ebp-24h]
  int v10; // [esp-14h] [ebp-24h]
  int v11; // [esp+8h] [ebp-8h] BYREF
  int v12; // [esp+Ch] [ebp-4h] BYREF

  v1 = dword_50C37C;
  if ( dword_50C37C != 4 && !byte_50BF66 )
  {
    BYTE1(dword_50BF60) = a1;
    byte_50AF44[0] = 0;
    switch ( (char)a1 )
    {
      case 0:
        goto LABEL_93;
      case 1:
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
      case 2:
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
      case 3:
        if ( !byte_50AF4D )
        {
          v9 = (unsigned __int8)sub_42B680(BYTE1(dword_50AF50));
          v4 = sub_42B680((unsigned __int8)dword_50AF50);
          v5 = dword_4FC4D4(v4, v9, 0, &unk_50BF7A, (char *)&unk_50BF7A + 1, &MEMORY[0x50BF7C]);
          LOBYTE(v5) = BYTE1(dword_50AF50);
          if ( unk_50BF7A == (_WORD)dword_50AF50 )
          {
            LOBYTE(v5) = BYTE1(dword_50AF50) + 2;
            BYTE1(dword_50AF50) = v5;
            if ( (unsigned __int8)v5 >= 0x3Cu )
            {
              LOBYTE(v5) = v5 - 60;
              BYTE1(dword_50AF50) = v5;
              LOBYTE(dword_50AF50) = dword_50AF50 + 1;
            }
            v10 = (unsigned __int8)sub_42B680(v5);
            v6 = sub_42B680((unsigned __int8)dword_50AF50);
            dword_4FC4D4(v6, v10, 0, &unk_50BF7A, (char *)&unk_50BF7A + 1, &MEMORY[0x50BF7C]);
            LOBYTE(v5) = BYTE1(dword_50AF50);
          }
          cdrom_play_cdda_cb((unsigned __int8)dword_50AF50, (unsigned __int8)v5, BYTE2(dword_50AF50));
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
      case 4:
      case 5:
        byte_50AF4B = 1;
        goto LABEL_93;
      case 6:
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
          dword_4FC49C();
        goto LABEL_27;
      case 7:
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
      case 8:
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
      case 9:
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
        if ( byte_4FC4E5 )
          dword_455945 = 5;
        word_455FA6 = 550;
        return;
      case 10:
        cdrom_stop_cb();
        byte_50AF48 &= 0x3Fu;
        byte_50AF4F = 0;
        dword_50BF5C = 0;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
        goto LABEL_34;
      case 11:
        byte_50AF4B = 1;
        byte_50AF49 = byte_50AF4A | 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = byte_50AF4A | 2;
        goto LABEL_8;
      case 12:
        byte_50AF4B = 1;
        byte_50AF49 = 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = 2;
        goto LABEL_8;
      case 13:
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
      case 14:
        byte_50AF4B = 1;
        byte_50AF48 |= 0x40u;
        byte_50AF49 = byte_50AF4A | 2;
        byte_50AF4F = word_50AEC3;
        byte_50AF44[1] = 3;
        LOBYTE(dword_50AE80) = byte_50AF4A | 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        goto LABEL_10;
      case 15:
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
      case 16:
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
      case 17:
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
            sub_42FCB0((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50), &dword_50AE80);
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
        v7 = 0;
        if ( byte_50AF44[2] )
        {
          LOBYTE(v7) = BYTE2(dword_50AF50);
          if ( v1 == 3 )
          {
            sub_42FCB0((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), v7, &dword_50BF6C);
          }
          else
          {
            dword_4FC4D8((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), v7, &dword_50BF6C);
            BYTE1(dword_50BF6C) = byte_50AF4D != 0;
          }
          byte_50BF6B = 8;
          byte_50BF6A = 3;
        }
        else
        {
          LOBYTE(v7) = BYTE1(dword_50AF50);
          if ( v1 == 3 )
          {
            sub_42FCB0((unsigned __int8)dword_50AF50, v7, BYTE2(dword_50AF50), &dword_50AF03);
          }
          else
          {
            dword_4FC4D8((unsigned __int8)dword_50AF50, v7, BYTE2(dword_50AF50), &dword_50AF03);
            BYTE1(dword_50AF03) = byte_50AF4D != 0;
          }
          byte_50AF43 = 8;
          byte_50AF44[2] = 3;
        }
        goto LABEL_9;
      case 19:
        dword_4FC4B8(&a1, &v11);
        if ( dword_50C37C == 3 )
        {
          LOBYTE(a1) = 1;
          LOBYTE(v11) = 1;
        }
        byte_50AF49 = 2;
        byte_50AF4B = 1;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = byte_50AF4A | 2;
        BYTE1(dword_50AF03) = sub_42B680(a1);
        BYTE2(dword_50AF03) = sub_42B680(v11);
        byte_50AF43 = 3;
        goto LABEL_9;
      case 20:
        v8 = sub_42B6A0(word_50AEC3);
        dword_4FC4BC(v8, &a1, &v11, &v12);
        byte_50AF4B = 1;
        byte_50AF49 = byte_50AF4A | 2;
        byte_50AF44[2] = 3;
        LOBYTE(dword_50AF03) = byte_50AF4A | 2;
        BYTE1(dword_50AF03) = sub_42B680(a1);
        BYTE2(dword_50AF03) = sub_42B680(v11);
        HIBYTE(dword_50AF03) = sub_42B680(v12);
        byte_50AF43 = 4;
        goto LABEL_9;
      case 21:
      case 22:
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
      case 24:
        goto LABEL_9;
      case 25:
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
      case 26:
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
      case 27:
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
        if ( byte_4FC4E5 )
          dword_455945 = 0;
        byte_50BF7D = 0;
        if ( (byte_50AF4F & 0x40) != 0 )
          dword_4FC49C();
LABEL_27:
        sub_42CA00();
        goto LABEL_9;
      case 28:
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
      case 30:
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
        if ( (unsigned __int8)a1 > 0x1Du )
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
