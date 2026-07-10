#include "pch.h"
int __cdecl sub_43C400(int a1, const void *a2, unsigned int a3)
{
  unsigned int v4; // ecx

  qmemcpy(*(void **)(a1 + 40), a2, a3);
  v4 = a3 + *(_DWORD *)(a1 + 40);
  *(_DWORD *)(a1 + 52) = v4;
  *(_DWORD *)(a1 + 48) = v4;
  return a1;
}
