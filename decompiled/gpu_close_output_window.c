#include "pch.h"
BOOL gpu_close_output_window()
{
  ChangeDisplaySettingsA(nullptr, 0);
  ShowCursor(1);
  if ( hOutputWnd && !DestroyWindow(hOutputWnd) )
  {
    MessageBoxA(nullptr, "Could Not Release hWnd.", "SHUTDOWN ERROR", 0x40u);
    hOutputWnd = nullptr;
  }
  return UnregisterClassA("EPSX", dword_50AE4C);
}
