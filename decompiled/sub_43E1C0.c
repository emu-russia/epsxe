#include "pch.h"
int __cdecl sub_43E1C0(char a1, char a2, int a3, int a4, int a5)
{
  int result; // eax

  result = (*(int (__cdecl **)(_DWORD, int, int))(a5 + 32))(*(_DWORD *)(a5 + 40), 1, 28);
  if ( result )
  {
    *(_BYTE *)(result + 16) = a1;
    *(_BYTE *)(result + 17) = a2;
    *(_DWORD *)result = 0;
    *(_DWORD *)(result + 20) = a3;
    *(_DWORD *)(result + 24) = a4;
  }
  return result;
}
