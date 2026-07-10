#include "pch.h"
int __cdecl sub_43DB30(int a1, int a2, int a3)
{
  int result; // eax
  unsigned int v4; // ecx
  int v5; // ebp
  int v6; // edi
  int v7; // edx
  int v8; // ecx
  unsigned __int16 v9; // si
  int v10; // edx
  int v11; // ecx
  int v12; // ebx
  int v13; // edx
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // ebx
  int v18; // esi
  unsigned __int16 v19; // si
  int v20; // ebp
  int v21; // ebx
  char v22; // cl
  int v23; // ebx
  __int16 v24; // si
  int v25; // ecx
  __int16 v26; // bp
  int v27; // ecx
  int v28; // esi
  int v29; // edx
  int v30; // ecx
  int v31; // ebp
  int v32; // ebx
  char v33; // cl
  int v34; // ebx
  unsigned int v35; // edi
  int v36; // ebx
  int v37; // ecx
  int v38; // esi
  unsigned __int16 v39; // dx
  int v40; // ebp
  int v41; // ebx
  char v42; // cl
  int v43; // ebx
  int v44; // edx
  int v45; // edx
  unsigned int v46; // edi
  int v47; // ecx
  unsigned int v48; // esi
  int v49; // ecx
  int v50; // ebx
  int v51; // esi
  int v52; // esi
  int v53; // ecx
  int v54; // esi
  unsigned __int16 v55; // dx
  int v56; // edi
  int v57; // ecx
  int v58; // ebx
  int v59; // edi
  int v60; // edi
  int v61; // [esp+10h] [ebp-8h]
  unsigned int v62; // [esp+14h] [ebp-4h]
  int v63; // [esp+1Ch] [ebp+4h]
  int v64; // [esp+1Ch] [ebp+4h]

  result = a1;
  v4 = 0;
  v5 = a2;
  if ( *(_DWORD *)(a1 + 5784) )
  {
    while ( 1 )
    {
      v6 = *(unsigned __int16 *)(*(_DWORD *)(result + 5788) + 2 * v4);
      v7 = *(unsigned __int8 *)(v4 + *(_DWORD *)(result + 5776));
      v62 = v4 + 1;
      if ( !(_WORD)v6 )
        break;
      v16 = *(_DWORD *)(result + 5812);
      v17 = (unsigned __int8)byte_4494B8[v7];
      v63 = v17;
      v18 = *(unsigned __int16 *)(v5 + 4 * v17 + 1030);
      v61 = (unsigned __int16)v18;
      if ( v16 <= 16 - (unsigned __int16)v18 )
      {
        v26 = *(_WORD *)(a2 + 4 * v17 + 1028) << v16;
        v27 = *(_DWORD *)(result + 5812);
        *(_WORD *)(result + 5808) |= v26;
        v25 = v18 + v27;
      }
      else
      {
        v19 = *(_WORD *)(a2 + 4 * v17 + 1028);
        v20 = *(_DWORD *)(result + 8);
        *(_WORD *)(result + 5808) |= v19 << v16;
        *(_BYTE *)(*(_DWORD *)(result + 20) + v20) = *(_BYTE *)(result + 5808);
        v21 = *(_DWORD *)(result + 20) + 1;
        v22 = *(_BYTE *)(result + 5809);
        *(_DWORD *)(result + 20) = v21;
        *(_BYTE *)(*(_DWORD *)(result + 8) + v21) = v22;
        v23 = *(_DWORD *)(result + 5812);
        ++*(_DWORD *)(result + 20);
        v24 = v19 >> (16 - v23);
        v25 = v23 + v61 - 16;
        v17 = v63;
        *(_WORD *)(result + 5808) = v24;
      }
      *(_DWORD *)(result + 5812) = v25;
      v28 = dword_448C74[v17];
      if ( v28 )
      {
        v29 = v7 - dword_4495B8[v17];
        v30 = *(_DWORD *)(result + 5812);
        if ( v30 <= 16 - v28 )
        {
          *(_WORD *)(result + 5808) |= v29 << v30;
          *(_DWORD *)(result + 5812) = v28 + v30;
        }
        else
        {
          v31 = *(_DWORD *)(result + 8);
          *(_WORD *)(result + 5808) |= v29 << v30;
          *(_BYTE *)(*(_DWORD *)(result + 20) + v31) = *(_BYTE *)(result + 5808);
          v32 = *(_DWORD *)(result + 20) + 1;
          v33 = *(_BYTE *)(result + 5809);
          *(_DWORD *)(result + 20) = v32;
          *(_BYTE *)(*(_DWORD *)(result + 8) + v32) = v33;
          v34 = *(_DWORD *)(result + 5812);
          ++*(_DWORD *)(result + 20);
          *(_WORD *)(result + 5808) = (unsigned __int16)v29 >> (16 - v34);
          *(_DWORD *)(result + 5812) = v34 + v28 - 16;
        }
      }
      v35 = v6 - 1;
      if ( v35 >= 0x100 )
        v36 = (unsigned __int8)byte_4493B8[v35 >> 7];
      else
        v36 = (unsigned __int8)byte_4492B8[v35];
      v37 = *(_DWORD *)(result + 5812);
      v38 = *(unsigned __int16 *)(a3 + 4 * v36 + 2);
      v64 = v36;
      if ( v37 <= 16 - (unsigned __int16)v38 )
      {
        v5 = a2;
        *(_WORD *)(result + 5808) |= *(_WORD *)(a3 + 4 * v36) << v37;
        *(_DWORD *)(result + 5812) = v38 + v37;
      }
      else
      {
        v39 = *(_WORD *)(a3 + 4 * v36);
        v40 = *(_DWORD *)(result + 8);
        *(_WORD *)(result + 5808) |= v39 << v37;
        *(_BYTE *)(*(_DWORD *)(result + 20) + v40) = *(_BYTE *)(result + 5808);
        v41 = *(_DWORD *)(result + 20) + 1;
        v42 = *(_BYTE *)(result + 5809);
        *(_DWORD *)(result + 20) = v41;
        *(_BYTE *)(*(_DWORD *)(result + 8) + v41) = v42;
        v43 = *(_DWORD *)(result + 5812);
        ++*(_DWORD *)(result + 20);
        v5 = a2;
        *(_WORD *)(result + 5808) = v39 >> (16 - v43);
        v44 = v43 + v38 - 16;
        v36 = v64;
        *(_DWORD *)(result + 5812) = v44;
      }
      v45 = dword_448CE8[v36];
      if ( !v45 )
        goto LABEL_24;
      v46 = v35 - dword_44962C[v36];
      v47 = *(_DWORD *)(result + 5812);
      if ( v47 <= 16 - v45 )
      {
        *(_WORD *)(result + 5808) |= v46 << v47;
        v15 = v45 + v47;
LABEL_23:
        *(_DWORD *)(result + 5812) = v15;
        goto LABEL_24;
      }
      v48 = v46 << v47;
      v49 = *(_DWORD *)(result + 8);
      *(_WORD *)(result + 5808) |= v48;
      *(_BYTE *)(v49 + *(_DWORD *)(result + 20)) = *(_BYTE *)(result + 5808);
      v50 = *(_DWORD *)(result + 8);
      LOBYTE(v49) = *(_BYTE *)(result + 5809);
      v51 = *(_DWORD *)(result + 20) + 1;
      *(_DWORD *)(result + 20) = v51;
      *(_BYTE *)(v51 + v50) = v49;
      v52 = *(_DWORD *)(result + 5812);
      ++*(_DWORD *)(result + 20);
      *(_DWORD *)(result + 5812) = v52 + v45 - 16;
      *(_WORD *)(result + 5808) = (unsigned __int16)v46 >> (16 - v52);
LABEL_24:
      v4 = v62;
      if ( v62 >= *(_DWORD *)(result + 5784) )
        goto LABEL_25;
    }
    LOWORD(v6) = *(_WORD *)(v5 + 4 * v7 + 2);
    v8 = *(_DWORD *)(result + 5812);
    if ( v8 <= 16 - (unsigned __int16)v6 )
    {
      *(_WORD *)(result + 5808) |= *(_WORD *)(v5 + 4 * v7) << v8;
      v15 = v6 + v8;
    }
    else
    {
      v9 = *(_WORD *)(v5 + 4 * v7);
      v10 = v9 << v8;
      v11 = *(_DWORD *)(result + 8);
      *(_WORD *)(result + 5808) |= v10;
      *(_BYTE *)(v11 + *(_DWORD *)(result + 20)) = *(_BYTE *)(result + 5808);
      v12 = *(_DWORD *)(result + 8);
      v13 = *(_DWORD *)(result + 20) + 1;
      *(_DWORD *)(result + 20) = v13;
      *(_BYTE *)(v13 + v12) = *(_BYTE *)(result + 5809);
      v14 = *(_DWORD *)(result + 5812);
      ++*(_DWORD *)(result + 20);
      v15 = v14 + v6 - 16;
      *(_WORD *)(result + 5808) = v9 >> (16 - v14);
    }
    goto LABEL_23;
  }
LABEL_25:
  v53 = *(_DWORD *)(result + 5812);
  v54 = *(unsigned __int16 *)(v5 + 1026);
  if ( v53 <= 16 - (unsigned __int16)v54 )
  {
    *(_WORD *)(result + 5808) |= *(_WORD *)(v5 + 1024) << v53;
    *(_DWORD *)(result + 5812) = v54 + v53;
  }
  else
  {
    v55 = *(_WORD *)(v5 + 1024);
    v56 = v55 << v53;
    v57 = *(_DWORD *)(result + 8);
    *(_WORD *)(result + 5808) |= v56;
    *(_BYTE *)(v57 + *(_DWORD *)(result + 20)) = *(_BYTE *)(result + 5808);
    v58 = *(_DWORD *)(result + 8);
    LOBYTE(v57) = *(_BYTE *)(result + 5809);
    v59 = *(_DWORD *)(result + 20) + 1;
    *(_DWORD *)(result + 20) = v59;
    *(_BYTE *)(v59 + v58) = v57;
    v60 = *(_DWORD *)(result + 5812);
    ++*(_DWORD *)(result + 20);
    *(_WORD *)(result + 5808) = v55 >> (16 - v60);
    *(_DWORD *)(result + 5812) = v60 + v54 - 16;
  }
  *(_DWORD *)(result + 5804) = *(unsigned __int16 *)(v5 + 1026);
  return result;
}
