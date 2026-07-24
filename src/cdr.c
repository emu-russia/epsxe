#include "pch.h"

int __cdecl cdr_sub_42B680(unsigned __int8 a1)
{
  return a1 % 10 + 16 * (a1 / 10);
}

int __cdecl sub_42B6A0(unsigned __int8 a1)
{
  return (a1 & 0xF) + 10 * (a1 >> 4);
}

char __cdecl cdr_reg0_write(char a1)
{
  char result; // al

  result = byte_50BF66;
  if ( !byte_50BF66 )
  {
    result = a1 - 1;
    if ( a1 == 1 )
    {
      byte_50AEC2 = 1;
    }
    else
    {
      result = a1 - 2;
      if ( a1 == 2 )
      {
        byte_50BF66 = 1;
        byte_50AF07[64] = a1 & 1;
        return result;
      }
    }
    byte_50AF07[64] = a1 & 1;
  }
  return result;
}

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
          cdrom_lba_to_msf_cb(v4, v10, 0, &word_50BF7A, (char *)&word_50BF7A + 1, &unk_50BF7C);
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
            v11 = (unsigned __int8)cdr_sub_42B680(v6);
            v7 = cdr_sub_42B680(dword_50AF50);
            cdrom_lba_to_msf_cb(v7, v11, 0, &word_50BF7A, (char *)&word_50BF7A + 1, &unk_50BF7C);
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
          byte_455945 = 5;
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
            cdrom_verify_sub_cb((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50), dword_50AE80);
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
            cdrom_verify_sub_cb((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), v8, &dword_50BF6C);
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
            cdrom_verify_sub_cb((unsigned __int8)dword_50AF50, v8, BYTE2(dword_50AF50), &dword_50AF03);
            BYTE1(dword_50AF03) = byte_50AF07[70] != 0;
          }
          byte_50AF07[60] = 8;
          byte_50AF07[63] = 3;
        }
        goto LABEL_9;
      case 0x13u:
        cdrom_get_first_last_TN_cb(&a1, &v12);
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
        cdrom_track_to_msf(v9, &a1, &v12, &v13);
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
            irq_cdrom_assert_int();
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
          byte_455945 = 0;
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

char __cdecl cdr_reg2_write(char a1)
{
  char result; // al

  result = byte_50BF66;
  if ( !byte_50BF66 )
  {
    result = byte_50AF07[64];
    if ( byte_50AF07[64] == 2 )
    {
      if ( a1 == 7 && byte_50AF07[61] )
      {
        byte_50AEC2 = 1;
        byte_50AF07[61] = 0;
        byte_50AF07[64] = 0;
        return result;
      }
      goto LABEL_7;
    }
    if ( byte_50AF07[64] )
    {
LABEL_7:
      byte_50BF84 = a1;
      byte_50AF07[64] = 0;
      return result;
    }
    result = byte_50AF07[61];
    *((_BYTE *)&word_50AEC3 + (unsigned __int8)byte_50AF07[61]++) = a1;
    byte_50AF07[64] = 0;
  }
  return result;
}

void __cdecl cdr_reg3_write(char a1)
{
  if ( byte_50BF66 )
  {
    if ( a1 == 32 )
      byte_50BF66 = 0;
  }
  else
  {
    byte_50AF07[65] |= 0x40u;
    if ( byte_50AF07[64] != 1 || (byte_50AF07[64] = 2, a1 != 7) )
      byte_50AF07[64] = 0;
    if ( byte_50AEC2 && a1 == 7 )
    {
      if ( byte_50AF07[62] == 1 && byte_50BF7D )
        --byte_50BF7D;
      byte_50AF07[62] = 0;
      if ( (unsigned __int8)byte_50AEC1 >= (unsigned __int8)byte_50AEC0 && byte_50AF07[63] )
      {
        if ( byte_50AF07[60] )
        {
          qmemcpy(dword_50AE80, &dword_50AF03, (unsigned __int8)byte_50AF07[60]);
          byte_50AEC0 = byte_50AF07[60];
          byte_50AEC1 = 0;
          byte_50AF07[60] = 0;
          byte_50AEC2 = 1;
        }
        byte_50AF07[62] = byte_50AF07[63];
        byte_50AF07[63] = 0;
        if ( byte_50BF84 != 24 )
          irq_cdrom_assert_int();
        if ( byte_50BF6A )
        {
          if ( byte_50BF6B )
          {
            qmemcpy(&dword_50AF03, &dword_50BF6C, (unsigned __int8)byte_50BF6B);
            byte_50AF07[60] = byte_50BF6B;
            byte_50AEC2 = 1;
            byte_50BF6B = 0;
          }
          byte_50AF07[63] = byte_50BF6A;
          byte_50BF6A = 0;
        }
      }
    }
  }
}

