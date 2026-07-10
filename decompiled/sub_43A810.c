#include "pch.h"
int __cdecl sub_43A810(int *a1, int a2)
{
  int v2; // ebx
  unsigned int v3; // eax
  int v4; // ecx
  bool v5; // zf
  int v6; // ecx
  unsigned int v7; // edx
  unsigned int v8; // eax
  int v9; // edx
  int v10; // ecx
  unsigned int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v16; // eax
  int v17; // [esp-14h] [ebp-20h]
  int v18; // [esp-14h] [ebp-20h]
  int v19; // [esp-14h] [ebp-20h]

  v2 = 0xFFFF;
  if ( (unsigned int)(a1[3] - 5) < 0xFFFF )
    v2 = a1[3] - 5;
  while ( 1 )
  {
    v3 = a1[27];
    if ( v3 <= 1 )
    {
      sub_43A970(a1);
      v3 = a1[27];
      if ( !v3 )
        break;
    }
    v4 = a1[25];
    a1[27] = 0;
    v5 = v3 + v4 == 0;
    a1[25] = v3 + v4;
    v6 = a1[21];
    v7 = a1[25];
    v8 = v6 + v2;
    if ( !v5 && v7 < v8
      || ((a1[25] = v8, a1[27] = v7 - v8, v6 < 0) ? (v9 = 0) : (v9 = v6 + a1[12]),
          sub_43C970(a1, v9, v2, 0),
          v17 = *a1,
          a1[21] = a1[25],
          sub_43A490(v17),
          *(_DWORD *)(*a1 + 16)) )
    {
      v10 = a1[21];
      v11 = a1[25] - v10;
      if ( v11 < a1[9] - 262 )
        continue;
      v12 = v10 < 0 ? 0 : v10 + a1[12];
      sub_43C970(a1, v12, v11, 0);
      v18 = *a1;
      a1[21] = a1[25];
      sub_43A490(v18);
      if ( *(_DWORD *)(*a1 + 16) )
        continue;
    }
    return 0;
  }
  if ( !a2 )
    return 0;
  v13 = a1[21];
  if ( v13 < 0 )
    v14 = 0;
  else
    v14 = v13 + a1[12];
  sub_43C970(a1, v14, a1[25] - v13, a2 == 4);
  v19 = *a1;
  a1[21] = a1[25];
  sub_43A490(v19);
  if ( !*(_DWORD *)(*a1 + 16) )
    return a2 != 4 ? 0 : 2;
  v16 = -(a2 != 4);
  LOBYTE(v16) = v16 & 0xFE;
  return v16 + 3;
}
