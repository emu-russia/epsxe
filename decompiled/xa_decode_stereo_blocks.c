#include "pch.h"
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
    v5 = &byte_44C124;
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
    while ( (int)v5 < (int)dword_44C134 );
    v2 = v20 + 128;
    result = v21 - 1;
    v17 = v21 == 1;
    v20 += 128;
    --v21;
  }
  while ( !v17 );
  return result;
}
