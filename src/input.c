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

int diAcquireMouseDevice()
{
  if ( g_pMouseDevice && point_device_enabled )
    (*(void (__stdcall **)(int))(*(_DWORD *)g_pMouseDevice + 28))(g_pMouseDevice);
  return 1;
}

static int diGetMouseState()
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

static int __stdcall diEnumEffectsCallback(_DWORD *a1, _DWORD *a2)
{
  if ( a2 )
  {
    *a2 = a1[1];
    a2[1] = a1[2];
    a2[2] = a1[3];
    a2[3] = a1[4];
  }
  return 0;
}

static unsigned int __cdecl diCreateEffectHelper(int a1, _DWORD *a2)
{
  int v3; // [esp+8h] [ebp-1Ch]
  _BYTE v4[16]; // [esp+14h] [ebp-10h] BYREF

  if ( *a2 )
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*a2 + 8))(*a2);
  v3 = a2[1];
  *a2 = 0;
  if ( (*(int (__stdcall **)(int, int (__stdcall *)(_DWORD *, _DWORD *), _BYTE *, int))(*(_DWORD *)a1 + 76))(
         a1,
         diEnumEffectsCallback,
         v4,
         v3) >= 0 )
    return (*(int (__stdcall **)(int, _BYTE *, _DWORD *, _DWORD *, _DWORD))(*(_DWORD *)a1 + 72))(a1, v4, a2 + 2, a2, 0) >= 0
         ? 0
         : 0x80004005;
  else
    return 0x80004005;
}

static unsigned int __cdecl diSetupConstantForceEffect(int a1, int a2)
{
  _DWORD *v2; // eax
  int v3; // edx
  _DWORD v5[2]; // [esp+0h] [ebp-10h] BYREF
  _DWORD v6[2]; // [esp+8h] [ebp-8h] BYREF

  v2 = (_DWORD *)a1;
  if ( !a1 )
    return E_FAIL;
  v3 = a2;
  if ( !a2 )
    return E_FAIL;
  *(_DWORD *)(a1 + 40) = v5;
  v2[5] = 0;
  v2[8] = 0;
  v2[11] = v6;
  v5[0] = 0;
  v6[0] = 0;
  v6[1] = 0;
  v2[12] = 0;
  v2[7] = -1;
  a1 = 10000;
  v5[1] = 4;
  v2[3] = 34;
  v2[4] = 20000;
  v2[9] = 2;
  v2[13] = 4;
  v2[14] = &a1;
  v2[1] = 1;
  return (diCreateEffectHelper(v3, v2) & 0x80000000) == 0 ? 0 : 0x80004005;
}

static unsigned int __cdecl diSetupPeriodicForceEffect(_DWORD *a1, int a2)
{
  int v3; // [esp+0h] [ebp-20h] BYREF
  int v4; // [esp+8h] [ebp-18h] BYREF
  _DWORD v5[4]; // [esp+10h] [ebp-10h] BYREF

  if ( !a1 || !a2 )
    return E_FAIL;
  a1[5] = 0;
  a1[8] = 0;
  a1[17] = 0;
  a1[18] = 0;
  a1[19] = 0;
  v5[1] = 0;
  v5[2] = 0;
  v3 = 0;
  v4 = 0;
  a1[10] = &v3;
  a1[12] = a1 + 16;
  a1[7] = -1;
  a1[11] = &v4;
  a1[20] = 1000000;
  v5[0] = 10000;
  v5[3] = 100000;
  a1[3] = 18;
  a1[4] = 20000;
  a1[9] = 1;
  a1[13] = 16;
  a1[14] = v5;
  a1[1] = 3;
  return (diCreateEffectHelper(a2, a1) & 0x80000000) == 0 ? 0 : E_FAIL;
}

static int __cdecl diSetConstantForceMagnitude(int a1, int a2)
{
  _DWORD *v2; // ebx
  int v3; // esi
  _DWORD v5[14]; // [esp+8h] [ebp-38h] BYREF

  v2 = (_DWORD *)a1;
  if ( !a1 )
    return E_INVALIDARG;
  v3 = *(_DWORD *)a1;
  if ( !*(_DWORD *)a1 )
    return E_INVALIDARG;
  memset(v5, 0, sizeof(v5));
  a1 = 10000 * a2 / 255;
  v5[0] = 56;
  v5[11] = 4;
  v5[12] = &a1;
  (*(void (__stdcall **)(int, _DWORD *, int))(*(_DWORD *)v3 + 24))(v3, v5, 256);
  return (*(int (__stdcall **)(_DWORD, int, _DWORD))(*(_DWORD *)*v2 + 28))(*v2, 1, 0);
}

