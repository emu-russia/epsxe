#include "pch.h"
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
                (int)"Select Memcard FILE 2",
                (int)"MEMCARD FILE (*.MCR, *.MEM, *.MCD, *.GME)",
                (int)temp_path,
                (int)"memcards\\",
                (int)"MCR") )
          return 1;
        SetDlgItemTextA(hDlg, 1026, temp_path);
        result = 1;
        break;
      case 1083:
        if ( !open_file_dialog(
                (int)"Select Memcard FILE 1",
                (int)"MEMCARD FILE (*.MCR, *.MEM, *.MCD, *.GME)",
                (int)temp_path,
                (int)"memcards\\",
                (int)"MCR") )
          return 1;
        SetDlgItemTextA(hDlg, 1082, temp_path);
        result = 1;
        break;
      case 1084:
        GetDlgItemTextA(hDlg, 1082, (LPSTR)Memcard1, 1024);
        GetDlgItemTextA(hDlg, 1026, (LPSTR)Memcard2, 1024);
        if ( byte_4FC460 )
        {
          byte_4FC460 = 0;
          memcard_load();
        }
        EndDialog(hDlg, 1);
        save_settings();
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
