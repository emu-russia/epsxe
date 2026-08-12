#include "pch.h"
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
