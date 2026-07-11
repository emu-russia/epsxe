#include "pch.h"
char memcard2_save()
{
  char result; // al
  FILE *v1; // esi

  result = byte_4FC460;
  if ( byte_4FC460 )
  {
    v1 = fopen((const char *)Memcard2, "wb");
    if ( v1 )
    {
      fseek(v1, dword_4FC474, 0);
      fwrite(byte_546860, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard2);
    }
  }
  return result;
}
