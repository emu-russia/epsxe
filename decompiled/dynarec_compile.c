#include "pch.h"
int __cdecl dynarec_compile(unsigned int ArgList, unsigned int a2)
{
  char *v2; // ebx
  unsigned int v3; // esi
  unsigned int v4; // eax
  unsigned int v6; // eax
  unsigned int v7; // esi
  unsigned __int8 v8; // dl
  int v9; // ecx
  unsigned __int8 v10; // cl
  _DWORD *v11; // eax
  int v12; // ecx
  char v13; // al
  char v14; // cl
  char v15; // dl
  char v16; // dl
  char v17; // dl
  char v18; // al
  char v19; // cl
  char v20; // dl
  char v21; // cl
  char v22; // dl
  char v23; // cl
  char v24; // dl
  int result; // eax
  char v26; // cl
  char v27; // al
  _BYTE *v28; // edx
  int v29; // eax
  int v30; // eax
  char v31; // al
  char v32; // dl
  char v33; // dl
  char v34; // dl
  char v35; // dl
  char v36; // dl
  char v37; // al
  char v38; // dl
  char v39; // cl
  char v40; // al
  char v41; // cl
  char v42; // cl
  char v43; // cl
  char v44; // cl
  unsigned int v45; // eax
  char v46; // cl
  char v47; // cl
  char v48; // cl
  char v49; // cl
  unsigned int v50; // eax
  int v51; // esi
  int v52; // ecx
  int v53; // eax
  int v54; // esi
  int v55; // eax
  char v56; // cl
  char v57; // al
  char v58; // cl
  char v59; // al
  _WORD *v60; // edx
  _BYTE *v61; // eax
  char v62; // cl
  char v63; // al
  char v64; // cl
  char v65; // al
  _WORD *v66; // edx
  _BYTE *v67; // eax
  char v68; // cl
  char v69; // cl
  char v70; // cl
  char v71; // cl
  char v72; // cl
  char v73; // al
  char v74; // cl
  _BYTE *v75; // ecx
  char v76; // cl
  char v77; // al
  char v78; // cl
  char v79; // al
  char v80; // al
  char v81; // cl
  char v82; // cl
  _BYTE *v83; // ecx
  char v84; // cl
  char v85; // cl
  _BYTE *v86; // ecx
  char v87; // cl
  char v88; // cl
  _BYTE *v89; // ecx
  int v90; // eax
  char v91; // bl
  char *v92; // ecx
  int v93; // eax
  char v94; // cl
  int v95; // eax
  char v96; // cl
  unsigned __int8 v97; // al
  GTE_REG *v98; // eax
  unsigned __int8 v99; // al
  int v100; // eax
  int (*v101)(); // edx
  char v102; // cl
  char v103; // al
  char v104; // cl
  _BYTE *v105; // eax
  char v106; // cl
  char v107; // al
  _BYTE *v108; // eax
  char v109; // al
  char v110; // cl
  char v111; // al
  char v112; // al
  char v113; // cl
  char v114; // al
  _BYTE *v115; // ecx
  bool v116; // zf
  char v117; // cl
  char v118; // al
  char v119; // cl
  _BYTE *v120; // eax
  char v121; // cl
  char v122; // al
  _BYTE *v123; // eax
  char v124; // al
  char v125; // cl
  char v126; // cl
  char v127; // al
  char v128; // cl
  _WORD *v129; // eax
  char v130; // cl
  char v131; // al
  char v132; // cl
  _WORD *v133; // eax
  char v134; // cl
  char v135; // al
  char v136; // cl
  char v137; // cl
  char v138; // al
  char v139; // cl
  _WORD *v140; // eax
  _BYTE *v141; // ecx
  unsigned int v142; // eax
  char v143; // cl
  char v144; // al
  char v145; // cl
  unsigned __int8 v146; // al
  unsigned int v147; // edx
  char *v148; // ecx
  char v149; // dl
  unsigned int v150; // ecx
  int v151; // eax
  int v152; // eax
  int v153; // eax
  unsigned int v154; // eax
  int v155; // eax
  unsigned int v156; // ebp
  char v157; // [esp+13h] [ebp-25h]
  int v158; // [esp+14h] [ebp-24h]
  int v159; // [esp+18h] [ebp-20h]
  unsigned __int8 ArgLista; // [esp+3Ch] [ebp+4h]

  v2 = (char *)dword_4FC4E0;
  v3 = a2;
  v4 = 0;
  v157 = 0;
  v158 = 0;
  v159 = 0;
  if ( a2 != 1 && dword_4FC4E0 - (int)dword_5164C0 >= 2080768 )
  {
    do
    {
      *(_DWORD *)((char *)dword_5164C4 + v4) = dword_5164C0;
      v4 += 4;
    }
    while ( v4 < 0x280000 );
    v3 = a2;
    dword_4FC4E0 = (int)dword_5164C0 + 1216;
    v2 = (char *)dword_5164C0 + 1216;
  }
  if ( cpu_gpr[0] )
    fatal_error_with_message_box(" dohh zero reg != 0\n");
  while ( 1 )
  {
    if ( v3 == 1 )
      v157 = 1;
    if ( ++v158 > v3 )
      fatal_error_with_message_box(" ePSXe (error) recompile block too large \n");
    v6 = (ArgList & 0xFFF00000) == 0xBFC00000 ? (ArgList & 0x7FFFF) + 0x200000 : ArgList & 0x1FFFFF;
    if ( *(LPVOID *)((char *)dword_5164C4 + v6) != dword_5164C0 && !v157 )
      break;
    v7 = *(_DWORD *)((unsigned __int16)ArgList + mem_read_hooks[HIWORD(ArgList)]);
    if ( a2 != 1 )
    {
      *(_DWORD *)((char *)dword_5164C4 + v6) = v2;
      if ( v158 == 1 )
        v159 = dword_4FC4E0;
      *(_DWORD *)((char *)dword_5164C8 + v6) = v159;
      v2 = (char *)dword_4FC4E0;
    }
    if ( (_BYTE)dword_4F831C )
    {
      v8 = 0;
      ArgLista = 0;
      do
      {
        v9 = dword_5B6DC4[2 * ArgLista];
        if ( (v9 & 0x1FFFFF) == ArgList )
        {
          v7 = dword_5B6DC0[2 * ArgLista];
          if ( (v9 & 0xF0000000) == 0 )
          {
            v10 = v8 + 1;
            if ( (unsigned __int8)(v8 + 1) < (unsigned __int8)dword_4F831C )
            {
              v11 = (_DWORD *)(8 * v10 + 5991868);
              v12 = (unsigned __int8)(dword_4F831C - v10);
              do
              {
                *(v11 - 1) = v11[1];
                *v11 = v11[2];
                v11 += 2;
                --v12;
              }
              while ( v12 );
            }
            LOBYTE(dword_4F831C) = dword_4F831C - 1;
          }
        }
        ArgLista = ++v8;
      }
      while ( v8 < (unsigned __int8)dword_4F831C );
      v2 = (char *)dword_4FC4E0;
    }
    ArgList += 4;
    switch ( v7 >> 26 )
    {
      case 0u:
        switch ( v7 & 0x3F )
        {
          case 0u:
            if ( !v7 )
              goto LABEL_33;
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v14 = (v7 >> 6) & 0x1F;
            v15 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v15 == v13 )
            {
              *(_WORD *)dword_4FC4E0 = 26305;
              goto LABEL_45;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = v15;
            *(_WORD *)(dword_4FC4E0 + 3) = -7999;
            goto LABEL_118;
          case 2u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v14 = (v7 >> 6) & 0x1F;
            v16 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v16 == v13 )
            {
              *(_WORD *)dword_4FC4E0 = 28353;
              goto LABEL_45;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = v16;
            *(_WORD *)(dword_4FC4E0 + 3) = -5951;
            goto LABEL_118;
          case 3u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v14 = (v7 >> 6) & 0x1F;
            v17 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v17 != v13 )
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v17;
              *(_WORD *)(dword_4FC4E0 + 3) = -1855;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = 32449;
LABEL_45:
            *(_BYTE *)(dword_4FC4E0 + 2) = v13;
            *(_BYTE *)(dword_4FC4E0 + 3) = v14;
            *(_BYTE *)(dword_4FC4E0 + 4) = 79;
            dword_4FC4E0 += 5;
            goto LABEL_422;
          case 4u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v19 = 4 * ((v7 >> 21) & 0x1F);
            v20 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v20 == v18 )
            {
              *(_WORD *)dword_4FC4E0 = 20107;
              *(_BYTE *)(dword_4FC4E0 + 2) = v19;
              *(_WORD *)(dword_4FC4E0 + 3) = -7807;
              *(_DWORD *)(dword_4FC4E0 + 5) = 31;
              *(_WORD *)(dword_4FC4E0 + 9) = 26323;
              goto LABEL_50;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = v20;
            *(_WORD *)(dword_4FC4E0 + 3) = 20107;
            *(_BYTE *)(dword_4FC4E0 + 5) = v19;
            *(_WORD *)(dword_4FC4E0 + 6) = -7807;
            *(_DWORD *)(dword_4FC4E0 + 8) = 31;
            *(_WORD *)(dword_4FC4E0 + 12) = -7981;
            goto LABEL_130;
          case 6u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v21 = 4 * ((v7 >> 21) & 0x1F);
            v22 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v22 == v18 )
            {
              *(_WORD *)dword_4FC4E0 = 20107;
              *(_BYTE *)(dword_4FC4E0 + 2) = v21;
              *(_WORD *)(dword_4FC4E0 + 3) = -7807;
              *(_DWORD *)(dword_4FC4E0 + 5) = 31;
              *(_WORD *)(dword_4FC4E0 + 9) = 28371;
              goto LABEL_50;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = v22;
            *(_WORD *)(dword_4FC4E0 + 3) = 20107;
            *(_BYTE *)(dword_4FC4E0 + 5) = v21;
            *(_WORD *)(dword_4FC4E0 + 6) = -7807;
            *(_DWORD *)(dword_4FC4E0 + 8) = 31;
            *(_WORD *)(dword_4FC4E0 + 12) = -5933;
            goto LABEL_130;
          case 7u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v23 = 4 * ((v7 >> 21) & 0x1F);
            v24 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v24 == v18 )
            {
              *(_WORD *)dword_4FC4E0 = 20107;
              *(_BYTE *)(dword_4FC4E0 + 2) = v23;
              *(_WORD *)(dword_4FC4E0 + 3) = -7807;
              *(_DWORD *)(dword_4FC4E0 + 5) = 31;
              *(_WORD *)(dword_4FC4E0 + 9) = 32467;
LABEL_50:
              *(_BYTE *)(dword_4FC4E0 + 11) = v18;
              *(_BYTE *)(dword_4FC4E0 + 12) = 79;
              dword_4FC4E0 += 13;
            }
            else
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v24;
              *(_WORD *)(dword_4FC4E0 + 3) = 20107;
              *(_BYTE *)(dword_4FC4E0 + 5) = v23;
              *(_WORD *)(dword_4FC4E0 + 6) = -7807;
              *(_DWORD *)(dword_4FC4E0 + 8) = 31;
              *(_WORD *)(dword_4FC4E0 + 12) = -1837;
LABEL_130:
              *(_WORD *)(dword_4FC4E0 + 14) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 16) = v18;
              *(_BYTE *)(dword_4FC4E0 + 17) = 79;
              dword_4FC4E0 += 18;
            }
            goto LABEL_422;
          case 8u:
            if ( a2 == 1 )
              goto LABEL_422;
            *(_WORD *)v2 = 32267;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            *(_BYTE *)(dword_4FC4E0 + 9) = 117;
            dword_5164CC = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            *(_BYTE *)dword_4FC4E0 = 79;
            *(_WORD *)(dword_4FC4E0 + 1) = 18059;
            *(_BYTE *)(dword_4FC4E0 + 3) = 4 * ((v7 >> 21) & 0x1F);
            *(_BYTE *)(dword_4FC4E0 + 4) = -24;
            *(_DWORD *)(dword_4FC4E0 + 5) = (char *)dword_5164C0 - dword_4FC4E0 + 119;
            *(_BYTE *)(dword_4FC4E0 + 9) = 80;
            dword_4FC4E0 += 10;
            dynarec_compile(ArgList, 1);
            *(_BYTE *)dword_4FC4E0 = 88;
            *(_WORD *)(dword_4FC4E0 + 1) = 8447;
            dword_4FC4E0 += 3;
            *(_BYTE *)dword_5164CC = dword_4FC4E0 - dword_5164CC - 1;
            *(_WORD *)dword_4FC4E0 = 18119;
            *(_BYTE *)(dword_4FC4E0 + 2) = 0x80;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 32393;
            *(_BYTE *)(dword_4FC4E0 + 9) = -112;
            *(_BYTE *)(dword_4FC4E0 + 10) = -24;
            *(_DWORD *)(dword_4FC4E0 + 11) = (char *)sub_4238B0 - dword_4FC4E0 - 15;
            *(_WORD *)(dword_4FC4E0 + 15) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
            *(_BYTE *)(dword_4FC4E0 + 21) = 116;
            *(_BYTE *)(dword_4FC4E0 + 22) = 8;
            *(_WORD *)(dword_4FC4E0 + 23) = -14463;
            *(_DWORD *)(dword_4FC4E0 + 25) = dword_455940;
            *(_WORD *)(dword_4FC4E0 + 29) = 8447;
            *(_WORD *)(dword_4FC4E0 + 31) = -2175;
            *(_DWORD *)(dword_4FC4E0 + 33) = 0x80000000;
            goto LABEL_62;
          case 9u:
            if ( a2 == 1 )
              goto LABEL_422;
            *(_WORD *)v2 = 32267;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            *(_BYTE *)(dword_4FC4E0 + 9) = 117;
            v26 = 4 * ((v7 >> 21) & 0x1F);
            v27 = 4 * ((v7 >> 11) & 0x1F);
            v28 = (_BYTE *)(dword_4FC4E0 + 11);
            dword_5164CC = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            if ( v27 == v26 )
              dword_4FF9E8 |= 0x800000u;
            *v28 = 79;
            if ( v27 )
            {
              *(_WORD *)(dword_4FC4E0 + 1) = 18119;
              *(_BYTE *)(dword_4FC4E0 + 3) = v27;
              v29 = ArgList + 4;
              if ( (ArgList & 0xF0000000) == 0 )
                v29 |= 0x80000000;
              *(_DWORD *)(dword_4FC4E0 + 4) = v29;
              *(_WORD *)(dword_4FC4E0 + 8) = 18059;
              *(_BYTE *)(dword_4FC4E0 + 10) = v26;
              *(_BYTE *)(dword_4FC4E0 + 11) = -24;
              *(_DWORD *)(dword_4FC4E0 + 12) = (char *)dword_5164C0 - dword_4FC4E0 + 112;
              *(_BYTE *)(dword_4FC4E0 + 16) = 80;
              v30 = dword_4FC4E0 + 17;
            }
            else
            {
              *(_WORD *)(dword_4FC4E0 + 1) = 18059;
              *(_BYTE *)(dword_4FC4E0 + 3) = v26;
              *(_BYTE *)(dword_4FC4E0 + 4) = -24;
              *(_DWORD *)(dword_4FC4E0 + 5) = (char *)dword_5164C0 - dword_4FC4E0 + 119;
              *(_BYTE *)(dword_4FC4E0 + 9) = 80;
              v30 = dword_4FC4E0 + 10;
            }
            dword_4FC4E0 = v30;
            dynarec_compile(ArgList, 1);
            *(_BYTE *)dword_4FC4E0 = 88;
            *(_WORD *)(dword_4FC4E0 + 1) = 8447;
            dword_4FC4E0 += 3;
            *(_BYTE *)dword_5164CC = dword_4FC4E0 - dword_5164CC - 1;
            *(_WORD *)dword_4FC4E0 = 18119;
            *(_BYTE *)(dword_4FC4E0 + 2) = 0x80;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 32393;
            *(_BYTE *)(dword_4FC4E0 + 9) = -112;
            *(_BYTE *)(dword_4FC4E0 + 10) = -24;
            *(_DWORD *)(dword_4FC4E0 + 11) = (char *)sub_4238B0 - dword_4FC4E0 - 15;
            *(_WORD *)(dword_4FC4E0 + 15) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
            *(_BYTE *)(dword_4FC4E0 + 21) = 116;
            *(_BYTE *)(dword_4FC4E0 + 22) = 8;
            *(_WORD *)(dword_4FC4E0 + 23) = -14463;
            *(_DWORD *)(dword_4FC4E0 + 25) = dword_455940;
            *(_WORD *)(dword_4FC4E0 + 29) = 8447;
            *(_WORD *)(dword_4FC4E0 + 31) = -2175;
            *(_DWORD *)(dword_4FC4E0 + 33) = 0x80000000;
