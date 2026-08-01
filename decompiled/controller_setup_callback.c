#include "pch.h"
INT_PTR __stdcall controller_setup_callback(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
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
        diAcquireAllDevices();
        return 0;
      }
      if ( a2 == 8 )
      {
        diUnacquireAllDevices();
        return 0;
      }
      return 0;
    }
    if ( multitap_1 )
    {
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Disabled");
      v5 = *(_DWORD *)&Keys4[2 * (unsigned __int8)pad_number_menu_selection + 14];
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
      switch ( GamepadAxis[(unsigned __int8)pad_number_menu_selection + 7] )
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
      v7 = g_PlayerDeviceMap4[(unsigned __int8)pad_number_menu_selection];
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
      v9 = dword_4FD8C8[(unsigned __int8)pad_number_menu_selection];
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
    if ( pad_number_menu_selection == 1 )
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
        switch ( g_PlayerDeviceMap1[0] )
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
        if ( g_EffectType2[0] )
        {
          if ( g_EffectType2[0] == 1 )
          {
            SendDlgItemMessageA(hDlg, 1090, CB_SETCURSEL, 0, 0);
          }
          else if ( g_EffectType2[0] == 2 )
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
        v11 = g_EffectType1[0];
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
    else if ( pad_number_menu_selection == 2 && !multitap_1 )
    {
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Digital/Mouse  (F5)");
      SendDlgItemMessageA(hDlg, 1086, CB_ADDSTRING, 0, (LPARAM)"Disabled");
      switch ( dword_456048[1] )
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
      switch ( g_PlayerDeviceMap2 )
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
    edit_button_id = -1;
    v13 = dword_4FD884[2 * (unsigned __int8)pad_number_menu_selection];
    v14 = mdec_disable_flag[2 * (unsigned __int8)pad_number_menu_selection];
    qmemcpy(byte_8A9500, &word_455FA8[16 * (unsigned __int8)pad_number_menu_selection], sizeof(byte_8A9500));
    dword_8B1548 = v13;
    dword_8B154C = v14;
    controller_set_keyboard(hDlg, 0xFFu);
    controller_set_joypad(hDlg, (unsigned __int8)edit_button_id);
    sprintf(String, "PAD NUMBER %d", (unsigned __int8)pad_number_menu_selection);
    SetDlgItemTextA(hDlg, 1049, String);
    SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: NONE");
    SetTimer(hDlg, 0, 0x21u, nullptr);
    hDlgInput = (int)hDlg;
    hInst_For_DInput = (int)g_hInstance;
    if ( diInitDirectInput() == 1 )
      dbg_print_no_flush(" * Direct input init ok. \n");
    diUpdateJoystickStates();
    return 1;
  }
  if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1023:
        edit_button_id = -1;
        cont_set_default(pad_number_menu_selection);
        v29 = hDlg;
        controller_set_keyboard(hDlg, (unsigned __int8)edit_button_id);
        goto LABEL_203;
      case 1031:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: L2");
        edit_button_id = 9;
        return 0;
      case 1032:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: L1");
        edit_button_id = 8;
        return 0;
      case 1033:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: UP");
        edit_button_id = 2;
        return 0;
      case 1034:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: LEFT");
        edit_button_id = 0;
        return 0;
      case 1035:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: DOWN");
        edit_button_id = 3;
        return 0;
      case 1036:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: RIGHT");
        edit_button_id = 1;
        return 0;
      case 1038:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: SELECT");
        edit_button_id = 13;
        return 0;
      case 1039:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: START");
        edit_button_id = 12;
        return 0;
      case 1040:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: R2");
        edit_button_id = 11;
        return 0;
      case 1041:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: R1");
        edit_button_id = 10;
        return 0;
      case 1042:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: TRIANGLE");
        edit_button_id = 4;
        return 0;
      case 1043:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: CIRCLE");
        edit_button_id = 5;
        return 0;
      case 1044:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: X");
        edit_button_id = 6;
        return 0;
      case 1045:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: SQUARE");
        edit_button_id = 7;
        return 0;
      case 1046:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: L3");
        edit_button_id = 14;
        return 0;
      case 1047:
        v27 = (unsigned __int8)pad_number_menu_selection;
        v28 = dword_8B154C;
        qmemcpy(&word_455FA8[16 * (unsigned __int8)pad_number_menu_selection], byte_8A9500, 0x20u);
        dword_4FD884[2 * v27] = dword_8B1548;
        mdec_disable_flag[2 * v27] = v28;
        KillTimer(hDlg, 0);
        EndDialog(hDlg, 1);
        diShutdownDirectInput();
        return 1;
      case 1048:
        v22 = SendDlgItemMessageA(hDlg, 1086, 0x147u, 0, 0);
        if ( v22 != -1 )
        {
          if ( v22 >= 6u || pad_number_menu_selection != 1 || multitap_1 )
          {
            if ( v22 >= 4u || pad_number_menu_selection != 2 || multitap_1 )
            {
              if ( v22 < 3u && multitap_1 )
              {
                v33 = 1;
                v34 = 4;
                v35 = 0;
                v23 = *(&v33 + v22);
                point_device_enabled = 0;
                *(_DWORD *)&Keys4[2 * (unsigned __int8)pad_number_menu_selection + 14] = v23;
              }
            }
            else
            {
              v33 = 1;
              v34 = 4;
              v35 = 2;
              v36 = 0;
              dword_456048[1] = *(&v33 + v22);
              point_device_enabled = 0;
              if ( dword_456048[1] == 2 )
              {
                point_device_enabled = 1;
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
            point_device_enabled = 0;
            if ( dword_456048[0] == 5 || dword_456048[0] == 6 || dword_456048[0] == 2 || dword_456048[0] == 3 )
            {
              point_device_enabled = 1;
              if ( dword_456048[1] == 2 )
              {
                dword_456048[1] = 1;
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
              GamepadAxis[(unsigned __int8)pad_number_menu_selection + 7] = 5;
              break;
            case 1u:
              GamepadAxis[(unsigned __int8)pad_number_menu_selection + 7] = 1;
              break;
            case 2u:
              GamepadAxis[(unsigned __int8)pad_number_menu_selection + 7] = 2;
              break;
            case 3u:
              GamepadAxis[(unsigned __int8)pad_number_menu_selection + 7] = 3;
              break;
            case 4u:
              GamepadAxis[(unsigned __int8)pad_number_menu_selection + 7] = 4;
              break;
            case 5u:
              GamepadAxis[(unsigned __int8)pad_number_menu_selection + 7] = 0;
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
              g_PlayerDeviceMap4[(unsigned __int8)pad_number_menu_selection] = 0;
            }
            else if ( v25 == 2 )
            {
              g_PlayerDeviceMap4[(unsigned __int8)pad_number_menu_selection] = 2;
            }
          }
          else
          {
            g_PlayerDeviceMap4[(unsigned __int8)pad_number_menu_selection] = 1;
          }
        }
        v26 = SendDlgItemMessageA(hDlg, 1089, 0x147u, 0, 0);
        if ( v26 != -1 && v26 < 3u )
        {
          if ( v26 )
          {
            if ( v26 == 1 )
            {
              dword_4FD8C8[(unsigned __int8)pad_number_menu_selection] = 0;
            }
            else if ( v26 == 2 )
            {
              dword_4FD8C8[(unsigned __int8)pad_number_menu_selection] = 2;
            }
          }
          else
          {
            dword_4FD8C8[(unsigned __int8)pad_number_menu_selection] = 1;
          }
        }
        cfg_save_settings();
        KillTimer(hDlg, 0);
        EndDialog(hDlg, 1);
        diShutdownDirectInput();
        return 1;
      case 1049:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: NONE");
        edit_button_id = -1;
        return 0;
      case 1050:
        SetDlgItemTextA(hDlg, 1060, "EDIT BUTTON: R3");
        edit_button_id = 15;
        return 0;
      case 1051:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: Y1");
        edit_button_id = 17;
        return 0;
      case 1052:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: X1");
        edit_button_id = 16;
        return 0;
      case 1053:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: X2");
        edit_button_id = 18;
        return 0;
      case 1054:
        SetDlgItemTextA(hDlg, 1060, "EDIT AXIS: Y2");
        edit_button_id = 19;
        return 0;
      case 1055:
        edit_button_id = -1;
        cont_reset_pad_state(pad_number_menu_selection);
        v29 = hDlg;
        controller_set_keyboard(hDlg, (unsigned __int8)edit_button_id);
        controller_set_joypad(hDlg, (unsigned __int8)edit_button_id);
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
  v15 = edit_button_id;
  LOBYTE(v40) = edit_button_id;
  if ( (unsigned __int8)edit_button_id >= 0x10u )
  {
    if ( (unsigned __int8)edit_button_id >= 0x14u )
      return 1;
    v19 = 0;
    v32 = 0;
    diUpdateDeviceStates();
    v20 = 0;
    v31 = 0;
    v21 = g_KeyboardState;
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
    cont_map_axis_state((unsigned __int8)v40 + 4 * (unsigned __int8)pad_number_menu_selection - 20, v19);
    controller_set_joypad(hDlg, v15 - 16);
    edit_button_id = v15;
    return 1;
  }
  memset(g_KeyboardStatePrev, 0, 0x200u);
  diUpdateDeviceStates();
  for ( i = 0; i < 0x100u; ++i )
  {
    if ( g_KeyboardStatePrev[i] && v15 != 0xFF )
    {
      v30 = i;
      goto LABEL_138;
    }
  }
  v17 = 272;
  while ( 1 )
  {
    if ( g_KeyboardStatePrev[v17] && v15 != 0xFF )
      goto LABEL_107;
    if ( byte_50ABE0[v17] && v15 != 0xFF )
    {
      v17 += 32;
LABEL_107:
      cont_map_button_state(v15 + 16 * ((unsigned __int8)pad_number_menu_selection - 1), v17);
      controller_set_keyboard(hDlg, v15);
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
      while ( !g_KeyboardStatePrev[v17] || v15 == 0xFF )
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
          while ( !g_KeyboardStatePrev[v18] || v15 == 0xFF )
          {
            if ( byte_50ABE0[v18] && v15 != 0xFF )
            {
              cont_map_button_state(v15 + 16 * ((unsigned __int8)pad_number_menu_selection - 1), v18 + 32);
              controller_set_keyboard(hDlg, v15);
              return 1;
            }
            if ( byte_50AC00[v18] && v15 != 0xFF )
            {
              cont_map_button_state(v15 + 16 * ((unsigned __int8)pad_number_menu_selection - 1), v18 + 64);
              controller_set_keyboard(hDlg, v15);
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
  cont_map_button_state(v15 + 16 * ((unsigned __int8)pad_number_menu_selection - 1), v30);
  controller_set_keyboard(hDlg, v15);
  return 1;
}
