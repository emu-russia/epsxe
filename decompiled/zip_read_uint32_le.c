#include "pch.h"
int __cdecl zip_read_uint32_le(unsigned __int8 *a1)
{
  return *a1 | ((a1[1] | (*((unsigned __int16 *)a1 + 1) << 8)) << 8);
}
