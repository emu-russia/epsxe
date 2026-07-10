#include "pch.h"
int (__cdecl *__cdecl sub_43B5A0(_DWORD *a1, int a2, _DWORD *a3))(_DWORD, _DWORD, _DWORD)
{
  int v3; // eax
  int (__cdecl *result)(_DWORD, _DWORD, _DWORD); // eax

  if ( a3 )
    *a3 = a1[15];
  if ( *a1 == 4 || *a1 == 5 )
    (*(void (__cdecl **)(_DWORD, _DWORD))(a2 + 36))(*(_DWORD *)(a2 + 40), a1[3]);
  if ( *a1 == 6 )
    sub_43E9B0(a1[1], a2);
  v3 = a1[10];
  *a1 = 0;
  a1[13] = v3;
  a1[12] = v3;
  result = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))a1[14];
  a1[7] = 0;
  a1[8] = 0;
  if ( result )
  {
    result = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))result(0, 0, 0);
    a1[15] = result;
    *(_DWORD *)(a2 + 48) = result;
  }
  return result;
}
