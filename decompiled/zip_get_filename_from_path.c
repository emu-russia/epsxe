#include "pch.h"
char *__cdecl zip_get_filename_from_path(const char *a1)
{
  char *result; // eax
  char *v2; // esi

  strcpy(byte_4FC350, a1);
  result = strtok(byte_4FC350, "/\\:");
  if ( result )
  {
    do
    {
      v2 = result;
      result = strtok(nullptr, "/\\:");
    }
    while ( result );
    return v2;
  }
  return result;
}
