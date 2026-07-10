#include "pch.h"
int __cdecl sub_439D60(_DWORD *a1, int a2, int a3, int a4, int a5, unsigned int a6, _BYTE *a7, int a8)
{
  int v8; // ebp
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // ebx
  _DWORD *v13; // eax
  _DWORD *v14; // esi
  int v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  unsigned int v21; // ecx

  v8 = 0;
  if ( !a7 || *a7 != *off_457594 || a8 != 56 )
    return -6;
  if ( !a1 )
    return -2;
  v10 = a1[8];
  a1[6] = 0;
  if ( !v10 )
  {
    a1[8] = sub_43B570;
    a1[10] = 0;
  }
  if ( !a1[9] )
    a1[9] = sub_43B590;
  v11 = a2;
  if ( a2 == -1 )
  {
    a2 = 6;
    v11 = 6;
  }
  v12 = a4;
  if ( a4 < 0 )
  {
    v8 = 1;
    v12 = -a4;
  }
  if ( a5 < 1 || a5 > 9 || a3 != 8 || v12 < 8 || v12 > 15 || v11 > 9 || a6 > 2 )
    return -2;
  v13 = (_DWORD *)((int (__cdecl *)(_DWORD, int, int))a1[8])(a1[10], 1, 5816);
  v14 = v13;
  if ( !v13 )
    return -4;
  a1[7] = v13;
  v13[6] = v8;
  v13[10] = v12;
  *v13 = a1;
  v13[18] = a5 + 7;
  v13[9] = 1 << v12;
  v13[11] = (1 << v12) - 1;
  v15 = 1 << (a5 + 7);
  v14[17] = v15;
  v14[19] = v15 - 1;
  v14[20] = (a5 + 9) / 3u;
  v16 = ((int (__cdecl *)(_DWORD, int, int))a1[8])(a1[10], 1 << v12, 2);
  v17 = v14[9];
  v14[12] = v16;
  v18 = ((int (__cdecl *)(_DWORD, int, int))a1[8])(a1[10], v17, 2);
  v19 = v14[17];
  v14[14] = v18;
  v14[15] = ((int (__cdecl *)(_DWORD, int, int))a1[8])(a1[10], v19, 2);
  v14[1445] = 1 << (a5 + 6);
  v20 = ((int (__cdecl *)(_DWORD, int, int))a1[8])(a1[10], 1 << (a5 + 6), 4);
  v21 = v14[1445];
  v14[2] = v20;
  v14[3] = 4 * v21;
  if ( v14[12] && v14[14] && v14[15] && v20 )
  {
    *((_BYTE *)v14 + 29) = 8;
    v14[1447] = v20 + 2 * (v21 >> 1);
    v14[1444] = v20 + 2 * v21 + v21;
    v14[32] = a6;
    v14[31] = a2;
    return sub_43A060(a1);
  }
  else
  {
    a1[6] = off_4575B8[0];
    sub_43A510(a1);
    return -4;
  }
}
