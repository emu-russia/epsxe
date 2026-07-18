#include "pch.h"
int __cdecl cdfs_read_le32(unsigned __int8 *a1)
{
  return *a1 | ((a1[1] | ((a1[2] | ((char)a1[3] << 8)) << 8)) << 8);
}
