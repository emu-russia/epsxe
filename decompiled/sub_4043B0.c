#include "pch.h"
INT_PTR __userpurge sub_4043B0@<eax>(int a1@<esi>, HWND hDlg, UINT a3, WPARAM a4, LPARAM a5)
{
  INT_PTR result; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // eax
  unsigned __int8 v16; // bl
  int v17; // edx
  unsigned __int16 i; // ax
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  __int16 v23; // si
  __int16 v24; // dx
  __int16 *v25; // ecx
  unsigned __int16 v26; // ax
  int v27; // ecx
  unsigned __int16 v28; // ax
  unsigned __int16 v29; // ax
  unsigned __int16 v30; // ax
  int v31; // eax
  int v32; // edx
  HWND v33; // esi
  __int16 v34; // [esp-4h] [ebp-43Ch]
  __int16 v35; // [esp-4h] [ebp-43Ch]
  __int16 v36; // [esp-4h] [ebp-43Ch]
  char v37; // [esp+0h] [ebp-438h]
  int v38; // [esp+10h] [ebp-428h]
  unsigned __int16 v39; // [esp+14h] [ebp-424h]
  int v40; // [esp+18h] [ebp-420h]
  int v41; // [esp+1Ch] [ebp-41Ch]
  int v42; // [esp+20h] [ebp-418h]
  int v43; // [esp+24h] [ebp-414h]
  int v44; // [esp+28h] [ebp-410h]
  int v45; // [esp+2Ch] [ebp-40Ch]
  int v46; // [esp+30h] [ebp-408h]
  int v47; // [esp+34h] [ebp-404h]
  CHAR String[1024]; // [esp+38h] [ebp-400h] BYREF

  if ( a3 <= 0x110 )
  {
    if ( a3 != 272 )
    {
      if ( a3 == 6 )
      {
        sub_40E1D0();
        return 0;
      }
      if ( a3 == 8 )
      {
        sub_40E240();
        return 0;
      }
      return 0;
    }
    if ( multitap_1 )
    {
      SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalOnly);
      SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalAnalogF);
      SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDisabled_0);
      v6 = *((_DWORD *)&unk_456044 + (unsigned __int8)byte_44DD1A);
      if ( v6 )
      {
        v7 = v6 - 1;
        if ( v7 )
        {
          if ( v7 == 3 )
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 1u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 2u, 0);
      }
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aBurutter);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy1);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy2);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy3);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy4);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aNone);
      switch ( dword_4FD8A8[(unsigned __int8)byte_44DD1A] )
      {
        case 0:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 5u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 1u, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 2u, 0);
          break;
        case 3:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 3u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 4u, 0);
          break;
        case 5:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 0, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aConstant);
      SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aNone);
      SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aSine);
      v8 = dword_4FD8B8[(unsigned __int8)byte_44DD1A];
      if ( v8 )
      {
        v9 = v8 - 1;
        if ( v9 )
        {
          if ( v9 == 1 )
            SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 2u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 1u, 0);
      }
      SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aConstant);
      SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aNone);
      SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aSine);
      v10 = dword_4FD8C8[(unsigned __int8)byte_44DD1A];
      if ( v10 )
      {
        v11 = v10 - 1;
        if ( v11 )
        {
          if ( v11 == 1 )
            SendDlgItemMessageA(hDlg, 1089, 0x14Eu, 2u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1089, 0x14Eu, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1089, 0x14Eu, 1u, 0);
      }
    }
    if ( byte_44DD1A == 1 )
    {
      if ( !multitap_1 )
      {
        SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalOnly);
        SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalAnalogF);
        SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalAnalogM);
        SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalAnalogM_0);
        SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalGunF5);
        SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalMouseF5);
        SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDisabled_0);
        switch ( dword_456048 )
        {
          case 0:
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 6u, 0);
            break;
          case 1:
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 0, 0);
            break;
          case 2:
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 5u, 0);
            break;
          case 3:
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 4u, 0);
            break;
          case 4:
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 1u, 0);
            break;
          case 5:
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 2u, 0);
            break;
          case 6:
            SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 3u, 0);
            break;
          default:
            break;
        }
        SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aBurutter);
        SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy1);
        SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy2);
        SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy3);
        SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy4);
        SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aNone);
        switch ( dword_4FD8AC )
        {
          case 0:
            SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 5u, 0);
            break;
          case 1:
            SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 1u, 0);
            break;
          case 2:
            SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 2u, 0);
            break;
          case 3:
            SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 3u, 0);
            break;
          case 4:
            SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 4u, 0);
            break;
          case 5:
            SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 0, 0);
            break;
          default:
            break;
        }
        SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aConstant);
        SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aNone);
        SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aSine);
        if ( dword_4FD8BC )
        {
          if ( dword_4FD8BC == 1 )
          {
            SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 0, 0);
          }
          else if ( dword_4FD8BC == 2 )
          {
            SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 2u, 0);
          }
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 1u, 0);
        }
        SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aConstant);
        SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aNone);
        SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aSine);
        v12 = dword_4FD8CC;
