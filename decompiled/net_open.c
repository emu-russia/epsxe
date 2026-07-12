#include "pch.h"
int net_open()
{
  int result; // eax

  result = network_enabled;
  if ( network_enabled )
  {
    dbg_print(" * Netplugin open... ");
    NETopen(hOutputWnd);
    result = dbg_print(" ok \n");
    byte_45696C = 0;
  }
  return result;
}