int __cdecl sub_42C6D0(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
  int v3; // ecx
  int v4; // eax

  v3 = a2 - 2;
  v4 = a1;
  if ( v3 < 0 )
  {
    v3 += 60;
    v4 = a1 - 1;
  }
  return a3 + 75 * (v3 + 60 * v4);
}

char sub_42C710()
{
  __int16 v0; // bx
  int v1; // eax

  v0 = dword_50AF50;
  v1 = sub_42C6D0(dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
  if ( dword_50BF58 != v1 )
  {
    cdrom_read_data_cb((unsigned __int8)v0, HIBYTE(v0), BYTE2(dword_50AF50), byte_50AF56);
    dword_50BF58 = sub_42C6D0(dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
    LOBYTE(v1) = byte_50AF07[72];
    dword_50BF5C = (byte_50AF07[72] & 0x20) != 0 ? 12 : 24;
    if ( (byte_50AF66[2] & 0xF) == 4 )
    {
      LOBYTE(v1) = byte_50AF07[72] & 0x48;
      if ( (byte_50AF07[72] & 0x48) == 0x40
        || (_BYTE)v1 == 72
        && byte_50AF66[0] == (_BYTE)word_50AF54
        && (LOBYTE(v1) = byte_50AF66[1], byte_50AF66[1] == HIBYTE(word_50AF54)) )
      {
        LOBYTE(v1) = spu_play_adpcm_cb(byte_50AF66);
      }
    }
  }
  return v1;
}

char sub_42C7E0()
{
  char result; // al
  bool v1; // zf

  result = ++BYTE2(dword_50AF50);
  if ( BYTE2(dword_50AF50) == 75 )
  {
    result = BYTE1(dword_50AF50) + 1;
    v1 = BYTE1(dword_50AF50)++ == 59;
    *(_WORD *)((char *)&dword_50AF50 + 1) = BYTE1(dword_50AF50);
    if ( v1 )
    {
      result = dword_50AF50 + 1;
      LOBYTE(dword_50AF50) = dword_50AF50 + 1;
      LOWORD(dword_50AF50) = (unsigned __int8)dword_50AF50;
    }
  }
  return result;
}

char __cdecl sub_42C820(char a1)
{
  LOBYTE(dword_50BF60) = a1;
  return a1;
}

char sub_42C830()
{
  byte_50AEC0 = 0;
  byte_50AF07[60] = 0;
  byte_50AEC1 = 0;
  byte_50AEC2 = 0;
  byte_50AF07[61] = 0;
  byte_50AF07[62] = 0;
  byte_50AF07[64] = 0;
  byte_50AF07[72] = 0;
  dword_50BF58 = 0;
  dword_50BF5C = 0;
  HIBYTE(dword_50BF60) = 0;
  byte_50AF07[70] = 0;
  byte_50BF64 = 0;
  byte_50AF07[68] = 0;
  byte_50AF07[69] = 0;
  byte_50BF66 = 0;
  byte_50BF7D = 0;
  byte_50AF07[65] = 17;
  byte_50AF07[66] = 2;
  HIBYTE(dword_50AF50) = 1;
  return sub_42C820(nocd);
}

int sub_42C8B0()
{
  if ( byte_50BF84 == 24 )
    return 0;
  else
    return (unsigned __int8)byte_50AF07[62];
}

void sub_42C8D0()
{
  if ( byte_50AF07[63] )
  {
    if ( byte_50AF07[60] )
    {
      qmemcpy(dword_50AE80, &dword_50AF03, (unsigned __int8)byte_50AF07[60]);
      byte_50AEC0 = byte_50AF07[60];
      byte_50AEC1 = 0;
      byte_50AF07[60] = 0;
      byte_50AEC2 = 1;
    }
    byte_50AF07[62] = byte_50AF07[63];
    byte_50AF07[63] = 0;
    if ( byte_50BF84 != 24 )
      irq_cdrom_assert_int();
  }
  if ( byte_50BF6A )
  {
    if ( byte_50BF6B )
    {
      qmemcpy(&dword_50AF03, &dword_50BF6C, (unsigned __int8)byte_50BF6B);
      byte_50AF07[60] = byte_50BF6B;
      byte_50BF6B = 0;
    }
    byte_50AF07[63] = byte_50BF6A;
    byte_50BF6A = 0;
  }
}

char sub_42C9A0()
{
  char result; // al

  result = byte_50AF07[62];
  if ( !byte_50AF07[62] && (byte_50AF07[63] || (result = byte_50BF6A) != 0) )
  {
    result = ++word_4FD87C;
    if ( (unsigned __int16)word_4FD87C >= (unsigned __int16)word_455FA6 )
    {
      sub_42C8D0();
      result = 10;
      word_4FD87C = 0;
      if ( (unsigned __int16)word_455FA6 > 0xAu )
        word_455FA6 = 10;
    }
  }
  return result;
}

__int16 sub_42CA00()
{
  __int16 result; // ax

  byte_50BF65 = 1;
  word_50BF82 = 0;
  byte_50BF67 = 0;
  byte_50BF64 = 0;
  if ( country_setting == 1 )
    LOBYTE(result) = byte_50AF07[72] < 0 ? 104 : -48;
  else
    LOBYTE(result) = byte_50AF07[72] < 0 ? 104 : -47;
  byte_50BF68 = result;
  result = (unsigned __int8)result;
  word_50BF7E = result;
  word_50BF80 = (unsigned __int8)result;
  if ( !byte_50AF07[70] )
  {
    result = 3 * (unsigned __int8)result;
    word_50BF80 = result;
  }
  return result;
}

void sub_42CA70()
{
  char v0; // cl

  if ( byte_50AF07[70] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)word_50BF80 )
    {
      v0 = byte_50AF07[72];
      if ( (byte_50AF07[72] & 4) == 4 )
      {
        if ( byte_50AF07[62] )
        {
          if ( byte_50AF07[62] != 1 )
          {
            if ( (byte_50AF07[72] & 2) != 0 )
              byte_50AF07[63] = 1;
            LOBYTE(dword_50AF03) = byte_50AF07[70] | 0x22;
            byte_50AF07[60] = 1;
          }
        }
        else
        {
          byte_50AF07[62] = 1;
          dword_50AE80[0] = byte_50AF07[70] | 0x22;
          if ( (byte_50AF07[72] & 2) != 0 )
          {
            byte_50AEC0 = 1;
          }
          else
          {
            dword_50AE80[1] = 1;
            dword_50AE80[2] = 0x80;
            if ( byte_455FA5 )
              dword_50AE80[3] = cdr_sub_42B680(dword_50AF50);
            else
              dword_50AE80[3] = 0;
            LOBYTE(dword_50AE84) = cdr_sub_42B680(BYTE1(dword_50AF50));
            BYTE1(dword_50AE84) = cdr_sub_42B680(BYTE2(dword_50AF50));
            byte_50AEC0 = 6;
          }
          byte_50AEC1 = 0;
          byte_50AEC2 = 1;
          irq_cdrom_assert_int();
          v0 = byte_50AF07[72];
        }
      }
      if ( (v0 & 2) == 2
        && word_50BF7A == (_BYTE)dword_50AF50
        && MEMORY[0x50BF7B] == *(_WORD *)((char *)&dword_50AF50 + 1)
        && loaded_file_type != 3 )
      {
        byte_50AF07[62] = 4;
        dword_50AE80[0] = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        byte_50AEC2 = 1;
        cdrom_stop_cb();
        byte_50AF07[68] = 1;
        byte_50AF07[65] &= 0x3Fu;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
      }
      word_50BF82 = 0;
      sub_42C7E0();
    }
  }
  else if ( byte_50AF07[67] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)word_50BF80 )
    {
      word_50BF82 = 0;
      if ( !byte_50BF7D )
      {
        sub_42C710();
        dword_50BF5C = (byte_50AF07[72] & 0x20) != 0 ? 12 : 24;
        sub_42C7E0();
        word_50BF80 = word_50BF7E;
        if ( (byte_50AF66[2] & 0xF) != 4 || (byte_50AF07[72] & 0x40) != 0x40 )
        {
          if ( byte_50AF07[62] )
          {
            if ( byte_50AF07[62] == 1 )
              return;
            if ( !byte_50AF07[63] )
            {
              byte_50AF07[63] = 1;
              LOBYTE(dword_50AF03) = 34;
              byte_50AF07[60] = 1;
              ++byte_50BF7D;
              return;
            }
          }
          else if ( !byte_50AF07[63] )
          {
            byte_50AF07[62] = 1;
            dword_50AE80[0] = 34;
            byte_50AEC0 = 1;
            byte_50AEC1 = 0;
            byte_50AEC2 = 1;
            irq_cdrom_assert_int();
            ++byte_50BF7D;
            return;
          }
          byte_50BF6A = 1;
          byte_50BF6B = 1;
          LOBYTE(dword_50BF6C) = 34;
          ++byte_50BF7D;
        }
      }
    }
  }
}

