#include "pch.h"
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
