#include "pch.h"
char memcard_save()
{
  FILE *v0; // esi
  int v1; // eax

  v1 = dword_4FC478;
  if ( dword_4FC478 )
    v1 = ++dword_4FC478;
  if ( dword_4FC47C )
    ++dword_4FC47C;
  if ( v1 == 120 )
  {
    dword_4FC478 = 0;
    LOBYTE(v1) = memcard1_save();
  }
  if ( dword_4FC47C == 120 )
  {
    dword_4FC47C = 0;
    LOBYTE(v1) = byte_4FC460;
    if ( byte_4FC460 )
    {
      v0 = fopen((const char *)&byte_8B3580, aWb);
      if ( v0 )
      {
        fseek(v0, dword_4FC474, 0);
        fwrite(byte_546860, 1u, 0x20000u, v0);
        LOBYTE(v1) = fclose(v0);
      }
      else
      {
        LOBYTE(v1) = dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)&byte_8B3580);
      }
    }
  }
  return v1;
}
