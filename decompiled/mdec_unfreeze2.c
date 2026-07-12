#include "pch.h"
int __cdecl mdec_unfreeze2(int a1, _DWORD *a2)
{
  char v3[64]; // [esp+4h] [ebp-40h] BYREF

  gzread(a2, v3, 7);
  return gzread(a2, dword_4FC4F0, 96);
}
