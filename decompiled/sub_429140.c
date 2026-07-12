#include "pch.h"
__int64 sub_429140()
{
  int v0; // eax
  __int64 v1; // rax
  __int64 v3; // [esp-20h] [ebp-2Ch]

  *(_BYTE *)dword_4FC4E0 = 0xBF;
  *(_DWORD *)(dword_4FC4E0 + 1) = dword_455940;
  *(_BYTE *)(dword_4FC4E0 + 5) = 0xBE;
  *(_DWORD *)(dword_4FC4E0 + 6) = cpu_gpr;
  *(_BYTE *)(dword_4FC4E0 + 10) = 0xB8;
  if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v0 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v0 = *(_DWORD *)reg_pc & 0x1FFFFF;
  LODWORD(v1) = (char *)dword_5164C4 + v0;
  *(_DWORD *)(dword_4FC4E0 + 11) = v1;
  HIDWORD(v1) = dword_4FC4E0;
  *(_WORD *)(dword_4FC4E0 + 15) = 8447;
  dword_4FC4E0 += 64;
  dword_4FC4EC = 0;
  v3 = v1;
  ((void (*)(void))((char *)dword_5164C0 + 1152))();
  return v3;
}
