#include "pch.h"
int __cdecl sub_43B6C0(_DWORD *a1, unsigned __int8 **a2, int a3)
{
  unsigned int v4; // ebp
  char *v5; // ecx
  unsigned int v6; // eax
  int v7; // eax
  unsigned int v8; // esi
  unsigned __int8 *v9; // eax
  unsigned __int8 *v10; // edi
  int v11; // edx
  unsigned int v12; // ebp
  int v13; // ecx
  int v14; // eax
  unsigned int v15; // esi
  unsigned __int8 *v16; // edi
  unsigned __int8 *v17; // eax
  int v18; // edx
  unsigned int v19; // edi
  unsigned int v20; // ecx
  char *v21; // ecx
  char *v22; // edx
  unsigned int v23; // eax
  unsigned int v24; // esi
  int v25; // eax
  char *v26; // edx
  unsigned int v27; // esi
  unsigned int v28; // eax
  unsigned int v29; // eax
  unsigned int v30; // eax
  unsigned int v31; // ecx
  unsigned int v32; // edi
  unsigned __int8 *v33; // esi
  unsigned __int8 *v34; // eax
  int v35; // edx
  unsigned int v36; // eax
  unsigned int v37; // ecx
  int v38; // esi
  int v39; // eax
  unsigned int v40; // edi
  unsigned __int8 *v41; // eax
  char v42; // cl
  int v43; // eax
  unsigned int v44; // edx
  unsigned int v45; // ecx
  unsigned int v46; // eax
  int v47; // edx
  int v48; // ecx
  int v49; // eax
  int v50; // edx
  unsigned int v51; // eax
  int v52; // eax
  int v53; // ecx
  int v54; // eax
  int v55; // eax
  int v56; // edx
  unsigned int v57; // edi
  int v58; // eax
  int v59; // ecx
  unsigned int v60; // eax
  int v61; // eax
  unsigned __int8 *v62; // edi
  int v63; // edx
  int v64; // eax
  char *v65; // ecx
  unsigned __int8 *v66; // edi
  unsigned int v67; // eax
  int v68; // eax
  int v69; // ebp
  int result; // eax
  unsigned __int8 *v71; // ebp
  unsigned __int8 *v72; // ebp
  unsigned __int8 *v73; // esi
  unsigned __int8 *v74; // ebp
  int v75; // ebp
  unsigned __int8 *v76; // ebp
  unsigned __int8 *v77; // edx
  unsigned __int8 *v78; // ebp
  unsigned __int8 *v79; // esi
  unsigned __int8 *v80; // esi
  unsigned __int8 *v81; // ebp
  unsigned __int8 *v82; // edi
  unsigned __int8 *v83; // edx
  unsigned __int8 *v84; // esi
  unsigned __int8 *v85; // ebp
  int v86; // ecx
  unsigned __int8 *v87; // edx
  bool v88; // zf
  unsigned __int8 *v89; // edi
  int v90; // ecx
  unsigned __int8 *v91; // edi
  int v92; // ecx
  unsigned __int8 *v93; // edi
  char *v94; // ecx
  unsigned __int8 *v95; // ebp
  unsigned __int8 *v96; // ebp
  unsigned __int8 *v97; // esi
  unsigned __int8 *v98; // ebp
  unsigned __int8 *v99; // esi
  unsigned __int8 *v100; // ebp
  int v101; // [esp-1Ch] [ebp-5Ch]
  int v102; // [esp-14h] [ebp-54h]
  int v103; // [esp-8h] [ebp-48h]
  int v104; // [esp-8h] [ebp-48h]
  unsigned __int8 *v105; // [esp+10h] [ebp-30h]
  unsigned __int8 *v106; // [esp+14h] [ebp-2Ch]
  unsigned int v107; // [esp+18h] [ebp-28h]
  int v108; // [esp+18h] [ebp-28h]
  int v109; // [esp+18h] [ebp-28h]
  int v110; // [esp+18h] [ebp-28h]
  int v111; // [esp+1Ch] [ebp-24h] BYREF
  unsigned int v112; // [esp+20h] [ebp-20h] BYREF
  int v113; // [esp+24h] [ebp-1Ch] BYREF
  int v114; // [esp+28h] [ebp-18h] BYREF
  int v115; // [esp+2Ch] [ebp-14h] BYREF
  int v116; // [esp+30h] [ebp-10h] BYREF
  unsigned int v117; // [esp+34h] [ebp-Ch]
  int v118; // [esp+38h] [ebp-8h] BYREF
  int v119; // [esp+3Ch] [ebp-4h] BYREF
  char *v120; // [esp+44h] [ebp+4h]
  int v121; // [esp+4Ch] [ebp+Ch]

  v4 = a1[7];
  v105 = *a2;
  v5 = (char *)a1[13];
  v107 = a1[8];
  v6 = a1[12];
  v106 = a2[1];
  v120 = v5;
  if ( (unsigned int)v5 >= v6 )
    v7 = a1[11] - (_DWORD)v5;
  else
    v7 = v6 - (_DWORD)v5 - 1;
  v111 = v7;
  while ( 2 )
  {
    switch ( *a1 )
    {
      case 0:
        v8 = v107;
        if ( v4 >= 3 )
        {
          v10 = v105;
LABEL_12:
          a1[6] = v8 & 1;
          switch ( (unsigned __int8)(v8 & 7) >> 1 )
          {
            case 0:
              v12 = v4 - 3;
              *a1 = 1;
              v13 = v12 & 7;
              v4 = v12 - v13;
              v107 = v8 >> 3 >> v13;
              continue;
            case 1:
              sub_43F0E0(&v116, &v115, &v114, &v113);
              v14 = sub_43E1C0(v116, v115, v114, v113, a2);
              a1[1] = v14;
              if ( v14 )
              {
                v107 = v8 >> 3;
                v4 -= 3;
                *a1 = 6;
                continue;
              }
              a1[8] = v8;
              a1[7] = v4;
              v71 = a2[2];
              a2[1] = v106;
              a2[2] = &v71[v10 - *a2];
              *a2 = v10;
              a1[13] = v120;
              result = sub_43F110(a1, a2, -4);
              break;
            case 2:
              v107 = v8 >> 3;
              v4 -= 3;
              *a1 = 3;
              continue;
            case 3:
              *a1 = 9;
              a2[6] = (unsigned __int8 *)aInvalidBlockTy;
              a1[8] = v8 >> 3;
              a1[7] = v4 - 3;
              v72 = a2[2];
              a2[1] = v106;
              a2[2] = &v72[v10 - *a2];
              *a2 = v10;
              a1[13] = v120;
              return sub_43F110(a1, a2, -3);
            default:
              continue;
          }
        }
        else
        {
          v9 = v106;
          v10 = v105;
          while ( v9 )
          {
            --v9;
            a3 = 0;
            v11 = *v10 << v4;
            v4 += 8;
            v106 = v9;
            v8 |= v11;
            ++v10;
            v107 = v8;
            v105 = v10;
            if ( v4 >= 3 )
              goto LABEL_12;
          }
          a1[8] = v8;
          a1[7] = v4;
          v69 = (int)&a2[2][v10 - *a2];
          a2[1] = nullptr;
          a2[2] = (unsigned __int8 *)v69;
          *a2 = v10;
          a1[13] = v120;
          return sub_43F110(a1, a2, a3);
        }
        return result;
      case 1:
        v15 = v107;
        v16 = v106;
        v17 = v105;
        if ( v4 >= 0x20 )
          goto LABEL_20;
        do
        {
          if ( !v16 )
          {
            a1[8] = v15;
            a1[7] = v4;
            v73 = *a2;
            v74 = a2[2];
            a2[1] = nullptr;
            *a2 = v17;
            a2[2] = &v74[v17 - v73];
            a1[13] = v120;
            return sub_43F110(a1, a2, a3);
          }
          a3 = 0;
          --v16;
          v18 = *v17 << v4;
          v4 += 8;
          v106 = v16;
          v15 |= v18;
          v105 = ++v17;
        }
        while ( v4 < 0x20 );
LABEL_20:
        if ( (unsigned __int16)v15 != ~v15 >> 16 )
        {
          *a1 = 9;
          a2[6] = (unsigned __int8 *)aInvalidStoredB;
          a1[8] = v15;
          a1[7] = v4;
          v75 = (int)&a2[2][v17 - *a2];
          *a2 = v17;
          a2[1] = v16;
          a2[2] = (unsigned __int8 *)v75;
          a1[13] = v120;
          return sub_43F110(a1, a2, -3);
        }
        v4 = 0;
        a1[1] = (unsigned __int16)v15;
        v107 = 0;
        if ( (_WORD)v15 )
        {
          *a1 = 2;
          continue;
        }
LABEL_47:
        *a1 = a1[6] != 0 ? 7 : 0;
        continue;
      case 2:
        v19 = (unsigned int)v106;
        if ( !v106 )
        {
          a1[8] = v107;
          a1[7] = v4;
          v76 = a2[2];
          v77 = (unsigned __int8 *)(v105 - *a2);
          *a2 = v105;
          a2[1] = nullptr;
          a2[2] = &v76[(_DWORD)v77];
          a1[13] = v120;
          return sub_43F110(a1, a2, a3);
        }
        v20 = v111;
        if ( v111 )
          goto LABEL_42;
        v21 = (char *)a1[11];
        v22 = v120;
        if ( v120 == v21 )
        {
          v23 = a1[12];
          v24 = a1[10];
          if ( v23 != v24 )
          {
            v22 = (char *)a1[10];
            v120 = v22;
            v20 = v24 >= v23 ? (unsigned int)&v21[-v24] : v23 - v24 - 1;
            v111 = v20;
            if ( v20 )
              goto LABEL_42;
          }
        }
        a1[13] = v22;
        v25 = sub_43F110(a1, a2, a3);
        v26 = (char *)a1[13];
        v27 = a1[12];
        v121 = v25;
        v120 = v26;
        if ( (unsigned int)v26 >= v27 )
          v20 = a1[11] - (_DWORD)v26;
        else
          v20 = v27 - (_DWORD)v26 - 1;
        v28 = a1[11];
        v111 = v20;
        v112 = v28;
        if ( v26 == (char *)v28 )
        {
          v29 = a1[10];
          if ( v27 != v29 )
          {
            v26 = (char *)a1[10];
            v120 = v26;
            if ( v29 >= v27 )
              v20 = v112 - v29;
            else
              v20 = v27 - v29 - 1;
            v111 = v20;
          }
        }
        if ( !v20 )
        {
          a1[8] = v107;
          a1[7] = v4;
          v78 = *a2;
          v79 = a2[2];
          a2[1] = v106;
          *a2 = v105;
          a2[2] = &v79[v105 - v78];
          a1[13] = v26;
          return sub_43F110(a1, a2, v121);
        }
        v19 = (unsigned int)v106;
LABEL_42:
        v30 = a1[1];
        a3 = 0;
        if ( v30 > v19 )
          v30 = v19;
        if ( v30 > v20 )
          v30 = v20;
        qmemcpy(v120, v105, v30);
        v105 += v30;
        v31 = a1[1] - v30;
        v106 -= v30;
        v120 += v30;
        v111 -= v30;
        a1[1] = v31;
        if ( !v31 )
          goto LABEL_47;
        continue;
      case 3:
        v32 = v107;
        if ( v4 >= 0xE )
          goto LABEL_52;
        v33 = v106;
        v34 = v105;
        do
        {
          if ( !v33 )
          {
            a1[8] = v32;
            a1[7] = v4;
            v80 = *a2;
            v81 = a2[2];
            *a2 = v105;
            a2[1] = nullptr;
            a2[2] = &v81[v105 - v80];
            a1[13] = v120;
            return sub_43F110(a1, a2, a3);
          }
          --v33;
          a3 = 0;
          v35 = *v34 << v4;
          v4 += 8;
          v106 = v33;
          v32 |= v35;
          v105 = ++v34;
        }
        while ( v4 < 0xE );
LABEL_52:
        v36 = v32 & 0x3FFF;
        a1[1] = v36;
        v37 = v32 & 0x1F;
        if ( v37 > 0x1D || (v32 & 0x3E0) > 0x3A0 )
        {
          *a1 = 9;
          a2[6] = (unsigned __int8 *)aTooManyLengthO;
          a1[8] = v32;
          a1[7] = v4;
          v84 = *a2;
          v85 = a2[2];
          a2[1] = v106;
          *a2 = v105;
          a2[2] = &v85[v105 - v84];
          a1[13] = v120;
          return sub_43F110(a1, a2, -3);
        }
        v38 = (int)a2;
        v39 = ((int (__cdecl *)(unsigned __int8 *, unsigned int, int))a2[8])(a2[10], ((v36 >> 5) & 0x1F) + v37 + 258, 4);
        a1[3] = v39;
        if ( !v39 )
        {
          a1[8] = v32;
          a1[7] = v4;
          v82 = *a2;
          v83 = a2[2];
          a2[1] = v106;
          *a2 = v105;
          a2[2] = &v83[v105 - v82];
          a1[13] = v120;
          return sub_43F110(a1, a2, -4);
        }
        v40 = v32 >> 14;
        v4 -= 14;
        a1[2] = 0;
        *a1 = 4;
LABEL_57:
        if ( a1[2] < (unsigned int)((a1[1] >> 10) + 4) )
        {
          while ( v4 >= 3 )
          {
LABEL_62:
            v43 = v40 & 7;
            v4 -= 3;
            v40 >>= 3;
            *(_DWORD *)(a1[3] + 4 * dword_448C28[a1[2]]) = v43;
            v44 = a1[2] + 1;
            a1[2] = v44;
            if ( v44 >= (a1[1] >> 10) + 4 )
              goto LABEL_63;
          }
          v41 = v105;
          while ( v106 )
          {
            --v106;
            v42 = v4;
            v4 += 8;
            a3 = 0;
            v40 |= *v41++ << v42;
            v105 = v41;
            if ( v4 >= 3 )
              goto LABEL_62;
          }
          goto LABEL_107;
        }
LABEL_63:
        if ( a1[2] < 0x13u )
        {
          do
          {
            *(_DWORD *)(a1[3] + 4 * dword_448C28[a1[2]]) = 0;
            v45 = a1[2] + 1;
            a1[2] = v45;
          }
          while ( v45 < 0x13 );
        }
        v103 = a1[9];
        v102 = a1[3];
        a1[4] = 7;
        v108 = sub_43E9D0(v102, a1 + 4, (int)(a1 + 5), v103, v38);
        if ( v108 )
        {
          (*(void (__cdecl **)(_DWORD, _DWORD))(v38 + 36))(*(_DWORD *)(v38 + 40), a1[3]);
          v88 = v108 == -3;
LABEL_112:
          if ( v88 )
            *a1 = 9;
          a1[8] = v40;
          a1[7] = v4;
          v91 = *(unsigned __int8 **)v38;
          *(_DWORD *)(v38 + 4) = v106;
          v92 = *(_DWORD *)(v38 + 8);
          *(_DWORD *)v38 = v105;
          *(_DWORD *)(v38 + 8) = v105 - v91 + v92;
          a1[13] = v120;
          return sub_43F110(a1, v38, v108);
        }
        a1[2] = 0;
        *a1 = 5;
LABEL_68:
        if ( a1[2] < ((a1[1] >> 5) & 0x1F) + (a1[1] & 0x1Fu) + 258 )
        {
          while ( 1 )
          {
            v46 = a1[4];
            if ( v4 < v46 )
              break;
LABEL_72:
            v48 = a1[5];
            v49 = v40 & dword_458938[v46];
            v50 = *(unsigned __int8 *)(v48 + 8 * v49 + 1);
            v109 = v50;
            v51 = *(_DWORD *)(v48 + 8 * v49 + 4);
            v117 = v51;
            if ( v51 >= 0x10 )
            {
              v53 = 7;
              if ( v51 != 18 )
                v53 = v51 - 14;
              v111 = v53;
              v54 = -(v51 != 18);
              LOBYTE(v54) = v54 & 0xF8;
              v112 = v50 + v53;
              v55 = v54 + 11;
              if ( v4 < v50 + v53 )
              {
                while ( v106 )
                {
                  a3 = 0;
                  --v106;
                  v56 = *v105 << v4;
                  v4 += 8;
                  v40 |= v56;
                  ++v105;
                  if ( v4 >= v112 )
                  {
                    v50 = v109;
                    goto LABEL_80;
                  }
                }
                goto LABEL_107;
              }
LABEL_80:
              v57 = v40 >> v50;
              v58 = (v57 & dword_458938[v111]) + v55;
              v40 = v57 >> v111;
              v110 = v58;
              v4 -= v50 + v111;
              v111 = a1[2];
              if ( v111 + v58 > ((a1[1] >> 5) & 0x1F) + (a1[1] & 0x1Fu) + 258 )
                goto LABEL_110;
              if ( v117 == 16 )
              {
                v52 = v111;
                if ( !v111 )
                {
LABEL_110:
                  (*(void (__cdecl **)(_DWORD, _DWORD))(v38 + 36))(*(_DWORD *)(v38 + 40), a1[3]);
                  *a1 = 9;
                  *(_DWORD *)(v38 + 24) = aInvalidBitLeng;
                  a1[8] = v40;
                  a1[7] = v4;
                  v89 = *(unsigned __int8 **)v38;
                  *(_DWORD *)(v38 + 4) = v106;
                  v90 = *(_DWORD *)(v38 + 8);
                  *(_DWORD *)v38 = v105;
                  *(_DWORD *)(v38 + 8) = v105 - v89 + v90;
                  a1[13] = v120;
                  return sub_43F110(a1, v38, -3);
                }
                v59 = *(_DWORD *)(a1[3] + 4 * v111 - 4);
              }
              else
              {
                v52 = v111;
                v59 = 0;
              }
              do
              {
                ++v52;
                *(_DWORD *)(a1[3] + 4 * v52 - 4) = v59;
                --v110;
              }
              while ( v110 );
            }
            else
            {
              v4 -= v50;
              v40 >>= v50;
              *(_DWORD *)(a1[3] + 4 * a1[2]) = v51;
              v52 = a1[2] + 1;
            }
            a1[2] = v52;
            if ( a1[2] >= ((a1[1] >> 5) & 0x1F) + (a1[1] & 0x1Fu) + 258 )
              goto LABEL_87;
          }
          while ( v106 )
          {
            a3 = 0;
            --v106;
            v47 = *v105 << v4;
            v4 += 8;
            v40 |= v47;
            ++v105;
            if ( v4 >= v46 )
              goto LABEL_72;
          }
LABEL_107:
          a1[8] = v40;
          a1[7] = v4;
          v86 = *(_DWORD *)(v38 + 8);
          v87 = &v105[-*(_DWORD *)v38];
          *(_DWORD *)v38 = v105;
          *(_DWORD *)(v38 + 8) = &v87[v86];
          *(_DWORD *)(v38 + 4) = 0;
          a1[13] = v120;
          return sub_43F110(a1, v38, a3);
        }
LABEL_87:
        v60 = a1[1];
        v104 = a1[9];
        v101 = a1[3];
        a1[5] = 0;
        v112 = 9;
        v111 = 6;
        v108 = sub_43EF50((v60 & 0x1F) + 257, ((v60 >> 5) & 0x1F) + 1, v101, &v112, &v111, &v119, &v118, v104, v38);
        (*(void (__cdecl **)(_DWORD, _DWORD))(v38 + 36))(*(_DWORD *)(v38 + 40), a1[3]);
        if ( v108 )
        {
          v88 = v108 == -3;
          goto LABEL_112;
        }
        v61 = sub_43E1C0(v112, v111, v119, v118, v38);
        if ( !v61 )
        {
          a1[8] = v40;
          a1[7] = v4;
          v93 = *(unsigned __int8 **)v38;
          *(_DWORD *)(v38 + 4) = v106;
          *(_DWORD *)(v38 + 8) += v105 - v93;
          *(_DWORD *)v38 = v105;
          a1[13] = v120;
          return sub_43F110(a1, v38, -4);
        }
        a1[1] = v61;
        *a1 = 6;
LABEL_91:
        a1[8] = v40;
        a1[7] = v4;
        v62 = *(unsigned __int8 **)v38;
        *(_DWORD *)(v38 + 4) = v106;
        v63 = *(_DWORD *)(v38 + 8);
        *(_DWORD *)v38 = v105;
        *(_DWORD *)(v38 + 8) = v105 - v62 + v63;
        a1[13] = v120;
        v64 = sub_43E200(a1, v38, a3);
        if ( v64 != 1 )
          return sub_43F110(a1, v38, v64);
        a3 = 0;
        sub_43E9B0(a1[1], v38);
        v65 = (char *)a1[13];
        v66 = *(unsigned __int8 **)v38;
        v4 = a1[7];
        v107 = a1[8];
        v67 = a1[12];
        v105 = *(unsigned __int8 **)v38;
        v106 = *(unsigned __int8 **)(v38 + 4);
        v120 = v65;
        if ( (unsigned int)v65 >= v67 )
          v68 = a1[11] - (_DWORD)v65;
        else
          v68 = v67 - (_DWORD)v65 - 1;
        v111 = v68;
        if ( !a1[6] )
        {
          *a1 = 0;
          continue;
        }
        *a1 = 7;
LABEL_118:
        a1[13] = v65;
        v64 = sub_43F110(a1, v38, a3);
        v94 = (char *)a1[13];
        if ( (char *)a1[12] != v94 )
        {
          a1[7] = v4;
          a1[8] = v107;
          v95 = *(unsigned __int8 **)v38;
          *(_DWORD *)(v38 + 4) = v106;
          *(_DWORD *)v38 = v66;
          *(_DWORD *)(v38 + 8) += v66 - v95;
          a1[13] = v94;
          return sub_43F110(a1, v38, v64);
        }
        *a1 = 8;
LABEL_123:
        a1[8] = v107;
        a1[7] = v4;
        v96 = *(unsigned __int8 **)v38;
        *(_DWORD *)(v38 + 4) = v106;
        *(_DWORD *)(v38 + 8) += v66 - v96;
        *(_DWORD *)v38 = v66;
        a1[13] = v94;
        return sub_43F110(a1, v38, 1);
      case 4:
        v40 = v107;
        v38 = (int)a2;
        goto LABEL_57;
      case 5:
        v40 = v107;
        v38 = (int)a2;
        goto LABEL_68;
      case 6:
        v40 = v107;
        v38 = (int)a2;
        goto LABEL_91;
      case 7:
        v65 = v120;
        v66 = v105;
        v38 = (int)a2;
        goto LABEL_118;
      case 8:
        v94 = v120;
        v66 = v105;
        v38 = (int)a2;
        goto LABEL_123;
      case 9:
        a1[8] = v107;
        a1[7] = v4;
        v97 = *a2;
        v98 = a2[2];
        a2[1] = v106;
        *a2 = v105;
        a2[2] = &v98[v105 - v97];
        a1[13] = v120;
        return sub_43F110(a1, a2, -3);
      default:
        a1[8] = v107;
        a1[7] = v4;
        v99 = *a2;
        v100 = a2[2];
        a2[1] = v106;
        *a2 = v105;
        a2[2] = &v100[v105 - v99];
        a1[13] = v120;
        return sub_43F110(a1, a2, -2);
    }
  }
}
