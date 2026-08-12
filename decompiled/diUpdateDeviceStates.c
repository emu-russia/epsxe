#include "pch.h"
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
                byte_50ACC0[32 * j] = 1;
                result = 16 * j;
                word_50AE02[8 * j] = *(_WORD *)v5;
              }
            }
            if ( !joystick_axis_1_positive_triggered[j] )
            {
              result = *v5;
              if ( *v5 < 0 )
              {
                byte_50ACC1[32 * j] = 1;
                result = 16 * j;
                word_50AE02[8 * j] = *(_WORD *)v5;
              }
            }
            if ( !joystick_axis_1_negative_triggered[j] )
            {
              result = dword_4F778C[20 * j];
              if ( result > 0 )
              {
                byte_50ACC2[32 * j] = 1;
                result = 16 * j;
                word_50AE04[8 * j] = dword_4F778C[20 * j];
              }
            }
            if ( !joystick_axis_2_positive_triggered[j] )
            {
              result = dword_4F778C[20 * j];
              if ( result < 0 )
              {
                byte_50ACC3[32 * j] = 1;
                result = 16 * j;
                word_50AE04[8 * j] = dword_4F778C[20 * j];
              }
            }
            if ( !dword_4F7B68[j] )
            {
              result = dword_4F7790[20 * j];
              if ( result > 0 )
              {
                byte_50ACC4[32 * j] = 1;
                result = 16 * j;
                word_50AE06[8 * j] = dword_4F7790[20 * j];
              }
            }
            if ( !joystick_axis_2_negative_triggered[j] )
            {
              result = dword_4F7790[20 * j];
              if ( result < 0 )
              {
                byte_50ACC5[32 * j] = 1;
                result = 16 * j;
                word_50AE06[8 * j] = dword_4F7790[20 * j];
              }
            }
            if ( !joystick_axis_4_positive_triggered[j] )
            {
              result = dword_4F7798[20 * j];
              if ( result > 0 )
              {
                byte_50ACC6[32 * j] = 1;
                result = 16 * j;
                word_50AE08[8 * j] = dword_4F7798[20 * j];
              }
            }
            if ( !joystick_axis_4_negative_triggered[j] )
            {
              result = dword_4F7798[20 * j];
              if ( result < 0 )
              {
                byte_50ACC7[32 * j] = 1;
                result = 16 * j;
                word_50AE08[8 * j] = dword_4F7798[20 * j];
              }
            }
            if ( !joystick_axis_5_positive_triggered[j] )
            {
              result = dword_4F779C[20 * j];
              if ( result > 0 )
              {
                byte_50ACC8[32 * j] = 1;
                result = 16 * j;
                word_50AE0A[8 * j] = dword_4F779C[20 * j];
              }
            }
            if ( !joystick_axis_5_negative_triggered[j] )
            {
              result = dword_4F779C[20 * j];
              if ( result < 0 )
              {
                byte_50ACC9[32 * j] = 1;
                result = 16 * j;
                word_50AE0A[8 * j] = dword_4F779C[20 * j];
              }
            }
            if ( !joystick_axis_6_positive_triggered[j] )
            {
              result = dword_4F77A0[20 * j];
              if ( result > 0 )
              {
                byte_50ACCA[32 * j] = 1;
                result = 16 * j;
                word_50AE0C[8 * j] = dword_4F77A0[20 * j];
              }
            }
            if ( !joystick_axis_6_negative_triggered[j] )
            {
              result = dword_4F77A0[20 * j];
              if ( result < 0 )
              {
                byte_50ACCB[32 * j] = 1;
                result = 16 * j;
                word_50AE0C[8 * j] = dword_4F77A0[20 * j];
              }
            }
            if ( !joystick_axis_7_positive_triggered[j] )
            {
              result = dword_4F77A4[20 * j];
              if ( result > 0 )
              {
                byte_50ACCC[32 * j] = 1;
                result = 16 * j;
                word_50AE0E[8 * j] = dword_4F77A4[20 * j];
              }
            }
            if ( !joystick_axis_7_negative_triggered[j] )
            {
              result = dword_4F77A4[20 * j];
              if ( result < 0 )
              {
                byte_50ACCD[32 * j] = 1;
                result = 16 * j;
                word_50AE0E[8 * j] = dword_4F77A4[20 * j];
              }
            }
            if ( !joystick_button_1_triggered[j] && byte_4F77B8[80 * j] )
              byte_50ACD0[32 * j] = 1;
            if ( !joystick_button_2_triggered[j] && byte_4F77B9[80 * j] )
            {
              result = 32 * j;
              byte_50ACD1[32 * j] = 1;
            }
            if ( !dword_4F7EE8[j] && byte_4F77BA[80 * j] )
              byte_50ACD2[32 * j] = 1;
            if ( !dword_4F7F28[j] && byte_4F77BB[80 * j] )
              byte_50ACD3[32 * j] = 1;
            if ( !dword_4F7F68[j] && byte_4F77BC[80 * j] )
            {
              result = 32 * j;
              byte_50ACD4[32 * j] = 1;
            }
            if ( !dword_4F7FA8[j] && byte_4F77BD[80 * j] )
              byte_50ACD5[32 * j] = 1;
            if ( !dword_4F7FE8[j] && byte_4F77BE[80 * j] )
              byte_50ACD6[32 * j] = 1;
            if ( !dword_4F8028[j] && byte_4F77BF[80 * j] )
            {
              result = 32 * j;
              byte_50ACD7[32 * j] = 1;
            }
            if ( !dword_4F8068[j] && byte_4F77C0[80 * j] )
              byte_50ACD8[32 * j] = 1;
            if ( !dword_4F80A8[j] && byte_4F77C1[80 * j] )
              byte_50ACD9[32 * j] = 1;
            if ( !dword_4F80E8[j] && byte_4F77C2[80 * j] )
            {
              result = 32 * j;
              byte_50ACDA[32 * j] = 1;
            }
            if ( !dword_4F8128[j] && byte_4F77C3[80 * j] )
              byte_50ACDB[32 * j] = 1;
            if ( !dword_4F8168[j] && byte_4F77C4[80 * j] )
              byte_50ACDC[32 * j] = 1;
            if ( !dword_4F81A8[j] && byte_4F77C5[80 * j] )
            {
              result = 32 * j;
              byte_50ACDD[32 * j] = 1;
            }
            if ( !dword_4F81E8[j] && byte_4F77C6[80 * j] )
              byte_50ACDE[32 * j] = 1;
            if ( !dword_4F8228[j] && byte_4F77C7[80 * j] )
              byte_50ACDF[32 * j] = 1;
            v7 = dword_4F77A8[20 * j];
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
                  byte_50AD43[32 * j] = 1;
                  break;
                case 0x7B0Cu:
                  result = 32 * j;
                  byte_50AD43[32 * j] = 1;
                  *v9 = 1;
                  break;
              }
            }
            else if ( v7 == 18000 )
            {
              byte_50AD42[32 * j] = 1;
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
              byte_50AD41[32 * j] = 1;
            }
            else if ( v7 )
            {
              if ( v7 == 4500 )
              {
                result = (int)&g_JoystickButtonState[32 * j];
                *v9 = 1;
                byte_50AD41[32 * j] = 1;
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
