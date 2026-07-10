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
          case 0x9C41u:
            if ( !strcmp((const char *)VideoPlugin, "NULL") )
              goto LABEL_26;
            if ( !strcmp((const char *)CdromPlugin, "NULL") )
              goto LABEL_28;
            if ( sub_41C0B0() )
              goto LABEL_30;
            PostQuitMessage(0);
            if ( byte_45B8E8 )
              fastboot = 0;
            nocd = 1;
            sub_41C010("NULL");
            dword_50C37C = 1;
            byte_44DD19 = 0;
            return 1;
          case 0x9C42u:
            if ( !strcmp((const char *)VideoPlugin, "NULL") )
              goto LABEL_26;
            if ( !strcmp((const char *)CdromPlugin, "NULL") )
              goto LABEL_28;
            if ( sub_41C0B0() )
              goto LABEL_30;
            PostQuitMessage(0);
            fastboot = 0;
            nocd = 0;
            sub_41C010("NULL");
            dword_50C37C = 2;
            byte_44DD19 = 0;
            return 1;
          case 0x9C43u:
            if ( !strcmp((const char *)VideoPlugin, "NULL") )
            {
LABEL_26:
              MessageBoxA(nullptr, aEpsxeIsNotComp, aEpsxeNotConfig, 0x10u);
              return 1;
            }
            if ( !strcmp((const char *)CdromPlugin, "NULL") )
            {
LABEL_28:
              MessageBoxA(nullptr, aEpsxeIsNotComp_0, aEpsxeNotConfig, 0x10u);
              return 1;
            }
            if ( sub_41C0B0() )
            {
LABEL_30:
              MessageBoxA(nullptr, aEpsxeIsNotComp_1, aEpsxeNotConfig, 0x10u);
              return 1;
            }
            if ( !open_file_dialog(
                    (int)"Open PSX ISO",
                    (int)"PSX ISOs (*.BIN, *.ISO, *.IMG)",
                    (int)temp_path,
                    (int)byte_8B3980,
                    (int)"ISO") )
              return 1;
            GetFullPathNameA(temp_path, 0x400u, Buffer, &FilePart);
            *FilePart = 0;
            sprintf((char *const)byte_8B3980, "%s", temp_path);
            cdrom_iso_set_path();
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
            sub_41C010("NULL");
            dword_50C37C = 3;
            byte_44DD19 = 0;
            return 1;
          case 0x9C44u:
            if ( !open_file_dialog(
                    (int)"Open PSX EXE",
                    (int)"PSX EXEs (*.ZIP, *.EXE)",
                    (int)temp_path,
                    (int)asc_44B034,
                    (int)"EXE") )
              return 1;
            PostQuitMessage(0);
            sub_41C010(temp_path);
            dword_50C37C = 4;
            byte_44DD19 = 0;
            return 1;
          case 0x9C45u:
            ui_error(" * Going out from gui. (exit)\n");
          case 0x9C46u:
            DialogBoxParamA(g_hInstance, "IDD_VIDEO", hWnd, search_video_plugin, 0);
            return 1;
          case 0x9C47u:
            DialogBoxParamA(g_hInstance, "IDD_SOUND", hWnd, search_spu_plugin, 0);
            return 1;
          case 0x9C48u:
            DialogBoxParamA(g_hInstance, "IDD_CDROM", hWnd, search_cdrom_plugin, 0);
            return 1;
          case 0x9C49u:
            DialogBoxParamA(g_hInstance, "IDD_BIOS", hWnd, bios_dialog_callback, 0);
            return 1;
          case 0x9C4Cu:
            DialogBoxParamA(g_hInstance, "IDD_CHEAT", hWnd, (DLGPROC)cheat_dialog_callback, 0);
            goto LABEL_68;
          case 0x9C4Du:
            DialogBoxParamA(g_hInstance, "IDD_ABOUT", hWnd, (DLGPROC)about_callback, 0);
            goto LABEL_68;
          case 0x9C4Fu:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com", nullptr, nullptr, 3);
            return 1;
          case 0x9C50u:
            if ( dword_50C37C )
              goto LABEL_41;
            return 1;
          case 0x9C51u:
            if ( !dword_50C37C )
              return 1;
            dword_50C380 = 1;
            goto LABEL_41;
          case 0x9C52u:
            byte_44DD1A = 1;
            DC = GetDC(hWnd);
            DeviceCaps = GetDeviceCaps(DC, 88);
            ReleaseDC(hWnd, DC);
            v31 = hWnd;
            goto LABEL_65;
          case 0x9C53u:
            byte_44DD1A = 2;
            v15 = GetDC(hWnd);
            v16 = GetDeviceCaps(v15, 88);
            ReleaseDC(hWnd, v15);
            v32 = hWnd;
            if ( v16 <= 96 )
              goto LABEL_70;
            goto LABEL_71;
          case 0x9C56u:
            DialogBoxParamA(g_hInstance, "IDD_MEMCARD", hWnd, memcard_settings, 0);
            return 1;
          case 0x9C58u:
            cdrom_deinit_cb(Msg - 256);
            MessageBoxA(nullptr, "Insert a new cdrom and hit the button to continue", "Change Disc Option", 0x40u);
            nocd = 1;
            sub_41C010("NULL");
            dword_50C37C = 1;
            goto LABEL_40;
          case 0x9C59u:
            if ( !open_file_dialog(
                    (int)"Open PSX ISO",
                    (int)"PSX ISOs (*.BIN, *.ISO, *.IMG)",
                    (int)temp_path,
                    (int)byte_8B3980,
                    (int)"ISO") )
              return 1;
            GetFullPathNameA(temp_path, 0x400u, Buffer, &FilePart);
            *FilePart = 0;
            sprintf((char *const)byte_8B3980, "%s", temp_path);
            cdrom_iso_set_path();
            cdrom_deinit_cb(v9);
            v10 = 0;
            do
            {
              v11 = temp_path[v10];
              bin_iso_file[v10++] = v11;
            }
            while ( v11 );
            sub_41C010("NULL");
            dword_50C37C = 3;
