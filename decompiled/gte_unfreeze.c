#include "pch.h"
int __cdecl gte_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  return gzread(a2, word_8A7F00, 256);
}
