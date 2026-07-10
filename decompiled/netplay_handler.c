#include "pch.h"
char sub_42F240()
{
  char result; // al
  FILE *v1; // eax
  FILE *v2; // esi
  signed int v3; // edi
  void *v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  char v9; // [esp+8h] [ebp-410h]
  char v10; // [esp+Ch] [ebp-40Ch]
  char v11; // [esp+14h] [ebp-404h]
  char Buffer[1024]; // [esp+18h] [ebp-400h] BYREF

  result = dword_4FD99C;
  if ( dword_4FD99C )
  {
    dword_50A1E0 = NETqueryPlayer();
    if ( (unsigned __int8)NETcompareData(byte_8B3D80, 12) )
      fatal_error_with_message_box(aNetplayErrorPs, Buffer[0]);
    byte_50A201 = fastboot;
    byte_50A200 = sound_enabled;
    if ( (unsigned __int8)NETcompareData(&byte_50A201, 1) )
      fatal_error_with_message_box(aNetplayStartMo, Buffer[0]);
    if ( (unsigned __int8)NETcompareData(&byte_50A200, 1) )
      fatal_error_with_message_box(aNetplaySoundEn, Buffer[0]);
    if ( sound_enabled )
    {
      if ( !strncmp(aSpucore, (const char *)&SoundPlugin, 7u) )
      {
        sprintf(Buffer, aSpucore140);
        if ( (unsigned __int8)NETcompareData(Buffer, 10) )
          fatal_error_with_message_box(aNetplayErrorSp, v11);
      }
      else
      {
        sprintf(Buffer, "%s%s", aPlugins, (const char *)&SoundPlugin);
        v1 = fopen(Buffer, Mode);
        v2 = v1;
        if ( v1 )
        {
          fseek(v1, 0, 2);
          v3 = ftell(v2);
          if ( v3 <= 0 )
            fatal_error_with_message_box(aNetplayErrorRe, v10);
          fseek(v2, 0, 0);
          v4 = malloc(v3);
          fread(v4, 1u, v3, v2);
          fclose(v2);
          if ( (unsigned __int8)NETcompareData(v4, v3) )
          {
            free(v4);
            fatal_error_with_message_box(aNetplayErrorSp, v9);
          }
          free(v4);
        }
      }
    }
    if ( (unsigned __int8)NETcompareData(&byte_7F6E80, 0x80000) )
      fatal_error_with_message_box(aNetplayErrorPs_0, Buffer[0]);
    v5 = sub_422340(1);
    if ( (unsigned __int8)NETcompareData(v5, 0x20000) )
    {
      v6 = sub_422340(1);
      NETtransferData(aTransferMemcar, v6, 0x20000);
      if ( dword_50A1E0 == 2 )
        sub_422360();
    }
    v7 = sub_422340(2);
    if ( (unsigned __int8)NETcompareData(v7, 0x20000) )
    {
      v8 = sub_422340(2);
      NETtransferData(aTransferMemcar_0, v8, 0x20000);
      if ( dword_50A1E0 == 2 )
        sub_422390();
    }
    LOBYTE(dword_50A620) = dword_456048;
    BYTE1(dword_50A620) = dword_45604C;
    LOBYTE(dword_50A624) = forcepad;
    BYTE1(dword_50A624) = dword_50C374;
    BYTE2(dword_50A624) = byte_4FD880;
    HIBYTE(dword_50A624) = country_setting;
    LOBYTE(dword_50A628) = mdectiming;
    BYTE1(dword_50A628) = mdec_disable;
    BYTE2(dword_50A628) = xa_read_enable;
    HIBYTE(dword_50A628) = forcespu;
    NETtransferData(aTransferConfig, &dword_50A620, 1037);
    dword_456048 = (unsigned __int8)dword_50A620;
    forcepad = (unsigned __int8)dword_50A624;
    dword_50C374 = BYTE1(dword_50A624);
    dword_45604C = BYTE1(dword_50A620);
    byte_4FD880 = BYTE2(dword_50A624);
    country_setting = HIBYTE(dword_50A624);
    mdectiming = (unsigned __int8)dword_50A628;
    forcespu = HIBYTE(dword_50A628);
    xa_read_enable = BYTE2(dword_50A628);
    mdec_disable = BYTE1(dword_50A628);
    return BYTE2(dword_50A628);
  }
  return result;
}
