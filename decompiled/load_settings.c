#include "pch.h"
int load_settings()
{
  int v1; // [esp+0h] [ebp-408h] BYREF
  unsigned int v2; // [esp+4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( reg_get_value("Software\\epsxe\\config", "VideoPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)VideoPlugin, "NULL");
  else
    sprintf((char *const)VideoPlugin, "%s", Buffer);
  if ( reg_get_value("Software\\epsxe\\config", "SoundPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)SoundPlugin, "SPUCORE");
  else
    sprintf((char *const)SoundPlugin, "%s", Buffer);
  if ( reg_get_value("Software\\epsxe\\config", "CdromPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)CdromPlugin, "NULL");
  else
    sprintf((char *const)CdromPlugin, "%s", Buffer);
  if ( reg_get_value("Software\\epsxe\\config", "NetPlugin", (LPBYTE)Buffer) )
    sprintf((char *const)NetPlugin, "DISABLED");
  else
    sprintf((char *const)NetPlugin, "%s", Buffer);
  if ( reg_get_value("Software\\epsxe\\config", "BiosName", bios_name) == -1 )
    sprintf((char *const)bios_name, "bios\\scph1001.bin");
  if ( !reg_get_value("Software\\epsxe\\config", "SubchannelW9xCdromEnabled", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCdromEnabled = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SubchannelW9xCaching", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCaching = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SubchannelW9xCachingLG", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCachingLG = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SubchannelW2kCdromEnabled", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCdromEnabled = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SubchannelW2kCaching", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCaching = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SubchannelW2kCachingLG", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCachingLG = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SoundEnabled", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_enabled = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SoundXA", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_use_xa = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "SoundCDDA", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_use_cdda = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "Keys1", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &word_455FC8,
      &word_455FCA,
      &word_455FCC,
      &word_455FCE,
      &word_455FD0,
      &word_455FD2,
      &word_455FD4,
      &word_455FD6,
      &word_455FD8,
      &word_455FDA,
      &word_455FDC,
      &word_455FDE,
      &word_455FE0,
      &word_455FE2,
      &word_455FE4,
      &word_455FE6);
  if ( !reg_get_value("Software\\epsxe\\config", "Keys2", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &word_455FE8,
      &word_455FEA,
      &word_455FEC,
      &word_455FEE,
      &word_455FF0,
      &word_455FF2,
      &word_455FF4,
      &word_455FF6,
      &word_455FF8,
      &word_455FFA,
      &dword_455FFC,
      (char *)&dword_455FFC + 2,
      &word_456000,
      &word_456002,
      &dword_456004,
      (char *)&dword_456004 + 2);
  if ( !reg_get_value("Software\\epsxe\\config", "Keys3", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &word_456008,
      &word_45600A,
      &word_45600C,
      &word_45600E,
      &word_456010,
      &word_456012,
      &word_456014,
      &word_456016,
      &word_456018,
      &word_45601A,
      &dword_45601C,
      (char *)&dword_45601C + 2,
      &word_456020,
      &word_456022,
      &dword_456024,
      (char *)&dword_456024 + 2);
  if ( !reg_get_value("Software\\epsxe\\config", "Keys4", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &word_456028,
      &word_45602A,
      &word_45602C,
      &word_45602E,
      &word_456030,
      &word_456032,
      &word_456034,
      &word_456036,
      &word_456038,
      &word_45603A,
      &word_45603C,
      &word_45603E,
      &word_456040,
      &word_456042,
      word_456044,
      &word_456046);
  if ( !reg_get_value("Software\\epsxe\\config", "CdromLetter", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    cdrom_letter = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "Logswindow", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    console_allocated = v1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "AutoPpfLoad", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    if ( (_BYTE)v1 )
      auto_ppf_load = 1;
  }
  if ( !reg_get_value("Software\\epsxe\\config", "Multitap1", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    if ( (_BYTE)v1 )
      multitap_1 = 1;
  }
  if ( !reg_get_value("Software\\epsxe\\config\\cdrom9x", "CdromHain", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_haid);
  if ( !reg_get_value("Software\\epsxe\\config\\cdrom9x", "CdromTarget", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_target);
  if ( !reg_get_value("Software\\epsxe\\config\\cdrom9x", "CdromLun", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_lun);
  if ( reg_get_value("Software\\epsxe\\config", "Memcard1", (LPBYTE)Buffer) )
    sprintf((char *const)Memcard1, "memcards\\epsxe000.mcr");
  else
    sprintf((char *const)Memcard1, "%s", Buffer);
  if ( reg_get_value("Software\\epsxe\\config", "Memcard2", (LPBYTE)Buffer) )
    sprintf((char *const)Memcard2, "memcards\\epsxe001.mcr");
  else
    sprintf((char *const)Memcard2, "%s", Buffer);
  if ( !reg_get_value("Software\\epsxe\\config", "Country", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    country_setting = (unsigned __int8)v1;
  }
  if ( reg_get_value("Software\\epsxe\\config", "Version", (LPBYTE)Buffer) )
  {
    mdectiming = 1;
    mdec_disable = 0;
    if ( create_window_flag )
      byte_45B8E0 = 1;
    version_setting = 67072;
    sprintf(Buffer, "%d", 67072);
    reg_set_value("Software\\epsxe\\config", "Version", (BYTE *)Buffer);
  }
  else
  {
    sscanf(Buffer, "%d", &v2);
    version_setting = v2;
    if ( v2 < 0x10600 )
    {
      if ( create_window_flag )
        byte_45B8E0 = 1;
      mdectiming = 1;
      mdec_disable = 0;
      version_setting = 67072;
      sprintf(Buffer, "%d", 67072);
      reg_set_value("Software\\epsxe\\config", "Version", (BYTE *)Buffer);
    }
  }
  if ( !reg_get_value("Software\\epsxe\\config", "GamepadType", (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d,%d,%d,%d", dword_456048, &dword_45604C, &dword_456050, &dword_456054);
    if ( dword_456048[0] == 5
      || dword_456048[0] == 6
      || dword_456048[0] == 3
      || dword_456048[0] == 2
      || dword_45604C == 2 )
    {
      point_device_enabled = 1;
    }
  }
  if ( !reg_get_value("Software\\epsxe\\config", "GamepadSubType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", dword_4FD8E0, &dword_4FD8E4, &dword_4FD8E8, &dword_4FD8EC);
  if ( !reg_get_value("Software\\epsxe\\config", "GamepadAxis", (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      word_4FD88C,
      word_4FD88E,
      word_4FD890,
      word_4FD892,
      &word_4FD894,
      &word_4FD896,
      &word_4FD898,
      &word_4FD89A,
      &word_4FD89C,
      &word_4FD89E,
      &word_4FD8A0,
      &word_4FD8A2,
      &word_4FD8A4,
      &word_4FD8A6,
      word_4FD8A8,
      &word_4FD8AA);
  if ( !reg_get_value("Software\\epsxe\\config", "GamepadMotorType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", g_PlayerDeviceMap1, &g_PlayerDeviceMap2, &g_PlayerDeviceMap3, g_PlayerDeviceMap4);
  if ( !reg_get_value("Software\\epsxe\\config", "GamepadSMotorType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", g_EffectType2, &dword_4FD8C0, &dword_4FD8C4, dword_4FD8C8);
  if ( !reg_get_value("Software\\epsxe\\config", "GamepadBMotorType", (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", g_EffectType1, &dword_4FD8D0, &dword_4FD8D4, &dword_4FD8D8);
  if ( reg_get_value("Software\\epsxe\\config", "IsoDirectory", (LPBYTE)Buffer) )
    return sprintf(IsoDirectory, ".");
  else
    return sprintf(IsoDirectory, "%s", Buffer);
}
