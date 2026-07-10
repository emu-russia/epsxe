#include "pch.h"
int __cdecl sub_43C3C0(_DWORD *a1, int a2)
{
  sub_43B5A0(a1, a2, nullptr);
  (*(void (__cdecl **)(_DWORD, _DWORD))(a2 + 36))(*(_DWORD *)(a2 + 40), a1[10]);
  (*(void (__cdecl **)(_DWORD, _DWORD))(a2 + 36))(*(_DWORD *)(a2 + 40), a1[9]);
  (*(void (__cdecl **)(_DWORD, _DWORD *))(a2 + 36))(*(_DWORD *)(a2 + 40), a1);
  return 0;
}
