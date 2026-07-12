#include "pch.h"
int save_settings()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  reg_set_value("Software\\epsxe\\config", "VideoPlugin", VideoPlugin);
  reg_set_value("Software\\epsxe\\config", "SoundPlugin", SoundPlugin);
  reg_set_value("Software\\epsxe\\config", "CdromPlugin", CdromPlugin);
  reg_set_value("Software\\epsxe\\config", "NetPlugin", NetPlugin);
  reg_set_value("Software\\epsxe\\config", "BiosName", bios_name);
  reg_set_value("Software\\epsxe\\config", "Memcard1", Memcard1);
  reg_set_value("Software\\epsxe\\config", "Memcard2", Memcard2);
  sprintf(Buffer, "%d", (unsigned __int8)sound_enabled);
  reg_set_value("Software\\epsxe\\config", "SoundEnabled", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)sound_use_xa);
  reg_set_value("Software\\epsxe\\config", "SoundXA", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)sound_use_cdda);
  reg_set_value("Software\\epsxe\\config", "SoundCDDA", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)word_455FC8,
    (unsigned __int16)word_455FCA,
    (unsigned __int16)word_455FCC,
    (unsigned __int16)word_455FCE,
    (unsigned __int16)word_455FD0,
    (unsigned __int16)word_455FD2,
    (unsigned __int16)word_455FD4,
    (unsigned __int16)word_455FD6,
    (unsigned __int16)word_455FD8,
    (unsigned __int16)word_455FDA,
    (unsigned __int16)word_455FDC,
    (unsigned __int16)word_455FDE,
    (unsigned __int16)word_455FE0,
    (unsigned __int16)word_455FE2,
    (unsigned __int16)word_455FE4,
    (unsigned __int16)word_455FE6);
  reg_set_value("Software\\epsxe\\config", "Keys1", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)word_455FE8,
    (unsigned __int16)word_455FEA,
    (unsigned __int16)word_455FEC,
    (unsigned __int16)word_455FEE,
    (unsigned __int16)word_455FF0,
    (unsigned __int16)word_455FF2,
    (unsigned __int16)word_455FF4,
    (unsigned __int16)word_455FF6,
    (unsigned __int16)word_455FF8,
    (unsigned __int16)word_455FFA,
    (unsigned __int16)dword_455FFC,
    HIWORD(dword_455FFC),
    (unsigned __int16)word_456000,
    (unsigned __int16)word_456002,
    (unsigned __int16)dword_456004,
    HIWORD(dword_456004));
  reg_set_value("Software\\epsxe\\config", "Keys2", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)word_456008,
    (unsigned __int16)word_45600A,
    (unsigned __int16)word_45600C,
    (unsigned __int16)word_45600E,
    (unsigned __int16)word_456010,
    (unsigned __int16)word_456012,
    (unsigned __int16)word_456014,
    (unsigned __int16)word_456016,
    (unsigned __int16)word_456018,
    (unsigned __int16)word_45601A,
    (unsigned __int16)dword_45601C,
    HIWORD(dword_45601C),
    (unsigned __int16)word_456020,
    (unsigned __int16)word_456022,
    (unsigned __int16)dword_456024,
    HIWORD(dword_456024));
  reg_set_value("Software\\epsxe\\config", "Keys3", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)word_456028,
    (unsigned __int16)word_45602A,
    (unsigned __int16)word_45602C,
    (unsigned __int16)word_45602E,
    (unsigned __int16)word_456030,
    (unsigned __int16)word_456032,
    (unsigned __int16)word_456034,
    (unsigned __int16)word_456036,
    (unsigned __int16)word_456038,
    (unsigned __int16)word_45603A,
    (unsigned __int16)word_45603C,
    (unsigned __int16)word_45603E,
    (unsigned __int16)word_456040,
    (unsigned __int16)word_456042,
    (unsigned __int16)word_456044[0],
    (unsigned __int16)word_456046);
  reg_set_value("Software\\epsxe\\config", "Keys4", (BYTE *)Buffer);
  sprintf(Buffer, "%d", country_setting);
  reg_set_value("Software\\epsxe\\config", "Country", (BYTE *)Buffer);
  sprintf(Buffer, "%d", version_setting);
  reg_set_value("Software\\epsxe\\config", "Version", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_456048[0], dword_45604C, dword_456050, dword_456054);
  reg_set_value("Software\\epsxe\\config", "GamepadType", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8E0[0], dword_4FD8E4, dword_4FD8E8, dword_4FD8EC);
  reg_set_value("Software\\epsxe\\config", "GamepadSubType", (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    LOWORD(word_4FD88C[0]),
    (unsigned __int16)word_4FD88E[0],
    LOWORD(word_4FD890[0]),
    (unsigned __int16)word_4FD892[0],
    (unsigned __int16)word_4FD894,
    (unsigned __int16)word_4FD896,
    (unsigned __int16)word_4FD898,
    (unsigned __int16)word_4FD89A,
    (unsigned __int16)word_4FD89C,
    (unsigned __int16)word_4FD89E,
    (unsigned __int16)word_4FD8A0,
    (unsigned __int16)word_4FD8A2,
    (unsigned __int16)word_4FD8A4,
    (unsigned __int16)word_4FD8A6,
    LOWORD(word_4FD8A8[0]),
    (unsigned __int16)word_4FD8AA);
  reg_set_value("Software\\epsxe\\config", "GamepadAxis", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8AC[0], dword_4FD8B0, dword_4FD8B4, dword_4FD8B8[0]);
  reg_set_value("Software\\epsxe\\config", "GamepadMotorType", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8BC[0], dword_4FD8C0, dword_4FD8C4, dword_4FD8C8[0]);
  reg_set_value("Software\\epsxe\\config", "GamepadSMotorType", (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8CC[0], dword_4FD8D0, dword_4FD8D4, dword_4FD8D8);
  reg_set_value("Software\\epsxe\\config", "GamepadBMotorType", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)auto_ppf_load);
  reg_set_value("Software\\epsxe\\config", "AutoPpfLoad", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)multitap_1);
  reg_set_value("Software\\epsxe\\config", "Multitap1", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCdromEnabled);
  reg_set_value("Software\\epsxe\\config", "SubchannelW9xCdromEnabled", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCaching);
  reg_set_value("Software\\epsxe\\config", "SubchannelW9xCaching", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCachingLG);
  reg_set_value("Software\\epsxe\\config", "SubchannelW9xCachingLG", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCdromEnabled);
  reg_set_value("Software\\epsxe\\config", "SubchannelW2kCdromEnabled", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCaching);
  reg_set_value("Software\\epsxe\\config", "SubchannelW2kCaching", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCachingLG);
  reg_set_value("Software\\epsxe\\config", "SubchannelW2kCachingLG", (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)console_allocated);
  return reg_set_value("Software\\epsxe\\config", "Logswindow", (BYTE *)Buffer);
}
