#include "pch.h"
int __stdcall output_win_callback(HWND hWnd, UINT a2, WPARAM a3, LPARAM a4)
{
  int result; // eax

  if ( a2 > 0xF )
  {
    switch ( a2 )
    {
      case 0x100u:
        byte_50AA60[a3] = 1;
        return 0;
      case 0x101u:
        byte_50AA60[a3] = 0;
        return 0;
      case 0x200u:
        sub_40E2C0();
        return 1;
      default:
        return DefWindowProcA(hWnd, a2, a3, a4);
    }
  }
  else if ( a2 == 15 )
  {
    ValidateRect(hWnd, nullptr);
    return 1;
  }
  else
  {
    switch ( a2 )
    {
      case 1u:
        return 1;
      case 2u:
        memcard12_save();
        PostQuitMessage(0);
        result = 1;
        break;
      case 6u:
        sub_40E1D0();
        result = 1;
        break;
      case 7u:
        ShowWindow(hWnd, 1);
        result = 1;
        break;
      case 8u:
        sub_40E240();
        result = 1;
        break;
      default:
        return DefWindowProcA(hWnd, a2, a3, a4);
    }
  }
  return result;
}
