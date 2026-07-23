#include "pch.h"
HWND create_output_window()
{
  dword_50AE4C = GetModuleHandleA(nullptr);
  if ( !gpu_register_output_win_class() )
    ui_error(" * Error registering window.\n");
  hOutputWnd = CreateWindowExA(
                 0x40100u,
                 "EPSX",
                 "ePSXe - Enhanced PSX emulator",
                 0x60A0000u,
                 0,
                 0,
                 640,
                 480,
                 nullptr,
                 nullptr,
                 dword_50AE4C,
                 nullptr);
  if ( !hOutputWnd )
    ui_error(" * Error creating window.\n");
  ShowCursor(0);
  ShowWindow(hOutputWnd, 5);
  SetForegroundWindow(hOutputWnd);
  return SetFocus(hOutputWnd);
}