LABEL_62:
            *(_WORD *)(dword_4FC4E0 + 37) = 8447;
            goto LABEL_63;
          case 0xCu:
            *(_WORD *)v2 = 18119;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_DWORD *)(dword_4FC4E0 + 3) = 0;
            dword_4FC4E0 += 7;
            *(_WORD *)dword_4FC4E0 = 18119;
            *(_BYTE *)(dword_4FC4E0 + 2) = -52;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 18119;
            *(_BYTE *)(dword_4FC4E0 + 9) = -56;
            *(_DWORD *)(dword_4FC4E0 + 10) = 32;
            *(_WORD *)(dword_4FC4E0 + 14) = 18059;
            *(_BYTE *)(dword_4FC4E0 + 16) = -60;
            *(_WORD *)(dword_4FC4E0 + 17) = 26241;
            *(_BYTE *)(dword_4FC4E0 + 19) = -60;
            *(_DWORD *)(dword_4FC4E0 + 20) = -64;
            *(_WORD *)(dword_4FC4E0 + 24) = -7999;
            *(_BYTE *)(dword_4FC4E0 + 26) = 2;
            *(_BYTE *)(dword_4FC4E0 + 27) = 37;
            *(_DWORD *)(dword_4FC4E0 + 28) = 63;
            *(_WORD *)(dword_4FC4E0 + 32) = 17929;
            *(_BYTE *)(dword_4FC4E0 + 34) = -60;
            *(_BYTE *)(dword_4FC4E0 + 35) = -72;
            *(_DWORD *)(dword_4FC4E0 + 36) = (char *)dword_5164C4 + 128;
            *(_WORD *)(dword_4FC4E0 + 40) = 8447;
            *(_BYTE *)(dword_4FC4E0 + 42) = 79;
            dword_4FC4E0 += 43;
            goto LABEL_422;
          case 0xDu:
            dword_4FF9E8 |= 0x2000u;
            goto LABEL_422;
          case 0x10u:
            v31 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v31 )
              goto LABEL_422;
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = -120;
            goto LABEL_75;
          case 0x11u:
            *(_WORD *)v2 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 5) = -120;
            *(_BYTE *)(dword_4FC4E0 + 6) = 79;
            dword_4FC4E0 += 7;
            goto LABEL_422;
          case 0x12u:
            v31 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v31 )
              goto LABEL_422;
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = -124;
LABEL_75:
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 5) = v31;
            goto LABEL_253;
          case 0x13u:
            *(_WORD *)v2 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 5) = -124;
            *(_BYTE *)(dword_4FC4E0 + 6) = 79;
            dword_4FC4E0 += 7;
            goto LABEL_422;
          case 0x18u:
            *(_WORD *)v2 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 28407;
            goto LABEL_81;
          case 0x19u:
            *(_WORD *)v2 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 26359;
