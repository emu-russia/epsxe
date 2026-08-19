#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
unsigned char bin_iso_file[0x100];
static unsigned char shift_key_pressed = 0x0;
static unsigned int save_load_state_slot[1] = {0xffffffff};
static unsigned int main_window_bitmap = 0x0;
unsigned char g_bDisableMouse = 0x1;
unsigned int g_hInstance;
unsigned int g_hWnd = 0x0;
static unsigned int h = 0x0;
static MSG stru_8A94E0;


static LRESULT __stdcall main_window_callback(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  LRESULT ret;
  HDC hdc;
  HDC CompatibleDC;
  int i;
  char ch;
  int uninit;
  int j;
  char c;
  HMENU logs_menu;
  HDC pad_dc;
  int device_caps;
  HDC cap_dc2;
  int device_caps2;
  HDC cap_dc3;
  int device_caps3;
  HDC cap_dc4;
  HMENU multitap_menu;
  HMENU ppf_menu;
  HMENU country_menu;
  HMENU ntsc_menu;
  HMENU pal_menu;
  HMENU popup_menu;
  int state0_exists;
  int state1_exists;
  int state2_exists;
  int state3_exists;
  int state4_exists;
  HWND dialog_parent;
  HWND dialog_parent2;
  LPSTR FilePart;
  CHAR Buffer[1024];

  if ( Msg > 0xF )
  {
    switch ( Msg )
    {
      case 0x100u:
        if ( wParam == 16 )
          shift_key_pressed = 1;
        ret = 0;
        break;
      case 0x101u:
        if ( wParam == 16 )
          shift_key_pressed = 0;
        ret = 0;
        break;
      case 0x111u:
        switch ( (uint16_t)wParam )
        {
          case IDM_RUN_CDROM:
            if ( !strcmp((const char *)VideoPlugin, "NULL") )
              goto LABEL_26;
            if ( !strcmp((const char *)CdromPlugin, "NULL") )
              goto LABEL_28;
            if ( loader_check_bios_file_exists() )
              goto LABEL_30;
            PostQuitMessage(0);
            if ( shift_key_pressed )
              fastboot = 0;
            nocd = 1;
            loader_set_filename("NULL");
            loaded_file_type = 1;
            g_bDisableMouse = 0;
            return 1;
          case IDM_RUN_BIOS:
            if ( !strcmp((const char *)VideoPlugin, "NULL") )
              goto LABEL_26;
            if ( !strcmp((const char *)CdromPlugin, "NULL") )
              goto LABEL_28;
            if ( loader_check_bios_file_exists() )
              goto LABEL_30;
            PostQuitMessage(0);
            fastboot = 0;
            nocd = 0;
            loader_set_filename("NULL");
            loaded_file_type = 2;
            g_bDisableMouse = 0;
            return 1;
          case IDM_RUN_ISO:
            if ( !strcmp((const char *)VideoPlugin, "NULL") )
            {
LABEL_26:
              MessageBoxA(
                nullptr,
                "ePSXe is NOT completely configurated go to config->video to configure it",
                "ePSXe not configurated",
                0x10u);
              return 1;
            }
            if ( !strcmp((const char *)CdromPlugin, "NULL") )
            {
LABEL_28:
              MessageBoxA(
                nullptr,
                "ePSXe is NOT completely configurated go to config->cdrom to configure it",
                "ePSXe not configurated",
                0x10u);
              return 1;
            }
            if ( loader_check_bios_file_exists() )
            {
LABEL_30:
              MessageBoxA(
                nullptr,
                "ePSXe is NOT completely configurated go to config->bios to configure it",
                "ePSXe not configurated",
                0x10u);
              return 1;
            }
            if ( !open_file_dialog("Open PSX ISO", "PSX ISOs (*.BIN, *.ISO, *.IMG)", temp_path, IsoDirectory, "ISO") )
              return 1;
            GetFullPathNameA(temp_path, 0x400u, Buffer, &FilePart);
            *FilePart = 0;
            sprintf(IsoDirectory, "%s", temp_path);
            cfg_cdrom_iso_set_path();
            PostQuitMessage(0);
            if ( shift_key_pressed )
              fastboot = 0;
            i = 0;
            do
            {
              ch = temp_path[i];
              bin_iso_file[i++] = ch;
            }
            while ( ch );
            loader_set_filename("NULL");
            loaded_file_type = 3;
            g_bDisableMouse = 0;
            return 1;
          case IDM_RUN_PS_EXE:
            if ( !open_file_dialog("Open PSX EXE", "PSX EXEs (*.ZIP, *.EXE)", temp_path, ".", "EXE") )
              return 1;
            PostQuitMessage(0);
            loader_set_filename(temp_path);
            loaded_file_type = 4;
            g_bDisableMouse = 0;
            return 1;
          case IDM_EXIT:
            ui_error(" * Going out from gui. (exit)\n");
          case IDM_CONFIG_VIDEO:
            DialogBoxParamA(g_hInstance, "IDD_VIDEO", hWnd, search_video_plugin, 0);
            return 1;
          case IDM_CONFIG_SOUND:
            DialogBoxParamA(g_hInstance, "IDD_SOUND", hWnd, search_spu_plugin, 0);
            return 1;
          case IDM_CONFIG_CDROM:
            DialogBoxParamA(g_hInstance, "IDD_CDROM", hWnd, search_cdrom_plugin, 0);
            return 1;
          case IDM_CONFIG_BIOS:
            DialogBoxParamA(g_hInstance, "IDD_BIOS", hWnd, bios_dialog_callback, 0);
            return 1;
          case IDM_CHEAT:
            DialogBoxParamA(g_hInstance, "IDD_CHEAT", hWnd, (DLGPROC)cheat_dialog_callback, 0);
            goto LABEL_68;
          case IDM_ABOUT:
            DialogBoxParamA(g_hInstance, "IDD_ABOUT", hWnd, (DLGPROC)about_callback, 0);
            goto LABEL_68;
          case IDM_VISIT_WEBSITE:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com", nullptr, nullptr, 3);
            return 1;
          case IDM_CONTINUE:
            if ( loaded_file_type )
              goto LABEL_41;
            return 1;
          case IDM_RESET:
            if ( !loaded_file_type )
              return 1;
            reset_flag = 1;
            goto LABEL_41;
          case IDM_PAD1:
            pad_number_menu_selection = 1;
            pad_dc = GetDC(hWnd);
            device_caps = GetDeviceCaps(pad_dc, 88);
            ReleaseDC(hWnd, pad_dc);
            dialog_parent = hWnd;
            goto LABEL_65;
          case IDM_PAD2:
            pad_number_menu_selection = 2;
            cap_dc2 = GetDC(hWnd);
            device_caps2 = GetDeviceCaps(cap_dc2, 88);
            ReleaseDC(hWnd, cap_dc2);
            dialog_parent2 = hWnd;
            if ( device_caps2 <= 96 )
              goto LABEL_70;
            goto LABEL_71;
          case IDM_MEMORY_CARD:
            DialogBoxParamA(g_hInstance, "IDD_MEMCARD", hWnd, memcard_settings, 0);
            return 1;
          case IDM_CHANGE_DISC_CDROM:
            cdrom_deinit_cb(Msg - 256);
            MessageBoxA(nullptr, "Insert a new cdrom and hit the button to continue", "Change Disc Option", 0x40u);
            nocd = 1;
            loader_set_filename("NULL");
            loaded_file_type = 1;
            goto LABEL_40;
          case IDM_CHANGE_DISC_ISO:
            if ( !open_file_dialog("Open PSX ISO", "PSX ISOs (*.BIN, *.ISO, *.IMG)", temp_path, IsoDirectory, "ISO") )
              return 1;
            GetFullPathNameA(temp_path, 0x400u, Buffer, &FilePart);
            *FilePart = 0;
            sprintf(IsoDirectory, "%s", temp_path);
            cfg_cdrom_iso_set_path();
            cdrom_deinit_cb(uninit);
            j = 0;
            do
            {
              c = temp_path[j];
              bin_iso_file[j++] = c;
            }
            while ( c );
            loader_set_filename("NULL");
            loaded_file_type = 3;
LABEL_40:
            g_bDisableMouse = 0;
            country_setting = 255;
            cdrom_reset_cb();
            cdrom_init_cb();
            loader_cdrom_detect_region();
            cdrom_subchannel_read_cb();
LABEL_41:
            PostQuitMessage(0);
            return 1;
          case IDM_COUNTRY_AUTODETECT:
            country_menu = GetMenu(hWnd);
            CheckMenuItem(country_menu, IDM_COUNTRY_AUTODETECT, 8u);
            CheckMenuItem(country_menu, IDM_COUNTRY_NTSC, 0);
            CheckMenuItem(country_menu, IDM_COUNTRY_PAL, 0);
            country_setting = 255;
            cfg_save_settings();
            return 1;
          case IDM_COUNTRY_NTSC:
            ntsc_menu = GetMenu(hWnd);
            CheckMenuItem(ntsc_menu, IDM_COUNTRY_AUTODETECT, 0);
            CheckMenuItem(ntsc_menu, IDM_COUNTRY_NTSC, 0);
            CheckMenuItem(ntsc_menu, IDM_COUNTRY_PAL, 8u);
            country_setting = 0;
            cfg_save_settings();
            return 1;
          case IDM_COUNTRY_PAL:
            pal_menu = GetMenu(hWnd);
            CheckMenuItem(pal_menu, IDM_COUNTRY_AUTODETECT, 0);
            CheckMenuItem(pal_menu, IDM_COUNTRY_NTSC, 0);
            CheckMenuItem(pal_menu, IDM_COUNTRY_PAL, 8u);
            country_setting = 1;
            cfg_save_settings();
            return 1;
          case IDM_SAVE_STATE_1:
            *(uint32_t *)save_load_state_slot = 10;
            goto LABEL_41;
          case IDM_SAVE_STATE_2:
            *(uint32_t *)save_load_state_slot = 11;
            goto LABEL_41;
          case IDM_SAVE_STATE_3:
            *(uint32_t *)save_load_state_slot = 12;
            goto LABEL_41;
          case IDM_SAVE_STATE_4:
            *(uint32_t *)save_load_state_slot = 13;
            goto LABEL_41;
          case IDM_SAVE_STATE_5:
            *(uint32_t *)save_load_state_slot = 14;
            goto LABEL_41;
          case IDM_LOAD_STATE_1:
            *(uint32_t *)save_load_state_slot = 0;
            goto LABEL_41;
          case IDM_LOAD_STATE_2:
            *(uint32_t *)save_load_state_slot = 1;
            goto LABEL_41;
          case IDM_LOAD_STATE_3:
            *(uint32_t *)save_load_state_slot = 2;
            goto LABEL_41;
          case IDM_LOAD_STATE_4:
            *(uint32_t *)save_load_state_slot = 3;
            goto LABEL_41;
          case IDM_LOAD_STATE_5:
            *(uint32_t *)save_load_state_slot = 4;
            goto LABEL_41;
          case IDM_CONFIG_GUIDE_EN:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com/step/step.html", nullptr, nullptr, 3);
            return 1;
          case IDM_CONFIG_GUIDE_ES:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com/step/step_sp.html", nullptr, nullptr, 3);
            return 1;
          case IDM_NETPLAY:
            DialogBoxParamA(g_hInstance, "IDD_NET", hWnd, search_net_plugin, 0);
            return 1;
          case IDM_WIZARD_GUIDE:
            setup_wizard_step = 0;
            setup_wizard_callback(hWnd);
            return 1;
          case IDM_PPF_AUTOLOAD:
            ppf_enabled ^= 1u;
            ppf_menu = GetMenu(hWnd);
            if ( ppf_enabled )
              CheckMenuItem(ppf_menu, IDM_PPF_AUTOLOAD, 8u);
            else
              CheckMenuItem(ppf_menu, IDM_PPF_AUTOLOAD, 0);
            goto LABEL_83;
          case IDM_HELP_CONTENTS:
            ShellExecuteA(hWnd, "open", "epsxe.chm", nullptr, nullptr, 3);
            return 1;
          case IDM_ENABLE_LOGS:
            console_allocated ^= 1u;
            logs_menu = GetMenu(hWnd);
            if ( console_allocated )
              CheckMenuItem(logs_menu, IDM_ENABLE_LOGS, 8u);
            else
              CheckMenuItem(logs_menu, IDM_ENABLE_LOGS, 0);
            if ( (uint8_t)console_allocated > 1u )
              console_allocated = 1;
            goto LABEL_83;
          case IDM_PAD3:
            pad_number_menu_selection = 3;
            if ( !multitap_1 )
              return 1;
            cap_dc3 = GetDC(hWnd);
            device_caps3 = GetDeviceCaps(cap_dc3, 88);
            ReleaseDC(hWnd, cap_dc3);
            dialog_parent2 = hWnd;
            if ( device_caps3 <= 96 )
            {
LABEL_70:
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", hWnd, controller_setup_callback, 0);
              goto LABEL_68;
            }
LABEL_71:
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", dialog_parent2, controller_setup_callback, 0);
            ret = 1;
            break;
          case IDM_PAD4:
            pad_number_menu_selection = 4;
            if ( !multitap_1 )
              return 1;
            cap_dc4 = GetDC(hWnd);
            device_caps = GetDeviceCaps(cap_dc4, 88);
            ReleaseDC(hWnd, cap_dc4);
            dialog_parent = hWnd;
LABEL_65:
            if ( device_caps > 96 )
            {
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", dialog_parent, controller_setup_callback, 0);
LABEL_68:
              ret = 1;
            }
            else
            {
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", dialog_parent, controller_setup_callback, 0);
              ret = 1;
            }
            break;
          case IDM_MULTITAP:
            multitap_1 ^= 1u;
            multitap_menu = GetMenu(hWnd);
            if ( multitap_1 )
            {
              EnableMenuItem(multitap_menu, IDM_PAD3, 0);
              EnableMenuItem(multitap_menu, IDM_PAD4, 0);
              CheckMenuItem(multitap_menu, IDM_MULTITAP, 8u);
            }
            else
            {
              CheckMenuItem(multitap_menu, IDM_MULTITAP, 0);
              EnableMenuItem(multitap_menu, IDM_PAD3, 3u);
              EnableMenuItem(multitap_menu, IDM_PAD4, 3u);
            }
LABEL_83:
            cfg_save_settings();
            return 1;
          default:
            return 1;
        }
        break;
      case 0x116u:
        popup_menu = GetMenu(hWnd);
        if ( !multitap_1 )
        {
          EnableMenuItem(popup_menu, IDM_PAD3, 3u);
          EnableMenuItem(popup_menu, IDM_PAD4, 3u);
        }
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_CONFIG_VIDEO, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_CONFIG_SOUND, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_CONFIG_CDROM, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_WIZARD_GUIDE, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_NETPLAY, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_CONFIG_BIOS, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_PAD1, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(popup_menu, IDM_PAD2, 3u);
        if ( g_bDisableMouse
          || (EnableMenuItem(popup_menu, IDM_PAD3, 3u), g_bDisableMouse)
          || (EnableMenuItem(popup_menu, IDM_PAD4, 3u), g_bDisableMouse)
          || (EnableMenuItem(popup_menu, IDM_MULTITAP, 3u), g_bDisableMouse)
          || (EnableMenuItem(popup_menu, IDM_RUN_CDROM, 3u), g_bDisableMouse)
          || (EnableMenuItem(popup_menu, IDM_RUN_BIOS, 3u), g_bDisableMouse)
          || (EnableMenuItem(popup_menu, IDM_RUN_ISO, 3u), g_bDisableMouse)
          || (EnableMenuItem(popup_menu, IDM_RUN_PS_EXE, 3u), g_bDisableMouse) )
        {
LABEL_122:
          EnableMenuItem(popup_menu, IDM_CHANGE_DISC_CDROM, 3u);
        }
        else
        {
          EnableMenuItem(popup_menu, IDM_CHANGE_DISC_CDROM, 0);
        }
        if ( g_bDisableMouse )
          EnableMenuItem(popup_menu, IDM_CHANGE_DISC_ISO, 3u);
        else
          EnableMenuItem(popup_menu, IDM_CHANGE_DISC_ISO, 0);
        if ( g_bDisableMouse )
          EnableMenuItem(popup_menu, IDM_CONTINUE, 3u);
        else
          EnableMenuItem(popup_menu, IDM_CONTINUE, 0);
        if ( g_bDisableMouse )
          EnableMenuItem(popup_menu, IDM_RESET, 3u);
        else
          EnableMenuItem(popup_menu, IDM_RESET, 0);
        if ( g_bDisableMouse )
        {
          EnableMenuItem(popup_menu, IDM_PPF_AUTOLOAD, 0);
          if ( ppf_enabled )
            CheckMenuItem(popup_menu, IDM_PPF_AUTOLOAD, 8u);
          else
            CheckMenuItem(popup_menu, IDM_PPF_AUTOLOAD, 0);
        }
        else
        {
          EnableMenuItem(popup_menu, IDM_PPF_AUTOLOAD, 3u);
        }
        if ( g_bDisableMouse )
        {
          EnableMenuItem(popup_menu, IDM_MULTITAP, 0);
          if ( multitap_1 )
            CheckMenuItem(popup_menu, IDM_MULTITAP, 8u);
          else
            CheckMenuItem(popup_menu, IDM_MULTITAP, 0);
        }
        else
        {
          EnableMenuItem(popup_menu, IDM_MULTITAP, 3u);
        }
        if ( g_bDisableMouse )
        {
          EnableMenuItem(popup_menu, IDM_ENABLE_LOGS, 0);
          if ( console_allocated )
            CheckMenuItem(popup_menu, IDM_ENABLE_LOGS, 8u);
          else
            CheckMenuItem(popup_menu, IDM_ENABLE_LOGS, 0);
        }
        else
        {
          EnableMenuItem(popup_menu, IDM_ENABLE_LOGS, 3u);
        }
        if ( g_bDisableMouse )
        {
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_1, 3u);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_2, 3u);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_3, 3u);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_4, 3u);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_5, 3u);
          EnableMenuItem(popup_menu, IDM_LOAD_STATE_1, 3u);
          EnableMenuItem(popup_menu, IDM_LOAD_STATE_2, 3u);
          EnableMenuItem(popup_menu, IDM_LOAD_STATE_3, 3u);
          EnableMenuItem(popup_menu, IDM_LOAD_STATE_4, 3u);
          EnableMenuItem(popup_menu, IDM_LOAD_STATE_5, 3u);
          CheckMenuItem(popup_menu, IDM_COUNTRY_AUTODETECT, 0);
          CheckMenuItem(popup_menu, IDM_COUNTRY_NTSC, 0);
          CheckMenuItem(popup_menu, IDM_COUNTRY_PAL, 0);
          switch ( country_setting )
          {
            case 0:
              CheckMenuItem(popup_menu, IDM_COUNTRY_NTSC, 8u);
              return 1;
            case 1:
              CheckMenuItem(popup_menu, IDM_COUNTRY_PAL, 8u);
              ret = 1;
              break;
            case 255:
              CheckMenuItem(popup_menu, IDM_COUNTRY_AUTODETECT, 8u);
              ret = 1;
              break;
            default:
              return 1;
          }
        }
        else
        {
          EnableMenuItem(popup_menu, IDM_COUNTRY_AUTODETECT, 3u);
          EnableMenuItem(popup_menu, IDM_COUNTRY_NTSC, 3u);
          EnableMenuItem(popup_menu, IDM_COUNTRY_PAL, 3u);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_1, 0);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_2, 0);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_3, 0);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_4, 0);
          EnableMenuItem(popup_menu, IDM_SAVE_STATE_5, 0);
          LOBYTE(state0_exists) = check_state_exists(0);
          if ( state0_exists )
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_1, 3u);
          else
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_1, 0);
          LOBYTE(state1_exists) = check_state_exists(1u);
          if ( state1_exists )
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_2, 3u);
          else
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_2, 0);
          LOBYTE(state2_exists) = check_state_exists(2u);
          if ( state2_exists )
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_3, 3u);
          else
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_3, 0);
          LOBYTE(state3_exists) = check_state_exists(3u);
          if ( state3_exists )
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_4, 3u);
          else
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_4, 0);
          LOBYTE(state4_exists) = check_state_exists(4u);
          if ( state4_exists )
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_5, 3u);
          else
            EnableMenuItem(popup_menu, IDM_LOAD_STATE_5, 0);
          ret = 1;
        }
        break;
      default:
