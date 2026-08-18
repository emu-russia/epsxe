#include "pch.h"
_DWORD *__cdecl xa_clear_adpcm_state(_DWORD *a1)
{
  *a1 = 0;
  a1[1] = 0;
  return a1;
}

int *__cdecl xa_decode_adpcm_block(int *a1, unsigned __int8 a2, __int16 *a3, _WORD *a4, unsigned int a5)
{
  int v6; // ebp
  char v7; // bl
  int v8; // edi
  int v9; // eax
  int v10; // esi
  int v11; // edx
  int v12; // ecx
  int v13; // ebx
  _WORD *v14; // ecx
  _WORD *v15; // ecx
  _WORD *v16; // ecx
  __int16 *v18; // [esp+10h] [ebp-Ch]
  int v19; // [esp+14h] [ebp-8h]
  unsigned int v20; // [esp+18h] [ebp-4h]
  char v21; // [esp+24h] [ebp+8h]
  int v22; // [esp+28h] [ebp+Ch]
  int v23; // [esp+30h] [ebp+14h]

  v19 = a2 >> 4;
  v6 = *a1;
  v7 = a2 & 0xF;
  v22 = a1[1];
  v21 = a2 & 0xF;
  v20 = a5;
  v23 = 7;
  while ( 1 )
  {
    v18 = a3 + 1;
    v8 = 16 * ((int)(*a3 & 0xFFFFF000) >> v7);
    v9 = 16 * ((__int16)(16 * (*a3 & 0xFF00)) >> v7);
    v10 = 16 * ((__int16)(*a3 & 0xF000) >> v21);
    v11 = 16 * ((__int16)(*a3 << 12) >> v21);
    switch ( v19 )
    {
      case 0:
        goto LABEL_9;
      case 1:
        v11 -= (-960 * v6) >> 10;
        v10 -= (-960 * v11) >> 10;
        v9 -= (-960 * v10) >> 10;
        v8 -= (-960 * v9) >> 10;
        goto LABEL_9;
      case 2:
        v11 -= (832 * v22 - 1840 * v6) >> 10;
        v10 -= (832 * v6 - 1840 * v11) >> 10;
        v9 -= (832 * v11 - 1840 * v10) >> 10;
        v12 = 1840 * v9;
        v13 = 832 * v10;
        goto LABEL_8;
      case 3:
        v11 -= (880 * v22 - 1568 * v6) >> 10;
        v10 -= (880 * v6 - 1568 * v11) >> 10;
        v9 -= (880 * v11 - 1568 * v10) >> 10;
        v12 = 1568 * v9;
        v13 = 880 * v10;
        goto LABEL_8;
      case 4:
        v11 -= (960 * v22 - 1952 * v6) >> 10;
        v10 -= (960 * v6 - 1952 * v11) >> 10;
        v9 -= (960 * v11 - 1952 * v10) >> 10;
        v12 = 1952 * v9;
        v13 = 960 * v10;
LABEL_8:
        v8 -= (v13 - v12) >> 10;
LABEL_9:
        v22 = v9;
        v6 = v8;
        break;
      default:
        break;
    }
    if ( v11 >= -524288 )
    {
      if ( v11 > 524272 )
        v11 = 524272;
    }
    else
    {
      v11 = -524288;
    }
    *a4 = v11 >> 4;
    v14 = &a4[v20];
    if ( v10 >= -524288 )
    {
      if ( v10 > 524272 )
        v10 = 524272;
    }
    else
    {
      v10 = -524288;
    }
    *v14 = v10 >> 4;
    v15 = &v14[v20];
    if ( v9 >= -524288 )
    {
      if ( v9 > 524272 )
        v9 = 524272;
    }
    else
    {
      v9 = -524288;
    }
    *v15 = v9 >> 4;
    v16 = &v15[v20];
    if ( v8 >= -524288 )
    {
      if ( v8 > 524272 )
        v8 = 524272;
    }
    else
    {
      v8 = -524288;
    }
    *v16 = v8 >> 4;
    a4 = &v16[v20];
    if ( !--v23 )
      break;
    a3 = v18;
    v7 = v21;
  }
  *a1 = v6;
  a1[1] = v22;
  return a1;
}