LABEL_81:
            *(_BYTE *)(dword_4FC4E0 + 5) = 4 * (BYTE2(v7) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 6) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 8) = -124;
            *(_WORD *)(dword_4FC4E0 + 9) = 22153;
            *(_BYTE *)(dword_4FC4E0 + 11) = -120;
            *(_BYTE *)(dword_4FC4E0 + 12) = 79;
            dword_4FC4E0 += 13;
            goto LABEL_422;
          case 0x1Au:
            *(_WORD *)v2 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
            *(_BYTE *)(dword_4FC4E0 + 3) = -103;
            *(_WORD *)(dword_4FC4E0 + 4) = 20107;
            *(_BYTE *)(dword_4FC4E0 + 6) = 4 * (BYTE2(v7) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 7) = -13947;
            *(_WORD *)(dword_4FC4E0 + 9) = 2676;
            *(_WORD *)(dword_4FC4E0 + 11) = -1545;
            *(_WORD *)(dword_4FC4E0 + 13) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 15) = -124;
            *(_WORD *)(dword_4FC4E0 + 16) = 22153;
            *(_BYTE *)(dword_4FC4E0 + 18) = -120;
            *(_WORD *)(dword_4FC4E0 + 19) = 6123;
            *(_WORD *)(dword_4FC4E0 + 21) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 23) = -120;
            *(_BYTE *)(dword_4FC4E0 + 24) = -70;
            *(_DWORD *)(dword_4FC4E0 + 25) = -1;
            *(_BYTE *)(dword_4FC4E0 + 29) = -87;
            *(_DWORD *)(dword_4FC4E0 + 30) = 0x80000000;
            *(_WORD *)(dword_4FC4E0 + 34) = 1396;
            *(_BYTE *)(dword_4FC4E0 + 36) = -70;
            *(_DWORD *)(dword_4FC4E0 + 37) = 1;
            *(_WORD *)(dword_4FC4E0 + 41) = 22153;
            *(_BYTE *)(dword_4FC4E0 + 43) = -124;
            *(_BYTE *)(dword_4FC4E0 + 44) = 79;
            dword_4FC4E0 += 45;
            goto LABEL_422;
          case 0x1Bu:
            *(_WORD *)v2 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = -11727;
            *(_WORD *)(dword_4FC4E0 + 5) = 20107;
            *(_BYTE *)(dword_4FC4E0 + 7) = 4 * (BYTE2(v7) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 8) = -13947;
            *(_WORD *)(dword_4FC4E0 + 10) = 2676;
            *(_WORD *)(dword_4FC4E0 + 12) = -3593;
            *(_WORD *)(dword_4FC4E0 + 14) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 16) = -124;
            *(_WORD *)(dword_4FC4E0 + 17) = 22153;
            *(_BYTE *)(dword_4FC4E0 + 19) = -120;
            *(_WORD *)(dword_4FC4E0 + 20) = 3051;
            *(_WORD *)(dword_4FC4E0 + 22) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 24) = -120;
            *(_BYTE *)(dword_4FC4E0 + 25) = -70;
            *(_DWORD *)(dword_4FC4E0 + 26) = -1;
            *(_WORD *)(dword_4FC4E0 + 30) = 22153;
            *(_BYTE *)(dword_4FC4E0 + 32) = -124;
            *(_BYTE *)(dword_4FC4E0 + 33) = 79;
            dword_4FC4E0 += 34;
            goto LABEL_422;
          case 0x20u:
          case 0x21u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v32 = 4 * ((v7 >> 21) & 0x1F);
            v14 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v32 )
            {
              if ( v32 == v13 )
              {
                *(_WORD *)dword_4FC4E0 = 18059;
                *(_BYTE *)(dword_4FC4E0 + 2) = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17921;
                *(_BYTE *)(dword_4FC4E0 + 5) = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v32;
              *(_WORD *)(dword_4FC4E0 + 3) = 17923;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *(_WORD *)(dword_4FC4E0 + 2) = 17923;
            *(_BYTE *)(dword_4FC4E0 + 4) = v14;
            goto LABEL_273;
          case 0x22u:
          case 0x23u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v33 = 4 * ((v7 >> 21) & 0x1F);
            v14 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v33 )
            {
              if ( v33 == v13 )
              {
                *(_WORD *)dword_4FC4E0 = 18059;
                *(_BYTE *)(dword_4FC4E0 + 2) = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17961;
                *(_BYTE *)(dword_4FC4E0 + 5) = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v33;
              *(_WORD *)(dword_4FC4E0 + 3) = 17963;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *(_WORD *)(dword_4FC4E0 + 2) = 17963;
            *(_BYTE *)(dword_4FC4E0 + 4) = v14;
            goto LABEL_273;
          case 0x24u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v34 = 4 * ((v7 >> 21) & 0x1F);
            v14 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v34 )
            {
              if ( v34 == v13 )
              {
                *(_WORD *)dword_4FC4E0 = 18059;
                *(_BYTE *)(dword_4FC4E0 + 2) = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17953;
                *(_BYTE *)(dword_4FC4E0 + 5) = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v34;
              *(_WORD *)(dword_4FC4E0 + 3) = 17955;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *(_WORD *)(dword_4FC4E0 + 2) = 17955;
            *(_BYTE *)(dword_4FC4E0 + 4) = v14;
            goto LABEL_273;
          case 0x25u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v35 = 4 * ((v7 >> 21) & 0x1F);
            v14 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v35 )
            {
              if ( v35 == v13 )
              {
                *(_WORD *)dword_4FC4E0 = 18059;
                *(_BYTE *)(dword_4FC4E0 + 2) = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17929;
                *(_BYTE *)(dword_4FC4E0 + 5) = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v35;
              *(_WORD *)(dword_4FC4E0 + 3) = 17931;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *(_WORD *)(dword_4FC4E0 + 2) = 17931;
            *(_BYTE *)(dword_4FC4E0 + 4) = v14;
            goto LABEL_273;
          case 0x26u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v36 = 4 * ((v7 >> 21) & 0x1F);
            v14 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v36 )
            {
              if ( v36 == v13 )
              {
                *(_WORD *)dword_4FC4E0 = 18059;
                *(_BYTE *)(dword_4FC4E0 + 2) = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17969;
                *(_BYTE *)(dword_4FC4E0 + 5) = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v36;
              *(_WORD *)(dword_4FC4E0 + 3) = 17971;
LABEL_118:
              *(_BYTE *)(dword_4FC4E0 + 5) = v14;
              *(_WORD *)(dword_4FC4E0 + 6) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 8) = v13;
              *(_BYTE *)(dword_4FC4E0 + 9) = 79;
              dword_4FC4E0 += 10;
            }
            else
            {
              *(_WORD *)dword_4FC4E0 = -16335;
              if ( v14 )
              {
                *(_WORD *)(dword_4FC4E0 + 2) = 17971;
                *(_BYTE *)(dword_4FC4E0 + 4) = v14;
                goto LABEL_273;
              }
LABEL_121:
              *(_WORD *)(dword_4FC4E0 + 2) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 4) = v13;
              *(_BYTE *)(dword_4FC4E0 + 5) = 79;
              dword_4FC4E0 += 6;
            }
            goto LABEL_422;
          case 0x27u:
            v37 = 4 * ((v7 >> 11) & 0x1F);
            v38 = 4 * ((v7 >> 21) & 0x1F);
            v39 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v37 )
              goto LABEL_422;
            if ( v38 )
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = v38;
              *(_WORD *)(dword_4FC4E0 + 3) = 17931;
              *(_BYTE *)(dword_4FC4E0 + 5) = v39;
              *(_WORD *)(dword_4FC4E0 + 6) = -12041;
              *(_WORD *)(dword_4FC4E0 + 8) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 10) = v37;
              *(_BYTE *)(dword_4FC4E0 + 11) = 79;
              dword_4FC4E0 += 12;
              goto LABEL_422;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = v39;
            *(_WORD *)(dword_4FC4E0 + 3) = -12041;
            break;
          case 0x2Au:
            v40 = 4 * ((v7 >> 11) & 0x1F);
            if ( v40 )
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
              *(_WORD *)(dword_4FC4E0 + 3) = 17979;
              *(_BYTE *)(dword_4FC4E0 + 5) = 4 * (BYTE2(v7) & 0x1F);
              *(_WORD *)(dword_4FC4E0 + 6) = -25585;
              *(_BYTE *)(dword_4FC4E0 + 8) = -64;
              *(_BYTE *)(dword_4FC4E0 + 9) = 37;
              *(_DWORD *)(dword_4FC4E0 + 10) = 1;
              *(_WORD *)(dword_4FC4E0 + 14) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 16) = v40;
              *(_BYTE *)(dword_4FC4E0 + 17) = 79;
              dword_4FC4E0 += 18;
            }
            goto LABEL_422;
          case 0x2Bu:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 17979;
            *(_BYTE *)(dword_4FC4E0 + 5) = 4 * (BYTE2(v7) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 6) = -28145;
            *(_BYTE *)(dword_4FC4E0 + 8) = -64;
            *(_BYTE *)(dword_4FC4E0 + 9) = 37;
            *(_DWORD *)(dword_4FC4E0 + 10) = 1;
            goto LABEL_130;
          default:
            fatal_error_with_message_box(
              "SPEC Opcode %02x UNK (PC %08x) (%08x) (%d,%d)\n",
              v7 & 0x3F,
              ArgList - 4,
              *(_DWORD *)reg_pc,
              dword_50C360,
              dword_50C364);
            return result;
        }
        goto LABEL_203;
      case 1u:
        switch ( HIWORD(v7) & 0x1F )
        {
          case 0:
            if ( a2 == 1 )
              goto LABEL_422;
            v41 = (v7 >> 21) & 0x1F;
            v7 = (unsigned __int16)v7;
            v42 = 4 * v41;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(_WORD *)v2 = 32267;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            *(_BYTE *)(dword_4FC4E0 + 9) = 117;
            dword_5164CC = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = -16335;
            *(_BYTE *)(dword_4FC4E0 + 2) = 79;
            *(_WORD *)(dword_4FC4E0 + 3) = 17977;
            *(_BYTE *)(dword_4FC4E0 + 5) = v42;
            *(_BYTE *)(dword_4FC4E0 + 6) = 124;
            goto LABEL_141;
          case 1:
            if ( a2 == 1 )
              goto LABEL_422;
            v43 = (v7 >> 21) & 0x1F;
            v7 = (unsigned __int16)v7;
            v44 = 4 * v43;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(_WORD *)v2 = 32267;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            *(_BYTE *)(dword_4FC4E0 + 9) = 117;
            dword_5164CC = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = -16335;
            *(_BYTE *)(dword_4FC4E0 + 2) = 79;
            *(_WORD *)(dword_4FC4E0 + 3) = 17977;
            *(_BYTE *)(dword_4FC4E0 + 5) = v44;
            *(_BYTE *)(dword_4FC4E0 + 6) = 125;
            goto LABEL_141;
          case 0x10:
            if ( a2 == 1 )
              goto LABEL_422;
            v46 = (v7 >> 21) & 0x1F;
            v7 = (unsigned __int16)v7;
            v47 = 4 * v46;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(_WORD *)v2 = 32267;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            *(_BYTE *)(dword_4FC4E0 + 9) = 117;
            dword_5164CC = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = 18119;
            *(_BYTE *)(dword_4FC4E0 + 2) = 124;
            *(_DWORD *)(dword_4FC4E0 + 3) = (ArgList + 4) | 0x80000000;
            *(_WORD *)(dword_4FC4E0 + 7) = -16335;
            *(_BYTE *)(dword_4FC4E0 + 9) = 79;
            *(_WORD *)(dword_4FC4E0 + 10) = 17977;
            *(_BYTE *)(dword_4FC4E0 + 12) = v47;
            *(_BYTE *)(dword_4FC4E0 + 13) = 124;
            goto LABEL_151;
          case 0x11:
            if ( a2 == 1 )
              goto LABEL_422;
            v48 = (v7 >> 21) & 0x1F;
            v7 = (unsigned __int16)v7;
            v49 = 4 * v48;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(_WORD *)v2 = 32267;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            *(_BYTE *)(dword_4FC4E0 + 9) = 117;
            dword_5164CC = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = 18119;
            *(_BYTE *)(dword_4FC4E0 + 2) = 124;
            *(_DWORD *)(dword_4FC4E0 + 3) = (ArgList + 4) | 0x80000000;
            *(_WORD *)(dword_4FC4E0 + 7) = -16335;
            *(_BYTE *)(dword_4FC4E0 + 9) = 79;
            *(_WORD *)(dword_4FC4E0 + 10) = 17977;
            *(_BYTE *)(dword_4FC4E0 + 12) = v49;
            *(_BYTE *)(dword_4FC4E0 + 13) = 125;
LABEL_151:
            *(_BYTE *)(dword_4FC4E0 + 14) = 7;
            *(_BYTE *)(dword_4FC4E0 + 15) = -72;
            if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
              v50 = (ArgList & 0x7FFFF) + 0x200000;
            else
              v50 = ArgList & 0x1FFFFF;
            *(_DWORD *)(dword_4FC4E0 + 16) = (char *)dword_5164C4 + v50;
            *(_WORD *)(dword_4FC4E0 + 20) = 8447;
            v151 = dword_4FC4E0 + 22;
            break;
          default:
            fatal_error_with_message_box(" REGIM Opcode %02x UNK PC[%08x]\n", 1, ArgList - 4);
            return result;
        }
        goto LABEL_428;
      case 2u:
        if ( a2 != 1 )
        {
          v51 = 4 * (v7 & 0x3FFFFFF);
          if ( !BYTE1(dword_455945) || ((v51 ^ (ArgList - 4)) & 0xFFFFFF) != 0 )
          {
            *(_WORD *)dword_4FC4E0 = 32267;
            *(_BYTE *)(dword_4FC4E0 + 2) = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            *(_BYTE *)(dword_4FC4E0 + 9) = 117;
            v52 = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            dword_5164CC = v52;
            *(_BYTE *)dword_4FC4E0++ = 79;
            dynarec_compile(ArgList, 1);
            *(_BYTE *)dword_4FC4E0 = -72;
            if ( (v51 & 0xFFF00000 | ArgList & 0xF0000000) == 0xBFC00000 )
              v53 = (v51 & 0x7FFFF) + 0x200000;
            else
              v53 = v51 & 0x1FFFFF;
            *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v53;
            *(_WORD *)(dword_4FC4E0 + 5) = 8447;
            dword_4FC4E0 += 7;
            *(_BYTE *)dword_5164CC = dword_4FC4E0 - dword_5164CC - 1;
            *(_WORD *)dword_4FC4E0 = 18119;
            *(_BYTE *)(dword_4FC4E0 + 2) = 0x80;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 32393;
            *(_BYTE *)(dword_4FC4E0 + 9) = -112;
            *(_BYTE *)(dword_4FC4E0 + 10) = -24;
            *(_DWORD *)(dword_4FC4E0 + 11) = (char *)sub_4238B0 - dword_4FC4E0 - 15;
            *(_WORD *)(dword_4FC4E0 + 15) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
            *(_BYTE *)(dword_4FC4E0 + 21) = 116;
            *(_BYTE *)(dword_4FC4E0 + 22) = 8;
            *(_WORD *)(dword_4FC4E0 + 23) = -14463;
            *(_DWORD *)(dword_4FC4E0 + 25) = dword_455940;
            *(_WORD *)(dword_4FC4E0 + 29) = 8447;
            *(_WORD *)(dword_4FC4E0 + 31) = -2175;
            *(_DWORD *)(dword_4FC4E0 + 33) = 0x80000000;
            *(_WORD *)(dword_4FC4E0 + 37) = 8447;
            dword_4FC4E0 += 39;
            ArgList = v51 | ArgList & 0xF0000000;
          }
        }
        goto LABEL_422;
      case 3u:
        if ( a2 != 1 )
        {
          *(_WORD *)dword_4FC4E0 = 32267;
          *(_BYTE *)(dword_4FC4E0 + 2) = -44;
          *(_WORD *)(dword_4FC4E0 + 3) = -14345;
          *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
          *(_BYTE *)(dword_4FC4E0 + 9) = 117;
          v54 = 4 * (v7 & 0x3FFFFFF);
          dword_5164CC = dword_4FC4E0 + 10;
          dword_4FC4E0 += 11;
          *(_BYTE *)dword_4FC4E0 = 79;
          *(_WORD *)(dword_4FC4E0 + 1) = 18119;
          *(_BYTE *)(dword_4FC4E0 + 3) = 124;
          if ( (ArgList & 0xF0000000) != 0 )
            *(_DWORD *)(dword_4FC4E0 + 4) = ArgList + 4;
          else
            *(_DWORD *)(dword_4FC4E0 + 4) = (ArgList + 4) | 0x80000000;
          dword_4FC4E0 += 8;
          dynarec_compile(ArgList, 1);
          *(_BYTE *)dword_4FC4E0 = -72;
          if ( (v54 & 0xFFF00000 | ArgList & 0xF0000000) == 0xBFC00000 )
            v55 = (v54 & 0x7FFFF) + 0x200000;
          else
            v55 = v54 & 0x1FFFFF;
          *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v55;
          *(_WORD *)(dword_4FC4E0 + 5) = 8447;
          dword_4FC4E0 += 7;
          *(_BYTE *)dword_5164CC = dword_4FC4E0 - dword_5164CC - 1;
          *(_WORD *)dword_4FC4E0 = 18119;
          *(_BYTE *)(dword_4FC4E0 + 2) = 0x80;
          *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
          *(_WORD *)(dword_4FC4E0 + 7) = 32393;
          *(_BYTE *)(dword_4FC4E0 + 9) = -112;
          *(_BYTE *)(dword_4FC4E0 + 10) = -24;
          *(_DWORD *)(dword_4FC4E0 + 11) = (char *)sub_4238B0 - dword_4FC4E0 - 15;
          *(_WORD *)(dword_4FC4E0 + 15) = -14345;
          *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
          *(_BYTE *)(dword_4FC4E0 + 21) = 116;
          *(_BYTE *)(dword_4FC4E0 + 22) = 8;
          *(_WORD *)(dword_4FC4E0 + 23) = -14463;
          *(_DWORD *)(dword_4FC4E0 + 25) = dword_455940;
          *(_WORD *)(dword_4FC4E0 + 29) = 8447;
          *(_WORD *)(dword_4FC4E0 + 31) = -2175;
          *(_DWORD *)(dword_4FC4E0 + 33) = 0x80000000;
          *(_WORD *)(dword_4FC4E0 + 37) = 8447;
          ArgList = v54 | ArgList & 0xF0000000;
          dword_4FC4E0 += 39;
        }
        goto LABEL_422;
      case 4u:
        if ( a2 == 1 )
          goto LABEL_422;
        v56 = (v7 >> 21) & 0x1F;
        v57 = BYTE2(v7) & 0x1F;
        v7 = (unsigned __int16)v7;
        v58 = 4 * v56;
        v59 = 4 * v57;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(_WORD *)v2 = 32267;
        *(_BYTE *)(dword_4FC4E0 + 2) = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        *(_BYTE *)(dword_4FC4E0 + 9) = 117;
        v60 = (_WORD *)(dword_4FC4E0 + 11);
        dword_5164CC = dword_4FC4E0 + 10;
        dword_4FC4E0 += 11;
        if ( v59 )
        {
          *v60 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v59;
          v61 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        else
        {
          *v60 = -16335;
          v61 = (_BYTE *)(dword_4FC4E0 + 2);
        }
        dword_4FC4E0 = (int)v61;
        *v61 = 79;
        *(_WORD *)(dword_4FC4E0 + 1) = 17977;
        *(_BYTE *)(dword_4FC4E0 + 3) = v58;
        *(_BYTE *)(dword_4FC4E0 + 4) = 116;
        goto LABEL_436;
      case 5u:
        if ( a2 == 1
          || BYTE1(dword_455945)
          && v7 == 339804155
          && *(_DWORD *)((unsigned __int16)(ArgList - 8) + mem_read_hooks[(ArgList - 8) >> 16]) == 4395045
          && !*(_DWORD *)((unsigned __int16)(ArgList - 12) + mem_read_hooks[(ArgList - 12) >> 16])
          && (*(_DWORD *)((unsigned __int16)(ArgList - 16) + mem_read_hooks[(ArgList - 16) >> 16]) & 0xFFFF0000) == 0x8C830000
          && (*(_DWORD *)((unsigned __int16)(ArgList - 20) + mem_read_hooks[(ArgList - 20) >> 16]) & 0xFFFF0000) == 0x8CA20000 )
        {
          goto LABEL_422;
        }
        v62 = (v7 >> 21) & 0x1F;
        v63 = BYTE2(v7) & 0x1F;
        v7 = (unsigned __int16)v7;
        v64 = 4 * v62;
        v65 = 4 * v63;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(_WORD *)dword_4FC4E0 = 32267;
        *(_BYTE *)(dword_4FC4E0 + 2) = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        *(_BYTE *)(dword_4FC4E0 + 9) = 117;
        v66 = (_WORD *)(dword_4FC4E0 + 11);
        dword_5164CC = dword_4FC4E0 + 10;
        dword_4FC4E0 += 11;
        if ( v65 )
        {
          *v66 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v65;
          v67 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        else
        {
          *v66 = -16335;
          v67 = (_BYTE *)(dword_4FC4E0 + 2);
        }
        dword_4FC4E0 = (int)v67;
        *v67 = 79;
        *(_WORD *)(dword_4FC4E0 + 1) = 17977;
        *(_BYTE *)(dword_4FC4E0 + 3) = v64;
        *(_BYTE *)(dword_4FC4E0 + 4) = 117;
LABEL_436:
        *(_BYTE *)(dword_4FC4E0 + 5) = 7;
        *(_BYTE *)(dword_4FC4E0 + 6) = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v154 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v154 = ArgList & 0x1FFFFF;
        *(_DWORD *)(dword_4FC4E0 + 7) = (char *)dword_5164C4 + v154;
        *(_WORD *)(dword_4FC4E0 + 11) = 8447;
        dword_4FC4E0 += 13;
        dynarec_compile(ArgList, 1);
        if ( !v7 )
          v7 = 1;
        *(_BYTE *)dword_4FC4E0 = -72;
        v155 = ArgList + 4 * v7;
        if ( (v155 & 0xFFF00000) == 0xBFC00000 )
          v153 = (v155 & 0x7FFFF) + 0x200000;
        else
          v153 = v155 & 0x1FFFFF;
        goto LABEL_447;
      case 6u:
        if ( a2 == 1 )
          goto LABEL_422;
        v68 = (v7 >> 21) & 0x1F;
        v7 = (unsigned __int16)v7;
        v69 = 4 * v68;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(_WORD *)v2 = 32267;
        *(_BYTE *)(dword_4FC4E0 + 2) = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        *(_BYTE *)(dword_4FC4E0 + 9) = 117;
        dword_5164CC = dword_4FC4E0 + 10;
        dword_4FC4E0 += 11;
        *(_WORD *)dword_4FC4E0 = -16335;
        *(_BYTE *)(dword_4FC4E0 + 2) = 79;
        *(_WORD *)(dword_4FC4E0 + 3) = 17977;
        *(_BYTE *)(dword_4FC4E0 + 5) = v69;
        *(_BYTE *)(dword_4FC4E0 + 6) = 126;
        goto LABEL_141;
      case 7u:
        if ( a2 == 1 )
          goto LABEL_422;
        v70 = (v7 >> 21) & 0x1F;
        v7 = (unsigned __int16)v7;
        v71 = 4 * v70;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(_WORD *)v2 = 32267;
        *(_BYTE *)(dword_4FC4E0 + 2) = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        *(_BYTE *)(dword_4FC4E0 + 9) = 117;
        dword_5164CC = dword_4FC4E0 + 10;
        dword_4FC4E0 += 11;
        *(_WORD *)dword_4FC4E0 = -16335;
        *(_BYTE *)(dword_4FC4E0 + 2) = 79;
        *(_WORD *)(dword_4FC4E0 + 3) = 17977;
        *(_BYTE *)(dword_4FC4E0 + 5) = v71;
        *(_BYTE *)(dword_4FC4E0 + 6) = 127;
LABEL_141:
        *(_BYTE *)(dword_4FC4E0 + 7) = 7;
        *(_BYTE *)(dword_4FC4E0 + 8) = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v45 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v45 = ArgList & 0x1FFFFF;
        *(_DWORD *)(dword_4FC4E0 + 9) = (char *)dword_5164C4 + v45;
        *(_WORD *)(dword_4FC4E0 + 13) = 8447;
        v151 = dword_4FC4E0 + 15;
LABEL_428:
        dword_4FC4E0 = v151;
        dynarec_compile(ArgList, 1);
        if ( !v7 )
          v7 = 1;
        *(_BYTE *)dword_4FC4E0 = -72;
        v152 = ArgList + 4 * v7;
        if ( (v152 & 0xFFF00000) == 0xBFC00000 )
          v153 = (v152 & 0x7FFFF) + 0x200000;
        else
          v153 = v152 & 0x1FFFFF;
LABEL_447:
        *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v153;
        *(_WORD *)(dword_4FC4E0 + 5) = 8447;
        dword_4FC4E0 += 7;
        *(_BYTE *)dword_5164CC = dword_4FC4E0 - dword_5164CC - 1;
        *(_WORD *)dword_4FC4E0 = 18119;
        *(_BYTE *)(dword_4FC4E0 + 2) = 0x80;
        *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
        *(_WORD *)(dword_4FC4E0 + 7) = 32393;
        *(_BYTE *)(dword_4FC4E0 + 9) = -112;
        *(_BYTE *)(dword_4FC4E0 + 10) = -24;
        *(_DWORD *)(dword_4FC4E0 + 11) = (char *)sub_4238B0 - dword_4FC4E0 - 15;
        *(_WORD *)(dword_4FC4E0 + 15) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
        *(_BYTE *)(dword_4FC4E0 + 21) = 116;
        *(_BYTE *)(dword_4FC4E0 + 22) = 8;
        *(_WORD *)(dword_4FC4E0 + 23) = -14463;
        *(_DWORD *)(dword_4FC4E0 + 25) = dword_455940;
        *(_WORD *)(dword_4FC4E0 + 29) = 8447;
        *(_WORD *)(dword_4FC4E0 + 31) = -2175;
        *(_DWORD *)(dword_4FC4E0 + 33) = 0x80000000;
        *(_WORD *)(dword_4FC4E0 + 37) = 8447;
LABEL_63:
        dword_4FC4E0 += 39;
        return v158;
      case 8u:
      case 9u:
        v72 = (v7 >> 21) & 0x1F;
        v73 = BYTE2(v7) & 0x1F;
        v7 = (unsigned __int16)v7;
        v74 = 4 * v72;
        v37 = 4 * v73;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( !v37 )
          goto LABEL_422;
        if ( v74 == v37 )
        {
          *(_WORD *)dword_4FC4E0 = 18049;
          goto LABEL_197;
        }
        if ( v74 )
        {
          *(_WORD *)dword_4FC4E0 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v74;
          v75 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        else
        {
          *(_WORD *)dword_4FC4E0 = -16335;
          v75 = (_BYTE *)(dword_4FC4E0 + 2);
        }
        dword_4FC4E0 = (int)v75;
        *v75 = 5;
        goto LABEL_202;
      case 0xAu:
        v76 = (v7 >> 21) & 0x1F;
        v77 = BYTE2(v7) & 0x1F;
        v7 = (unsigned __int16)v7;
        v78 = 4 * v76;
        v79 = 4 * v77;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v79 )
        {
          *(_WORD *)dword_4FC4E0 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v78;
          *(_BYTE *)(dword_4FC4E0 + 3) = 61;
          *(_DWORD *)(dword_4FC4E0 + 4) = v7;
          *(_WORD *)(dword_4FC4E0 + 8) = -25585;
          *(_BYTE *)(dword_4FC4E0 + 10) = -64;
          *(_BYTE *)(dword_4FC4E0 + 11) = 37;
          *(_DWORD *)(dword_4FC4E0 + 12) = 1;
          *(_WORD *)(dword_4FC4E0 + 16) = 18057;
          *(_BYTE *)(dword_4FC4E0 + 18) = v79;
          *(_BYTE *)(dword_4FC4E0 + 19) = 79;
          dword_4FC4E0 += 20;
        }
        goto LABEL_422;
      case 0xBu:
        v80 = 4 * (BYTE2(v7) & 0x1F);
        if ( v80 )
        {
          *(_WORD *)dword_4FC4E0 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = 4 * ((v7 >> 21) & 0x1F);
          *(_BYTE *)(dword_4FC4E0 + 3) = 61;
          *(_DWORD *)(dword_4FC4E0 + 4) = (unsigned __int16)v7;
          *(_WORD *)(dword_4FC4E0 + 8) = -28145;
          *(_BYTE *)(dword_4FC4E0 + 10) = -64;
          *(_BYTE *)(dword_4FC4E0 + 11) = 37;
          *(_DWORD *)(dword_4FC4E0 + 12) = 1;
          *(_WORD *)(dword_4FC4E0 + 16) = 18057;
          *(_BYTE *)(dword_4FC4E0 + 18) = v80;
          *(_BYTE *)(dword_4FC4E0 + 19) = 79;
          dword_4FC4E0 += 20;
        }
        goto LABEL_422;
      case 0xCu:
        v81 = (v7 >> 21) & 0x1F;
        v37 = 4 * (BYTE2(v7) & 0x1F);
        v7 = (unsigned __int16)v7;
        v82 = 4 * v81;
        if ( !v37 )
          goto LABEL_422;
        if ( v82 == v37 )
        {
          *(_WORD *)dword_4FC4E0 = 26241;
          goto LABEL_197;
        }
        if ( v82 )
        {
          *(_WORD *)dword_4FC4E0 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v82;
          v83 = (_BYTE *)(dword_4FC4E0 + 3);
          dword_4FC4E0 += 3;
        }
        else
        {
          *(_WORD *)dword_4FC4E0 = -16335;
          v83 = (_BYTE *)(dword_4FC4E0 + 2);
          dword_4FC4E0 += 2;
        }
        *v83 = 37;
        goto LABEL_202;
      case 0xDu:
        v84 = (v7 >> 21) & 0x1F;
        v37 = 4 * (BYTE2(v7) & 0x1F);
        v7 = (unsigned __int16)v7;
        v85 = 4 * v84;
        if ( !v37 )
          goto LABEL_422;
        if ( v85 == v37 )
        {
          *(_WORD *)dword_4FC4E0 = 20097;
          goto LABEL_197;
        }
        if ( v85 )
        {
          *(_WORD *)dword_4FC4E0 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v85;
          v86 = (_BYTE *)(dword_4FC4E0 + 3);
          dword_4FC4E0 += 3;
        }
        else
        {
          *(_WORD *)dword_4FC4E0 = -16335;
          v86 = (_BYTE *)(dword_4FC4E0 + 2);
          dword_4FC4E0 += 2;
        }
        *v86 = 13;
        goto LABEL_202;
      case 0xEu:
        v87 = (v7 >> 21) & 0x1F;
        v37 = 4 * (BYTE2(v7) & 0x1F);
        v7 = (unsigned __int16)v7;
        v88 = 4 * v87;
        if ( !v37 )
          goto LABEL_422;
        if ( v88 == v37 )
        {
          *(_WORD *)dword_4FC4E0 = 30337;
LABEL_197:
          *(_BYTE *)(dword_4FC4E0 + 2) = v37;
          *(_DWORD *)(dword_4FC4E0 + 3) = v7;
          *(_BYTE *)(dword_4FC4E0 + 7) = 79;
          dword_4FC4E0 += 8;
        }
        else
        {
          if ( v88 )
          {
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = v88;
            v89 = (_BYTE *)(dword_4FC4E0 + 3);
            dword_4FC4E0 += 3;
          }
          else
          {
            *(_WORD *)dword_4FC4E0 = -16335;
            v89 = (_BYTE *)(dword_4FC4E0 + 2);
            dword_4FC4E0 += 2;
          }
          *v89 = 53;
LABEL_202:
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
LABEL_203:
          *(_WORD *)(dword_4FC4E0 + 5) = 18057;
          *(_BYTE *)(dword_4FC4E0 + 7) = v37;
          *(_BYTE *)(dword_4FC4E0 + 8) = 79;
          dword_4FC4E0 += 9;
        }
        goto LABEL_422;
      case 0xFu:
        v13 = 4 * (BYTE2(v7) & 0x1F);
        if ( v13 )
        {
          *(_BYTE *)dword_4FC4E0 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = (unsigned __int16)v7 << 16;
LABEL_273:
          *(_WORD *)(dword_4FC4E0 + 5) = 18057;
          *(_BYTE *)(dword_4FC4E0 + 7) = v13;
          *(_BYTE *)(dword_4FC4E0 + 8) = 79;
          dword_4FC4E0 += 9;
        }
        goto LABEL_422;
      case 0x10u:
        v90 = (v7 >> 21) & 0x1F;
        if ( v90 )
        {
          if ( v90 == 4 )
          {
            v91 = 4 * ((v7 >> 11) & 0x1F);
            if ( ArgList == 548880 )
              ui_error("bye pie\n");
            if ( v91 == 12 )
            {
              *(_WORD *)dword_4FC4E0 = 32393;
              *(_BYTE *)(dword_4FC4E0 + 2) = -112;
              *(_BYTE *)(dword_4FC4E0 + 3) = 87;
              *(_BYTE *)(dword_4FC4E0 + 4) = 86;
              *(_WORD *)(dword_4FC4E0 + 5) = 18119;
              *(_BYTE *)(dword_4FC4E0 + 7) = -116;
              *(_DWORD *)(dword_4FC4E0 + 8) = v7;
              v92 = (char *)op_MTC0;
LABEL_242:
              *(_BYTE *)(dword_4FC4E0 + 12) = -24;
LABEL_243:
              *(_DWORD *)(dword_4FC4E0 + 13) = &v92[-dword_4FC4E0 - 17];
              *(_BYTE *)(dword_4FC4E0 + 17) = 94;
              *(_BYTE *)(dword_4FC4E0 + 18) = 95;
              *(_BYTE *)(dword_4FC4E0 + 19) = 79;
              dword_4FC4E0 += 20;
            }
            else
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = 4 * (BYTE2(v7) & 0x1F);
              *(_WORD *)(dword_4FC4E0 + 3) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 5) = (v91 & 0x3F) - 108;
              *(_BYTE *)(dword_4FC4E0 + 6) = 79;
              dword_4FC4E0 += 7;
              if ( v91 == 48 || v91 == 52 )
              {
                *(_WORD *)dword_4FC4E0 = 18059;
                *(_BYTE *)(dword_4FC4E0 + 2) = -60;
                *(_BYTE *)(dword_4FC4E0 + 3) = 37;
                *(_DWORD *)(dword_4FC4E0 + 4) = 257;
                *(_BYTE *)(dword_4FC4E0 + 8) = 61;
                *(_DWORD *)(dword_4FC4E0 + 9) = 257;
                *(_BYTE *)(dword_4FC4E0 + 13) = 117;
                *(_BYTE *)(dword_4FC4E0 + 14) = 50;
                *(_WORD *)(dword_4FC4E0 + 15) = 18059;
                *(_BYTE *)(dword_4FC4E0 + 17) = -56;
                *(_BYTE *)(dword_4FC4E0 + 18) = 37;
                *(_DWORD *)(dword_4FC4E0 + 19) = 256;
                *(_BYTE *)(dword_4FC4E0 + 23) = 61;
                *(_DWORD *)(dword_4FC4E0 + 24) = 256;
                *(_BYTE *)(dword_4FC4E0 + 28) = 117;
                *(_BYTE *)(dword_4FC4E0 + 29) = 35;
                *(_WORD *)(dword_4FC4E0 + 30) = 18119;
                *(_BYTE *)(dword_4FC4E0 + 32) = -52;
                *(_DWORD *)(dword_4FC4E0 + 33) = ArgList;
                *(_WORD *)(dword_4FC4E0 + 37) = 18059;
                *(_BYTE *)(dword_4FC4E0 + 39) = -60;
                *(_WORD *)(dword_4FC4E0 + 40) = 26241;
                *(_BYTE *)(dword_4FC4E0 + 42) = -60;
                *(_DWORD *)(dword_4FC4E0 + 43) = -256;
                *(_WORD *)(dword_4FC4E0 + 47) = -7999;
                *(_BYTE *)(dword_4FC4E0 + 49) = 2;
                *(_BYTE *)(dword_4FC4E0 + 50) = 37;
                *(_DWORD *)(dword_4FC4E0 + 51) = 63;
                *(_WORD *)(dword_4FC4E0 + 55) = 17929;
                *(_BYTE *)(dword_4FC4E0 + 57) = -60;
                *(_BYTE *)(dword_4FC4E0 + 58) = -72;
                *(_DWORD *)(dword_4FC4E0 + 59) = (char *)dword_5164C4 + 128;
                *(_WORD *)(dword_4FC4E0 + 63) = 8447;
                dword_4FC4E0 += 65;
              }
              if ( v91 == 48 )
              {
                *(_BYTE *)dword_4FC4E0 = -95;
                *(_DWORD *)(dword_4FC4E0 + 1) = int_reg;
                *(_WORD *)(dword_4FC4E0 + 5) = 1315;
                *(_DWORD *)(dword_4FC4E0 + 7) = &int_mask;
                *(_BYTE *)(dword_4FC4E0 + 11) = -87;
                *(_DWORD *)(dword_4FC4E0 + 12) = 1019;
                *(_BYTE *)(dword_4FC4E0 + 16) = 116;
                *(_BYTE *)(dword_4FC4E0 + 17) = 22;
                *(_WORD *)(dword_4FC4E0 + 18) = 18059;
                *(_BYTE *)(dword_4FC4E0 + 20) = -60;
                *(_BYTE *)(dword_4FC4E0 + 21) = 37;
                *(_DWORD *)(dword_4FC4E0 + 22) = 1025;
                *(_BYTE *)(dword_4FC4E0 + 26) = 61;
                *(_DWORD *)(dword_4FC4E0 + 27) = 1025;
                *(_BYTE *)(dword_4FC4E0 + 31) = 117;
                *(_BYTE *)(dword_4FC4E0 + 32) = 7;
                *(_WORD *)(dword_4FC4E0 + 33) = 18119;
                *(_BYTE *)(dword_4FC4E0 + 35) = -44;
                *(_DWORD *)(dword_4FC4E0 + 36) = 0x80000000;
                dword_4FC4E0 += 40;
              }
            }
          }
          else
          {
            if ( v90 != 16 )
              fatal_error_with_message_box(" COP0 Opcode %02x UNK \n", (v7 >> 21) & 0x1F);
            *(_WORD *)v2 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = -60;
            *(_WORD *)(dword_4FC4E0 + 3) = 26241;
            *(_BYTE *)(dword_4FC4E0 + 5) = -60;
            *(_DWORD *)(dword_4FC4E0 + 6) = -16;
            *(_WORD *)(dword_4FC4E0 + 10) = -5951;
            *(_BYTE *)(dword_4FC4E0 + 12) = 2;
            *(_BYTE *)(dword_4FC4E0 + 13) = 37;
            *(_DWORD *)(dword_4FC4E0 + 14) = 15;
            *(_WORD *)(dword_4FC4E0 + 18) = 17929;
            *(_BYTE *)(dword_4FC4E0 + 20) = -60;
            *(_BYTE *)(dword_4FC4E0 + 21) = 79;
            dword_4FC4E0 += 22;
            *(_BYTE *)dword_4FC4E0 = -95;
            *(_DWORD *)(dword_4FC4E0 + 1) = int_reg;
            *(_WORD *)(dword_4FC4E0 + 5) = 1315;
            *(_DWORD *)(dword_4FC4E0 + 7) = &int_mask;
            *(_BYTE *)(dword_4FC4E0 + 11) = -87;
            *(_DWORD *)(dword_4FC4E0 + 12) = 1019;
            *(_BYTE *)(dword_4FC4E0 + 16) = 116;
            *(_BYTE *)(dword_4FC4E0 + 17) = 22;
            *(_WORD *)(dword_4FC4E0 + 18) = 18059;
            *(_BYTE *)(dword_4FC4E0 + 20) = -60;
            *(_BYTE *)(dword_4FC4E0 + 21) = 37;
            *(_DWORD *)(dword_4FC4E0 + 22) = 1025;
            *(_BYTE *)(dword_4FC4E0 + 26) = 61;
            *(_DWORD *)(dword_4FC4E0 + 27) = 1025;
            *(_BYTE *)(dword_4FC4E0 + 31) = 117;
            *(_BYTE *)(dword_4FC4E0 + 32) = 7;
            *(_WORD *)(dword_4FC4E0 + 33) = 18119;
            *(_BYTE *)(dword_4FC4E0 + 35) = -44;
            *(_DWORD *)(dword_4FC4E0 + 36) = 0x80000000;
            dword_4FC4E0 += 40;
          }
        }
        else
        {
          v93 = (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
          v94 = 4 * (BYTE2(v7) & 0x1F);
          if ( (_BYTE)v93 == 12 )
          {
            *(_WORD *)v2 = 32393;
            *(_BYTE *)(dword_4FC4E0 + 2) = -112;
            *(_BYTE *)(dword_4FC4E0 + 3) = 87;
            *(_BYTE *)(dword_4FC4E0 + 4) = 86;
            *(_WORD *)(dword_4FC4E0 + 5) = 18119;
            *(_BYTE *)(dword_4FC4E0 + 7) = -116;
            *(_DWORD *)(dword_4FC4E0 + 8) = v7;
            *(_BYTE *)(dword_4FC4E0 + 12) = -24;
            *(_DWORD *)(dword_4FC4E0 + 13) = (char *)op_MFC0 - dword_4FC4E0 - 17;
            *(_BYTE *)(dword_4FC4E0 + 17) = 94;
            *(_BYTE *)(dword_4FC4E0 + 18) = 95;
            *(_BYTE *)(dword_4FC4E0 + 19) = 79;
            dword_4FC4E0 += 20;
          }
          else if ( v94 )
          {
            *(_WORD *)dword_4FC4E0 = 18059;
            *(_BYTE *)(dword_4FC4E0 + 2) = (v93 & 0x3F) - 108;
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 5) = v94;
LABEL_253:
            *(_BYTE *)(dword_4FC4E0 + 6) = 79;
            dword_4FC4E0 += 7;
          }
        }
        goto LABEL_422;
      case 0x12u:
        switch ( (v7 >> 21) & 0x1F )
        {
          case 0u:
            if ( (v7 == 1208125440 || v7 == 1208127488 || v7 == 1208129536)
              && *(_DWORD *)((unsigned __int16)ArgList + mem_read_hooks[HIWORD(ArgList)]) == 6166570 )
            {
              v2[18] = -95;
              *(_DWORD *)(dword_4FC4E0 + 19) = (char *)&gte_regs + (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
              *(_WORD *)(dword_4FC4E0 + 23) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 25) = 4 * (BYTE2(v7) & 0x1F);
              *(_BYTE *)(dword_4FC4E0 + 26) = 79;
              *(_WORD *)dword_4FC4E0 = 18059;
              *(_BYTE *)(dword_4FC4E0 + 2) = 8;
              *(_WORD *)(dword_4FC4E0 + 3) = 17979;
              *(_BYTE *)(dword_4FC4E0 + 5) = 120;
              *(_WORD *)(dword_4FC4E0 + 6) = -25585;
              *(_BYTE *)(dword_4FC4E0 + 8) = -64;
              *(_BYTE *)(dword_4FC4E0 + 9) = 37;
              *(_DWORD *)(dword_4FC4E0 + 10) = 1;
              *(_WORD *)(dword_4FC4E0 + 14) = 18057;
              *(_BYTE *)(dword_4FC4E0 + 16) = 12;
              *(_BYTE *)(dword_4FC4E0 + 17) = 79;
              dword_4FC4E0 += 27;
              ArgList += 4;
              goto LABEL_422;
            }
            if ( a2 != 1 )
              goto LABEL_265;
            v95 = (unsigned __int16)*(_DWORD *)((unsigned __int16)(ArgList - 8) + mem_read_hooks[(ArgList - 8) >> 16]);
            if ( (v95 & 0x8000) != 0 )
              v95 |= 0xFFFF0000;
            if ( *(_DWORD *)((unsigned __int16)(ArgList + 4 * v95 - 4) + mem_read_hooks[(ArgList + 4 * v95 - 4) >> 16]) != 1216872448 )
            {
              v2 = (char *)dword_4FC4E0;
LABEL_265:
              v37 = 4 * (BYTE2(v7) & 0x1F);
              v96 = 4 * ((v7 >> 11) & 0x1F);
              if ( v37 )
              {
                if ( v96 != 124 && v96 != 116 )
                {
                  *v2 = -95;
                  *(_DWORD *)(dword_4FC4E0 + 1) = (char *)&gte_regs + (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
                  goto LABEL_203;
                }
                *(_WORD *)v2 = 32393;
                *(_BYTE *)(dword_4FC4E0 + 2) = -112;
                *(_BYTE *)(dword_4FC4E0 + 3) = 87;
                *(_BYTE *)(dword_4FC4E0 + 4) = 86;
                *(_WORD *)(dword_4FC4E0 + 5) = 18119;
                *(_BYTE *)(dword_4FC4E0 + 7) = -116;
                *(_DWORD *)(dword_4FC4E0 + 8) = v7;
                *(_BYTE *)(dword_4FC4E0 + 12) = -24;
                v92 = (char *)gte_exec_opcode;
                goto LABEL_243;
              }
              *v2 = 79;
              ++dword_4FC4E0;
            }
            goto LABEL_422;
          case 2u:
            v13 = 4 * (BYTE2(v7) & 0x1F);
            if ( v13 )
            {
              *v2 = -95;
              *(_DWORD *)(dword_4FC4E0 + 1) = (char *)gte_regs.ctrl + (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
              goto LABEL_273;
            }
LABEL_33:
            *v2 = 79;
            ++dword_4FC4E0;
            goto LABEL_422;
          case 4u:
            v97 = (v7 >> 11) & 0x1F;
            if ( v97 >= 0xEu && v97 <= 0x13u || v97 == 28 )
              goto LABEL_304;
            *v2 = 79;
            *(_WORD *)(dword_4FC4E0 + 1) = 18059;
            *(_BYTE *)(dword_4FC4E0 + 3) = 4 * (BYTE2(v7) & 0x1F);
            if ( v97 == 1 || v97 == 3 || v97 == 5 || v97 == 8 || v97 == 9 || v97 == 10 || v97 == 11 )
            {
              *(_WORD *)(dword_4FC4E0 + 4) = -16625;
              v98 = &gte_regs.data[v97];
              goto LABEL_286;
            }
            *(_BYTE *)(dword_4FC4E0 + 4) = -93;
            *(_DWORD *)(dword_4FC4E0 + 5) = (char *)&gte_regs + v97 * 4;
            dword_4FC4E0 += 9;
            goto LABEL_422;
          case 6u:
            *v2 = 79;
            v99 = (v7 >> 11) & 0x1F;
            *(_WORD *)(dword_4FC4E0 + 1) = 18059;
            *(_BYTE *)(dword_4FC4E0 + 3) = 4 * (BYTE2(v7) & 0x1F);
            if ( v99 == 4 || v99 == 12 || v99 == 20 || v99 == 26 || v99 == 27 || v99 == 29 || v99 == 30 )
            {
              *(_WORD *)(dword_4FC4E0 + 4) = -16625;
              v98 = &gte_regs.ctrl[v99];
LABEL_286:
              *(_BYTE *)(dword_4FC4E0 + 6) = -64;
              *(_BYTE *)(dword_4FC4E0 + 7) = -93;
              *(_DWORD *)(dword_4FC4E0 + 8) = v98;
              dword_4FC4E0 += 12;
            }
            else
            {
              *(_BYTE *)(dword_4FC4E0 + 4) = -93;
              *(_DWORD *)(dword_4FC4E0 + 5) = &gte_regs.ctrl[v99];
              dword_4FC4E0 += 9;
            }
            goto LABEL_422;
          default:
            v100 = v7 & 0x1FFFFFF;
            if ( (v7 & 0x1FFFFFF) > 0x280030 )
            {
              if ( v100 != 20971526 )
                goto LABEL_304;
              *(_WORD *)v2 = 1479;
              *(_DWORD *)(dword_4FC4E0 + 2) = &gte_regs.ctrl[31];
              *(_DWORD *)(dword_4FC4E0 + 6) = 0;
              *(_WORD *)(dword_4FC4E0 + 10) = -16625;
              *(_BYTE *)(dword_4FC4E0 + 12) = 5;
              *(_DWORD *)(dword_4FC4E0 + 13) = &gte_regs.data[13].s16.lo;
              *(_WORD *)(dword_4FC4E0 + 17) = -16625;
              *(_BYTE *)(dword_4FC4E0 + 19) = 13;
              *(_DWORD *)(dword_4FC4E0 + 20) = &gte_regs.data[14].s16.lo;
              *(_WORD *)(dword_4FC4E0 + 24) = -16625;
              *(_BYTE *)(dword_4FC4E0 + 26) = 21;
              *(_DWORD *)(dword_4FC4E0 + 27) = &gte_regs.data[12];
              *(_WORD *)(dword_4FC4E0 + 31) = -16085;
              *(_WORD *)(dword_4FC4E0 + 33) = -20721;
              *(_BYTE *)(dword_4FC4E0 + 35) = -62;
              *(_WORD *)(dword_4FC4E0 + 36) = -10101;
              *(_WORD *)(dword_4FC4E0 + 38) = -16625;
              *(_BYTE *)(dword_4FC4E0 + 40) = 5;
              *(_DWORD *)(dword_4FC4E0 + 41) = &gte_regs.data[12].s16.lo;
              *(_WORD *)(dword_4FC4E0 + 45) = -16625;
              *(_BYTE *)(dword_4FC4E0 + 47) = 21;
              *(_DWORD *)(dword_4FC4E0 + 48) = &gte_regs.data[13];
              *(_WORD *)(dword_4FC4E0 + 52) = -14293;
              *(_WORD *)(dword_4FC4E0 + 54) = -20721;
              *(_BYTE *)(dword_4FC4E0 + 56) = -54;
              *(_WORD *)(dword_4FC4E0 + 57) = -9981;
              *(_WORD *)(dword_4FC4E0 + 59) = -16625;
              *(_BYTE *)(dword_4FC4E0 + 61) = 13;
              *(_DWORD *)(dword_4FC4E0 + 62) = &gte_regs.data[13].s16.lo;
              *(_WORD *)(dword_4FC4E0 + 66) = -16625;
              *(_BYTE *)(dword_4FC4E0 + 68) = 21;
              *(_DWORD *)(dword_4FC4E0 + 69) = &gte_regs.data[14];
              *(_WORD *)(dword_4FC4E0 + 73) = -16085;
              *(_WORD *)(dword_4FC4E0 + 75) = -20721;
              *(_BYTE *)(dword_4FC4E0 + 77) = -62;
              *(_WORD *)(dword_4FC4E0 + 78) = -10237;
              *(_WORD *)(dword_4FC4E0 + 80) = -15477;
              *(_BYTE *)(dword_4FC4E0 + 82) = -93;
              *(_DWORD *)(dword_4FC4E0 + 83) = &gte_regs.data[24];
              *(_WORD *)(dword_4FC4E0 + 87) = 32653;
              *(_BYTE *)(dword_4FC4E0 + 89) = -4;
              dword_4FC4E0 += 90;
            }
            else
            {
              if ( (v7 & 0x1FFFFFF) == 0x280030 )
              {
                v101 = gte_rtpt;
              }
              else
              {
                if ( v100 != 1572865 && v100 != 1671169 )
                {
LABEL_304:
                  *(_WORD *)v2 = 32393;
                  *(_BYTE *)(dword_4FC4E0 + 2) = -112;
                  *(_BYTE *)(dword_4FC4E0 + 3) = 87;
                  *(_BYTE *)(dword_4FC4E0 + 4) = 86;
                  *(_WORD *)(dword_4FC4E0 + 5) = 18119;
                  *(_BYTE *)(dword_4FC4E0 + 7) = -116;
                  *(_DWORD *)(dword_4FC4E0 + 8) = v7;
                  v92 = (char *)gte_exec_opcode;
                  goto LABEL_242;
                }
                v101 = gte_rtps;
              }
              *v2 = -24;
              *(_DWORD *)(dword_4FC4E0 + 1) = (char *)v101 - dword_4FC4E0 - 5;
              *(_WORD *)(dword_4FC4E0 + 5) = 32653;
              *(_BYTE *)(dword_4FC4E0 + 7) = -4;
              dword_4FC4E0 += 8;
            }
LABEL_422:
            if ( v157 )
              return v158;
            v2 = (char *)dword_4FC4E0;
            v3 = a2;
            break;
        }
        break;
      case 0x20u:
        v102 = BYTE2(v7) & 0x1F;
        v103 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v104 = 4 * v102;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v103;
          v105 = (_BYTE *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v103;
          v105 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v105;
        *v105 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C0 - dword_4FC4E0 + 187;
        if ( !v104 )
        {
          dword_4FC4E0 += 5;
          goto LABEL_422;
        }
        *(_WORD *)(dword_4FC4E0 + 5) = -16881;
        goto LABEL_314;
      case 0x21u:
        v106 = BYTE2(v7) & 0x1F;
        v107 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v104 = 4 * v106;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v107;
          v108 = (_BYTE *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v107;
          v108 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v108;
        *v108 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C0 - dword_4FC4E0 + 315;
        if ( v104 )
        {
          *(_WORD *)(dword_4FC4E0 + 5) = -16625;
LABEL_314:
          *(_BYTE *)(dword_4FC4E0 + 7) = -64;
          *(_WORD *)(dword_4FC4E0 + 8) = 18057;
          *(_BYTE *)(dword_4FC4E0 + 10) = v104;
          dword_4FC4E0 += 11;
        }
        else
        {
          dword_4FC4E0 += 5;
        }
        goto LABEL_422;
      case 0x22u:
        v109 = BYTE2(v7) & 0x1F;
        v110 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v111 = 4 * v109;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(_DWORD *)(dword_4FC4E0 + 1) = v7;
        *(_WORD *)(dword_4FC4E0 + 5) = 17923;
        *(_BYTE *)(dword_4FC4E0 + 7) = v110;
        *(_WORD *)(dword_4FC4E0 + 8) = -10101;
        *(_WORD *)(dword_4FC4E0 + 10) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 12) = 3;
        *(_BYTE *)(dword_4FC4E0 + 16) = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        *(_BYTE *)(dword_4FC4E0 + 21) = -24;
        *(_DWORD *)(dword_4FC4E0 + 22) = (char *)dword_5164C0 - dword_4FC4E0 + 422;
        if ( !v111 )
        {
          dword_4FC4E0 += 26;
          goto LABEL_422;
        }
        *(_WORD *)(dword_4FC4E0 + 26) = 3211;
        *(_BYTE *)(dword_4FC4E0 + 28) = -99;
        *(_DWORD *)(dword_4FC4E0 + 29) = byte_4558BC;
        *(_WORD *)(dword_4FC4E0 + 33) = 20001;
        *(_BYTE *)(dword_4FC4E0 + 35) = v111;
        *(_WORD *)(dword_4FC4E0 + 36) = 3211;
        *(_BYTE *)(dword_4FC4E0 + 38) = -99;
        *(_DWORD *)(dword_4FC4E0 + 39) = byte_4558CC;
        *(_WORD *)(dword_4FC4E0 + 43) = -7981;
        goto LABEL_328;
      case 0x23u:
        v112 = BYTE2(v7) & 0x1F;
        v113 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v114 = 4 * v112;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v113;
          v115 = (_BYTE *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v113;
          v115 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v115;
        v116 = adjust_timing == 0;
        *v115 = -87;
        *(_DWORD *)(dword_4FC4E0 + 1) = 1602224128;
        *(_BYTE *)(dword_4FC4E0 + 5) = 117;
        if ( v116 )
        {
          *(_BYTE *)(dword_4FC4E0 + 6) = 17;
          *(_BYTE *)(dword_4FC4E0 + 7) = 37;
          *(_DWORD *)(dword_4FC4E0 + 8) = 0x1FFFFF;
          *(_BYTE *)(dword_4FC4E0 + 12) = 5;
          *(_DWORD *)(dword_4FC4E0 + 13) = ram;
          *(_WORD *)(dword_4FC4E0 + 17) = 32653;
          *(_BYTE *)(dword_4FC4E0 + 19) = -(char)dword_455945;
          *(_WORD *)(dword_4FC4E0 + 20) = 139;
          *(_BYTE *)(dword_4FC4E0 + 22) = -21;
          *(_BYTE *)(dword_4FC4E0 + 23) = 5;
          *(_BYTE *)(dword_4FC4E0 + 24) = -24;
          *(_DWORD *)(dword_4FC4E0 + 25) = (char *)dword_5164C0 - dword_4FC4E0 + 419;
          if ( v114 )
          {
            *(_WORD *)(dword_4FC4E0 + 29) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 31) = v114;
            dword_4FC4E0 += 32;
          }
          else
          {
            dword_4FC4E0 += 29;
          }
        }
        else
        {
          *(_BYTE *)(dword_4FC4E0 + 6) = 22;
          *(_BYTE *)(dword_4FC4E0 + 7) = 37;
          *(_DWORD *)(dword_4FC4E0 + 8) = 0x1FFFFF;
          *(_BYTE *)(dword_4FC4E0 + 12) = 5;
          *(_DWORD *)(dword_4FC4E0 + 13) = ram;
          *(_WORD *)(dword_4FC4E0 + 17) = 7563;
          *(_DWORD *)(dword_4FC4E0 + 19) = &dword_455945;
          *(_WORD *)(dword_4FC4E0 + 23) = -1237;
          *(_WORD *)(dword_4FC4E0 + 25) = 139;
          *(_BYTE *)(dword_4FC4E0 + 27) = -21;
          *(_BYTE *)(dword_4FC4E0 + 28) = 5;
          *(_BYTE *)(dword_4FC4E0 + 29) = -24;
          *(_DWORD *)(dword_4FC4E0 + 30) = (char *)dword_5164C0 - dword_4FC4E0 + 414;
          if ( v114 )
          {
            *(_WORD *)(dword_4FC4E0 + 34) = 18057;
            *(_BYTE *)(dword_4FC4E0 + 36) = v114;
            dword_4FC4E0 += 37;
          }
          else
          {
            dword_4FC4E0 += 34;
          }
        }
        goto LABEL_422;
      case 0x24u:
        if ( a2 == 1
          && v7 == -1820196858
          && *(_DWORD *)((unsigned __int16)(ArgList - 8) + mem_read_hooks[(ArgList - 8) >> 16]) == 65011720
          && *(_DWORD *)((unsigned __int16)(ArgList + 128) + mem_read_hooks[(ArgList + 128) >> 16]) == 608305167 )
        {
          dbg_print(" * warning: skullmonkeys trick enabled. \n");
          goto LABEL_422;
        }
        v117 = BYTE2(v7) & 0x1F;
        v118 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v119 = 4 * v117;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v118;
          v120 = (_BYTE *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v118;
          v120 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v120;
        *v120 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C0 - dword_4FC4E0 + 187;
        if ( !v119 )
        {
          dword_4FC4E0 += 5;
          goto LABEL_422;
        }
        *(_BYTE *)(dword_4FC4E0 + 5) = 37;
        *(_DWORD *)(dword_4FC4E0 + 6) = 255;
        goto LABEL_354;
      case 0x25u:
        v121 = BYTE2(v7) & 0x1F;
        v122 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v119 = 4 * v121;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v122;
          v123 = (_BYTE *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v122;
          v123 = (_BYTE *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v123;
        *v123 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C0 - dword_4FC4E0 + 315;
        if ( !v119 )
        {
          dword_4FC4E0 += 5;
          goto LABEL_422;
        }
        *(_BYTE *)(dword_4FC4E0 + 5) = 37;
        *(_DWORD *)(dword_4FC4E0 + 6) = 0xFFFF;
LABEL_354:
        *(_WORD *)(dword_4FC4E0 + 10) = 18057;
        *(_BYTE *)(dword_4FC4E0 + 12) = v119;
        goto LABEL_355;
      case 0x26u:
        v124 = BYTE2(v7) & 0x1F;
        v125 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v111 = 4 * v124;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(_DWORD *)(dword_4FC4E0 + 1) = v7;
        *(_WORD *)(dword_4FC4E0 + 5) = 17923;
        *(_BYTE *)(dword_4FC4E0 + 7) = v125;
        *(_WORD *)(dword_4FC4E0 + 8) = -10101;
        *(_WORD *)(dword_4FC4E0 + 10) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 12) = 3;
        *(_BYTE *)(dword_4FC4E0 + 16) = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        *(_BYTE *)(dword_4FC4E0 + 21) = -24;
        *(_DWORD *)(dword_4FC4E0 + 22) = (char *)dword_5164C0 - dword_4FC4E0 + 422;
        if ( v111 )
        {
          *(_WORD *)(dword_4FC4E0 + 26) = 0xC8B;
          *(_BYTE *)(dword_4FC4E0 + 28) = 0x9D;
          *(_DWORD *)(dword_4FC4E0 + 29) = byte_4558DC;
          *(_WORD *)(dword_4FC4E0 + 33) = 0x4E21;
          *(_BYTE *)(dword_4FC4E0 + 35) = v111;
          *(_WORD *)(dword_4FC4E0 + 36) = 0xC8B;
          *(_BYTE *)(dword_4FC4E0 + 38) = 0x9D;
          *(_DWORD *)(dword_4FC4E0 + 39) = byte_4558EC;
          *(_WORD *)(dword_4FC4E0 + 43) = 0xE8D3;
LABEL_328:
          *(_WORD *)(dword_4FC4E0 + 45) = 0x4609;
          *(_BYTE *)(dword_4FC4E0 + 47) = v111;
          dword_4FC4E0 += 48;
        }
        else
        {
          dword_4FC4E0 += 26;
        }
        goto LABEL_422;
      case 0x28u:
        v126 = BYTE2(v7) & 0x1F;
        v127 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v128 = 4 * v126;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v127;
          v129 = (_WORD *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v127;
          v129 = (_WORD *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v129;
        *v129 = 24203;
        *(_BYTE *)(dword_4FC4E0 + 2) = v128;
        *(_WORD *)(dword_4FC4E0 + 3) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 5) = 255;
        *(_BYTE *)(dword_4FC4E0 + 9) = -24;
        *(_DWORD *)(dword_4FC4E0 + 10) = (char *)dword_5164C0 - dword_4FC4E0 + 562;
        dword_4FC4E0 += 14;
        goto LABEL_422;
      case 0x29u:
        v130 = BYTE2(v7) & 0x1F;
        v131 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v132 = 4 * v130;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v131;
          v133 = (_WORD *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v131;
          v133 = (_WORD *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v133;
        *v133 = 24203;
        *(_BYTE *)(dword_4FC4E0 + 2) = v132;
        *(_WORD *)(dword_4FC4E0 + 3) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0xFFFF;
        *(_BYTE *)(dword_4FC4E0 + 9) = -24;
        *(_DWORD *)(dword_4FC4E0 + 10) = (char *)dword_5164C0 - dword_4FC4E0 + 754;
        dword_4FC4E0 += 14;
        goto LABEL_422;
      case 0x2Au:
        v134 = BYTE2(v7) & 0x1F;
        v135 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v136 = 4 * v134;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(_DWORD *)(dword_4FC4E0 + 1) = v7;
        *(_WORD *)(dword_4FC4E0 + 5) = 17923;
        *(_BYTE *)(dword_4FC4E0 + 7) = v135;
        *(_WORD *)(dword_4FC4E0 + 8) = -10101;
        *(_WORD *)(dword_4FC4E0 + 10) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 12) = 3;
        *(_BYTE *)(dword_4FC4E0 + 16) = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        *(_BYTE *)(dword_4FC4E0 + 21) = 80;
        *(_BYTE *)(dword_4FC4E0 + 22) = -24;
        *(_DWORD *)(dword_4FC4E0 + 23) = (char *)dword_5164C0 - dword_4FC4E0 + 421;
        *(_WORD *)(dword_4FC4E0 + 27) = 3211;
        *(_BYTE *)(dword_4FC4E0 + 29) = -99;
        *(_DWORD *)(dword_4FC4E0 + 30) = byte_4558FC;
        *(_WORD *)(dword_4FC4E0 + 34) = -16093;
        *(_WORD *)(dword_4FC4E0 + 36) = 3211;
        *(_BYTE *)(dword_4FC4E0 + 38) = -99;
        *(_DWORD *)(dword_4FC4E0 + 39) = byte_45590C;
        *(_WORD *)(dword_4FC4E0 + 43) = 24203;
        *(_BYTE *)(dword_4FC4E0 + 45) = v136;
        *(_WORD *)(dword_4FC4E0 + 46) = -5165;
        goto LABEL_384;
      case 0x2Bu:
        v137 = BYTE2(v7) & 0x1F;
        v138 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v139 = 4 * v137;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
          *(_WORD *)(dword_4FC4E0 + 5) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 7) = v138;
          v140 = (_WORD *)(dword_4FC4E0 + 8);
        }
        else
        {
          *(_WORD *)v2 = 18059;
          *(_BYTE *)(dword_4FC4E0 + 2) = v138;
          v140 = (_WORD *)(dword_4FC4E0 + 3);
        }
        dword_4FC4E0 = (int)v140;
        *v140 = 24203;
        *(_BYTE *)(dword_4FC4E0 + 2) = v139;
        *(_BYTE *)(dword_4FC4E0 + 3) = -24;
        *(_DWORD *)(dword_4FC4E0 + 4) = (char *)dword_5164C0 - dword_4FC4E0 + 952;
        v141 = (_BYTE *)(dword_4FC4E0 + 8);
        dword_4FC4E0 += 8;
        if ( a2 != 1 )
        {
          *v141 = -72;
          if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
            v142 = (ArgList & 0x7FFFF) + 0x200000;
          else
            v142 = ArgList & 0x1FFFFF;
          *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v142;
          *(_WORD *)(dword_4FC4E0 + 5) = 8447;
          dword_4FC4E0 += 7;
        }
        goto LABEL_422;
      case 0x2Eu:
        v143 = BYTE2(v7) & 0x1F;
        v144 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v145 = 4 * v143;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(_DWORD *)(dword_4FC4E0 + 1) = v7;
        *(_WORD *)(dword_4FC4E0 + 5) = 17923;
        *(_BYTE *)(dword_4FC4E0 + 7) = v144;
        *(_WORD *)(dword_4FC4E0 + 8) = -10101;
        *(_WORD *)(dword_4FC4E0 + 10) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 12) = 3;
        *(_BYTE *)(dword_4FC4E0 + 16) = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        *(_BYTE *)(dword_4FC4E0 + 21) = 80;
        *(_BYTE *)(dword_4FC4E0 + 22) = -24;
        *(_DWORD *)(dword_4FC4E0 + 23) = (char *)dword_5164C0 - dword_4FC4E0 + 421;
        *(_WORD *)(dword_4FC4E0 + 27) = 3211;
        *(_BYTE *)(dword_4FC4E0 + 29) = -99;
        *(_DWORD *)(dword_4FC4E0 + 30) = byte_45591C;
        *(_WORD *)(dword_4FC4E0 + 34) = -16093;
        *(_WORD *)(dword_4FC4E0 + 36) = 3211;
        *(_BYTE *)(dword_4FC4E0 + 38) = -99;
        *(_DWORD *)(dword_4FC4E0 + 39) = byte_45592C;
        *(_WORD *)(dword_4FC4E0 + 43) = 24203;
        *(_BYTE *)(dword_4FC4E0 + 45) = v145;
        *(_WORD *)(dword_4FC4E0 + 46) = -7213;
LABEL_384:
        *(_WORD *)(dword_4FC4E0 + 48) = -10229;
        *(_BYTE *)(dword_4FC4E0 + 50) = 88;
        *(_BYTE *)(dword_4FC4E0 + 51) = -24;
        *(_DWORD *)(dword_4FC4E0 + 52) = (char *)dword_5164C0 - dword_4FC4E0 + 904;
        dword_4FC4E0 += 56;
        goto LABEL_422;
      case 0x32u:
        v146 = 4 * (BYTE2(v7) & 0x1F);
        v147 = (unsigned __int16)v7;
        if ( (v7 & 0x8000) != 0 )
          v147 = v7 | 0xFFFF0000;
        if ( v146 >= 0x38u && v146 <= 0x4Cu || v146 == 112 )
        {
          *(_WORD *)v2 = 32393;
          *(_BYTE *)(dword_4FC4E0 + 2) = -112;
          *(_BYTE *)(dword_4FC4E0 + 3) = 87;
          *(_BYTE *)(dword_4FC4E0 + 4) = 86;
          *(_WORD *)(dword_4FC4E0 + 5) = 18119;
          *(_BYTE *)(dword_4FC4E0 + 7) = -116;
          *(_DWORD *)(dword_4FC4E0 + 8) = v7;
          v148 = (char *)op_LWC2;
          goto LABEL_414;
        }
        *v2 = -72;
        *(_DWORD *)(dword_4FC4E0 + 1) = v147;
        *(_WORD *)(dword_4FC4E0 + 5) = 17923;
        *(_BYTE *)(dword_4FC4E0 + 7) = 4 * ((v7 >> 21) & 0x1F);
        *(_BYTE *)(dword_4FC4E0 + 8) = -24;
        *(_DWORD *)(dword_4FC4E0 + 9) = (char *)dword_5164C0 - dword_4FC4E0 + 435;
        if ( v146 == 28 )
        {
LABEL_355:
          dword_4FC4E0 += 13;
        }
        else if ( v146 == 4 || v146 == 12 || v146 == 20 || v146 == 32 || v146 == 36 || v146 == 40 || v146 == 44 )
        {
          *(_WORD *)(dword_4FC4E0 + 13) = -16625;
          *(_BYTE *)(dword_4FC4E0 + 15) = -64;
          *(_BYTE *)(dword_4FC4E0 + 16) = -93;
          *(_DWORD *)(dword_4FC4E0 + 17) = (char *)&gte_regs + v146;
          dword_4FC4E0 += 21;
        }
        else
        {
          *(_BYTE *)(dword_4FC4E0 + 13) = -93;
          *(_DWORD *)(dword_4FC4E0 + 14) = (char *)&gte_regs + v146;
          dword_4FC4E0 += 18;
        }
        goto LABEL_422;
      case 0x3Au:
        v149 = 4 * (BYTE2(v7) & 0x1F);
        v150 = (unsigned __int16)v7;
        if ( (v7 & 0x8000) != 0 )
          v150 = v7 | 0xFFFF0000;
        if ( v149 == 124 || v149 == 116 )
        {
          *(_WORD *)v2 = 32393;
          *(_BYTE *)(dword_4FC4E0 + 2) = -112;
          *(_BYTE *)(dword_4FC4E0 + 3) = 87;
          *(_BYTE *)(dword_4FC4E0 + 4) = 86;
          *(_WORD *)(dword_4FC4E0 + 5) = 18119;
          *(_BYTE *)(dword_4FC4E0 + 7) = -116;
          *(_DWORD *)(dword_4FC4E0 + 8) = v7;
          v148 = (char *)op_SWC2;
LABEL_414:
          *(_BYTE *)(dword_4FC4E0 + 12) = -24;
          *(_DWORD *)(dword_4FC4E0 + 13) = &v148[-dword_4FC4E0 - 17];
          *(_BYTE *)(dword_4FC4E0 + 17) = 94;
          *(_BYTE *)(dword_4FC4E0 + 18) = 95;
          *(_WORD *)(dword_4FC4E0 + 19) = 32653;
          *(_BYTE *)(dword_4FC4E0 + 21) = -5;
          dword_4FC4E0 += 22;
        }
        else
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v150;
          *(_WORD *)(dword_4FC4E0 + 5) = 7563;
          *(_DWORD *)(dword_4FC4E0 + 7) = (char *)&gte_regs + (unsigned __int8)(4 * (BYTE2(v7) & 0x1F));
          *(_WORD *)(dword_4FC4E0 + 11) = 17923;
          *(_BYTE *)(dword_4FC4E0 + 13) = 4 * ((v7 >> 21) & 0x1F);
          *(_BYTE *)(dword_4FC4E0 + 14) = -24;
          *(_DWORD *)(dword_4FC4E0 + 15) = (char *)dword_5164C0 - dword_4FC4E0 + 941;
          dword_4FC4E0 += 19;
        }
        goto LABEL_422;
      default:
        fatal_error_with_message_box(
          " Opcode %02x UNK (PC %08x) (%d,%d)\n",
          v7 >> 26,
          ArgList - 4,
          dword_50C360,
          dword_50C364);
        return result;
    }
  }
  if ( v158 == 1 )
    fatal_error_with_message_box(" 1 compiled and??? pc %04x n:%d t:%d\n", ArgList, v3, 1);
  if ( v3 == 1 )
    fatal_error_with_message_box("dynarec problem (slot_in and recompiled) [%08x] [%d]\n", ArgList, 1);
  *v2 = -72;
  if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
    v156 = (ArgList & 0x7FFFF) + 0x200000;
  else
    v156 = ArgList & 0x1FFFFF;
  *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v156;
  *(_WORD *)(dword_4FC4E0 + 5) = 8447;
  dword_4FC4E0 += 7;
  return v158 - 1;
}
