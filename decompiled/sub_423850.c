#include "pch.h"
char *__cdecl sub_423850(int a1)
{
  unsigned int v1; // eax
  int v2; // eax

  v1 = a1 - (_DWORD)dword_5164C4;
  if ( (unsigned int)(a1 - (_DWORD)dword_5164C4) >= 0x200000 )
    v1 -= 0x40600000;
  *(_DWORD *)reg_pc = v1;
  dynarec_compile(v1, 20480);
  if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v2 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v2 = *(_DWORD *)reg_pc & 0x1FFFFF;
  return (char *)dword_5164C4 + v2;
}
