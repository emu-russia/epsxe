#include "pch.h"
int __cdecl sub_43F110(_DWORD *a1, _DWORD *a2, int a3)
{
  unsigned int v3; // ebp
  char *v4; // edi
  unsigned int v5; // eax
  unsigned int v6; // ebp
  unsigned int v7; // edx
  int (__cdecl *v8)(_DWORD, char *, unsigned int); // eax
  int v9; // eax
  char *v10; // eax
  char *v11; // ecx
  char *v12; // esi
  unsigned int v13; // ebp
  unsigned int v14; // eax
  unsigned int v15; // edx
  int (__cdecl *v16)(_DWORD, char *, unsigned int); // eax
  int v17; // eax
  char *v18; // edi
  char *v20; // [esp+10h] [ebp-4h]
  char *v21; // [esp+10h] [ebp-4h]

  v3 = a1[13];
  v4 = (char *)a1[12];
  v20 = (char *)a2[3];
  if ( (unsigned int)v4 > v3 )
    v3 = a1[11];
  v5 = a2[4];
  v6 = v3 - (_DWORD)v4;
  if ( v6 > v5 )
    v6 = a2[4];
  if ( v6 && a3 == -5 )
    a3 = 0;
  v7 = v6 + a2[5];
  a2[4] = v5 - v6;
  a2[5] = v7;
  v8 = (int (__cdecl *)(_DWORD, char *, unsigned int))a1[14];
  if ( v8 )
  {
    v9 = v8(a1[15], v4, v6);
    a1[15] = v9;
    a2[12] = v9;
  }
  qmemcpy(v20, v4, v6);
  v10 = &v4[v6];
  v11 = (char *)a1[11];
  v21 = &v20[v6];
  if ( &v4[v6] == v11 )
  {
    v12 = (char *)a1[10];
    if ( (char *)a1[13] == v11 )
      a1[13] = v12;
    v13 = a1[13] - (_DWORD)v12;
    v14 = a2[4];
    if ( v13 > v14 )
      v13 = a2[4];
    if ( v13 && a3 == -5 )
      a3 = 0;
    v15 = v13 + a2[5];
    a2[4] = v14 - v13;
    a2[5] = v15;
    v16 = (int (__cdecl *)(_DWORD, char *, unsigned int))a1[14];
    if ( v16 )
    {
      v17 = v16(a1[15], v12, v13);
      a1[15] = v17;
      a2[12] = v17;
    }
    qmemcpy(v21, v12, 4 * (v13 >> 2));
    v18 = &v21[4 * (v13 >> 2)];
    v21 += v13;
    v10 = &v12[v13];
    qmemcpy(v18, &v12[4 * (v13 >> 2)], v13 & 3);
  }
  a2[3] = v21;
  a1[12] = v10;
  return a3;
}
