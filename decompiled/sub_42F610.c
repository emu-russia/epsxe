#include "pch.h"
HMODULE sub_42F610()
{
  HMODULE result; // eax

  result = (HMODULE)dword_4FD99C;
  if ( dword_4FD99C )
  {
    result = dword_4FD998;
    if ( dword_4FD998 )
      return (HMODULE)NETresume(dword_4FD98C);
  }
  return result;
}
