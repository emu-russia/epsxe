#include "pch.h"
HMODULE gpu_destroy()
{
  HMODULE result; // eax

  result = hGpuModule;
  if ( hGpuModule )
  {
    if ( !gpu_closed )
    {
      dbg_print(" * Closing gpu ...\n");
      GPUclose();
      gpu_closed = 1;
    }
    dbg_print(" * Shutdown gpu ...\n");
    GPUshutdown();
    ChangeDisplaySettingsA(nullptr, 0);
    ShowCursor(1);
    result = (HMODULE)hSaveLoadWnd;
    if ( hSaveLoadWnd )
    {
      result = (HMODULE)DestroyWindow(hSaveLoadWnd);
      if ( !result )
      {
        result = (HMODULE)MessageBoxA(nullptr, "Could NOT release hWnd.", "SHUTDOWN ERROR", 0x40u);
        hSaveLoadWnd = nullptr;
      }
    }
  }
  return result;
}
