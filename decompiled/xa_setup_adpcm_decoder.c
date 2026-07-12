#include "pch.h"
int __cdecl xa_setup_adpcm_decoder(_DWORD *a1, int a2, int a3, int a4)
{
  int v4; // edx
  int v5; // eax
  int v7; // ecx
  char v8; // al
  int v9; // [esp-4h] [ebp-10h]
  int v10; // [esp+0h] [ebp-Ch]

  v4 = 1;
  if ( a4 )
  {
    byte_8B1960[0] = (*(_BYTE *)(a2 + 3) >> 2) & 3;
    if ( byte_8B1960[0] )
    {
      if ( byte_8B1960[0] == 1 )
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
      xa_clear_adpcm_state(a1 + 4);
      a1[3] = 4032;
      xa_decode_mono_blocks((int)a1, a3, v9);
      return 0;
    }
    xa_clear_adpcm_state(a1 + 4);
    xa_clear_adpcm_state(a1 + 6);
    if ( a1[1] != v7 || *a1 != 37800 && *a1 != 18900 )
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
    xa_decode_stereo_blocks((int)a1, a3);
  else
    xa_decode_mono_blocks((int)a1, a3, v10);
  if ( spu_adpcm_flag )
    return 0;
  v8 = (*(_BYTE *)(a2 + 3) >> 2) & 3;
  if ( byte_8B1960[0] == v8 )
    return 0;
  byte_8B1960[0] = (*(_BYTE *)(a2 + 3) >> 2) & 3;
  if ( !v8 )
  {
    *a1 = 37800;
    spu_set_adpcm_flag_cb();
    return 0;
  }
  if ( v8 == 1 )
    *a1 = 18900;
  else
    *a1 = 0;
  spu_set_adpcm_flag_cb();
  return 0;
}
