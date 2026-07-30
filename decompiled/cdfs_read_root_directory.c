#include "pch.h"
char *cdfs_read_root_directory()
{
  int le32; // esi

  cdfs_read_data(16, 24, 0x800u, byte_4FE9E8);
  le32 = cdfs_read_le32((unsigned __int8 *)&byte_4FE9E8[158]);
  cdfs_read_data(le32, 24, 0x800u, byte_4FE9E8);
  cdfs_read_data(le32 + 1, 24, 0x800u, byte_4FF1E8);
  return byte_4FE9E8;
}
