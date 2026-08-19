#include "pch.h"
uint8_t * cont_build_controller_response_digital(char port, uint8_t *response)
{
  switch ( port )
  {
    case 0:
      *response = 0;
      response[1] = 65;
      response[2] = 90;
      response[3] = pad1_buttons_high;
      response[4] = pad1_buttons_low;
      break;
    case 1:
      *response = 0;
      response[1] = 65;
      response[2] = 90;
      response[3] = pad2_buttons_high;
      response[4] = pad2_buttons_low;
      break;
    case 2:
      *response = 0;
      response[1] = 65;
      response[2] = 90;
      response[3] = pad3_buttons_high;
      response[4] = pad3_buttons_low;
      break;
    case 3:
      *response = 0;
      response[1] = 65;
      response[2] = 90;
      response[3] = pad4_buttons_high;
      response[4] = pad4_buttons_low;
      break;
    default:
      *response = 0;
      response[1] = -1;
      response[2] = -1;
      response[3] = -1;
      response[4] = -1;
      break;
  }
  return response;
}

char cont_build_controller_response_analog(char port, uint8_t *response)
{
  char ret;
  int16_t clamped_x;
  char clamped_y;
  int tripled_delta_x;
  int tripled_delta_y;

  switch ( port )
  {
    case 0:
      *response = 0;
      response[1] = 115;
      response[2] = 90;
      response[3] = pad1_buttons_high;
      response[4] = pad1_buttons_low;
      response[8] = 0x80;
      response[7] = 0x80;
      response[6] = 0x80;
      response[5] = 0x80;
      if ( controller_port_modes[0] == 4 )
      {
        response[7] = LOBYTE(joystick_button_state1[0]) + 0x80;
        response[8] = LOBYTE(joystick_button_state2[0]) + 0x80;
        response[5] = LOBYTE(joystick_button_state3[0]) + 0x80;
        ret = LOBYTE(joystick_button_state4[0]) + 0x80;
        response[6] = LOBYTE(joystick_button_state4[0]) + 0x80;
        return ret;
      }
      if ( controller_port_modes[0] != 5 )
      {
        ret = LOBYTE(controller_port_modes[0]) - 6;
        if ( controller_port_modes[0] != 6 )
          return ret;
        if ( (mouse_buttons_state & 3) != 0 )
        {
          mouse_accumulated_x += mouse_delta_x / 3;
          LOBYTE(clamped_x) = mouse_accumulated_x;
          if ( mouse_accumulated_x <= 127 )
          {
            if ( mouse_accumulated_x >= -128 )
              goto LABEL_12;
            clamped_x = -128;
          }
          else
          {
            clamped_x = 127;
          }
        }
        else
        {
          clamped_x = 0;
        }
        mouse_accumulated_x = clamped_x;
LABEL_12:
        response[7] = clamped_x + 0x80;
        if ( (mouse_buttons_state & 3) != 0 )
        {
          mouse_accumulated_y += mouse_delta_y / 3;
          clamped_y = mouse_accumulated_y;
          if ( mouse_accumulated_y <= 127 )
          {
            if ( mouse_accumulated_y < -128 )
            {
              clamped_y = 0x80;
              mouse_accumulated_y = -128;
            }
            ret = clamped_y + 0x80;
            response[8] = ret;
          }
          else
          {
            mouse_accumulated_y = 127;
            response[8] = -1;
            return -1;
          }
        }
        else
        {
          mouse_accumulated_y = 0;
          response[8] = 0x80;
          return 0x80;
        }
        return ret;
      }
      tripled_delta_x = 3 * mouse_delta_x;
      mouse_delta_x *= 3;
      if ( mouse_delta_x <= 127 )
      {
        if ( tripled_delta_x >= -128 )
          goto LABEL_24;
        tripled_delta_x = -128;
      }
      else
      {
        tripled_delta_x = 127;
      }
      mouse_delta_x = tripled_delta_x;
LABEL_24:
      response[7] = tripled_delta_x + 0x80;
      tripled_delta_y = 3 * mouse_delta_y;
      mouse_delta_y *= 3;
      if ( mouse_delta_y <= 127 )
      {
        if ( tripled_delta_y < -128 )
        {
          LOBYTE(tripled_delta_y) = 0x80;
          mouse_delta_y = -128;
        }
        ret = tripled_delta_y + 0x80;
        response[8] = ret;
      }
      else
      {
        mouse_delta_y = 127;
        response[8] = -1;
        return -1;
      }
      return ret;
    case 1:
      *response = 0;
      response[1] = 115;
      response[2] = 90;
      response[3] = pad2_buttons_high;
      response[4] = pad2_buttons_low;
      response[7] = pad1_analog_joy_x + 0x80;
      response[8] = pad1_analog_joy_y + 0x80;
      response[5] = pad1_analog_joy2_x + 0x80;
      response[6] = pad1_analog_joy2_y + 0x80;
      return (char)response;
    case 2:
      *response = 0;
      response[1] = 115;
      response[2] = 90;
      response[3] = pad3_buttons_high;
      response[4] = pad3_buttons_low;
      response[7] = pad2_analog_joy_x + 0x80;
      response[8] = pad2_analog_joy_y + 0x80;
      response[5] = pad2_analog_joy2_x + 0x80;
      response[6] = pad2_analog_joy2_y + 0x80;
      return (char)response;
    case 3:
      *response = 0;
      response[1] = 115;
      response[2] = 90;
      response[3] = pad4_buttons_high;
      response[4] = pad4_buttons_low;
      response[7] = pad3_analog_joy_x + 0x80;
      response[8] = pad3_analog_joy_y + 0x80;
      response[5] = pad3_analog_joy2_x + 0x80;
      response[6] = pad3_analog_joy2_y + 0x80;
      return (char)response;
    default:
      *response = 0;
      response[1] = -1;
      response[2] = 90;
      response[3] = -1;
      response[4] = -1;
      response[8] = 0x80;
      response[7] = 0x80;
      response[6] = 0x80;
      response[5] = 0x80;
      return (char)response;
  }
}

