#include "pch.h"
int diUnacquireAllDevices()
{
  if ( g_pMouseDevice && point_device_enabled )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pMouseDevice + 32))(g_pMouseDevice);
  if ( g_pKeyboardDevice )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pKeyboardDevice + 32))(g_pKeyboardDevice);
  if ( g_pJoystickDevices[0] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[0] + 32))(g_pJoystickDevices[0]);
  if ( g_pJoystickDevices[1] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[1] + 32))(g_pJoystickDevices[1]);
  if ( g_pJoystickDevices[2] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[2] + 32))(g_pJoystickDevices[2]);
  if ( g_pJoystickDevices[3] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[3] + 32))(g_pJoystickDevices[3]);
  g_bDevicesAcquired = 0;
  return 1;
}
