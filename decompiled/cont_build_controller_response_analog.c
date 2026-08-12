#include "pch.h"
char __cdecl cont_build_controller_response_analog(char a1, _BYTE *a2)
{
  char result; // al
  __int16 v3; // ax
  char v4; // al
  int v5; // eax
  int v6; // eax

  switch ( a1 )
  {
    case 0:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = pad1_buttons_high;
      a2[4] = pad1_buttons_low;
      a2[8] = 0x80;
      a2[7] = 0x80;
      a2[6] = 0x80;
      a2[5] = 0x80;
      if ( controller_port_modes[0] == 4 )
      {
        a2[7] = LOBYTE(joystick_button_state1[0]) + 0x80;
        a2[8] = LOBYTE(joystick_button_state2[0]) + 0x80;
        a2[5] = LOBYTE(joystick_button_state3[0]) + 0x80;
        result = LOBYTE(joystick_button_state4[0]) + 0x80;
        a2[6] = LOBYTE(joystick_button_state4[0]) + 0x80;
        return result;
      }
      if ( controller_port_modes[0] != 5 )
      {
        result = LOBYTE(controller_port_modes[0]) - 6;
        if ( controller_port_modes[0] != 6 )
          return result;
        if ( (mouse_buttons_state & 3) != 0 )
        {
          mouse_accumulated_x += mouse_delta_x / 3;
          LOBYTE(v3) = mouse_accumulated_x;
          if ( mouse_accumulated_x <= 127 )
          {
            if ( mouse_accumulated_x >= -128 )
              goto LABEL_12;
            v3 = -128;
          }
          else
          {
            v3 = 127;
          }
        }
        else
        {
          v3 = 0;
        }
        mouse_accumulated_x = v3;
LABEL_12:
        a2[7] = v3 + 0x80;
        if ( (mouse_buttons_state & 3) != 0 )
        {
          mouse_accumulated_y += mouse_delta_y / 3;
          v4 = mouse_accumulated_y;
          if ( mouse_accumulated_y <= 127 )
          {
            if ( mouse_accumulated_y < -128 )
            {
              v4 = 0x80;
              mouse_accumulated_y = -128;
            }
            result = v4 + 0x80;
            a2[8] = result;
          }
          else
          {
            mouse_accumulated_y = 127;
            a2[8] = -1;
            return -1;
          }
        }
        else
        {
          mouse_accumulated_y = 0;
          a2[8] = 0x80;
          return 0x80;
        }
        return result;
      }
      v5 = 3 * mouse_delta_x;
      mouse_delta_x *= 3;
      if ( mouse_delta_x <= 127 )
      {
        if ( v5 >= -128 )
          goto LABEL_24;
        v5 = -128;
      }
      else
      {
        v5 = 127;
      }
      mouse_delta_x = v5;
LABEL_24:
      a2[7] = v5 + 0x80;
      v6 = 3 * mouse_delta_y;
      mouse_delta_y *= 3;
      if ( mouse_delta_y <= 127 )
      {
        if ( v6 < -128 )
        {
          LOBYTE(v6) = 0x80;
          mouse_delta_y = -128;
        }
        result = v6 + 0x80;
        a2[8] = result;
      }
      else
      {
        mouse_delta_y = 127;
        a2[8] = -1;
        return -1;
      }
      return result;
    case 1:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = pad2_buttons_high;
      a2[4] = pad2_buttons_low;
      a2[7] = pad1_analog_joy_x + 0x80;
      a2[8] = pad1_analog_joy_y + 0x80;
      a2[5] = pad1_analog_joy2_x + 0x80;
      a2[6] = pad1_analog_joy2_y + 0x80;
      return (char)a2;
    case 2:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = pad3_buttons_high;
      a2[4] = pad3_buttons_low;
      a2[7] = pad2_analog_joy_x + 0x80;
      a2[8] = pad2_analog_joy_y + 0x80;
      a2[5] = pad2_analog_joy2_x + 0x80;
      a2[6] = pad2_analog_joy2_y + 0x80;
      return (char)a2;
    case 3:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = pad4_buttons_high;
      a2[4] = pad4_buttons_low;
      a2[7] = pad3_analog_joy_x + 0x80;
      a2[8] = pad3_analog_joy_y + 0x80;
      a2[5] = pad3_analog_joy2_x + 0x80;
      a2[6] = pad3_analog_joy2_y + 0x80;
      return (char)a2;
    default:
      *a2 = 0;
      a2[1] = -1;
      a2[2] = 90;
      a2[3] = -1;
      a2[4] = -1;
      a2[8] = 0x80;
      a2[7] = 0x80;
      a2[6] = 0x80;
      a2[5] = 0x80;
      return (char)a2;
  }
}