static int __cdecl diSetPeriodicForceMagnitude(_DWORD *a1, int a2)
{
  int v2; // esi
  int v4; // [esp+8h] [ebp-48h] BYREF
  _DWORD v5[14]; // [esp+18h] [ebp-38h] BYREF

  if ( !a1 )
    return E_INVALIDARG;
  v2 = *a1;
  if ( !*a1 )
    return E_INVALIDARG;
  memset(v5, 0, sizeof(v5));
  v4 = 10000 * a2 / 255;
  v5[0] = 56;
  v5[11] = 16;
  v5[12] = &v4;
  (*(void (__stdcall **)(int, _DWORD *, int))(*(_DWORD *)v2 + 24))(v2, v5, 256);
  return (*(int (__stdcall **)(_DWORD, int, _DWORD))(*(_DWORD *)*a1 + 28))(*a1, 1, 0);
}

static _DWORD *__cdecl diInitEffectStruct(_DWORD *a1)
{
  memset(a1 + 2, 0, 0x38u);
  a1[2] = 56;
  a1[6] = 7500;
  a1[16] = 0;
  a1[17] = 0;
  a1[18] = 0;
  a1[19] = 0;
  a1[20] = 0;
  a1[16] = 20;
  *a1 = 0;
  return a1 + 16;
}

int __cdecl diSetEffectMagnitude(int a1, int a2, int a3, int a4)
{
  int result; // eax

  if ( a1 )
  {
    result = g_EffectType1[a4];
    if ( result == 1 )
    {
      return diSetConstantForceMagnitude(g_MouseY[g_PlayerDeviceMap1[a4]], a2);
    }
    else if ( result == 2 )
    {
      return diSetPeriodicForceMagnitude((_DWORD *)g_MouseY[g_PlayerDeviceMap1[a4]], a2);
    }
  }
  else
  {
    result = g_EffectType2[a4];
    if ( result == 1 )
    {
      return diSetConstantForceMagnitude(force_feedback_effect_handles2[g_PlayerDeviceMap1[a4]], a2);
    }
    else if ( result == 2 )
    {
      return diSetPeriodicForceMagnitude((_DWORD *)force_feedback_effect_handles2[g_PlayerDeviceMap1[a4]], a2);
    }
  }
  return result;
}

