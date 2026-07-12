#include "pch.h"
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
    v6 = dword_44C134;
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
    while ( (int)v6 < (int)&dword_44C144 );
    v4 = v21 + 128;
    result = v23 - 1;
    v18 = v23 == 1;
    v21 += 128;
    --v23;
  }
  while ( !v18 );
  return result;
}
