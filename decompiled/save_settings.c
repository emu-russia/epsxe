#include "pch.h"
int sub_401C00()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  reg_set_value(SubKey, aVideoPlugin, &byte_8B1980);
  reg_set_value(SubKey, aSoundplugin, &byte_8B1D80);
  reg_set_value(SubKey, aCdromplugin, &byte_8B2180);
  reg_set_value(SubKey, aNetplugin, &byte_8B4180);
  reg_set_value(SubKey, aBiosname, &byte_8B2980);
  reg_set_value(SubKey, aMemcard1, &byte_8B3180);
  reg_set_value(SubKey, aMemcard2, &byte_8B3580);
  sprintf(Buffer, "%d", (unsigned __int8)sound_enabled);
  reg_set_value(SubKey, aSoundenabled, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)sound_use_xa);
  reg_set_value(SubKey, aSoundxa, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)sound_use_cdda);
  reg_set_value(SubKey, aSoundcdda, (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)word_455FC8,
    HIWORD(word_455FC8),
    (unsigned __int16)word_455FCC,
    HIWORD(word_455FCC),
    word_455FD0[0],
    word_455FD0[1],
    word_455FD0[2],
    (unsigned __int16)word_455FD6,
    (unsigned __int16)word_455FD8,
    HIWORD(word_455FD8),
    (unsigned __int16)word_455FDC,
    HIWORD(word_455FDC),
    (unsigned __int16)word_455FE0,
    HIWORD(word_455FE0),
    (unsigned __int16)word_455FE4,
    HIWORD(word_455FE4));
  reg_set_value(SubKey, aKeys1, (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    unk_455FE8,
    (unsigned __int16)word_455FEA,
    unk_455FEC,
    (unsigned __int16)word_455FEE,
    unk_455FF0,
    (unsigned __int16)word_455FF2,
    unk_455FF4,
    (unsigned __int16)word_455FF6,
    unk_455FF8,
    (unsigned __int16)word_455FFA,
    (unsigned __int16)dword_455FFC,
    HIWORD(dword_455FFC),
    unk_456000,
    (unsigned __int16)word_456002,
    (unsigned __int16)dword_456004,
    HIWORD(dword_456004));
  reg_set_value(SubKey, aKeys2, (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    unk_456008,
    (unsigned __int16)word_45600A,
    unk_45600C,
    (unsigned __int16)word_45600E,
    unk_456010,
    (unsigned __int16)word_456012,
    unk_456014,
    (unsigned __int16)word_456016,
    unk_456018,
    (unsigned __int16)word_45601A,
    (unsigned __int16)dword_45601C,
    HIWORD(dword_45601C),
    unk_456020,
    (unsigned __int16)word_456022,
    (unsigned __int16)dword_456024,
    HIWORD(dword_456024));
  reg_set_value(SubKey, aKeys3, (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    unk_456028,
    (unsigned __int16)word_45602A,
    unk_45602C,
    (unsigned __int16)word_45602E,
    unk_456030,
    (unsigned __int16)word_456032,
    unk_456034,
    (unsigned __int16)word_456036,
    unk_456038,
    (unsigned __int16)word_45603A,
    unk_45603C,
    (unsigned __int16)word_45603E,
    (unsigned __int16)dword_456040,
    HIWORD(dword_456040),
    unk_456044,
    (unsigned __int16)word_456046);
  reg_set_value(SubKey, aKeys4, (BYTE *)Buffer);
  sprintf(Buffer, "%d", country_setting);
  reg_set_value(SubKey, aCountry, (BYTE *)Buffer);
  sprintf(Buffer, "%d", version_setting);
  reg_set_value(SubKey, aVersion, (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_456048, dword_45604C, dword_456050, dword_456054);
  reg_set_value(SubKey, aGamepadtype, (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8E0[0], dword_4FD8E4, dword_4FD8E8, dword_4FD8EC);
  reg_set_value(SubKey, aGamepadsubtype, (BYTE *)Buffer);
  sprintf(
    Buffer,
    "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
    (unsigned __int16)dword_4FD88C,
    HIWORD(dword_4FD88C),
    (unsigned __int16)dword_4FD890,
    HIWORD(dword_4FD890),
    unk_4FD894,
    (unsigned __int16)word_4FD896,
    unk_4FD898,
    (unsigned __int16)word_4FD89A,
    unk_4FD89C,
    (unsigned __int16)word_4FD89E,
    (unsigned __int16)dword_4FD8A0,
    HIWORD(dword_4FD8A0),
    unk_4FD8A4,
    (unsigned __int16)word_4FD8A6,
    LOWORD(dword_4FD8A8[0]),
    HIWORD(dword_4FD8A8[0]));
  reg_set_value(SubKey, aGamepadaxis, (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8AC[0], dword_4FD8B0, dword_4FD8B4, dword_4FD8B8[0]);
  reg_set_value(SubKey, aGamepadmotorty, (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8BC[0], dword_4FD8C0, dword_4FD8C4, dword_4FD8C8[0]);
  reg_set_value(SubKey, aGamepadsmotort, (BYTE *)Buffer);
  sprintf(Buffer, "%d,%d,%d,%d", dword_4FD8CC[0], dword_4FD8D0, dword_4FD8D4, dword_4FD8D8);
  reg_set_value(SubKey, aGamepadbmotort, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)auto_ppf_load);
  reg_set_value(SubKey, aAutoppfload, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)multitap_1);
  reg_set_value(SubKey, aMultitap1, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCdromEnabled);
  reg_set_value(SubKey, aSubchannelw9xc, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCaching);
  reg_set_value(SubKey, aSubchannelw9xc_0, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW9xCachingLG);
  reg_set_value(SubKey, aSubchannelw9xc_1, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCdromEnabled);
  reg_set_value(SubKey, aSubchannelw2kc, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCaching);
  reg_set_value(SubKey, aSubchannelw2kc_0, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)SubchannelW2kCachingLG);
  reg_set_value(SubKey, aSubchannelw2kc_1, (BYTE *)Buffer);
  sprintf(Buffer, "%d", (unsigned __int8)console_allocated);
  return reg_set_value(SubKey, aLogswindow, (BYTE *)Buffer);
}
