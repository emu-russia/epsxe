#include "pch.h"

BOOL open_file_dialog(const CHAR *title, const CHAR *filter, CHAR *file_path, const CHAR *initial_dir, const CHAR *def_ext)
{
  BOOL opened;
  int index;
  CHAR ch;
  OPENFILENAMEA ofn;
  uint8_t file_title[1024];

  memset(&ofn.pvReserved, 0, 0x400u);
  memset(file_title, 0, sizeof(file_title));
  ofn.lpstrFile = (LPSTR)&ofn.pvReserved;
  ofn.hwndOwner = g_hWnd;
  ofn.lpstrFilter = filter;
  ofn.lpstrFileTitle = file_title;
  ofn.nMaxFile = 1024;
  ofn.lpstrInitialDir = initial_dir;
  ofn.nMaxFileTitle = 1024;
  ofn.lStructSize = 76;
  ofn.lpstrCustomFilter = nullptr;
  ofn.nMaxCustFilter = 0;
  ofn.nFilterIndex = 1;
  ofn.lpstrTitle = title;
  ofn.lpstrDefExt = def_ext;
  ofn.Flags = 12;
  opened = GetOpenFileNameA(&ofn);
  if ( opened )
  {
    index = 0;
    do
    {
      ch = *((uint8_t *)&ofn.pvReserved + index);
      temp_path[index++] = ch;
    }
    while ( ch );
    return 1;
  }
  return opened;
}

static BOOL controller_set_joypad(HWND hDlg, uint16_t button)
{
  int index;
  int *id_ptr;
  int map_index;
  int button_index;
  int count;
  CHAR String[1024];

  index = 0;
  id_ptr = &nIDDlgItem;
  count = 4;
  do
  {
    map_index = index + 4 * (uint8_t)pad_number_menu_selection;
    if ( *((uint16_t *)joypad_button_map + map_index) >= 0x20u )
    {
      sprintf(String, "%d", *((uint16_t *)joypad_button_map + map_index));
      SetDlgItemTextA(hDlg, *(uint16_t *)id_ptr, String);
    }
    else
    {
      SetDlgItemTextA(hDlg, *(uint16_t *)id_ptr, &joy_names[14 * *((uint16_t *)joypad_button_map + map_index)]);
    }
    ++index;
    id_ptr = (int *)((char *)id_ptr + 2);
    --count;
  }
  while ( count );
  button_index = button + 4 * (uint8_t)pad_number_menu_selection;
  if ( *((uint16_t *)joypad_button_map + button_index) < 0x20u )
    return SetDlgItemTextA(
             hDlg,
             *((uint16_t *)&nIDDlgItem + button),
             &joy_names[14 * *((uint16_t *)joypad_button_map + button_index)]);
  sprintf(String, "%d", *((uint16_t *)joypad_button_map + button_index));
  return SetDlgItemTextA(hDlg, *((uint16_t *)&nIDDlgItem + button), String);
}

static int controller_set_keyboard(HWND hDlg, uint16_t button)
{
  int index;
  int *id_ptr;
  KBD_NAME *name;
  int status;
  int key_index;
  int count;
  CHAR String[1024];

  index = 0;
  id_ptr = &controller_button_dlg_ids;
  count = 16;
  do
  {
    if ( (uint16_t)pad_key_assignments[16 * (uint8_t)pad_number_menu_selection + index] >= 0x200u )
    {
      sprintf(String, "%d", (uint16_t)pad_key_assignments[16 * (uint8_t)pad_number_menu_selection + index]);
      name = (KBD_NAME *)String;
    }
    else
    {
      name = &((KBD_NAME *)stru_44C148)[(uint16_t)pad_key_assignments[16 * (uint8_t)pad_number_menu_selection + index]];
    }
    SetDlgItemTextA(hDlg, *(uint16_t *)id_ptr, name->text);
    ++index;
    id_ptr = (int *)((char *)id_ptr + 2);
    status = --count;
  }
  while ( count );
  if ( button < 0xFFu )
  {
    key_index = button + 16 * (uint8_t)pad_number_menu_selection;
    if ( (uint16_t)pad_key_assignments[key_index] >= 0x200u )
    {
      sprintf(String, "%d", (uint16_t)pad_key_assignments[key_index]);
      return SetDlgItemTextA(hDlg, *((uint16_t *)&controller_button_dlg_ids + button), String);
    }
    else
    {
      return SetDlgItemTextA(
               hDlg,
               *((uint16_t *)&controller_button_dlg_ids + button),
               ((KBD_NAME *)stru_44C148)[(uint16_t)pad_key_assignments[key_index]].text);
    }
  }
  return status;
}

INT_PTR __stdcall controller_setup_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  INT_PTR status;
  int type;
  int type_idx;
  int small_motor;
  int small_motor_idx;
  int big_motor;
  int big_motor_idx;
  int motor_type;
  int motor_idx;
  int joypad_buttons;
  int mdec_flag;
  uint8_t edit_button;
  uint16_t i;
  uint16_t scan;
  uint16_t scan2;
  int16_t axis;
  int16_t index;
  int16_t *state_ptr;
  uint16_t type_sel;
  int type_value;
  uint16_t device_sel;
  uint16_t small_motor_sel;
  uint16_t big_motor_sel;
  int pad;
  int saved_mdec_flag;
  HWND dlg;
  int16_t key;
  int offset;
  uint16_t max_value;
  int sel0;
  int sel1;
  int sel2;
  int sel3;
  int sel4;
  int sel5;
  int sel6;
  int axis_button;
  CHAR String[1024];

  if ( uMsg <= 0x110 )
  {
    if ( uMsg != 272 )
    {
      if ( uMsg == 6 )
      {
        diAcquireAllDevices();
        return 0;
      }
      if ( uMsg == 8 )
      {
        diUnacquireAllDevices();
        return 0;
      }
      return 0;
    }
    if ( multitap_1 )
    {
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Disabled");
      type = *(uint32_t *)&Keys4[2 * (uint8_t)pad_number_menu_selection + 14];
      if ( type )
      {
        type_idx = type - 1;
        if ( type_idx )
        {
          if ( type_idx == 3 )
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 1u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 2u, 0);
      }
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"Burutter");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy1");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy2");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy3");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy4");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"None");
      switch ( GamepadAxis[(uint8_t)pad_number_menu_selection + 7] )
      {
        case 0:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 5u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 1u, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 2u, 0);
          break;
        case 3:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 3u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 4u, 0);
          break;
        case 5:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 0, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Sine");
      small_motor = g_PlayerDeviceMap4[(uint8_t)pad_number_menu_selection];
      if ( small_motor )
      {
        small_motor_idx = small_motor - 1;
        if ( small_motor_idx )
        {
          if ( small_motor_idx == 1 )
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 2u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 1u, 0);
      }
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Sine");
      big_motor = pad4_small_motor_type[(uint8_t)pad_number_menu_selection];
      if ( big_motor )
      {
        big_motor_idx = big_motor - 1;
        if ( big_motor_idx )
        {
          if ( big_motor_idx == 1 )
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_SETCURSEL, 2u, 0);
        }
        else
        {
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_SETCURSEL, 0, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_SETCURSEL, 1u, 0);
      }
    }
    if ( pad_number_menu_selection == 1 )
    {
      if ( !multitap_1 )
      {
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog Mouse T0 (F5)");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog Mouse T1 (F5)");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Gun    (F5)");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Mouse  (F5)");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Disabled");
        switch ( controller_port_modes[0] )
        {
          case 0:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 6u, 0);
            break;
          case 1:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 0, 0);
            break;
          case 2:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 5u, 0);
            break;
          case 3:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 4u, 0);
            break;
          case 4:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 1u, 0);
            break;
          case 5:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 2u, 0);
            break;
          case 6:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 3u, 0);
            break;
          default:
            break;
        }
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"Burutter");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy1");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy2");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy3");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy4");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"None");
        switch ( g_PlayerDeviceMap1[0] )
        {
          case 0:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 5u, 0);
            break;
          case 1:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 1u, 0);
            break;
          case 2:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 2u, 0);
            break;
          case 3:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 3u, 0);
            break;
          case 4:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 4u, 0);
            break;
          case 5:
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 0, 0);
            break;
          default:
            break;
        }
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Constant");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"None");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Sine");
        if ( g_EffectType2[0] )
        {
          if ( g_EffectType2[0] == 1 )
          {
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 0, 0);
          }
          else if ( g_EffectType2[0] == 2 )
          {
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 2u, 0);
          }
        }
        else
        {
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 1u, 0);
        }
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Constant");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"None");
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Sine");
        motor_type = g_EffectType1[0];
