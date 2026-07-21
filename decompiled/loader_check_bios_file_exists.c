#include "pch.h"
int loader_check_bios_file_exists()
{
  FILE *v0; // eax
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF

  sprintf(Buffer, "%s", (const char *)bios_name);
  v0 = fopen(Buffer, "rb");
  if ( !v0 )
    return -1;
  fclose(v0);
  return 0;
}
