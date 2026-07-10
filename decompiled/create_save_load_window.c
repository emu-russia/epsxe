#include "pch.h"
HWND create_save_load_window()
{
  dword_50AE4C = GetModuleHandleA(nullptr);
  if ( !register_save_load_win_class() )
    ui_error(aErrorRegisteri);
  hSaveLoadWnd = CreateWindowExA(
                   0x40100u,
                   aEpsx,
                   ConsoleTitle,
                   0x60A0000u,
                   0,
                   0,
                   640,
                   480,
                   nullptr,
                   nullptr,
                   dword_50AE4C,
                   nullptr);
  if ( !hSaveLoadWnd )
    ui_error(aErrorCreatingW);
  ShowCursor(0);
  ShowWindow(hSaveLoadWnd, 5);
  SetForegroundWindow(hSaveLoadWnd);
  return SetFocus(hSaveLoadWnd);
}
