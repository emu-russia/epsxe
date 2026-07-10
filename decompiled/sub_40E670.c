#include "pch.h"
int __cdecl sub_40E670(_DWORD *a1, int a2)
{
  int v2; // esi
  int v4; // [esp+8h] [ebp-48h] BYREF
  _DWORD v5[14]; // [esp+18h] [ebp-38h] BYREF

  if ( !a1 )
    return E_INVALIDARG;
  v2 = *a1;
  if ( !*a1 )
    return E_INVALIDARG;
  memset(v5, 0, sizeof(v5));
  v4 = 10000 * a2 / 255;
  v5[0] = 56;
  v5[11] = 16;
  v5[12] = &v4;
  (*(void (__stdcall **)(int, _DWORD *, int))(*(_DWORD *)v2 + 24))(v2, v5, 256);
  return (*(int (__stdcall **)(_DWORD, int, _DWORD))(*(_DWORD *)*a1 + 28))(*a1, 1, 0);
}
