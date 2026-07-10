#include "pch.h"
int __cdecl sub_43EF50(
        unsigned int a1,
        unsigned int a2,
        int *a3,
        unsigned int *a4,
        unsigned int *a5,
        _DWORD *a6,
        _DWORD *a7,
        int a8,
        int a9)
{
  unsigned int *v9; // edi
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int v14; // [esp-Ch] [ebp-20h]
  int v15; // [esp-8h] [ebp-1Ch]
  int v16; // [esp-8h] [ebp-1Ch]
  int v17; // [esp-8h] [ebp-1Ch]
  unsigned int v18; // [esp+10h] [ebp-4h] BYREF

  v14 = *(_DWORD *)(a9 + 40);
  v18 = 0;
  v9 = (unsigned int *)(*(int (__cdecl **)(int, int, int))(a9 + 32))(v14, 288, 4);
  if ( !v9 )
    return -4;
  v11 = sub_43EA80(a3, a1, 0x101u, (int)&unk_4496D4, (int)&unk_449750, a6, a4, a8, &v18, v9);
  v12 = v11;
  if ( v11 )
  {
    if ( v11 == -3 )
    {
      v17 = *(_DWORD *)(a9 + 40);
      *(_DWORD *)(a9 + 24) = aOversubscribed_1;
      (*(void (__cdecl **)(int, unsigned int *))(a9 + 36))(v17, v9);
      return -3;
    }
    if ( v11 == -4 )
      goto LABEL_20;
LABEL_19:
    *(_DWORD *)(a9 + 24) = aIncompleteLite;
    v12 = -3;
    goto LABEL_20;
  }
  if ( !*a4 )
    goto LABEL_19;
  v13 = sub_43EA80(&a3[a1], a2, 0, (int)&unk_4497CC, (int)&unk_449844, a7, a5, a8, &v18, v9);
  v12 = v13;
  if ( v13 )
  {
    switch ( v13 )
    {
      case -3:
        v15 = *(_DWORD *)(a9 + 40);
        *(_DWORD *)(a9 + 24) = aOversubscribed_0;
        (*(void (__cdecl **)(int, unsigned int *))(a9 + 36))(v15, v9);
        return -3;
      case -5:
        v16 = *(_DWORD *)(a9 + 40);
        *(_DWORD *)(a9 + 24) = aIncompleteDist;
        (*(void (__cdecl **)(int, unsigned int *))(a9 + 36))(v16, v9);
        return -3;
      case -4:
        goto LABEL_20;
    }
  }
  else if ( *a5 || a1 <= 0x101 )
  {
    (*(void (__cdecl **)(_DWORD, unsigned int *))(a9 + 36))(*(_DWORD *)(a9 + 40), v9);
    return 0;
  }
  *(_DWORD *)(a9 + 24) = aEmptyDistanceT;
  v12 = -3;
LABEL_20:
  (*(void (__cdecl **)(_DWORD, unsigned int *))(a9 + 36))(*(_DWORD *)(a9 + 40), v9);
  return v12;
}
