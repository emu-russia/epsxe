#include "pch.h"
uint8_t * cont_build_controller_response_digital(char a1, uint8_t *a2)
{
  uint8_t *result;

  switch ( a1 )
  {
    case 0:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad1_buttons_high;
      a2[4] = pad1_buttons_low;
      result = a2;
      break;
    case 1:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad2_buttons_high;
      a2[4] = pad2_buttons_low;
      result = a2;
      break;
    case 2:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad3_buttons_high;
      a2[4] = pad3_buttons_low;
      result = a2;
      break;
    case 3:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad4_buttons_high;
      a2[4] = pad4_buttons_low;
      result = a2;
      break;
    default:
      *a2 = 0;
      a2[1] = -1;
      a2[2] = -1;
      a2[3] = -1;
      a2[4] = -1;
      result = a2;
      break;
  }
  return result;
}

char cont_build_controller_response_analog(char a1, uint8_t *a2)
{
  char result;
  int16_t v3;
  char v4;
  int v5;
  int v6;

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

uint8_t * cont_build_mouse_response(char a1, uint8_t *a2)
{
  uint8_t *result;

  if ( a1 )
  {
    result = a2;
    a2[3] = -1;
    a2[2] = 90;
    a2[1] = 18;
    *a2 = 0;
    if ( a1 != 1 )
    {
      a2[4] = -1;
      a2[6] = -1;
      a2[5] = -1;
      return result;
    }
  }
  else
  {
    result = a2;
    *a2 = 0;
    a2[1] = 18;
    a2[2] = 90;
    a2[3] = -1;
  }
  result[4] = -4;
  if ( (mouse_buttons_state & 1) != 0 )
    result[4] = -12;
  if ( (mouse_buttons_state & 2) != 0 )
    result[4] &= ~4u;
  result[5] = mouse_delta_x;
  result[6] = mouse_delta_y;
  return result;
}

uint8_t * cont_build_guncon_response(char a1, uint8_t *a2)
{
  uint8_t *result;
  int16_t v3;
  int v4;
  int v5;
  int v6;
  int v7;

  if ( a1 )
  {
    result = a2;
    a2[7] = 0;
    a2[6] = 0;
    a2[5] = 0;
    a2[4] = -1;
    a2[3] = -1;
    a2[2] = 90;
    *a2 = 0;
    if ( a1 == 1 )
    {
      a2[1] = -1;
      a2[8] = -1;
    }
    else
    {
      a2[8] = 0;
      a2[1] = 99;
    }
  }
  else
  {
    *a2 = 0;
    a2[1] = 99;
    a2[2] = 90;
    *(uint16_t *)(a2 + 3) = -1;
    a2[8] = 0;
    a2[7] = 0;
    a2[6] = 0;
    a2[5] = 0;
    v3 = mouse_delta_y / 2 + HIWORD(guncon_position);
    LOWORD(guncon_position) = mouse_delta_x / 2 + guncon_position;
    HIWORD(guncon_position) = v3;
    if ( (int16_t)guncon_position <= 511 )
    {
      if ( (guncon_position & 0x8000u) != 0 )
        LOWORD(guncon_position) = 0;
    }
    else
    {
      LOWORD(guncon_position) = 511;
    }
    if ( v3 <= 255 )
    {
      if ( v3 < 0 )
        HIWORD(guncon_position) = 0;
    }
    else
    {
      HIWORD(guncon_position) = 255;
    }
    if ( (mouse_buttons_state & 1) != 0 )
      a2[4] &= ~0x20u;
    if ( (mouse_buttons_state & 2) != 0 )
      a2[3] &= ~8u;
    if ( (mouse_buttons_state & 4) != 0 )
      a2[4] &= ~0x40u;
    *(uint16_t *)(a2 + 5) = guncon_position;
    a2[7] = BYTE2(guncon_position);
    if ( (guncon_position & 0x100) != 0 )
    {
      v4 = (int16_t)guncon_position + ((int16_t)guncon_position - 255) / 2;
      v5 = SHIWORD(guncon_position) - 40;
      if ( v4 <= 511 )
      {
        if ( v4 < 0 )
          v4 = 0;
      }
      else
      {
        v4 = 511;
      }
      if ( v5 <= 255 )
      {
        if ( v5 < 0 )
          v5 = 0;
        return gpu_cursor(0, v4, v5);
      }
      else
      {
        return gpu_cursor(0, v4, 255);
      }
    }
    else
    {
      v6 = (int16_t)guncon_position - (255 - (int16_t)guncon_position) / 2;
      v7 = SHIWORD(guncon_position) - 40;
      if ( v6 <= 511 )
      {
        if ( v6 < 0 )
          v6 = 0;
      }
      else
      {
        v6 = 511;
      }
      if ( v7 <= 255 )
      {
        if ( v7 < 0 )
          v7 = 0;
        return gpu_cursor(0, v6, v7);
      }
      else
      {
        return gpu_cursor(0, v6, 255);
      }
    }
  }
  return result;
}

int (__stdcall * cont_update_led_and_mode(uint8_t a1))(uint32_t)
{
  int v1;
  int (__stdcall *result)(uint32_t);

  v1 = controller_port_modes[a1];
  if ( v1 == 4 || v1 == 5 || v1 == 6 )
    gpu_display_flags(((a1 + 1) << 12) | ((pad_analog_mode_flags[a1] != 0) << 8));
  if ( controller_port_modes[a1] == 2 )
    gpu_display_flags(((a1 + 1) << 12) | ((pad_analog_mode_flags[a1] != 0 ? 2 : 0) << 8));
  if ( controller_port_modes[a1] == 3 )
    gpu_display_flags(((a1 + 1) << 12) | ((pad_analog_mode_flags[a1] != 0 ? 3 : 0) << 8));
  result = (int (__stdcall *)(uint32_t))controller_port_modes[a1];
  if ( (unsigned int)result <= 1 )
    return gpu_display_flags((a1 + 1) << 12);
  return result;
}

int cont_process_input()
{
  int v0;
  int v1;
  int v2;
  uint8_t v3;
  int v4;
  char *v5;
  uint16_t *v6;
  int v7;
  uint16_t v8;
  int result;

  diUpdateDeviceStates();
  mouse_delta_x = diGetClampedMouseX();
  mouse_delta_y = diGetClampedMouseY();
  mouse_buttons_state = g_MouseButtons;
  v0 = 0;
  v1 = 2;
  do
  {
    joystick_button_state1[v0] = diGetJoystickButtonState1(v0);
    joystick_button_state2[v0] = diGetJoystickButtonState2(v0);
    joystick_button_state3[v0] = diGetJoystickButtonState3(v0);
    joystick_button_state4[v0] = diGetJoystickButtonState4(v0);
    ++v0;
    --v1;
  }
  while ( v1 );
  if ( keyboard_escape_pressed[0] )
  {
    if ( !create_window_flag )
      ui_error(" User   hit ESC ... \n");
    if ( network_enabled )
    {
      netplay_reset_request = 1;
    }
    else
    {
      save_load_state();
      memset(gpu_keyboard_state, 0, 0x100u);
    }
  }
  if ( dynarec_clear_request )
    dynarec_clear_needed = 1;
  if ( cdr_status_command_2 )
    cdr_get_status(2);
  if ( cdr_status_command_3 )
    cdr_get_status(3);
  if ( sio_irq_assert_request[0] )
    irq_sio_assert_int();
  if ( screen_pic_display_counter )
  {
    if ( screen_pic_display_counter == 1 )
      gpu_hide_screen_pic();
    --screen_pic_display_counter;
  }
  if ( ui_feedback_timer )
  {
    --ui_feedback_timer;
    goto LABEL_51;
  }
  if ( save_state_request )
  {
    state_save();
    dbg_print(" * SaveState Done! \n");
    ui_feedback_timer = 25;
    goto LABEL_51;
  }
  if ( increase_slot_state_request )
  {
    LOBYTE(v2) = gpu_freeze_with_counter();
    v3 = v2;
    dbg_print(" * Increased SlotState! (%d)\n", v2);
    gpu_show_screen_pic(v3);
    ui_feedback_timer = 25;
    screen_pic_display_counter = 150;
    goto LABEL_51;
  }
  if ( load_state_request )
  {
    if ( network_enabled )
    {
      dbg_print(" * LoadState doesn't implemented yet with Netplay! \n");
    }
    else
    {
      state_load();
      dbg_print(" * LoadState Done! \n");
      dynarec_clear_needed = 1;
    }
    ui_feedback_timer = 25;
    goto LABEL_51;
  }
  if ( toggle_sio_irq_request )
  {
    if ( network_enabled )
    {
      dbg_print(" * SIO trick doesn't implemented yet with Netplay! \n");
      ui_feedback_timer = 25;
    }
    else
    {
      forcepad ^= 0x80u;
      if ( forcepad )
        dbg_print(" * SIO irq enabled. \n");
      else
        dbg_print(" * SIO irq disabled. \n");
      ui_feedback_timer = 25;
    }
    goto LABEL_51;
  }
  if ( toggle_pad_mode_request )
  {
    pad_analog_mode_flags[(uint8_t)selected_slot_for_mode_switch] ^= 1u;
    LOBYTE(v4) = selected_slot_for_mode_switch;
LABEL_42:
    cont_update_led_and_mode(v4);
    ui_feedback_timer = 25;
    goto LABEL_51;
  }
  if ( switch_controller_slot_request )
  {
    v4 = ((uint8_t)selected_slot_for_mode_switch + 1) % (2 * (multitap_1 != 0) + 2);
    LOBYTE(selected_slot_for_mode_switch) = v4;
    goto LABEL_42;
  }
  if ( toggle_xenogears_trick_request )
  {
    xenogears_trick_enabled ^= 1u;
    if ( xenogears_trick_enabled )
      dbg_print(" * Xenogears trick disabled. \n");
    else
      dbg_print(" * Xenogears trick enabled. \n");
    ui_feedback_timer = 25;
  }
  else if ( make_snapshot_request[0] )
  {
    dbg_print(" * Picture done. \n");
    gpu_make_snapshot();
    ui_feedback_timer = 25;
  }
LABEL_51:
  v5 = &pad1_buttons_low;
  v6 = (uint16_t *)(Keys1 + 10);
  v7 = 4;
  do
  {
    v8 = *(v6 - 5);
    *(uint32_t *)v5 = -1;
    if ( v8 )
    {
      if ( g_KeyboardStatePrev[v6[1]] )
        *(uint32_t *)v5 = -65;
      if ( g_KeyboardStatePrev[*v6] )
        *(uint32_t *)v5 &= ~0x20u;
      if ( g_KeyboardStatePrev[v6[2]] )
        *(uint32_t *)v5 &= ~0x80u;
      if ( g_KeyboardStatePrev[*(v6 - 1)] )
        *(uint32_t *)v5 &= ~0x10u;
      if ( g_KeyboardStatePrev[v6[7]] )
        *(uint32_t *)v5 &= ~0x800u;
      if ( g_KeyboardStatePrev[v6[8]] )
        *(uint32_t *)v5 &= ~0x100u;
      if ( g_KeyboardStatePrev[*(v6 - 3)] )
        *(uint32_t *)v5 &= ~0x1000u;
      if ( g_KeyboardStatePrev[*(v6 - 2)] )
        *(uint32_t *)v5 &= ~0x4000u;
      if ( g_KeyboardStatePrev[v8] )
        *(uint32_t *)v5 &= ~0x8000u;
      if ( g_KeyboardStatePrev[*(v6 - 4)] )
        *(uint32_t *)v5 &= ~0x2000u;
      if ( g_KeyboardStatePrev[v6[3]] )
        *(uint32_t *)v5 &= ~4u;
      if ( g_KeyboardStatePrev[v6[4]] )
        *(uint32_t *)v5 &= ~1u;
      if ( g_KeyboardStatePrev[v6[5]] )
        *(uint32_t *)v5 &= ~8u;
      if ( g_KeyboardStatePrev[v6[6]] )
        *(uint32_t *)v5 &= ~2u;
      if ( g_KeyboardStatePrev[v6[9]] )
        *(uint32_t *)v5 &= ~0x200u;
      if ( g_KeyboardStatePrev[v6[10]] )
        *(uint32_t *)v5 &= ~0x400u;
    }
    v6 += 16;
    v5 += 4;
    --v7;
  }
  while ( v7 );
  if ( LOBYTE(mdec_disable_flag[0]) )
  {
    LOBYTE(mdec_disable_flag[0]) = 0;
    *(uint32_t *)&pad1_buttons_low &= 0xFFFFF7BF;
  }
  result = network_enabled;
  if ( network_enabled )
  {
    result = net_fill_input();
    if ( result )
    {
      netplay_reset_request = 0;
      save_load_state();
      memset(gpu_keyboard_state, 0, 0x100u);
      return 0;
    }
  }
  return result;
}

int16_t cont_map_axis_state(uint16_t a1, int16_t a2)
{
  int16_t result;

  result = a2;
  if ( a2 )
    *((uint16_t *)GamepadAxis + a1) = a2;
  return result;
}

int16_t cont_map_button_state(uint16_t a1, int16_t a2)
{
  int16_t result;

  result = a2;
  if ( a2 != 1 )
    Keys1[a1] = a2;
  return result;
}

int cont_set_default(uint8_t a1)
{
  int result;

  if ( a1 == 1 )
  {
    Keys1[0] = 203;
    Keys1[1] = 205;
    Keys1[2] = 200;
    Keys1[3] = 208;
    Keys1[4] = 32;
    Keys1[5] = 45;
    Keys1[6] = 44;
    Keys1[7] = 31;
    Keys1[8] = 17;
    Keys1[9] = 18;
    Keys1[10] = 19;
    Keys1[11] = 20;
    Keys1[12] = 47;
    Keys1[13] = 46;
    Keys1[14] = 16;
    Keys1[15] = 21;
  }
  else if ( a1 > 1u && a1 < 4u )
  {
    memset(&pad_key_assignments[16 * a1], 0, 0x20u);
    return 0;
  }
  return result;
}

int cont_reset_pad_state(uint8_t a1)
{
  uint32_t *v2;

  memset(&pad_key_assignments[16 * a1], 0, 0x20u);
  v2 = (uint32_t *)(8 * a1 + 5232772);
  *v2 = 0;
  v2[1] = 0;
  return 0;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char cdr_status_command_2[8];
unsigned char cdr_status_command_3[8];
unsigned char dynarec_clear_needed;
int dynarec_clear_request;
unsigned char g_KeyboardStatePrev[1];
unsigned int g_MouseButtons;
unsigned char gpu_keyboard_state[0x1b];
unsigned int guncon_position;
int increase_slot_state_request;
unsigned char joystick_button_state1[4];
unsigned char joystick_button_state2[4];
unsigned char joystick_button_state3[4];
unsigned char joystick_button_state4[4];
int keyboard_escape_pressed[2];
int load_state_request;
int make_snapshot_request[2];
unsigned int mdec_disable_flag[1];
int mouse_accumulated_x;
int mouse_accumulated_y;
unsigned int mouse_buttons_state;
int mouse_delta_x;
int mouse_delta_y;
int netplay_reset_request;
unsigned short pad1_analog_joy2_x;
unsigned short pad1_analog_joy2_y;
unsigned short pad1_analog_joy_x;
unsigned short pad1_analog_joy_y;
unsigned short pad1_buttons_high;
unsigned short pad1_buttons_low;
unsigned short pad2_analog_joy2_x;
unsigned short pad2_analog_joy2_y;
unsigned short pad2_analog_joy_x;
unsigned short pad2_analog_joy_y;
unsigned short pad2_buttons_high;
unsigned short pad2_buttons_low;
unsigned short pad3_analog_joy2_x;
unsigned short pad3_analog_joy2_y;
unsigned short pad3_analog_joy_x;
unsigned short pad3_analog_joy_y;
unsigned short pad3_buttons_high;
unsigned short pad3_buttons_low;
unsigned short pad4_analog_joy2_x;
unsigned short pad4_analog_joy2_y;
unsigned short pad4_analog_joy_x;
unsigned short pad4_analog_joy_y;
unsigned short pad4_buttons_high;
unsigned short pad4_buttons_low;
int save_state_request;
int screen_pic_display_counter;
int selected_slot_for_mode_switch;
int sio_irq_assert_request[2];
int switch_controller_slot_request;
int toggle_pad_mode_request;
int toggle_sio_irq_request;
int toggle_xenogears_trick_request;
int ui_feedback_timer;
unsigned char xenogears_trick_enabled = 0x1;