static int diEnumDevicesCallback(int a1, _DWORD *a2, int a3)
{
  int v3; // ebp
  int v4; // edx
  int i; // eax
  int *v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  bool v11; // sf
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // ecx
  int *v37; // eax
  int v38; // eax
  int v39; // ebp
  char *v40; // [esp+C4h] [ebp-64h]
  _DWORD v41[4]; // [esp+D8h] [ebp-50h] BYREF
  int v42; // [esp+E8h] [ebp-40h] BYREF
  int v43; // [esp+ECh] [ebp-3Ch]
  int v44; // [esp+F0h] [ebp-38h]
  int v45; // [esp+F4h] [ebp-34h]
  int v46; // [esp+F8h] [ebp-30h]
  _DWORD v47[5]; // [esp+FCh] [ebp-2Ch] BYREF
  int v48; // [esp+110h] [ebp-18h] BYREF
  _DWORD v49[2]; // [esp+114h] [ebp-14h] BYREF
  int v50; // [esp+11Ch] [ebp-Ch]
  int v51; // [esp+120h] [ebp-8h]
  int v52; // [esp+124h] [ebp-4h]
  int a1a; // [esp+12Ch] [ebp+4h]

  v4 = *(_DWORD *)(a1 + 8);
  v41[0] = *(_DWORD *)(a1 + 4);
  v41[2] = *(_DWORD *)(a1 + 12);
  v41[1] = v4;
  v41[3] = *(_DWORD *)(a1 + 16);
  a1a = -1;
  if ( (unsigned int)g_uiNumJoysticks <= 3 )
  {
    for ( i = 0; i < 4; ++i )
    {
      if ( g_PlayerDeviceMap1[i] == g_uiNumJoysticks + 1 )
        a1a = i;
    }
    if ( !(*(int (__stdcall **)(_DWORD *, _DWORD *, GUID *, int, _DWORD))(*a2 + 36))(
            a2,
            v41,
            &GUID_Joystick,
            4 * g_uiNumJoysticks + 5207916,
            0) )
    {
      if ( (*(int (__stdcall **)(int, char *))(*(_DWORD *)g_pJoystickDevices[g_uiNumJoysticks] + 44))(
             g_pJoystickDevices[g_uiNumJoysticks],
             &g_JoystickDataFormat)
        || ((v7 = (int *)g_pJoystickDevices[g_uiNumJoysticks], v8 = *v7, a1a == -1)
          ? (v9 = (*(int (__stdcall **)(int *, int, int))(v8 + 52))(v7, hDlgInput, 6))
          : (v9 = (*(int (__stdcall **)(int *, int, int))(v8 + 52))(v7, hDlgInput, 5)),
            v9) )
      {
        (*(void (__stdcall **)(int))(*(_DWORD *)g_pJoystickDevices[g_uiNumJoysticks] + 8))(g_pJoystickDevices[g_uiNumJoysticks]);
        return 1;
      }
      v10 = g_pJoystickDevices[g_uiNumJoysticks];
      v48 = 24;
      v49[0] = 16;
      v49[1] = 0;
      v50 = 1;
      v51 = -128;
      v52 = 127;
      v11 = (*(int (__stdcall **)(int, int, int *, int))(*(_DWORD *)v10 + 24))(v10, 4, &v48, v3) < 0;
      v12 = g_uiNumJoysticks;
      if ( v11 )
      {
        g_JoystickStateFlags[g_uiNumJoysticks] = 1;
        joystick_axis_1_positive_triggered[v12] = 1;
      }
      v13 = g_pJoystickDevices[v12];
      v50 = 4;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v13 + 24))(v13, 4, v49) < 0;
      v14 = g_uiNumJoysticks;
      if ( v11 )
      {
        joystick_axis_1_negative_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_2_positive_triggered[v14] = 1;
      }
      v15 = g_pJoystickDevices[v14];
      v50 = 8;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v15 + 24))(v15, 4, v49) < 0;
      v16 = g_uiNumJoysticks;
      if ( v11 )
      {
        joystick_z_axis_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_2_negative_triggered[v16] = 1;
      }
      v17 = g_pJoystickDevices[v16];
      v50 = 12;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v17 + 24))(v17, 4, v49) < 0;
      v18 = g_uiNumJoysticks;
      if ( v11 )
      {
        joystick_axis_3_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_3_negative_triggered[v18] = 1;
      }
      v19 = g_pJoystickDevices[v18];
      v50 = 16;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v19 + 24))(v19, 4, v49) < 0;
      v20 = g_uiNumJoysticks;
      if ( v11 )
      {
        joystick_axis_4_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_4_negative_triggered[v20] = 1;
      }
      v21 = g_pJoystickDevices[v20];
      v50 = 20;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v21 + 24))(v21, 4, v49) < 0;
      v22 = g_uiNumJoysticks;
      if ( v11 )
      {
        joystick_axis_5_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_5_negative_triggered[v22] = 1;
      }
      v23 = g_pJoystickDevices[v22];
      v50 = 24;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v23 + 24))(v23, 4, v49) < 0;
      v24 = g_uiNumJoysticks;
      if ( v11 )
      {
        joystick_axis_6_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_6_negative_triggered[v24] = 1;
      }
      v25 = g_pJoystickDevices[v24];
      v50 = 28;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v25 + 24))(v25, 4, v49) < 0;
      v26 = g_uiNumJoysticks;
      if ( v11 )
      {
        joystick_axis_7_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_7_negative_triggered[v26] = 1;
      }
      v27 = g_pJoystickDevices[v26];
      v43 = 20;
      v44 = 16;
      v46 = 1;
      v47[0] = 2500;
      v45 = 0;
      (*(void (__stdcall **)(int, int))(*(_DWORD *)v27 + 24))(v27, 5);
      v28 = g_pJoystickDevices[g_uiNumJoysticks];
      v44 = 4;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v28 + 24))(v28, 5, &v42);
      v29 = g_pJoystickDevices[g_uiNumJoysticks];
      v44 = 8;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v29 + 24))(v29, 5, &v42);
      v30 = g_pJoystickDevices[g_uiNumJoysticks];
      v44 = 12;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v30 + 24))(v30, 5, &v42);
      v31 = g_pJoystickDevices[g_uiNumJoysticks];
      v44 = 16;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v31 + 24))(v31, 5, &v42);
      v32 = g_pJoystickDevices[g_uiNumJoysticks];
      v44 = 20;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v32 + 24))(v32, 5, &v42);
      v33 = g_pJoystickDevices[g_uiNumJoysticks];
      v44 = 24;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v33 + 24))(v33, 5, &v42);
      v34 = g_pJoystickDevices[g_uiNumJoysticks];
      v44 = 28;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v34 + 24))(v34, 5, &v42);
      v42 = 20;
      v43 = 16;
      v45 = 0;
      v46 = 0;
      v44 = 0;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)g_pJoystickDevices[g_uiNumJoysticks] + 24))(
        g_pJoystickDevices[g_uiNumJoysticks],
        2,
        &v42);
      if ( a1a != -1 )
      {
        v35 = g_pJoystickDevices[g_uiNumJoysticks];
        v47[0] = 20;
        v47[1] = 16;
        memset(&v47[2], 0, 12);
        (*(void (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v35 + 24))(v35, 9, v47);
        v36 = g_uiNumJoysticks;
        v37 = &g_EffectBuffer2[25 * g_uiNumJoysticks];
        v40 = &g_EffectBuffer1[100 * g_uiNumJoysticks];
        g_pEffectStructs[g_uiNumJoysticks] = (int)v40;
        g_pEffectStructs2[v36] = (int)v37;
        diInitEffectStruct(v40);
        diInitEffectStruct((_DWORD *)g_pEffectStructs2[g_uiNumJoysticks]);
        *(_DWORD *)(g_pEffectStructs[g_uiNumJoysticks] + 24) = 100 * g_EffectScaleFactor;
        *(_DWORD *)(g_pEffectStructs2[g_uiNumJoysticks] + 24) = 100 * g_EffectScaleFactor;
        v38 = g_EffectType1[a1a];
        if ( v38 == 1 )
        {
          diSetupConstantForceEffect(g_pEffectStructs[g_uiNumJoysticks], g_pJoystickDevices[g_uiNumJoysticks]);
        }
        else if ( v38 == 2 )
        {
          diSetupPeriodicForceEffect((_DWORD *)g_pEffectStructs[g_uiNumJoysticks], g_pJoystickDevices[g_uiNumJoysticks]);
        }
        v39 = g_EffectType2[a1a];
        if ( v39 == 1 )
        {
          diSetupConstantForceEffect(g_pEffectStructs2[g_uiNumJoysticks], g_pJoystickDevices[g_uiNumJoysticks]);
        }
        else if ( v39 == 2 )
        {
          diSetupPeriodicForceEffect(
            (_DWORD *)g_pEffectStructs2[g_uiNumJoysticks],
            g_pJoystickDevices[g_uiNumJoysticks]);
        }
      }
      ++g_uiNumJoysticks;
    }
  }
  return 1;
}

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

