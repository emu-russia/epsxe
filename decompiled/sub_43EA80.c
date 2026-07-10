#include "pch.h"
int __cdecl sub_43EA80(
        int *a1,
        unsigned int a2,
        unsigned int a3,
        int a4,
        int a5,
        _DWORD *a6,
        unsigned int *a7,
        int a8,
        unsigned int *a9,
        unsigned int *a10)
{
  int *v10; // ecx
  unsigned int v11; // edi
  unsigned int v12; // edx
  int v13; // eax
  unsigned int v15; // ecx
  _DWORD *v16; // eax
  unsigned int v17; // ebp
  signed int v18; // eax
  unsigned int v19; // edx
  int *v20; // esi
  int v21; // esi
  _DWORD *v22; // ebx
  int v23; // esi
  int v24; // ebx
  int v25; // esi
  int v26; // ecx
  unsigned int v27; // edx
  int v28; // ebx
  int *v29; // edx
  unsigned int v30; // ebx
  int v31; // ecx
  int v32; // edx
  int v33; // ebx
  unsigned int v34; // esi
  int v35; // edx
  unsigned int v36; // ecx
  unsigned int v37; // edx
  unsigned int v38; // ecx
  unsigned int v39; // eax
  _DWORD *v40; // ebp
  unsigned int v41; // eax
  unsigned int v42; // edi
  unsigned int v43; // eax
  unsigned int v44; // eax
  unsigned int v45; // edx
  int v46; // eax
  unsigned int v47; // eax
  int v48; // ecx
  char v49; // dl
  int v50; // esi
  int v51; // edx
  unsigned int v52; // eax
  _DWORD *v53; // ecx
  unsigned int i; // eax
  int v55; // edx
  _DWORD *v56; // eax
  int v57; // edx
  unsigned int v58; // [esp+10h] [ebp-100h]
  signed int v59; // [esp+14h] [ebp-FCh]
  int v60; // [esp+18h] [ebp-F8h]
  int *v61; // [esp+1Ch] [ebp-F4h]
  unsigned int *v62; // [esp+1Ch] [ebp-F4h]
  unsigned int v63; // [esp+20h] [ebp-F0h]
  char v64; // [esp+20h] [ebp-F0h]
  int v65; // [esp+24h] [ebp-ECh]
  _DWORD *v66; // [esp+28h] [ebp-E8h]
  signed int v67; // [esp+2Ch] [ebp-E4h]
  int v68; // [esp+30h] [ebp-E0h]
  unsigned int v69; // [esp+34h] [ebp-DCh]
  unsigned int v70; // [esp+38h] [ebp-D8h]
  unsigned int v71; // [esp+3Ch] [ebp-D4h]
  int v72; // [esp+40h] [ebp-D0h]
  int v73; // [esp+44h] [ebp-CCh]
  signed int v74; // [esp+48h] [ebp-C8h]
  _DWORD *v75; // [esp+4Ch] [ebp-C4h]
  unsigned int v76; // [esp+50h] [ebp-C0h]
  int v77; // [esp+54h] [ebp-BCh] BYREF
  _DWORD v78[14]; // [esp+58h] [ebp-B8h] BYREF
  int v79; // [esp+90h] [ebp-80h] BYREF
  int v80; // [esp+94h] [ebp-7Ch] BYREF
  _DWORD v81[15]; // [esp+98h] [ebp-78h]
  _DWORD v82[15]; // [esp+D4h] [ebp-3Ch] BYREF
  int v83; // [esp+118h] [ebp+8h]

  v10 = a1;
  v11 = 0;
  v12 = a2;
  v77 = 0;
  memset(v78, 0, sizeof(v78));
  v79 = 0;
  do
  {
    v13 = *v10++;
    --v12;
    ++v78[v13 - 1];
  }
  while ( v12 );
  if ( v77 == a2 )
  {
    *a6 = 0;
    *a7 = 0;
    return 0;
  }
  v15 = 1;
  v16 = v78;
  v17 = *a7;
  v58 = *a7;
  do
  {
    if ( *v16 )
      break;
    ++v15;
    ++v16;
  }
  while ( v15 <= 0xF );
  v18 = v15;
  v59 = v15;
  if ( v17 < v15 )
  {
    v58 = v15;
    v17 = v15;
  }
  v19 = 15;
  v20 = &v79;
  do
  {
    if ( *v20 )
      break;
    --v19;
    --v20;
  }
  while ( v19 );
  v67 = v19;
  if ( v17 > v19 )
  {
    v58 = v19;
    v17 = v19;
  }
  *a7 = v17;
  v21 = 1 << v15;
  if ( v15 < v19 )
  {
    v22 = &v78[v15 - 1];
    do
    {
      v23 = v21 - *v22;
      if ( v23 < 0 )
        return -3;
      ++v15;
      ++v22;
      v21 = 2 * v23;
    }
    while ( v15 < v19 );
  }
  v63 = v19;
  v24 = v78[v19 - 1];
  v25 = v21 - v24;
  v73 = v25;
  if ( v25 < 0 )
    return -3;
  v81[0] = 0;
  v78[v19 - 1] = v25 + v24;
  v26 = 0;
  v27 = v19 - 1;
  if ( v27 )
  {
    v28 = 0;
    do
    {
      v26 += v78[v28++];
      --v27;
      v81[v28] = v26;
    }
    while ( v27 );
  }
  v29 = a1;
  v30 = 0;
  do
  {
    v31 = *v29++;
    v61 = v29;
    if ( v31 )
    {
      v32 = v81[v31 - 1];
      a10[v32] = v30;
      v25 = v73;
      v81[v31 - 1] = v32 + 1;
      v29 = v61;
    }
    ++v30;
  }
  while ( v30 < a2 );
  v33 = -v17;
  v62 = a10;
  v83 = v81[v63 - 1];
  v70 = 0;
  v80 = 0;
  v60 = -1;
  v82[0] = 0;
  v72 = 0;
  v71 = 0;
  if ( v18 > v67 )
  {
LABEL_66:
    if ( !v25 || v67 == 1 )
      return 0;
    return -5;
  }
  else
  {
    v34 = v69;
    v64 = v18 - 1;
    v66 = &v78[v18 - 1];
    while ( 1 )
    {
      v35 = *v66 - 1;
      v65 = v35;
      if ( *v66 )
        break;
LABEL_64:
      ++v18;
      ++v66;
      v59 = v18;
      ++v64;
      if ( v18 > v67 )
      {
        v25 = v73;
        goto LABEL_66;
      }
    }
    while ( 1 )
    {
      v36 = v33 + v17;
      if ( v18 > (int)(v33 + v17) )
        break;
LABEL_49:
      BYTE1(v68) = v18 - v33;
      if ( v62 < &a10[v83] )
      {
        v34 = *v62;
        if ( *v62 >= a3 )
        {
          v50 = 4 * (v34 - a3);
          v49 = *(_BYTE *)(v50 + a5) + 80;
          v34 = *(_DWORD *)(v50 + a4);
        }
        else
        {
          v49 = v34 < 0x100 ? 0 : 96;
        }
        LOBYTE(v68) = v49;
        ++v62;
      }
      else
      {
        LOBYTE(v68) = -64;
      }
      v51 = 1 << (v18 - v33);
      v52 = v11 >> v33;
      if ( v11 >> v33 < v71 )
      {
        v53 = (_DWORD *)(v72 + 8 * v52);
        do
        {
          v52 += v51;
          *v53 = v68;
          v53[1] = v34;
          v53 += 2 * v51;
        }
        while ( v52 < v71 );
      }
      for ( i = 1 << v64; (i & v11) != 0; i >>= 1 )
        v11 ^= i;
      v55 = v60;
      v11 ^= i;
      v56 = &v81[v60 - 1];
      v70 = v11;
      if ( (v11 & ((1 << v33) - 1)) != *v56 )
      {
        do
        {
          --v55;
          v33 -= v58;
          --v56;
        }
        while ( (v11 & ((1 << v33) - 1)) != *v56 );
        v60 = v55;
      }
      v17 = v58;
      v57 = v65--;
      v18 = v59;
      if ( !v57 )
        goto LABEL_64;
      v35 = v65;
    }
    v76 = v35 + 1;
    while ( 1 )
    {
      v33 += v17;
      ++v60;
      v37 = v67 - v33;
      v74 = v17 + v36;
      if ( v67 - v33 > v17 )
        v37 = v17;
      v38 = v18 - v33;
      v39 = 1 << (v18 - v33);
      if ( v39 > v76 )
      {
        v40 = v66;
        v41 = -1 - v65 + v39;
        if ( v38 < v37 && ++v38 < v37 )
        {
          do
          {
            v42 = v40[1];
            ++v40;
            v43 = 2 * v41;
            if ( v43 <= v42 )
              break;
            v41 = v43 - v42;
            ++v38;
          }
          while ( v38 < v37 );
        }
      }
      v44 = *a9;
      v71 = 1 << v38;
      v45 = *a9 + (1 << v38);
      if ( v45 > 0x5A0 )
        return -4;
      *a9 = v45;
      v46 = a8 + 8 * v44;
      v72 = v46;
      v75 = &v82[v60];
      *v75 = v46;
      v11 = v70;
      if ( v60 )
      {
        LOBYTE(v68) = v38;
        v81[v60 - 1] = v70;
        BYTE1(v68) = v58;
        v47 = v70 >> (v33 - v58);
        v48 = *(v75 - 1);
        v34 = ((v72 - v48) >> 3) - v47;
        *(_DWORD *)(v48 + 8 * v47) = v68;
        *(_DWORD *)(v48 + 8 * v47 + 4) = v34;
      }
      else
      {
        *a6 = v46;
      }
      v36 = v74;
      LOBYTE(v18) = v59;
      if ( v59 <= v74 )
        goto LABEL_49;
      v17 = v58;
      v18 = v59;
    }
  }
}
