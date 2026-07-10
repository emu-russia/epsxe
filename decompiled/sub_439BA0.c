#include "pch.h"
int __cdecl sub_439BA0(int a1, int a2, unsigned int a3)
{
  unsigned int v3; // ebx
  _DWORD *v4; // eax
  int v5; // ebp
  int v7; // edx
  unsigned int v8; // eax

  v3 = a3;
  if ( !a1 )
    return -2;
  v4 = *(_DWORD **)(a1 + 28);
  if ( !v4 || *v4 != 6 )
    return -2;
  v5 = a2;
  if ( sub_43C450(1, a2, a3) != *(_DWORD *)(a1 + 48) )
    return -3;
  v7 = *(_DWORD *)(a1 + 28);
  *(_DWORD *)(a1 + 48) = 1;
  v8 = 1 << *(_DWORD *)(v7 + 16);
  if ( a3 >= v8 )
  {
    v3 = v8 - 1;
    v5 = a3 - (v8 - 1) + a2;
  }
  sub_43C400(*(_DWORD *)(v7 + 20), v5, v3);
  **(_DWORD **)(a1 + 28) = 7;
  return 0;
}
