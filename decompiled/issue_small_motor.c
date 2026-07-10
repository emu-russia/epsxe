#include "pch.h"
int issue_small_motor()
{
  int result; // eax

  if ( dword_4FC45C )
    return Small_Motor();
  joy_init();
  result = dword_4FC45C;
  if ( dword_4FC45C )
    return Small_Motor();
  return result;
}