LABEL_78:
        if ( motor_type )
        {
          motor_idx = motor_type - 1;
          if ( motor_idx )
          {
            if ( motor_idx == 1 )
              SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_SETCURSEL, 2u, 0);
          }
          else
          {
            SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_SETCURSEL, 0, 0);
          }
        }
        else
        {
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_SETCURSEL, 1u, 0);
        }
      }
    }
    else if ( pad_number_menu_selection == 2 && !multitap_1 )
    {
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital Only");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Analog (F5)");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Digital/Mouse  (F5)");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_ADDSTRING, 0, (LPARAM)"Disabled");
      switch ( controller_port_modes[1] )
      {
        case 0:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 3u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 0, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 2u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, CB_SETCURSEL, 1u, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"Burutter");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy1");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy2");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy3");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"DX Joy4");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_ADDSTRING, 0, (LPARAM)"None");
      switch ( g_PlayerDeviceMap2 )
      {
        case 0:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 5u, 0);
          break;
        case 1:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 1u, 0);
          break;
        case 2:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 2u, 0);
          break;
        case 3:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 3u, 0);
          break;
        case 4:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 4u, 0);
          break;
        case 5:
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, CB_SETCURSEL, 0, 0);
          break;
        default:
          break;
      }
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Sine");
      if ( pad2_small_motor_type )
      {
        if ( pad2_small_motor_type == 1 )
        {
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 0, 0);
        }
        else if ( pad2_small_motor_type == 2 )
        {
          SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 2u, 0);
        }
      }
      else
      {
        SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, CB_SETCURSEL, 1u, 0);
      }
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Constant");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"None");
      SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, CB_ADDSTRING, 0, (LPARAM)"Sine");
      motor_type = pad2_big_motor_type;
      goto LABEL_78;
    }
    edit_button_id = -1;
    joypad_buttons = joypad_button_map[2 * (uint8_t)pad_number_menu_selection];
    mdec_flag = mdec_disable_flag[2 * (uint8_t)pad_number_menu_selection];
    qmemcpy(pad_keymap_dialog_copy, &pad_key_assignments[16 * (uint8_t)pad_number_menu_selection], sizeof(pad_keymap_dialog_copy));
    saved_pad_joypad_buttons = joypad_buttons;
    saved_pad_mdec_disable_flag = mdec_flag;
    controller_set_keyboard(hDlg, 0xFFu);
    controller_set_joypad(hDlg, (uint8_t)edit_button_id);
    sprintf(String, "PAD NUMBER %d", (uint8_t)pad_number_menu_selection);
    SetDlgItemTextA(hDlg, IDC_CONTROLLER_PAD_NUMBER, String);
    SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: NONE");
    SetTimer(hDlg, 0, 0x21u, nullptr);
    hDlgInput = (int)hDlg;
    hInst_For_DInput = (int)g_hInstance;
    if ( diInitDirectInput() == 1 )
      dbg_print_no_flush(" * Direct input init ok. \n");
    diUpdateJoystickStates();
    return 1;
  }
  if ( uMsg == 273 )
  {
    switch ( (int16_t)wParam )
    {
      case IDC_CONTROLLER_DEFAULT:
        edit_button_id = -1;
        cont_set_default(pad_number_menu_selection);
        dlg = hDlg;
        controller_set_keyboard(hDlg, (uint8_t)edit_button_id);
        goto LABEL_203;
      case IDC_CONTROLLER_L2:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: L2");
        edit_button_id = 9;
        return 0;
      case IDC_CONTROLLER_L1:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: L1");
        edit_button_id = 8;
        return 0;
      case IDC_CONTROLLER_UP:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: UP");
        edit_button_id = 2;
        return 0;
      case IDC_CONTROLLER_LEFT:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: LEFT");
        edit_button_id = 0;
        return 0;
      case IDC_CONTROLLER_DOWN:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: DOWN");
        edit_button_id = 3;
        return 0;
      case IDC_CONTROLLER_RIGHT:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: RIGHT");
        edit_button_id = 1;
        return 0;
      case IDC_CONTROLLER_SELECT:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: SELECT");
        edit_button_id = 13;
        return 0;
      case IDC_CONTROLLER_START:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: START");
        edit_button_id = 12;
        return 0;
      case IDC_CONTROLLER_R2:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: R2");
        edit_button_id = 11;
        return 0;
      case IDC_CONTROLLER_R1:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: R1");
        edit_button_id = 10;
        return 0;
      case IDC_CONTROLLER_TRIANGLE:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: TRIANGLE");
        edit_button_id = 4;
        return 0;
      case IDC_CONTROLLER_CIRCLE:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: CIRCLE");
        edit_button_id = 5;
        return 0;
      case IDC_CONTROLLER_CROSS:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: X");
        edit_button_id = 6;
        return 0;
      case IDC_CONTROLLER_SQUARE:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: SQUARE");
        edit_button_id = 7;
        return 0;
      case IDC_CONTROLLER_L3:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: L3");
        edit_button_id = 14;
        return 0;
      case IDC_CONTROLLER_CANCEL:
        pad = (uint8_t)pad_number_menu_selection;
        saved_mdec_flag = saved_pad_mdec_disable_flag;
        qmemcpy(&pad_key_assignments[16 * (uint8_t)pad_number_menu_selection], pad_keymap_dialog_copy, 0x20u);
        joypad_button_map[2 * pad] = saved_pad_joypad_buttons;
        mdec_disable_flag[2 * pad] = saved_mdec_flag;
        KillTimer(hDlg, 0);
        EndDialog(hDlg, 1);
        diShutdownDirectInput();
        return 1;
      case IDC_CONTROLLER_OK:
        type_sel = SendDlgItemMessageA(hDlg, IDC_CONTROLLER_TYPE, 0x147u, 0, 0);
        if ( type_sel != -1 )
        {
          if ( type_sel >= 6u || pad_number_menu_selection != 1 || multitap_1 )
          {
            if ( type_sel >= 4u || pad_number_menu_selection != 2 || multitap_1 )
            {
              if ( type_sel < 3u && multitap_1 )
              {
                sel0 = 1;
                sel1 = 4;
                sel2 = 0;
                type_value = *(&sel0 + type_sel);
                point_device_enabled = 0;
                *(uint32_t *)&Keys4[2 * (uint8_t)pad_number_menu_selection + 14] = type_value;
              }
            }
            else
            {
              sel0 = 1;
              sel1 = 4;
              sel2 = 2;
              sel3 = 0;
              controller_port_modes[1] = *(&sel0 + type_sel);
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
            sel0 = 1;
            sel1 = 4;
            sel2 = 5;
            sel3 = 6;
            sel4 = 3;
            sel5 = 2;
            sel6 = 0;
            controller_port_modes[0] = *(&sel0 + type_sel);
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
        device_sel = SendDlgItemMessageA(hDlg, IDC_CONTROLLER_DEVICE, 0x147u, 0, 0);
        if ( device_sel != -1 && device_sel < 6u )
        {
          switch ( device_sel )
          {
            case 0u:
              GamepadAxis[(uint8_t)pad_number_menu_selection + 7] = 5;
              break;
            case 1u:
              GamepadAxis[(uint8_t)pad_number_menu_selection + 7] = 1;
              break;
            case 2u:
              GamepadAxis[(uint8_t)pad_number_menu_selection + 7] = 2;
              break;
            case 3u:
              GamepadAxis[(uint8_t)pad_number_menu_selection + 7] = 3;
              break;
            case 4u:
              GamepadAxis[(uint8_t)pad_number_menu_selection + 7] = 4;
              break;
            case 5u:
              GamepadAxis[(uint8_t)pad_number_menu_selection + 7] = 0;
              break;
          }
        }
        small_motor_sel = SendDlgItemMessageA(hDlg, IDC_CONTROLLER_SMALL_MOTOR, 0x147u, 0, 0);
        if ( small_motor_sel != -1 && small_motor_sel < 3u )
        {
          if ( small_motor_sel )
          {
            if ( small_motor_sel == 1 )
            {
              g_PlayerDeviceMap4[(uint8_t)pad_number_menu_selection] = 0;
            }
            else if ( small_motor_sel == 2 )
            {
              g_PlayerDeviceMap4[(uint8_t)pad_number_menu_selection] = 2;
            }
          }
          else
          {
            g_PlayerDeviceMap4[(uint8_t)pad_number_menu_selection] = 1;
          }
        }
        big_motor_sel = SendDlgItemMessageA(hDlg, IDC_CONTROLLER_BIG_MOTOR, 0x147u, 0, 0);
        if ( big_motor_sel != -1 && big_motor_sel < 3u )
        {
          if ( big_motor_sel )
          {
            if ( big_motor_sel == 1 )
            {
              pad4_small_motor_type[(uint8_t)pad_number_menu_selection] = 0;
            }
            else if ( big_motor_sel == 2 )
            {
              pad4_small_motor_type[(uint8_t)pad_number_menu_selection] = 2;
            }
          }
          else
          {
            pad4_small_motor_type[(uint8_t)pad_number_menu_selection] = 1;
          }
        }
        cfg_save_settings();
        KillTimer(hDlg, 0);
        EndDialog(hDlg, 1);
        diShutdownDirectInput();
        return 1;
      case IDC_CONTROLLER_PAD_NUMBER:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: NONE");
        edit_button_id = -1;
        return 0;
      case IDC_CONTROLLER_R3:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: R3");
        edit_button_id = 15;
        return 0;
      case IDC_CONTROLLER_AXIS_Y1:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT AXIS: Y1");
        edit_button_id = 17;
        return 0;
      case IDC_CONTROLLER_AXIS_X1:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT AXIS: X1");
        edit_button_id = 16;
        return 0;
      case IDC_CONTROLLER_AXIS_X2:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT AXIS: X2");
        edit_button_id = 18;
        return 0;
      case IDC_CONTROLLER_AXIS_Y2:
        SetDlgItemTextA(hDlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT AXIS: Y2");
        edit_button_id = 19;
        return 0;
      case IDC_CONTROLLER_CLEAR:
        edit_button_id = -1;
        cont_reset_pad_state(pad_number_menu_selection);
        dlg = hDlg;
        controller_set_keyboard(hDlg, (uint8_t)edit_button_id);
        controller_set_joypad(hDlg, (uint8_t)edit_button_id);
LABEL_203:
        SetDlgItemTextA(dlg, IDC_CONTROLLER_EDIT_BUTTON, "EDIT BUTTON: NONE");
        status = 0;
        break;
      default:
        return 0;
    }
    return status;
  }
  if ( uMsg != 275 )
    return 0;
  edit_button = edit_button_id;
  LOBYTE(axis_button) = edit_button_id;
  if ( (uint8_t)edit_button_id >= 0x10u )
  {
    if ( (uint8_t)edit_button_id >= 0x14u )
      return 1;
    axis = 0;
    max_value = 0;
    diUpdateDeviceStates();
    index = 0;
    offset = 0;
    state_ptr = g_KeyboardState;
    do
    {
      if ( offset % 8 && *state_ptr )
      {
        if ( *state_ptr < 0 )
          *state_ptr = -*state_ptr;
        if ( *state_ptr > (int)max_value )
        {
          max_value = *state_ptr;
          axis = index;
        }
      }
      ++index;
      ++state_ptr;
      ++offset;
    }
    while ( (uint16_t)index < 0x20u );
    if ( !axis )
      return 1;
    cont_map_axis_state((uint8_t)axis_button + 4 * (uint8_t)pad_number_menu_selection - 20, axis);
    controller_set_joypad(hDlg, edit_button - 16);
    edit_button_id = edit_button;
    return 1;
  }
  memset(g_KeyboardStatePrev, 0, 0x200u);
  diUpdateDeviceStates();
  for ( i = 0; i < 0x100u; ++i )
  {
    if ( g_KeyboardStatePrev[i] && edit_button != 0xFF )
    {
      key = i;
      goto LABEL_138;
    }
  }
  scan = 272;
  while ( 1 )
  {
    if ( g_KeyboardStatePrev[scan] && edit_button != 0xFF )
      goto LABEL_107;
    if ( extended_key_states_1[scan] && edit_button != 0xFF )
    {
      scan += 32;
LABEL_107:
      cont_map_button_state(edit_button + 16 * ((uint8_t)pad_number_menu_selection - 1), scan);
      controller_set_keyboard(hDlg, edit_button);
      return 1;
    }
    if ( extended_key_states_2[scan] && edit_button != 0xFF )
      break;
    if ( extended_key_states_3[scan] && edit_button != 0xFF )
    {
      scan += 96;
      goto LABEL_107;
    }
    if ( ++scan >= 0x120u )
    {
      scan = 256;
      while ( !g_KeyboardStatePrev[scan] || edit_button == 0xFF )
      {
        if ( extended_key_states_1[scan] && edit_button != 0xFF )
        {
          scan2 = scan + 32;
          goto LABEL_137;
        }
        if ( extended_key_states_2[scan] && edit_button != 0xFF )
        {
          scan += 64;
          goto LABEL_107;
        }
        if ( extended_key_states_3[scan] && edit_button != 0xFF )
        {
          scan += 96;
          goto LABEL_107;
        }
        if ( ++scan >= 0x110u )
        {
          scan2 = 384;
          while ( !g_KeyboardStatePrev[scan2] || edit_button == 0xFF )
          {
            if ( extended_key_states_1[scan2] && edit_button != 0xFF )
            {
              cont_map_button_state(edit_button + 16 * ((uint8_t)pad_number_menu_selection - 1), scan2 + 32);
              controller_set_keyboard(hDlg, edit_button);
              return 1;
            }
            if ( extended_key_states_2[scan2] && edit_button != 0xFF )
            {
              cont_map_button_state(edit_button + 16 * ((uint8_t)pad_number_menu_selection - 1), scan2 + 64);
              controller_set_keyboard(hDlg, edit_button);
              return 1;
            }
            if ( extended_key_states_3[scan2] && edit_button != 0xFF )
            {
              scan2 += 96;
              goto LABEL_137;
            }
            if ( ++scan2 >= 0x184u )
              return 1;
          }
          goto LABEL_137;
        }
      }
      goto LABEL_107;
    }
  }
  scan2 = scan + 64;
LABEL_137:
  key = scan2;
LABEL_138:
  cont_map_button_state(edit_button + 16 * ((uint8_t)pad_number_menu_selection - 1), key);
  controller_set_keyboard(hDlg, edit_button);
  return 1;
}

LRESULT __stdcall cheat_dialog_callback(HWND hDlg, int uMsg, int16_t wParam, int lParam)
{
  LRESULT count;
  LRESULT next;
  LRESULT status;
  LRESULT sel;
  LRESULT remaining;
  FILE *in_file;
  FILE *out_file;
  LRESULT save_count;
  LRESULT save_next;
  unsigned int i;
  int value;
  int address;
  char item_text[1024];
  CHAR String[1024];
  CHAR Buffer[1024];

  if ( uMsg == 272 )
  {
    for ( i = 0; i < (uint8_t)active_mini_cheat_count; ++i )
    {
      sprintf(item_text, "  %06x    %08x", mini_cheat_id_array[2 * i], mini_cheat_attr_array[2 * i]);
      SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x180u, 0, (LPARAM)item_text);
    }
    return 1;
  }
  else if ( uMsg == 273 )
  {
    switch ( wParam )
    {
      case IDC_CHEAT_LOAD:
        if ( !open_file_dialog("Open PSX CHEAT", "PSX CHEATs (*.CHT)", temp_path, "cheats\\", "CHT") )
          return 0;
        in_file = fopen(temp_path, "r");
        while ( !feof(in_file) )
        {
          sprintf(item_text, asc_44E24C);
          fgets(item_text, 1024, in_file);
          if ( item_text[0] != 35 && sscanf(item_text, "%x %x", &address, &value) == 2 )
          {
            sprintf(item_text, "  %06x    %08x", address & 0x1FFFFF, value);
            SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x180u, 0, (LPARAM)item_text);
          }
        }
        fclose(in_file);
        status = 0;
        break;
      case IDC_CHEAT_SAVE:
        if ( open_file_dialog("Save PSX CHEAT", "PSX CHEATs (*.CHT)", temp_path, "cheats\\", "CHT") )
        {
          out_file = fopen(temp_path, aW);
          save_count = SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x18Bu, 0, 0);
          if ( save_count )
          {
            do
            {
              save_next = save_count - 1;
              SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x189u, save_count - 1, (LPARAM)item_text);
              sscanf(item_text, "  %06x    %08x", &address, &value);
              sprintf(item_text, "%x %x\n", address, value);
              fputs(item_text, out_file);
              save_count = save_next;
            }
            while ( save_next );
          }
          fclose(out_file);
        }
        return 0;
      case IDC_CHEAT_OK:
        count = SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x18Bu, 0, 0);
        active_mini_cheat_count = 0;
        if ( count )
        {
          do
          {
            next = count - 1;
            SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x189u, count - 1, (LPARAM)item_text);
            sscanf(
              item_text,
              "  %06x    %08x",
              &mini_cheat_id_array[2 * (uint8_t)active_mini_cheat_count],
              &mini_cheat_attr_array[2 * (uint8_t)active_mini_cheat_count]);
            count = next;
            ++active_mini_cheat_count;
          }
          while ( next );
        }
        EndDialog(hDlg, 1);
        status = 1;
        break;
      case IDC_CHEAT_CANCEL:
        EndDialog(hDlg, 1);
        status = 1;
        break;
      case IDC_CHEAT_REMOVE_ALL:
        status = SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x18Bu, 0, 0);
        if ( !status )
          return 0;
        do
        {
          remaining = status - 1;
          SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x182u, status - 1, 0);
          status = remaining;
        }
        while ( remaining );
        break;
      case IDC_CHEAT_REMOVE:
        sel = SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x188u, 0, 0);
        if ( sel == -1 )
          return 0;
        SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x182u, sel, 0);
        status = 0;
        break;
      case IDC_CHEAT_ADD:
        GetDlgItemTextA(hDlg, IDC_CHEAT_VALUE, String, 1024);
        GetDlgItemTextA(hDlg, IDC_CHEAT_ADDRESS, Buffer, 1024);
        sscanf(String, "%x", &value);
        sscanf(Buffer, "%x", &address);
        sprintf(item_text, "  %06x    %08x", address, value);
        SendDlgItemMessageA(hDlg, IDC_CHEAT_LIST, 0x180u, 0, (LPARAM)item_text);
        status = 0;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return status;
}

