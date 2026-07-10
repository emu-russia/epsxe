#include "pch.h"
size_t __cdecl sub_41C390(const char *a1)
{
  size_t result; // eax
  unsigned int v2; // edi
  const char *v3; // ebp
  size_t v4; // [esp+8h] [ebp-4h]

  result = 0x100000;
  v2 = 0;
  v4 = 0x100000;
  if ( dword_4FC458 )
  {
    v3 = byte_566980;
    do
    {
      if ( !strcmp(v3, a1) )
        v4 = Size[v2];
      ++v2;
      v3 += 256;
    }
    while ( v2 < dword_4FC458 );
    return v4;
  }
  return result;
}
