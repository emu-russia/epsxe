#include "pch.h"
int __cdecl mdec_unfreeze(int a1, _DWORD *a2)
{
  char v3[64]; // [esp+4h] [ebp-440h] BYREF
  char v4[1024]; // [esp+44h] [ebp-400h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dword_4FC4F0, 96);
  gzread(a2, (char *)dword_5120C0, 128);
  return gzread(a2, v4, 1024);
}
