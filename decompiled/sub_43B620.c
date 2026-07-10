#include "pch.h"
int __cdecl sub_43B620(int a1, int a2, int a3)
{
  int result; // eax
  _DWORD *v4; // esi
  int v5; // eax
  int v6; // eax

  result = (*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), 1, 64);
  v4 = (_DWORD *)result;
  if ( result )
  {
    v5 = (*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), 8, 1440);
    v4[9] = v5;
    if ( v5 )
    {
      v6 = (*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), 1, a3);
      v4[10] = v6;
      if ( v6 )
      {
        v4[11] = a3 + v6;
        v4[14] = a2;
        *v4 = 0;
        sub_43B5A0(v4, a1, nullptr);
        return (int)v4;
      }
      else
      {
        (*(void (__cdecl **)(_DWORD, _DWORD))(a1 + 36))(*(_DWORD *)(a1 + 40), v4[9]);
        (*(void (__cdecl **)(_DWORD, _DWORD *))(a1 + 36))(*(_DWORD *)(a1 + 40), v4);
        return 0;
      }
    }
    else
    {
      (*(void (__cdecl **)(_DWORD, _DWORD *))(a1 + 36))(*(_DWORD *)(a1 + 40), v4);
      return 0;
    }
  }
  return result;
}
