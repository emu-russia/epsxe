#include "pch.h"
int sub_437340(FILE *Stream, char *Format, ...)
{
  char *v2; // esi
  va_list va; // [esp+10h] [ebp+Ch] BYREF

  va_start(va, Format);
  v2 = (char *)malloc(0x8000u);
  vsprintf(v2, Format, va);
  if ( Stream && byte_4FF9F2 )
    fprintf(Stream, "%s", v2);
  return free(v2);
}
