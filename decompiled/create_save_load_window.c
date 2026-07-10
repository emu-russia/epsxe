#include "pch.h"
HWND create_save_load_window()
{
  dword_50AE4C = GetModuleHandleA(nullptr);
  if ( !register_save_load_win_class() )
    ui_error(aErrorRegisteri);
  dword_4FD98C = CreateWindowExA(
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
  if ( !dword_4FD98C )
    ui_error(aErrorCreatingW);
  ShowCursor(0);
  ShowWindow(dword_4FD98C, 5);
  SetForegroundWindow(dword_4FD98C);
  return SetFocus(dword_4FD98C);
}
