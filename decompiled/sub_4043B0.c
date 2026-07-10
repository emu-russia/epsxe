#include "pch.h"
INT_PTR __stdcall sub_4043B0(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  INT_PTR result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // eax
  unsigned __int8 v15; // bl
  unsigned __int16 i; // ax
  unsigned __int16 v17; // cx
  unsigned __int16 v18; // cx
  __int16 v19; // si
  __int16 v20; // dx
  __int16 *v21; // ecx
  unsigned __int16 v22; // ax
  int v23; // ecx
  unsigned __int16 v24; // ax
  unsigned __int16 v25; // ax
  unsigned __int16 v26; // ax
  int v27; // eax
  int v28; // edx
  HWND v29; // esi
  __int16 v30; // [esp-4h] [ebp-43Ch]
  int v31; // [esp+10h] [ebp-428h]
  unsigned __int16 v32; // [esp+14h] [ebp-424h]
  int v33; // [esp+18h] [ebp-420h]
  int v34; // [esp+1Ch] [ebp-41Ch]
  int v35; // [esp+20h] [ebp-418h]
  int v36; // [esp+24h] [ebp-414h]
  int v37; // [esp+28h] [ebp-410h]
  int v38; // [esp+2Ch] [ebp-40Ch]
  int v39; // [esp+30h] [ebp-408h]
  int v40; // [esp+34h] [ebp-404h]
  CHAR String[1024]; // [esp+38h] [ebp-400h] BYREF

  if ( a2 <= 0x110 )
  {
    if ( a2 != 272 )
    {
      if ( a2 == 6 )
      {
        sub_40E1D0();
        return 0;
      }
      if ( a2 == 8 )
      {
        sub_40E240();
        return 0;
      }
      return 0;
    }
    if ( multitap_1 )
    {
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Disabled");
      v5 = *(_DWORD *)&word_456044[2 * (unsigned __int8)byte_44DD1A];
      if ( v5 )
      {
        v6 = v5 - 1;
        if ( v6 )
        {
          if ( v6 == 3 )
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 1u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 2u, 0);
      }
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"Burutter");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy1");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy2");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy3");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy4");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"None");
      switch ( word_4FD8A8[(unsigned __int8)byte_44DD1A] )
      {
        case 0:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 5u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 1u, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 2u, 0);
          break;
        case 3:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 3u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 4u, 0);
          break;
        case 5:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 0, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"Sine");
      v7 = dword_4FD8B8[(unsigned __int8)byte_44DD1A];
      if ( v7 )
      {
        v8 = v7 - 1;
        if ( v8 )
        {
          if ( v8 == 1 )
            SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 2u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 1u, 0);
      }
      SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"Sine");
      v9 = dword_4FD8C8[(unsigned __int8)byte_44DD1A];
      if ( v9 )
      {
        v10 = v9 - 1;
        if ( v10 )
        {
          if ( v10 == 1 )
            SendDlgItemMessageA(hDlg, 1089, CB_SETCURSEL, 2u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1089, CB_SETCURSEL, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1089, CB_SETCURSEL, 1u, 0);
      }
    }
    if ( byte_44DD1A == 1 )
    {
      if ( !multitap_1 )
      {
        SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
        SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
        SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog Mouse T0 (F5)");
        SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog Mouse T1 (F5)");
        SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Gun    (F5)");
        SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Mouse  (F5)");
        SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Disabled");
        switch ( dword_456048[0] )
        {
          case 0:
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 6u, 0);
            break;
          case 1:
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 0, 0);
            break;
          case 2:
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 5u, 0);
            break;
          case 3:
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 4u, 0);
            break;
          case 4:
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 1u, 0);
            break;
          case 5:
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 2u, 0);
            break;
          case 6:
            SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 3u, 0);
            break;
          default:
            break;
        }
        SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"Burutter");
        SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy1");
        SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy2");
        SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy3");
        SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy4");
        SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"None");
        switch ( dword_4FD8AC[0] )
        {
          case 0:
            SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 5u, 0);
            break;
          case 1:
            SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 1u, 0);
            break;
          case 2:
            SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 2u, 0);
            break;
          case 3:
            SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 3u, 0);
            break;
          case 4:
            SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 4u, 0);
            break;
          case 5:
            SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 0, 0);
            break;
          default:
            break;
        }
        SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"Constant");
        SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"None");
        SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"Sine");
        if ( dword_4FD8BC[0] )
        {
          if ( dword_4FD8BC[0] == 1 )
          {
            SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 0, 0);
          }
          else if ( dword_4FD8BC[0] == 2 )
          {
            SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 2u, 0);
          }
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 1u, 0);
        }
        SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"Constant");
        SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"None");
        SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"Sine");
        v11 = dword_4FD8CC[0];
