#include "pch.h"
int __cdecl sub_439470(FILE *Stream, unsigned int a2)
{
  int v3; // ebx
  int result; // eax

  v3 = 4;
  do
  {
    result = fputc((unsigned __int8)a2, Stream);
    a2 >>= 8;
    --v3;
  }
  while ( v3 );
  return result;
}
