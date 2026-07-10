#include "pch.h"
HMODULE net_close()
{
  HMODULE result; // eax

  result = (HMODULE)dword_4FD99C;
  if ( dword_4FD99C )
  {
    result = dword_4FD998;
    if ( dword_4FD998 )
    {
      if ( !byte_45696C )
      {
        dbg_print(aClosingNet);
        NETclose();
        byte_45696C = 1;
      }
      dbg_print(aShutdownNet);
      return (HMODULE)NETshutdown();
    }
  }
  return result;
}
