#include "pch.h"
int __cdecl sub_41EE40(int a1, int a2, unsigned int a3, unsigned int a4)
{
  unsigned int v4; // edx
  unsigned int v5; // ebx
  unsigned int v6; // ebp
  unsigned __int8 *i; // esi
  char v8; // cl
  unsigned __int8 *v9; // edi
  unsigned int v10; // eax
  int v11; // ecx
  unsigned int v12; // eax
  int v13; // edx
  int v14; // ecx
  char v15; // cl
  unsigned int v16; // ebx
  unsigned int j; // ebp
  char v18; // cl
  unsigned __int8 *v19; // edi
  unsigned int v20; // eax
  int v21; // ecx
  unsigned int v22; // eax
  int v23; // edx
  int v24; // ecx
  unsigned int v25; // ebp
  unsigned int v26; // ebx
  int v27; // edx
  unsigned int v28; // esi
  unsigned int v29; // ecx
  unsigned int v30; // eax
  unsigned int v32; // [esp+10h] [ebp-14h]
  unsigned int v33; // [esp+18h] [ebp-Ch]
  int v34; // [esp+1Ch] [ebp-8h]
  int v35; // [esp+20h] [ebp-4h]

  v4 = dword_4F8324;
  v5 = dword_4F832C;
  v6 = dword_4F8328;
  v34 = (unsigned __int16)word_448700[a3];
  v35 = (unsigned __int16)word_448700[a4];
LABEL_2:
  v32 = v4;
  while ( 1 )
  {
    while ( 1 )
    {
      for ( i = (unsigned __int8 *)dword_576980; v5 < a3; dword_576980 = (int)i )
      {
        v8 = v5;
        v5 += 8;
        v6 |= *i++ << v8;
      }
      v9 = (unsigned __int8 *)(a1 + 8 * (v6 & v34));
      v10 = *v9;
      if ( v10 > 0x10 )
      {
        while ( v10 != 99 )
        {
          v11 = v9[1];
          v12 = v10 - 16;
          v6 >>= v11;
          v5 -= v11;
          if ( v5 < v12 )
          {
            do
            {
              v13 = *i << v5;
              v5 += 8;
              v6 |= v13;
              dword_576980 = (int)++i;
            }
            while ( v5 < v12 );
            v4 = v32;
          }
          v9 = (unsigned __int8 *)(*((_DWORD *)v9 + 1) + 8 * (v6 & (unsigned __int16)word_448700[v12]));
          v10 = *v9;
          if ( v10 <= 0x10 )
            goto LABEL_11;
        }
        return 1;
      }
LABEL_11:
      v14 = v9[1];
      v6 >>= v14;
      v5 -= v14;
      if ( v10 != 16 )
        break;
      *((_BYTE *)lpMem + v4++) = v9[4];
      v32 = v4;
      if ( v4 == 0x8000 )
      {
        sub_41FE70(lpMem, 0x8000u);
        v4 = 0;
        goto LABEL_2;
      }
    }
    if ( v10 == 15 )
      break;
    if ( v5 < v10 )
    {
      do
      {
        v15 = v5;
        v5 += 8;
        v6 |= *i++ << v15;
        dword_576980 = (int)i;
      }
      while ( v5 < v10 );
      v4 = v32;
    }
    v16 = v5 - v10;
    v33 = *((unsigned __int16 *)v9 + 2) + (v6 & (unsigned __int16)word_448700[v10]);
    for ( j = v6 >> v10; v16 < a4; dword_576980 = (int)i )
    {
      v18 = v16;
      v16 += 8;
      j |= *i++ << v18;
    }
    v19 = (unsigned __int8 *)(a2 + 8 * (j & v35));
    v20 = *v19;
    if ( v20 > 0x10 )
    {
      while ( v20 != 99 )
      {
        v21 = v19[1];
        v22 = v20 - 16;
        j >>= v21;
        v16 -= v21;
        if ( v16 < v22 )
        {
          do
          {
            v23 = *i << v16;
            v16 += 8;
            j |= v23;
            dword_576980 = (int)++i;
          }
          while ( v16 < v22 );
          v4 = v32;
        }
        v19 = (unsigned __int8 *)(*((_DWORD *)v19 + 1) + 8 * (j & (unsigned __int16)word_448700[v22]));
        v20 = *v19;
        if ( v20 <= 0x10 )
          goto LABEL_26;
      }
      return 1;
    }
LABEL_26:
    v24 = v19[1];
    v25 = j >> v24;
    v26 = v16 - v24;
    if ( v26 < v20 )
    {
      do
      {
        v27 = *i << v26;
        v26 += 8;
        v25 |= v27;
        dword_576980 = (int)++i;
      }
      while ( v26 < v20 );
      v4 = v32;
    }
    LOWORD(v28) = v4 - (v25 & word_448700[v20]) - *((_WORD *)v19 + 2);
    v6 = v25 >> v20;
    v5 = v26 - v20;
    do
    {
      v28 &= 0x7FFFu;
      v29 = v28;
      if ( v28 <= v4 )
        v29 = v4;
      v30 = 0x8000 - v29;
      if ( 0x8000 - v29 > v33 )
        v30 = v33;
      v33 -= v30;
      if ( v4 - v28 < v30 )
      {
        do
        {
          *((_BYTE *)lpMem + v4++) = *((_BYTE *)lpMem + v28++);
          --v30;
        }
        while ( v30 );
      }
      else
      {
        qmemcpy((char *)lpMem + v4, (char *)lpMem + v28, v30);
        v4 = v30 + v32;
        LOWORD(v28) = v30 + v28;
      }
      v32 = v4;
      if ( v4 == 0x8000 )
      {
        sub_41FE70(lpMem, 0x8000u);
        v4 = 0;
        v32 = 0;
      }
    }
    while ( v33 );
  }
  dword_4F8328 = v6;
  dword_4F832C = v5;
  dword_4F8324 = v4;
  return 0;
}
