#include "pch.h"
int cont_process_input()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  unsigned __int8 v3; // si
  int v4; // edx
  char *v5; // eax
  unsigned __int16 *v6; // ecx
  int v7; // esi
  unsigned __int16 v8; // dx
  int result; // eax

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
    pad_analog_mode_flags[(unsigned __int8)selected_slot_for_mode_switch] ^= 1u;
    LOBYTE(v4) = selected_slot_for_mode_switch;
LABEL_42:
    cont_update_led_and_mode(v4);
    ui_feedback_timer = 25;
    goto LABEL_51;
  }
  if ( switch_controller_slot_request )
  {
    v4 = ((unsigned __int8)selected_slot_for_mode_switch + 1) % (2 * (multitap_1 != 0) + 2);
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
  v6 = (unsigned __int16 *)(Keys1 + 10);
  v7 = 4;
  do
  {
    v8 = *(v6 - 5);
    *(_DWORD *)v5 = -1;
    if ( v8 )
    {
      if ( g_KeyboardStatePrev[v6[1]] )
        *(_DWORD *)v5 = -65;
      if ( g_KeyboardStatePrev[*v6] )
        *(_DWORD *)v5 &= ~0x20u;
      if ( g_KeyboardStatePrev[v6[2]] )
        *(_DWORD *)v5 &= ~0x80u;
      if ( g_KeyboardStatePrev[*(v6 - 1)] )
        *(_DWORD *)v5 &= ~0x10u;
      if ( g_KeyboardStatePrev[v6[7]] )
        *(_DWORD *)v5 &= ~0x800u;
      if ( g_KeyboardStatePrev[v6[8]] )
        *(_DWORD *)v5 &= ~0x100u;
      if ( g_KeyboardStatePrev[*(v6 - 3)] )
        *(_DWORD *)v5 &= ~0x1000u;
      if ( g_KeyboardStatePrev[*(v6 - 2)] )
        *(_DWORD *)v5 &= ~0x4000u;
      if ( g_KeyboardStatePrev[v8] )
        *(_DWORD *)v5 &= ~0x8000u;
      if ( g_KeyboardStatePrev[*(v6 - 4)] )
        *(_DWORD *)v5 &= ~0x2000u;
      if ( g_KeyboardStatePrev[v6[3]] )
        *(_DWORD *)v5 &= ~4u;
      if ( g_KeyboardStatePrev[v6[4]] )
        *(_DWORD *)v5 &= ~1u;
      if ( g_KeyboardStatePrev[v6[5]] )
        *(_DWORD *)v5 &= ~8u;
      if ( g_KeyboardStatePrev[v6[6]] )
        *(_DWORD *)v5 &= ~2u;
      if ( g_KeyboardStatePrev[v6[9]] )
        *(_DWORD *)v5 &= ~0x200u;
      if ( g_KeyboardStatePrev[v6[10]] )
        *(_DWORD *)v5 &= ~0x400u;
    }
    v6 += 16;
    v5 += 4;
    --v7;
  }
  while ( v7 );
  if ( LOBYTE(mdec_disable_flag[0]) )
  {
    LOBYTE(mdec_disable_flag[0]) = 0;
    *(_DWORD *)&pad1_buttons_low &= 0xFFFFF7BF;
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
