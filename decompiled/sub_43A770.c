#include "pch.h"
int __cdecl sub_43A770(int a1)
{
  int v1; // ecx
  int v2; // eax
  int v3; // ecx

  v1 = *(_DWORD *)(a1 + 68);
  *(_DWORD *)(a1 + 52) = 2 * *(_DWORD *)(a1 + 36);
  *(_WORD *)(*(_DWORD *)(a1 + 60) + 2 * v1 - 2) = 0;
  memset(*(void **)(a1 + 60), 0, 2 * *(_DWORD *)(a1 + 68) - 2);
  v2 = 6 * *(_DWORD *)(a1 + 124);
  *(_DWORD *)(a1 + 120) = (unsigned __int16)word_4487B2[v2];
  *(_DWORD *)(a1 + 132) = (unsigned __int16)word_4487B0[v2];
  *(_DWORD *)(a1 + 136) = (unsigned __int16)word_4487B4[v2];
  v3 = (unsigned __int16)word_4487B6[v2];
  *(_DWORD *)(a1 + 100) = 0;
  *(_DWORD *)(a1 + 84) = 0;
  *(_DWORD *)(a1 + 108) = 0;
  *(_DWORD *)(a1 + 96) = 0;
  *(_DWORD *)(a1 + 64) = 0;
  *(_DWORD *)(a1 + 116) = v3;
  *(_DWORD *)(a1 + 112) = 2;
  *(_DWORD *)(a1 + 88) = 2;
  return 2;
}
