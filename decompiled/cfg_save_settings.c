#include "pch.h"
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
