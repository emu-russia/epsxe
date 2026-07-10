#include "pch.h"
int __cdecl sub_4393D0(int a1)
{
  int v1; // edi
  int v2; // edi
  int v3; // edi
  int v4; // eax

  v1 = sub_438B70(a1);
  v2 = (sub_438B70(a1) << 8) + v1;
  v3 = (sub_438B70(a1) << 16) + v2;
  v4 = sub_438B70(a1);
  if ( v4 == -1 )
    *(_DWORD *)(a1 + 56) = -3;
  return v3 + (v4 << 24);
}
