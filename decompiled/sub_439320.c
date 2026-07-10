#include "pch.h"
int __cdecl sub_439320(int a1)
{
  int v1; // eax

  if ( !a1 || *(_BYTE *)(a1 + 92) != 114 )
    return -1;
  v1 = *(_DWORD *)(a1 + 68);
  *(_DWORD *)(a1 + 56) = 0;
  *(_DWORD *)(a1 + 60) = 0;
  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)a1 = v1;
  *(_DWORD *)(a1 + 76) = crc32_calc(0, nullptr, 0);
  if ( *(_DWORD *)(a1 + 96) )
  {
    sub_4395A0(a1);
    return fseek(*(FILE **)(a1 + 64), *(_DWORD *)(a1 + 96), 0);
  }
  else
  {
    rewind(*(FILE **)(a1 + 64));
    return 0;
  }
}