int diUpdateJoystickStates()
{
  char *v0; // edi
  int i; // esi
  int result; // eax
  int v3; // eax

  v0 = g_JoystickStateBuffer;
  for ( i = 0; ; ++i )
  {
    result = g_pJoystickDevices[i];
    if ( result )
      break;
LABEL_97:
    v0 += 80;
    if ( (int)v0 >= (int)g_EffectBuffer2 )
      return result;
  }
  (*(void (__stdcall **)(int))(*(_DWORD *)result + 100))(g_pJoystickDevices[i]);
  if ( (*(int (__stdcall **)(int, int, char *))(*(_DWORD *)g_pJoystickDevices[i] + 36))(g_pJoystickDevices[i], 80, v0) != -2147024866 )
    goto LABEL_8;
  v3 = g_pJoystickDevices[i];
  if ( v3 )
    (*(void (__stdcall **)(int))(*(_DWORD *)v3 + 28))(g_pJoystickDevices[i]);
  result = (*(int (__stdcall **)(int, int, char *))(*(_DWORD *)g_pJoystickDevices[i] + 36))(
             g_pJoystickDevices[i],
             80,
             v0);
  if ( result >= 0 )
  {
LABEL_8:
    if ( !g_JoystickStateFlags[i] && *(int *)v0 > 0 )
      g_JoystickStateFlags[i] = 1;
    if ( !joystick_axis_1_positive_triggered[i] && *(int *)v0 < 0 )
      joystick_axis_1_positive_triggered[i] = 1;
    if ( !joystick_axis_1_negative_triggered[i] && *((int *)v0 + 1) > 0 )
      joystick_axis_1_negative_triggered[i] = 1;
    if ( !joystick_axis_2_positive_triggered[i] && *((int *)v0 + 1) < 0 )
      joystick_axis_2_positive_triggered[i] = 1;
    if ( !joystick_z_axis_positive_triggered[i] && *((int *)v0 + 2) > 0 )
      joystick_z_axis_positive_triggered[i] = 1;
    if ( !joystick_axis_2_negative_triggered[i] && *((int *)v0 + 2) < 0 )
      joystick_axis_2_negative_triggered[i] = 1;
    if ( !joystick_axis_4_positive_triggered[i] && *((int *)v0 + 4) > 0 )
      joystick_axis_4_positive_triggered[i] = 1;
    if ( !joystick_axis_4_negative_triggered[i] && *((int *)v0 + 4) < 0 )
      joystick_axis_4_negative_triggered[i] = 1;
    if ( !joystick_axis_5_positive_triggered[i] && *((int *)v0 + 5) > 0 )
      joystick_axis_5_positive_triggered[i] = 1;
    if ( !joystick_axis_5_negative_triggered[i] && *((int *)v0 + 5) < 0 )
      joystick_axis_5_negative_triggered[i] = 1;
    if ( !joystick_axis_6_positive_triggered[i] && *((int *)v0 + 6) > 0 )
      joystick_axis_6_positive_triggered[i] = 1;
    if ( !joystick_axis_6_negative_triggered[i] && *((int *)v0 + 6) < 0 )
      joystick_axis_6_negative_triggered[i] = 1;
    if ( !joystick_axis_7_positive_triggered[i] && *((int *)v0 + 7) > 0 )
      joystick_axis_7_positive_triggered[i] = 1;
    if ( !joystick_axis_7_negative_triggered[i] && *((int *)v0 + 7) < 0 )
      joystick_axis_7_negative_triggered[i] = 1;
    if ( !joystick_button_1_triggered[i] && v0[48] )
      joystick_button_1_triggered[i] = 1;
    if ( !joystick_button_2_triggered[i] && v0[49] )
      joystick_button_2_triggered[i] = 1;
    if ( !joystick_button_3_triggered[i] && v0[50] )
      joystick_button_3_triggered[i] = 1;
    if ( !joystick_button_4_triggered[i] && v0[51] )
      joystick_button_4_triggered[i] = 1;
    if ( !joystick_button_5_triggered[i] && v0[52] )
      joystick_button_5_triggered[i] = 1;
    if ( !joystick_button_6_triggered[i] && v0[53] )
      joystick_button_6_triggered[i] = 1;
    if ( !joystick_button_7_triggered[i] && v0[54] )
      joystick_button_7_triggered[i] = 1;
    if ( !joystick_button_8_triggered[i] && v0[55] )
      joystick_button_8_triggered[i] = 1;
    if ( !joystick_button_9_triggered[i] && v0[56] )
      joystick_button_9_triggered[i] = 1;
    if ( !joystick_button_10_triggered[i] && v0[57] )
      joystick_button_10_triggered[i] = 1;
    if ( !joystick_button_11_triggered[i] && v0[58] )
      joystick_button_11_triggered[i] = 1;
    if ( !joystick_button_12_triggered[i] && v0[59] )
      joystick_button_12_triggered[i] = 1;
    if ( !joystick_button_13_triggered[i] && v0[60] )
      joystick_button_13_triggered[i] = 1;
    if ( !joystick_button_14_triggered[i] && v0[61] )
      joystick_button_14_triggered[i] = 1;
    if ( !joystick_button_15_triggered[i] && v0[62] )
      joystick_button_15_triggered[i] = 1;
    result = joystick_button_16_triggered[i];
    if ( !result )
    {
      result = (unsigned __int8)v0[63];
      if ( (_BYTE)result )
        joystick_button_16_triggered[i] = 1;
    }
    goto LABEL_97;
  }
  return result;
}

