#include "pch.h"
int __cdecl sub_43A1B0(int a1, int a2)
{
  int v3; // esi
  int v4; // eax
  int v6; // ecx
  unsigned int v7; // eax
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // [esp+14h] [ebp+4h]

  if ( !a1 )
    return -2;
  v3 = *(_DWORD *)(a1 + 28);
  if ( !v3 || (unsigned int)a2 > 4 )
    return -2;
  if ( !*(_DWORD *)(a1 + 12)
    || !*(_DWORD *)a1 && *(_DWORD *)(a1 + 4)
    || (v4 = *(_DWORD *)(v3 + 4), v4 == 666) && a2 != 4 )
  {
    *(char **)(a1 + 24) = off_4575B0[0];
    return -2;
  }
  if ( !*(_DWORD *)(a1 + 16) )
  {
    *(char **)(a1 + 24) = off_4575BC[0];
    return -5;
  }
  v6 = *(_DWORD *)(v3 + 32);
  *(_DWORD *)v3 = a1;
  v13 = v6;
  *(_DWORD *)(v3 + 32) = a2;
  if ( v4 == 42 )
  {
    v7 = (*(_DWORD *)(v3 + 124) - 1) >> 1;
    if ( v7 > 3 )
      v7 = 3;
    v8 = (v7 << 6) | ((*(_DWORD *)(v3 + 40) << 12) - 30720);
    if ( *(_DWORD *)(v3 + 100) )
      v8 |= 0x20u;
    *(_DWORD *)(v3 + 4) = 113;
    sub_43A460(v3, v8 - v8 % 0x1F + 31);
    if ( *(_DWORD *)(v3 + 100) )
    {
      sub_43A460(v3, HIWORD(*(_DWORD *)(a1 + 48)));
      sub_43A460(v3, (unsigned __int16)*(_DWORD *)(a1 + 48));
    }
    *(_DWORD *)(a1 + 48) = 1;
  }
  if ( *(_DWORD *)(v3 + 20) )
  {
    sub_43A490(a1);
    if ( !*(_DWORD *)(a1 + 16) )
    {
      *(_DWORD *)(v3 + 32) = -1;
      return 0;
    }
  }
  else if ( !*(_DWORD *)(a1 + 4) && a2 <= v13 && a2 != 4 )
  {
    *(char **)(a1 + 24) = off_4575BC[0];
    return -5;
  }
  v9 = *(_DWORD *)(v3 + 4);
  v10 = *(_DWORD *)(a1 + 4);
  if ( v9 == 666 )
  {
    if ( v10 )
    {
      *(char **)(a1 + 24) = off_4575BC[0];
      return -5;
    }
  }
  else if ( v10 )
  {
    goto LABEL_33;
  }
  if ( !*(_DWORD *)(v3 + 108) && (!a2 || v9 == 666) )
  {
LABEL_45:
    if ( a2 != 4 )
      return 0;
    if ( *(_DWORD *)(v3 + 24) )
      return 1;
    sub_43A460(v3, HIWORD(*(_DWORD *)(a1 + 48)));
    sub_43A460(v3, (unsigned __int16)*(_DWORD *)(a1 + 48));
    sub_43A490(a1);
    v12 = *(_DWORD *)(v3 + 20);
    *(_DWORD *)(v3 + 24) = -1;
    return v12 == 0;
  }
LABEL_33:
  v11 = funcs_43A344[3 * *(_DWORD *)(v3 + 124)](v3, a2);
  if ( v11 == 2 || v11 == 3 )
    *(_DWORD *)(v3 + 4) = 666;
  if ( v11 && v11 != 2 )
  {
    if ( v11 == 1 )
    {
      if ( a2 == 1 )
      {
        sub_43C710(v3);
      }
      else
      {
        sub_43C670(v3, 0, 0, 0);
        if ( a2 == 3 )
        {
          *(_WORD *)(*(_DWORD *)(v3 + 60) + 2 * *(_DWORD *)(v3 + 68) - 2) = 0;
          memset(*(void **)(v3 + 60), 0, 2 * *(_DWORD *)(v3 + 68) - 2);
        }
      }
      sub_43A490(a1);
      if ( !*(_DWORD *)(a1 + 16) )
      {
        *(_DWORD *)(v3 + 32) = -1;
        return 0;
      }
    }
    goto LABEL_45;
  }
  if ( !*(_DWORD *)(a1 + 16) )
    *(_DWORD *)(v3 + 32) = -1;
  return 0;
}
