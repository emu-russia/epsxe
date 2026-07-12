#include "pch.h"
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