LABEL_178:
        ret = DefWindowProcA(hWnd, Msg, wParam, lParam);
        break;
    }
  }
  else if ( Msg == 15 )
  {
    ValidateRect(hWnd, nullptr);
    if ( main_window_bitmap )
    {
      hdc = GetDC(hWnd);
      CompatibleDC = CreateCompatibleDC(hdc);
      SelectObject(CompatibleDC, h);
      StretchBlt(hdc, 0, 0, 400, 255, CompatibleDC, 0, 0, 10, 10, 0xCC0020u);
      SelectObject(CompatibleDC, main_window_bitmap);
      BitBlt(hdc, 50, 30, 400, 300, CompatibleDC, 0, 0, 0xCC0020u);
      ReleaseDC(hWnd, hdc);
      DeleteDC(CompatibleDC);
      return 1;
    }
    else
    {
      return 1;
    }
  }
  else
  {
    switch ( Msg )
    {
      case 1u:
        if ( !setup_wizard_required )
          return 1;
        setup_wizard_required = 0;
        setup_wizard_step = 0;
        setup_wizard_callback(hWnd);
        ret = 1;
        break;
      case 2u:
        ui_error(" * Going out from gui (destroy). \n");
      case 6u:
      case 8u:
        return 1;
      case 7u:
        ShowWindow(hWnd, 1);
        return 1;
      default:
        goto LABEL_178;
    }
  }
  return ret;
}

