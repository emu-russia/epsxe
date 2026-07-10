#include "pch.h"
int load_settings()
{
  int v1; // [esp+0h] [ebp-408h] BYREF
  unsigned int v2; // [esp+4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( reg_get_value(SubKey, aVideoPlugin, (LPBYTE)Buffer) )
    sprintf((char *const)byte_8B1980, aNull);
  else
    sprintf((char *const)byte_8B1980, "%s", Buffer);
  if ( reg_get_value(SubKey, aSoundplugin, (LPBYTE)Buffer) )
    sprintf((char *const)byte_8B1D80, aSpucore);
  else
    sprintf((char *const)byte_8B1D80, "%s", Buffer);
  if ( reg_get_value(SubKey, aCdromplugin, (LPBYTE)Buffer) )
    sprintf((char *const)byte_8B2180, aNull);
  else
    sprintf((char *const)byte_8B2180, "%s", Buffer);
  if ( reg_get_value(SubKey, aNetplugin, (LPBYTE)Buffer) )
    sprintf((char *const)byte_8B4180, aDisabled);
  else
    sprintf((char *const)byte_8B4180, "%s", Buffer);
  if ( reg_get_value(SubKey, aBiosname, byte_8B2980) == -1 )
    sprintf((char *const)byte_8B2980, aBiosScph1001Bi);
  if ( !reg_get_value(SubKey, aSubchannelw9xc, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCdromEnabled = v1;
  }
  if ( !reg_get_value(SubKey, aSubchannelw9xc_0, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCaching = v1;
  }
  if ( !reg_get_value(SubKey, aSubchannelw9xc_1, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW9xCachingLG = v1;
  }
  if ( !reg_get_value(SubKey, aSubchannelw2kc, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCdromEnabled = v1;
  }
  if ( !reg_get_value(SubKey, aSubchannelw2kc_0, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCaching = v1;
  }
  if ( !reg_get_value(SubKey, aSubchannelw2kc_1, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    SubchannelW2kCachingLG = v1;
  }
  if ( !reg_get_value(SubKey, aSoundenabled, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_enabled = v1;
  }
  if ( !reg_get_value(SubKey, aSoundxa, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_use_xa = v1;
  }
  if ( !reg_get_value(SubKey, aSoundcdda, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    sound_use_cdda = v1;
  }
  if ( !reg_get_value(SubKey, aKeys1, (LPBYTE)Buffer) )
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
  if ( !reg_get_value(SubKey, aKeys2, (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &unk_455FE8,
      &word_455FEA,
      &unk_455FEC,
      &word_455FEE,
      &unk_455FF0,
      &word_455FF2,
      &unk_455FF4,
      &word_455FF6,
      &unk_455FF8,
      &word_455FFA,
      &dword_455FFC,
      (char *)&dword_455FFC + 2,
      &unk_456000,
      &word_456002,
      &dword_456004,
      (char *)&dword_456004 + 2);
  if ( !reg_get_value(SubKey, aKeys3, (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &unk_456008,
      &word_45600A,
      &unk_45600C,
      &word_45600E,
      &unk_456010,
      &word_456012,
      &unk_456014,
      &word_456016,
      &unk_456018,
      &word_45601A,
      &dword_45601C,
      (char *)&dword_45601C + 2,
      &unk_456020,
      &word_456022,
      &dword_456024,
      (char *)&dword_456024 + 2);
  if ( !reg_get_value(SubKey, aKeys4, (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      &unk_456028,
      &word_45602A,
      &unk_45602C,
      &word_45602E,
      &unk_456030,
      &word_456032,
      &unk_456034,
      &word_456036,
      &unk_456038,
      &word_45603A,
      &unk_45603C,
      &word_45603E,
      &dword_456040,
      (char *)&dword_456040 + 2,
      &unk_456044,
      &word_456046);
  if ( !reg_get_value(SubKey, aCdromletter, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    cdrom_letter = v1;
  }
  if ( !reg_get_value(SubKey, aLogswindow, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    console_allocated = v1;
  }
  if ( !reg_get_value(SubKey, aAutoppfload, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    if ( (_BYTE)v1 )
      auto_ppf_load = 1;
  }
  if ( !reg_get_value(SubKey, aMultitap1, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    if ( (_BYTE)v1 )
      multitap_1 = 1;
  }
  if ( !reg_get_value(aSoftwareEpsxeC_0, aCdromhain, (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_hain);
  if ( !reg_get_value(aSoftwareEpsxeC_0, aCdromtarget, (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_target);
  if ( !reg_get_value(aSoftwareEpsxeC_0, aCdromlun, (LPBYTE)Buffer) )
    sscanf(Buffer, "%d", &cdrom_lun);
  if ( reg_get_value(SubKey, aMemcard1, (LPBYTE)Buffer) )
    sprintf((char *const)byte_8B3180, aMemcardsEpsxe0);
  else
    sprintf((char *const)byte_8B3180, "%s", Buffer);
  if ( reg_get_value(SubKey, aMemcard2, (LPBYTE)Buffer) )
    sprintf((char *const)byte_8B3580, aMemcardsEpsxe0_0);
  else
    sprintf((char *const)byte_8B3580, "%s", Buffer);
  if ( !reg_get_value(SubKey, aCountry, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d", &v1);
    country_setting = (unsigned __int8)v1;
  }
  if ( reg_get_value(SubKey, aVersion, (LPBYTE)Buffer) )
  {
    mdectiming = 1;
    mdec_disable = 0;
    if ( create_window_flag )
      byte_45B8E0 = 1;
    version_setting = 67072;
    sprintf(Buffer, "%d", 67072);
    reg_set_value(SubKey, aVersion, (BYTE *)Buffer);
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
      reg_set_value(SubKey, aVersion, (BYTE *)Buffer);
    }
  }
  if ( !reg_get_value(SubKey, aGamepadtype, (LPBYTE)Buffer) )
  {
    sscanf(Buffer, "%d,%d,%d,%d", dword_456048, &dword_45604C, &dword_456050, &dword_456054);
    if ( dword_456048[0] == 5
      || dword_456048[0] == 6
      || dword_456048[0] == 3
      || dword_456048[0] == 2
      || dword_45604C == 2 )
    {
      dword_4FD8DC = 1;
    }
  }
  if ( !reg_get_value(SubKey, aGamepadsubtype, (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", dword_4FD8E0, &dword_4FD8E4, &dword_4FD8E8, &dword_4FD8EC);
  if ( !reg_get_value(SubKey, aGamepadaxis, (LPBYTE)Buffer) )
    sscanf(
      Buffer,
      "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      dword_4FD88C,
      (char *)dword_4FD88C + 2,
      dword_4FD890,
      (char *)dword_4FD890 + 2,
      &unk_4FD894,
      &word_4FD896,
      &unk_4FD898,
      &word_4FD89A,
      &unk_4FD89C,
      &word_4FD89E,
      &dword_4FD8A0,
      (char *)&dword_4FD8A0 + 2,
      &unk_4FD8A4,
      &word_4FD8A6,
      dword_4FD8A8,
      (char *)dword_4FD8A8 + 2);
  if ( !reg_get_value(SubKey, aGamepadmotorty, (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", dword_4FD8AC, &dword_4FD8B0, &dword_4FD8B4, dword_4FD8B8);
  if ( !reg_get_value(SubKey, aGamepadsmotort, (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", dword_4FD8BC, &dword_4FD8C0, &dword_4FD8C4, dword_4FD8C8);
  if ( !reg_get_value(SubKey, aGamepadbmotort, (LPBYTE)Buffer) )
    sscanf(Buffer, "%d,%d,%d,%d", dword_4FD8CC, &dword_4FD8D0, &dword_4FD8D4, &dword_4FD8D8);
  if ( reg_get_value(SubKey, aIsodirectory, (LPBYTE)Buffer) )
    return sprintf((char *const)byte_8B3980, asc_44B034);
  else
    return sprintf((char *const)byte_8B3980, "%s", Buffer);
}
