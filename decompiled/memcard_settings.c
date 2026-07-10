#include "pch.h"
INT_PTR __stdcall sub_407DD0(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  INT_PTR result; // eax

  if ( a2 == 272 )
  {
    SetDlgItemTextA(hDlg, 1082, (LPCSTR)&byte_8B3180);
    SetDlgItemTextA(hDlg, 1026, (LPCSTR)&byte_8B3580);
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
                (int)aSelectMemcardF_0,
                (int)aMemcardFileMcr,
                (int)byte_8B1560,
                (int)aMemcards,
                (int)&off_44E628) )
          return 1;
        SetDlgItemTextA(hDlg, 1026, byte_8B1560);
        result = 1;
        break;
      case 1083:
        if ( !open_file_dialog(
                (int)aSelectMemcardF,
                (int)aMemcardFileMcr,
                (int)byte_8B1560,
                (int)aMemcards,
                (int)&off_44E628) )
          return 1;
        SetDlgItemTextA(hDlg, 1082, byte_8B1560);
        result = 1;
        break;
      case 1084:
        GetDlgItemTextA(hDlg, 1082, (LPSTR)&byte_8B3180, 1024);
        GetDlgItemTextA(hDlg, 1026, (LPSTR)&byte_8B3580, 1024);
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
