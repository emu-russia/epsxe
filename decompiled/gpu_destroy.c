#include "pch.h"
HMODULE gpu_destroy()
{
  HMODULE result; // eax

  result = dword_4FD990;
  if ( dword_4FD990 )
  {
    if ( !gpu_closed )
    {
      dbg_print(aClosingGpu);
      GPUclose();
      gpu_closed = 1;
    }
    dbg_print(aShutdownGpu);
    GPUshutdown();
    ChangeDisplaySettingsA(nullptr, 0);
    ShowCursor(1);
    result = (HMODULE)dword_4FD98C;
    if ( dword_4FD98C )
    {
      result = (HMODULE)DestroyWindow(dword_4FD98C);
      if ( !result )
      {
        result = (HMODULE)MessageBoxA(nullptr, aCouldNotReleas_0, aShutdownError, 0x40u);
        dword_4FD98C = nullptr;
      }
    }
  }
  return result;
}
