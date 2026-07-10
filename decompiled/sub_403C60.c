#include "pch.h"
int __cdecl sub_403C60(_DWORD *a1, int a2, int a3, int a4)
{
  int v4; // edx
  int v5; // eax
  int v7; // edx
  int v8; // ecx
  char v9; // al

  v4 = 1;
  if ( a4 )
  {
    byte_8B1960 = (*(_BYTE *)(a2 + 3) >> 2) & 3;
    if ( byte_8B1960 )
    {
      if ( byte_8B1960 == 1 )
        *a1 = 18900;
      else
        *a1 = 0;
    }
    else
    {
      *a1 = 37800;
    }
    v5 = (*(unsigned __int8 *)(a2 + 3) >> 4) & 3;
    if ( v5 )
    {
      if ( v5 == 1 )
        a1[1] = 8;
      else
        a1[1] = 0;
    }
    else
    {
      a1[1] = 4;
    }
    a1[2] = (*(_BYTE *)(a2 + 3) & 3) != 0 && (*(_BYTE *)(a2 + 3) & 3) == 1;
    if ( !*a1 )
      return -1;
    if ( !a1[2] )
    {
      sub_4038F0(a1 + 4);
      a1[3] = 4032;
      sub_403F60(v7, (int)a1, a3);
      return 0;
    }
    sub_4038F0(a1 + 4);
    sub_4038F0(a1 + 6);
    if ( a1[1] != v8 || *a1 != 37800 && *a1 != 18900 )
      return -1;
    a1[3] = 2016;
  }
  if ( (*(_BYTE *)(a2 + 3) & 3) == (_BYTE)v4 )
  {
    a1[2] = v4;
    a1[3] = 2016;
  }
  else
  {
    a1[2] = 0;
    a1[3] = 4032;
  }
  if ( a1[2] )
    sub_403DF0((int)a1, a3);
  else
    sub_403F60(v4, (int)a1, a3);
  if ( spu_adpcm_flag )
    return 0;
  v9 = (*(_BYTE *)(a2 + 3) >> 2) & 3;
  if ( byte_8B1960 == v9 )
    return 0;
  byte_8B1960 = (*(_BYTE *)(a2 + 3) >> 2) & 3;
  if ( !v9 )
  {
    *a1 = 37800;
    spu_set_adpcm_flag_cb();
    return 0;
  }
  if ( v9 == 1 )
    *a1 = 18900;
  else
    *a1 = 0;
  spu_set_adpcm_flag_cb();
  return 0;
}
