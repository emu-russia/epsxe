#include "pch.h"
int __cdecl sub_43F250(int a1, int a2, int a3, int a4, _DWORD *a5, unsigned __int8 **a6)
{
  _BYTE *v6; // ebx
  unsigned int v7; // esi
  unsigned int v8; // edx
  unsigned __int8 **v9; // edi
  unsigned __int8 *v10; // ebp
  unsigned int v11; // eax
  int v12; // esi
  int v13; // ebx
  _BYTE *v14; // esi
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ebx
  unsigned int v19; // eax
  unsigned int i; // edx
  int v21; // esi
  int v22; // ebx
  int v23; // esi
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  unsigned int j; // ebx
  char v28; // cl
  unsigned int v29; // edi
  int v30; // esi
  _BYTE *v31; // ecx
  _BYTE *v32; // esi
  unsigned int v33; // edi
  int v34; // ecx
  unsigned int v35; // ebx
  unsigned int v36; // ecx
  unsigned int v37; // esi
  unsigned int v38; // ecx
  unsigned __int8 *v39; // ebp
  unsigned __int8 *v40; // edx
  int v41; // ecx
  unsigned int v43; // ecx
  unsigned __int8 *v44; // ebp
  unsigned __int8 *v45; // edx
  unsigned __int8 *v46; // ecx
  unsigned __int8 *v47; // ebp
  unsigned __int8 *v48; // edx
  unsigned __int8 *v49; // ecx
  unsigned int v50; // [esp+10h] [ebp-14h]
  _BYTE *v51; // [esp+14h] [ebp-10h]
  unsigned int v52; // [esp+18h] [ebp-Ch]
  int v53; // [esp+1Ch] [ebp-8h]
  int v54; // [esp+20h] [ebp-4h]
  unsigned int v55; // [esp+28h] [ebp+4h]

  v6 = (_BYTE *)a5[13];
  v7 = a5[12];
  v8 = a5[8];
  v9 = a6;
  v51 = v6;
  v10 = *a6;
  v50 = (unsigned int)a6[1];
  v11 = a5[7];
  if ( (unsigned int)v6 >= v7 )
    v52 = a5[11] - (_DWORD)v6;
  else
    v52 = v7 - (_DWORD)v6 - 1;
  v53 = dword_458938[a1];
  v54 = dword_458938[a2];
  while ( 1 )
  {
    for ( ; v11 < 0x14; ++v10 )
    {
      --v50;
      v12 = *v10 << v11;
      v11 += 8;
      v8 |= v12;
    }
    v13 = *(unsigned __int8 *)(a3 + 8 * (v8 & v53));
    v14 = (_BYTE *)(a3 + 8 * (v8 & v53));
    if ( *v14 )
      break;
LABEL_27:
    v34 = (unsigned __int8)v14[1];
    v8 >>= v34;
    v11 -= v34;
    *v51++ = v14[4];
    --v52;
LABEL_28:
    if ( v52 < 0x102 || v50 < 0xA )
    {
      v38 = (unsigned int)&v9[1][-v50];
      if ( v11 >> 3 < v38 )
        v38 = v11 >> 3;
      v39 = &v10[-v38];
      a5[8] = v8;
      a5[7] = v11 - 8 * v38;
      v40 = *v9;
      v9[1] = (unsigned __int8 *)(v50 + v38);
      v41 = (int)&v9[2][v39 - v40];
      *v9 = v39;
      v9[2] = (unsigned __int8 *)v41;
      a5[13] = v51;
      return 0;
    }
  }
  v15 = (unsigned __int8)v14[1];
  v8 >>= v15;
  v11 -= v15;
  if ( (v13 & 0x10) != 0 )
  {
LABEL_12:
    v18 = v13 & 0xF;
    v19 = v11 - v18;
    v55 = *((_DWORD *)v14 + 1) + (v8 & dword_458938[v18]);
    for ( i = v8 >> v18; v19 < 0xF; ++v10 )
    {
      --v50;
      v21 = *v10 << v19;
      v19 += 8;
      i |= v21;
    }
    v22 = *(unsigned __int8 *)(a4 + 8 * (i & v54));
    v23 = a4 + 8 * (i & v54);
    v24 = *(unsigned __int8 *)(v23 + 1);
    v8 = i >> v24;
    v11 = v19 - v24;
    if ( (v22 & 0x10) == 0 )
    {
      while ( (v22 & 0x40) == 0 )
      {
        v25 = *(_DWORD *)(v23 + 4) + (v8 & dword_458938[v22]);
        v22 = *(unsigned __int8 *)(v23 + 8 * v25);
        v23 += 8 * v25;
        v26 = *(unsigned __int8 *)(v23 + 1);
        v8 >>= v26;
        v11 -= v26;
        if ( (v22 & 0x10) != 0 )
          goto LABEL_17;
      }
      v35 = v50;
      v36 = (unsigned int)&v9[1][-v50];
      v37 = v11 >> 3;
      v9[6] = (unsigned __int8 *)aInvalidDistanc_0;
      if ( v11 >> 3 < v36 )
LABEL_41:
        v36 = v37;
LABEL_42:
      v47 = &v10[-v36];
      a5[8] = v8;
      a5[7] = v11 - 8 * v36;
      v48 = *v9;
      v9[1] = (unsigned __int8 *)(v35 + v36);
      v49 = v9[2];
      *v9 = v47;
      v9[2] = &v49[v47 - v48];
      a5[13] = v51;
      return -3;
    }
LABEL_17:
    for ( j = v22 & 0xF; v11 < j; ++v10 )
    {
      --v50;
      v28 = v11;
      v11 += 8;
      v8 |= *v10 << v28;
    }
    v29 = *(_DWORD *)(v23 + 4) + (v8 & dword_458938[j]);
    v8 >>= j;
    v11 -= j;
    v52 -= v55;
    v30 = a5[10];
    v31 = v51;
    if ( (unsigned int)&v51[-v30] < v29 )
    {
      v33 = v29 + v30 - (_DWORD)v51;
      v32 = (_BYTE *)(a5[11] - v33);
      if ( v55 > v33 )
      {
        v55 -= v33;
        do
        {
          *v31++ = *v32++;
          --v33;
        }
        while ( v33 );
        v32 = (_BYTE *)a5[10];
      }
    }
    else
    {
      *v51 = v51[-v29];
      v31 = v51 + 2;
      v32 = &v51[-v29 + 2];
      v51[1] = v51[-v29 + 1];
      v55 -= 2;
    }
    do
    {
      *v31++ = *v32++;
      --v55;
    }
    while ( v55 );
    v9 = a6;
    v51 = v31;
    goto LABEL_28;
  }
  while ( (v13 & 0x40) == 0 )
  {
    v16 = *((_DWORD *)v14 + 1) + (v8 & dword_458938[v13]);
    v13 = (unsigned __int8)v14[8 * v16];
    v14 += 8 * v16;
    if ( !v13 )
      goto LABEL_27;
    v17 = (unsigned __int8)v14[1];
    v8 >>= v17;
    v11 -= v17;
    if ( (v13 & 0x10) != 0 )
      goto LABEL_12;
  }
  if ( (v13 & 0x20) == 0 )
  {
    v35 = v50;
    v36 = (unsigned int)&v9[1][-v50];
    v37 = v11 >> 3;
    v9[6] = (unsigned __int8 *)aInvalidLiteral_0;
    if ( v11 >> 3 < v36 )
      goto LABEL_41;
    goto LABEL_42;
  }
  v43 = (unsigned int)&v9[1][-v50];
  if ( v11 >> 3 < v43 )
    v43 = v11 >> 3;
  v44 = &v10[-v43];
  a5[8] = v8;
  a5[7] = v11 - 8 * v43;
  v45 = *v9;
  v9[1] = (unsigned __int8 *)(v50 + v43);
  v46 = v9[2];
  *v9 = v44;
  v9[2] = &v46[v44 - v45];
  a5[13] = v51;
  return 1;
}
