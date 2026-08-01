#include "pch.h"
char *dynarec_invalidate()
{
  unsigned int i; // eax

  for ( i = 0; i < 0x280000; i += 4 )
    *(_DWORD *)((char *)recomp_code_base + i) = recomp_buffer;
  code_ptr = (uint8_t *)recomp_buffer + 1216;
  return (char *)recomp_buffer + 1216;
}
