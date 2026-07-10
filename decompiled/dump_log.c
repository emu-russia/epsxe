#include "pch.h"
void dump_log(FILE *Stream, char *Format, ...)
{
  char *v2; // esi
  va_list ArgList; // [esp+10h] [ebp+Ch] BYREF

  va_start(ArgList, Format);
  v2 = (char *)malloc(0x8000u);
  vsprintf(v2, Format, ArgList);
  if ( Stream && byte_4FF9F2 )
    fprintf(Stream, "%s", v2);
  free(v2);
}
