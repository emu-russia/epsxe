#include "pch.h"
int diShutdownDirectInput()
{
  int *v0; // esi
  int result; // eax

  diUnacquireAllDevices();
  if ( g_pKeyboardDevice )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pKeyboardDevice + 8))(g_pKeyboardDevice);
  g_pKeyboardDevice = 0;
  v0 = g_pJoystickDevices;
  do
  {
    if ( *v0 )
      (*(void (__stdcall **)(int))(*(_DWORD *)*v0 + 8))(*v0);
    *v0++ = 0;
  }
  while ( (int)v0 < (int)&byte_4F777C );
  result = (*(int (__stdcall **)(int))(*(_DWORD *)g_pDirectInput + 8))(g_pDirectInput);
  g_pDirectInput = 0;
  g_uiNumJoysticks = 0;
  return result;
}
