#include "pch.h"
BOOL __cdecl open_file_dialog(const CHAR *a1, const CHAR *a2, CHAR *a3, const CHAR *a4, const CHAR *a5)
{
  BOOL result; // eax
  int v6; // eax
  CHAR v7; // cl
  OPENFILENAMEA v8; // [esp+4h] [ebp-84Ch] BYREF NOPROP
  _BYTE v9[1024]; // [esp+450h] [ebp-400h] BYREF

  memset(&v8.pvReserved, 0, 0x400u);
  memset(v9, 0, sizeof(v9));
  v8.lpstrFile = (LPSTR)&v8.pvReserved;
  v8.hwndOwner = g_hWnd;
  v8.lpstrFilter = a2;
  v8.lpstrFileTitle = v9;
  v8.nMaxFile = 1024;
  v8.lpstrInitialDir = a4;
  v8.nMaxFileTitle = 1024;
  v8.lStructSize = 76;
  v8.lpstrCustomFilter = nullptr;
  v8.nMaxCustFilter = 0;
  v8.nFilterIndex = 1;
  v8.lpstrTitle = a1;
  v8.lpstrDefExt = a5;
  v8.Flags = 12;
  result = GetOpenFileNameA(&v8);
  if ( result )
  {
    v6 = 0;
    do
    {
      v7 = *((_BYTE *)&v8.pvReserved + v6);
      temp_path[v6++] = v7;
    }
    while ( v7 );
    return 1;
  }
  return result;
}

BOOL __cdecl controller_set_joypad(HWND hDlg, unsigned __int16 a2)
{
  int v2; // ebp
  int *v3; // esi
  int v4; // ecx
  int v5; // ecx
  int v7; // [esp+10h] [ebp-404h]
  CHAR String[1024]; // [esp+14h] [ebp-400h] BYREF

  v2 = 0;
  v3 = &nIDDlgItem;
  v7 = 4;
  do
  {
    v4 = v2 + 4 * (unsigned __int8)pad_number_menu_selection;
    if ( *((_WORD *)dword_4FD884 + v4) >= 0x20u )
    {
      sprintf(String, "%d", *((unsigned __int16 *)dword_4FD884 + v4));
      SetDlgItemTextA(hDlg, *(unsigned __int16 *)v3, String);
    }
    else
    {
      SetDlgItemTextA(hDlg, *(unsigned __int16 *)v3, &joy_names[14 * *((unsigned __int16 *)dword_4FD884 + v4)]);
    }
    ++v2;
    v3 = (int *)((char *)v3 + 2);
    --v7;
  }
  while ( v7 );
  v5 = a2 + 4 * (unsigned __int8)pad_number_menu_selection;
  if ( *((_WORD *)dword_4FD884 + v5) < 0x20u )
    return SetDlgItemTextA(
             hDlg,
             *((unsigned __int16 *)&nIDDlgItem + a2),
             &joy_names[14 * *((unsigned __int16 *)dword_4FD884 + v5)]);
  sprintf(String, "%d", *((unsigned __int16 *)dword_4FD884 + v5));
  return SetDlgItemTextA(hDlg, *((unsigned __int16 *)&nIDDlgItem + a2), String);
}

