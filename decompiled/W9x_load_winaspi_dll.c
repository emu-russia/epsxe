#include "pch.h"
int (__cdecl *W9x_load_winaspi_dll())(LPSRB)
{
  HMODULE LibraryA; // eax
  int (__cdecl *result)(LPSRB); // eax

  LibraryA = LoadLibraryA("WNASPI32.DLL");
  hCdrModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading WNASPI32.DLL\n");
  *(_DWORD *)GetASPI32SupportInfo = GetProcAddress(LibraryA, "GetASPI32SupportInfo");
  result = (int (__cdecl *)(LPSRB))GetProcAddress(hCdrModule, "SendASPI32Command");
  SendASPI32Command_cb = result;
  if ( !*(_DWORD *)GetASPI32SupportInfo || !result )
    fatal_error_with_message_box("Error loading WNASPI32.DLL\n");
  return result;
}
