#include "pch.h"
unsigned __int8 __cdecl cdfs_load_executable(char *Buffer)
{
  int v2; // [esp+0h] [ebp-8h] BYREF
  int v3; // [esp+4h] [ebp-4h] BYREF

  cdfs_read_root_directory();
  cdfs_find_file("SYSTEM.CNF;1", &v2, (int **)&v3);
  if ( v2 )
    return cdfs_parse_system_cnf_for_exec(v2, v3, Buffer, &v3, (int **)&Buffer);
  else
    return sprintf(Buffer, "SLUS_999.99");
}
