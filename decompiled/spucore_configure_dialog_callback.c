#include "pch.h"
INT_PTR __stdcall sub_407740(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  if ( a2 != 272 )
  {
    if ( a2 != 273 || (_WORD)a3 != 1105 )
      return 0;
    EndDialog(hDlg, 1);
  }
  return 1;
}
