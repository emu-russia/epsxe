#include "pch.h"
int __cdecl sub_43D500(int a1, unsigned int a2, int a3)
{
  __int64 v3; // rax
  int v4; // ebx
  int v5; // ecx
  int v6; // esi
  int v7; // edi
  int v8; // ebp
  int v9; // ecx
  int v10; // esi
  int v11; // edi
  int v12; // ecx
  int v13; // ebx
  int v14; // edi
  int v15; // edi
  int v16; // ecx
  int v17; // esi
  int v18; // edi
  int v19; // ecx
  int v20; // ebx
  int v21; // edi
  int v22; // edi
  int v23; // ecx
  int v24; // esi
  int v25; // edi
  int v26; // ecx
  int v27; // ebx
  int v28; // edi
  int v29; // edi
  int v30; // ecx
  int v31; // esi
  int v32; // ecx
  int v33; // edi
  int v34; // esi
  int v35; // esi
  int v36; // ecx
  int v37; // ecx
  int v38; // esi
  int v39; // edi
  int v40; // ecx
  int v41; // ebx
  int v42; // edi
  int v43; // edi
  int v44; // ecx
  int v45; // esi
  int v46; // ecx
  int v47; // edi
  int v48; // esi
  int v49; // esi
  int v50; // ecx
  int v51; // esi
  int v52; // edi
  int v53; // ecx
  int v54; // ebx
  int v55; // edi
  int v56; // edi
  int v57; // ecx
  int v58; // esi
  int v59; // ecx
  int v60; // edi
  int v61; // esi
  int v62; // esi
  bool v63; // zf
  int v65; // [esp+Ch] [ebp-8h]
  int v66; // [esp+10h] [ebp-4h]
  int v67; // [esp+18h] [ebp+4h]
  int v68; // [esp+1Ch] [ebp+8h]
  unsigned __int16 *v69; // [esp+20h] [ebp+Ch]

  v3 = a2;
  v4 = *(unsigned __int16 *)(a2 + 2);
  v65 = -1;
  v5 = 7;
  v6 = 4;
  if ( !(_WORD)v4 )
  {
    v5 = 138;
    v6 = 3;
  }
  if ( a3 >= 0 )
  {
    v7 = a3 + 1;
    v69 = (unsigned __int16 *)(a2 + 6);
    LODWORD(v3) = a1;
    v66 = v7;
    do
    {
      v8 = v4;
      ++HIDWORD(v3);
      v4 = *v69;
      v67 = v4;
      v68 = HIDWORD(v3);
      if ( SHIDWORD(v3) < v5 && v8 == v4 )
        goto LABEL_44;
      if ( SHIDWORD(v3) < v6 )
      {
        do
        {
          v9 = *(_DWORD *)(v3 + 5812);
          v10 = *(unsigned __int16 *)(v3 + 4 * v8 + 2678);
          if ( v9 <= 16 - (unsigned __int16)v10 )
          {
            *(_WORD *)(v3 + 5808) |= *(_WORD *)(v3 + 4 * v8 + 2676) << v9;
            *(_DWORD *)(v3 + 5812) = v10 + v9;
          }
          else
          {
            WORD2(v3) = *(_WORD *)(v3 + 4 * v8 + 2676);
            v11 = WORD2(v3) << v9;
            v12 = *(_DWORD *)(v3 + 8);
            *(_WORD *)(v3 + 5808) |= v11;
            *(_BYTE *)(v12 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
            v13 = *(_DWORD *)(v3 + 8);
            LOBYTE(v12) = *(_BYTE *)(v3 + 5809);
            v14 = *(_DWORD *)(v3 + 20) + 1;
            *(_DWORD *)(v3 + 20) = v14;
            *(_BYTE *)(v14 + v13) = v12;
            v15 = *(_DWORD *)(v3 + 5812);
            ++*(_DWORD *)(v3 + 20);
            *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v15);
            *(_DWORD *)(v3 + 5812) = v15 + v10 - 16;
            HIDWORD(v3) = v68;
          }
          v68 = --HIDWORD(v3);
        }
        while ( HIDWORD(v3) );
        goto LABEL_39;
      }
      if ( v8 )
      {
        if ( v8 != v65 )
        {
          v16 = *(_DWORD *)(v3 + 5812);
          v17 = *(unsigned __int16 *)(v3 + 4 * v8 + 2678);
          if ( v16 <= 16 - (unsigned __int16)v17 )
          {
            *(_WORD *)(v3 + 5808) |= *(_WORD *)(v3 + 4 * v8 + 2676) << v16;
            *(_DWORD *)(v3 + 5812) = v17 + v16;
          }
          else
          {
            WORD2(v3) = *(_WORD *)(v3 + 4 * v8 + 2676);
            v18 = WORD2(v3) << v16;
            v19 = *(_DWORD *)(v3 + 8);
            *(_WORD *)(v3 + 5808) |= v18;
            *(_BYTE *)(v19 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
            v20 = *(_DWORD *)(v3 + 8);
            LOBYTE(v19) = *(_BYTE *)(v3 + 5809);
            v21 = *(_DWORD *)(v3 + 20) + 1;
            *(_DWORD *)(v3 + 20) = v21;
            *(_BYTE *)(v21 + v20) = v19;
            v22 = *(_DWORD *)(v3 + 5812);
            ++*(_DWORD *)(v3 + 20);
            *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v22);
            *(_DWORD *)(v3 + 5812) = v22 + v17 - 16;
            HIDWORD(v3) = v68;
          }
          v68 = --HIDWORD(v3);
        }
        v23 = *(_DWORD *)(v3 + 5812);
        v24 = *(unsigned __int16 *)(v3 + 2742);
        if ( v23 <= 16 - (unsigned __int16)v24 )
        {
          *(_WORD *)(v3 + 5808) |= *(_WORD *)(v3 + 2740) << v23;
          *(_DWORD *)(v3 + 5812) = v24 + v23;
        }
        else
        {
          WORD2(v3) = *(_WORD *)(v3 + 2740);
          v25 = WORD2(v3) << v23;
          v26 = *(_DWORD *)(v3 + 8);
          *(_WORD *)(v3 + 5808) |= v25;
          *(_BYTE *)(v26 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
          v27 = *(_DWORD *)(v3 + 8);
          LOBYTE(v26) = *(_BYTE *)(v3 + 5809);
          v28 = *(_DWORD *)(v3 + 20) + 1;
          *(_DWORD *)(v3 + 20) = v28;
          *(_BYTE *)(v28 + v27) = v26;
          v29 = *(_DWORD *)(v3 + 5812);
          ++*(_DWORD *)(v3 + 20);
          *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v29);
          *(_DWORD *)(v3 + 5812) = v29 + v24 - 16;
          HIDWORD(v3) = v68;
        }
        v30 = *(_DWORD *)(v3 + 5812);
        if ( v30 > 14 )
        {
          HIDWORD(v3) -= 3;
          v31 = HIDWORD(v3) << v30;
          v32 = *(_DWORD *)(v3 + 8);
          *(_WORD *)(v3 + 5808) |= v31;
          *(_BYTE *)(v32 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
          v33 = *(_DWORD *)(v3 + 8);
          LOBYTE(v32) = *(_BYTE *)(v3 + 5809);
          v34 = *(_DWORD *)(v3 + 20) + 1;
          *(_DWORD *)(v3 + 20) = v34;
          *(_BYTE *)(v34 + v33) = v32;
          v35 = *(_DWORD *)(v3 + 5812);
          ++*(_DWORD *)(v3 + 20);
          *(_DWORD *)(v3 + 5812) = v35 - 14;
          *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v35);
          goto LABEL_39;
        }
        *(_WORD *)(v3 + 5808) |= (HIDWORD(v3) - 3) << v30;
        v36 = v30 + 2;
      }
      else if ( SHIDWORD(v3) > 10 )
      {
        v50 = *(_DWORD *)(v3 + 5812);
        v51 = *(unsigned __int16 *)(v3 + 2750);
        if ( v50 <= 16 - (unsigned __int16)v51 )
        {
          *(_WORD *)(v3 + 5808) |= *(_WORD *)(v3 + 2748) << v50;
          *(_DWORD *)(v3 + 5812) = v51 + v50;
        }
        else
        {
          WORD2(v3) = *(_WORD *)(v3 + 2748);
          v52 = WORD2(v3) << v50;
          v53 = *(_DWORD *)(v3 + 8);
          *(_WORD *)(v3 + 5808) |= v52;
          *(_BYTE *)(v53 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
          v54 = *(_DWORD *)(v3 + 8);
          LOBYTE(v53) = *(_BYTE *)(v3 + 5809);
          v55 = *(_DWORD *)(v3 + 20) + 1;
          *(_DWORD *)(v3 + 20) = v55;
          *(_BYTE *)(v55 + v54) = v53;
          v56 = *(_DWORD *)(v3 + 5812);
          ++*(_DWORD *)(v3 + 20);
          *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v56);
          *(_DWORD *)(v3 + 5812) = v56 + v51 - 16;
          HIDWORD(v3) = v68;
        }
        v57 = *(_DWORD *)(v3 + 5812);
        if ( v57 > 9 )
        {
          HIDWORD(v3) -= 11;
          v58 = HIDWORD(v3) << v57;
          v59 = *(_DWORD *)(v3 + 8);
          *(_WORD *)(v3 + 5808) |= v58;
          *(_BYTE *)(v59 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
          v60 = *(_DWORD *)(v3 + 8);
          LOBYTE(v59) = *(_BYTE *)(v3 + 5809);
          v61 = *(_DWORD *)(v3 + 20) + 1;
          *(_DWORD *)(v3 + 20) = v61;
          *(_BYTE *)(v61 + v60) = v59;
          v62 = *(_DWORD *)(v3 + 5812);
          ++*(_DWORD *)(v3 + 20);
          *(_DWORD *)(v3 + 5812) = v62 - 9;
          *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v62);
          goto LABEL_39;
        }
        *(_WORD *)(v3 + 5808) |= (HIDWORD(v3) - 11) << v57;
        v36 = v57 + 7;
      }
      else
      {
        v37 = *(_DWORD *)(v3 + 5812);
        v38 = *(unsigned __int16 *)(v3 + 2746);
        if ( v37 <= 16 - (unsigned __int16)v38 )
        {
          *(_WORD *)(v3 + 5808) |= *(_WORD *)(v3 + 2744) << v37;
          *(_DWORD *)(v3 + 5812) = v38 + v37;
        }
        else
        {
          WORD2(v3) = *(_WORD *)(v3 + 2744);
          v39 = WORD2(v3) << v37;
          v40 = *(_DWORD *)(v3 + 8);
          *(_WORD *)(v3 + 5808) |= v39;
          *(_BYTE *)(v40 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
          v41 = *(_DWORD *)(v3 + 8);
          LOBYTE(v40) = *(_BYTE *)(v3 + 5809);
          v42 = *(_DWORD *)(v3 + 20) + 1;
          *(_DWORD *)(v3 + 20) = v42;
          *(_BYTE *)(v42 + v41) = v40;
          v43 = *(_DWORD *)(v3 + 5812);
          ++*(_DWORD *)(v3 + 20);
          *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v43);
          *(_DWORD *)(v3 + 5812) = v43 + v38 - 16;
          HIDWORD(v3) = v68;
        }
        v44 = *(_DWORD *)(v3 + 5812);
        if ( v44 > 13 )
        {
          HIDWORD(v3) -= 3;
          v45 = HIDWORD(v3) << v44;
          v46 = *(_DWORD *)(v3 + 8);
          *(_WORD *)(v3 + 5808) |= v45;
          *(_BYTE *)(v46 + *(_DWORD *)(v3 + 20)) = *(_BYTE *)(v3 + 5808);
          v47 = *(_DWORD *)(v3 + 8);
          LOBYTE(v46) = *(_BYTE *)(v3 + 5809);
          v48 = *(_DWORD *)(v3 + 20) + 1;
          *(_DWORD *)(v3 + 20) = v48;
          *(_BYTE *)(v48 + v47) = v46;
          v49 = *(_DWORD *)(v3 + 5812);
          ++*(_DWORD *)(v3 + 20);
          *(_DWORD *)(v3 + 5812) = v49 - 13;
          *(_WORD *)(v3 + 5808) = WORD2(v3) >> (16 - v49);
          goto LABEL_39;
        }
        *(_WORD *)(v3 + 5808) |= (HIDWORD(v3) - 3) << v44;
        v36 = v44 + 3;
      }
      *(_DWORD *)(v3 + 5812) = v36;
LABEL_39:
      v4 = v67;
      HIDWORD(v3) = 0;
      v65 = v8;
      if ( v67 )
      {
        if ( v8 == v67 )
        {
          v5 = 6;
          v6 = 3;
        }
        else
        {
          v5 = 7;
          v6 = 4;
        }
      }
      else
      {
        v5 = 138;
        v6 = 3;
      }
LABEL_44:
      v63 = v66 == 1;
      v69 += 2;
      --v66;
    }
    while ( !v63 );
  }
  return v3;
}
