#include "pch.h"
int __cdecl sub_43AB20(int a1, int a2)
{
  int v2; // edi
  unsigned int v3; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // eax
  char v7; // cl
  __int16 v8; // ax
  unsigned __int16 v9; // ax
  int v10; // edx
  int v11; // eax
  unsigned int v12; // eax
  unsigned int v13; // edx
  BOOL v14; // ebp
  unsigned int v15; // ecx
  int v16; // eax
  int v17; // edi
  int v18; // edx
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  unsigned int v22; // ecx
  unsigned __int8 *v23; // edx
  int v24; // ecx
  int v25; // eax
  unsigned __int8 v26; // al
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  int v30; // eax
  int v32; // eax
  int v33; // [esp-14h] [ebp-24h]
  int v34; // [esp-14h] [ebp-24h]

  v2 = 0;
  while ( 1 )
  {
    v3 = *(_DWORD *)(a1 + 108);
    if ( v3 < 0x106 )
    {
      sub_43A970(a1);
      v3 = *(_DWORD *)(a1 + 108);
      if ( v3 < 0x106 && !a2 )
        return 0;
      if ( !v3 )
        break;
    }
    if ( v3 >= 3 )
    {
      v4 = *(_DWORD *)(a1 + 100);
      v5 = *(_DWORD *)(a1 + 60);
      v6 = *(_DWORD *)(a1 + 76)
         & (*(unsigned __int8 *)(*(_DWORD *)(a1 + 48) + v4 + 2)
          ^ (*(_DWORD *)(a1 + 64) << *(_DWORD *)(a1 + 80)));
      HIWORD(v2) = 0;
      *(_DWORD *)(a1 + 64) = v6;
      LOWORD(v2) = *(_WORD *)(v5 + 2 * v6);
      *(_WORD *)(*(_DWORD *)(a1 + 56) + 2 * (v4 & *(_DWORD *)(a1 + 44))) = v2;
      *(_WORD *)(*(_DWORD *)(a1 + 60) + 2 * *(_DWORD *)(a1 + 64)) = *(_WORD *)(a1 + 100);
    }
    if ( v2 && *(_DWORD *)(a1 + 100) - v2 <= (unsigned int)(*(_DWORD *)(a1 + 36) - 262) && *(_DWORD *)(a1 + 128) != 2 )
      *(_DWORD *)(a1 + 88) = sub_43AE50(a1, v2);
    if ( *(_DWORD *)(a1 + 88) < 3u )
    {
      v26 = *(_BYTE *)(*(_DWORD *)(a1 + 100) + *(_DWORD *)(a1 + 48));
      *(_WORD *)(*(_DWORD *)(a1 + 5788) + 2 * *(_DWORD *)(a1 + 5784)) = 0;
      *(_BYTE *)(*(_DWORD *)(a1 + 5776) + (*(_DWORD *)(a1 + 5784))++) = v26;
      ++*(_WORD *)(a1 + 4 * v26 + 140);
      v14 = *(_DWORD *)(a1 + 5784) == *(_DWORD *)(a1 + 5780) - 1;
      --*(_DWORD *)(a1 + 108);
    }
    else
    {
      v7 = *(_DWORD *)(a1 + 88);
      v8 = *(_WORD *)(a1 + 100) - *(_WORD *)(a1 + 104);
      *(_WORD *)(*(_DWORD *)(a1 + 5788) + 2 * *(_DWORD *)(a1 + 5784)) = v8;
      v9 = v8 - 1;
      *(_BYTE *)(*(_DWORD *)(a1 + 5776) + (*(_DWORD *)(a1 + 5784))++) = v7 - 3;
      v10 = (unsigned __int8)byte_4494B8[(unsigned __int8)(v7 - 3)];
      ++*(_WORD *)(a1 + 4 * v10 + 1168);
      if ( v9 >= 0x100u )
        v11 = (unsigned __int8)byte_4493B8[v9 >> 7];
      else
        v11 = (unsigned __int8)byte_4492B8[v9];
      ++*(_WORD *)(a1 + 4 * v11 + 2432);
      v12 = *(_DWORD *)(a1 + 88);
      v13 = *(_DWORD *)(a1 + 120);
      v14 = *(_DWORD *)(a1 + 5784) == *(_DWORD *)(a1 + 5780) - 1;
      v15 = *(_DWORD *)(a1 + 108) - v12;
      *(_DWORD *)(a1 + 108) = v15;
      if ( v12 > v13 || v15 < 3 )
      {
        v22 = v12 + *(_DWORD *)(a1 + 100);
        v23 = (unsigned __int8 *)(v22 + *(_DWORD *)(a1 + 48));
        *(_DWORD *)(a1 + 100) = v22;
        v24 = *(_DWORD *)(a1 + 80);
        *(_DWORD *)(a1 + 88) = 0;
        v25 = *v23;
        *(_DWORD *)(a1 + 64) = v25;
        *(_DWORD *)(a1 + 64) = *(_DWORD *)(a1 + 76) & (v23[1] ^ (v25 << v24));
        goto LABEL_24;
      }
      *(_DWORD *)(a1 + 88) = v12 - 1;
      do
      {
        v16 = *(_DWORD *)(a1 + 48);
        v17 = *(_DWORD *)(a1 + 64);
        v18 = *(_DWORD *)(a1 + 100) + 1;
        *(_DWORD *)(a1 + 100) = v18;
        v19 = *(_DWORD *)(a1 + 60);
        v20 = *(_DWORD *)(a1 + 76) & ((v17 << *(_DWORD *)(a1 + 80)) ^ *(unsigned __int8 *)(v18 + v16 + 2));
        HIWORD(v2) = 0;
        *(_DWORD *)(a1 + 64) = v20;
        LOWORD(v2) = *(_WORD *)(v19 + 2 * v20);
        *(_WORD *)(*(_DWORD *)(a1 + 56) + 2 * (*(_DWORD *)(a1 + 44) & v18)) = v2;
        *(_WORD *)(*(_DWORD *)(a1 + 60) + 2 * *(_DWORD *)(a1 + 64)) = *(_WORD *)(a1 + 100);
        v21 = *(_DWORD *)(a1 + 88) - 1;
        *(_DWORD *)(a1 + 88) = v21;
      }
      while ( v21 );
    }
    ++*(_DWORD *)(a1 + 100);
LABEL_24:
    if ( v14 )
    {
      v27 = *(_DWORD *)(a1 + 84);
      v28 = v27 < 0 ? 0 : *(_DWORD *)(a1 + 48) + v27;
      sub_43C970(a1, v28, *(_DWORD *)(a1 + 100) - v27, 0);
      v33 = *(_DWORD *)a1;
      *(_DWORD *)(a1 + 84) = *(_DWORD *)(a1 + 100);
      sub_43A490(v33);
      if ( !*(_DWORD *)(*(_DWORD *)a1 + 16) )
        return 0;
    }
  }
  v29 = *(_DWORD *)(a1 + 84);
  if ( v29 < 0 )
    v30 = 0;
  else
    v30 = v29 + *(_DWORD *)(a1 + 48);
  sub_43C970(a1, v30, *(_DWORD *)(a1 + 100) - v29, a2 == 4);
  v34 = *(_DWORD *)a1;
  *(_DWORD *)(a1 + 84) = *(_DWORD *)(a1 + 100);
  sub_43A490(v34);
  if ( !*(_DWORD *)(*(_DWORD *)a1 + 16) )
    return a2 != 4 ? 0 : 2;
  v32 = -(a2 != 4);
  LOBYTE(v32) = v32 & 0xFE;
  return v32 + 3;
}
