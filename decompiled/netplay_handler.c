#include "pch.h"
char netplay_handler()
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
    if ( (unsigned __int8)NETcompareData(ppf_default_filename, 12) )
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
    v5 = sub_422340(1u);
    if ( (unsigned __int8)NETcompareData(v5, 0x20000) )
    {
      v6 = sub_422340(1u);
      NETtransferData("Transfer Memcard 1", v6, 0x20000);
      if ( dword_50A1E0 == 2 )
        save_temp_memcard1();
    }
    v7 = sub_422340(2u);
    if ( (unsigned __int8)NETcompareData(v7, 0x20000) )
    {
      v8 = sub_422340(2u);
      NETtransferData("Transfer Memcard 2", v8, 0x20000);
      if ( dword_50A1E0 == 2 )
        save_temp_memcard2();
    }
    LOBYTE(dword_50A620) = dword_456048[0];
    BYTE1(dword_50A620) = dword_456048[1];
    LOBYTE(dword_50A624) = forcepad;
    BYTE1(dword_50A624) = dword_50C374;
    BYTE2(dword_50A624) = nocdstatus;
    HIBYTE(dword_50A624) = country_setting;
    byte_50A628 = mdectiming;
    byte_50A629 = mdec_disable;
    byte_50A62A = xa_read_enable;
    byte_50A62B[0] = forcespu;
    NETtransferData("Transfer configuration info", &dword_50A620, 1037);
    dword_456048[0] = (unsigned __int8)dword_50A620;
    forcepad = (unsigned __int8)dword_50A624;
    dword_50C374 = BYTE1(dword_50A624);
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
