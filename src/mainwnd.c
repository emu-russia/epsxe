#include "pch.h"
LRESULT __stdcall main_window_callback(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  LRESULT result; // eax
  HDC v5; // edi
  HDC CompatibleDC; // esi
  int v7; // eax
  char v8; // cl
  int v9; // ecx
  int v10; // eax
  char v11; // cl
  HMENU v12; // eax
  HDC DC; // esi
  int DeviceCaps; // ebp
  HDC v15; // esi
  int v16; // ebp
  HDC v17; // edi
  int v18; // ebp
  HDC v19; // edi
  HMENU v20; // esi
  HMENU v21; // eax
  HMENU Menu; // esi
  HMENU v23; // esi
  HMENU v24; // esi
  HMENU v25; // esi
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  HWND v31; // [esp-Ch] [ebp-420h]
  HWND v32; // [esp-Ch] [ebp-420h]
  LPSTR FilePart; // [esp+10h] [ebp-404h] BYREF
  CHAR Buffer[1024]; // [esp+14h] [ebp-400h] BYREF

  if ( Msg > 0xF )
  {
    switch ( Msg )
    {
      case 0x100u:
        if ( wParam == 16 )
          byte_45B8E8 = 1;
        result = 0;
        break;
      case 0x101u:
        if ( wParam == 16 )
          byte_45B8E8 = 0;
        result = 0;
        break;
      case 0x111u:
        switch ( (unsigned __int16)wParam )
        {
          case 40001u:
            if ( !strcmp((const char *)VideoPlugin, "NULL") )
              goto LABEL_26;
            if ( !strcmp((const char *)CdromPlugin, "NULL") )
              goto LABEL_28;
            if ( loader_check_bios_file_exists() )
              goto LABEL_30;
            PostQuitMessage(0);
            if ( byte_45B8E8 )
              fastboot = 0;
            nocd = 1;
            loader_set_filename("NULL");
            loaded_file_type = 1;
            g_bDisableMouse = 0;
            return 1;
          case 40002u:
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
          case 40003u:
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
            if ( byte_45B8E8 )
              fastboot = 0;
            v7 = 0;
            do
            {
              v8 = temp_path[v7];
              bin_iso_file[v7++] = v8;
            }
            while ( v8 );
            loader_set_filename("NULL");
            loaded_file_type = 3;
            g_bDisableMouse = 0;
            return 1;
          case 40004u:
            if ( !open_file_dialog("Open PSX EXE", "PSX EXEs (*.ZIP, *.EXE)", temp_path, ".", "EXE") )
              return 1;
            PostQuitMessage(0);
            loader_set_filename(temp_path);
            loaded_file_type = 4;
            g_bDisableMouse = 0;
            return 1;
          case 40005u:
            ui_error(" * Going out from gui. (exit)\n");
          case 40006u:
            DialogBoxParamA(g_hInstance, "IDD_VIDEO", hWnd, search_video_plugin, 0);
            return 1;
          case 40007u:
            DialogBoxParamA(g_hInstance, "IDD_SOUND", hWnd, search_spu_plugin, 0);
            return 1;
          case 40008u:
            DialogBoxParamA(g_hInstance, "IDD_CDROM", hWnd, search_cdrom_plugin, 0);
            return 1;
          case 40009u:
            DialogBoxParamA(g_hInstance, "IDD_BIOS", hWnd, bios_dialog_callback, 0);
            return 1;
          case 40012u:
            DialogBoxParamA(g_hInstance, "IDD_CHEAT", hWnd, (DLGPROC)cheat_dialog_callback, 0);
            goto LABEL_68;
          case 40013u:
            DialogBoxParamA(g_hInstance, "IDD_ABOUT", hWnd, (DLGPROC)about_callback, 0);
            goto LABEL_68;
          case 40015u:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com", nullptr, nullptr, 3);
            return 1;
          case 40016u:
            if ( loaded_file_type )
              goto LABEL_41;
            return 1;
          case 40017u:
            if ( !loaded_file_type )
              return 1;
            reset_flag = 1;
            goto LABEL_41;
          case 40018u:
            pad_number_menu_selection = 1;
            DC = GetDC(hWnd);
            DeviceCaps = GetDeviceCaps(DC, 88);
            ReleaseDC(hWnd, DC);
            v31 = hWnd;
            goto LABEL_65;
          case 40019u:
            pad_number_menu_selection = 2;
            v15 = GetDC(hWnd);
            v16 = GetDeviceCaps(v15, 88);
            ReleaseDC(hWnd, v15);
            v32 = hWnd;
            if ( v16 <= 96 )
              goto LABEL_70;
            goto LABEL_71;
          case 40022u:
            DialogBoxParamA(g_hInstance, "IDD_MEMCARD", hWnd, memcard_settings, 0);
            return 1;
          case 40024u:
            cdrom_deinit_cb(Msg - 256);
            MessageBoxA(nullptr, "Insert a new cdrom and hit the button to continue", "Change Disc Option", 0x40u);
            nocd = 1;
            loader_set_filename("NULL");
            loaded_file_type = 1;
            goto LABEL_40;
          case 40025u:
            if ( !open_file_dialog("Open PSX ISO", "PSX ISOs (*.BIN, *.ISO, *.IMG)", temp_path, IsoDirectory, "ISO") )
              return 1;
            GetFullPathNameA(temp_path, 0x400u, Buffer, &FilePart);
            *FilePart = 0;
            sprintf(IsoDirectory, "%s", temp_path);
            cfg_cdrom_iso_set_path();
            cdrom_deinit_cb(v9);
            v10 = 0;
            do
            {
              v11 = temp_path[v10];
              bin_iso_file[v10++] = v11;
            }
            while ( v11 );
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
          case 40026u:
            Menu = GetMenu(hWnd);
            CheckMenuItem(Menu, 0x9C5Au, 8u);
            CheckMenuItem(Menu, 0x9C5Bu, 0);
            CheckMenuItem(Menu, 0x9C5Cu, 0);
            country_setting = 255;
            cfg_save_settings();
            return 1;
          case 40027u:
            v23 = GetMenu(hWnd);
            CheckMenuItem(v23, 0x9C5Au, 0);
            CheckMenuItem(v23, 0x9C5Bu, 0);
            CheckMenuItem(v23, 0x9C5Cu, 8u);
            country_setting = 0;
            cfg_save_settings();
            return 1;
          case 40028u:
            v24 = GetMenu(hWnd);
            CheckMenuItem(v24, 0x9C5Au, 0);
            CheckMenuItem(v24, 0x9C5Bu, 0);
            CheckMenuItem(v24, 0x9C5Cu, 8u);
            country_setting = 1;
            cfg_save_settings();
            return 1;
          case 40030u:
            *(_DWORD *)dword_44DF24 = 10;
            goto LABEL_41;
          case 40031u:
            *(_DWORD *)dword_44DF24 = 11;
            goto LABEL_41;
          case 40032u:
            *(_DWORD *)dword_44DF24 = 12;
            goto LABEL_41;
          case 40033u:
            *(_DWORD *)dword_44DF24 = 13;
            goto LABEL_41;
          case 40034u:
            *(_DWORD *)dword_44DF24 = 14;
            goto LABEL_41;
          case 40035u:
            *(_DWORD *)dword_44DF24 = 0;
            goto LABEL_41;
          case 40036u:
            *(_DWORD *)dword_44DF24 = 1;
            goto LABEL_41;
          case 40037u:
            *(_DWORD *)dword_44DF24 = 2;
            goto LABEL_41;
          case 40038u:
            *(_DWORD *)dword_44DF24 = 3;
            goto LABEL_41;
          case 40039u:
            *(_DWORD *)dword_44DF24 = 4;
            goto LABEL_41;
          case 40041u:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com/step/step.html", nullptr, nullptr, 3);
            return 1;
          case 40042u:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com/step/step_sp.html", nullptr, nullptr, 3);
            return 1;
          case 40047u:
            DialogBoxParamA(g_hInstance, "IDD_NET", hWnd, search_net_plugin, 0);
            return 1;
          case 40048u:
            setup_wizard_step = 0;
            setup_wizard_callback(hWnd);
            return 1;
          case 40049u:
            ppf_enabled ^= 1u;
            v21 = GetMenu(hWnd);
            if ( ppf_enabled )
              CheckMenuItem(v21, 0x9C71u, 8u);
            else
              CheckMenuItem(v21, 0x9C71u, 0);
            goto LABEL_83;
          case 40050u:
            ShellExecuteA(hWnd, "open", "epsxe.chm", nullptr, nullptr, 3);
            return 1;
          case 40051u:
            console_allocated ^= 1u;
            v12 = GetMenu(hWnd);
            if ( console_allocated )
              CheckMenuItem(v12, 0x9C73u, 8u);
            else
              CheckMenuItem(v12, 0x9C73u, 0);
            if ( (unsigned __int8)console_allocated > 1u )
              console_allocated = 1;
            goto LABEL_83;
          case 40052u:
            pad_number_menu_selection = 3;
            if ( !multitap_1 )
              return 1;
            v17 = GetDC(hWnd);
            v18 = GetDeviceCaps(v17, 88);
            ReleaseDC(hWnd, v17);
            v32 = hWnd;
            if ( v18 <= 96 )
            {
LABEL_70:
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", hWnd, controller_setup_callback, 0);
              goto LABEL_68;
            }
LABEL_71:
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", v32, controller_setup_callback, 0);
            result = 1;
            break;
          case 40053u:
            pad_number_menu_selection = 4;
            if ( !multitap_1 )
              return 1;
            v19 = GetDC(hWnd);
            DeviceCaps = GetDeviceCaps(v19, 88);
            ReleaseDC(hWnd, v19);
            v31 = hWnd;
LABEL_65:
            if ( DeviceCaps > 96 )
            {
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", v31, controller_setup_callback, 0);
LABEL_68:
              result = 1;
            }
            else
            {
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", v31, controller_setup_callback, 0);
              result = 1;
            }
            break;
          case 40054u:
            multitap_1 ^= 1u;
            v20 = GetMenu(hWnd);
            if ( multitap_1 )
            {
              EnableMenuItem(v20, 0x9C74u, 0);
              EnableMenuItem(v20, 0x9C75u, 0);
              CheckMenuItem(v20, 0x9C76u, 8u);
            }
            else
            {
              CheckMenuItem(v20, 0x9C76u, 0);
              EnableMenuItem(v20, 0x9C74u, 3u);
              EnableMenuItem(v20, 0x9C75u, 3u);
            }
LABEL_83:
            cfg_save_settings();
            return 1;
          default:
            return 1;
        }
        break;
      case 0x116u:
        v25 = GetMenu(hWnd);
        if ( !multitap_1 )
        {
          EnableMenuItem(v25, 0x9C74u, 3u);
          EnableMenuItem(v25, 0x9C75u, 3u);
        }
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C46u, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C47u, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C48u, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C70u, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C6Fu, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C49u, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C52u, 3u);
        if ( g_bDisableMouse )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C53u, 3u);
        if ( g_bDisableMouse
          || (EnableMenuItem(v25, 0x9C74u, 3u), g_bDisableMouse)
          || (EnableMenuItem(v25, 0x9C75u, 3u), g_bDisableMouse)
          || (EnableMenuItem(v25, 0x9C76u, 3u), g_bDisableMouse)
          || (EnableMenuItem(v25, 0x9C41u, 3u), g_bDisableMouse)
          || (EnableMenuItem(v25, 0x9C42u, 3u), g_bDisableMouse)
          || (EnableMenuItem(v25, 0x9C43u, 3u), g_bDisableMouse)
          || (EnableMenuItem(v25, 0x9C44u, 3u), g_bDisableMouse) )
        {
LABEL_122:
          EnableMenuItem(v25, 0x9C58u, 3u);
        }
        else
        {
          EnableMenuItem(v25, 0x9C58u, 0);
        }
        if ( g_bDisableMouse )
          EnableMenuItem(v25, 0x9C59u, 3u);
        else
          EnableMenuItem(v25, 0x9C59u, 0);
        if ( g_bDisableMouse )
          EnableMenuItem(v25, 0x9C50u, 3u);
        else
          EnableMenuItem(v25, 0x9C50u, 0);
        if ( g_bDisableMouse )
          EnableMenuItem(v25, 0x9C51u, 3u);
        else
          EnableMenuItem(v25, 0x9C51u, 0);
        if ( g_bDisableMouse )
        {
          EnableMenuItem(v25, 0x9C71u, 0);
          if ( ppf_enabled )
            CheckMenuItem(v25, 0x9C71u, 8u);
          else
            CheckMenuItem(v25, 0x9C71u, 0);
        }
        else
        {
          EnableMenuItem(v25, 0x9C71u, 3u);
        }
        if ( g_bDisableMouse )
        {
          EnableMenuItem(v25, 0x9C76u, 0);
          if ( multitap_1 )
            CheckMenuItem(v25, 0x9C76u, 8u);
          else
            CheckMenuItem(v25, 0x9C76u, 0);
        }
        else
        {
          EnableMenuItem(v25, 0x9C76u, 3u);
        }
        if ( g_bDisableMouse )
        {
          EnableMenuItem(v25, 0x9C73u, 0);
          if ( console_allocated )
            CheckMenuItem(v25, 0x9C73u, 8u);
          else
            CheckMenuItem(v25, 0x9C73u, 0);
        }
        else
        {
          EnableMenuItem(v25, 0x9C73u, 3u);
        }
        if ( g_bDisableMouse )
        {
          EnableMenuItem(v25, 0x9C5Eu, 3u);
          EnableMenuItem(v25, 0x9C5Fu, 3u);
          EnableMenuItem(v25, 0x9C60u, 3u);
          EnableMenuItem(v25, 0x9C61u, 3u);
          EnableMenuItem(v25, 0x9C62u, 3u);
          EnableMenuItem(v25, 0x9C63u, 3u);
          EnableMenuItem(v25, 0x9C64u, 3u);
          EnableMenuItem(v25, 0x9C65u, 3u);
          EnableMenuItem(v25, 0x9C66u, 3u);
          EnableMenuItem(v25, 0x9C67u, 3u);
          CheckMenuItem(v25, 0x9C5Au, 0);
          CheckMenuItem(v25, 0x9C5Bu, 0);
          CheckMenuItem(v25, 0x9C5Cu, 0);
          switch ( country_setting )
          {
            case 0:
              CheckMenuItem(v25, 0x9C5Bu, 8u);
              return 1;
            case 1:
              CheckMenuItem(v25, 0x9C5Cu, 8u);
              result = 1;
              break;
            case 255:
              CheckMenuItem(v25, 0x9C5Au, 8u);
              result = 1;
              break;
            default:
              return 1;
          }
        }
        else
        {
          EnableMenuItem(v25, 0x9C5Au, 3u);
          EnableMenuItem(v25, 0x9C5Bu, 3u);
          EnableMenuItem(v25, 0x9C5Cu, 3u);
          EnableMenuItem(v25, 0x9C5Eu, 0);
          EnableMenuItem(v25, 0x9C5Fu, 0);
          EnableMenuItem(v25, 0x9C60u, 0);
          EnableMenuItem(v25, 0x9C61u, 0);
          EnableMenuItem(v25, 0x9C62u, 0);
          LOBYTE(v26) = check_state_exists(0);
          if ( v26 )
            EnableMenuItem(v25, 0x9C63u, 3u);
          else
            EnableMenuItem(v25, 0x9C63u, 0);
          LOBYTE(v27) = check_state_exists(1u);
          if ( v27 )
            EnableMenuItem(v25, 0x9C64u, 3u);
          else
            EnableMenuItem(v25, 0x9C64u, 0);
          LOBYTE(v28) = check_state_exists(2u);
          if ( v28 )
            EnableMenuItem(v25, 0x9C65u, 3u);
          else
            EnableMenuItem(v25, 0x9C65u, 0);
          LOBYTE(v29) = check_state_exists(3u);
          if ( v29 )
            EnableMenuItem(v25, 0x9C66u, 3u);
          else
            EnableMenuItem(v25, 0x9C66u, 0);
          LOBYTE(v30) = check_state_exists(4u);
          if ( v30 )
            EnableMenuItem(v25, 0x9C67u, 3u);
          else
            EnableMenuItem(v25, 0x9C67u, 0);
          result = 1;
        }
        break;
      default:
LABEL_178:
        result = DefWindowProcA(hWnd, Msg, wParam, lParam);
        break;
    }
  }
  else if ( Msg == 15 )
  {
    ValidateRect(hWnd, nullptr);
    if ( dword_45B8D8 )
    {
      v5 = GetDC(hWnd);
      CompatibleDC = CreateCompatibleDC(v5);
      SelectObject(CompatibleDC, h);
      StretchBlt(v5, 0, 0, 400, 255, CompatibleDC, 0, 0, 10, 10, 0xCC0020u);
      SelectObject(CompatibleDC, dword_45B8D8);
      BitBlt(v5, 50, 30, 400, 300, CompatibleDC, 0, 0, 0xCC0020u);
      ReleaseDC(hWnd, v5);
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
        result = 1;
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
  return result;
}

BOOL register_win_class()
{
  WNDCLASSEXA v1; // [esp+8h] [ebp-30h] BYREF

  v1.cbSize = 48;
  v1.style = 0;
  v1.cbClsExtra = 0;
  v1.cbWndExtra = 0;
  v1.hIcon = LoadIconA(nullptr, (LPCSTR)0x89);
  v1.hIconSm = LoadIconA(g_hInstance, (LPCSTR)0x89);
  v1.hCursor = nullptr;
  v1.hInstance = g_hInstance;
  v1.lpfnWndProc = main_window_callback;
  v1.hbrBackground = (HBRUSH)GetStockObject(0);
  v1.lpszMenuName = "EPSXMENU";
  v1.lpszClassName = "EPSXGUI";
  return RegisterClassExA(&v1) != 0;
}

BOOL create_main_window()
{
  HWND Window; // eax

  byte_45B8E8 = 0;
  g_hInstance = GetModuleHandleA(nullptr);
  if ( !register_win_class() )
    ui_error(" * Error registering window.\n");
  dword_45B8D8 = LoadBitmapA(g_hInstance, (LPCSTR)0x8C);
  h = LoadBitmapA(g_hInstance, (LPCSTR)0x8E);
  Window = CreateWindowExA(
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
  g_hWnd = Window;
  if ( !Window )
    ui_error(" * Error creating window.\n");
  ShowWindow(Window, 5);
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
  int v0; // esi
  char v1; // [esp+8h] [ebp-4h]
  char gpu_freeze_counter; // [esp+8h] [ebp-4h]

  *(_DWORD *)dword_44DF24 = 255;
  byte_45B8E8 = 0;
  dword_4F7594 = 1;
  v0 = 20;
  do
  {
    spu_update_cb();
    Sleep(10u);
    --v0;
  }
  while ( v0 );
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
  dword_4F7594 = 0;
  if ( *(int *)dword_44DF24 >= 10 )
  {
    if ( *(int *)dword_44DF24 < 20 )
    {
      gpu_freeze_counter = get_gpu_freeze_counter();
      set_gpu_freeze_counter(dword_44DF24[0] - 10);
      state_save();
      dbg_print(" * SaveState Done! (%d)\n", *(_DWORD *)dword_44DF24 - 10);
      set_gpu_freeze_counter(gpu_freeze_counter);
      PostQuitMessage(0);
    }
  }
  else
  {
    v1 = get_gpu_freeze_counter();
    set_gpu_freeze_counter(dword_44DF24[0]);
    state_load();
    dynarec_invalidate();
    dbg_print(" * LoadState Done! (%d)\n", *(_DWORD *)dword_44DF24);
    set_gpu_freeze_counter(v1);
  }
}

