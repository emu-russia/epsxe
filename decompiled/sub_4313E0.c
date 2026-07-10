#include "pch.h"
HMODULE sub_4313E0()
{
  HMODULE result; // eax

  result = hLibModule;
  if ( hLibModule )
  {
    FreeLibrary(hLibModule);
    if ( GetASPI32SupportInfo )
      GetASPI32SupportInfo = nullptr;
    result = (HMODULE)dword_4FFF68;
    if ( dword_4FFF68 )
      dword_4FFF68 = nullptr;
  }
  return result;
}