unsigned int cdr_dma()
{
  int v0; // ecx
  unsigned int result; // eax
  unsigned int v2; // edi
  unsigned int v3; // ebp
  int v4; // esi

  v0 = HIWORD(dword_516508);
  result = (unsigned __int16)dword_516508;
  v2 = dword_516504;
  if ( (dword_51650C & 0x11000000) == 0x11000000 )
  {
    if ( !HIWORD(dword_516508) )
      v0 = 1;
    if ( !(_WORD)dword_516508 )
      result = 512;
    v3 = 4 * v0 * result;
    v4 = dword_50BF5C;
    result = v3 + dword_50BF5C;
    dword_50BF5C += v3;
    if ( dword_50C36C == 1 )
      result = dynarec_invalidate_range(dword_516504, v3 >> 2);
    if ( v3 + (v2 & 0x1FFFFF) <= 0x200000 )
    {
      result = mem_dma_read(v2);
      qmemcpy((void *)result, &byte_50AF56[v4], v3);
    }
    byte_50BF64 = 1;
  }
  return result;
}

void sub_42CDE0()
{
  byte_50AF07[68] = 0;
  byte_50AF07[69] = 2;
  dword_50BF58 = 0;
  if ( byte_50AF07[62] )
  {
    byte_50AF07[63] = 2;
    LOBYTE(dword_50AF03) = 16;
    byte_50AF07[60] = 1;
  }
  else
  {
    byte_50AF07[62] = 2;
    dword_50AE80[0] = 16;
    byte_50AEC0 = 1;
    byte_50AEC1 = 0;
    byte_50AEC2 = 1;
    irq_cdrom_assert_int();
  }
}

