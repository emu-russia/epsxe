#include "pch.h"
FARPROC load_winaspi_dll()
{
  HMODULE LibraryA; // eax
  FARPROC result; // eax

  LibraryA = LoadLibraryA(aWNASPI32DLL);
  hCdrModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(aErrorLoadingWn);
  GetASPI32SupportInfo = GetProcAddress(LibraryA, aGetaspi32suppo);
  result = GetProcAddress(hCdrModule, aSendaspi32comm);
  dword_4FFF68 = (int (__cdecl *)(_DWORD))result;
  if ( !GetASPI32SupportInfo || !result )
    fatal_error_with_message_box(aErrorLoadingWn_0);
  return result;
}
