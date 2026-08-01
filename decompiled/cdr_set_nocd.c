#include "pch.h"
char __cdecl cdr_set_nocd(char a1)
{
  LOBYTE(g_cdr_registers) = a1;
  return a1;
}