LABEL_78:
        if ( v11 )
        {
          v12 = v11 - 1;
          if ( v12 )
          {
            if ( v12 == 1 )
              SendDlgItemMessageA(hDlg, 1089, CB_SETCURSEL, 2u, 0);
          }
          else
          {
            SendDlgItemMessageA(hDlg, 1089, CB_SETCURSEL, 0, 0);
          }
        }
        else
        {
          SendDlgItemMessageA(hDlg, 1089, CB_SETCURSEL, 1u, 0);
        }
      }
    }
    else if ( byte_44DD1A == 2 && !multitap_1 )
    {
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Mouse  (F5)");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Disabled");
      switch ( dword_45604C )
      {
        case 0:
          SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 3u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 0, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 2u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, 1086, CB_SETCURSEL, 1u, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"Burutter");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy1");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy2");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy3");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"DX Joy4");
      SendDlgItemMessageA(hDlg, 1088, CB_ADDSTRING, 0, (LPARAM)"None");
      switch ( dword_4FD8B0 )
      {
        case 0:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 5u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 1u, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 2u, 0);
          break;
        case 3:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 3u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 4u, 0);
          break;
        case 5:
          SendDlgItemMessageA(hDlg, 1088, CB_SETCURSEL, 0, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, 1090, CB_ADDSTRING, 0, (LPARAM)"Sine");
      if ( dword_4FD8C0 )
      {
        if ( dword_4FD8C0 == 1 )
        {
          SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 0, 0);
        }
        else if ( dword_4FD8C0 == 2 )
        {
          SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 2u, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 1u, 0);
      }
      SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, 1089, CB_ADDSTRING, 0, (LPARAM)"Sine");
      v11 = dword_4FD8D0;
      goto LABEL_78;
    }
    byte_44DD44 = -1;
    v13 = dword_4FD884[2 * (unsigned __int8)byte_44DD1A];
    v14 = dword_4FD888[2 * (unsigned __int8)byte_44DD1A];
    qmemcpy(&unk_8A9500, &word_455FA8[16 * (unsigned __int8)byte_44DD1A], 0x20u);
    unk_8B1548 = v13;
    unk_8B154C = v14;
    sub_4042B0(hDlg, 0xFFu);
    sub_4041B0(hDlg, (unsigned __int8)byte_44DD44);
    sprintf(String, "PAD NUMBER %d", (unsigned __int8)byte_44DD1A);
    SetDlgItemTextA(hDlg, 1049, String);
    SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: NONE");
    SetTimer(hDlg, 0, 0x21u, nullptr);
    hDlgInput = (int)hDlg;
    hInst_For_DInput = (int)g_hInstance;
    if ( init_direct_input() == 1 )
      dbg_print_no_flush(" * Direct input init ok. \n");
    sub_40F010();
    return 1;
  }
  if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1023:
        byte_44DD44 = -1;
        sub_42DC00(byte_44DD1A);
        v29 = hDlg;
        sub_4042B0(hDlg, (unsigned __int8)byte_44DD44);
        goto LABEL_203;
      case 1031:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: L2");
        byte_44DD44 = 9;
        return 0;
      case 1032:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: L1");
        byte_44DD44 = 8;
        return 0;
      case 1033:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: UP");
        byte_44DD44 = 2;
        return 0;
      case 1034:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: LEFT");
        byte_44DD44 = 0;
        return 0;
      case 1035:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: DOWN");
        byte_44DD44 = 3;
        return 0;
      case 1036:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: RIGHT");
        byte_44DD44 = 1;
        return 0;
      case 1038:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: SELECT");
        byte_44DD44 = 13;
        return 0;
      case 1039:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: START");
        byte_44DD44 = 12;
        return 0;
      case 1040:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: R2");
        byte_44DD44 = 11;
        return 0;
      case 1041:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: R1");
        byte_44DD44 = 10;
        return 0;
      case 1042:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: TRIANGLE");
        byte_44DD44 = 4;
        return 0;
      case 1043:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: CIRCLE");
        byte_44DD44 = 5;
        return 0;
      case 1044:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: X");
        byte_44DD44 = 6;
        return 0;
      case 1045:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: SQUARE");
        byte_44DD44 = 7;
        return 0;
      case 1046:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: L3");
        byte_44DD44 = 14;
        return 0;
      case 1047:
        v27 = (unsigned __int8)byte_44DD1A;
        v28 = unk_8B154C;
        qmemcpy(&word_455FA8[16 * (unsigned __int8)byte_44DD1A], &unk_8A9500, 0x20u);
        dword_4FD884[2 * v27] = unk_8B1548;
        dword_4FD888[2 * v27] = v28;
        KillTimer(hDlg, 0);
        EndDialog(hDlg, 1);
        sub_40FAB0();
        return 1;
      case 1048:
        v22 = SendDlgItemMessageA(hDlg, 1086, 0x147u, 0, 0);
        if ( v22 != -1 )
        {
          if ( v22 >= 6u || byte_44DD1A != 1 || multitap_1 )
          {
            if ( v22 >= 4u || byte_44DD1A != 2 || multitap_1 )
            {
              if ( v22 < 3u && multitap_1 )
              {
                v33 = 1;
                v34 = 4;
                v35 = 0;
                v23 = *(&v33 + v22);
                dword_4FD8DC = 0;
                *(_DWORD *)&word_456044[2 * (unsigned __int8)byte_44DD1A] = v23;
              }
            }
            else
            {
              v33 = 1;
              v34 = 4;
              v35 = 2;
              v36 = 0;
              dword_45604C = *(&v33 + v22);
              dword_4FD8DC = 0;
              if ( dword_45604C == 2 )
              {
                dword_4FD8DC = 1;
                if ( dword_456048[0] == 5 || dword_456048[0] == 6 || dword_456048[0] == 2 || dword_456048[0] == 3 )
                {
                  dword_456048[0] = 1;
                  MessageBoxA(
                    nullptr,
                    "Sorry only 1 mouse supported, \n the other pad will be set to Digital Joypad",
                    "Only 1 mouse supported",
                    0x40u);
                }
              }
            }
          }
          else
          {
            v33 = 1;
            v34 = 4;
            v35 = 5;
            v36 = 6;
            v37 = 3;
            v38 = 2;
            v39 = 0;
            dword_456048[0] = *(&v33 + v22);
            dword_4FD8DC = 0;
            if ( dword_456048[0] == 5 || dword_456048[0] == 6 || dword_456048[0] == 2 || dword_456048[0] == 3 )
            {
              dword_4FD8DC = 1;
              if ( dword_45604C == 2 )
              {
                dword_45604C = 1;
                MessageBoxA(
                  nullptr,
                  "Sorry only 1 mouse supported, \n the other pad will be set to Digital Joypad",
                  "Only 1 mouse supported",
                  0x40u);
              }
            }
          }
        }
        v24 = SendDlgItemMessageA(hDlg, 1088, 0x147u, 0, 0);
        if ( v24 != -1 && v24 < 6u )
        {
          switch ( v24 )
          {
            case 0u:
              word_4FD8A8[(unsigned __int8)byte_44DD1A] = 5;
              break;
            case 1u:
              word_4FD8A8[(unsigned __int8)byte_44DD1A] = 1;
              break;
            case 2u:
              word_4FD8A8[(unsigned __int8)byte_44DD1A] = 2;
              break;
            case 3u:
              word_4FD8A8[(unsigned __int8)byte_44DD1A] = 3;
              break;
            case 4u:
              word_4FD8A8[(unsigned __int8)byte_44DD1A] = 4;
              break;
            case 5u:
              word_4FD8A8[(unsigned __int8)byte_44DD1A] = 0;
              break;
          }
        }
        v25 = SendDlgItemMessageA(hDlg, 1090, 0x147u, 0, 0);
        if ( v25 != -1 && v25 < 3u )
        {
          if ( v25 )
          {
            if ( v25 == 1 )
            {
              dword_4FD8B8[(unsigned __int8)byte_44DD1A] = 0;
            }
            else if ( v25 == 2 )
            {
              dword_4FD8B8[(unsigned __int8)byte_44DD1A] = 2;
            }
          }
          else
          {
            dword_4FD8B8[(unsigned __int8)byte_44DD1A] = 1;
          }
        }
        v26 = SendDlgItemMessageA(hDlg, 1089, 0x147u, 0, 0);
        if ( v26 != -1 && v26 < 3u )
        {
          if ( v26 )
          {
            if ( v26 == 1 )
            {
              dword_4FD8C8[(unsigned __int8)byte_44DD1A] = 0;
            }
            else if ( v26 == 2 )
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
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: NONE");
        byte_44DD44 = -1;
        return 0;
      case 1050:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: R3");
        byte_44DD44 = 15;
        return 0;
      case 1051:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: Y1");
        byte_44DD44 = 17;
        return 0;
      case 1052:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: X1");
        byte_44DD44 = 16;
        return 0;
      case 1053:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: X2");
        byte_44DD44 = 18;
        return 0;
      case 1054:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: Y2");
        byte_44DD44 = 19;
        return 0;
      case 1055:
        byte_44DD44 = -1;
        sub_42DCC0(byte_44DD1A);
        v29 = hDlg;
        sub_4042B0(hDlg, (unsigned __int8)byte_44DD44);
        sub_4041B0(hDlg, (unsigned __int8)byte_44DD44);
LABEL_203:
        SetDlgItemTextA(v29, 1060, "EDIT BUTTON: NONE");
        result = 0;
        break;
      default:
        return 0;
    }
    return result;
  }
  if ( a2 != 275 )
    return 0;
  v15 = byte_44DD44;
  LOBYTE(v40) = byte_44DD44;
  if ( (unsigned __int8)byte_44DD44 >= 0x10u )
  {
    if ( (unsigned __int8)byte_44DD44 >= 0x14u )
      return 1;
    v19 = 0;
    v32 = 0;
    sub_40F340();
    v20 = 0;
    v31 = 0;
    v21 = word_50AE00;
    do
    {
      if ( v31 % 8 && *v21 )
      {
        if ( *v21 < 0 )
          *v21 = -*v21;
        if ( *v21 > (int)v32 )
        {
          v32 = *v21;
          v19 = v20;
        }
      }
      ++v20;
      ++v21;
      ++v31;
    }
    while ( (unsigned __int16)v20 < 0x20u );
    if ( !v19 )
      return 1;
    sub_42DBC0((unsigned __int8)v40 + 4 * (unsigned __int8)byte_44DD1A - 20, v19);
    sub_4041B0(hDlg, v15 - 16);
    byte_44DD44 = v15;
    return 1;
  }
  memset(byte_50ABC0, 0, 0x200u);
  sub_40F340();
  for ( i = 0; i < 0x100u; ++i )
  {
    if ( byte_50ABC0[i] && v15 != 0xFF )
    {
      v30 = i;
      goto LABEL_138;
    }
  }
  v17 = 272;
  while ( 1 )
  {
    if ( byte_50ABC0[v17] && v15 != 0xFF )
      goto LABEL_107;
    if ( byte_50ABE0[v17] && v15 != 0xFF )
    {
      v17 += 32;
LABEL_107:
      sub_42DBE0(v15 + 16 * ((unsigned __int8)byte_44DD1A - 1), v17);
      sub_4042B0(hDlg, v15);
      return 1;
    }
    if ( byte_50AC00[v17] && v15 != 0xFF )
      break;
    if ( byte_50AC20[v17] && v15 != 0xFF )
    {
      v17 += 96;
      goto LABEL_107;
    }
    if ( ++v17 >= 0x120u )
    {
      v17 = 256;
      while ( !byte_50ABC0[v17] || v15 == 0xFF )
      {
        if ( byte_50ABE0[v17] && v15 != 0xFF )
        {
          v18 = v17 + 32;
          goto LABEL_137;
        }
        if ( byte_50AC00[v17] && v15 != 0xFF )
        {
          v17 += 64;
          goto LABEL_107;
        }
        if ( byte_50AC20[v17] && v15 != 0xFF )
        {
          v17 += 96;
          goto LABEL_107;
        }
        if ( ++v17 >= 0x110u )
        {
          v18 = 384;
          while ( !byte_50ABC0[v18] || v15 == 0xFF )
          {
            if ( byte_50ABE0[v18] && v15 != 0xFF )
            {
              sub_42DBE0(v15 + 16 * ((unsigned __int8)byte_44DD1A - 1), v18 + 32);
              sub_4042B0(hDlg, v15);
              return 1;
            }
            if ( byte_50AC00[v18] && v15 != 0xFF )
            {
              sub_42DBE0(v15 + 16 * ((unsigned __int8)byte_44DD1A - 1), v18 + 64);
              sub_4042B0(hDlg, v15);
              return 1;
            }
            if ( byte_50AC20[v18] && v15 != 0xFF )
            {
              v18 += 96;
              goto LABEL_137;
            }
            if ( ++v18 >= 0x184u )
              return 1;
          }
          goto LABEL_137;
        }
      }
      goto LABEL_107;
    }
  }
  v18 = v17 + 64;
LABEL_137:
  v30 = v18;
LABEL_138:
  sub_42DBE0(v15 + 16 * ((unsigned __int8)byte_44DD1A - 1), v30);
  sub_4042B0(hDlg, v15);
  return 1;
}
