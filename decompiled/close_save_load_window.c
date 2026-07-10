#include "pch.h"
BOOL close_save_load_window()
{
  ChangeDisplaySettingsA(nullptr, 0);
  ShowCursor(1);
  if ( hSaveLoadWnd && !DestroyWindow(hSaveLoadWnd) )
  {
    MessageBoxA(nullptr, "Could Not Release hWnd.", "SHUTDOWN ERROR", 0x40u);
    hSaveLoadWnd = nullptr;
  }
  return UnregisterClassA("EPSX", dword_50AE4C);
}
