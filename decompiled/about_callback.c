#include "pch.h"
int __stdcall sub_405D70(HWND hDlg, int a2, __int16 a3, int a4)
{
  if ( a2 == 272 )
    return 1;
  if ( a2 == 273 && a3 == 1002 )
  {
    EndDialog(hDlg, 1);
    return 1;
  }
  return 0;
}