int diUpdateDeviceStates()
{
  int result; // eax
  int i; // eax
  int j; // esi
  int v3; // ecx
  char *v4; // edx
  int *v5; // ebp
  int v6; // eax
  unsigned int v7; // edi
  char *v8; // ecx
  char *v9; // [esp+2Ch] [ebp-104h]
  _BYTE v10[256]; // [esp+30h] [ebp-100h] BYREF

  memset(g_KeyboardState, 0, 0x40u);
  memset(v10, 0, sizeof(v10));
  result = g_pKeyboardDevice;
  if ( g_pKeyboardDevice )
  {
    if ( g_bDevicesAcquired == 1 )
    {
      result = (*(int (__stdcall **)(int, int, _BYTE *))(*(_DWORD *)g_pKeyboardDevice + 36))(
                 g_pKeyboardDevice,
                 256,
                 v10);
      if ( result >= 0 )
      {
        for ( i = 0; i < 256; ++i )
        {
          if ( v10[i] )
          {
            if ( !g_KeyboardStatePrev[i] )
              g_KeyboardStatePrev[i] = 1;
          }
          else
          {
            g_KeyboardStatePrev[i] = 0;
          }
        }
        g_KeyboardStatePrev[0] = 0;
        for ( j = 0; j < 4; ++j )
        {
          v3 = g_pJoystickDevices[j];
          result = 0;
          if ( v3 )
          {
            v4 = &g_JoystickButtonState[32 * j];
            v9 = v4;
            do
            {
              v4[result - 128] = 0;
              v4[result++] = 0;
            }
            while ( result < 32 );
            (*(void (__stdcall **)(int))(*(_DWORD *)v3 + 100))(v3);
            v5 = (int *)&g_JoystickStateBuffer[80 * j];
            result = (*(int (__stdcall **)(int, int, int *))(*(_DWORD *)g_pJoystickDevices[j] + 36))(
                       g_pJoystickDevices[j],
                       80,
                       v5);
            if ( result == -2147024866 )
            {
              v6 = g_pJoystickDevices[j];
              if ( v6 )
                (*(void (__stdcall **)(int))(*(_DWORD *)v6 + 28))(g_pJoystickDevices[j]);
              result = (*(int (__stdcall **)(int, int, char *))(*(_DWORD *)g_pJoystickDevices[j] + 36))(
                         g_pJoystickDevices[j],
                         80,
                         &g_JoystickStateBuffer[80 * j]);
              if ( result < 0 )
                return result;
            }
            if ( !g_JoystickStateFlags[j] )
            {
              result = *v5;
              if ( *v5 > 0 )
              {
                pad_axis_1_positive_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_1_value[8 * j] = *(_WORD *)v5;
              }
            }
            if ( !joystick_axis_1_positive_triggered[j] )
            {
              result = *v5;
              if ( *v5 < 0 )
              {
                pad_axis_1_negative_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_1_value[8 * j] = *(_WORD *)v5;
              }
            }
            if ( !joystick_axis_1_negative_triggered[j] )
            {
              result = joystick_axis_2_state[20 * j];
              if ( result > 0 )
              {
                pad_axis_2_positive_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_2_value[8 * j] = joystick_axis_2_state[20 * j];
              }
            }
            if ( !joystick_axis_2_positive_triggered[j] )
            {
              result = joystick_axis_2_state[20 * j];
              if ( result < 0 )
              {
                pad_axis_2_negative_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_2_value[8 * j] = joystick_axis_2_state[20 * j];
              }
            }
            if ( !joystick_z_axis_positive_triggered[j] )
            {
              result = joystick_axis_3_state[20 * j];
              if ( result > 0 )
              {
                pad_axis_3_positive_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_3_value[8 * j] = joystick_axis_3_state[20 * j];
              }
            }
            if ( !joystick_axis_2_negative_triggered[j] )
            {
              result = joystick_axis_3_state[20 * j];
              if ( result < 0 )
              {
                pad_axis_3_negative_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_3_value[8 * j] = joystick_axis_3_state[20 * j];
              }
            }
            if ( !joystick_axis_4_positive_triggered[j] )
            {
              result = joystick_axis_4_state[20 * j];
              if ( result > 0 )
              {
                pad_axis_4_positive_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_4_value[8 * j] = joystick_axis_4_state[20 * j];
              }
            }
            if ( !joystick_axis_4_negative_triggered[j] )
            {
              result = joystick_axis_4_state[20 * j];
              if ( result < 0 )
              {
                pad_axis_4_negative_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_4_value[8 * j] = joystick_axis_4_state[20 * j];
              }
            }
            if ( !joystick_axis_5_positive_triggered[j] )
            {
              result = joystick_axis_5_state[20 * j];
              if ( result > 0 )
              {
                pad_axis_5_positive_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_5_value[8 * j] = joystick_axis_5_state[20 * j];
              }
            }
            if ( !joystick_axis_5_negative_triggered[j] )
            {
              result = joystick_axis_5_state[20 * j];
              if ( result < 0 )
              {
                pad_axis_5_negative_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_5_value[8 * j] = joystick_axis_5_state[20 * j];
              }
            }
            if ( !joystick_axis_6_positive_triggered[j] )
            {
              result = joystick_axis_6_state[20 * j];
              if ( result > 0 )
              {
                pad_axis_6_positive_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_6_value[8 * j] = joystick_axis_6_state[20 * j];
              }
            }
            if ( !joystick_axis_6_negative_triggered[j] )
            {
              result = joystick_axis_6_state[20 * j];
              if ( result < 0 )
              {
                pad_axis_6_negative_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_6_value[8 * j] = joystick_axis_6_state[20 * j];
              }
            }
            if ( !joystick_axis_7_positive_triggered[j] )
            {
              result = joystick_axis_7_state[20 * j];
              if ( result > 0 )
              {
                pad_axis_7_positive_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_7_value[8 * j] = joystick_axis_7_state[20 * j];
              }
            }
            if ( !joystick_axis_7_negative_triggered[j] )
            {
              result = joystick_axis_7_state[20 * j];
              if ( result < 0 )
              {
                pad_axis_7_negative_pressed[32 * j] = 1;
                result = 16 * j;
                pad_axis_7_value[8 * j] = joystick_axis_7_state[20 * j];
              }
            }
            if ( !joystick_button_1_triggered[j] && joystick_button_1_state[80 * j] )
              pad_button_1_pressed[32 * j] = 1;
            if ( !joystick_button_2_triggered[j] && joystick_button_2_state[80 * j] )
            {
              result = 32 * j;
              pad_button_2_pressed[32 * j] = 1;
            }
            if ( !joystick_button_3_triggered[j] && joystick_button_3_state[80 * j] )
              pad_button_3_pressed[32 * j] = 1;
            if ( !joystick_button_4_triggered[j] && joystick_button_4_state[80 * j] )
              pad_button_4_pressed[32 * j] = 1;
            if ( !joystick_button_5_triggered[j] && joystick_button_5_state[80 * j] )
            {
              result = 32 * j;
              pad_button_5_pressed[32 * j] = 1;
            }
            if ( !joystick_button_6_triggered[j] && joystick_button_6_state[80 * j] )
              pad_button_6_pressed[32 * j] = 1;
            if ( !joystick_button_7_triggered[j] && joystick_button_7_state[80 * j] )
              pad_button_7_pressed[32 * j] = 1;
            if ( !joystick_button_8_triggered[j] && joystick_button_8_state[80 * j] )
            {
              result = 32 * j;
              pad_button_8_pressed[32 * j] = 1;
            }
            if ( !joystick_button_9_triggered[j] && joystick_button_9_state[80 * j] )
              pad_button_9_pressed[32 * j] = 1;
            if ( !joystick_button_10_triggered[j] && joystick_button_10_state[80 * j] )
              pad_button_10_pressed[32 * j] = 1;
            if ( !joystick_button_11_triggered[j] && joystick_button_11_state[80 * j] )
            {
              result = 32 * j;
              pad_button_11_pressed[32 * j] = 1;
            }
            if ( !joystick_button_12_triggered[j] && joystick_button_12_state[80 * j] )
              pad_button_12_pressed[32 * j] = 1;
            if ( !joystick_button_13_triggered[j] && joystick_button_13_state[80 * j] )
              pad_button_13_pressed[32 * j] = 1;
            if ( !joystick_button_14_triggered[j] && joystick_button_14_state[80 * j] )
            {
              result = 32 * j;
              pad_button_14_pressed[32 * j] = 1;
            }
            if ( !joystick_button_15_triggered[j] && joystick_button_15_state[80 * j] )
              pad_button_15_pressed[32 * j] = 1;
            if ( !joystick_button_16_triggered[j] && joystick_button_16_state[80 * j] )
              pad_button_16_pressed[32 * j] = 1;
            v7 = joystick_pov_hat_value[20 * j];
            if ( v7 > 0x4650 )
            {
              switch ( v7 )
              {
                case 0x57E4u:
                  result = (int)&g_KeyboardStatePrev[32 * j];
                  *(_BYTE *)(result + 386) = 1;
                  *(_BYTE *)(result + 387) = 1;
                  break;
                case 0x6978u:
                  pad_pov_left_pressed[32 * j] = 1;
                  break;
                case 0x7B0Cu:
                  result = 32 * j;
                  pad_pov_left_pressed[32 * j] = 1;
                  *v9 = 1;
                  break;
              }
            }
            else if ( v7 == 18000 )
            {
              pad_pov_down_pressed[32 * j] = 1;
            }
            else if ( v7 > 0x2328 )
            {
              if ( v7 == 13500 )
              {
                result = (int)&g_KeyboardStatePrev[32 * j];
                *(_BYTE *)(result + 385) = 1;
                *(_BYTE *)(result + 386) = 1;
              }
            }
            else if ( v7 == 9000 )
            {
              result = 32 * j;
              pad_pov_right_pressed[32 * j] = 1;
            }
            else if ( v7 )
            {
              if ( v7 == 4500 )
              {
                result = (int)&g_JoystickButtonState[32 * j];
                *v9 = 1;
                pad_pov_right_pressed[32 * j] = 1;
              }
            }
            else
            {
              *v9 = 1;
            }
          }
          else
          {
            v8 = &g_JoystickButtonState[32 * j];
            do
            {
              v8[result - 128] = 0;
              v8[result++] = 0;
            }
            while ( result < 32 );
          }
        }
      }
    }
  }
  return result;
}

