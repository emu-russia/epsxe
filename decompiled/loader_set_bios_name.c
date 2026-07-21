#include "pch.h"
int __cdecl loader_set_bios_name(const char *a1)
{
  return sprintf((char *const)bios_name, "%s", a1);
}
