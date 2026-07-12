#include "pch.h"
int load_win_aspi_silent()
{
  HMODULE LibraryA; // eax
  FARPROC SendASPI32Command; // eax

  LibraryA = LoadLibraryA("WNASPI32.DLL");
  hCdrModule = LibraryA;
  if ( LibraryA
    && (GetASPI32SupportInfo = GetProcAddress(LibraryA, "GetASPI32SupportInfo"),
        SendASPI32Command = GetProcAddress(hCdrModule, "SendASPI32Command"),
        SendASPI32Command_cb = (int (__cdecl *)(_DWORD))SendASPI32Command,
        GetASPI32SupportInfo)
    && SendASPI32Command )
  {
    return 0;
  }
  else
  {
    return -1;
  }
}