static BOOL register_win_class()
{
  WNDCLASSEXA wc;

  wc.cbSize = 48;
  wc.style = 0;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hIcon = LoadIconA(nullptr, (LPCSTR)IDI_APP);
  wc.hIconSm = LoadIconA(g_hInstance, (LPCSTR)IDI_APP);
  wc.hCursor = nullptr;
  wc.hInstance = g_hInstance;
  wc.lpfnWndProc = main_window_callback;
  wc.hbrBackground = (HBRUSH)GetStockObject(0);
  wc.lpszMenuName = "EPSXMENU";
  wc.lpszClassName = "EPSXGUI";
  return RegisterClassExA(&wc) != 0;
}

BOOL create_main_window()
{
  HWND window;

  shift_key_pressed = 0;
  g_hInstance = GetModuleHandleA(nullptr);
  if ( !register_win_class() )
    ui_error(" * Error registering window.\n");
  main_window_bitmap = LoadBitmapA(g_hInstance, (LPCSTR)IDB_MAIN_WINDOW);
  h = LoadBitmapA(g_hInstance, (LPCSTR)IDB_MAIN_WINDOW_BG);
  window = CreateWindowExA(
             0,
             "EPSXGUI",
             " ePSXe - Enhanced PSX emulator",
             0xA0000u,
             0,
             0,
             400,
             300,
             nullptr,
             nullptr,
             g_hInstance,
             nullptr);
  g_hWnd = window;
  if ( !window )
    ui_error(" * Error creating window.\n");
  ShowWindow(window, 5);
  UpdateWindow(g_hWnd);
  while ( GetMessageA(&stru_8A94E0, nullptr, 0, 0) )
  {
    TranslateMessage(&stru_8A94E0);
    DispatchMessageA(&stru_8A94E0);
  }
  return ShowWindow(g_hWnd, 0);
}

