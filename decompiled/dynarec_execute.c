#include "pch.h"
__int64 dynarec_execute()
{
  int v0; // eax
  __int64 v1; // rax
  __int64 v3; // [esp-20h] [ebp-2Ch]

  *code_ptr = 0xBF;
  *(_DWORD *)(code_ptr + 1) = cpu_speed_scale;
  code_ptr[5] = 0xBE;
  *(_DWORD *)(code_ptr + 6) = cpu_gpr;
  code_ptr[10] = 0xB8;
  if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v0 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v0 = *(_DWORD *)reg_pc & 0x1FFFFF;
  LODWORD(v1) = (char *)recomp_code_base + v0;
  *(_DWORD *)(code_ptr + 11) = v1;
  HIDWORD(v1) = code_ptr;
  *(_WORD *)(code_ptr + 15) = 8447;
  code_ptr += 64;
  dword_4FC4EC = 0;
  v3 = v1;
  ((void (*)(void))((char *)recomp_buffer + 1152))();
  return v3;
}
