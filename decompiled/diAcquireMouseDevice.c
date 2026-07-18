#include "pch.h"
int diAcquireMouseDevice()
{
  if ( g_pMouseDevice && point_device_enabled )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pMouseDevice + 28))(g_pMouseDevice);
  return 1;
}
