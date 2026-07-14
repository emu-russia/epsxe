#include "pch.h"
INT_PTR __stdcall w9x_cdrom_settings(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  LRESULT v5; // eax
  LRESULT v6; // eax
  int v7; // ecx
  int v8; // edx
  signed int v9; // ebp
  char *v10; // esi
  char lParam[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( a2 == 272 )
  {
    load_winaspi_dll();
    init_aspi();
    free_winaspi_dll();
    v9 = 0;
    if ( HIBYTE(dword_4FD9BC) )
    {
      v10 = byte_504FE9;
      do
      {
        sprintf(
          lParam,
          "%d:%d:%d %08s  %016s  %04s",
          *(_DWORD *)(v10 + 43),
          *(_DWORD *)(v10 + 47),
          *(_DWORD *)(v10 + 51),
          v10 - 9,
          v10,
          v10 + 17);
        SendDlgItemMessageA(hDlg, 1081, CB_ADDSTRING, 0, (LPARAM)lParam);
        if ( *(_DWORD *)(v10 + 43) == cdrom_haid
          && *(_DWORD *)(v10 + 47) == cdrom_target
          && *(_DWORD *)(v10 + 51) == cdrom_lun )
        {
          SendDlgItemMessageA(hDlg, 1081, 0x14Eu, v9, 0);
        }
        ++v9;
        v10 += 64;
      }
      while ( v9 < HIBYTE(dword_4FD9BC) );
    }
    SendDlgItemMessageA(hDlg, 1136, BM_SETCHECK, (unsigned __int8)SubchannelW9xCdromEnabled, 0);
    SendDlgItemMessageA(hDlg, 1137, BM_SETCHECK, (unsigned __int8)SubchannelW9xCaching, 0);
    SendDlgItemMessageA(hDlg, 1138, BM_SETCHECK, (unsigned __int8)SubchannelW9xCachingLG, 0);
    return 1;
  }
  else
  {
    if ( a2 != 273 )
      return 0;
    if ( (unsigned __int16)a3 == 1079 )
    {
      v5 = SendDlgItemMessageA(hDlg, 1081, CB_GETCURSEL, 0, 0);
      if ( v5 != -1 && v5 < HIBYTE(dword_4FD9BC) )
      {
        v6 = v5 << 6;
        v7 = *(int *)((char *)&dword_505018 + v6);
        cdrom_haid = *(int *)((char *)&dword_505014 + v6);
        v8 = *(int *)((char *)dword_50501C + v6);
        cdrom_target = v7;
        cdrom_lun = v8;
      }
      SubchannelW9xCdromEnabled = SendDlgItemMessageA(hDlg, 1136, BM_GETCHECK, 0, 0);
      SubchannelW9xCaching = SendDlgItemMessageA(hDlg, 1137, BM_GETCHECK, 0, 0);
      SubchannelW9xCachingLG = SendDlgItemMessageA(hDlg, 1138, BM_GETCHECK, 0, 0);
      EndDialog(hDlg, 1);
      cdrom_set_hain_target_lun();
      return 1;
    }
    else
    {
      if ( (unsigned __int16)a3 != 1080 )
        return 0;
      EndDialog(hDlg, 1);
      return 1;
    }
  }
}
