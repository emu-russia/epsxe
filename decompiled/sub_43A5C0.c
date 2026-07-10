#include "pch.h"
int __cdecl sub_43A5C0(int a1, _DWORD *a2)
{
  int *v3; // eax
  int *v4; // ebx
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  void *v12; // edi
  int v13; // esi
  int v14; // ecx
  int v15; // [esp+18h] [ebp+8h]

  if ( !a2 )
    return -2;
  if ( !a1 )
    return -2;
  v15 = a2[7];
  if ( !v15 )
    return -2;
  qmemcpy((void *)a1, a2, 0x38u);
  v3 = (int *)(*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), 1, 5816);
  v4 = v3;
  if ( !v3 )
    return -4;
  *(_DWORD *)(a1 + 28) = v3;
  qmemcpy(v3, (const void *)v15, 0x16B8u);
  v6 = v3[9];
  *v3 = a1;
  v3[12] = (*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), v6, 2);
  v7 = (*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), v4[9], 2);
  v8 = v4[17];
  v4[14] = v7;
  v9 = (*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), v8, 2);
  v10 = v4[1445];
  v4[15] = v9;
  v11 = (*(int (__cdecl **)(_DWORD, int, int))(a1 + 32))(*(_DWORD *)(a1 + 40), v10, 4);
  v12 = (void *)v4[12];
  v4[2] = v11;
  if ( v12 && v4[14] && v4[15] && v11 )
  {
    qmemcpy(v12, *(const void **)(v15 + 48), 2 * v4[9]);
    qmemcpy((void *)v4[14], *(const void **)(v15 + 56), 2 * v4[9]);
    qmemcpy((void *)v4[15], *(const void **)(v15 + 60), 2 * v4[17]);
    qmemcpy((void *)v4[2], *(const void **)(v15 + 8), v4[3]);
    v13 = v4[2];
    v4[4] = v13 + *(_DWORD *)(v15 + 16) - *(_DWORD *)(v15 + 8);
    v14 = v13 + 2 * v4[1445] + v4[1445];
    v4[1447] = v11 + 2 * ((unsigned int)v4[1445] >> 1);
    v4[1444] = v14;
    v4[708] = (int)(v4 + 35);
    v4[711] = (int)(v4 + 608);
    v4[714] = (int)(v4 + 669);
    return 0;
  }
  else
  {
    sub_43A510(a1);
    return -4;
  }
}
