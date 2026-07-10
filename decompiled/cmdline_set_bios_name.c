#include "pch.h"
int __cdecl cmdline_set_bios_name(const char *a1)
{
  return sprintf((char *const)&byte_8B2980, "%s", a1);
}
