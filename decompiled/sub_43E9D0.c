#include "pch.h"
int __cdecl sub_43E9D0(int a1, _DWORD *a2, int a3, int a4, int a5)
{
  int v5; // ebx
  int v7; // eax
  int v8; // esi
  int v9; // [esp-10h] [ebp-1Ch]
  int v10; // [esp+8h] [ebp-4h] BYREF

  v10 = 0;
  v5 = (*(int (__cdecl **)(_DWORD, int, int))(a5 + 32))(*(_DWORD *)(a5 + 40), 19, 4);
  if ( !v5 )
    return -4;
  v7 = sub_43EA80(a1, 19, 19, 0, 0, a3, a2, a4, &v10, v5);
  v8 = v7;
  if ( v7 == -3 )
  {
    v9 = *(_DWORD *)(a5 + 40);
    *(_DWORD *)(a5 + 24) = aOversubscribed;
    (*(void (__cdecl **)(int, int))(a5 + 36))(v9, v5);
    return -3;
  }
  else
  {
    if ( v7 == -5 || !*a2 )
    {
      *(_DWORD *)(a5 + 24) = aIncompleteDyna;
      v8 = -3;
    }
    (*(void (__cdecl **)(_DWORD, int))(a5 + 36))(*(_DWORD *)(a5 + 40), v5);
    return v8;
  }
}
