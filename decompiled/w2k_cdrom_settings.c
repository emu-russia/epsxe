#include "pch.h"
INT_PTR __stdcall sub_406DD0(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  LRESULT v5; // eax
  LRESULT v6; // eax
  int i; // ebx
  LRESULT v8; // eax
  CHAR lParam[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( a2 == 272 )
  {
    sprintf(lParam, aFirstcdrom);
    v6 = SendDlgItemMessageA(hDlg, 1133, 0x143u, 0, (LPARAM)lParam);
    if ( !cdrom_letter )
      SendDlgItemMessageA(hDlg, 1133, 0x14Eu, v6, 0);
    for ( i = 65; i <= 90; ++i )
    {
      sprintf(lParam, "%c:\\", i);
      if ( GetDriveTypeA(lParam) == 5 )
      {
        sprintf(lParam, "--%c:--", i);
        v8 = SendDlgItemMessageA(hDlg, 1133, 0x143u, 0, (LPARAM)lParam);
        if ( i == cdrom_letter )
          SendDlgItemMessageA(hDlg, 1133, 0x14Eu, v8, 0);
      }
    }
    SendDlgItemMessageA(hDlg, 1139, 0xF1u, (unsigned __int8)SubchannelW2kCdromEnabled, 0);
    SendDlgItemMessageA(hDlg, 1140, 0xF1u, (unsigned __int8)SubchannelW2kCaching, 0);
    SendDlgItemMessageA(hDlg, 1141, 0xF1u, (unsigned __int8)SubchannelW2kCachingLG, 0);
    return 1;
  }
  else
  {
    if ( a2 != 273 )
      return 0;
    if ( (unsigned __int16)a3 == 1134 )
    {
      v5 = SendDlgItemMessageA(hDlg, 1133, 0x147u, 0, 0);
      if ( v5 != -1 )
      {
        SendDlgItemMessageA(hDlg, 1133, 0x148u, v5, (LPARAM)lParam);
        if ( !strncmp(lParam, aFirstcdrom, 4u) )
          cdrom_letter = 0;
        else
          sscanf(lParam, "--%c:--", &cdrom_letter);
      }
      SubchannelW2kCdromEnabled = SendDlgItemMessageA(hDlg, 1139, 0xF0u, 0, 0);
      SubchannelW2kCaching = SendDlgItemMessageA(hDlg, 1140, 0xF0u, 0, 0);
      SubchannelW2kCachingLG = SendDlgItemMessageA(hDlg, 1141, 0xF0u, 0, 0);
      EndDialog(hDlg, 1);
      cdrom_set_letter();
      return 1;
    }
    else
    {
      if ( (unsigned __int16)a3 != 1135 )
        return 0;
      EndDialog(hDlg, 1);
      return 1;
    }
  }
}
