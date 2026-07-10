#include "pch.h"
char sub_421DB0()
{
  char result; // al
  FILE *v1; // esi

  result = byte_4FC460;
  if ( byte_4FC460 )
  {
    v1 = fopen((const char *)&byte_8B3180, aWb);
    if ( v1 )
    {
      fseek(v1, Offset, 0);
      fwrite(&byte_526860, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)&byte_8B3180);
    }
  }
  return result;
}
