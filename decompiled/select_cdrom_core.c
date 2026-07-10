#include "pch.h"
char sub_4223C0()
{
  int v0; // eax
  struct _OSVERSIONINFOA VersionInformation; // [esp+8h] [ebp-94h] BYREF

  LOBYTE(v0) = 0;
  if ( !strcmp((const char *)&byte_8B2180, aNull) )
  {
    memset(&VersionInformation, 0, sizeof(VersionInformation));
    VersionInformation.dwOSVersionInfoSize = 148;
    GetVersionExA(&VersionInformation);
    if ( VersionInformation.dwPlatformId == 2 )
    {
      LOBYTE(v0) = sprintf((char *const)&byte_8B2180, aW2kcdrcore);
    }
    else
    {
      v0 = sub_431390();
      if ( !v0 )
      {
        init_aspi();
        sub_4313E0();
        LOBYTE(v0) = HIBYTE(dword_4FD9BC);
        if ( HIBYTE(dword_4FD9BC) )
        {
          cdrom_hain = dword_505014;
          cdrom_target = dword_505018;
          cdrom_lun = dword_50501C;
          LOBYTE(v0) = sprintf((char *const)&byte_8B2180, aW9xcdrcore);
        }
      }
    }
  }
  return v0;
}
