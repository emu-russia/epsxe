#include "pch.h"
int __cdecl cdr_hex_to_bcd(unsigned __int8 a1)
{
  return (a1 & 0xF) + 10 * (a1 >> 4);
}
