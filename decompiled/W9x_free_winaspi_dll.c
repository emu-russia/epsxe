#include "pch.h"
HMODULE W9x_free_winaspi_dll()
{
  HMODULE result; // eax

  result = hCdrModule;
  if ( hCdrModule )
  {
    FreeLibrary(hCdrModule);
    if ( *(_DWORD *)GetASPI32SupportInfo )
      *(_DWORD *)GetASPI32SupportInfo = 0;
    result = (HMODULE)SendASPI32Command_cb;
    if ( SendASPI32Command_cb )
      SendASPI32Command_cb = nullptr;
  }
  return result;
}
