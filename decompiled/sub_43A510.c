#include "pch.h"
char __cdecl sub_43A510(int a1)
{
  int v1; // eax
  int v2; // edi
  int v3; // eax
  int v4; // ecx
  int v5; // edx

  if ( !a1 )
    return -2;
  v1 = *(_DWORD *)(a1 + 28);
  if ( !v1 )
    return -2;
  v2 = *(_DWORD *)(v1 + 4);
  if ( v2 != 42 && v2 != 113 && v2 != 666 )
    return -2;
  v3 = *(_DWORD *)(v1 + 8);
  if ( v3 )
    (*(void (__cdecl **)(_DWORD, int))(a1 + 36))(*(_DWORD *)(a1 + 40), v3);
  v4 = *(_DWORD *)(a1 + 28);
  if ( *(_DWORD *)(v4 + 60) )
    (*(void (__cdecl **)(_DWORD, _DWORD))(a1 + 36))(*(_DWORD *)(a1 + 40), *(_DWORD *)(v4 + 60));
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 28) + 56) )
    (*(void (__cdecl **)(_DWORD, _DWORD))(a1 + 36))(*(_DWORD *)(a1 + 40), *(_DWORD *)(*(_DWORD *)(a1 + 28) + 56));
  v5 = *(_DWORD *)(a1 + 28);
  if ( *(_DWORD *)(v5 + 48) )
    (*(void (__cdecl **)(_DWORD, _DWORD))(a1 + 36))(*(_DWORD *)(a1 + 40), *(_DWORD *)(v5 + 48));
  (*(void (__cdecl **)(_DWORD, _DWORD))(a1 + 36))(*(_DWORD *)(a1 + 40), *(_DWORD *)(a1 + 28));
  *(_DWORD *)(a1 + 28) = 0;
  return v2 != 113 ? 0 : 0xFD;
}
