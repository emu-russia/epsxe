#include "pch.h"
int diInitDirectInput()
{
  HRESULT hr; // edi
  CHAR Text[256]; // [esp+8h] [ebp-100h] BYREF

  hr = DirectInputCreateA(hInst_For_DInput, 0x700, (int)&g_pDirectInput, 0);
  if ( hr >= 0 )
  {
    if ( (*(int (__stdcall **)(int, GUID *, int *, _DWORD))(*(_DWORD *)g_pDirectInput + 12))(
           g_pDirectInput,
           &GUID_Keyboard,
           &g_pKeyboardDevice,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, char *))(*(_DWORD *)g_pKeyboardDevice + 44))(
           g_pKeyboardDevice,
           &g_KeyboardDataFormat) < 0 )
      return 0;
    (*(void (__stdcall **)(int, int, int))(*(_DWORD *)g_pKeyboardDevice + 52))(g_pKeyboardDevice, hDlgInput, 6);
    if ( !point_device_enabled || g_bDisableMouse )
      goto LABEL_25;
    if ( (*(int (__stdcall **)(int, GUID *, int *, _DWORD))(*(_DWORD *)g_pDirectInput + 12))(
           g_pDirectInput,
           &GUID_Mouse,
           &g_pMouseDevice,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, char *))(*(_DWORD *)g_pMouseDevice + 44))(g_pMouseDevice, &g_MouseDataFormat) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, int, int))(*(_DWORD *)g_pMouseDevice + 52))(g_pMouseDevice, hDlgInput, 5) >= 0 )
    {
LABEL_25:
      g_pJoystickDevices[0] = 0;
      g_pJoystickDevices[1] = 0;
      g_pJoystickDevices[2] = 0;
      g_pJoystickDevices[3] = 0;
      (*(void (__stdcall **)(int, int, int (*)(int, _DWORD *, int), int, int))(*(_DWORD *)g_pDirectInput + 16))(
        g_pDirectInput,
        4,
        diEnumDevicesCallback,
        g_pDirectInput,
        1);
      if ( (g_PlayerDeviceMap1[0] && g_PlayerDeviceMap1[0] <= 4u
         || g_PlayerDeviceMap2 && (unsigned int)g_PlayerDeviceMap2 <= 4
         || g_PlayerDeviceMap3 && (unsigned int)g_PlayerDeviceMap3 <= 4
         || g_PlayerDeviceMap4[0] && g_PlayerDeviceMap4[0] <= 4u)
        && (*(int (__stdcall **)(int, int, int (*)(int, _DWORD *, int), int, int))(*(_DWORD *)g_pDirectInput + 16))(
             g_pDirectInput,
             4,
             diEnumDevicesCallback,
             g_pDirectInput,
             257) < 0 )
      {
        printf(" * No force-feedback joysticks available. \n");
      }
      diAcquireAllDevices();
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    sprintf(Text, "Error initializing DirectInput\n");
    MessageBoxA(nullptr, Text, "Init Error", 0x10u);
    if ( hr > DIERR_OLDDIRECTINPUTVERSION )
    {
      if ( hr != DIERR_BETADIRECTINPUTVERSION )
      {
LABEL_10:
        sprintf(Text, "UNKNOWN %X\n", hr);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      sprintf(Text, "Beta %X\n", DIERR_BETADIRECTINPUTVERSION);
    }
    else
    {
      if ( hr == DIERR_OLDDIRECTINPUTVERSION )
      {
        sprintf(Text, "OLDDIRECTINPUTVERSION %X\n", DIERR_OLDDIRECTINPUTVERSION);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      if ( hr != DIERR_OUTOFMEMORY )
      {
        if ( hr == DIERR_INVALIDPARAM )
        {
          sprintf(Text, "Invalid %X\n", DIERR_INVALIDPARAM);
          MessageBoxA(nullptr, Text, "Init", 0x10u);
          return 0;
        }
        goto LABEL_10;
      }
      sprintf(Text, "OUTOFMEMORY %X\n", DIERR_OUTOFMEMORY);
    }
    MessageBoxA(nullptr, Text, "Init", 0x10u);
    return 0;
  }
}