uint8_t * cont_build_mouse_response(char port, uint8_t *response)
{
  if ( port )
  {
    response[3] = -1;
    response[2] = 90;
    response[1] = 18;
    *response = 0;
    if ( port != 1 )
    {
      response[4] = -1;
      response[6] = -1;
      response[5] = -1;
      return response;
    }
  }
  else
  {
    *response = 0;
    response[1] = 18;
    response[2] = 90;
    response[3] = -1;
  }
  response[4] = -4;
  if ( (mouse_buttons_state & 1) != 0 )
    response[4] = -12;
  if ( (mouse_buttons_state & 2) != 0 )
    response[4] &= ~4u;
  response[5] = mouse_delta_x;
  response[6] = mouse_delta_y;
  return response;
}

uint8_t * cont_build_guncon_response(char port, uint8_t *response)
{
  int16_t gun_y;
  int cursor_x;
  int cursor_y;
  int cursor_x2;
  int cursor_y2;

  if ( port )
  {
    response[7] = 0;
    response[6] = 0;
    response[5] = 0;
    response[4] = -1;
    response[3] = -1;
    response[2] = 90;
    *response = 0;
    if ( port == 1 )
    {
      response[1] = -1;
      response[8] = -1;
    }
    else
    {
      response[8] = 0;
      response[1] = 99;
    }
  }
  else
  {
    *response = 0;
    response[1] = 99;
    response[2] = 90;
    *(uint16_t *)(response + 3) = -1;
    response[8] = 0;
    response[7] = 0;
    response[6] = 0;
    response[5] = 0;
    gun_y = mouse_delta_y / 2 + HIWORD(guncon_position);
    LOWORD(guncon_position) = mouse_delta_x / 2 + guncon_position;
    HIWORD(guncon_position) = gun_y;
    if ( (int16_t)guncon_position <= 511 )
    {
      if ( (guncon_position & 0x8000u) != 0 )
        LOWORD(guncon_position) = 0;
    }
    else
    {
      LOWORD(guncon_position) = 511;
    }
    if ( gun_y <= 255 )
    {
      if ( gun_y < 0 )
        HIWORD(guncon_position) = 0;
    }
    else
    {
      HIWORD(guncon_position) = 255;
    }
    if ( (mouse_buttons_state & 1) != 0 )
      response[4] &= ~0x20u;
    if ( (mouse_buttons_state & 2) != 0 )
      response[3] &= ~8u;
    if ( (mouse_buttons_state & 4) != 0 )
      response[4] &= ~0x40u;
    *(uint16_t *)(response + 5) = guncon_position;
    response[7] = BYTE2(guncon_position);
    if ( (guncon_position & 0x100) != 0 )
    {
      cursor_x = (int16_t)guncon_position + ((int16_t)guncon_position - 255) / 2;
      cursor_y = SHIWORD(guncon_position) - 40;
      if ( cursor_x <= 511 )
      {
        if ( cursor_x < 0 )
          cursor_x = 0;
      }
      else
      {
        cursor_x = 511;
      }
      if ( cursor_y <= 255 )
      {
        if ( cursor_y < 0 )
          cursor_y = 0;
        return gpu_cursor(0, cursor_x, cursor_y);
      }
      else
      {
        return gpu_cursor(0, cursor_x, 255);
      }
    }
    else
    {
      cursor_x2 = (int16_t)guncon_position - (255 - (int16_t)guncon_position) / 2;
      cursor_y2 = SHIWORD(guncon_position) - 40;
      if ( cursor_x2 <= 511 )
      {
        if ( cursor_x2 < 0 )
          cursor_x2 = 0;
      }
      else
      {
        cursor_x2 = 511;
      }
      if ( cursor_y2 <= 255 )
      {
        if ( cursor_y2 < 0 )
          cursor_y2 = 0;
        return gpu_cursor(0, cursor_x2, cursor_y2);
      }
      else
      {
        return gpu_cursor(0, cursor_x2, 255);
      }
    }
  }
  return response;
}

