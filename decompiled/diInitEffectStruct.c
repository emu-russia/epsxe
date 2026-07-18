#include "pch.h"
_DWORD *__cdecl diInitEffectStruct(_DWORD *a1)
{
  memset(a1 + 2, 0, 0x38u);
  a1[2] = 56;
  a1[6] = 7500;
  a1[16] = 0;
  a1[17] = 0;
  a1[18] = 0;
  a1[19] = 0;
  a1[20] = 0;
  a1[16] = 20;
  *a1 = 0;
  return a1 + 16;
}
