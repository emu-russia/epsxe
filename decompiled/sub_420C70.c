#include "pch.h"
int __cdecl sub_420C70(FILE *Stream, _DWORD *a2)
{
  int v2; // esi
  int result; // eax

  v2 = fseek(Stream, 0, 2);
  if ( v2 )
    return v2;
  result = ftell(Stream);
  *a2 = result;
  if ( result != -1 )
    return v2;
  return result;
}