char sub_42CE40()
{
  char result; // al

  result = byte_50AF07[69];
  if ( byte_50AF07[69] == 1 )
  {
    byte_50AF07[68] = 1;
    byte_50AF07[69] = 0;
    return 0;
  }
  else if ( byte_50AF07[69] )
  {
    return --byte_50AF07[69];
  }
  return result;
}

int __cdecl cdr_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 4396;
  byte_50BF69 = word_4FD87C;
  byte_50BF67 = word_50BF82;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  return gzwrite(a2, (unsigned __int8 *)dword_50AE80, 0x112Cu);
}

int __cdecl sub_42CED0(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dword_50AE80, 4396);
  word_4FD87C = (unsigned __int8)byte_50BF69;
  if ( byte_50AF07[70] )
    return cdrom_play_cdda_cb((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
  else
    return cdrom_stop_cb();
}

int __cdecl cdr_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dword_50AE80, 4396);
  word_50BF7E = (unsigned __int8)byte_50BF68;
  word_50BF80 = (unsigned __int8)byte_50BF68;
  word_4FD87C = (unsigned __int8)byte_50BF69;
  word_50BF82 = (unsigned __int8)byte_50BF67;
  if ( byte_50AF07[70] )
    return cdrom_play_cdda_cb((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
  else
    return cdrom_stop_cb();
}