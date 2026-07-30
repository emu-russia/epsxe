#include "pch.h"
int __cdecl loader_set_filename(const char *a1)
{
  return sprintf(FileName, "%s", a1);
}
