#include "pch.h"
int net_load_plugin()
{
  int result; // eax
  HMODULE LibraryA; // eax
  CHAR LibFileName[1024]; // [esp+8h] [ebp-400h] BYREF

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)NetPlugin);
  if ( !strcmp((const char *)NetPlugin, "DISABLED") )
  {
    result = network_enabled;
    if ( !network_enabled )
      return result;
  }
  else
  {
    network_enabled = 1;
  }
  LibraryA = LoadLibraryA(LibFileName);
  hNetModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
  NETinit = GetProcAddress(LibraryA, "NETinit");
  if ( !NETinit )
    ui_error(" * GetProcAddress error NETinit\n");
  NETshutdown = (int (__stdcall *)(void))GetProcAddress(hNetModule, "NETshutdown");
  if ( !NETshutdown )
    ui_error(" * GetProcAddress error NETshutdoww\n");
  NETopen = (int (__stdcall *)(_DWORD))GetProcAddress(hNetModule, "NETopen");
  if ( !NETopen )
    ui_error(" * GetProcAddress error NETopen\n");
  NETclose = GetProcAddress(hNetModule, "NETclose");
  if ( !NETclose )
    ui_error(" * GetProcAddress error NETclose\n");
  NETpause = (int (__stdcall *)(void))GetProcAddress(hNetModule, "NETpause");
  if ( !NETpause )
    ui_error(" * GetProcAddress error NETpause\n");
  NETresume = (int (__stdcall *)(_DWORD))GetProcAddress(hNetModule, "NETresume");
  if ( !NETresume )
    ui_error(" * GetProcAddress error NETresume\n");
  NETpadState = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hNetModule, "NETpadState");
  if ( !NETpadState )
    ui_error(" * GetProcAddress error NETpadState\n");
  NETcompareData = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hNetModule, "NETcompareData");
  if ( !NETcompareData )
    ui_error(" * GetProcAddress error NETcompareData\n");
  NETqueryPlayer = GetProcAddress(hNetModule, "NETqueryPlayer");
  if ( !NETqueryPlayer )
    ui_error(" * GetProcAddress error NETqueryPlayer\n");
  NETtransferData = (int (__stdcall *)(_DWORD, _DWORD, _DWORD))GetProcAddress(hNetModule, "NETtransferData");
  if ( !NETtransferData )
    ui_error(" * GetProcAddress error NETtransferData\n");
  dbg_print(" * Init netplugin ... ");
  NETinit();
  return dbg_print(" ok \n");
}

int net_open()
{
  int result; // eax

  result = network_enabled;
  if ( network_enabled )
  {
    dbg_print(" * Netplugin open... ");
    NETopen(hOutputWnd);
    result = dbg_print(" ok \n");
    net_closed_flag = 0;
  }
  return result;
}

