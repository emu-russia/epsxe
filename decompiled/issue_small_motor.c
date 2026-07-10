#include "pch.h"
int sub_420D30()
{
  int result; // eax

  if ( dword_4FC45C )
    return Small_Motor(1);
  joy_init();
  result = dword_4FC45C;
  if ( dword_4FC45C )
    return Small_Motor(1);
  return result;
}
