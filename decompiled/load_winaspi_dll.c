#include "pch.h"
FARPROC load_winaspi_dll()
{
  HMODULE LibraryA; // eax
  FARPROC result; // eax

  LibraryA = LoadLibraryA("WNASPI32.DLL");
  hCdrModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading WNASPI32.DLL\n");
  GetASPI32SupportInfo = GetProcAddress(LibraryA, "GetASPI32SupportInfo");
  result = GetProcAddress(hCdrModule, "SendASPI32Command");
  SendASPI32Command_cb = (int (__cdecl *)(_DWORD))result;
  if ( !GetASPI32SupportInfo || !result )
    fatal_error_with_message_box("Error loading WNASPI32.DLL\n");
  return result;
}
