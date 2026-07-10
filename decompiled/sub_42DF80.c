#include "pch.h"
BOOL sub_42DF80()
{
  ChangeDisplaySettingsA(nullptr, 0);
  ShowCursor(1);
  if ( dword_4FD98C && !DestroyWindow(dword_4FD98C) )
  {
    MessageBoxA(nullptr, aCouldNotReleas, aShutdownError, 0x40u);
    dword_4FD98C = nullptr;
  }
  return UnregisterClassA(aEpsx, dword_50AE4C);
}
