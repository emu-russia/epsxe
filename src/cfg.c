#include "pch.h"

uint8_t console_allocated;

char __cdecl cfg_get_value(LPCSTR lpSubKey, LPCSTR lpValueName, LPBYTE lpData)
{
  char v3; // bl
  HKEY hKey; // [esp+4h] [ebp-10h] BYREF
  HKEY phkResult; // [esp+8h] [ebp-Ch] BYREF
  DWORD cbData; // [esp+Ch] [ebp-8h] BYREF
  DWORD Type; // [esp+10h] [ebp-4h] BYREF

  v3 = -1;
  if ( !RegConnectRegistryA(nullptr, HKEY_CURRENT_USER, &phkResult) )
  {
    if ( !RegOpenKeyA(phkResult, lpSubKey, &hKey) )
    {
      cbData = 1024;
      if ( !RegQueryValueExA(hKey, lpValueName, nullptr, &Type, lpData, &cbData) )
        v3 = 0;
      RegCloseKey(hKey);
    }
    RegCloseKey(phkResult);
  }
  return v3;
}

int __cdecl cfg_set_value(LPCSTR lpSubKey, LPCSTR lpValueName, BYTE *lpData)
{
  int result; // eax
  HKEY hKey; // [esp+0h] [ebp-8h] BYREF
  HKEY phkResult; // [esp+4h] [ebp-4h] BYREF

  result = RegConnectRegistryA(nullptr, HKEY_CURRENT_USER, &phkResult);
  if ( !result )
  {
    if ( !RegOpenKeyA(phkResult, lpSubKey, &hKey) || !RegCreateKeyA(phkResult, lpSubKey, &hKey) )
    {
      RegSetValueExA(hKey, lpValueName, 0, 1u, lpData, strlen((const char *)lpData) + 1);
      RegCloseKey(hKey);
    }
    return RegCloseKey(phkResult);
  }
  return result;
}

