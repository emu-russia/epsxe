#include "pch.h"
int __cdecl cdr_bcd_to_hex(unsigned __int8 a1)
{
  return a1 % 10 + 16 * (a1 / 10);
}
