#include "pch.h"
char *mdec_init_pointers()
{
  char *v0; // ecx
  char *result; // eax

  v0 = mdec_idct_buffer_end;
  result = (char *)mdec_idct_buffer;
  do
  {
    *(_DWORD *)v0 = result;
    result += 8;
    v0 += 4;
  }
  while ( (int)result < (int)mdec_idct_buffer_end );
  return result;
}
