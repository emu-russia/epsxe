#include "pch.h"
HMODULE free_winaspi_dll()
{
  HMODULE result; // eax

  result = hCdrModule;
  if ( hCdrModule )
  {
    FreeLibrary(hCdrModule);
    if ( GetASPI32SupportInfo )
      GetASPI32SupportInfo = nullptr;
    result = (HMODULE)SendASPI32Command_cb;
    if ( SendASPI32Command_cb )
      SendASPI32Command_cb = nullptr;
  }
  return result;
}
