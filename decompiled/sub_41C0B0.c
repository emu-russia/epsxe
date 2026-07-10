#include "pch.h"
int sub_41C0B0()
{
  FILE *v0; // eax
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF

  sprintf(Buffer, "%s", (const char *)&byte_8B2980);
  v0 = fopen(Buffer, Mode);
  if ( !v0 )
    return -1;
  fclose(v0);
  return 0;
}
