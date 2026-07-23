#include "pch.h"
char *__cdecl dynarec_recompile_block(int a1)
{
  unsigned int v1; // eax
  int v2; // eax

  v1 = a1 - (_DWORD)recomp_code_base;
  if ( (unsigned int)(a1 - (_DWORD)recomp_code_base) >= 0x200000 )
    v1 -= 0x40600000;
  *(_DWORD *)reg_pc = v1;
  dynarec_compile(v1, 20480);
  if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v2 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v2 = *(_DWORD *)reg_pc & 0x1FFFFF;
  return (char *)recomp_code_base + v2;
}
