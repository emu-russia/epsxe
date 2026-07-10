#include "pch.h"
INT_PTR __stdcall sub_409C00(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 == 272 )
    return 1;
  if ( a2 != 273 || (_WORD)a3 != 1114 )
    return 0;
  ++setup_wizard_step;
  EndDialog(hDlg, 1);
  return 1;
}
