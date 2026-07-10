#include "pch.h"
// Microsoft VisualC 2-14/net runtime
char sub_421E90()
{
  char result; // al
  FILE *v1; // esi

  memcard1_save();
  result = byte_4FC460;
  if ( byte_4FC460 )
  {
    v1 = fopen((const char *)&byte_8B3580, aWb);
    if ( v1 )
    {
      fseek(v1, dword_4FC474, 0);
      fwrite(&byte_546860, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(aWarningTheMemc, (char)&byte_8B3580);
    }
  }
  return result;
}