char net_netplay_handler()
{
  char result; // al
  FILE *v1; // eax
  FILE *v2; // esi
  signed int v3; // edi
  void *v4; // ebx
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  char *v8; // eax
  char Buffer[1024]; // [esp+18h] [ebp-400h] BYREF

  result = network_enabled;
  if ( network_enabled )
  {
    netplay_player_count = NETqueryPlayer();
    if ( (unsigned __int8)NETcompareData(default_filename, 12) )
      fatal_error_with_message_box(" * NETPLAY: Error psx game is different in every site. \n");
    netplay_start_options[0] = fastboot;
    netplay_sound_enabled = sound_enabled;
    if ( (unsigned __int8)NETcompareData(netplay_start_options, 1) )
      fatal_error_with_message_box(" * NETPLAY: Start Mode option is different in every site. \n");
    if ( (unsigned __int8)NETcompareData(&netplay_sound_enabled, 1) )
      fatal_error_with_message_box(" * NETPLAY: Sound Enable option is different in every site. \n");
    if ( sound_enabled )
    {
      if ( !strncmp("SPUCORE", (const char *)SoundPlugin, 7u) )
      {
        sprintf(Buffer, "SPUCORE140");
        if ( (unsigned __int8)NETcompareData(Buffer, 10) )
          fatal_error_with_message_box(" * NETPLAY: Error spu plugin is different in every site. \n");
      }
      else
      {
        sprintf(Buffer, "%s%s", "plugins\\", (const char *)SoundPlugin);
        v1 = fopen(Buffer, "rb");
        v2 = v1;
        if ( v1 )
        {
          fseek(v1, 0, 2);
          v3 = ftell(v2);
          if ( v3 <= 0 )
            fatal_error_with_message_box(" * NETPLAY: Error reading spu plugin \n");
          fseek(v2, 0, 0);
          v4 = malloc(v3);
          fread(v4, 1u, v3, v2);
          fclose(v2);
          if ( (unsigned __int8)NETcompareData(v4, v3) )
          {
            free(v4);
            fatal_error_with_message_box(" * NETPLAY: Error spu plugin is different in every site. \n");
          }
          free(v4);
        }
      }
    }
    if ( (unsigned __int8)NETcompareData(bios_image, 0x80000) )
      fatal_error_with_message_box(" * NETPLAY: Error psx bios is different in every site. \n");
    v5 = sio_for_netplay(1u);
    if ( (unsigned __int8)NETcompareData(v5, 0x20000) )
    {
      v6 = sio_for_netplay(1u);
      NETtransferData("Transfer Memcard 1", v6, 0x20000);
      if ( netplay_player_count == 2 )
        save_temp_memcard1();
    }
    v7 = sio_for_netplay(2u);
    if ( (unsigned __int8)NETcompareData(v7, 0x20000) )
    {
      v8 = sio_for_netplay(2u);
      NETtransferData("Transfer Memcard 2", v8, 0x20000);
      if ( netplay_player_count == 2 )
        save_temp_memcard2();
    }
    LOBYTE(netplay_config_packet) = controller_port_modes[0];
    BYTE1(netplay_config_packet) = controller_port_modes[1];
    LOBYTE(netplay_config_options) = forcepad;
    BYTE1(netplay_config_options) = unknown_timing_value;
    BYTE2(netplay_config_options) = nocdstatus;
    HIBYTE(netplay_config_options) = country_setting;
    netplay_config_mdectiming = mdectiming;
    netplay_config_mdec_disable = mdec_disable;
    netplay_config_xa_read_enable = xa_read_enable;
    netplay_config_padding[0] = forcespu;
    NETtransferData("Transfer configuration info", &netplay_config_packet, 1037);
    controller_port_modes[0] = (unsigned __int8)netplay_config_packet;
    forcepad = (unsigned __int8)netplay_config_options;
    unknown_timing_value = BYTE1(netplay_config_options);
    controller_port_modes[1] = BYTE1(netplay_config_packet);
    nocdstatus = BYTE2(netplay_config_options);
    country_setting = HIBYTE(netplay_config_options);
    mdectiming = (unsigned __int8)netplay_config_mdectiming;
    xa_read_enable = netplay_config_xa_read_enable;
    forcespu = netplay_config_padding[0];
    mdec_disable = (unsigned __int8)netplay_config_mdec_disable;
    return netplay_config_xa_read_enable;
  }
  return result;
}

HMODULE net_close()
{
  HMODULE result; // eax

  result = (HMODULE)network_enabled;
  if ( network_enabled )
  {
    result = hNetModule;
    if ( hNetModule )
    {
      if ( !net_closed_flag )
      {
        dbg_print(" * Closing net ...\n");
        NETclose();
        net_closed_flag = 1;
      }
      dbg_print(" * Shutdown net ...\n");
      return NETshutdown();
    }
  }
  return result;
}

HMODULE net_pause()
{
  HMODULE result; // eax

  result = (HMODULE)network_enabled;
  if ( network_enabled )
  {
    result = hNetModule;
    if ( hNetModule )
      return NETpause();
  }
  return result;
}

HMODULE net_resume()
{
  HMODULE result; // eax

  result = (HMODULE)network_enabled;
  if ( network_enabled )
  {
    result = hNetModule;
    if ( hNetModule )
      return (HMODULE)NETresume(hOutputWnd);
  }
  return result;
}

