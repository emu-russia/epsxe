#include "pch.h"
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
    if ( !dword_4F7B68[i] && *((int *)v0 + 2) > 0 )
      dword_4F7B68[i] = 1;
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
    if ( !dword_4F7EE8[i] && v0[50] )
      dword_4F7EE8[i] = 1;
    if ( !dword_4F7F28[i] && v0[51] )
      dword_4F7F28[i] = 1;
    if ( !dword_4F7F68[i] && v0[52] )
      dword_4F7F68[i] = 1;
    if ( !dword_4F7FA8[i] && v0[53] )
      dword_4F7FA8[i] = 1;
    if ( !dword_4F7FE8[i] && v0[54] )
      dword_4F7FE8[i] = 1;
    if ( !dword_4F8028[i] && v0[55] )
      dword_4F8028[i] = 1;
    if ( !dword_4F8068[i] && v0[56] )
      dword_4F8068[i] = 1;
    if ( !dword_4F80A8[i] && v0[57] )
      dword_4F80A8[i] = 1;
    if ( !dword_4F80E8[i] && v0[58] )
      dword_4F80E8[i] = 1;
    if ( !dword_4F8128[i] && v0[59] )
      dword_4F8128[i] = 1;
    if ( !dword_4F8168[i] && v0[60] )
      dword_4F8168[i] = 1;
    if ( !dword_4F81A8[i] && v0[61] )
      dword_4F81A8[i] = 1;
    if ( !dword_4F81E8[i] && v0[62] )
      dword_4F81E8[i] = 1;
    result = dword_4F8228[i];
    if ( !result )
    {
      result = (unsigned __int8)v0[63];
      if ( (_BYTE)result )
        dword_4F8228[i] = 1;
    }
    goto LABEL_97;
  }
  return result;
}
