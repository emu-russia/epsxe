#include "pch.h"
HMODULE net_resume()
{
  HMODULE result; // eax

  result = (HMODULE)network_enabled;
  if ( network_enabled )
  {
    result = hNetModule;
    if ( hNetModule )
      return (HMODULE)NETresume(hOutputWnd);
  }
  return result;
}
