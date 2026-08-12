#include "pch.h"
int net_fill_input()
{
  int result; // eax

  result = 0;
  if ( network_enabled )
  {
    HIWORD(dword_50A1D0) = pad1_buttons_low;
    byte_50A1D4 = joystick_button_state1[0];
    byte_50A1D5 = joystick_button_state2[0];
    byte_50A1D6 = joystick_button_state3[0];
    byte_50A1D7 = joystick_button_state4[0];
    LOBYTE(dword_50A1D8) = mouse_buttons_state;
    BYTE1(dword_50A1D8) = mouse_delta_x;
    HIWORD(dword_50A1C0) = pad2_buttons_low;
    BYTE2(dword_50A1D8) = mouse_delta_y;
    LOBYTE(dword_50A1D0) = controller_port_modes[0];
    LOBYTE(dword_50A1C0) = controller_port_modes[1];
    byte_50A1C4 = 0;
    byte_50A1C5 = 0;
    byte_50A1C6 = 0;
    byte_50A1C7 = 0;
    byte_50A1C8 = 0;
    byte_50A1C9 = 0;
    byte_50A1CA = 0;
    if ( netplay_reset_request )
    {
      LOBYTE(dword_50A1D0) = LOBYTE(controller_port_modes[0]) | 0x80;
      LOBYTE(dword_50A1C0) = LOBYTE(controller_port_modes[1]) | 0x80;
    }
    NETpadState(&dword_50A1D0, &dword_50A1C0);
    if ( (dword_50A1D0 & 0x80u) != 0 || (dword_50A1C0 & 0x80u) != 0 )
    {
      return 1;
    }
    else
    {
      controller_port_modes[0] = (unsigned __int8)dword_50A1D0;
      joystick_button_state2[0] = byte_50A1D5;
      pad1_buttons_low = HIWORD(dword_50A1D0);
      joystick_button_state3[0] = byte_50A1D6;
      mouse_delta_x = SBYTE1(dword_50A1D8);
      joystick_button_state1[0] = byte_50A1D4;
      mouse_buttons_state = (unsigned __int8)dword_50A1D8;
      joystick_button_state4[0] = byte_50A1D7;
      controller_port_modes[1] = (unsigned __int8)dword_50A1C0;
      mouse_delta_y = SBYTE2(dword_50A1D8);
      pad2_buttons_low = HIWORD(dword_50A1C0);
      return 0;
    }
  }
  return result;
}