LABEL_40:
            byte_44DD19 = 0;
            country_setting = 255;
            dword_4FC4CC();
            cdrom_init_cb();
            cdrom_detect_region();
            cdrom_subchannel_read_cb();
LABEL_41:
            PostQuitMessage(0);
            return 1;
          case 0x9C5Au:
            Menu = GetMenu(hWnd);
            CheckMenuItem(Menu, 0x9C5Au, 8u);
            CheckMenuItem(Menu, 0x9C5Bu, 0);
            CheckMenuItem(Menu, 0x9C5Cu, 0);
            country_setting = 255;
            save_settings();
            return 1;
          case 0x9C5Bu:
            v23 = GetMenu(hWnd);
            CheckMenuItem(v23, 0x9C5Au, 0);
            CheckMenuItem(v23, 0x9C5Bu, 0);
            CheckMenuItem(v23, 0x9C5Cu, 8u);
            country_setting = 0;
            save_settings();
            return 1;
          case 0x9C5Cu:
            v24 = GetMenu(hWnd);
            CheckMenuItem(v24, 0x9C5Au, 0);
            CheckMenuItem(v24, 0x9C5Bu, 0);
            CheckMenuItem(v24, 0x9C5Cu, 8u);
            country_setting = 1;
            save_settings();
            return 1;
          case 0x9C5Eu:
            *(_DWORD *)dword_44DF24 = 10;
            goto LABEL_41;
          case 0x9C5Fu:
            *(_DWORD *)dword_44DF24 = 11;
            goto LABEL_41;
          case 0x9C60u:
            *(_DWORD *)dword_44DF24 = 12;
            goto LABEL_41;
          case 0x9C61u:
            *(_DWORD *)dword_44DF24 = 13;
            goto LABEL_41;
          case 0x9C62u:
            *(_DWORD *)dword_44DF24 = 14;
            goto LABEL_41;
          case 0x9C63u:
            *(_DWORD *)dword_44DF24 = 0;
            goto LABEL_41;
          case 0x9C64u:
            *(_DWORD *)dword_44DF24 = 1;
            goto LABEL_41;
          case 0x9C65u:
            *(_DWORD *)dword_44DF24 = 2;
            goto LABEL_41;
          case 0x9C66u:
            *(_DWORD *)dword_44DF24 = 3;
            goto LABEL_41;
          case 0x9C67u:
            *(_DWORD *)dword_44DF24 = 4;
            goto LABEL_41;
          case 0x9C69u:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com/step/step.html", nullptr, nullptr, 3);
            return 1;
          case 0x9C6Au:
            ShellExecuteA(hWnd, "open", "http://www.epsxe.com/step/step_sp.html", nullptr, nullptr, 3);
            return 1;
          case 0x9C6Fu:
            DialogBoxParamA(g_hInstance, "IDD_NET", hWnd, (DLGPROC)search_net_plugin, 0);
            return 1;
          case 0x9C70u:
            setup_wizard_step = 0;
            setup_wizard_callback(hWnd);
            return 1;
          case 0x9C71u:
            auto_ppf_load ^= 1u;
            v21 = GetMenu(hWnd);
            if ( auto_ppf_load )
              CheckMenuItem(v21, 0x9C71u, 8u);
            else
              CheckMenuItem(v21, 0x9C71u, 0);
            goto LABEL_83;
          case 0x9C72u:
            ShellExecuteA(hWnd, "open", "epsxe.chm", nullptr, nullptr, 3);
            return 1;
          case 0x9C73u:
            console_allocated ^= 1u;
            v12 = GetMenu(hWnd);
            if ( console_allocated )
              CheckMenuItem(v12, 0x9C73u, 8u);
            else
              CheckMenuItem(v12, 0x9C73u, 0);
            if ( (unsigned __int8)console_allocated > 1u )
              console_allocated = 1;
            goto LABEL_83;
          case 0x9C74u:
            byte_44DD1A = 3;
            if ( !multitap_1 )
              return 1;
            v17 = GetDC(hWnd);
            v18 = GetDeviceCaps(v17, 88);
            ReleaseDC(hWnd, v17);
            v32 = hWnd;
            if ( v18 <= 96 )
            {
LABEL_70:
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", hWnd, (DLGPROC)sub_4043B0, 0);
              goto LABEL_68;
            }
