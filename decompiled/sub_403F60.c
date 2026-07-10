#include "pch.h"
int __usercall sub_403F60@<eax>(int a1@<edx>, int a2, int a3)
{
  int v3; // ebx
  int v4; // ebp
  _DWORD *v5; // esi
  _BYTE *v6; // ecx
  int v7; // eax
  int v8; // edi
  int v9; // edx
  int v10; // edx
  int v11; // edx
  _BYTE *v12; // ecx
  int v13; // eax
  int v14; // edi
  int v15; // edx
  int v16; // edx
  bool v17; // zf
  int result; // eax
  int v19; // [esp+10h] [ebp-2010h]
  int v20; // [esp+14h] [ebp-200Ch]
  int v21; // [esp+18h] [ebp-2008h]
  int v22; // [esp+1Ch] [ebp-2004h]
  _BYTE v23[8192]; // [esp+20h] [ebp-2000h] BYREF

  v3 = a3;
  v19 = a2 + 32;
  v21 = a2 + 16;
  v20 = a3;
  v22 = 18;
  do
  {
    v4 = v3 + 16;
    v5 = &dword_44C134;
    do
    {
      v6 = v23;
      v7 = v4;
      v8 = 7;
      do
      {
        LOWORD(v3) = *(unsigned __int8 *)(v7 + 12);
        LOWORD(a1) = *(_BYTE *)(v7 + 8) & 0xF;
        v6 += 2;
        v7 += 16;
        v3 *= 16;
        v9 = v3 | a1;
        LOWORD(v3) = *(_BYTE *)(v7 - 12) & 0xF;
        v10 = v3 | (16 * v9);
        LOWORD(v3) = *(_BYTE *)(v7 - 16) & 0xF;
        a1 = v3 | (16 * v10);
        --v8;
        *((_WORD *)v6 - 1) = a1;
      }
      while ( v8 );
      sub_403910(v21, *(unsigned __int8 *)(v20 + *v5), v23, v19, 1);
      v12 = v23;
      v13 = v4;
      v14 = 7;
      do
      {
        LOWORD(v3) = *(_BYTE *)(v13 + 8) >> 4;
        LOWORD(v11) = *(_BYTE *)(v13 + 12) >> 4;
        v12 += 2;
        v13 += 16;
        v15 = v3 | (16 * v11);
        LOWORD(v3) = *(_BYTE *)(v13 - 12) >> 4;
        v16 = v3 | (16 * v15);
        LOWORD(v3) = *(_BYTE *)(v13 - 16) >> 4;
        v11 = v3 | (16 * v16);
        --v14;
        *((_WORD *)v12 - 1) = v11;
      }
      while ( v14 );
      HIWORD(v3) = HIWORD(v20);
      sub_403910(v21, *(unsigned __int8 *)(v20 + *v5++ + 1), v23, v19 + 56, 1);
      ++v4;
      v19 += 112;
    }
    while ( (int)v5 < (int)&dword_44C144 );
    v3 = v20 + 128;
    result = v22 - 1;
    v17 = v22 == 1;
    v20 += 128;
    --v22;
  }
  while ( !v17 );
  return result;
}
