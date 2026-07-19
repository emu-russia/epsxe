#include "pch.h"
int __cdecl setup_wizard_callback(HWND hWndParent)
{
  int result; // eax

  byte_8A94C0 = 0;
  while ( 2 )
  {
    result = setup_wizard_step;
    switch ( setup_wizard_step )
    {
      case 0:
        setup_wizard_init();
        DialogBoxParamA(g_hInstance, "IDD_INSTALL", hWndParent, setup_wizard_begin, 0);
        continue;
      case 1:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_BIOS", hWndParent, setup_wizard_search_bios, 0);
        continue;
      case 2:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_GPU", hWndParent, setup_wizard_search_video_plugin, 0);
        continue;
      case 3:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_SPU", hWndParent, setup_wizard_search_spu_plugin, 0);
        continue;
      case 4:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_CDROM", hWndParent, setup_wizard_search_cdrom_plugin, 0);
        continue;
      case 5:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_PAD", hWndParent, setup_wizard_controllers, 0);
        continue;
      case 6:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_END", hWndParent, setup_wizard_end, 0);
        continue;
      case 7:
        sprintf((char *const)VideoPlugin, "%s", byte_8A84C0);
        sprintf((char *const)SoundPlugin, "%s", byte_8A88C0);
        sprintf((char *const)CdromPlugin, "%s", byte_8A8CC0);
        sprintf((char *const)bios_name, "%s", byte_8A90C0);
        result = cfg_save_settings();
        break;
      default:
        return result;
    }
    break;
  }
  return result;
}
