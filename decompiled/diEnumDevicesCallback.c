#include "pch.h"
int diEnumDevicesCallback(int a1, _DWORD *a2, int a3)
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
        dword_4F7B68[g_uiNumJoysticks] = 1;
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
