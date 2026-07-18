#include "pch.h"
int diGetMouseState()
{
  int v1; // eax
  int v2; // eax
  _DWORD v3[3]; // [esp+Ch] [ebp-14h] BYREF
  _BYTE v4[8]; // [esp+18h] [ebp-8h]

  if ( !point_device_enabled )
    return 0;
  v1 = g_pMouseDevice;
  g_MouseX = 0;
  g_MouseY[0] = 0;
  if ( g_pMouseDevice && g_bDevicesAcquired == 1 )
  {
    while ( 1 )
    {
      v2 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v1 + 36))(v1, 16, v3);
      if ( v2 != DIERR_INPUTLOST )
        break;
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)g_pMouseDevice + 28))(g_pMouseDevice) < 0 )
        return 0;
      v1 = g_pMouseDevice;
    }
    if ( v2 < 0 )
      return 0;
    g_MouseX = 3 * v3[0];
    g_MouseY[0] = 3 * v3[1];
    g_MouseButtons = (v4[3] | ((v4[2] | ((unsigned int)(v4[1] | (v4[0] >> 1)) >> 1)) >> 1)) >> 4;
  }
  return 1;
}
