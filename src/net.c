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
  NETshutdown = (HMODULE (*)(void))GetProcAddress(hNetModule, "NETshutdown");
  if ( !NETshutdown )
    ui_error(" * GetProcAddress error NETshutdoww\n");
  NETopen = (int (__stdcall *)(_DWORD))GetProcAddress(hNetModule, "NETopen");
  if ( !NETopen )
    ui_error(" * GetProcAddress error NETopen\n");
  NETclose = GetProcAddress(hNetModule, "NETclose");
  if ( !NETclose )
    ui_error(" * GetProcAddress error NETclose\n");
  NETpause = (HMODULE (*)(void))GetProcAddress(hNetModule, "NETpause");
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
    byte_45696C = 0;
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
    dword_50A1E0 = NETqueryPlayer();
    if ( (unsigned __int8)NETcompareData(default_filename, 12) )
      fatal_error_with_message_box(" * NETPLAY: Error psx game is different in every site. \n");
    byte_50A201[0] = fastboot;
    byte_50A200 = sound_enabled;
    if ( (unsigned __int8)NETcompareData(byte_50A201, 1) )
      fatal_error_with_message_box(" * NETPLAY: Start Mode option is different in every site. \n");
    if ( (unsigned __int8)NETcompareData(&byte_50A200, 1) )
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
      if ( dword_50A1E0 == 2 )
        save_temp_memcard1();
    }
    v7 = sio_for_netplay(2u);
    if ( (unsigned __int8)NETcompareData(v7, 0x20000) )
    {
      v8 = sio_for_netplay(2u);
      NETtransferData("Transfer Memcard 2", v8, 0x20000);
      if ( dword_50A1E0 == 2 )
        save_temp_memcard2();
    }
    LOBYTE(dword_50A620) = dword_456048[0];
    BYTE1(dword_50A620) = dword_456048[1];
    LOBYTE(dword_50A624) = forcepad;
    BYTE1(dword_50A624) = unknown_timing_value;
    BYTE2(dword_50A624) = nocdstatus;
    HIBYTE(dword_50A624) = country_setting;
    byte_50A628 = mdectiming;
    byte_50A629 = mdec_disable;
    byte_50A62A = xa_read_enable;
    byte_50A62B[0] = forcespu;
    NETtransferData("Transfer configuration info", &dword_50A620, 1037);
    dword_456048[0] = (unsigned __int8)dword_50A620;
    forcepad = (unsigned __int8)dword_50A624;
    unknown_timing_value = BYTE1(dword_50A624);
    dword_456048[1] = BYTE1(dword_50A620);
    nocdstatus = BYTE2(dword_50A624);
    country_setting = HIBYTE(dword_50A624);
    mdectiming = (unsigned __int8)byte_50A628;
    xa_read_enable = byte_50A62A;
    forcespu = byte_50A62B[0];
    mdec_disable = (unsigned __int8)byte_50A629;
    return byte_50A62A;
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
      if ( !byte_45696C )
      {
        dbg_print(" * Closing net ...\n");
        NETclose();
        byte_45696C = 1;
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
    HIWORD(dword_50A1D0) = byte_455FB0;
    byte_50A1D4 = dword_4FD900[0];
    byte_50A1D5 = dword_4FD910[0];
    byte_50A1D6 = dword_4FD920[0];
    byte_50A1D7 = dword_4FD930[0];
    LOBYTE(dword_50A1D8) = dword_50AB60;
    BYTE1(dword_50A1D8) = dword_4FD8F0;
    HIWORD(dword_50A1C0) = byte_455FB4;
    BYTE2(dword_50A1D8) = dword_4FD8F4;
    LOBYTE(dword_50A1D0) = dword_456048[0];
    LOBYTE(dword_50A1C0) = dword_456048[1];
    byte_50A1C4 = 0;
    byte_50A1C5 = 0;
    byte_50A1C6 = 0;
    byte_50A1C7 = 0;
    byte_50A1C8 = 0;
    byte_50A1C9 = 0;
    byte_50A1CA = 0;
    if ( dword_4FD9A0 )
    {
      LOBYTE(dword_50A1D0) = LOBYTE(dword_456048[0]) | 0x80;
      LOBYTE(dword_50A1C0) = LOBYTE(dword_456048[1]) | 0x80;
    }
    NETpadState(&dword_50A1D0, &dword_50A1C0);
    if ( (dword_50A1D0 & 0x80u) != 0 || (dword_50A1C0 & 0x80u) != 0 )
    {
      return 1;
    }
    else
    {
      dword_456048[0] = (unsigned __int8)dword_50A1D0;
      dword_4FD910[0] = byte_50A1D5;
      byte_455FB0 = HIWORD(dword_50A1D0);
      dword_4FD920[0] = byte_50A1D6;
      dword_4FD8F0 = SBYTE1(dword_50A1D8);
      dword_4FD900[0] = byte_50A1D4;
      dword_50AB60 = (unsigned __int8)dword_50A1D8;
      dword_4FD930[0] = byte_50A1D7;
      dword_456048[1] = (unsigned __int8)dword_50A1C0;
      dword_4FD8F4 = SBYTE2(dword_50A1D8);
      byte_455FB4 = HIWORD(dword_50A1C0);
      return 0;
    }
  }
  return result;
}