void save_load_state()
{
  int count;
  char freeze_counter;
  char gpu_freeze_counter;

  *(uint32_t *)save_load_state_slot = 255;
  shift_key_pressed = 0;
  spu_mute_flag = 1;
  count = 20;
  do
  {
    spu_update_cb();
    Sleep(10u);
    --count;
  }
  while ( count );
  spu_update_cb();
  sio_memcard_both_save();
  spu_close();
  net_pause();
  gpu_close();
  if ( hOutputWnd )
    ShowWindow(hOutputWnd, 0);
  ShowWindow(g_hWnd, 5);
  ShowCursor(1);
  UpdateWindow(g_hWnd);
  while ( GetMessageA(&stru_8A94E0, nullptr, 0, 0) )
  {
    TranslateMessage(&stru_8A94E0);
    DispatchMessageA(&stru_8A94E0);
  }
  ShowCursor(0);
  ShowWindow(g_hWnd, 0);
  gpu_close_output_window();
  gpu_create_output_window();
  if ( hOutputWnd )
    ShowWindow(hOutputWnd, 5);
  gpu_open();
  net_resume();
  spu_open();
  spu_mute_flag = 0;
  if ( *(int *)save_load_state_slot >= 10 )
  {
    if ( *(int *)save_load_state_slot < 20 )
    {
      gpu_freeze_counter = get_gpu_freeze_counter();
      set_gpu_freeze_counter(save_load_state_slot[0] - 10);
      state_save();
      dbg_print(" * SaveState Done! (%d)\n", *(uint32_t *)save_load_state_slot - 10);
      set_gpu_freeze_counter(gpu_freeze_counter);
      PostQuitMessage(0);
    }
  }
  else
  {
    freeze_counter = get_gpu_freeze_counter();
    set_gpu_freeze_counter(save_load_state_slot[0]);
    state_load();
    dynarec_invalidate();
    dbg_print(" * LoadState Done! (%d)\n", *(uint32_t *)save_load_state_slot);
    set_gpu_freeze_counter(freeze_counter);
  }
}
