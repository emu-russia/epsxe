#include "pch.h"
int __cdecl gte_clamp(int a1, int a2)
{
  int result; // eax

  result = a2;
  if ( a2 >= -32768 )
  {
    if ( a2 > 0x7FFF )
    {
      dword_8A7FFC |= a1;
      return 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= a1;
    return -32768;
  }
  return result;
}
