#include "pch.h"
char *sub_4291E0()
{
  unsigned int i; // eax

  for ( i = 0; i < 0x280000; i += 4 )
    *(_DWORD *)((char *)dword_5164C4 + i) = dword_5164C0;
  dword_4FC4E0 = (int)dword_5164C0 + 1216;
  return (char *)dword_5164C0 + 1216;
}
