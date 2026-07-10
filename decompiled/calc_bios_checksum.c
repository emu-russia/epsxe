#include "pch.h"
int __cdecl calc_bios_checksum(uint8_t *ptr, int size)
{
  unsigned __int16 v2; // si
  int v3; // ebp
  uint8_t *v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // ecx

  v2 = 0;
  v3 = 0;
  if ( size > 0 )
  {
    v4 = ptr + 1;
    do
    {
      v5 = *(v4 - 1);
      v6 = *v4;
      v4 += 2;
      v7 = v6 + (v5 << 8);
      v3 += v7;
      v2 ^= v7;
    }
    while ( (int)&v4[-1 - (_DWORD)ptr] < size );
  }
  return v2 ^ (v3 << 16);
}
