#include "pch.h"
int __cdecl spucore_write_status_hi(__int16 a1)
{
  HIWORD(dword_463904) = a1 & 0xF800;
  return a1 & 0xF800;
}
