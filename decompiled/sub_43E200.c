#include "pch.h"
int __cdecl sub_43E200(_DWORD *a1, _DWORD *a2, int a3)
{
  _DWORD *v5; // eax
  unsigned __int8 *v6; // ebp
  unsigned int v7; // ebx
  unsigned int v8; // ecx
  _BYTE *v9; // edx
  int v10; // ecx
  unsigned __int8 *v11; // ebx
  int v12; // ecx
  int v13; // eax
  unsigned int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  unsigned int v17; // eax
  char v18; // cl
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  unsigned int v23; // eax
  char v24; // cl
  int v25; // ecx
  int v26; // ecx
  unsigned int v27; // eax
  char v28; // cl
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  unsigned int v32; // eax
  char v33; // cl
  int v34; // ecx
  unsigned int v35; // eax
  unsigned int v36; // eax
  unsigned int v37; // ecx
  int v38; // eax
  int v39; // eax
  unsigned int v40; // eax
  int v41; // ecx
  unsigned int v42; // ecx
  int v43; // eax
  int v44; // ecx
  unsigned int v45; // eax
  unsigned int v46; // ecx
  int v47; // eax
  int v48; // eax
  unsigned int v49; // eax
  int v50; // ecx
  unsigned int v51; // ecx
  int v52; // eax
  int v53; // eax
  unsigned __int8 *v54; // ecx
  unsigned __int8 *v56; // ebx
  unsigned __int8 *v57; // ebx
  int v58; // ecx
  int v59; // eax
  unsigned __int8 *v60; // ebx
  unsigned __int8 *v61; // ebx
  unsigned __int8 *v62; // ebx
  _DWORD *v63; // [esp+10h] [ebp-10h]
  unsigned int v64; // [esp+14h] [ebp-Ch]
  unsigned int v65; // [esp+18h] [ebp-8h]
  unsigned __int8 *v66; // [esp+18h] [ebp-8h]
  unsigned int v67; // [esp+18h] [ebp-8h]
  unsigned int v68; // [esp+18h] [ebp-8h]
  unsigned int v69; // [esp+18h] [ebp-8h]
  _BYTE *v70; // [esp+1Ch] [ebp-4h]
  unsigned int v71; // [esp+24h] [ebp+4h]
  unsigned int v72; // [esp+28h] [ebp+8h]
  int v73; // [esp+2Ch] [ebp+Ch]

  v5 = (_DWORD *)a1[1];
  v6 = (unsigned __int8 *)*a2;
  v7 = a1[7];
  v72 = a2[1];
  v8 = a1[12];
  v71 = a1[8];
  v9 = (_BYTE *)a1[13];
  v63 = v5;
  if ( (unsigned int)v9 >= v8 )
    v10 = a1[11] - (_DWORD)v9;
  else
    v10 = v8 - (_DWORD)v9 - 1;
  v64 = v10;
  while ( 2 )
  {
    switch ( *v5 )
    {
      case 0:
        if ( v64 >= 0x102 && v72 >= 0xA )
        {
          a1[8] = v71;
          a1[7] = v7;
          v11 = (unsigned __int8 *)*a2;
          a2[1] = v72;
          v12 = a2[2];
          *a2 = v6;
          a2[2] = v6 - v11 + v12;
          a1[13] = v9;
          v13 = sub_43F250(*((unsigned __int8 *)v63 + 16), *((unsigned __int8 *)v63 + 17), v63[5], v63[6], a1, a2);
          v6 = (unsigned __int8 *)*a2;
          v7 = a1[7];
          v72 = a2[1];
          v14 = a1[12];
          v71 = a1[8];
          v9 = (_BYTE *)a1[13];
          a3 = v13;
          v15 = (unsigned int)v9 >= v14 ? a1[11] - (_DWORD)v9 : v14 - (_DWORD)v9 - 1;
          v64 = v15;
          if ( v13 )
          {
            *v63 = v13 != 1 ? 9 : 7;
            v5 = v63;
            continue;
          }
        }
        v5 = v63;
        v16 = *((unsigned __int8 *)v63 + 16);
        *v63 = 1;
        v63[3] = v16;
        v63[2] = v63[5];
        goto LABEL_14;
      case 1:
LABEL_14:
        v17 = v5[3];
        v65 = v17;
        if ( v7 >= v17 )
          goto LABEL_17;
        do
        {
          if ( !v72 )
            goto LABEL_86;
          v18 = v7;
          --v72;
          v7 += 8;
          a3 = 0;
          v19 = (*v6 << v18) | v71;
          v17 = v65;
          ++v6;
          v71 = v19;
        }
        while ( v7 < v65 );
LABEL_17:
        v66 = (unsigned __int8 *)(v63[2] + 8 * (v71 & dword_458938[v17]));
        v20 = v66[1];
        v71 >>= v20;
        v7 -= v20;
        v21 = *v66;
        if ( *v66 )
        {
          if ( (v21 & 0x10) != 0 )
          {
            v5 = v63;
            v63[2] = v21 & 0xF;
            v22 = *((_DWORD *)v66 + 1);
            *v63 = 2;
            v63[1] = v22;
          }
          else
          {
            if ( (v21 & 0x40) == 0 )
              goto LABEL_22;
            v5 = v63;
            if ( (v21 & 0x20) == 0 )
            {
              *v63 = 9;
              a2[6] = aInvalidLiteral;
LABEL_88:
              a1[8] = v71;
              a1[7] = v7;
              v56 = (unsigned __int8 *)*a2;
              a2[1] = v72;
              a2[2] += v6 - v56;
              *a2 = v6;
              a1[13] = v9;
              return sub_43F110(a1, a2, -3);
            }
            *v63 = 7;
          }
        }
        else
        {
          v5 = v63;
          v63[2] = *((_DWORD *)v66 + 1);
          *v63 = 6;
        }
        continue;
      case 2:
        v23 = v5[2];
        v67 = v23;
        if ( v7 >= v23 )
          goto LABEL_28;
        do
        {
          if ( !v72 )
            goto LABEL_86;
          v24 = v7;
          --v72;
          v7 += 8;
          a3 = 0;
          v25 = (*v6 << v24) | v71;
          v23 = v67;
          ++v6;
          v71 = v25;
        }
        while ( v7 < v67 );
LABEL_28:
        v63[1] += v71 & dword_458938[v23];
        v71 >>= v67;
        v7 -= v67;
        v5 = v63;
        v26 = *((unsigned __int8 *)v63 + 17);
        *v63 = 3;
        v63[3] = v26;
        v63[2] = v63[6];
LABEL_29:
        v27 = v5[3];
        v68 = v27;
        if ( v7 < v27 )
        {
          while ( v72 )
          {
            v28 = v7;
            --v72;
            v7 += 8;
            a3 = 0;
            v29 = (*v6 << v28) | v71;
            v27 = v68;
            ++v6;
            v71 = v29;
            if ( v7 >= v68 )
              goto LABEL_32;
          }
LABEL_86:
          a1[7] = v7;
          a1[8] = v71;
          v53 = a2[2];
          v54 = &v6[-*a2];
          a2[1] = 0;
          *a2 = v6;
          a2[2] = &v54[v53];
          a1[13] = v9;
          return sub_43F110(a1, a2, a3);
        }
LABEL_32:
        v66 = (unsigned __int8 *)(v63[2] + 8 * (v71 & dword_458938[v27]));
        v30 = v66[1];
        v7 -= v30;
        v71 >>= v30;
        v21 = *v66;
        if ( (v21 & 0x10) != 0 )
        {
          v5 = v63;
          v63[2] = v21 & 0xF;
          v31 = *((_DWORD *)v66 + 1);
          *v63 = 4;
          v63[3] = v31;
        }
        else
        {
          if ( (v21 & 0x40) != 0 )
          {
            *v63 = 9;
            a2[6] = aInvalidDistanc;
            goto LABEL_88;
          }
LABEL_22:
          v63[3] = v21;
          v5 = v63;
          v63[2] = &v66[8 * *((_DWORD *)v66 + 1)];
        }
        continue;
      case 3:
        goto LABEL_29;
      case 4:
        v32 = v5[2];
        v69 = v32;
        if ( v7 >= v32 )
          goto LABEL_39;
        do
        {
          if ( !v72 )
            goto LABEL_86;
          v33 = v7;
          --v72;
          v7 += 8;
          a3 = 0;
          v34 = (*v6 << v33) | v71;
          v32 = v69;
          ++v6;
          v71 = v34;
        }
        while ( v7 < v69 );
LABEL_39:
        v63[3] += v71 & dword_458938[v32];
        v71 >>= v69;
        v7 -= v69;
        *v63 = 5;
LABEL_40:
        v35 = v63[3];
        if ( (unsigned int)&v9[-a1[10]] >= v35 )
          v70 = &v9[-v35];
        else
          v70 = &v9[a1[11] - a1[10] - v63[3]];
        v5 = v63;
        if ( !v63[1] )
        {
LABEL_65:
          *v5 = 0;
          continue;
        }
        while ( v64 )
        {
LABEL_62:
          ++v9;
          a3 = 0;
          *(v9 - 1) = *v70++;
          --v64;
          if ( v70 == (_BYTE *)a1[11] )
            v70 = (_BYTE *)a1[10];
          v44 = v5[1] - 1;
          v5[1] = v44;
          if ( !v44 )
            goto LABEL_65;
        }
        if ( v9 == (_BYTE *)a1[11] )
        {
          v36 = a1[12];
          v37 = a1[10];
          if ( v36 != v37 )
          {
            v9 = (_BYTE *)a1[10];
            v38 = v37 >= v36 ? a1[11] - v37 : v36 - v37 - 1;
            v64 = v38;
            if ( v38 )
              goto LABEL_61;
          }
        }
        a1[13] = v9;
        v39 = sub_43F110(a1, a2, a3);
        v9 = (_BYTE *)a1[13];
        v73 = v39;
        v40 = a1[12];
        if ( (unsigned int)v9 >= v40 )
          v41 = a1[11] - (_DWORD)v9;
        else
          v41 = v40 - (_DWORD)v9 - 1;
        v64 = v41;
        if ( v9 == (_BYTE *)a1[11] )
        {
          v42 = a1[10];
          if ( v40 != v42 )
          {
            v9 = (_BYTE *)a1[10];
            if ( v42 >= v40 )
              v43 = a1[11] - v42;
            else
              v43 = v40 - v42 - 1;
            v64 = v43;
          }
        }
        if ( v64 )
        {
LABEL_61:
          v5 = v63;
          goto LABEL_62;
        }
LABEL_89:
        a1[8] = v71;
        a1[7] = v7;
        v57 = (unsigned __int8 *)*a2;
        a2[1] = v72;
        v58 = a2[2];
        *a2 = v6;
        a2[2] = v6 - v57 + v58;
        a1[13] = v9;
        return sub_43F110(a1, a2, v73);
      case 5:
        goto LABEL_40;
      case 6:
        if ( v64 )
          goto LABEL_84;
        if ( v9 != (_BYTE *)a1[11]
          || (v45 = a1[12], v46 = a1[10], v45 == v46)
          || ((v9 = (_BYTE *)a1[10], v46 >= v45) ? (v47 = a1[11] - v46) : (v47 = v45 - v46 - 1), (v64 = v47) == 0) )
        {
          a1[13] = v9;
          v48 = sub_43F110(a1, a2, a3);
          v9 = (_BYTE *)a1[13];
          v73 = v48;
          v49 = a1[12];
          if ( (unsigned int)v9 >= v49 )
            v50 = a1[11] - (_DWORD)v9;
          else
            v50 = v49 - (_DWORD)v9 - 1;
          v64 = v50;
          if ( v9 == (_BYTE *)a1[11] )
          {
            v51 = a1[10];
            if ( v49 != v51 )
            {
              v9 = (_BYTE *)a1[10];
              if ( v51 >= v49 )
                v52 = a1[11] - v51;
              else
                v52 = v49 - v51 - 1;
              v64 = v52;
            }
          }
          if ( !v64 )
            goto LABEL_89;
        }
        v5 = v63;
LABEL_84:
        a3 = 0;
        *v9++ = *((_BYTE *)v5 + 8);
        --v64;
        *v5 = 0;
        continue;
      case 7:
        if ( v7 > 7 )
        {
          v7 -= 8;
          --v6;
          ++v72;
        }
        a1[13] = v9;
        v59 = sub_43F110(a1, a2, a3);
        v9 = (_BYTE *)a1[13];
        if ( (_BYTE *)a1[12] == v9 )
        {
          *v63 = 8;
LABEL_95:
          a1[8] = v71;
          a1[7] = v7;
          v61 = (unsigned __int8 *)*a2;
          a2[1] = v72;
          a2[2] += v6 - v61;
          *a2 = v6;
          a1[13] = v9;
          return sub_43F110(a1, a2, 1);
        }
        else
        {
          a1[7] = v7;
          a1[8] = v71;
          v60 = (unsigned __int8 *)*a2;
          a2[1] = v72;
          a2[2] += v6 - v60;
          *a2 = v6;
          a1[13] = v9;
          return sub_43F110(a1, a2, v59);
        }
      case 8:
        goto LABEL_95;
      case 9:
        goto LABEL_88;
      default:
        a1[8] = v71;
        a1[7] = v7;
        v62 = (unsigned __int8 *)*a2;
        a2[1] = v72;
        a2[2] += v6 - v62;
        *a2 = v6;
        a1[13] = v9;
        return sub_43F110(a1, a2, -2);
    }
  }
}
