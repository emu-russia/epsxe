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
    result = (HMODULE)hOutputWnd;
    if ( hOutputWnd )
    {
      result = (HMODULE)DestroyWindow(hOutputWnd);
      if ( !result )
      {
        result = (HMODULE)MessageBoxA(nullptr, "Could NOT release hWnd.", "SHUTDOWN ERROR", 0x40u);
        hOutputWnd = nullptr;
      }
    }
  }
  return result;
}