int diGetClampedMouseX()
{
  int result; // eax

  if ( !point_device_enabled )
    return 0;
  diGetMouseState();
  result = g_MouseX;
  if ( g_MouseX < g_MouseMinX )
  {
    result = g_MouseMinX;
    g_MouseX = g_MouseMinX;
  }
  if ( result > g_MouseMaxX )
  {
    g_MouseX = g_MouseMaxX;
    return g_MouseMaxX;
  }
  return result;
}

int diGetClampedMouseY()
{
  int result; // eax

  if ( !point_device_enabled )
    return 0;
  result = g_MouseY[0];
  if ( g_MouseY[0] < g_MouseMinY )
  {
    result = g_MouseMinY;
    g_MouseY[0] = g_MouseMinY;
  }
  if ( result > g_MouseMaxY )
  {
    g_MouseY[0] = g_MouseMaxY;
    return g_MouseMaxY;
  }
  return result;
}

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
  while ( (int)v0 < (int)&g_directinput_initialized );
  result = (*(int (__stdcall **)(int))(*(_DWORD *)g_pDirectInput + 8))(g_pDirectInput);
  g_pDirectInput = 0;
  g_uiNumJoysticks = 0;
  return result;
}

int __cdecl diGetJoystickButtonState1(int a1)
{
  return g_KeyboardState[LOWORD(GamepadAxis[2 * a1])];
}

