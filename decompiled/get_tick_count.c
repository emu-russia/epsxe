#include "pch.h"
DWORD get_tick_count()
{
  DWORD result; // eax

  result = GetTickCount();
  last_tick_count = result;
  return result;
}
