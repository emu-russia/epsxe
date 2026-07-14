#include "pch.h"
char select_cdrom_core()
{
  int win_aspi_silent; // eax
  struct _OSVERSIONINFOA VersionInformation; // [esp+8h] [ebp-94h] BYREF

  LOBYTE(win_aspi_silent) = 0;
  if ( !strcmp((const char *)CdromPlugin, "NULL") )
  {
    memset(&VersionInformation, 0, sizeof(VersionInformation));
    VersionInformation.dwOSVersionInfoSize = 148;
    GetVersionExA(&VersionInformation);
    if ( VersionInformation.dwPlatformId == 2 )
    {
      LOBYTE(win_aspi_silent) = sprintf((char *const)CdromPlugin, "W2KCDRCORE");
    }
    else
    {
      win_aspi_silent = load_win_aspi_silent();
      if ( !win_aspi_silent )
      {
        init_aspi();
        free_winaspi_dll();
        LOBYTE(win_aspi_silent) = HIBYTE(dword_4FD9BC);
        if ( HIBYTE(dword_4FD9BC) )
        {
          cdrom_haid = dword_505014;
          cdrom_target = dword_505018;
          cdrom_lun = dword_50501C[0];
          LOBYTE(win_aspi_silent) = sprintf((char *const)CdromPlugin, "W9XCDRCORE");
        }
      }
    }
  }
  return win_aspi_silent;
}
