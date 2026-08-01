#include "pch.h"
char __cdecl check_state_exists(unsigned __int8 a1)
{
  FILE *v1; // eax
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%s%s.%03d", "sstates\\", default_filename, a1);
  v1 = fopen(Buffer, "rb");
  if ( !v1 )
    return -1;
  fclose(v1);
  return 0;
}
