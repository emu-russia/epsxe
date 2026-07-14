#include "pch.h"
int issue_big_motor()
{
  int result; // eax

  if ( dword_4FC45C )
    return Big_Motor();
  joy_init();
  result = dword_4FC45C;
  if ( dword_4FC45C )
    return Big_Motor();
  return result;
}
