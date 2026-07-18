#include "pch.h"
int __cdecl diSetConstantForceMagnitude(int a1, int a2)
{
  _DWORD *v2; // ebx
  int v3; // esi
  _DWORD v5[14]; // [esp+8h] [ebp-38h] BYREF

  v2 = (_DWORD *)a1;
  if ( !a1 )
    return E_INVALIDARG;
  v3 = *(_DWORD *)a1;
  if ( !*(_DWORD *)a1 )
    return E_INVALIDARG;
  memset(v5, 0, sizeof(v5));
  a1 = 10000 * a2 / 255;
  v5[0] = 56;
  v5[11] = 4;
  v5[12] = &a1;
  (*(void (__stdcall **)(int, _DWORD *, int))(*(_DWORD *)v3 + 24))(v3, v5, 256);
  return (*(int (__stdcall **)(_DWORD, int, _DWORD))(*(_DWORD *)*v2 + 28))(*v2, 1, 0);
}