int __stdcall about_callback(HWND hDlg, int uMsg, int16_t wParam, int lParam)
{
  if ( uMsg == 272 )
    return 1;
  if ( uMsg == 273 && wParam == 1002 )
  {
    EndDialog(hDlg, 1);
    return 1;
  }
  return 0;
}

INT_PTR __stdcall bios_dialog_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  INT_PTR status;

  if ( uMsg == 272 )
  {
    SetDlgItemTextA(hDlg, IDC_BIOS_PATH, (LPCSTR)bios_name);
    return 1;
  }
  else if ( uMsg == 273 )
  {
    switch ( (int16_t)wParam )
    {
      case IDC_BIOS_PATH:
        return 1;
      case IDC_BIOS_SELECT:
        if ( !open_file_dialog("Select PSX BIOS", "PSX BIOS (*.BIN)", temp_path, "bios\\", "BIN") )
          return 1;
        SetDlgItemTextA(hDlg, IDC_BIOS_PATH, temp_path);
        status = 1;
        break;
      case IDC_BIOS_OK:
        GetDlgItemTextA(hDlg, IDC_BIOS_PATH, (LPSTR)bios_name, 1024);
        EndDialog(hDlg, 1);
        cfg_save_settings();
        status = 1;
        break;
      case IDC_BIOS_CANCEL:
        EndDialog(hDlg, 1);
        status = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return status;
}

INT_PTR __stdcall search_video_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  int i;
  char ch;
  INT_PTR status;
  unsigned int sel_ok;
  unsigned int sel_test;
  HMODULE test_lib;
  char test_result;
  unsigned int sel_cfg;
  HMODULE cfg_lib;
  unsigned int sel_about;
  HMODULE about_lib;
  HMODULE library;
  HMODULE lib;
  FARPROC PSEgetLibVersion_ptr;
  uint8_t version;
  int version_info;
  const char *lib_name;
  LRESULT index;
  int count;
  CHAR *name;
  char *dst_offset;
  CHAR ch2;
  char *src;
  int shift_count;
  char *ptr;
  char ch3;
  int insert_offset;
  CHAR *name_src;
  char ch4;
  int major;
  int minor;
  char plugin_dir[12];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  CHAR FileName[1024];
  char item_text[1024];

  strcpy(plugin_dir, "plugins\\");
  i = 0;
  do
  {
    ch = plugin_dir[i];
    FileName[i++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.dll");
  if ( uMsg == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print("not video plugins found\n");
    found_plugin_count = 0;
    do
    {
      sprintf(LibFileName, "%s%s", plugin_dir, FindFileData.cFileName);
      library = LoadLibraryA(LibFileName);
      lib = library;
      if ( library )
      {
        PSEgetLibType = GetProcAddress(library, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(lib, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(lib, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              version = PSEgetLibVersion_ptr();
              version_info = PSEgetLibVersion(version);
              lib_name = (const char *)PSEgetLibName(BYTE1(version_info));
              sprintf(item_text, "%s %d.%d", lib_name, major, minor);
              if ( PSEgetLibType() == 2 )
              {
                index = SendDlgItemMessageA(hDlg, IDC_VIDEO_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
                if ( !strcmp((const char *)VideoPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(hDlg, IDC_VIDEO_PLUGIN_LIST, 0x14Eu, index, 0);
                count = found_plugin_count;
                if ( index == found_plugin_count )
                {
                  name = FindFileData.cFileName;
                  dst_offset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    ch2 = *name;
                    name[(uint32_t)dst_offset] = *name;
                    ++name;
                  }
                  while ( ch2 );
                }
                else
                {
                  if ( index < found_plugin_count )
                  {
                    src = &plugin_name_list_shift[1024 * found_plugin_count];
                    shift_count = found_plugin_count - index;
                    do
                    {
                      ptr = src;
                      do
                      {
                        ch3 = *ptr;
                        ptr[1024] = *ptr;
                        ++ptr;
                      }
                      while ( ch3 );
                      src -= 1024;
                      --shift_count;
                    }
                    while ( shift_count );
                  }
                  insert_offset = (index << 10) - (uint32_t)FindFileData.cFileName;
                  name_src = FindFileData.cFileName;
                  do
                  {
                    ch4 = *name_src;
                    plugin_name_list[insert_offset + (uint32_t)name_src] = *name_src;
                    ++name_src;
                  }
                  while ( ch4 );
                }
                found_plugin_count = count + 1;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    return 1;
  }
  else if ( uMsg == 273 )
  {
    switch ( (int16_t)wParam )
    {
      case IDC_VIDEO_TEST:
        if ( !found_plugin_count )
          return 0;
        sel_test = SendDlgItemMessageA(hDlg, IDC_VIDEO_PLUGIN_LIST, CB_GETCURSEL, 0, 0);
        if ( sel_test == -1 || sel_test >= found_plugin_count )
          return 0;
        sprintf(LibFileName, "%s%s", plugin_dir, &plugin_name_list[1024 * sel_test]);
        test_lib = LoadLibraryA(LibFileName);
        GPUinit_0 = GetProcAddress(test_lib, "GPUinit");
        GPUtest_0 = GetProcAddress(test_lib, "GPUtest");
        GPUshutdown_0 = GetProcAddress(test_lib, "GPUshutdown");
        GPUinit_0();
        test_result = GPUtest_0();
        if ( test_result )
        {
          if ( test_result == -1 )
            MessageBoxA(nullptr, "   Plugin NOT working, try configuring it.  ", "Testing GPU Plugin", 0x10u);
          else
            MessageBoxA(nullptr, "UNK value", "Testing GPU Plugin", 0x40u);
          GPUshutdown_0();
          status = 0;
        }
        else
        {
          MessageBoxA(nullptr, "   Plugin working correctly.  ", "Testing GPU Plugin", 0x40u);
          GPUshutdown_0();
          status = 0;
        }
        break;
      case IDC_VIDEO_CONFIGURE:
        if ( !found_plugin_count )
          return 0;
        sel_cfg = SendDlgItemMessageA(hDlg, IDC_VIDEO_PLUGIN_LIST, CB_GETCURSEL, 0, 0);
        if ( sel_cfg == -1 || sel_cfg >= found_plugin_count )
          return 0;
        sprintf(LibFileName, "%s%s", plugin_dir, &plugin_name_list[1024 * sel_cfg]);
        cfg_lib = LoadLibraryA(LibFileName);
        GPUinit_0 = GetProcAddress(cfg_lib, "GPUinit");
        PSEconfigure = GetProcAddress(cfg_lib, "GPUconfigure");
        GPUshutdown_0 = GetProcAddress(cfg_lib, "GPUshutdown");
        GPUinit_0();
        PSEconfigure();
        GPUshutdown_0();
        status = 0;
        break;
      case IDC_VIDEO_ABOUT:
        if ( found_plugin_count )
        {
          sel_about = SendDlgItemMessageA(hDlg, IDC_VIDEO_PLUGIN_LIST, CB_GETCURSEL, 0, 0);
          if ( sel_about != -1 && sel_about < found_plugin_count )
          {
            sprintf(LibFileName, "%s%s", plugin_dir, &plugin_name_list[1024 * sel_about]);
            about_lib = LoadLibraryA(LibFileName);
            GPUinit_0 = GetProcAddress(about_lib, "GPUinit");
            GPUabout_0 = GetProcAddress(about_lib, "GPUabout");
            GPUshutdown_0 = GetProcAddress(about_lib, "GPUshutdown");
            GPUinit_0();
            GPUabout_0();
            GPUshutdown_0();
          }
        }
        return 0;
      case IDC_VIDEO_OK:
        if ( found_plugin_count )
        {
          sel_ok = SendDlgItemMessageA(hDlg, IDC_VIDEO_PLUGIN_LIST, 0x147u, 0, 0);
          if ( sel_ok != -1 && sel_ok < found_plugin_count )
            sprintf((char *const)VideoPlugin, "%s", &plugin_name_list[1024 * sel_ok]);
          EndDialog(hDlg, 1);
          cfg_save_settings();
          status = 1;
        }
        else
        {
          sprintf((char *const)VideoPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
          status = 1;
        }
        break;
      case IDC_VIDEO_CANCEL:
        if ( found_plugin_count )
        {
          EndDialog(hDlg, 1);
        }
        else
        {
          sprintf((char *const)VideoPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
        }
        status = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return status;
}

INT_PTR __stdcall search_net_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  int i;
  char ch;
  INT_PTR status;
  unsigned int sel_ok;
  unsigned int sel_test;
  const char *test_name;
  HMODULE test_lib;
  char test_result;
  unsigned int sel_cfg;
  const char *cfg_name;
  HMODULE cfg_lib;
  unsigned int sel_about;
  const char *about_name;
  HMODULE about_lib;
  HWND dlg;
  LRESULT (__stdcall *send_dlg_msg)(HWND, int, UINT, WPARAM, LPARAM);
  LRESULT disabled_index;
  int count;
  HMODULE library;
  HMODULE lib;
  FARPROC PSEgetLibVersion_ptr;
  uint8_t version;
  int version_info;
  const char *lib_name;
  signed int index;
  int saved_count;
  CHAR *name;
  char *dst_offset;
  CHAR ch2;
  char *src;
  int shift_count;
  char *ptr;
  char ch3;
  int insert_offset;
  CHAR *name_src;
  char ch4;
  int major;
  int minor;
  char plugin_dir[12];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  char item_text[1024];
  CHAR FileName[1024];

  strcpy(plugin_dir, "plugins\\");
  i = 0;
  do
  {
    ch = plugin_dir[i];
    FileName[i++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.dll");
  if ( uMsg == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print("not net plugins found\n");
    found_plugin_count = 0;
    sprintf(item_text, "Disabled Netplay");
    dlg = hDlg;
    send_dlg_msg = SendDlgItemMessageA;
    disabled_index = SendDlgItemMessageA(hDlg, IDC_NET_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
    if ( !strcmp((const char *)NetPlugin, "DISABLED") )
      SendDlgItemMessageA(hDlg, IDC_NET_PLUGIN_LIST, 0x14Eu, disabled_index, 0);
    count = found_plugin_count;
    strcpy(&plugin_name_list[1024 * found_plugin_count], "DISABLED");
    found_plugin_count = count + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", plugin_dir, FindFileData.cFileName);
      library = LoadLibraryA(LibFileName);
      lib = library;
      if ( library )
      {
        PSEgetLibType = GetProcAddress(library, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(lib, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(lib, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              version = PSEgetLibVersion_ptr();
              version_info = PSEgetLibVersion(version);
              lib_name = (const char *)PSEgetLibName(BYTE1(version_info));
              sprintf(item_text, "%s %d.%d", lib_name, major, minor);
              if ( PSEgetLibType() == 16 )
              {
                index = send_dlg_msg(dlg, IDC_NET_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
                if ( !strcmp((const char *)NetPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(dlg, IDC_NET_PLUGIN_LIST, CB_SETCURSEL, index, 0);
                saved_count = found_plugin_count;
                if ( index == found_plugin_count )
                {
                  name = FindFileData.cFileName;
                  dst_offset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    ch2 = *name;
                    name[(uint32_t)dst_offset] = *name;
                    ++name;
                  }
                  while ( ch2 );
                }
                else
                {
                  if ( (unsigned int)index < found_plugin_count )
                  {
                    src = &plugin_name_list_shift[1024 * found_plugin_count];
                    shift_count = found_plugin_count - index;
                    do
                    {
                      ptr = src;
                      do
                      {
                        ch3 = *ptr;
                        ptr[1024] = *ptr;
                        ++ptr;
                      }
                      while ( ch3 );
                      src -= 1024;
                      --shift_count;
                    }
                    while ( shift_count );
                  }
                  insert_offset = (index << 10) - (uint32_t)FindFileData.cFileName;
                  name_src = FindFileData.cFileName;
                  do
                  {
                    ch4 = *name_src;
                    plugin_name_list[insert_offset + (uint32_t)name_src] = *name_src;
                    ++name_src;
                  }
                  while ( ch4 );
                }
                found_plugin_count = saved_count + 1;
                dlg = hDlg;
              }
            }
          }
        }
      }
      if ( !FindNextFileA(hFindFile, &FindFileData) )
        break;
      send_dlg_msg = SendDlgItemMessageA;
    }
    return 1;
  }
  else if ( uMsg == 273 )
  {
    switch ( (int16_t)wParam )
    {
      case IDC_NET_TEST:
        if ( !found_plugin_count )
          return 0;
        sel_test = SendDlgItemMessageA(hDlg, IDC_NET_PLUGIN_LIST, CB_GETCURSEL, 0, 0);
        if ( sel_test == -1 )
          return 0;
        if ( sel_test >= found_plugin_count )
          return 0;
        test_name = &plugin_name_list[1024 * sel_test];
        if ( !strcmp(test_name, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", plugin_dir, test_name);
        test_lib = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(test_lib, "NETtest");
        test_result = GPUtest_0();
        if ( test_result )
        {
          if ( test_result == -1 )
            MessageBoxA(nullptr, "   Plugin NOT working, try configuring it.  ", "Testing NET Plugin", 0x10u);
          else
            MessageBoxA(nullptr, "UNK value", "Testing NET Plugin", 0x40u);
          status = 0;
        }
        else
        {
          MessageBoxA(nullptr, "   Plugin working correctly.  ", "Testing NET Plugin", 0x40u);
          status = 0;
        }
        break;
      case IDC_NET_CONFIGURE:
        if ( !found_plugin_count )
          return 0;
        sel_cfg = SendDlgItemMessageA(hDlg, IDC_NET_PLUGIN_LIST, CB_GETCURSEL, 0, 0);
        if ( sel_cfg == -1 )
          return 0;
        if ( sel_cfg >= found_plugin_count )
          return 0;
        cfg_name = &plugin_name_list[1024 * sel_cfg];
        if ( !strcmp(cfg_name, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", plugin_dir, cfg_name);
        cfg_lib = LoadLibraryA(LibFileName);
        PSEconfigure = GetProcAddress(cfg_lib, "NETconfigure");
        PSEconfigure();
        status = 0;
        break;
      case IDC_NET_ABOUT:
        if ( found_plugin_count )
        {
          sel_about = SendDlgItemMessageA(hDlg, IDC_NET_PLUGIN_LIST, 0x147u, 0, 0);
          if ( sel_about != -1 && sel_about < found_plugin_count )
          {
            about_name = &plugin_name_list[1024 * sel_about];
            if ( strcmp(about_name, "DISABLED") )
            {
              sprintf(LibFileName, "%s%s", plugin_dir, about_name);
              about_lib = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(about_lib, "NETabout");
              GPUabout_0();
            }
          }
        }
        return 0;
      case IDC_NET_OK:
        if ( found_plugin_count )
        {
          sel_ok = SendDlgItemMessageA(hDlg, IDC_NET_PLUGIN_LIST, 0x147u, 0, 0);
          if ( sel_ok != -1 && sel_ok < found_plugin_count )
            sprintf((char *const)NetPlugin, "%s", &plugin_name_list[1024 * sel_ok]);
          EndDialog(hDlg, 1);
          cfg_save_settings();
          status = 1;
        }
        else
        {
          sprintf((char *const)NetPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
          status = 1;
        }
        break;
      case IDC_NET_CANCEL:
        if ( found_plugin_count )
        {
          EndDialog(hDlg, 1);
        }
        else
        {
          sprintf((char *const)NetPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
        }
        status = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return status;
}

INT_PTR __stdcall w9x_cdrom_settings(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LRESULT selection;
  LRESULT offset;
  int target;
  int lun;
  signed int index;
  char *device;
  char item_text[1024];

  if ( uMsg == 272 )
  {
    W9x_load_winaspi_dll();
    W9x_init_aspi();
    W9x_free_winaspi_dll();
    index = 0;
    if ( HIBYTE(w9x_cdrom_info) )
    {
      device = cd_device_product;
      do
      {
        sprintf(
          item_text,
          "%d:%d:%d %08s  %016s  %04s",
          *(uint32_t *)(device + 43),
          *(uint32_t *)(device + 47),
          *(uint32_t *)(device + 51),
          device - 9,
          device,
          device + 17);
        SendDlgItemMessageA(hDlg, IDC_CDROM9X_DEVICE_LIST, CB_ADDSTRING, 0, (LPARAM)item_text);
        if ( *(uint32_t *)(device + 43) == cdrom_haid
          && *(uint32_t *)(device + 47) == cdrom_target
          && *(uint32_t *)(device + 51) == cdrom_lun )
        {
          SendDlgItemMessageA(hDlg, IDC_CDROM9X_DEVICE_LIST, 0x14Eu, index, 0);
        }
        ++index;
        device += 64;
      }
      while ( index < HIBYTE(w9x_cdrom_info) );
    }
    SendDlgItemMessageA(hDlg, IDC_CDROM9X_SUBCHANNEL_READ, BM_SETCHECK, (uint8_t)SubchannelW9xCdromEnabled, 0);
    SendDlgItemMessageA(hDlg, IDC_CDROM9X_SUBCHANNEL_CACHE, BM_SETCHECK, (uint8_t)SubchannelW9xCaching, 0);
    SendDlgItemMessageA(hDlg, IDC_CDROM9X_SUBCHANNEL_CACHE_LG, BM_SETCHECK, (uint8_t)SubchannelW9xCachingLG, 0);
    return 1;
  }
  else
  {
    if ( uMsg != 273 )
      return 0;
    if ( (uint16_t)wParam == 1079 )
    {
      selection = SendDlgItemMessageA(hDlg, IDC_CDROM9X_DEVICE_LIST, CB_GETCURSEL, 0, 0);
      if ( selection != -1 && selection < HIBYTE(w9x_cdrom_info) )
      {
        offset = selection << 6;
        target = *(int *)((char *)&cd_device_target + offset);
        cdrom_haid = *(int *)((char *)&cd_device_haid + offset);
        lun = *(int *)((char *)cd_device_lun + offset);
        cdrom_target = target;
        cdrom_lun = lun;
      }
      SubchannelW9xCdromEnabled = SendDlgItemMessageA(hDlg, IDC_CDROM9X_SUBCHANNEL_READ, BM_GETCHECK, 0, 0);
      SubchannelW9xCaching = SendDlgItemMessageA(hDlg, IDC_CDROM9X_SUBCHANNEL_CACHE, BM_GETCHECK, 0, 0);
      SubchannelW9xCachingLG = SendDlgItemMessageA(hDlg, IDC_CDROM9X_SUBCHANNEL_CACHE_LG, BM_GETCHECK, 0, 0);
      EndDialog(hDlg, 1);
      cfg_cdrom_set_hain_target_lun();
      return 1;
    }
    else
    {
      if ( (uint16_t)wParam != 1080 )
        return 0;
      EndDialog(hDlg, 1);
      return 1;
    }
  }
}

static INT_PTR __stdcall w2k_cdrom_settings(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  LRESULT selection;
  LRESULT first_idx;
  int letter;
  LRESULT index;
  CHAR item_text[1024];

  if ( uMsg == 272 )
  {
    sprintf(item_text, "FirstCdrom");
    first_idx = SendDlgItemMessageA(hDlg, IDC_CDROM2K_LETTER, CB_ADDSTRING, 0, (LPARAM)item_text);
    if ( !cdrom_letter )
      SendDlgItemMessageA(hDlg, IDC_CDROM2K_LETTER, CB_SETCURSEL, first_idx, 0);
    for ( letter = 65; letter <= 90; ++letter )
    {
      sprintf(item_text, "%c:\\", letter);
      if ( GetDriveTypeA(item_text) == 5 )
      {
        sprintf(item_text, "--%c:--", letter);
        index = SendDlgItemMessageA(hDlg, IDC_CDROM2K_LETTER, CB_ADDSTRING, 0, (LPARAM)item_text);
        if ( letter == cdrom_letter )
          SendDlgItemMessageA(hDlg, IDC_CDROM2K_LETTER, CB_SETCURSEL, index, 0);
      }
    }
    SendDlgItemMessageA(hDlg, IDC_CDROM2K_SUBCHANNEL_READ, BM_SETCHECK, (uint8_t)SubchannelW2kCdromEnabled, 0);
    SendDlgItemMessageA(hDlg, IDC_CDROM2K_SUBCHANNEL_CACHE, BM_SETCHECK, (uint8_t)SubchannelW2kCaching, 0);
    SendDlgItemMessageA(hDlg, IDC_CDROM2K_SUBCHANNEL_CACHE_LG, BM_SETCHECK, (uint8_t)SubchannelW2kCachingLG, 0);
    return 1;
  }
  else
  {
    if ( uMsg != 273 )
      return 0;
    if ( (uint16_t)wParam == 1134 )
    {
      selection = SendDlgItemMessageA(hDlg, IDC_CDROM2K_LETTER, CB_GETCURSEL, 0, 0);
      if ( selection != -1 )
      {
        SendDlgItemMessageA(hDlg, IDC_CDROM2K_LETTER, CB_GETLBTEXT, selection, (LPARAM)item_text);
        if ( !strncmp(item_text, "FirstCdrom", 4u) )
          cdrom_letter = 0;
        else
          sscanf(item_text, "--%c:--", &cdrom_letter);
      }
      SubchannelW2kCdromEnabled = SendDlgItemMessageA(hDlg, IDC_CDROM2K_SUBCHANNEL_READ, BM_GETCHECK, 0, 0);
      SubchannelW2kCaching = SendDlgItemMessageA(hDlg, IDC_CDROM2K_SUBCHANNEL_CACHE, BM_GETCHECK, 0, 0);
      SubchannelW2kCachingLG = SendDlgItemMessageA(hDlg, IDC_CDROM2K_SUBCHANNEL_CACHE_LG, BM_GETCHECK, 0, 0);
      EndDialog(hDlg, 1);
      cfg_cdrom_set_letter();
      return 1;
    }
    else
    {
      if ( (uint16_t)wParam != 1135 )
        return 0;
      EndDialog(hDlg, 1);
      return 1;
    }
  }
}

INT_PTR __stdcall search_cdrom_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  int i;
  char ch;
  unsigned int sel_ok;
  INT_PTR status;
  unsigned int sel_test;
  const char *test_name;
  HMODULE test_lib;
  unsigned int sel_cfg;
  const char *cfg_name;
  HMODULE cfg_lib;
  unsigned int sel_about;
  const char *about_name;
  HMODULE about_lib;
  HWND dlg;
  LRESULT (__stdcall *send_dlg_msg)(HWND, int, UINT, WPARAM, LPARAM);
  LRESULT aspi_index;
  int count;
  LRESULT w2k_index;
  int count2;
  HMODULE library;
  HMODULE lib;
  FARPROC PSEgetLibVersion_ptr;
  uint8_t version;
  int version_info;
  const char *lib_name;
  signed int index;
  int saved_count;
  CHAR *name;
  char *dst_offset;
  CHAR ch2;
  char *src;
  int shift_count;
  char *ptr;
  char ch3;
  int insert_offset;
  CHAR *name_src;
  char ch4;
  int major;
  int minor;
  char plugin_dir[12];
  HANDLE hFindFile;
  struct _OSVERSIONINFOA VersionInformation;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  char item_text[1024];
  CHAR FileName[1024];

  strcpy(plugin_dir, "plugins\\");
  i = 0;
  do
  {
    ch = plugin_dir[i];
    FileName[i++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.dll");
  if ( uMsg == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    found_plugin_count = 0;
    sprintf(item_text, "ePSXe CDR ASPI core 1.5.2.");
    dlg = hDlg;
    send_dlg_msg = SendDlgItemMessageA;
    aspi_index = SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
    if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
      SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x14Eu, aspi_index, 0);
    count = found_plugin_count;
    strcpy(&plugin_name_list[1024 * found_plugin_count], "W9XCDRCORE");
    found_plugin_count = count + 1;
    memset(&VersionInformation, 0, sizeof(VersionInformation));
    VersionInformation.dwOSVersionInfoSize = 148;
    GetVersionExA(&VersionInformation);
    if ( VersionInformation.dwPlatformId == 2 )
    {
      sprintf(item_text, "ePSXe CDR WNT/W2K core 1.5.2.");
      w2k_index = SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
      if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
        SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x14Eu, w2k_index, 0);
      count2 = found_plugin_count;
      strcpy(&plugin_name_list[1024 * found_plugin_count], "W2KCDRCORE");
      found_plugin_count = count2 + 1;
    }
    do
    {
      sprintf(LibFileName, "%s%s", plugin_dir, FindFileData.cFileName);
      library = LoadLibraryA(LibFileName);
      lib = library;
      if ( library )
      {
        PSEgetLibType = GetProcAddress(library, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(lib, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(lib, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              version = PSEgetLibVersion_ptr();
              version_info = PSEgetLibVersion(version);
              lib_name = (const char *)PSEgetLibName(BYTE1(version_info));
              sprintf(item_text, "%s %d.%d", lib_name, major, minor);
              if ( PSEgetLibType() == 1 )
              {
                index = send_dlg_msg(dlg, IDC_CDROM_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
                if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(dlg, IDC_CDROM_PLUGIN_LIST, 0x14Eu, index, 0);
                saved_count = found_plugin_count;
                if ( index == found_plugin_count )
                {
                  name = FindFileData.cFileName;
                  dst_offset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    ch2 = *name;
                    name[(uint32_t)dst_offset] = *name;
                    ++name;
                  }
                  while ( ch2 );
                }
                else
                {
                  if ( (unsigned int)index < found_plugin_count )
                  {
                    src = &plugin_name_list_shift[1024 * found_plugin_count];
                    shift_count = found_plugin_count - index;
                    do
                    {
                      ptr = src;
                      do
                      {
                        ch3 = *ptr;
                        ptr[1024] = *ptr;
                        ++ptr;
                      }
                      while ( ch3 );
                      src -= 1024;
                      --shift_count;
                    }
                    while ( shift_count );
                  }
                  insert_offset = (index << 10) - (uint32_t)FindFileData.cFileName;
                  name_src = FindFileData.cFileName;
                  do
                  {
                    ch4 = *name_src;
                    plugin_name_list[insert_offset + (uint32_t)name_src] = *name_src;
                    ++name_src;
                  }
                  while ( ch4 );
                }
                send_dlg_msg = SendDlgItemMessageA;
                found_plugin_count = saved_count + 1;
                dlg = hDlg;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    return 1;
  }
  else if ( uMsg == 273 )
  {
    switch ( (int16_t)wParam )
    {
      case IDC_CDROM_TEST:
        sel_test = SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x147u, 0, 0);
        if ( sel_test == -1 )
          return 0;
        if ( sel_test >= found_plugin_count )
          return 0;
        test_name = &plugin_name_list[1024 * sel_test];
        if ( !strcmp(test_name, "W9XCDRCORE") || !strcmp(test_name, "W2KCDRCORE") )
          return 0;
        sprintf(LibFileName, "%s%s", plugin_dir, test_name);
        test_lib = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(test_lib, "CDRtest");
        GPUtest_0();
        status = 0;
        break;
      case IDC_CDROM_CONFIGURE:
        sel_cfg = SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x147u, 0, 0);
        if ( sel_cfg == -1 || sel_cfg >= found_plugin_count )
          return 0;
        cfg_name = &plugin_name_list[1024 * sel_cfg];
        if ( !strcmp(cfg_name, "W9XCDRCORE") )
        {
          DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
          status = 0;
        }
        else
        {
          if ( !strcmp(cfg_name, "W2KCDRCORE") )
          {
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CDROMCORE2K", hDlg, w2k_cdrom_settings, 0);
          }
          else
          {
            sprintf(LibFileName, "%s%s", plugin_dir, cfg_name);
            cfg_lib = LoadLibraryA(LibFileName);
            GPUinit_0 = GetProcAddress(cfg_lib, "CDRinit");
            GPUinit_0();
            PSEconfigure = GetProcAddress(cfg_lib, "CDRconfigure");
            PSEconfigure();
          }
          status = 0;
        }
        break;
      case IDC_CDROM_ABOUT:
        sel_about = SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x147u, 0, 0);
        if ( sel_about != -1 && sel_about < found_plugin_count )
        {
          about_name = &plugin_name_list[1024 * sel_about];
          if ( strcmp(about_name, "W9XCDRCORE") )
          {
            if ( strcmp(about_name, "W2KCDRCORE") )
            {
              sprintf(LibFileName, "%s%s", plugin_dir, about_name);
              about_lib = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(about_lib, "CDRabout");
              GPUabout_0();
            }
          }
        }
        return 0;
      case IDC_CDROM_OK:
        sel_ok = SendDlgItemMessageA(hDlg, IDC_CDROM_PLUGIN_LIST, 0x147u, 0, 0);
        if ( sel_ok != -1 && sel_ok < found_plugin_count )
          sprintf((char *const)CdromPlugin, "%s", &plugin_name_list[1024 * sel_ok]);
        EndDialog(hDlg, 1);
        cfg_save_settings();
        status = 1;
        break;
      case IDC_CDROM_CANCEL:
        EndDialog(hDlg, 1);
        status = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return status;
}

INT_PTR __stdcall spucore_configure_dialog_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if ( uMsg != 272 )
  {
    if ( uMsg != 273 || (uint16_t)wParam != 1105 )
      return 0;
    EndDialog(hDlg, 1);
  }
  return 1;
}

INT_PTR __stdcall search_spu_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  int i;
  char ch;
  unsigned int sel_ok;
  INT_PTR status;
  unsigned int sel_test;
  const char *test_name;
  HMODULE test_lib;
  unsigned int sel_cfg;
  const char *cfg_name;
  HMODULE cfg_lib;
  unsigned int sel_about;
  const char *about_name;
  HMODULE about_lib;
  HWND dlg;
  LRESULT (__stdcall *send_dlg_msg)(HWND, int, UINT, WPARAM, LPARAM);
  LRESULT core_index;
  int count;
  int name_offset;
  HMODULE library;
  HMODULE lib;
  FARPROC PSEgetLibVersion_ptr;
  uint8_t version;
  int version_info;
  const char *lib_name;
  signed int index;
  int saved_count;
  CHAR *name;
  char *dst_offset;
  CHAR ch2;
  char *src;
  int shift_count;
  char *ptr;
  char ch3;
  int insert_offset;
  CHAR *name_src;
  char ch4;
  int major;
  int minor;
  char plugin_dir[12];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  char item_text[1024];
  CHAR FileName[1024];

  strcpy(plugin_dir, "plugins\\");
  i = 0;
  do
  {
    ch = plugin_dir[i];
    FileName[i++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.dll");
  if ( uMsg == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    found_plugin_count = 0;
    sprintf(item_text, "ePSXe SPU core 1.5.2.");
    dlg = hDlg;
    send_dlg_msg = SendDlgItemMessageA;
    core_index = SendDlgItemMessageA(hDlg, IDC_SOUND_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
    if ( !strcmp((const char *)SoundPlugin, "SPUCORE") )
      SendDlgItemMessageA(hDlg, IDC_SOUND_PLUGIN_LIST, 0x14Eu, core_index, 0);
    count = found_plugin_count;
    name_offset = found_plugin_count << 10;
    *(uint32_t *)&plugin_name_list[name_offset] = *(uint32_t *)"SPUCORE";
    strcpy(&plugin_name_list_tail[name_offset], "ORE");
    found_plugin_count = count + 1;
    do
    {
      sprintf(LibFileName, "%s%s", plugin_dir, FindFileData.cFileName);
      library = LoadLibraryA(LibFileName);
      lib = library;
      if ( library )
      {
        PSEgetLibType = GetProcAddress(library, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(lib, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(lib, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              version = PSEgetLibVersion_ptr();
              version_info = PSEgetLibVersion(version);
              lib_name = (const char *)PSEgetLibName(BYTE1(version_info));
              sprintf(item_text, "%s %d.%d", lib_name, major, minor);
              if ( PSEgetLibType() == 4 )
              {
                index = send_dlg_msg(dlg, IDC_SOUND_PLUGIN_LIST, 0x143u, 0, (LPARAM)item_text);
                if ( !strcmp((const char *)SoundPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(dlg, IDC_SOUND_PLUGIN_LIST, 0x14Eu, index, 0);
                saved_count = found_plugin_count;
                if ( index == found_plugin_count )
                {
                  name = FindFileData.cFileName;
                  dst_offset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    ch2 = *name;
                    name[(uint32_t)dst_offset] = *name;
                    ++name;
                  }
                  while ( ch2 );
                }
                else
                {
                  if ( (unsigned int)index < found_plugin_count )
                  {
                    src = &plugin_name_list_shift[1024 * found_plugin_count];
                    shift_count = found_plugin_count - index;
                    do
                    {
                      ptr = src;
                      do
                      {
                        ch3 = *ptr;
                        ptr[1024] = *ptr;
                        ++ptr;
                      }
                      while ( ch3 );
                      src -= 1024;
                      --shift_count;
                    }
                    while ( shift_count );
                  }
                  insert_offset = (index << 10) - (uint32_t)FindFileData.cFileName;
                  name_src = FindFileData.cFileName;
                  do
                  {
                    ch4 = *name_src;
                    plugin_name_list[insert_offset + (uint32_t)name_src] = *name_src;
                    ++name_src;
                  }
                  while ( ch4 );
                }
                send_dlg_msg = SendDlgItemMessageA;
                found_plugin_count = saved_count + 1;
                dlg = hDlg;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    send_dlg_msg(dlg, IDC_SOUND_ENABLE, 0xF1u, (uint8_t)sound_enabled, 0);
    send_dlg_msg(dlg, IDC_SOUND_XA, 0xF1u, (uint8_t)sound_use_xa, 0);
    send_dlg_msg(dlg, IDC_SOUND_CDDA, 0xF1u, (uint8_t)sound_use_cdda, 0);
    send_dlg_msg(dlg, IDC_SOUND_SPU_IRQ_HACK, 0xF1u, (uint8_t)forcespu, 0);
    return 1;
  }
  else if ( uMsg == 273 )
  {
    switch ( (int16_t)wParam )
    {
      case IDC_SOUND_TEST:
        sel_test = SendDlgItemMessageA(hDlg, IDC_SOUND_PLUGIN_LIST, 0x147u, 0, 0);
        if ( sel_test == -1 )
          return 0;
        if ( sel_test >= found_plugin_count )
          return 0;
        test_name = &plugin_name_list[1024 * sel_test];
        if ( !strcmp(test_name, "SPUCORE") )
          return 0;
        sprintf(LibFileName, "%s%s", plugin_dir, test_name);
        test_lib = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(test_lib, "SPUtest");
        GPUtest_0();
        status = 0;
        break;
      case IDC_SOUND_CONFIGURE:
        sel_cfg = SendDlgItemMessageA(hDlg, IDC_SOUND_PLUGIN_LIST, 0x147u, 0, 0);
        if ( sel_cfg == -1 || sel_cfg >= found_plugin_count )
          return 0;
        cfg_name = &plugin_name_list[1024 * sel_cfg];
        if ( !strcmp(cfg_name, "SPUCORE") )
        {
          DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_SOUND9X", hDlg, spucore_configure_dialog_callback, 0);
        }
        else
        {
          sprintf(LibFileName, "%s%s", plugin_dir, cfg_name);
          cfg_lib = LoadLibraryA(LibFileName);
          PSEconfigure = GetProcAddress(cfg_lib, "SPUconfigure");
          PSEconfigure();
        }
        status = 0;
        break;
      case IDC_SOUND_ABOUT:
        sel_about = SendDlgItemMessageA(hDlg, IDC_SOUND_PLUGIN_LIST, CB_GETCURSEL, 0, 0);
        if ( sel_about != -1 && sel_about < found_plugin_count )
        {
          about_name = &plugin_name_list[1024 * sel_about];
          if ( strcmp(about_name, "SPUCORE") )
          {
            sprintf(LibFileName, "%s%s", plugin_dir, about_name);
            about_lib = LoadLibraryA(LibFileName);
            GPUabout_0 = GetProcAddress(about_lib, "SPUabout");
            GPUabout_0();
          }
        }
        return 0;
      case IDC_SOUND_OK:
        sel_ok = SendDlgItemMessageA(hDlg, IDC_SOUND_PLUGIN_LIST, CB_GETCURSEL, 0, 0);
        if ( sel_ok != -1 && sel_ok < found_plugin_count )
          sprintf((char *const)SoundPlugin, "%s", &plugin_name_list[1024 * sel_ok]);
        sound_enabled = SendDlgItemMessageA(hDlg, IDC_SOUND_ENABLE, 0xF0u, 0, 0);
        sound_use_xa = SendDlgItemMessageA(hDlg, IDC_SOUND_XA, 0xF0u, 0, 0);
        sound_use_cdda = SendDlgItemMessageA(hDlg, IDC_SOUND_CDDA, 0xF0u, 0, 0);
        forcespu = SendDlgItemMessageA(hDlg, IDC_SOUND_SPU_IRQ_HACK, 0xF0u, 0, 0);
        EndDialog(hDlg, 1);
        cfg_save_settings();
        status = 1;
        break;
      case IDC_SOUND_CANCEL:
        EndDialog(hDlg, 1);
        status = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return status;
}

INT_PTR __stdcall memcard_settings(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  INT_PTR status;

  if ( uMsg == 272 )
  {
    SetDlgItemTextA(hDlg, IDC_MEMCARD_FILE1, (LPCSTR)Memcard1);
    SetDlgItemTextA(hDlg, IDC_MEMCARD_FILE2, (LPCSTR)Memcard2);
    return 1;
  }
  else if ( uMsg == 273 )
  {
    switch ( (int16_t)wParam )
    {
      case IDC_MEMCARD_FILE2:
      case IDC_MEMCARD_FILE1:
        return 1;
      case IDC_MEMCARD_SELECT2:
        if ( !open_file_dialog(
                "Select Memcard FILE 2",
                "MEMCARD FILE (*.MCR, *.MEM, *.MCD, *.GME)",
                temp_path,
                "memcards\\",
                "MCR") )
          return 1;
        SetDlgItemTextA(hDlg, IDC_MEMCARD_FILE2, temp_path);
        status = 1;
        break;
      case IDC_MEMCARD_SELECT1:
        if ( !open_file_dialog(
                "Select Memcard FILE 1",
                "MEMCARD FILE (*.MCR, *.MEM, *.MCD, *.GME)",
                temp_path,
                "memcards\\",
                "MCR") )
          return 1;
        SetDlgItemTextA(hDlg, IDC_MEMCARD_FILE1, temp_path);
        status = 1;
        break;
      case IDC_MEMCARD_OK:
        GetDlgItemTextA(hDlg, IDC_MEMCARD_FILE1, (LPSTR)Memcard1, 1024);
        GetDlgItemTextA(hDlg, IDC_MEMCARD_FILE2, (LPSTR)Memcard2, 1024);
        if ( sio_memcard_loaded )
        {
          sio_memcard_loaded = 0;
          sio_memcard_load();
        }
        EndDialog(hDlg, 1);
        cfg_save_settings();
        status = 1;
        break;
      case IDC_MEMCARD_CANCEL:
        EndDialog(hDlg, 1);
        status = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return status;
}

int calc_bios_checksum(uint8_t *ptr, int size)
{
  uint16_t checksum;
  int sum;
  uint8_t *p;
  int low;
  int high;
  int word;

  checksum = 0;
  sum = 0;
  if ( size > 0 )
  {
    p = ptr + 1;
    do
    {
      low = *(p - 1);
      high = *p;
      p += 2;
      word = high + (low << 8);
      sum += word;
      checksum ^= word;
    }
    while ( (int)&p[-1 - (uint32_t)ptr] < size );
  }
  return checksum ^ (sum << 16);
}


/* Decompiled globals (previously generated in src/_gen) */
int (__stdcall *GPUabout_0)();
int (__stdcall *GPUinit_0)();
int (__stdcall *GPUshutdown_0)();
int (__stdcall *GPUtest_0)();
int ( *PSEconfigure)();
int ( *PSEgetLibName)();
int ( *PSEgetLibType)();
int ( *PSEgetLibVersion)();
char aW[8];
char asc_44E24C[64];
unsigned char extended_key_states_1[1];
unsigned char extended_key_states_2[1];
unsigned char extended_key_states_3[0xa0];
unsigned char plugin_name_list_shift[0x380];
unsigned char pad_keymap_dialog_copy[0x20];
unsigned char plugin_name_list[0x4];
unsigned char plugin_name_list_tail[0x7ffc];
unsigned int controller_port_modes[8];
unsigned int found_plugin_count = 0x0;
unsigned int joypad_button_map[1];
unsigned int pad2_small_motor_type;
unsigned int pad4_small_motor_type[1];
unsigned int saved_pad_joypad_buttons;
unsigned int saved_pad_mdec_disable_flag;
unsigned char edit_button_id = 0xff;
unsigned int g_EffectType2[1];
unsigned int g_PlayerDeviceMap4[1];
unsigned char joy_names[14] = {0x4a, 0x31, 0x5f, 0x4e, 0x4f, 0x4e, 0x45, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned char multitap_1;
unsigned short nIDDlgItem = IDC_CONTROLLER_AXIS_X1;
unsigned char pad_number_menu_selection = 0x1;
unsigned char stru_44C148[13] = {0x4e, 0x4f, 0x4e, 0x45, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned char temp_path[0x400];
unsigned short controller_button_dlg_ids[9] = {IDC_CONTROLLER_LEFT, IDC_CONTROLLER_RIGHT, IDC_CONTROLLER_UP, IDC_CONTROLLER_DOWN,
                        IDC_CONTROLLER_TRIANGLE, IDC_CONTROLLER_CIRCLE, IDC_CONTROLLER_CROSS,
                        IDC_CONTROLLER_SQUARE, IDC_CONTROLLER_L1};
unsigned short pad_key_assignments[4] = {0x1, 0x0, 0x0, 0x0};
