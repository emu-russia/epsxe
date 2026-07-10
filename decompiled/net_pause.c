#include "pch.h"
HMODULE net_pause()
{
  HMODULE result; // eax

  result = (HMODULE)dword_4FD99C;
  if ( dword_4FD99C )
  {
    result = hNetModule;
    if ( hNetModule )
      return NETpause();
  }
  return result;
}
