#include "pch.h"
HMODULE net_close()
{
  HMODULE result; // eax

  result = (HMODULE)network_enabled;
  if ( network_enabled )
  {
    result = hNetModule;
    if ( hNetModule )
    {
      if ( !byte_45696C )
      {
        dbg_print(" * Closing net ...\n");
        NETclose();
        byte_45696C = 1;
      }
      dbg_print(" * Shutdown net ...\n");
      return NETshutdown();
    }
  }
  return result;
}
