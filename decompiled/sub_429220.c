#include "pch.h"
char *sub_429220()
{
  char *v0; // ecx
  char *result; // eax

  v0 = byte_514E40;
  result = (char *)dword_512140;
  do
  {
    *(_DWORD *)v0 = result;
    result += 8;
    v0 += 4;
  }
  while ( (int)result < (int)byte_514E40 );
  return result;
}
