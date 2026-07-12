#include "pch.h"
HMODULE net_pause()
{
  HMODULE result; // eax

  result = (HMODULE)network_enabled;
  if ( network_enabled )
  {
    result = hNetModule;
    if ( hNetModule )
      return NETpause();
  }
  return result;
}