int net_fill_input()
{
  int result; // eax

  result = 0;
  if ( network_enabled )
  {
    HIWORD(netplay_pad1_state) = pad1_buttons_low;
    netplay_joy1_state = joystick_button_state1[0];
    netplay_joy2_state = joystick_button_state2[0];
    netplay_joy3_state = joystick_button_state3[0];
    netplay_joy4_state = joystick_button_state4[0];
    LOBYTE(netplay_mouse_state) = mouse_buttons_state;
    BYTE1(netplay_mouse_state) = mouse_delta_x;
    HIWORD(netplay_pad2_state) = pad2_buttons_low;
    BYTE2(netplay_mouse_state) = mouse_delta_y;
    LOBYTE(netplay_pad1_state) = controller_port_modes[0];
    LOBYTE(netplay_pad2_state) = controller_port_modes[1];
    netplay_pad2_reserved_1 = 0;
    netplay_pad2_reserved_2 = 0;
    netplay_pad2_reserved_3 = 0;
    netplay_pad2_reserved_4 = 0;
    netplay_pad2_reserved_5 = 0;
    netplay_pad2_reserved_6 = 0;
    netplay_pad2_reserved_7 = 0;
    if ( netplay_reset_request )
    {
      LOBYTE(netplay_pad1_state) = LOBYTE(controller_port_modes[0]) | 0x80;
      LOBYTE(netplay_pad2_state) = LOBYTE(controller_port_modes[1]) | 0x80;
    }
    NETpadState(&netplay_pad1_state, &netplay_pad2_state);
    if ( (netplay_pad1_state & 0x80u) != 0 || (netplay_pad2_state & 0x80u) != 0 )
    {
      return 1;
    }
    else
    {
      controller_port_modes[0] = (unsigned __int8)netplay_pad1_state;
      joystick_button_state2[0] = netplay_joy2_state;
      pad1_buttons_low = HIWORD(netplay_pad1_state);
      joystick_button_state3[0] = netplay_joy3_state;
      mouse_delta_x = SBYTE1(netplay_mouse_state);
      joystick_button_state1[0] = netplay_joy1_state;
      mouse_buttons_state = (unsigned __int8)netplay_mouse_state;
      joystick_button_state4[0] = netplay_joy4_state;
      controller_port_modes[1] = (unsigned __int8)netplay_pad2_state;
      mouse_delta_y = SBYTE2(netplay_mouse_state);
      pad2_buttons_low = HIWORD(netplay_pad2_state);
      return 0;
    }
  }
  return result;
}



/* Decompiled globals (previously generated in src/_gen) */
int (__stdcall *NETclose)();
int (__stdcall *NETcompareData)();
int (__stdcall *NETinit)();
int (__stdcall *NETopen)();
int (__stdcall *NETpadState)();
int (__stdcall *NETpause)();
int (__stdcall *NETqueryPlayer)();
int (__stdcall *NETresume)();
int (__stdcall *NETshutdown)();
int (__stdcall *NETtransferData)();
unsigned char net_closed_flag = 0x1;
unsigned char netplay_pad2_reserved_1;
unsigned char netplay_pad2_reserved_2;
unsigned char netplay_pad2_reserved_3;
unsigned char netplay_pad2_reserved_4;
unsigned char netplay_pad2_reserved_5;
unsigned char netplay_pad2_reserved_6;
unsigned char netplay_pad2_reserved_7;
unsigned char netplay_joy1_state;
unsigned char netplay_joy2_state;
unsigned char netplay_joy3_state;
unsigned char netplay_joy4_state;
unsigned char netplay_sound_enabled;
unsigned char netplay_start_options[0x41f];
unsigned char netplay_config_mdectiming;
unsigned char netplay_config_mdec_disable;
unsigned char netplay_config_xa_read_enable;
unsigned char netplay_config_padding[0x405];
unsigned int netplay_pad2_state;
unsigned int netplay_pad1_state;
unsigned int netplay_mouse_state;
unsigned int netplay_player_count;
unsigned int netplay_config_packet;
unsigned int netplay_config_options;
unsigned int hNetModule;
unsigned int network_enabled;
unsigned int unknown_timing_value;
