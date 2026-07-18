#include "pch.h"
int diAcquireAllDevices()
{
  if ( g_pJoystickDevices[0] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[0] + 28))(g_pJoystickDevices[0]);
  if ( g_pJoystickDevices[1] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[1] + 28))(g_pJoystickDevices[1]);
  if ( g_pJoystickDevices[2] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[2] + 28))(g_pJoystickDevices[2]);
  if ( g_pJoystickDevices[3] )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[3] + 28))(g_pJoystickDevices[3]);
  if ( g_pMouseDevice )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pMouseDevice + 28))(g_pMouseDevice);
  if ( g_pKeyboardDevice )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pKeyboardDevice + 28))(g_pKeyboardDevice);
  g_bDevicesAcquired = 1;
  return 1;
}