LABEL_78:
        if ( v12 )
        {
          v13 = v12 - 1;
          if ( v13 )
          {
            if ( v13 == 1 )
              SendDlgItemMessageA(hDlg, 1089, 0x14Eu, 2u, 0);
          }
          else
          {
            SendDlgItemMessageA(hDlg, 1089, 0x14Eu, 0, 0);
          }
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1089, 0x14Eu, 1u, 0);
        }
      }
    }
    else if ( byte_44DD1A == 2 && !multitap_1 )
    {
      SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalOnly);
      SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalAnalogF);
      SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDigitalMouseF5);
      SendDlgItemMessageA(hDlg, 1086, 0x143u, 0, (LPARAM)aDisabled_0);
      switch ( dword_45604C )
      {
        case 0:
          SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 3u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 0, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 2u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, 1086, 0x14Eu, 1u, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aBurutter);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy1);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy2);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy3);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aDxJoy4);
      SendDlgItemMessageA(hDlg, 1088, 0x143u, 0, (LPARAM)aNone);
      switch ( dword_4FD8B0 )
      {
        case 0:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 5u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 1u, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 2u, 0);
          break;
        case 3:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 3u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 4u, 0);
          break;
        case 5:
          SendDlgItemMessageA(hDlg, 1088, 0x14Eu, 0, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aConstant);
      SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aNone);
      SendDlgItemMessageA(hDlg, 1090, 0x143u, 0, (LPARAM)aSine);
      if ( dword_4FD8C0 )
      {
        if ( dword_4FD8C0 == 1 )
        {
          SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 0, 0);
        }
        else if ( dword_4FD8C0 == 2 )
        {
          SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 2u, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1090, 0x14Eu, 1u, 0);
      }
      SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aConstant);
      SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aNone);
      SendDlgItemMessageA(hDlg, 1089, 0x143u, 0, (LPARAM)aSine);
      v12 = dword_4FD8D0;
      goto LABEL_78;
    }
    byte_44DD44 = -1;
    v14 = dword_4FD884[2 * (unsigned __int8)byte_44DD1A];
    v15 = dword_4FD888[2 * (unsigned __int8)byte_44DD1A];
    qmemcpy(&unk_8A9500, &word_455FA8[16 * (unsigned __int8)byte_44DD1A], 0x20u);
    unk_8B1548 = v14;
    unk_8B154C = v15;
    sub_4042B0(hDlg, 0xFFu);
    sub_4041B0(hDlg, (unsigned __int8)byte_44DD44);
    sprintf(String, "PAD NUMBER %d", (unsigned __int8)byte_44DD1A);
    SetDlgItemTextA(hDlg, 1049, String);
    SetDlgItemTextA(hDlg, 1060, ::String);
    SetTimer(hDlg, 0, 0x21u, nullptr);
    dword_4F7A60 = (int)hDlg;
    dword_4F7A58 = (int)g_hInstance;
    if ( init_direct_input() == 1 )
      dbg_print_no_flush(aDirectInputIni, v37);
    sub_40F010();
    return 1;
  }
  if ( a3 == 273 )
  {
    switch ( (__int16)a4 )
    {
      case 1023:
        byte_44DD44 = -1;
        sub_42DC00((unsigned __int8)byte_44DD1A);
        v33 = hDlg;
        sub_4042B0(hDlg, (unsigned __int8)byte_44DD44);
        goto LABEL_203;
      case 1031:
        SetDlgItemTextA(hDlg, 1060, aEditButtonL2);
        byte_44DD44 = 9;
        return 0;
      case 1032:
        SetDlgItemTextA(hDlg, 1060, aEditButtonL1);
        byte_44DD44 = 8;
        return 0;
      case 1033:
        SetDlgItemTextA(hDlg, 1060, aEditButtonUp);
        byte_44DD44 = 2;
        return 0;
      case 1034:
        SetDlgItemTextA(hDlg, 1060, aEditButtonLeft);
        byte_44DD44 = 0;
        return 0;
      case 1035:
        SetDlgItemTextA(hDlg, 1060, aEditButtonDown);
        byte_44DD44 = 3;
        return 0;
      case 1036:
        SetDlgItemTextA(hDlg, 1060, aEditButtonRigh);
        byte_44DD44 = 1;
        return 0;
      case 1038:
        SetDlgItemTextA(hDlg, 1060, aEditButtonSele);
        byte_44DD44 = 13;
        return 0;
      case 1039:
        SetDlgItemTextA(hDlg, 1060, aEditButtonStar);
        byte_44DD44 = 12;
        return 0;
      case 1040:
        SetDlgItemTextA(hDlg, 1060, aEditButtonR2);
        byte_44DD44 = 11;
        return 0;
      case 1041:
        SetDlgItemTextA(hDlg, 1060, aEditButtonR1);
        byte_44DD44 = 10;
        return 0;
      case 1042:
        SetDlgItemTextA(hDlg, 1060, aEditButtonTria);
        byte_44DD44 = 4;
        return 0;
      case 1043:
        SetDlgItemTextA(hDlg, 1060, aEditButtonCirc);
        byte_44DD44 = 5;
        return 0;
      case 1044:
        SetDlgItemTextA(hDlg, 1060, aEditButtonX);
        byte_44DD44 = 6;
        return 0;
      case 1045:
        SetDlgItemTextA(hDlg, 1060, aEditButtonSqua);
        byte_44DD44 = 7;
        return 0;
      case 1046:
        SetDlgItemTextA(hDlg, 1060, aEditButtonL3);
        byte_44DD44 = 14;
        return 0;
      case 1047:
        v31 = (unsigned __int8)byte_44DD1A;
        v32 = unk_8B154C;
        qmemcpy(&word_455FA8[16 * (unsigned __int8)byte_44DD1A], &unk_8A9500, 0x20u);
        dword_4FD884[2 * v31] = unk_8B1548;
        dword_4FD888[2 * v31] = v32;
        KillTimer(hDlg, 0);
        EndDialog(hDlg, 1);
        sub_40FAB0();
        return 1;
      case 1048:
        v26 = SendDlgItemMessageA(hDlg, 1086, 0x147u, 0, 0);
        if ( v26 != -1 )
        {
          if ( v26 >= 6u || byte_44DD1A != 1 || multitap_1 )
          {
            if ( v26 >= 4u || byte_44DD1A != 2 || multitap_1 )
            {
              if ( v26 < 3u && multitap_1 )
              {
                v40 = 1;
                v41 = 4;
                v42 = 0;
                v27 = *(&v40 + v26);
                dword_4FD8DC = 0;
                *((_DWORD *)&unk_456044 + (unsigned __int8)byte_44DD1A) = v27;
              }
            }
            else
            {
              v40 = 1;
              v41 = 4;
              v42 = 2;
              v43 = 0;
              dword_45604C = *(&v40 + v26);
              dword_4FD8DC = 0;
              if ( dword_45604C == 2 )
              {
                dword_4FD8DC = 1;
                if ( dword_456048 == 5 || dword_456048 == 6 || dword_456048 == 2 || dword_456048 == 3 )
                {
                  dword_456048 = 1;
                  MessageBoxA(nullptr, Text, Caption, 0x40u);
                }
              }
            }
          }
          else
          {
            v40 = 1;
            v41 = 4;
            v42 = 5;
            v43 = 6;
            v44 = 3;
            v45 = 2;
            v46 = 0;
            dword_456048 = *(&v40 + v26);
            dword_4FD8DC = 0;
            if ( dword_456048 == 5 || dword_456048 == 6 || dword_456048 == 2 || dword_456048 == 3 )
            {
              dword_4FD8DC = 1;
              if ( dword_45604C == 2 )
              {
                dword_45604C = 1;
                MessageBoxA(nullptr, Text, Caption, 0x40u);
              }
            }
          }
        }
        v28 = SendDlgItemMessageA(hDlg, 1088, 0x147u, 0, 0);
        if ( v28 != -1 && v28 < 6u )
        {
          switch ( v28 )
          {
            case 0u:
              dword_4FD8A8[(unsigned __int8)byte_44DD1A] = 5;
              break;
            case 1u:
              dword_4FD8A8[(unsigned __int8)byte_44DD1A] = 1;
              break;
            case 2u:
              dword_4FD8A8[(unsigned __int8)byte_44DD1A] = 2;
              break;
            case 3u:
              dword_4FD8A8[(unsigned __int8)byte_44DD1A] = 3;
              break;
            case 4u:
              dword_4FD8A8[(unsigned __int8)byte_44DD1A] = 4;
              break;
            case 5u:
              dword_4FD8A8[(unsigned __int8)byte_44DD1A] = 0;
              break;
          }
        }
        v29 = SendDlgItemMessageA(hDlg, 1090, 0x147u, 0, 0);
        if ( v29 != -1 && v29 < 3u )
        {
          if ( v29 )
          {
            if ( v29 == 1 )
            {
              dword_4FD8B8[(unsigned __int8)byte_44DD1A] = 0;
            }
            else if ( v29 == 2 )
            {
              dword_4FD8B8[(unsigned __int8)byte_44DD1A] = 2;
            }
          }
          else
          {
            dword_4FD8B8[(unsigned __int8)byte_44DD1A] = 1;
          }
        }
        v30 = SendDlgItemMessageA(hDlg, 1089, 0x147u, 0, 0);
        if ( v30 != -1 && v30 < 3u )
        {
          if ( v30 )
          {
            if ( v30 == 1 )
            {
              dword_4FD8C8[(unsigned __int8)byte_44DD1A] = 0;
            }
            else if ( v30 == 2 )
            {
              dword_4FD8C8[(unsigned __int8)byte_44DD1A] = 2;
            }
          }
          else
          {
            dword_4FD8C8[(unsigned __int8)byte_44DD1A] = 1;
          }
        }
        save_settings();
        KillTimer(hDlg, 0);
        EndDialog(hDlg, 1);
        sub_40FAB0();
        return 1;
      case 1049:
        SetDlgItemTextA(hDlg, 1060, ::String);
        byte_44DD44 = -1;
        return 0;
      case 1050:
        SetDlgItemTextA(hDlg, 1060, aEditButtonR3);
        byte_44DD44 = 15;
        return 0;
      case 1051:
        SetDlgItemTextA(hDlg, 1060, aEditAxisY1);
        byte_44DD44 = 17;
        return 0;
      case 1052:
        SetDlgItemTextA(hDlg, 1060, aEditAxisX1);
        byte_44DD44 = 16;
        return 0;
      case 1053:
        SetDlgItemTextA(hDlg, 1060, aEditAxisX2);
        byte_44DD44 = 18;
        return 0;
      case 1054:
        SetDlgItemTextA(hDlg, 1060, aEditAxisY2);
        byte_44DD44 = 19;
        return 0;
      case 1055:
        byte_44DD44 = -1;
        sub_42DCC0((unsigned __int8)byte_44DD1A);
        v33 = hDlg;
        sub_4042B0(hDlg, (unsigned __int8)byte_44DD44);
        sub_4041B0(hDlg, (unsigned __int8)byte_44DD44);
LABEL_203:
        SetDlgItemTextA(v33, 1060, ::String);
        result = 0;
        break;
      default:
        return 0;
    }
    return result;
  }
  if ( a3 != 275 )
    return 0;
  v16 = byte_44DD44;
  LOBYTE(v47) = byte_44DD44;
  if ( (unsigned __int8)byte_44DD44 >= 0x10u )
  {
    if ( (unsigned __int8)byte_44DD44 >= 0x14u )
      return 1;
    v23 = 0;
    v39 = 0;
    sub_40F340();
    v24 = 0;
    v38 = 0;
    v25 = &word_50AE00;
    do
    {
      if ( v38 % 8 && *v25 )
      {
        if ( *v25 < 0 )
          *v25 = -*v25;
        if ( *v25 > (int)v39 )
        {
          v39 = *v25;
          v23 = v24;
        }
      }
      ++v24;
      ++v25;
      ++v38;
    }
    while ( (unsigned __int16)v24 < 0x20u );
    if ( !v23 )
      return 1;
    sub_42DBC0((unsigned __int8)v47 + 4 * (unsigned __int8)byte_44DD1A - 20, v23);
    sub_4041B0(hDlg, v16 - 16);
    byte_44DD44 = v16;
    return 1;
  }
  memset(byte_50ABC0, 0, 0x200u);
  sub_40F340();
  for ( i = 0; i < 0x100u; ++i )
  {
    if ( byte_50ABC0[i] && v16 != 0xFF )
    {
      v34 = i;
      goto LABEL_138;
    }
  }
  v19 = 272;
  while ( 1 )
  {
    v20 = (unsigned __int16)v19;
    if ( byte_50ABC0[(unsigned __int16)v19] && v16 != 0xFF )
      goto LABEL_110;
    if ( byte_50ABE0[(unsigned __int16)v19] && v16 != 0xFF )
    {
      LOWORD(v19) = v19 + 32;
LABEL_107:
      LOWORD(v20) = (unsigned __int8)byte_44DD1A;
      LOWORD(a1) = v16;
      sub_42DBE0(a1 + 16 * (v20 - 1), v19);
      sub_4042B0(hDlg, v16);
      return 1;
    }
    if ( byte_50AC00[(unsigned __int16)v19] && v16 != 0xFF )
      break;
    if ( byte_50AC20[(unsigned __int16)v19] && v16 != 0xFF )
    {
      v19 += 96;
LABEL_110:
      v35 = v19;
      LOWORD(v19) = (unsigned __int8)byte_44DD1A;
      LOWORD(a1) = v16;
      sub_42DBE0(a1 + 16 * (v19 - 1), v35);
      sub_4042B0(hDlg, v16);
      return 1;
    }
    if ( (unsigned __int16)++v19 >= 0x120u )
    {
      v19 = 256;
      while ( 1 )
      {
        v20 = (unsigned __int16)v19;
        if ( byte_50ABC0[(unsigned __int16)v19] )
        {
          if ( v16 != 0xFF )
            goto LABEL_107;
        }
        if ( byte_50ABE0[(unsigned __int16)v19] && v16 != 0xFF )
        {
          LOWORD(v19) = v19 + 32;
          goto LABEL_137;
        }
        if ( byte_50AC00[(unsigned __int16)v19] && v16 != 0xFF )
        {
          v19 += 64;
          goto LABEL_110;
        }
        if ( byte_50AC20[(unsigned __int16)v19] && v16 != 0xFF )
        {
          LOWORD(v19) = v19 + 96;
          goto LABEL_107;
        }
        if ( (unsigned __int16)++v19 >= 0x110u )
        {
          v19 = 384;
          while ( 1 )
          {
            v21 = (unsigned __int16)v19;
            if ( byte_50ABC0[(unsigned __int16)v19] )
            {
              if ( v16 != 0xFF )
                goto LABEL_137;
            }
            if ( byte_50ABE0[(unsigned __int16)v19] && v16 != 0xFF )
            {
              v22 = v19 + 32;
              v36 = v22;
              LOWORD(v22) = (unsigned __int8)byte_44DD1A;
              LOWORD(a1) = v16;
              sub_42DBE0(a1 + 16 * (v22 - 1), v36);
              sub_4042B0(hDlg, v16);
              return 1;
            }
            if ( byte_50AC00[(unsigned __int16)v19] && v16 != 0xFF )
            {
              LOWORD(v21) = (unsigned __int8)byte_44DD1A;
              LOWORD(a1) = v16;
              sub_42DBE0(a1 + 16 * (v21 - 1), v19 + 64);
              sub_4042B0(hDlg, v16);
              return 1;
            }
            if ( byte_50AC20[(unsigned __int16)v19] && v16 != 0xFF )
            {
              LOWORD(v19) = v19 + 96;
              goto LABEL_137;
            }
            if ( (unsigned __int16)++v19 >= 0x184u )
              return 1;
          }
        }
      }
    }
  }
  LOWORD(v19) = v19 + 64;
LABEL_137:
  v34 = v19;
LABEL_138:
  LOWORD(v17) = (unsigned __int8)byte_44DD1A;
  LOWORD(a1) = v16;
  sub_42DBE0(a1 + 16 * (v17 - 1), v34);
  sub_4042B0(hDlg, v16);
  return 1;
}
