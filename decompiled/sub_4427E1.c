#include "pch.h"
_DWORD *__cdecl sub_4427E1(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  int *v3; // esi
  unsigned int v4; // edi
  int v5; // ecx
  char *v6; // ebx
  unsigned int v7; // edx
  _BYTE *v8; // ecx
  unsigned int v9; // ebx
  bool v10; // zf
  _BYTE *v11; // ecx
  unsigned int v12; // ebx
  unsigned int v13; // edx
  unsigned int v14; // ebx
  unsigned int v15; // esi
  unsigned int v16; // esi
  _DWORD *v17; // ecx
  LPVOID *v18; // eax
  _DWORD *v19; // [esp+Ch] [ebp-10h]
  int v20; // [esp+10h] [ebp-Ch]
  int v21; // [esp+14h] [ebp-8h]
  int v22; // [esp+18h] [ebp-4h]
  char *v23; // [esp+28h] [ebp+Ch]
  int *v24; // [esp+28h] [ebp+Ch]
  char v25; // [esp+2Bh] [ebp+Fh]

  result = (_DWORD *)a1[4];
  v3 = (int *)(a2 - 4);
  v4 = (unsigned int)(a2 - a1[3]) >> 15;
  v19 = &result[129 * v4 + 81];
  v5 = *(_DWORD *)(a2 - 4) - 1;
  v22 = v5;
  if ( (v5 & 1) == 0 )
  {
    v6 = (char *)v3 + v5;
    v20 = *(int *)((char *)v3 + v5);
    v21 = *(_DWORD *)(a2 - 8);
    v23 = (char *)v3 + v5;
    if ( (v20 & 1) == 0 )
    {
      v7 = (v20 >> 4) - 1;
      if ( v7 > 0x3F )
        v7 = 63;
      if ( *((_DWORD *)v6 + 1) == *((_DWORD *)v6 + 2) )
      {
        if ( v7 >= 0x20 )
        {
          v11 = (char *)result + v7 + 4;
          v12 = ~(0x80000000 >> (v7 - 32));
          result[v4 + 49] &= v12;
          v10 = (*v11)-- == 1;
          if ( v10 )
            a1[1] &= v12;
        }
        else
        {
          v8 = (char *)result + v7 + 4;
          v9 = ~(0x80000000 >> v7);
          result[v4 + 17] &= v9;
          v10 = (*v8)-- == 1;
          if ( v10 )
            *a1 &= v9;
        }
        v5 = v22;
        v6 = v23;
      }
      v5 += v20;
      *(_DWORD *)(*((_DWORD *)v6 + 2) + 4) = *((_DWORD *)v6 + 1);
      v22 = v5;
      *(_DWORD *)(*((_DWORD *)v23 + 1) + 8) = *((_DWORD *)v23 + 2);
    }
    v13 = (v5 >> 4) - 1;
    if ( v13 > 0x3F )
      v13 = 63;
    if ( (v21 & 1) != 0 )
    {
      v14 = (unsigned int)a1;
    }
    else
    {
      v24 = (int *)((char *)v3 - v21);
      v14 = (v21 >> 4) - 1;
      if ( v14 > 0x3F )
        v14 = 63;
      v22 = v21 + v5;
      v13 = ((v21 + v5) >> 4) - 1;
      if ( v13 > 0x3F )
        v13 = 63;
      if ( v14 != v13 )
      {
        if ( v24[1] == v24[2] )
        {
          if ( v14 >= 0x20 )
          {
            v16 = ~(0x80000000 >> (v14 - 32));
            result[v4 + 49] &= v16;
            v10 = (*((_BYTE *)result + v14 + 4))-- == 1;
            if ( v10 )
              a1[1] &= v16;
          }
          else
          {
            v15 = ~(0x80000000 >> v14);
            result[v4 + 17] &= v15;
            v10 = (*((_BYTE *)result + v14 + 4))-- == 1;
            if ( v10 )
              *a1 &= v15;
          }
        }
        *(_DWORD *)(v24[2] + 4) = v24[1];
        *(_DWORD *)(v24[1] + 8) = v24[2];
      }
      v3 = v24;
    }
    if ( (v21 & 1) != 0 || v14 != v13 )
    {
      v17 = &v19[2 * v13];
      v3[1] = v17[1];
      v3[2] = (int)v17;
      v17[1] = v3;
      *(_DWORD *)(v3[1] + 8) = v3;
      if ( v3[1] == v3[2] )
      {
        v25 = *((_BYTE *)result + v13 + 4);
        *((_BYTE *)result + v13 + 4) = v25 + 1;
        if ( v13 >= 0x20 )
        {
          if ( !v25 )
            a1[1] |= 0x80000000 >> (v13 - 32);
          result[v4 + 49] |= 0x80000000 >> (v13 - 32);
        }
        else
        {
          if ( !v25 )
            *a1 |= 0x80000000 >> v13;
          result[v4 + 17] |= 0x80000000 >> v13;
        }
      }
    }
    *v3 = v22;
    *(int *)((char *)v3 + v22 - 4) = v22;
    result += 129 * v4 + 81;
    v10 = (*v19)-- == 1;
    if ( v10 )
    {
      if ( unk_8B5CF0 )
      {
        VirtualFree((LPVOID)(*((_DWORD *)unk_8B5CF0 + 3) + (*(_DWORD *)byte_8B5CE8 << 15)), 0x8000u, 0x4000u);
        *((_DWORD *)unk_8B5CF0 + 2) |= 0x80000000 >> byte_8B5CE8[0];
        *(_DWORD *)(*((_DWORD *)unk_8B5CF0 + 4) + 4 * *(_DWORD *)byte_8B5CE8 + 196) = 0;
        --*(_BYTE *)(*((_DWORD *)unk_8B5CF0 + 4) + 67);
        v18 = (LPVOID *)unk_8B5CF0;
        if ( !*(_BYTE *)(*((_DWORD *)unk_8B5CF0 + 4) + 67) )
        {
          *((_DWORD *)unk_8B5CF0 + 1) &= ~1u;
          v18 = (LPVOID *)unk_8B5CF0;
        }
        if ( v18[2] == (LPVOID)-1 )
        {
          VirtualFree(v18[3], 0, 0x8000u);
          HeapFree(unk_8B5D00, 0, *((LPVOID *)unk_8B5CF0 + 4));
          memcpy_0(unk_8B5CF0, (char *)unk_8B5CF0 + 20, (size_t)unk_8B5CF8 + 20 * unk_8B5CF4 - (_DWORD)unk_8B5CF0 - 20);
          --unk_8B5CF4;
          if ( a1 > unk_8B5CF0 )
            a1 -= 5;
          unk_8B5CEC = unk_8B5CF8;
        }
      }
      *(_DWORD *)byte_8B5CE8 = v4;
      unk_8B5CF0 = a1;
      return a1;
    }
  }
  return result;
}