LABEL_71:
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", v32, (DLGPROC)sub_4043B0, 0);
            result = 1;
            break;
          case 0x9C75u:
            byte_44DD1A = 4;
            if ( !multitap_1 )
              return 1;
            v19 = GetDC(hWnd);
            DeviceCaps = GetDeviceCaps(v19, 88);
            ReleaseDC(hWnd, v19);
            v31 = hWnd;
LABEL_65:
            if ( DeviceCaps > 96 )
            {
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", v31, (DLGPROC)sub_4043B0, 0);
LABEL_68:
              result = 1;
            }
            else
            {
              DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", v31, (DLGPROC)sub_4043B0, 0);
              result = 1;
            }
            break;
          case 0x9C76u:
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
            save_settings();
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
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C46u, 3u);
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C47u, 3u);
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C48u, 3u);
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C70u, 3u);
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C6Fu, 3u);
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C49u, 3u);
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C52u, 3u);
        if ( byte_44DD19 )
          goto LABEL_122;
        EnableMenuItem(v25, 0x9C53u, 3u);
        if ( byte_44DD19
          || (EnableMenuItem(v25, 0x9C74u, 3u), byte_44DD19)
          || (EnableMenuItem(v25, 0x9C75u, 3u), byte_44DD19)
          || (EnableMenuItem(v25, 0x9C76u, 3u), byte_44DD19)
          || (EnableMenuItem(v25, 0x9C41u, 3u), byte_44DD19)
          || (EnableMenuItem(v25, 0x9C42u, 3u), byte_44DD19)
          || (EnableMenuItem(v25, 0x9C43u, 3u), byte_44DD19)
          || (EnableMenuItem(v25, 0x9C44u, 3u), byte_44DD19) )
        {
LABEL_122:
          EnableMenuItem(v25, 0x9C58u, 3u);
        }
        else
        {
          EnableMenuItem(v25, 0x9C58u, 0);
        }
        if ( byte_44DD19 )
          EnableMenuItem(v25, 0x9C59u, 3u);
        else
          EnableMenuItem(v25, 0x9C59u, 0);
        if ( byte_44DD19 )
          EnableMenuItem(v25, 0x9C50u, 3u);
        else
          EnableMenuItem(v25, 0x9C50u, 0);
        if ( byte_44DD19 )
          EnableMenuItem(v25, 0x9C51u, 3u);
        else
          EnableMenuItem(v25, 0x9C51u, 0);
        if ( byte_44DD19 )
        {
          EnableMenuItem(v25, 0x9C71u, 0);
          if ( auto_ppf_load )
            CheckMenuItem(v25, 0x9C71u, 8u);
          else
            CheckMenuItem(v25, 0x9C71u, 0);
        }
        else
        {
          EnableMenuItem(v25, 0x9C71u, 3u);
        }
        if ( byte_44DD19 )
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
        if ( byte_44DD19 )
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
        if ( byte_44DD19 )
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
        if ( !byte_45B8E0 )
          return 1;
        byte_45B8E0 = 0;
        setup_wizard_step = 0;
        setup_wizard_callback(hWnd);
        result = 1;
        break;
      case 2u:
        ui_error(aGoingOutFromGu);
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
