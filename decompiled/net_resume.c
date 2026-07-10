#include "pch.h"
HMODULE net_resume()
{
  HMODULE result; // eax

  result = (HMODULE)dword_4FD99C;
  if ( dword_4FD99C )
  {
    result = hNetModule;
    if ( hNetModule )
      return (HMODULE)NETresume(hSaveLoadWnd);
  }
  return result;
}
