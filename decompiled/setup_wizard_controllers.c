#include "pch.h"
INT_PTR __stdcall setup_wizard_controllers(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  HDC DC; // esi
  int DeviceCaps; // ebx
  HDC v7; // esi
  int v8; // ebx

  switch ( a2 )
  {
    case 0x10u:
      setup_wizard_step = 8;
LABEL_16:
      EndDialog(hDlg, 1);
      return 1;
    case 0x110u:
      return 1;
    case 0x111u:
      switch ( (__int16)a3 )
      {
        case 1115:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case 1116:
          ++setup_wizard_step;
          goto LABEL_16;
        case 1117:
          pad_number_menu_selection = 1;
          DC = GetDC(hDlg);
          DeviceCaps = GetDeviceCaps(DC, 88);
          ReleaseDC(hDlg, DC);
          if ( DeviceCaps > 96 )
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", hDlg, controller_setup_callback, 0);
          else
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", hDlg, controller_setup_callback, 0);
          return 0;
        case 1118:
          pad_number_menu_selection = 2;
          v7 = GetDC(hDlg);
          v8 = GetDeviceCaps(v7, 88);
          ReleaseDC(hDlg, v7);
          if ( v8 <= 96 )
          {
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", hDlg, controller_setup_callback, 0);
            return 0;
          }
          DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", hDlg, controller_setup_callback, 0);
          break;
        default:
          return 0;
      }
      break;
  }
  return 0;
}
