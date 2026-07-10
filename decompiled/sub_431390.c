#include "pch.h"
int sub_431390()
{
  HMODULE LibraryA; // eax
  FARPROC SendASPI32Command; // eax

  LibraryA = LoadLibraryA(aWNASPI32DLL);
  hCdrModule = LibraryA;
  if ( LibraryA
    && (GetASPI32SupportInfo = GetProcAddress(LibraryA, aGetaspi32suppo),
        SendASPI32Command = GetProcAddress(hCdrModule, aSendaspi32comm),
        dword_4FFF68 = (int (__cdecl *)(_DWORD))SendASPI32Command,
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
