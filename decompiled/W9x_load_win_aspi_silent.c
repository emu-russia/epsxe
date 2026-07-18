#include "pch.h"
int W9x_load_win_aspi_silent()
{
  HMODULE LibraryA; // eax
  int (__cdecl *SendASPI32Command)(LPSRB); // eax

  LibraryA = LoadLibraryA("WNASPI32.DLL");
  hCdrModule = LibraryA;
  if ( LibraryA
    && (*(_DWORD *)GetASPI32SupportInfo = GetProcAddress(LibraryA, "GetASPI32SupportInfo"),
        SendASPI32Command = (int (__cdecl *)(LPSRB))GetProcAddress(hCdrModule, "SendASPI32Command"),
        SendASPI32Command_cb = SendASPI32Command,
        *(_DWORD *)GetASPI32SupportInfo)
    && SendASPI32Command )
  {
    return 0;
  }
  else
  {
    return -1;
  }
}
