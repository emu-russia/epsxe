#include "pch.h"
int __cdecl sub_439640(_DWORD *a1, int a2, _BYTE *a3, int a4)
{
  int v5; // eax
  int v6; // eax
  int v7; // ecx

  if ( !a3 || *a3 != byte_45751C || a4 != 56 )
    return -6;
  if ( !a1 )
    return -2;
  v5 = a1[8];
  a1[6] = 0;
  if ( !v5 )
  {
    a1[8] = sub_43B570;
    a1[10] = 0;
  }
  if ( !a1[9] )
    a1[9] = sub_43B590;
  v6 = ((int (__cdecl *)(_DWORD, int, int))a1[8])(a1[10], 1, 24);
  a1[7] = v6;
  if ( !v6 )
    return -4;
  v7 = a2;
  *(_DWORD *)(v6 + 20) = 0;
  *(_DWORD *)(a1[7] + 12) = 0;
  if ( a2 < 0 )
  {
    v7 = -a2;
    *(_DWORD *)(a1[7] + 12) = 1;
  }
  if ( v7 < 8 || v7 > 15 )
  {
    sub_4395F0(a1);
    return -2;
  }
  else
  {
    *(_DWORD *)(a1[7] + 16) = v7;
    *(_DWORD *)(a1[7] + 20) = sub_43B620(a1, *(_DWORD *)(a1[7] + 12) == 0 ? sub_43C450 : nullptr, 1 << v7);
    if ( *(_DWORD *)(a1[7] + 20) )
    {
      sub_4395A0(a1);
      return 0;
    }
    else
    {
      sub_4395F0(a1);
      return -4;
    }
  }
}