int __cdecl diGetJoystickButtonState2(int a1)
{
  return g_KeyboardState[HIWORD(GamepadAxis[2 * a1])];
}

int __cdecl diGetJoystickButtonState3(int a1)
{
  return g_KeyboardState[LOWORD(GamepadAxis[2 * a1 + 1])];
}

int __cdecl diGetJoystickButtonState4(int a1)
{
  return g_KeyboardState[HIWORD(GamepadAxis[2 * a1 + 1])];
}


/* Decompiled globals (previously generated in src/_gen) */
GUID GUID_Keyboard;
GUID GUID_Mouse;
unsigned char g_directinput_initialized;
unsigned char joystick_button_1_state[1];
unsigned char joystick_button_2_state[1];
unsigned char joystick_button_3_state[1];
unsigned char joystick_button_4_state[1];
unsigned char joystick_button_5_state[1];
unsigned char joystick_button_6_state[1];
unsigned char joystick_button_7_state[1];
unsigned char joystick_button_8_state[1];
unsigned char joystick_button_9_state[1];
unsigned char joystick_button_10_state[1];
unsigned char joystick_button_11_state[1];
unsigned char joystick_button_12_state[1];
unsigned char joystick_button_13_state[1];
unsigned char joystick_button_14_state[1];
unsigned char joystick_button_15_state[1];
unsigned char joystick_button_16_state[0x101];
unsigned char pad_axis_1_positive_pressed[1];
unsigned char pad_axis_1_negative_pressed[1];
unsigned char pad_axis_2_positive_pressed[1];
unsigned char pad_axis_2_negative_pressed[1];
unsigned char pad_axis_3_positive_pressed[1];
unsigned char pad_axis_3_negative_pressed[1];
unsigned char pad_axis_4_positive_pressed[1];
unsigned char pad_axis_4_negative_pressed[1];
unsigned char pad_axis_5_positive_pressed[1];
unsigned char pad_axis_5_negative_pressed[1];
unsigned char pad_axis_6_positive_pressed[1];
unsigned char pad_axis_6_negative_pressed[1];
unsigned char pad_axis_7_positive_pressed[1];
unsigned char pad_axis_7_negative_pressed[1];
unsigned char pad_button_1_pressed[1];
unsigned char pad_button_2_pressed[1];
unsigned char pad_button_3_pressed[1];
unsigned char pad_button_4_pressed[1];
unsigned char pad_button_5_pressed[1];
unsigned char pad_button_6_pressed[1];
unsigned char pad_button_7_pressed[1];
unsigned char pad_button_8_pressed[1];
unsigned char pad_button_9_pressed[1];
unsigned char pad_button_10_pressed[1];
unsigned char pad_button_11_pressed[1];
unsigned char pad_button_12_pressed[1];
unsigned char pad_button_13_pressed[1];
unsigned char pad_button_14_pressed[1];
unsigned char pad_button_15_pressed[1];
unsigned char pad_button_16_pressed[0x61];
unsigned char pad_pov_right_pressed[1];
unsigned char pad_pov_down_pressed[1];
unsigned char pad_pov_left_pressed[0x7d];
unsigned int joystick_axis_2_state[1];
unsigned int joystick_axis_3_state[1];
unsigned int joystick_axis_4_state[1];
unsigned int joystick_axis_5_state[1];
unsigned int joystick_axis_6_state[1];
unsigned int joystick_axis_7_state[1];
unsigned int joystick_pov_hat_value[0x4];
unsigned int joystick_z_axis_positive_triggered[0x10];
unsigned int joystick_button_3_triggered[0x10];
unsigned int joystick_button_4_triggered[0x10];
unsigned int joystick_button_5_triggered[0x10];
unsigned int joystick_button_6_triggered[0x10];
unsigned int joystick_button_7_triggered[0x10];
unsigned int joystick_button_8_triggered[0x10];
unsigned int joystick_button_9_triggered[0x10];
unsigned int joystick_button_10_triggered[0x10];
unsigned int joystick_button_11_triggered[0x10];
unsigned int joystick_button_12_triggered[0x10];
unsigned int joystick_button_13_triggered[0x10];
unsigned int joystick_button_14_triggered[0x10];
unsigned int joystick_button_15_triggered[0x10];
unsigned int joystick_button_16_triggered[0x30];
void *force_feedback_effect_handles2[4];
unsigned char g_EffectBuffer1[0x190];
unsigned int g_EffectBuffer2[0x64];
unsigned int g_EffectScaleFactor = 0x4b;
unsigned char g_JoystickButtonState[1];
unsigned char g_JoystickDataFormat = 0x18;
unsigned char g_JoystickStateBuffer[1];
unsigned int g_JoystickStateFlags[0x10];
unsigned char g_KeyboardDataFormat = 0x18;
unsigned short g_KeyboardState[1];
unsigned char g_MouseDataFormat = 0x18;
unsigned int g_MouseMaxX = 0x7f;
unsigned int g_MouseMaxY = 0x7f;
unsigned int g_MouseMinX = 0xffffff80;
unsigned int g_MouseMinY = 0xffffff80;
unsigned int g_MouseX;
unsigned int g_MouseY[1];
unsigned int g_PlayerDeviceMap1[1];
unsigned int g_bDevicesAcquired;
unsigned int g_pDirectInput;
unsigned int g_pEffectStructs[0x3];
unsigned int g_pEffectStructs2[0x4];
unsigned int g_pJoystickDevices[0x4];
unsigned int g_pKeyboardDevice;
unsigned int g_pMouseDevice;
unsigned int g_uiNumJoysticks;
unsigned int hDlgInput;
int joystick_axis_1_negative_triggered[4];
int joystick_axis_1_positive_triggered[4];
int joystick_axis_2_negative_triggered[4];
int joystick_axis_2_positive_triggered[4];
int joystick_axis_3_negative_triggered[4];
int joystick_axis_3_positive_triggered[4];
int joystick_axis_4_negative_triggered[4];
int joystick_axis_4_positive_triggered[4];
int joystick_axis_5_negative_triggered[4];
int joystick_axis_5_positive_triggered[4];
int joystick_axis_6_negative_triggered[4];
int joystick_axis_6_positive_triggered[4];
int joystick_axis_7_negative_triggered[4];
int joystick_axis_7_positive_triggered[4];
int joystick_button_1_triggered[4];
int joystick_button_2_triggered[4];
unsigned int point_device_enabled;
unsigned short pad_axis_1_value[1];
unsigned short pad_axis_2_value[1];
unsigned short pad_axis_3_value[1];
unsigned short pad_axis_4_value[1];
unsigned short pad_axis_5_value[1];
unsigned short pad_axis_6_value[1];
unsigned short pad_axis_7_value[1];
