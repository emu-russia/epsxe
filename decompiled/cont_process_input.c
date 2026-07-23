#include "pch.h"
int cont_process_input()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  unsigned __int8 v3; // si
  int v4; // edx
  int *v5; // eax
  unsigned __int16 *v6; // ecx
  int v7; // esi
  unsigned __int16 v8; // dx
  int result; // eax

  diUpdateDeviceStates();
  dword_4FD8F0 = diGetClampedMouseX();
  dword_4FD8F4 = diGetClampedMouseY();
  dword_50AB60 = g_MouseButtons;
  v0 = 0;
  v1 = 2;
  do
  {
    dword_4FD900[v0] = diGetJoystickButtonState1(v0);
    dword_4FD910[v0] = diGetJoystickButtonState2(v0);
    dword_4FD920[v0] = diGetJoystickButtonState3(v0);
    dword_4FD930[v0] = diGetJoystickButtonState4(v0);
    ++v0;
    --v1;
  }
  while ( v1 );
  if ( byte_50AA7B[0] )
  {
    if ( !create_window_flag )
      ui_error(" User   hit ESC ... \n");
    if ( network_enabled )
    {
      dword_4FD9A0 = 1;
    }
    else
    {
      save_load_state();
      memset(byte_50AA60, 0, 0x100u);
    }
  }
  if ( byte_50AA91 )
    byte_4FC4E4 = 1;
  if ( byte_50AA92 )
    cont_sub_42CFE0(2);
  if ( byte_50AA93 )
    cont_sub_42CFE0(3);
  if ( byte_50AA94[0] )
    irq_sio_assert_int();
  if ( word_4FD986 )
  {
    if ( word_4FD986 == 1 )
      gpu_hide_screen_pic();
    --word_4FD986;
  }
  if ( byte_4FD984 )
  {
    --byte_4FD984;
    goto LABEL_51;
  }
  if ( byte_50AAD0 )
  {
    state_save();
    dbg_print(" * SaveState Done! \n");
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD1 )
  {
    LOBYTE(v2) = gpu_freeze_with_counter();
    v3 = v2;
    dbg_print(" * Increased SlotState! (%d)\n", v2);
    gpu_show_screen_pic(v3);
    byte_4FD984 = 25;
    word_4FD986 = 150;
    goto LABEL_51;
  }
  if ( byte_50AAD2 )
  {
    if ( network_enabled )
    {
      dbg_print(" * LoadState doesn't implemented yet with Netplay! \n");
    }
    else
    {
      state_load();
      dbg_print(" * LoadState Done! \n");
      byte_4FC4E4 = 1;
    }
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD3 )
  {
    if ( network_enabled )
    {
      dbg_print(" * SIO trick doesn't implemented yet with Netplay! \n");
      byte_4FD984 = 25;
    }
    else
    {
      forcepad ^= 0x80u;
      if ( forcepad )
        dbg_print(" * SIO irq enabled. \n");
      else
        dbg_print(" * SIO irq disabled. \n");
      byte_4FD984 = 25;
    }
    goto LABEL_51;
  }
  if ( byte_50AAD4 )
  {
    dword_4FD8E0[(unsigned __int8)dword_4FD988] ^= 1u;
    LOBYTE(v4) = dword_4FD988;
LABEL_42:
    sub_42D620(v4);
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD5 )
  {
    v4 = ((unsigned __int8)dword_4FD988 + 1) % (2 * (multitap_1 != 0) + 2);
    LOBYTE(dword_4FD988) = v4;
    goto LABEL_42;
  }
  if ( byte_50AAD6 )
  {
    xenogears_trick_enabled ^= 1u;
    if ( xenogears_trick_enabled )
      dbg_print(" * Xenogears trick disabled. \n");
    else
      dbg_print(" * Xenogears trick enabled. \n");
    byte_4FD984 = 25;
  }
  else if ( byte_50AAD7[0] )
  {
    dbg_print(" * Picture done. \n");
    gpu_make_snapshot();
    byte_4FD984 = 25;
  }
LABEL_51:
  v5 = &dword_455FB0;
  v6 = (unsigned __int16 *)&word_455FD2;
  v7 = 4;
  do
  {
    v8 = *(v6 - 5);
    *v5 = -1;
    if ( v8 )
    {
      if ( g_KeyboardStatePrev[v6[1]] )
        *v5 = -65;
      if ( g_KeyboardStatePrev[*v6] )
        *v5 &= ~0x20u;
      if ( g_KeyboardStatePrev[v6[2]] )
        *v5 &= ~0x80u;
      if ( g_KeyboardStatePrev[*(v6 - 1)] )
        *v5 &= ~0x10u;
      if ( g_KeyboardStatePrev[v6[7]] )
        *v5 &= ~0x800u;
      if ( g_KeyboardStatePrev[v6[8]] )
        *v5 &= ~0x100u;
      if ( g_KeyboardStatePrev[*(v6 - 3)] )
        *v5 &= ~0x1000u;
      if ( g_KeyboardStatePrev[*(v6 - 2)] )
        *v5 &= ~0x4000u;
      if ( g_KeyboardStatePrev[v8] )
        *v5 &= ~0x8000u;
      if ( g_KeyboardStatePrev[*(v6 - 4)] )
        *v5 &= ~0x2000u;
      if ( g_KeyboardStatePrev[v6[3]] )
        *v5 &= ~4u;
      if ( g_KeyboardStatePrev[v6[4]] )
        *v5 &= ~1u;
      if ( g_KeyboardStatePrev[v6[5]] )
        *v5 &= ~8u;
      if ( g_KeyboardStatePrev[v6[6]] )
        *v5 &= ~2u;
      if ( g_KeyboardStatePrev[v6[9]] )
        *v5 &= ~0x200u;
      if ( g_KeyboardStatePrev[v6[10]] )
        *v5 &= ~0x400u;
    }
    v6 += 16;
    ++v5;
    --v7;
  }
  while ( v7 );
  if ( LOBYTE(mdec_disable_flag[0]) )
  {
    LOBYTE(mdec_disable_flag[0]) = 0;
    dword_455FB0 &= 0xFFFFF7BF;
  }
  result = network_enabled;
  if ( network_enabled )
  {
    result = net_fill_input();
    if ( result )
    {
      dword_4FD9A0 = 0;
      save_load_state();
      memset(byte_50AA60, 0, 0x100u);
      return 0;
    }
  }
  return result;
}