int __cdecl xa_decode_wrapper(_DWORD *a1, int a2, int a3)
{
  if ( xa_get_audio_mode(a2) == 2 )
    return -(xa_setup_adpcm_decoder(a1, a2, a2 + 8, a3) != 0);
  else
    return -1;
}

int __cdecl xa_get_audio_mode(int a1)
{
  if ( (*(_BYTE *)(a1 + 2) & 0x24) == 0x24 )
    return 2;
  else
    return (*(_BYTE *)(a1 + 2) & 2) == 2;
}

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
    xa_prev_sample_rate[0] = (*(_BYTE *)(a2 + 3) >> 2) & 3;
    if ( xa_prev_sample_rate[0] )
    {
      if ( xa_prev_sample_rate[0] == 1 )
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
  if ( xa_prev_sample_rate[0] == v8 )
    return 0;
  xa_prev_sample_rate[0] = (*(_BYTE *)(a2 + 3) >> 2) & 3;
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

int __cdecl xa_decode_stereo_blocks(int a1, int a2)
{
  int v2; // ebx
  int v3; // edx
  int v4; // ebp
  char *v5; // esi
  __int16 *v6; // ecx
  int v7; // eax
  int v8; // edi
  int v9; // edx
  int v10; // edx
  int v11; // edx
  __int16 *v12; // ecx
  int v13; // eax
  int v14; // edi
  int v15; // edx
  int v16; // edx
  bool v17; // zf
  int result; // eax
  _WORD *v19; // [esp+10h] [ebp-2014h]
  int v20; // [esp+14h] [ebp-2010h]
  int v21; // [esp+18h] [ebp-200Ch]
  __int16 v22[4096]; // [esp+24h] [ebp-2000h] BYREF

  v2 = a2;
  v3 = a1 + 16;
  v19 = (_WORD *)(a1 + 32);
  v20 = a2;
  v21 = 18;
  do
  {
    v4 = v2 + 16;
    v5 = &xa_stereo_nibble_offset_table;
    do
    {
      v6 = v22;
      v7 = v4;
      v8 = 7;
      do
      {
        LOWORD(v2) = *(unsigned __int8 *)(v7 + 12);
        LOWORD(v3) = *(_BYTE *)(v7 + 8) & 0xF;
        ++v6;
        v7 += 16;
        v2 *= 16;
        v9 = v2 | v3;
        LOWORD(v2) = *(_BYTE *)(v7 - 12) & 0xF;
        v10 = v2 | (16 * v9);
        LOWORD(v2) = *(_BYTE *)(v7 - 16) & 0xF;
        v3 = v2 | (16 * v10);
        --v8;
        *(v6 - 1) = v3;
      }
      while ( v8 );
      xa_decode_adpcm_block((int *)(a1 + 16), *(_BYTE *)(v20 + *(_DWORD *)v5), v22, v19, 2u);
      v12 = v22;
      v13 = v4;
      v14 = 7;
      do
      {
        LOWORD(v2) = *(_BYTE *)(v13 + 8) >> 4;
        LOWORD(v11) = *(_BYTE *)(v13 + 12) >> 4;
        ++v12;
        v13 += 16;
        v15 = v2 | (16 * v11);
        LOWORD(v2) = *(_BYTE *)(v13 - 12) >> 4;
        v16 = v2 | (16 * v15);
        LOWORD(v2) = *(_BYTE *)(v13 - 16) >> 4;
        v11 = v2 | (16 * v16);
        --v14;
        *(v12 - 1) = v11;
      }
      while ( v14 );
      HIWORD(v2) = HIWORD(v20);
      xa_decode_adpcm_block((int *)(a1 + 24), *(_BYTE *)(v20 + *(_DWORD *)v5 + 1), v22, v19 + 1, 2u);
      v5 += 4;
      ++v4;
      v19 += 56;
    }
    while ( (int)v5 < (int)xa_mono_nibble_offset_table );
    v2 = v20 + 128;
    result = v21 - 1;
    v17 = v21 == 1;
    v20 += 128;
    --v21;
  }
  while ( !v17 );
  return result;
}

int xa_decode_mono_blocks(int a1, int a2, int a3)
{
  int v3; // edx
  int v4; // ebx
  int v5; // ebp
  _DWORD *v6; // esi
  __int16 *v7; // ecx
  int v8; // eax
  int v9; // edi
  int v10; // edx
  int v11; // edx
  int v12; // edx
  __int16 *v13; // ecx
  int v14; // eax
  int v15; // edi
  int v16; // edx
  int v17; // edx
  bool v18; // zf
  int result; // eax
  _WORD *v20; // [esp+10h] [ebp-2010h]
  int v21; // [esp+14h] [ebp-200Ch]
  int *v22; // [esp+18h] [ebp-2008h]
  int v23; // [esp+1Ch] [ebp-2004h]
  __int16 v24[4096]; // [esp+20h] [ebp-2000h] BYREF

  v4 = a2;
  v20 = (_WORD *)(a1 + 32);
  v22 = (int *)(a1 + 16);
  v21 = a2;
  v23 = 18;
  do
  {
    v5 = v4 + 16;
    v6 = xa_mono_nibble_offset_table;
    do
    {
      v7 = v24;
      v8 = v5;
      v9 = 7;
      do
      {
        LOWORD(v4) = *(unsigned __int8 *)(v8 + 12);
        LOWORD(v3) = *(_BYTE *)(v8 + 8) & 0xF;
        ++v7;
        v8 += 16;
        v4 *= 16;
        v10 = v4 | v3;
        LOWORD(v4) = *(_BYTE *)(v8 - 12) & 0xF;
        v11 = v4 | (16 * v10);
        LOWORD(v4) = *(_BYTE *)(v8 - 16) & 0xF;
        v3 = v4 | (16 * v11);
        --v9;
        *(v7 - 1) = v3;
      }
      while ( v9 );
      xa_decode_adpcm_block(v22, *(_BYTE *)(v21 + *v6), v24, v20, 1u);
      v13 = v24;
      v14 = v5;
      v15 = 7;
      do
      {
        LOWORD(v4) = *(_BYTE *)(v14 + 8) >> 4;
        LOWORD(v12) = *(_BYTE *)(v14 + 12) >> 4;
        ++v13;
        v14 += 16;
        v16 = v4 | (16 * v12);
        LOWORD(v4) = *(_BYTE *)(v14 - 12) >> 4;
        v17 = v4 | (16 * v16);
        LOWORD(v4) = *(_BYTE *)(v14 - 16) >> 4;
        v12 = v4 | (16 * v17);
        --v15;
        *(v13 - 1) = v12;
      }
      while ( v15 );
      HIWORD(v4) = HIWORD(v21);
      xa_decode_adpcm_block(v22, *(_BYTE *)(v21 + *v6++ + 1), v24, v20 + 28, 1u);
      ++v5;
      v20 += 56;
    }
    while ( (int)v6 < (int)&xa_mono_nibble_offset_table_end );
    v4 = v21 + 128;
    result = v23 - 1;
    v18 = v23 == 1;
    v21 += 128;
    --v23;
  }
  while ( !v18 );
  return result;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char xa_stereo_nibble_offset_table = 0x0;
unsigned char xa_prev_sample_rate[0x20];
unsigned int xa_mono_nibble_offset_table[4] = {0x0, 0x2, 0x8, 0xa};
unsigned int xa_mono_nibble_offset_table_end = 0x0;