int (__stdcall * cont_update_led_and_mode(uint8_t port))(uint32_t)
{
  int mode;
  int (__stdcall *callback)(uint32_t);

  mode = controller_port_modes[port];
  if ( mode == 4 || mode == 5 || mode == 6 )
    gpu_display_flags(((port + 1) << 12) | ((pad_analog_mode_flags[port] != 0) << 8));
  if ( controller_port_modes[port] == 2 )
    gpu_display_flags(((port + 1) << 12) | ((pad_analog_mode_flags[port] != 0 ? 2 : 0) << 8));
  if ( controller_port_modes[port] == 3 )
    gpu_display_flags(((port + 1) << 12) | ((pad_analog_mode_flags[port] != 0 ? 3 : 0) << 8));
  callback = (int (__stdcall *)(uint32_t))controller_port_modes[port];
  if ( (unsigned int)callback <= 1 )
    return gpu_display_flags((port + 1) << 12);
  return callback;
}

int cont_process_input()
{
  int port;
  int joy_count;
  int freeze_counter;
  uint8_t freeze_counter_byte;
  int slot;
  char *pad_buttons;
  uint16_t *key_map;
  int pad_count;
  uint16_t key;
  int net_result;

  diUpdateDeviceStates();
  mouse_delta_x = diGetClampedMouseX();
  mouse_delta_y = diGetClampedMouseY();
  mouse_buttons_state = g_MouseButtons;
  port = 0;
  joy_count = 2;
  do
  {
    joystick_button_state1[port] = diGetJoystickButtonState1(port);
    joystick_button_state2[port] = diGetJoystickButtonState2(port);
    joystick_button_state3[port] = diGetJoystickButtonState3(port);
    joystick_button_state4[port] = diGetJoystickButtonState4(port);
    ++port;
    --joy_count;
  }
  while ( joy_count );
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
    LOBYTE(freeze_counter) = gpu_freeze_with_counter();
    freeze_counter_byte = freeze_counter;
    dbg_print(" * Increased SlotState! (%d)\n", freeze_counter);
    gpu_show_screen_pic(freeze_counter_byte);
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
    LOBYTE(slot) = selected_slot_for_mode_switch;
LABEL_42:
    cont_update_led_and_mode(slot);
    ui_feedback_timer = 25;
    goto LABEL_51;
  }
  if ( switch_controller_slot_request )
  {
    slot = ((uint8_t)selected_slot_for_mode_switch + 1) % (2 * (multitap_1 != 0) + 2);
    LOBYTE(selected_slot_for_mode_switch) = slot;
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
  pad_buttons = &pad1_buttons_low;
  key_map = (uint16_t *)(Keys1 + 10);
  pad_count = 4;
  do
  {
    key = *(key_map - 5);
    *(uint32_t *)pad_buttons = -1;
    if ( key )
    {
      if ( g_KeyboardStatePrev[key_map[1]] )
        *(uint32_t *)pad_buttons = -65;
      if ( g_KeyboardStatePrev[*key_map] )
        *(uint32_t *)pad_buttons &= ~0x20u;
      if ( g_KeyboardStatePrev[key_map[2]] )
        *(uint32_t *)pad_buttons &= ~0x80u;
      if ( g_KeyboardStatePrev[*(key_map - 1)] )
        *(uint32_t *)pad_buttons &= ~0x10u;
      if ( g_KeyboardStatePrev[key_map[7]] )
        *(uint32_t *)pad_buttons &= ~0x800u;
      if ( g_KeyboardStatePrev[key_map[8]] )
        *(uint32_t *)pad_buttons &= ~0x100u;
      if ( g_KeyboardStatePrev[*(key_map - 3)] )
        *(uint32_t *)pad_buttons &= ~0x1000u;
      if ( g_KeyboardStatePrev[*(key_map - 2)] )
        *(uint32_t *)pad_buttons &= ~0x4000u;
      if ( g_KeyboardStatePrev[key] )
        *(uint32_t *)pad_buttons &= ~0x8000u;
      if ( g_KeyboardStatePrev[*(key_map - 4)] )
        *(uint32_t *)pad_buttons &= ~0x2000u;
      if ( g_KeyboardStatePrev[key_map[3]] )
        *(uint32_t *)pad_buttons &= ~4u;
      if ( g_KeyboardStatePrev[key_map[4]] )
        *(uint32_t *)pad_buttons &= ~1u;
      if ( g_KeyboardStatePrev[key_map[5]] )
        *(uint32_t *)pad_buttons &= ~8u;
      if ( g_KeyboardStatePrev[key_map[6]] )
        *(uint32_t *)pad_buttons &= ~2u;
      if ( g_KeyboardStatePrev[key_map[9]] )
        *(uint32_t *)pad_buttons &= ~0x200u;
      if ( g_KeyboardStatePrev[key_map[10]] )
        *(uint32_t *)pad_buttons &= ~0x400u;
    }
    key_map += 16;
    pad_buttons += 4;
    --pad_count;
  }
  while ( pad_count );
  if ( LOBYTE(mdec_disable_flag[0]) )
  {
    LOBYTE(mdec_disable_flag[0]) = 0;
    *(uint32_t *)&pad1_buttons_low &= 0xFFFFF7BF;
  }
  net_result = network_enabled;
  if ( network_enabled )
  {
    net_result = net_fill_input();
    if ( net_result )
    {
      netplay_reset_request = 0;
      save_load_state();
      memset(gpu_keyboard_state, 0, 0x100u);
      return 0;
    }
  }
  return net_result;
}

int16_t cont_map_axis_state(uint16_t axis, int16_t value)
{
  if ( value )
    *((uint16_t *)GamepadAxis + axis) = value;
  return value;
}

int16_t cont_map_button_state(uint16_t key, int16_t value)
{
  if ( value != 1 )
    Keys1[key] = value;
  return value;
}

int cont_set_default(uint8_t port)
{
  int result;

  if ( port == 1 )
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
  else if ( port > 1u && port < 4u )
  {
    memset(&pad_key_assignments[16 * port], 0, 0x20u);
    return 0;
  }
  return result;
}

int cont_reset_pad_state(uint8_t port)
{
  uint32_t *pad_state;

  memset(&pad_key_assignments[16 * port], 0, 0x20u);
  pad_state = (uint32_t *)(8 * port + 5232772);
  *pad_state = 0;
  pad_state[1] = 0;
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
