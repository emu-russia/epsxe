#include "pch.h"
int __cdecl sub_41F1F0(int *a1)
{
  int v1; // ecx
  unsigned int v2; // eax
  unsigned __int8 *v3; // esi
  int v4; // edx
  unsigned __int8 *v5; // esi
  int v6; // edx
  unsigned int v7; // eax
  unsigned int v8; // ecx
  int v9; // edx
  int v10; // edx
  int result; // eax
  unsigned __int8 *v12; // eax
  int v13; // ebp
  int v14; // ecx
  unsigned int v15; // esi
  unsigned int m; // ebx
  int v17; // edx
  unsigned int v18; // esi
  int v19; // edi
  unsigned int n; // ebx
  int v21; // edx
  unsigned int v22; // ebx
  unsigned int v23; // esi
  char v24; // cl
  int v25; // esi
  unsigned __int8 *v26; // eax
  unsigned int v27; // ebx
  unsigned int i; // esi
  int v29; // edx
  unsigned int v30; // edx
  unsigned int v31; // esi
  unsigned int v32; // ebx
  int v33; // edi
  unsigned int v34; // edi
  unsigned int v35; // esi
  unsigned int v36; // ebx
  int v37; // ebp
  unsigned int v38; // ebp
  unsigned int v39; // ebx
  unsigned int v40; // esi
  unsigned int v41; // edi
  char v42; // cl
  int v43; // edx
  int v44; // ecx
  int v45; // ecx
  int v46; // eax
  unsigned int v47; // ecx
  int v48; // edi
  unsigned int v49; // ebp
  unsigned __int16 v50; // dx
  unsigned int v51; // edi
  unsigned __int8 *v52; // edx
  int v53; // eax
  int v54; // ecx
  int v55; // ecx
  int v56; // eax
  unsigned int v57; // ecx
  int v58; // eax
  int v59; // ecx
  int v60; // eax
  int v61; // esi
  unsigned int v62; // esi
  int v63; // [esp+0h] [ebp-524h] BYREF
  unsigned int v64; // [esp+4h] [ebp-520h] BYREF
  int v65; // [esp+8h] [ebp-51Ch]
  unsigned int v66; // [esp+Ch] [ebp-518h]
  int v67; // [esp+10h] [ebp-514h] BYREF
  int v68; // [esp+14h] [ebp-510h] BYREF
  unsigned int j; // [esp+18h] [ebp-50Ch]
  unsigned int k; // [esp+1Ch] [ebp-508h]
  int v71; // [esp+20h] [ebp-504h]
  _DWORD v72[32]; // [esp+24h] [ebp-500h] BYREF
  _DWORD v73[144]; // [esp+A4h] [ebp-480h] BYREF
  _DWORD v74[112]; // [esp+2E4h] [ebp-240h] BYREF
  _DWORD v75[24]; // [esp+4A4h] [ebp-80h] BYREF
  _DWORD v76[8]; // [esp+504h] [ebp-20h] BYREF

  v1 = dword_4F832C;
  v2 = dword_4F8328;
  if ( !dword_4F832C )
  {
    v3 = (unsigned __int8 *)dword_576980;
    do
    {
      v4 = *v3 << v1;
      v1 += 8;
      v2 |= v4;
      dword_576980 = (int)++v3;
    }
    while ( !v1 );
  }
  v5 = (unsigned __int8 *)a1;
  v6 = v2 & 1;
  v7 = v2 >> 1;
  v8 = v1 - 1;
  *a1 = v6;
  if ( v8 < 2 )
  {
    v5 = (unsigned __int8 *)dword_576980;
    do
    {
      v9 = *v5 << v8;
      v8 += 8;
      v7 |= v9;
      dword_576980 = (int)++v5;
    }
    while ( v8 < 2 );
  }
  v10 = v7 & 3;
  dword_4F8328 = v7 >> 2;
  dword_4F832C = v8 - 2;
  if ( v10 == 2 )
  {
    v26 = (unsigned __int8 *)dword_576980;
    v27 = dword_4F8328;
    for ( i = dword_4F832C; i < 5; dword_576980 = (int)v26 )
    {
      v29 = *v26 << i;
      i += 8;
      v27 |= v29;
      ++v26;
    }
    v30 = (v27 & 0x1F) + 257;
    v31 = i - 5;
    v32 = v27 >> 5;
    for ( j = v30; v31 < 5; dword_576980 = (int)v26 )
    {
      v33 = *v26 << v31;
      v31 += 8;
      v32 |= v33;
      ++v26;
    }
    v34 = (v32 & 0x1F) + 1;
    v35 = v31 - 5;
    v36 = v32 >> 5;
    for ( k = v34; v35 < 4; dword_576980 = (int)v26 )
    {
      v37 = *v26 << v35;
      v35 += 8;
      v36 |= v37;
      ++v26;
    }
    v38 = (v36 & 0xF) + 4;
    v39 = v36 >> 4;
    v40 = v35 - 4;
    if ( v30 <= 0x120 && v34 <= 0x20 )
    {
      v41 = 0;
      if ( !v38 )
        goto LABEL_94;
      do
      {
        for ( ; v40 < 3; dword_576980 = (int)v26 )
        {
          v42 = v40;
          v40 += 8;
          v39 |= *v26++ << v42;
        }
        v43 = dword_455028[v41];
        v44 = v39 & 7;
        v39 >>= 3;
        v40 -= 3;
        ++v41;
        v72[v43] = v44;
      }
      while ( v41 < v38 );
      if ( v41 < 0x13 )
      {
LABEL_94:
        do
        {
          v45 = dword_455028[v41++];
          v72[v45] = 0;
        }
        while ( v41 < 0x13 );
      }
      v64 = 7;
      v46 = sub_41F960(v72, 19, 19, 0, 0, &v63, &v64);
      v47 = v64;
      v48 = v46;
      if ( !v64 )
      {
        sub_41FE40(v63);
        return 1;
      }
      if ( v46 )
      {
        if ( v46 == 1 )
          sub_41FE40(v63);
        return v48;
      }
      v49 = j;
      v50 = word_448700[v64];
      v51 = 0;
      v66 = j + k;
      v65 = 0;
      v71 = v50;
      if ( j + k )
      {
        v52 = (unsigned __int8 *)dword_576980;
        while ( 1 )
        {
          if ( v40 < v47 )
          {
            do
            {
              v53 = *v52 << v40;
              v40 += 8;
              v39 |= v53;
              dword_576980 = (int)++v52;
            }
            while ( v40 < v64 );
          }
          v67 = v63 + 8 * (v39 & v71);
          v54 = *(unsigned __int8 *)(v67 + 1);
          v39 >>= v54;
          v40 -= v54;
          v55 = *(unsigned __int16 *)(v67 + 4);
          if ( (unsigned __int16)v55 >= 0x10u )
          {
            if ( (unsigned __int16)v55 == 16 )
            {
              for ( ; v40 < 2; dword_576980 = (int)v52 )
              {
                v56 = *v52 << v40;
                v40 += 8;
                v39 |= v56;
                ++v52;
              }
              v57 = (v39 & 3) + 3;
              v39 >>= 2;
              v40 -= 2;
              if ( v51 + v57 > v66 )
                return 1;
              if ( v57 )
              {
                memset32(&v72[v51], v65, v57);
                v51 += v57;
              }
            }
            else
            {
              if ( v55 == 17 )
              {
                for ( ; v40 < 3; dword_576980 = (int)v52 )
                {
                  v58 = *v52 << v40;
                  v40 += 8;
                  v39 |= v58;
                  ++v52;
                }
                v59 = (v39 & 7) + 3;
                v39 >>= 3;
                v40 -= 3;
              }
              else
              {
                for ( ; v40 < 7; dword_576980 = (int)v52 )
                {
                  v60 = *v52 << v40;
                  v40 += 8;
                  v39 |= v60;
                  ++v52;
                }
                v59 = (v39 & 0x7F) + 11;
                v39 >>= 7;
                v40 -= 7;
              }
              if ( v51 + v59 > v66 )
                return 1;
              if ( v59 )
              {
                memset(&v72[v51], 0, 4 * v59);
                v51 += v59;
              }
              v65 = 0;
            }
          }
          else
          {
            v72[v51] = v55;
            v65 = v55;
            ++v51;
          }
          if ( v51 >= v66 )
            break;
          v47 = v64;
        }
        v49 = j;
      }
      sub_41FE40(v63);
      v64 = dword_45516C;
      dword_4F8328 = v39;
      dword_4F832C = v40;
      v61 = sub_41F960(v72, v49, 257, &unk_455074, &unk_4550B4, &v63, &v64);
      if ( !v64 )
      {
        v61 = 1;
        goto LABEL_82;
      }
      if ( v61 )
      {
        if ( v61 != 1 )
          return v61;
LABEL_82:
        printf("%s", aIncompleteLTre);
        sub_41FE40(v63);
        return v61;
      }
      v68 = dword_455170;
      v62 = sub_41F960(&v72[v49], k, 0, &unk_4550F4, &unk_455130, &v67, &v68);
      if ( v68 || v49 <= 0x101 )
      {
        if ( v62 >= 2 )
        {
          sub_41FE40(v63);
          return v62;
        }
        if ( !sub_41EE40(v63, v67, v64, v68) )
        {
          sub_41FE40(v63);
          sub_41FE40(v67);
          return 0;
        }
      }
      else
      {
        printf("%s", aIncompleteDTre);
        sub_41FE40(v63);
      }
    }
    return 1;
  }
  if ( (v7 & 3) != 0 )
  {
    if ( v10 != 1 )
      return 2;
    v72[31] = v5;
    if ( dword_4F8330 )
      return sub_41EE40(dword_4F8330, dword_4F8334, dword_4F8338, dword_4F833C) != 0;
    memset32(v73, 8, 0x90u);
    memset32(v74, 9, 0x70u);
    memset32(v75, 7, 0x18u);
    memset32(v76, 8, 8u);
    dword_4F8338 = 7;
    result = sub_41F960(v73, 288, 257, &unk_455074, &unk_4550B4, &dword_4F8330, &dword_4F8338);
    if ( result )
    {
      dword_4F8330 = 0;
      return result;
    }
    memset32(v73, 5, 0x1Eu);
    dword_4F833C = 5;
    v25 = sub_41F960(v73, 30, 0, &unk_4550F4, &unk_455130, &dword_4F8334, &dword_4F833C);
    if ( v25 <= 1 )
    {
      return sub_41EE40(dword_4F8330, dword_4F8334, dword_4F8338, dword_4F833C) != 0;
    }
    else
    {
      sub_41FE40(dword_4F8330);
      dword_4F8330 = 0;
      return v25;
    }
  }
  else
  {
    v12 = (unsigned __int8 *)dword_576980;
    v13 = dword_4F8324;
    v76[5] = v5;
    v14 = dword_4F832C & 7;
    v15 = dword_4F832C - v14;
    for ( m = (unsigned int)dword_4F8328 >> v14; v15 < 0x10; dword_576980 = (int)v12 )
    {
      v17 = *v12 << v15;
      v15 += 8;
      m |= v17;
      ++v12;
    }
    v18 = v15 - 16;
    v19 = (unsigned __int16)m;
    for ( n = HIWORD(m); v18 < 0x10; dword_576980 = (int)v12 )
    {
      v21 = *v12 << v18;
      v18 += 8;
      n |= v21;
      ++v12;
    }
    if ( v19 == (unsigned __int16)~(_WORD)n )
    {
      v22 = HIWORD(n);
      v23 = v18 - 16;
      if ( v19 )
      {
        while ( 1 )
        {
          for ( ; v23 < 8; dword_576980 = (int)v12 )
          {
            v24 = v23;
            v23 += 8;
            v22 |= *v12++ << v24;
          }
          *((_BYTE *)dword_576984 + v13++) = v22;
          if ( v13 == 0x8000 )
          {
            sub_41FE70(dword_576984, 0x8000);
            v13 = 0;
          }
          v22 >>= 8;
          v23 -= 8;
          if ( !--v19 )
            break;
          v12 = (unsigned __int8 *)dword_576980;
        }
      }
      dword_4F832C = v23;
      dword_4F8324 = v13;
      dword_4F8328 = v22;
      return 0;
    }
    else
    {
      return 1;
    }
  }
}