int __cdecl controller_set_keyboard(HWND hDlg, unsigned __int16 a2)
{
  int v2; // ebp
  int *v3; // esi
  KBD_NAME *v4; // eax
  int result; // eax
  int v6; // edx
  int v7; // [esp+10h] [ebp-404h]
  CHAR String[1024]; // [esp+14h] [ebp-400h] BYREF

  v2 = 0;
  v3 = &word_44DD1C;
  v7 = 16;
  do
  {
    if ( (unsigned __int16)word_455FA8[16 * (unsigned __int8)pad_number_menu_selection + v2] >= 0x200u )
    {
      sprintf(String, "%d", (unsigned __int16)word_455FA8[16 * (unsigned __int8)pad_number_menu_selection + v2]);
      v4 = (KBD_NAME *)String;
    }
    else
    {
      v4 = &stru_44C148[(unsigned __int16)word_455FA8[16 * (unsigned __int8)pad_number_menu_selection + v2]];
    }
    SetDlgItemTextA(hDlg, *(unsigned __int16 *)v3, v4->text);
    ++v2;
    v3 = (int *)((char *)v3 + 2);
    result = --v7;
  }
  while ( v7 );
  if ( a2 < 0xFFu )
  {
    v6 = a2 + 16 * (unsigned __int8)pad_number_menu_selection;
    if ( (unsigned __int16)word_455FA8[v6] >= 0x200u )
    {
      sprintf(String, "%d", (unsigned __int16)word_455FA8[v6]);
      return SetDlgItemTextA(hDlg, *((unsigned __int16 *)&word_44DD1C + a2), String);
    }
    else
    {
      return SetDlgItemTextA(
               hDlg,
               *((unsigned __int16 *)&word_44DD1C + a2),
               stru_44C148[(unsigned __int16)word_455FA8[v6]].text);
    }
  }
  return result;
}

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
        switch ( controller_port_modes[0] )
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
      switch ( controller_port_modes[1] )
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
              controller_port_modes[1] = *(&v33 + v22);
              point_device_enabled = 0;
              if ( controller_port_modes[1] == 2 )
              {
                point_device_enabled = 1;
                if ( controller_port_modes[0] == 5
                  || controller_port_modes[0] == 6
                  || controller_port_modes[0] == 2
                  || controller_port_modes[0] == 3 )
                {
                  controller_port_modes[0] = 1;
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
            controller_port_modes[0] = *(&v33 + v22);
            point_device_enabled = 0;
            if ( controller_port_modes[0] == 5
              || controller_port_modes[0] == 6
              || controller_port_modes[0] == 2
              || controller_port_modes[0] == 3 )
            {
              point_device_enabled = 1;
              if ( controller_port_modes[1] == 2 )
              {
                controller_port_modes[1] = 1;
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

LRESULT __stdcall cheat_dialog_callback(HWND hDlg, int a2, __int16 a3, int a4)
{
  LRESULT v4; // eax
  LRESULT v5; // esi
  LRESULT result; // eax
  LRESULT v7; // eax
  LRESULT v8; // esi
  FILE *v9; // ebp
  FILE *v10; // edi
  LRESULT v11; // eax
  LRESULT v12; // esi
  unsigned int i; // esi
  int v14; // [esp+10h] [ebp-C08h] BYREF
  int v15; // [esp+14h] [ebp-C04h] BYREF
  char lParam[1024]; // [esp+18h] [ebp-C00h] BYREF
  CHAR String[1024]; // [esp+418h] [ebp-800h] BYREF
  CHAR Buffer[1024]; // [esp+818h] [ebp-400h] BYREF

  if ( a2 == 272 )
  {
    for ( i = 0; i < (unsigned __int8)active_mini_cheat_count; ++i )
    {
      sprintf(lParam, "  %06x    %08x", mini_cheat_id_array[2 * i], mini_cheat_attr_array[2 * i]);
      SendDlgItemMessageA(hDlg, 1142, 0x180u, 0, (LPARAM)lParam);
    }
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( a3 )
    {
      case 1056:
        if ( !open_file_dialog("Open PSX CHEAT", "PSX CHEATs (*.CHT)", temp_path, "cheats\\", "CHT") )
          return 0;
        v9 = fopen(temp_path, "r");
        while ( (v9->_flag & 0x10) == 0 )
        {
          sprintf(lParam, asc_44E24C);
          fgets(lParam, 1024, v9);
          if ( lParam[0] != 35 && sscanf(lParam, "%x %x", &v15, &v14) == 2 )
          {
            sprintf(lParam, "  %06x    %08x", v15 & 0x1FFFFF, v14);
            SendDlgItemMessageA(hDlg, 1142, 0x180u, 0, (LPARAM)lParam);
          }
        }
        fclose(v9);
        result = 0;
        break;
      case 1057:
        if ( open_file_dialog("Save PSX CHEAT", "PSX CHEATs (*.CHT)", temp_path, "cheats\\", "CHT") )
        {
          v10 = fopen(temp_path, aW);
          v11 = SendDlgItemMessageA(hDlg, 1142, 0x18Bu, 0, 0);
          if ( v11 )
          {
            do
            {
              v12 = v11 - 1;
              SendDlgItemMessageA(hDlg, 1142, 0x189u, v11 - 1, (LPARAM)lParam);
              sscanf(lParam, "  %06x    %08x", &v15, &v14);
              sprintf(lParam, "%x %x\n", v15, v14);
              fputs(lParam, v10);
              v11 = v12;
            }
            while ( v12 );
          }
          fclose(v10);
        }
        return 0;
      case 1058:
        v4 = SendDlgItemMessageA(hDlg, 1142, 0x18Bu, 0, 0);
        active_mini_cheat_count = 0;
        if ( v4 )
        {
          do
          {
            v5 = v4 - 1;
            SendDlgItemMessageA(hDlg, 1142, 0x189u, v4 - 1, (LPARAM)lParam);
            sscanf(
              lParam,
              "  %06x    %08x",
              &mini_cheat_id_array[2 * (unsigned __int8)active_mini_cheat_count],
              &mini_cheat_attr_array[2 * (unsigned __int8)active_mini_cheat_count]);
            v4 = v5;
            ++active_mini_cheat_count;
          }
          while ( v5 );
        }
        EndDialog(hDlg, 1);
        result = 1;
        break;
      case 1059:
        EndDialog(hDlg, 1);
        result = 1;
        break;
      case 1143:
        result = SendDlgItemMessageA(hDlg, 1142, 0x18Bu, 0, 0);
        if ( !result )
          return 0;
        do
        {
          v8 = result - 1;
          SendDlgItemMessageA(hDlg, 1142, 0x182u, result - 1, 0);
          result = v8;
        }
        while ( v8 );
        break;
      case 1144:
        v7 = SendDlgItemMessageA(hDlg, 1142, 0x188u, 0, 0);
        if ( v7 == -1 )
          return 0;
        SendDlgItemMessageA(hDlg, 1142, 0x182u, v7, 0);
        result = 0;
        break;
      case 1145:
        GetDlgItemTextA(hDlg, 1055, String, 1024);
        GetDlgItemTextA(hDlg, 1146, Buffer, 1024);
        sscanf(String, "%x", &v14);
        sscanf(Buffer, "%x", &v15);
        sprintf(lParam, "  %06x    %08x", v15, v14);
        SendDlgItemMessageA(hDlg, 1142, 0x180u, 0, (LPARAM)lParam);
        result = 0;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

int __stdcall about_callback(HWND hDlg, int a2, __int16 a3, int a4)
{
  if ( a2 == 272 )
    return 1;
  if ( a2 == 273 && a3 == 1002 )
  {
    EndDialog(hDlg, 1);
    return 1;
  }
  return 0;
}

INT_PTR __stdcall bios_dialog_callback(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  INT_PTR result; // eax

  if ( a2 == 272 )
  {
    SetDlgItemTextA(hDlg, 1025, (LPCSTR)bios_name);
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1025:
        return 1;
      case 1027:
        if ( !open_file_dialog("Select PSX BIOS", "PSX BIOS (*.BIN)", temp_path, "bios\\", "BIN") )
          return 1;
        SetDlgItemTextA(hDlg, 1025, temp_path);
        result = 1;
        break;
      case 1028:
        GetDlgItemTextA(hDlg, 1025, (LPSTR)bios_name, 1024);
        EndDialog(hDlg, 1);
        cfg_save_settings();
        result = 1;
        break;
      case 1029:
        EndDialog(hDlg, 1);
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

INT_PTR __stdcall search_video_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  INT_PTR result; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  HMODULE v9; // esi
  char v10; // al
  unsigned int v11; // eax
  HMODULE v12; // esi
  unsigned int v13; // eax
  HMODULE v14; // esi
  HMODULE LibraryA; // eax
  HMODULE v16; // esi
  FARPROC PSEgetLibVersion_ptr; // eax
  unsigned __int8 v18; // al
  int v19; // eax
  const char *v20; // eax
  LRESULT v21; // ebp
  int v22; // ebx
  CHAR *cFileName; // eax
  char *v24; // edx
  CHAR v25; // cl
  char *v26; // esi
  int v27; // edi
  char *v28; // eax
  char v29; // cl
  int v30; // ebp
  CHAR *v31; // eax
  char v32; // cl
  int v33; // [esp-18h] [ebp-D68h]
  int v34; // [esp-14h] [ebp-D64h]
  char v35[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  CHAR FileName[1024]; // [esp+550h] [ebp-800h] BYREF
  char lParam[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v35, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v35[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print("not video plugins found\n");
    dword_45B8E4 = 0;
    do
    {
      sprintf(LibFileName, "%s%s", v35, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v16 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v16, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(v16, "PSEgetLibVersion");
        PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              v18 = PSEgetLibVersion_ptr();
              v19 = PSEgetLibVersion(v18);
              v20 = (const char *)PSEgetLibName(BYTE1(v19));
              sprintf(lParam, "%s %d.%d", v20, v33, v34);
              if ( PSEgetLibType() == 2 )
              {
                v21 = SendDlgItemMessageA(hDlg, 1017, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)VideoPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(hDlg, 1017, 0x14Eu, v21, 0);
                v22 = dword_45B8E4;
                if ( v21 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v24 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                  do
                  {
                    v25 = *cFileName;
                    cFileName[(_DWORD)v24] = *cFileName;
                    ++cFileName;
                  }
                  while ( v25 );
                }
                else
                {
                  if ( v21 < dword_45B8E4 )
                  {
                    v26 = &byte_8A9140[1024 * dword_45B8E4];
                    v27 = dword_45B8E4 - v21;
                    do
                    {
                      v28 = v26;
                      do
                      {
                        v29 = *v28;
                        v28[1024] = *v28;
                        ++v28;
                      }
                      while ( v29 );
                      v26 -= 1024;
                      --v27;
                    }
                    while ( v27 );
                  }
                  v30 = (v21 << 10) - (_DWORD)FindFileData.cFileName;
                  v31 = FindFileData.cFileName;
                  do
                  {
                    v32 = *v31;
                    byte_8A9540[v30 + (_DWORD)v31] = *v31;
                    ++v31;
                  }
                  while ( v32 );
                }
                dword_45B8E4 = v22 + 1;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1018:
        if ( !dword_45B8E4 )
          return 0;
        v8 = SendDlgItemMessageA(hDlg, 1017, CB_GETCURSEL, 0, 0);
        if ( v8 == -1 || v8 >= dword_45B8E4 )
          return 0;
        sprintf(LibFileName, "%s%s", v35, &byte_8A9540[1024 * v8]);
        v9 = LoadLibraryA(LibFileName);
        GPUinit_0 = GetProcAddress(v9, "GPUinit");
        GPUtest_0 = GetProcAddress(v9, "GPUtest");
        GPUshutdown_0 = GetProcAddress(v9, "GPUshutdown");
        GPUinit_0();
        v10 = GPUtest_0();
        if ( v10 )
        {
          if ( v10 == -1 )
            MessageBoxA(nullptr, "   Plugin NOT working, try configuring it.  ", "Testing GPU Plugin", 0x10u);
          else
            MessageBoxA(nullptr, "UNK value", "Testing GPU Plugin", 0x40u);
          GPUshutdown_0();
          result = 0;
        }
        else
        {
          MessageBoxA(nullptr, "   Plugin working correctly.  ", "Testing GPU Plugin", 0x40u);
          GPUshutdown_0();
          result = 0;
        }
        break;
      case 1019:
        if ( !dword_45B8E4 )
          return 0;
        v11 = SendDlgItemMessageA(hDlg, 1017, CB_GETCURSEL, 0, 0);
        if ( v11 == -1 || v11 >= dword_45B8E4 )
          return 0;
        sprintf(LibFileName, "%s%s", v35, &byte_8A9540[1024 * v11]);
        v12 = LoadLibraryA(LibFileName);
        GPUinit_0 = GetProcAddress(v12, "GPUinit");
        PSEconfigure = GetProcAddress(v12, "GPUconfigure");
        GPUshutdown_0 = GetProcAddress(v12, "GPUshutdown");
        GPUinit_0();
        PSEconfigure();
        GPUshutdown_0();
        result = 0;
        break;
      case 1020:
        if ( dword_45B8E4 )
        {
          v13 = SendDlgItemMessageA(hDlg, 1017, CB_GETCURSEL, 0, 0);
          if ( v13 != -1 && v13 < dword_45B8E4 )
          {
            sprintf(LibFileName, "%s%s", v35, &byte_8A9540[1024 * v13]);
            v14 = LoadLibraryA(LibFileName);
            GPUinit_0 = GetProcAddress(v14, "GPUinit");
            GPUabout_0 = GetProcAddress(v14, "GPUabout");
            GPUshutdown_0 = GetProcAddress(v14, "GPUshutdown");
            GPUinit_0();
            GPUabout_0();
            GPUshutdown_0();
          }
        }
        return 0;
      case 1021:
        if ( dword_45B8E4 )
        {
          v7 = SendDlgItemMessageA(hDlg, 1017, 0x147u, 0, 0);
          if ( v7 != -1 && v7 < dword_45B8E4 )
            sprintf((char *const)VideoPlugin, "%s", &byte_8A9540[1024 * v7]);
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        else
        {
          sprintf((char *const)VideoPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        break;
      case 1022:
        if ( dword_45B8E4 )
        {
          EndDialog(hDlg, 1);
        }
        else
        {
          sprintf((char *const)VideoPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
        }
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

INT_PTR __stdcall search_net_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  INT_PTR result; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  const char *v9; // eax
  HMODULE v10; // eax
  char v11; // al
  unsigned int v12; // eax
  const char *v13; // eax
  HMODULE v14; // eax
  unsigned int v15; // eax
  const char *v16; // eax
  HMODULE v17; // eax
  HWND v18; // ebx
  LRESULT (__stdcall *v19)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v20; // eax
  int v21; // eax
  HMODULE LibraryA; // eax
  HMODULE v23; // esi
  FARPROC PSEgetLibVersion_ptr; // eax
  unsigned __int8 v25; // al
  int v26; // eax
  const char *v27; // eax
  signed int v28; // ebp
  int v29; // ebx
  CHAR *cFileName; // eax
  char *v31; // edx
  CHAR v32; // cl
  char *v33; // esi
  int v34; // edi
  char *v35; // eax
  char v36; // cl
  int v37; // ebp
  CHAR *v38; // eax
  char v39; // cl
  int v40; // [esp-18h] [ebp-D68h]
  int v41; // [esp-14h] [ebp-D64h]
  char v42[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+550h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v42, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v42[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print("not net plugins found\n");
    dword_45B8E4 = 0;
    sprintf(lParam, "Disabled Netplay");
    v18 = hDlg;
    v19 = SendDlgItemMessageA;
    v20 = SendDlgItemMessageA(hDlg, 1104, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)NetPlugin, "DISABLED") )
      SendDlgItemMessageA(hDlg, 1104, 0x14Eu, v20, 0);
    v21 = dword_45B8E4;
    strcpy(&byte_8A9540[1024 * dword_45B8E4], "DISABLED");
    dword_45B8E4 = v21 + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", v42, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v23 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v23, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(v23, "PSEgetLibVersion");
        PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              v25 = PSEgetLibVersion_ptr();
              v26 = PSEgetLibVersion(v25);
              v27 = (const char *)PSEgetLibName(BYTE1(v26));
              sprintf(lParam, "%s %d.%d", v27, v40, v41);
              if ( PSEgetLibType() == 16 )
              {
                v28 = v19(v18, 1104, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)NetPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v18, 1104, CB_SETCURSEL, v28, 0);
                v29 = dword_45B8E4;
                if ( v28 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v31 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                  do
                  {
                    v32 = *cFileName;
                    cFileName[(_DWORD)v31] = *cFileName;
                    ++cFileName;
                  }
                  while ( v32 );
                }
                else
                {
                  if ( v28 < dword_45B8E4 )
                  {
                    v33 = &byte_8A9140[1024 * dword_45B8E4];
                    v34 = dword_45B8E4 - v28;
                    do
                    {
                      v35 = v33;
                      do
                      {
                        v36 = *v35;
                        v35[1024] = *v35;
                        ++v35;
                      }
                      while ( v36 );
                      v33 -= 1024;
                      --v34;
                    }
                    while ( v34 );
                  }
                  v37 = (v28 << 10) - (_DWORD)FindFileData.cFileName;
                  v38 = FindFileData.cFileName;
                  do
                  {
                    v39 = *v38;
                    byte_8A9540[v37 + (_DWORD)v38] = *v38;
                    ++v38;
                  }
                  while ( v39 );
                }
                dword_45B8E4 = v29 + 1;
                v18 = hDlg;
              }
            }
          }
        }
      }
      if ( !FindNextFileA(hFindFile, &FindFileData) )
        break;
      v19 = SendDlgItemMessageA;
    }
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1099:
        if ( !dword_45B8E4 )
          return 0;
        v8 = SendDlgItemMessageA(hDlg, 1104, CB_GETCURSEL, 0, 0);
        if ( v8 == -1 )
          return 0;
        if ( v8 >= dword_45B8E4 )
          return 0;
        v9 = &byte_8A9540[1024 * v8];
        if ( !strcmp(v9, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", v42, v9);
        v10 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v10, "NETtest");
        v11 = GPUtest_0();
        if ( v11 )
        {
          if ( v11 == -1 )
            MessageBoxA(nullptr, "   Plugin NOT working, try configuring it.  ", "Testing NET Plugin", 0x10u);
          else
            MessageBoxA(nullptr, "UNK value", "Testing NET Plugin", 0x40u);
          result = 0;
        }
        else
        {
          MessageBoxA(nullptr, "   Plugin working correctly.  ", "Testing NET Plugin", 0x40u);
          result = 0;
        }
        break;
      case 1100:
        if ( !dword_45B8E4 )
          return 0;
        v12 = SendDlgItemMessageA(hDlg, 1104, CB_GETCURSEL, 0, 0);
        if ( v12 == -1 )
          return 0;
        if ( v12 >= dword_45B8E4 )
          return 0;
        v13 = &byte_8A9540[1024 * v12];
        if ( !strcmp(v13, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", v42, v13);
        v14 = LoadLibraryA(LibFileName);
        PSEconfigure = GetProcAddress(v14, "NETconfigure");
        PSEconfigure();
        result = 0;
        break;
      case 1101:
        if ( dword_45B8E4 )
        {
          v15 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
          if ( v15 != -1 && v15 < dword_45B8E4 )
          {
            v16 = &byte_8A9540[1024 * v15];
            if ( strcmp(v16, "DISABLED") )
            {
              sprintf(LibFileName, "%s%s", v42, v16);
              v17 = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(v17, "NETabout");
              GPUabout_0();
            }
          }
        }
        return 0;
      case 1102:
        if ( dword_45B8E4 )
        {
          v7 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
          if ( v7 != -1 && v7 < dword_45B8E4 )
            sprintf((char *const)NetPlugin, "%s", &byte_8A9540[1024 * v7]);
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        else
        {
          sprintf((char *const)NetPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        break;
      case 1103:
        if ( dword_45B8E4 )
        {
          EndDialog(hDlg, 1);
        }
        else
        {
          sprintf((char *const)NetPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
        }
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

INT_PTR __stdcall w9x_cdrom_settings(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  LRESULT v5; // eax
  LRESULT v6; // eax
  int v7; // ecx
  int v8; // edx
  signed int v9; // ebp
  char *v10; // esi
  char lParam[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( a2 == 272 )
  {
    W9x_load_winaspi_dll();
    W9x_init_aspi();
    W9x_free_winaspi_dll();
    v9 = 0;
    if ( HIBYTE(dword_4FD9BC) )
    {
      v10 = byte_504FE9;
      do
      {
        sprintf(
          lParam,
          "%d:%d:%d %08s  %016s  %04s",
          *(_DWORD *)(v10 + 43),
          *(_DWORD *)(v10 + 47),
          *(_DWORD *)(v10 + 51),
          v10 - 9,
          v10,
          v10 + 17);
        SendDlgItemMessageA(hDlg, 1081, CB_ADDSTRING, 0, (LPARAM)lParam);
        if ( *(_DWORD *)(v10 + 43) == cdrom_haid
          && *(_DWORD *)(v10 + 47) == cdrom_target
          && *(_DWORD *)(v10 + 51) == cdrom_lun )
        {
          SendDlgItemMessageA(hDlg, 1081, 0x14Eu, v9, 0);
        }
        ++v9;
        v10 += 64;
      }
      while ( v9 < HIBYTE(dword_4FD9BC) );
    }
    SendDlgItemMessageA(hDlg, 1136, BM_SETCHECK, (unsigned __int8)SubchannelW9xCdromEnabled, 0);
    SendDlgItemMessageA(hDlg, 1137, BM_SETCHECK, (unsigned __int8)SubchannelW9xCaching, 0);
    SendDlgItemMessageA(hDlg, 1138, BM_SETCHECK, (unsigned __int8)SubchannelW9xCachingLG, 0);
    return 1;
  }
  else
  {
    if ( a2 != 273 )
      return 0;
    if ( (unsigned __int16)a3 == 1079 )
    {
      v5 = SendDlgItemMessageA(hDlg, 1081, CB_GETCURSEL, 0, 0);
      if ( v5 != -1 && v5 < HIBYTE(dword_4FD9BC) )
      {
        v6 = v5 << 6;
        v7 = *(int *)((char *)&dword_505018 + v6);
        cdrom_haid = *(int *)((char *)&dword_505014 + v6);
        v8 = *(int *)((char *)dword_50501C + v6);
        cdrom_target = v7;
        cdrom_lun = v8;
      }
      SubchannelW9xCdromEnabled = SendDlgItemMessageA(hDlg, 1136, BM_GETCHECK, 0, 0);
      SubchannelW9xCaching = SendDlgItemMessageA(hDlg, 1137, BM_GETCHECK, 0, 0);
      SubchannelW9xCachingLG = SendDlgItemMessageA(hDlg, 1138, BM_GETCHECK, 0, 0);
      EndDialog(hDlg, 1);
      cfg_cdrom_set_hain_target_lun();
      return 1;
    }
    else
    {
      if ( (unsigned __int16)a3 != 1080 )
        return 0;
      EndDialog(hDlg, 1);
      return 1;
    }
  }
}

INT_PTR __stdcall w2k_cdrom_settings(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  LRESULT v5; // eax
  LRESULT v6; // eax
  int i; // ebx
  LRESULT v8; // eax
  CHAR lParam[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( a2 == 272 )
  {
    sprintf(lParam, "FirstCdrom");
    v6 = SendDlgItemMessageA(hDlg, 1133, CB_ADDSTRING, 0, (LPARAM)lParam);
    if ( !cdrom_letter )
      SendDlgItemMessageA(hDlg, 1133, CB_SETCURSEL, v6, 0);
    for ( i = 65; i <= 90; ++i )
    {
      sprintf(lParam, "%c:\\", i);
      if ( GetDriveTypeA(lParam) == 5 )
      {
        sprintf(lParam, "--%c:--", i);
        v8 = SendDlgItemMessageA(hDlg, 1133, CB_ADDSTRING, 0, (LPARAM)lParam);
        if ( i == cdrom_letter )
          SendDlgItemMessageA(hDlg, 1133, CB_SETCURSEL, v8, 0);
      }
    }
    SendDlgItemMessageA(hDlg, 1139, BM_SETCHECK, (unsigned __int8)SubchannelW2kCdromEnabled, 0);
    SendDlgItemMessageA(hDlg, 1140, BM_SETCHECK, (unsigned __int8)SubchannelW2kCaching, 0);
    SendDlgItemMessageA(hDlg, 1141, BM_SETCHECK, (unsigned __int8)SubchannelW2kCachingLG, 0);
    return 1;
  }
  else
  {
    if ( a2 != 273 )
      return 0;
    if ( (unsigned __int16)a3 == 1134 )
    {
      v5 = SendDlgItemMessageA(hDlg, 1133, CB_GETCURSEL, 0, 0);
      if ( v5 != -1 )
      {
        SendDlgItemMessageA(hDlg, 1133, CB_GETLBTEXT, v5, (LPARAM)lParam);
        if ( !strncmp(lParam, "FirstCdrom", 4u) )
          cdrom_letter = 0;
        else
          sscanf(lParam, "--%c:--", &cdrom_letter);
      }
      SubchannelW2kCdromEnabled = SendDlgItemMessageA(hDlg, 1139, BM_GETCHECK, 0, 0);
      SubchannelW2kCaching = SendDlgItemMessageA(hDlg, 1140, BM_GETCHECK, 0, 0);
      SubchannelW2kCachingLG = SendDlgItemMessageA(hDlg, 1141, BM_GETCHECK, 0, 0);
      EndDialog(hDlg, 1);
      cfg_cdrom_set_letter();
      return 1;
    }
    else
    {
      if ( (unsigned __int16)a3 != 1135 )
        return 0;
      EndDialog(hDlg, 1);
      return 1;
    }
  }
}

INT_PTR __stdcall search_cdrom_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  INT_PTR result; // eax
  unsigned int v8; // eax
  const char *v9; // eax
  HMODULE v10; // eax
  unsigned int v11; // eax
  const char *v12; // eax
  HMODULE v13; // esi
  unsigned int v14; // eax
  const char *v15; // eax
  HMODULE v16; // eax
  HWND v17; // ebx
  LRESULT (__stdcall *v18)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v19; // eax
  int v20; // eax
  LRESULT v21; // eax
  int v22; // eax
  HMODULE LibraryA; // eax
  HMODULE v24; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v26; // al
  int v27; // eax
  const char *v28; // eax
  signed int v29; // ebp
  int v30; // ebx
  CHAR *cFileName; // eax
  char *v32; // edx
  CHAR v33; // cl
  char *v34; // esi
  int v35; // edi
  char *v36; // eax
  char v37; // cl
  int v38; // ebp
  CHAR *v39; // eax
  char v40; // cl
  int v41; // [esp-18h] [ebp-DFCh]
  int v42; // [esp-14h] [ebp-DF8h]
  char v43[12]; // [esp+0h] [ebp-DE4h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-DD8h]
  struct _OSVERSIONINFOA VersionInformation; // [esp+10h] [ebp-DD4h] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+A4h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+1E4h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+5E4h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+9E4h] [ebp-400h] BYREF

  strcpy(v43, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v43[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    dword_45B8E4 = 0;
    sprintf(lParam, "ePSXe CDR ASPI core 1.5.2.");
    v17 = hDlg;
    v18 = SendDlgItemMessageA;
    v19 = SendDlgItemMessageA(hDlg, 1000, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
      SendDlgItemMessageA(hDlg, 1000, 0x14Eu, v19, 0);
    v20 = dword_45B8E4;
    strcpy(&byte_8A9540[1024 * dword_45B8E4], "W9XCDRCORE");
    dword_45B8E4 = v20 + 1;
    memset(&VersionInformation, 0, sizeof(VersionInformation));
    VersionInformation.dwOSVersionInfoSize = 148;
    GetVersionExA(&VersionInformation);
    if ( VersionInformation.dwPlatformId == 2 )
    {
      sprintf(lParam, "ePSXe CDR WNT/W2K core 1.5.2.");
      v21 = SendDlgItemMessageA(hDlg, 1000, 0x143u, 0, (LPARAM)lParam);
      if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
        SendDlgItemMessageA(hDlg, 1000, 0x14Eu, v21, 0);
      v22 = dword_45B8E4;
      strcpy(&byte_8A9540[1024 * dword_45B8E4], "W2KCDRCORE");
      dword_45B8E4 = v22 + 1;
    }
    do
    {
      sprintf(LibFileName, "%s%s", v43, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v24 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v24, "PSEgetLibName");
        PSEgetLibVersion = GetProcAddress(v24, "PSEgetLibVersion");
        ::PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v26 = PSEgetLibVersion();
              v27 = ::PSEgetLibVersion(v26);
              v28 = (const char *)PSEgetLibName(BYTE1(v27));
              sprintf(lParam, "%s %d.%d", v28, v41, v42);
              if ( PSEgetLibType() == 1 )
              {
                v29 = v18(v17, 1000, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v17, 1000, 0x14Eu, v29, 0);
                v30 = dword_45B8E4;
                if ( v29 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v32 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                  do
                  {
                    v33 = *cFileName;
                    cFileName[(_DWORD)v32] = *cFileName;
                    ++cFileName;
                  }
                  while ( v33 );
                }
                else
                {
                  if ( v29 < dword_45B8E4 )
                  {
                    v34 = &byte_8A9140[1024 * dword_45B8E4];
                    v35 = dword_45B8E4 - v29;
                    do
                    {
                      v36 = v34;
                      do
                      {
                        v37 = *v36;
                        v36[1024] = *v36;
                        ++v36;
                      }
                      while ( v37 );
                      v34 -= 1024;
                      --v35;
                    }
                    while ( v35 );
                  }
                  v38 = (v29 << 10) - (_DWORD)FindFileData.cFileName;
                  v39 = FindFileData.cFileName;
                  do
                  {
                    v40 = *v39;
                    byte_8A9540[v38 + (_DWORD)v39] = *v39;
                    ++v39;
                  }
                  while ( v40 );
                }
                v18 = SendDlgItemMessageA;
                dword_45B8E4 = v30 + 1;
                v17 = hDlg;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1001:
        v8 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v8 == -1 )
          return 0;
        if ( v8 >= dword_45B8E4 )
          return 0;
        v9 = &byte_8A9540[1024 * v8];
        if ( !strcmp(v9, "W9XCDRCORE") || !strcmp(v9, "W2KCDRCORE") )
          return 0;
        sprintf(LibFileName, "%s%s", v43, v9);
        v10 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v10, "CDRtest");
        GPUtest_0();
        result = 0;
        break;
      case 1003:
        v11 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v11 == -1 || v11 >= dword_45B8E4 )
          return 0;
        v12 = &byte_8A9540[1024 * v11];
        if ( !strcmp(v12, "W9XCDRCORE") )
        {
          DialogBoxParamA(g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
          result = 0;
        }
        else
        {
          if ( !strcmp(v12, "W2KCDRCORE") )
          {
            DialogBoxParamA(g_hInstance, "IDD_CDROMCORE2K", hDlg, w2k_cdrom_settings, 0);
          }
          else
          {
            sprintf(LibFileName, "%s%s", v43, v12);
            v13 = LoadLibraryA(LibFileName);
            GPUinit_0 = GetProcAddress(v13, "CDRinit");
            GPUinit_0();
            PSEconfigure = GetProcAddress(v13, "CDRconfigure");
            PSEconfigure();
          }
          result = 0;
        }
        break;
      case 1004:
        v14 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v14 != -1 && v14 < dword_45B8E4 )
        {
          v15 = &byte_8A9540[1024 * v14];
          if ( strcmp(v15, "W9XCDRCORE") )
          {
            if ( strcmp(v15, "W2KCDRCORE") )
            {
              sprintf(LibFileName, "%s%s", v43, v15);
              v16 = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(v16, "CDRabout");
              GPUabout_0();
            }
          }
        }
        return 0;
      case 1023:
        v6 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v6 != -1 && v6 < dword_45B8E4 )
          sprintf((char *const)CdromPlugin, "%s", &byte_8A9540[1024 * v6]);
        EndDialog(hDlg, 1);
        cfg_save_settings();
        result = 1;
        break;
      case 1024:
        EndDialog(hDlg, 1);
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

INT_PTR __stdcall spucore_configure_dialog_callback(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  if ( a2 != 272 )
  {
    if ( a2 != 273 || (_WORD)a3 != 1105 )
      return 0;
    EndDialog(hDlg, 1);
  }
  return 1;
}

INT_PTR __stdcall search_spu_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  INT_PTR result; // eax
  unsigned int v8; // eax
  const char *v9; // eax
  HMODULE v10; // eax
  unsigned int v11; // eax
  const char *v12; // eax
  HMODULE v13; // eax
  unsigned int v14; // eax
  const char *v15; // eax
  HMODULE v16; // eax
  HWND v17; // ebx
  LRESULT (__stdcall *v18)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v19; // eax
  int v20; // eax
  int v21; // ecx
  HMODULE LibraryA; // eax
  HMODULE v23; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v25; // al
  int v26; // eax
  const char *v27; // eax
  signed int v28; // ebp
  int v29; // ebx
  CHAR *cFileName; // eax
  char *v31; // edx
  CHAR v32; // cl
  char *v33; // esi
  int v34; // edi
  char *v35; // eax
  char v36; // cl
  int v37; // ebp
  CHAR *v38; // eax
  char v39; // cl
  int v40; // [esp-18h] [ebp-D68h]
  int v41; // [esp-14h] [ebp-D64h]
  char v42[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+550h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v42, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v42[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    dword_45B8E4 = 0;
    sprintf(lParam, "ePSXe SPU core 1.5.2.");
    v17 = hDlg;
    v18 = SendDlgItemMessageA;
    v19 = SendDlgItemMessageA(hDlg, 1010, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)SoundPlugin, "SPUCORE") )
      SendDlgItemMessageA(hDlg, 1010, 0x14Eu, v19, 0);
    v20 = dword_45B8E4;
    v21 = dword_45B8E4 << 10;
    *(_DWORD *)&byte_8A9540[v21] = *(_DWORD *)"SPUCORE";
    strcpy(&byte_8A9544[v21], "ORE");
    dword_45B8E4 = v20 + 1;
    do
    {
      sprintf(LibFileName, "%s%s", v42, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v23 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v23, "PSEgetLibName");
        PSEgetLibVersion = GetProcAddress(v23, "PSEgetLibVersion");
        ::PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v25 = PSEgetLibVersion();
              v26 = ::PSEgetLibVersion(v25);
              v27 = (const char *)PSEgetLibName(BYTE1(v26));
              sprintf(lParam, "%s %d.%d", v27, v40, v41);
              if ( PSEgetLibType() == 4 )
              {
                v28 = v18(v17, 1010, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)SoundPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v17, 1010, 0x14Eu, v28, 0);
                v29 = dword_45B8E4;
                if ( v28 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v31 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                  do
                  {
                    v32 = *cFileName;
                    cFileName[(_DWORD)v31] = *cFileName;
                    ++cFileName;
                  }
                  while ( v32 );
                }
                else
                {
                  if ( v28 < dword_45B8E4 )
                  {
                    v33 = &byte_8A9140[1024 * dword_45B8E4];
                    v34 = dword_45B8E4 - v28;
                    do
                    {
                      v35 = v33;
                      do
                      {
                        v36 = *v35;
                        v35[1024] = *v35;
                        ++v35;
                      }
                      while ( v36 );
                      v33 -= 1024;
                      --v34;
                    }
                    while ( v34 );
                  }
                  v37 = (v28 << 10) - (_DWORD)FindFileData.cFileName;
                  v38 = FindFileData.cFileName;
                  do
                  {
                    v39 = *v38;
                    byte_8A9540[v37 + (_DWORD)v38] = *v38;
                    ++v38;
                  }
                  while ( v39 );
                }
                v18 = SendDlgItemMessageA;
                dword_45B8E4 = v29 + 1;
                v17 = hDlg;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    v18(v17, 1005, 0xF1u, (unsigned __int8)sound_enabled, 0);
    v18(v17, 1006, 0xF1u, (unsigned __int8)sound_use_xa, 0);
    v18(v17, 1009, 0xF1u, (unsigned __int8)sound_use_cdda, 0);
    v18(v17, 1030, 0xF1u, (unsigned __int8)forcespu, 0);
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1011:
        v8 = SendDlgItemMessageA(hDlg, 1010, 0x147u, 0, 0);
        if ( v8 == -1 )
          return 0;
        if ( v8 >= dword_45B8E4 )
          return 0;
        v9 = &byte_8A9540[1024 * v8];
        if ( !strcmp(v9, "SPUCORE") )
          return 0;
        sprintf(LibFileName, "%s%s", v42, v9);
        v10 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v10, "SPUtest");
        GPUtest_0();
        result = 0;
        break;
      case 1012:
        v11 = SendDlgItemMessageA(hDlg, 1010, 0x147u, 0, 0);
        if ( v11 == -1 || v11 >= dword_45B8E4 )
          return 0;
        v12 = &byte_8A9540[1024 * v11];
        if ( !strcmp(v12, "SPUCORE") )
        {
          DialogBoxParamA(g_hInstance, "IDD_SOUND9X", hDlg, spucore_configure_dialog_callback, 0);
        }
        else
        {
          sprintf(LibFileName, "%s%s", v42, v12);
          v13 = LoadLibraryA(LibFileName);
          PSEconfigure = GetProcAddress(v13, "SPUconfigure");
          PSEconfigure();
        }
        result = 0;
        break;
      case 1013:
        v14 = SendDlgItemMessageA(hDlg, 1010, CB_GETCURSEL, 0, 0);
        if ( v14 != -1 && v14 < dword_45B8E4 )
        {
          v15 = &byte_8A9540[1024 * v14];
          if ( strcmp(v15, "SPUCORE") )
          {
            sprintf(LibFileName, "%s%s", v42, v15);
            v16 = LoadLibraryA(LibFileName);
            GPUabout_0 = GetProcAddress(v16, "SPUabout");
            GPUabout_0();
          }
        }
        return 0;
      case 1014:
        v6 = SendDlgItemMessageA(hDlg, 1010, CB_GETCURSEL, 0, 0);
        if ( v6 != -1 && v6 < dword_45B8E4 )
          sprintf((char *const)SoundPlugin, "%s", &byte_8A9540[1024 * v6]);
        sound_enabled = SendDlgItemMessageA(hDlg, 1005, 0xF0u, 0, 0);
        sound_use_xa = SendDlgItemMessageA(hDlg, 1006, 0xF0u, 0, 0);
        sound_use_cdda = SendDlgItemMessageA(hDlg, 1009, 0xF0u, 0, 0);
        forcespu = SendDlgItemMessageA(hDlg, 1030, 0xF0u, 0, 0);
        EndDialog(hDlg, 1);
        cfg_save_settings();
        result = 1;
        break;
      case 1015:
        EndDialog(hDlg, 1);
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

INT_PTR __stdcall memcard_settings(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  INT_PTR result; // eax

  if ( a2 == 272 )
  {
    SetDlgItemTextA(hDlg, 1082, (LPCSTR)Memcard1);
    SetDlgItemTextA(hDlg, 1026, (LPCSTR)Memcard2);
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1026:
      case 1082:
        return 1;
      case 1030:
        if ( !open_file_dialog(
                "Select Memcard FILE 2",
                "MEMCARD FILE (*.MCR, *.MEM, *.MCD, *.GME)",
                temp_path,
                "memcards\\",
                "MCR") )
          return 1;
        SetDlgItemTextA(hDlg, 1026, temp_path);
        result = 1;
        break;
      case 1083:
        if ( !open_file_dialog(
                "Select Memcard FILE 1",
                "MEMCARD FILE (*.MCR, *.MEM, *.MCD, *.GME)",
                temp_path,
                "memcards\\",
                "MCR") )
          return 1;
        SetDlgItemTextA(hDlg, 1082, temp_path);
        result = 1;
        break;
      case 1084:
        GetDlgItemTextA(hDlg, 1082, (LPSTR)Memcard1, 1024);
        GetDlgItemTextA(hDlg, 1026, (LPSTR)Memcard2, 1024);
        if ( sio_memcard_loaded )
        {
          sio_memcard_loaded = 0;
          sio_memcard_load();
        }
        EndDialog(hDlg, 1);
        cfg_save_settings();
        result = 1;
        break;
      case 1085:
        EndDialog(hDlg, 1);
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}

int __cdecl calc_bios_checksum(uint8_t *ptr, int size)
{
  unsigned __int16 v2; // si
  int v3; // ebp
  uint8_t *v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // ecx

  v2 = 0;
  v3 = 0;
  if ( size > 0 )
  {
    v4 = ptr + 1;
    do
    {
      v5 = *(v4 - 1);
      v6 = *v4;
      v4 += 2;
      v7 = v6 + (v5 << 8);
      v3 += v7;
      v2 ^= v7;
    }
    while ( (int)&v4[-1 - (_DWORD)ptr] < size );
  }
  return v2 ^ (v3 << 16);
}