int cfg_load_settings()
{
  int v1; // [esp+0h] [ebp-408h] BYREF
  unsigned int v2; // [esp+4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( cfg_get_value("Software\\epsxe\\config", "VideoPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)VideoPlugin, "NULL");
  else
    sprintf((char *const)VideoPlugin, "%s", Buffer);
  if ( cfg_get_value("Software\\epsxe\\config", "SoundPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)SoundPlugin, "SPUCORE");
  else
    sprintf((char *const)SoundPlugin, "%s", Buffer);
  if ( cfg_get_value("Software\\epsxe\\config", "CdromPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)CdromPlugin, "NULL");
  else
    sprintf((char *const)CdromPlugin, "%s", Buffer);
  if ( cfg_get_value("Software\\epsxe\\config", "NetPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)NetPlugin, "DISABLED");
  else
    sprintf((char *const)NetPlugin, "%s", Buffer);
  if ( cfg_get_value("Software\\epsxe\\config", "BiosName", bios_name) == -1 )
    sprintf((char *const)bios_name, "bios\\scph1001.bin");
  if ( !cfg_get_value("Software\\epsxe\\config", "SubchannelW9xCdromEnabled", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCdromEnabled = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SubchannelW9xCaching", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCaching = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SubchannelW9xCachingLG", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCachingLG = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SubchannelW2kCdromEnabled", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCdromEnabled = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SubchannelW2kCaching", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCaching = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SubchannelW2kCachingLG", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCachingLG = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SoundEnabled", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_enabled = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SoundXA", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_use_xa = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "SoundCDDA", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_use_cdda = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "Keys1", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      Keys1,
      &Keys1[1],
      &Keys1[2],
      &Keys1[3],
      &Keys1[4],
      &Keys1[5],
      &Keys1[6],
      &Keys1[7],
      &Keys1[8],
      &Keys1[9],
      &Keys1[10],
      &Keys1[11],
      &Keys1[12],
      &Keys1[13],
      &Keys1[14],
      &Keys1[15]);
  if ( !cfg_get_value("Software\\epsxe\\config", "Keys2", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      Keys2,
      &Keys2[1],
      &Keys2[2],
      &Keys2[3],
      &Keys2[4],
      &Keys2[5],
      &Keys2[6],
      &Keys2[7],
      &Keys2[8],
      &Keys2[9],
      &Keys2[10],
      &Keys2[11],
      &Keys2[12],
      &Keys2[13],
      &Keys2[14],
      &Keys2[15]);
  if ( !cfg_get_value("Software\\epsxe\\config", "Keys3", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      Keys3,
      &Keys3[1],
      &Keys3[2],
      &Keys3[3],
      &Keys3[4],
      &Keys3[5],
      &Keys3[6],
      &Keys3[7],
      &Keys3[8],
      &Keys3[9],
      &Keys3[10],
      &Keys3[11],
      &Keys3[12],
      &Keys3[13],
      &Keys3[14],
      &Keys3[15]);
  if ( !cfg_get_value("Software\\epsxe\\config", "Keys4", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      Keys4,
      &Keys4[1],
      &Keys4[2],
      &Keys4[3],
      &Keys4[4],
      &Keys4[5],
      &Keys4[6],
      &Keys4[7],
      &Keys4[8],
      &Keys4[9],
      &Keys4[10],
      &Keys4[11],
      &Keys4[12],
      &Keys4[13],
      &Keys4[14],
      &Keys4[15]);
  if ( !cfg_get_value("Software\\epsxe\\config", "CdromLetter", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    cdrom_letter = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "Logswindow", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    console_allocated = v1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "AutoPpfLoad", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    if ( (_BYTE)v1 )
      ppf_enabled = 1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "Multitap1", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    if ( (_BYTE)v1 )
      multitap_1 = 1;
  }
  if ( !cfg_get_value("Software\\epsxe\\config\\cdrom9x", "CdromHain", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_haid);
  if ( !cfg_get_value("Software\\epsxe\\config\\cdrom9x", "CdromTarget", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_target);
  if ( !cfg_get_value("Software\\epsxe\\config\\cdrom9x", "CdromLun", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_lun);
  if ( cfg_get_value("Software\\epsxe\\config", "Memcard1", (LPBYTE)Buffer) )
    sprintf((char *const)Memcard1, "memcards\\epsxe000.mcr");
  else
    sprintf((char *const)Memcard1, "%s", Buffer);
  if ( cfg_get_value("Software\\epsxe\\config", "Memcard2", (LPBYTE)Buffer) )
    sprintf((char *const)Memcard2, "memcards\\epsxe001.mcr");
  else
    sprintf((char *const)Memcard2, "%s", Buffer);
  if ( !cfg_get_value("Software\\epsxe\\config", "Country", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    country_setting = (unsigned __int8)v1;
  }
  if ( cfg_get_value("Software\\epsxe\\config", "Version", (LPBYTE)Buffer) )
  {
    mdectiming = 1;
    mdec_disable = 0;
    if ( create_window_flag )
      setup_wizard_required = 1;
    version_setting = 0x10600;
    sprintf(Buffer, "%d", 67072);
    cfg_set_value("Software\\epsxe\\config", "Version", (BYTE *)Buffer);
  }
  else
  {
    sscanf(Buffer, "%d", &v2);
    version_setting = v2;
    if ( v2 < 0x10600 )
    {
      if ( create_window_flag )
        setup_wizard_required = 1;
      mdectiming = 1;
      mdec_disable = 0;
      version_setting = 0x10600;
      sprintf(Buffer, "%d", 67072);
      cfg_set_value("Software\\epsxe\\config", "Version", (BYTE *)Buffer);
    }
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "GamepadType", (LPBYTE)Buffer) )
  {
    sscanf(
      Buffer,
      "%d,%d,%d,%d",
      controller_port_modes,
      &controller_port_modes[1],
      &controller_port_modes[2],
      &controller_port_modes[3]);
    if ( controller_port_modes[0] == 5
      || controller_port_modes[0] == 6
      || controller_port_modes[0] == 3
      || controller_port_modes[0] == 2
      || controller_port_modes[1] == 2 )
    {
      point_device_enabled = 1;
    }
  }
  if ( !cfg_get_value("Software\\epsxe\\config", "GamepadSubType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", pad_analog_mode_flags, &dword_4FD8E4, &dword_4FD8E8, &dword_4FD8EC);
  if ( !cfg_get_value("Software\\epsxe\\config", "GamepadAxis", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      GamepadAxis,
      (char *)GamepadAxis + 2,
      &GamepadAxis[1],
      (char *)&GamepadAxis[1] + 2,
      &GamepadAxis[2],
      (char *)&GamepadAxis[2] + 2,
      &GamepadAxis[3],
      (char *)&GamepadAxis[3] + 2,
      &GamepadAxis[4],
      (char *)&GamepadAxis[4] + 2,
      &GamepadAxis[5],
      (char *)&GamepadAxis[5] + 2,
      &GamepadAxis[6],
      (char *)&GamepadAxis[6] + 2,
      &GamepadAxis[7],
      (char *)&GamepadAxis[7] + 2);
  if ( !cfg_get_value("Software\\epsxe\\config", "GamepadMotorType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", g_PlayerDeviceMap1, &g_PlayerDeviceMap2, &g_PlayerDeviceMap3, g_PlayerDeviceMap4);
  if ( !cfg_get_value("Software\\epsxe\\config", "GamepadSMotorType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", g_EffectType2, &dword_4FD8C0, &dword_4FD8C4, dword_4FD8C8);
  if ( !cfg_get_value("Software\\epsxe\\config", "GamepadBMotorType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", g_EffectType1, &dword_4FD8D0, &dword_4FD8D4, &dword_4FD8D8);
  if ( cfg_get_value("Software\\epsxe\\config", "IsoDirectory", (LPBYTE)Buffer) )
    return sprintf(IsoDirectory, ".");
  else
    return sprintf(IsoDirectory, "%s", Buffer);
}

int cfg_save_settings()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  cfg_set_value("Software\\epsxe\\config", "VideoPlugin", VideoPlugin);
  cfg_set_value("Software\\epsxe\\config", "SoundPlugin", SoundPlugin);
  cfg_set_value("Software\\epsxe\\config", "CdromPlugin", CdromPlugin);
  cfg_set_value("Software\\epsxe\\config", "NetPlugin", NetPlugin);
  cfg_set_value("Software\\epsxe\\config", "BiosName", bios_name);
  cfg_set_value("Software\\epsxe\\config", "Memcard1", Memcard1);
  cfg_set_value("Software\\epsxe\\config", "Memcard2", Memcard2);
  sprintf(Buffer, "%d", (unsigned __int8)sound_enabled);
  cfg_set_value("Software\\epsxe\\config", "SoundEnabled", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)sound_use_xa);
  cfg_set_value("Software\\epsxe\\config", "SoundXA", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)sound_use_cdda);
  cfg_set_value("Software\\epsxe\\config", "SoundCDDA", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)Keys1[0],
    (unsigned __int16)Keys1[1],
    (unsigned __int16)Keys1[2],
    (unsigned __int16)Keys1[3],
    (unsigned __int16)Keys1[4],
    (unsigned __int16)Keys1[5],
    (unsigned __int16)Keys1[6],
    (unsigned __int16)Keys1[7],
    (unsigned __int16)Keys1[8],
    (unsigned __int16)Keys1[9],
    (unsigned __int16)Keys1[10],
    (unsigned __int16)Keys1[11],
    (unsigned __int16)Keys1[12],
    (unsigned __int16)Keys1[13],
    (unsigned __int16)Keys1[14],
    (unsigned __int16)Keys1[15]);
  cfg_set_value("Software\\epsxe\\config", "Keys1", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)Keys2[0],
    (unsigned __int16)Keys2[1],
    (unsigned __int16)Keys2[2],
    (unsigned __int16)Keys2[3],
    (unsigned __int16)Keys2[4],
    (unsigned __int16)Keys2[5],
    (unsigned __int16)Keys2[6],
    (unsigned __int16)Keys2[7],
    (unsigned __int16)Keys2[8],
    (unsigned __int16)Keys2[9],
    (unsigned __int16)Keys2[10],
    (unsigned __int16)Keys2[11],
    (unsigned __int16)Keys2[12],
    (unsigned __int16)Keys2[13],
    (unsigned __int16)Keys2[14],
    (unsigned __int16)Keys2[15]);
  cfg_set_value("Software\\epsxe\\config", "Keys2", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)Keys3[0],
    (unsigned __int16)Keys3[1],
    (unsigned __int16)Keys3[2],
    (unsigned __int16)Keys3[3],
    (unsigned __int16)Keys3[4],
    (unsigned __int16)Keys3[5],
    (unsigned __int16)Keys3[6],
    (unsigned __int16)Keys3[7],
    (unsigned __int16)Keys3[8],
    (unsigned __int16)Keys3[9],
    (unsigned __int16)Keys3[10],
    (unsigned __int16)Keys3[11],
    (unsigned __int16)Keys3[12],
    (unsigned __int16)Keys3[13],
    (unsigned __int16)Keys3[14],
    (unsigned __int16)Keys3[15]);
  cfg_set_value("Software\\epsxe\\config", "Keys3", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)Keys4[0],
    (unsigned __int16)Keys4[1],
    (unsigned __int16)Keys4[2],
    (unsigned __int16)Keys4[3],
    (unsigned __int16)Keys4[4],
    (unsigned __int16)Keys4[5],
    (unsigned __int16)Keys4[6],
    (unsigned __int16)Keys4[7],
    (unsigned __int16)Keys4[8],
    (unsigned __int16)Keys4[9],
    (unsigned __int16)Keys4[10],
    (unsigned __int16)Keys4[11],
    (unsigned __int16)Keys4[12],
    (unsigned __int16)Keys4[13],
    (unsigned __int16)Keys4[14],
    (unsigned __int16)Keys4[15]);
  cfg_set_value("Software\\epsxe\\config", "Keys4", (BYTE *)Buffer);
  sprintf(Buffer, "%d", country_setting);
  cfg_set_value("Software\\epsxe\\config", "Country", (BYTE *)Buffer);
  sprintf(Buffer, "%d", version_setting);
  cfg_set_value("Software\\epsxe\\config", "Version", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d",
    controller_port_modes[0],
    controller_port_modes[1],
    controller_port_modes[2],
    controller_port_modes[3]);
  cfg_set_value("Software\\epsxe\\config", "GamepadType", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", pad_analog_mode_flags[0], dword_4FD8E4, dword_4FD8E8, dword_4FD8EC);
  cfg_set_value("Software\\epsxe\\config", "GamepadSubType", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    LOWORD(GamepadAxis[0]),
    HIWORD(GamepadAxis[0]),
    LOWORD(GamepadAxis[1]),
    HIWORD(GamepadAxis[1]),
    LOWORD(GamepadAxis[2]),
    HIWORD(GamepadAxis[2]),
    LOWORD(GamepadAxis[3]),
    HIWORD(GamepadAxis[3]),
    LOWORD(GamepadAxis[4]),
    HIWORD(GamepadAxis[4]),
    LOWORD(GamepadAxis[5]),
    HIWORD(GamepadAxis[5]),
    LOWORD(GamepadAxis[6]),
    HIWORD(GamepadAxis[6]),
    LOWORD(GamepadAxis[7]),
    HIWORD(GamepadAxis[7]));
  cfg_set_value("Software\\epsxe\\config", "GamepadAxis", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", g_PlayerDeviceMap1[0], g_PlayerDeviceMap2, g_PlayerDeviceMap3, g_PlayerDeviceMap4[0]);
  cfg_set_value("Software\\epsxe\\config", "GamepadMotorType", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", g_EffectType2[0], dword_4FD8C0, dword_4FD8C4, dword_4FD8C8[0]);
  cfg_set_value("Software\\epsxe\\config", "GamepadSMotorType", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", g_EffectType1[0], dword_4FD8D0, dword_4FD8D4, dword_4FD8D8);
  cfg_set_value("Software\\epsxe\\config", "GamepadBMotorType", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)ppf_enabled);
  cfg_set_value("Software\\epsxe\\config", "AutoPpfLoad", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)multitap_1);
  cfg_set_value("Software\\epsxe\\config", "Multitap1", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCdromEnabled);
  cfg_set_value("Software\\epsxe\\config", "SubchannelW9xCdromEnabled", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCaching);
  cfg_set_value("Software\\epsxe\\config", "SubchannelW9xCaching", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCachingLG);
  cfg_set_value("Software\\epsxe\\config", "SubchannelW9xCachingLG", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCdromEnabled);
  cfg_set_value("Software\\epsxe\\config", "SubchannelW2kCdromEnabled", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCaching);
  cfg_set_value("Software\\epsxe\\config", "SubchannelW2kCaching", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCachingLG);
  cfg_set_value("Software\\epsxe\\config", "SubchannelW2kCachingLG", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)console_allocated);
  return cfg_set_value("Software\\epsxe\\config", "Logswindow", (BYTE *)Buffer);
}

int cfg_cdrom_set_hain_target_lun()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%d", cdrom_haid);
  cfg_set_value("Software\\epsxe\\config\\cdrom9x", "CdromHain", (BYTE *)Buffer);
  sprintf(Buffer, "%d", cdrom_target);
  cfg_set_value("Software\\epsxe\\config\\cdrom9x", "CdromTarget", (BYTE *)Buffer);
  sprintf(Buffer, "%d", cdrom_lun);
  return cfg_set_value("Software\\epsxe\\config\\cdrom9x", "CdromLun", (BYTE *)Buffer);
}

int cfg_cdrom_set_letter()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%d", cdrom_letter);
  return cfg_set_value("Software\\epsxe\\config", "CdromLetter", (BYTE *)Buffer);
}

int cfg_cdrom_iso_set_path()
{
  return cfg_set_value("Software\\epsxe\\config", "IsoDirectory", (BYTE *)IsoDirectory);
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char CdromPlugin[0x400];
unsigned short GamepadAxis[0x10];
unsigned char IsoDirectory[0x400];
unsigned short Keys1[10] = {0xcb, 0xcd, 0xc8, 0xd0, 0x20, 0x2d, 0x2c, 0x1f, 0x11, 0x12};
unsigned short Keys2[16] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned short Keys3[16] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned short Keys4[16] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned char NetPlugin[0x400];
unsigned char SoundPlugin[0x400];
unsigned char SubchannelW2kCachingLG;
unsigned char SubchannelW2kCdromEnabled;
unsigned char SubchannelW9xCachingLG;
unsigned char SubchannelW9xCdromEnabled;
unsigned char VideoPlugin[0x400];
unsigned char create_window_flag = 0x1;
unsigned int dword_4FD8C4;
unsigned int dword_4FD8D0;
unsigned int dword_4FD8D4;
unsigned int dword_4FD8D8;
unsigned int dword_4FD8E4;
unsigned int dword_4FD8E8;
unsigned int dword_4FD8EC;
unsigned int g_EffectType1[1];
unsigned int g_PlayerDeviceMap2;
unsigned int g_PlayerDeviceMap3;
unsigned int mdec_disable;
unsigned char setup_wizard_required = 0x0;
unsigned char sound_use_xa;
unsigned int version_setting;
