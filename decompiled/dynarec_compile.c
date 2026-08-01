#include "pch.h"
int __cdecl dynarec_compile(unsigned int ArgList, int a2)
{
  uint8_t *v2; // ebx
  unsigned int v3; // esi
  unsigned int v4; // eax
  unsigned int v6; // eax
  unsigned int v7; // esi
  unsigned __int8 v8; // dl
  int v9; // ecx
  unsigned __int8 v10; // cl
  _DWORD *v11; // eax
  int v12; // ecx
  uint8_t v13; // al
  uint8_t v14; // cl
  uint8_t v15; // dl
  uint8_t v16; // dl
  uint8_t v17; // dl
  uint8_t v18; // al
  uint8_t v19; // cl
  uint8_t v20; // dl
  uint8_t v21; // cl
  uint8_t v22; // dl
  uint8_t v23; // cl
  uint8_t v24; // dl
  int result; // eax
  uint8_t v26; // cl
  uint8_t v27; // al
  uint8_t *v28; // edx
  int v29; // eax
  uint8_t *v30; // eax
  uint8_t v31; // al
  uint8_t v32; // dl
  uint8_t v33; // dl
  uint8_t v34; // dl
  uint8_t v35; // dl
  uint8_t v36; // dl
  uint8_t v37; // al
  uint8_t v38; // dl
  uint8_t v39; // cl
  uint8_t v40; // al
  char v41; // cl
  uint8_t v42; // cl
  char v43; // cl
  uint8_t v44; // cl
  unsigned int v45; // eax
  char v46; // cl
  uint8_t v47; // cl
  char v48; // cl
  uint8_t v49; // cl
  unsigned int v50; // eax
  int v51; // esi
  uint8_t *v52; // ecx
  int v53; // eax
  int v54; // esi
  int v55; // eax
  char v56; // cl
  char v57; // al
  uint8_t v58; // cl
  uint8_t v59; // al
  uint8_t *v60; // edx
  uint8_t *v61; // eax
  char v62; // cl
  char v63; // al
  uint8_t v64; // cl
  uint8_t v65; // al
  uint8_t *v66; // edx
  uint8_t *v67; // eax
  char v68; // cl
  uint8_t v69; // cl
  char v70; // cl
  uint8_t v71; // cl
  char v72; // cl
  char v73; // al
  uint8_t v74; // cl
  uint8_t *v75; // ecx
  char v76; // cl
  char v77; // al
  uint8_t v78; // cl
  uint8_t v79; // al
  uint8_t v80; // al
  char v81; // cl
  uint8_t v82; // cl
  uint8_t *v83; // ecx
  char v84; // cl
  uint8_t v85; // cl
  uint8_t *v86; // ecx
  char v87; // cl
  uint8_t v88; // cl
  uint8_t *v89; // ecx
  int v90; // eax
  char v91; // bl
  _BYTE *v92; // ecx
  int v93; // eax
  uint8_t v94; // cl
  int v95; // eax
  char v96; // cl
  unsigned __int8 v97; // al
  GTE_REG *v98; // eax
  unsigned __int8 v99; // al
  int v100; // eax
  int (*v101)(); // edx
  char v102; // cl
  uint8_t v103; // al
  uint8_t v104; // cl
  uint8_t *v105; // eax
  char v106; // cl
  uint8_t v107; // al
  uint8_t *v108; // eax
  char v109; // al
  uint8_t v110; // cl
  uint8_t v111; // al
  char v112; // al
  uint8_t v113; // cl
  uint8_t v114; // al
  uint8_t *v115; // ecx
  bool v116; // zf
  char v117; // cl
  uint8_t v118; // al
  uint8_t v119; // cl
  uint8_t *v120; // eax
  char v121; // cl
  uint8_t v122; // al
  uint8_t *v123; // eax
  char v124; // al
  uint8_t v125; // cl
  char v126; // cl
  uint8_t v127; // al
  uint8_t v128; // cl
  uint8_t *v129; // eax
  char v130; // cl
  uint8_t v131; // al
  uint8_t v132; // cl
  uint8_t *v133; // eax
  char v134; // cl
  uint8_t v135; // al
  uint8_t v136; // cl
  char v137; // cl
  uint8_t v138; // al
  uint8_t v139; // cl
  uint8_t *v140; // eax
  uint8_t *v141; // ecx
  unsigned int v142; // eax
  char v143; // cl
  uint8_t v144; // al
  uint8_t v145; // cl
  unsigned __int8 v146; // al
  unsigned int v147; // edx
  _BYTE *v148; // ecx
  char v149; // dl
  unsigned int v150; // ecx
  uint8_t *v151; // eax
  int v152; // eax
  int v153; // eax
  unsigned int v154; // eax
  int v155; // eax
  unsigned int v156; // ebp
  char v157; // [esp+13h] [ebp-25h]
  int v158; // [esp+14h] [ebp-24h]
  uint8_t *v159; // [esp+18h] [ebp-20h]
  unsigned __int8 ArgLista; // [esp+3Ch] [ebp+4h]

  v2 = code_ptr;
  v3 = a2;
  v4 = 0;
  v157 = 0;
  v158 = 0;
  v159 = nullptr;
  if ( a2 != 1 && code_ptr - (_BYTE *)recomp_buffer >= 2080768 )
  {
    do
    {
      *(_DWORD *)((char *)recomp_code_base + v4) = recomp_buffer;
      v4 += 4;
    }
    while ( v4 < 0x280000 );
    v3 = a2;
    code_ptr = (uint8_t *)recomp_buffer + 1216;
    v2 = (uint8_t *)recomp_buffer + 1216;
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
    if ( *(LPVOID *)((char *)recomp_code_base + v6) != recomp_buffer && !v157 )
      break;
    v7 = *(_DWORD *)((unsigned __int16)ArgList + mem_read_hooks[HIWORD(ArgList)]);
    if ( a2 != 1 )
    {
      *(_DWORD *)((char *)recomp_code_base + v6) = v2;
      if ( v158 == 1 )
        v159 = code_ptr;
      *(_DWORD *)((char *)recomp_metadata + v6) = v159;
      v2 = code_ptr;
    }
    if ( byte_4F831C )
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
            if ( (unsigned __int8)(v8 + 1) < (unsigned __int8)byte_4F831C )
            {
              v11 = (_DWORD *)(8 * v10 + 5991868);
              v12 = (unsigned __int8)(byte_4F831C - v10);
              do
              {
                *(v11 - 1) = v11[1];
                *v11 = v11[2];
                v11 += 2;
                --v12;
              }
              while ( v12 );
            }
            --byte_4F831C;
          }
        }
        ArgLista = ++v8;
      }
      while ( v8 < (unsigned __int8)byte_4F831C );
      v2 = code_ptr;
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
              *(_WORD *)code_ptr = 26305;
              goto LABEL_45;
            }
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = v15;
            *(_WORD *)(code_ptr + 3) = -7999;
            goto LABEL_118;
          case 2u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v14 = (v7 >> 6) & 0x1F;
            v16 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v16 == v13 )
            {
              *(_WORD *)code_ptr = 28353;
              goto LABEL_45;
            }
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = v16;
            *(_WORD *)(code_ptr + 3) = -5951;
            goto LABEL_118;
          case 3u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v14 = (v7 >> 6) & 0x1F;
            v17 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v17 != v13 )
            {
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v17;
              *(_WORD *)(code_ptr + 3) = -1855;
              goto LABEL_118;
            }
            *(_WORD *)code_ptr = 32449;
LABEL_45:
            code_ptr[2] = v13;
            code_ptr[3] = v14;
            code_ptr[4] = 79;
            code_ptr += 5;
            goto LABEL_422;
          case 4u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v19 = 4 * ((v7 >> 21) & 0x1F);
            v20 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v20 == v18 )
            {
              *(_WORD *)code_ptr = 20107;
              code_ptr[2] = v19;
              *(_WORD *)(code_ptr + 3) = -7807;
              *(_DWORD *)(code_ptr + 5) = 31;
              *(_WORD *)(code_ptr + 9) = 26323;
              goto LABEL_50;
            }
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = v20;
            *(_WORD *)(code_ptr + 3) = 20107;
            code_ptr[5] = v19;
            *((_WORD *)code_ptr + 3) = -7807;
            *((_DWORD *)code_ptr + 2) = 31;
            *((_WORD *)code_ptr + 6) = -7981;
            goto LABEL_130;
          case 6u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v21 = 4 * ((v7 >> 21) & 0x1F);
            v22 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v22 == v18 )
            {
              *(_WORD *)code_ptr = 20107;
              code_ptr[2] = v21;
              *(_WORD *)(code_ptr + 3) = -7807;
              *(_DWORD *)(code_ptr + 5) = 31;
              *(_WORD *)(code_ptr + 9) = 28371;
              goto LABEL_50;
            }
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = v22;
            *(_WORD *)(code_ptr + 3) = 20107;
            code_ptr[5] = v21;
            *((_WORD *)code_ptr + 3) = -7807;
            *((_DWORD *)code_ptr + 2) = 31;
            *((_WORD *)code_ptr + 6) = -5933;
            goto LABEL_130;
          case 7u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v23 = 4 * ((v7 >> 21) & 0x1F);
            v24 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v24 == v18 )
            {
              *(_WORD *)code_ptr = 20107;
              code_ptr[2] = v23;
              *(_WORD *)(code_ptr + 3) = -7807;
              *(_DWORD *)(code_ptr + 5) = 31;
              *(_WORD *)(code_ptr + 9) = 32467;
LABEL_50:
              code_ptr[11] = v18;
              code_ptr[12] = 79;
              code_ptr += 13;
            }
            else
            {
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v24;
              *(_WORD *)(code_ptr + 3) = 20107;
              code_ptr[5] = v23;
              *((_WORD *)code_ptr + 3) = -7807;
              *((_DWORD *)code_ptr + 2) = 31;
              *((_WORD *)code_ptr + 6) = -1837;
LABEL_130:
              *((_WORD *)code_ptr + 7) = 18057;
              code_ptr[16] = v18;
              code_ptr[17] = 79;
              code_ptr += 18;
            }
            goto LABEL_422;
          case 8u:
            if ( a2 == 1 )
              goto LABEL_422;
            *(_WORD *)v2 = 32267;
            code_ptr[2] = -44;
            *(_WORD *)(code_ptr + 3) = 0xC7F7;
            *(_DWORD *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *code_ptr = 79;
            *(_WORD *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * ((v7 >> 21) & 0x1F);
            code_ptr[4] = -24;
            *(_DWORD *)(code_ptr + 5) = (_BYTE *)recomp_buffer - code_ptr + 119;
            code_ptr[9] = 80;
            code_ptr += 10;
            dynarec_compile(ArgList, 1u);
            *code_ptr = 88;
            *(_WORD *)(code_ptr + 1) = 8447;
            code_ptr += 3;
            *(_BYTE *)patch_offset_ptr = (_BYTE)code_ptr - patch_offset_ptr - 1;
            *(_WORD *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(_DWORD *)(code_ptr + 3) = ArgList - 4;
            *(_WORD *)(code_ptr + 7) = 32393;
            code_ptr[9] = -112;
            code_ptr[10] = -24;
            *(_DWORD *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
            *(_WORD *)(code_ptr + 15) = 0xC7F7;
            *(_DWORD *)(code_ptr + 17) = 0x40000000;
            code_ptr[21] = 116;
            code_ptr[22] = 8;
            *(_WORD *)(code_ptr + 23) = -14463;
            *(_DWORD *)(code_ptr + 25) = cpu_speed_scale;
            *(_WORD *)(code_ptr + 29) = 8447;
            *(_WORD *)(code_ptr + 31) = 0xF781;
            *(_DWORD *)(code_ptr + 33) = 0x80000000;
            goto LABEL_62;
          case 9u:
            if ( a2 == 1 )
              goto LABEL_422;
            *(_WORD *)v2 = 32267;
            code_ptr[2] = -44;
            *(_WORD *)(code_ptr + 3) = 0xC7F7;
            *(_DWORD *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            v26 = 4 * ((v7 >> 21) & 0x1F);
            v27 = 4 * ((v7 >> 11) & 0x1F);
            v28 = code_ptr + 11;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            if ( v27 == v26 )
              dword_4FF9E8 |= 0x800000u;
            *v28 = 79;
            if ( v27 )
            {
              *(_WORD *)(code_ptr + 1) = 18119;
              code_ptr[3] = v27;
              v29 = ArgList + 4;
              if ( (ArgList & 0xF0000000) == 0 )
                v29 |= 0x80000000;
              *((_DWORD *)code_ptr + 1) = v29;
              *((_WORD *)code_ptr + 4) = 18059;
              code_ptr[10] = v26;
              code_ptr[11] = -24;
              *((_DWORD *)code_ptr + 3) = (_BYTE *)recomp_buffer - code_ptr + 112;
              code_ptr[16] = 80;
              v30 = code_ptr + 17;
            }
            else
            {
              *(_WORD *)(code_ptr + 1) = 18059;
              code_ptr[3] = v26;
              code_ptr[4] = -24;
              *(_DWORD *)(code_ptr + 5) = (_BYTE *)recomp_buffer - code_ptr + 119;
              code_ptr[9] = 80;
              v30 = code_ptr + 10;
            }
            code_ptr = v30;
            dynarec_compile(ArgList, 1u);
            *code_ptr = 88;
            *(_WORD *)(code_ptr + 1) = 8447;
            code_ptr += 3;
            *(_BYTE *)patch_offset_ptr = (_BYTE)code_ptr - patch_offset_ptr - 1;
            *(_WORD *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(_DWORD *)(code_ptr + 3) = ArgList - 4;
            *(_WORD *)(code_ptr + 7) = 32393;
            code_ptr[9] = -112;
            code_ptr[10] = -24;
            *(_DWORD *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
            *(_WORD *)(code_ptr + 15) = 0xC7F7;
            *(_DWORD *)(code_ptr + 17) = 0x40000000;
            code_ptr[21] = 116;
            code_ptr[22] = 8;
            *(_WORD *)(code_ptr + 23) = -14463;
            *(_DWORD *)(code_ptr + 25) = cpu_speed_scale;
            *(_WORD *)(code_ptr + 29) = 8447;
            *(_WORD *)(code_ptr + 31) = -2175;
            *(_DWORD *)(code_ptr + 33) = 0x80000000;
LABEL_62:
            *(_WORD *)(code_ptr + 37) = 8447;
            goto LABEL_63;
          case 0xCu:
            *(_WORD *)v2 = 18119;
            code_ptr[2] = -44;
            *(_DWORD *)(code_ptr + 3) = 0;
            code_ptr += 7;
            *(_WORD *)code_ptr = 18119;
            code_ptr[2] = -52;
            *(_DWORD *)(code_ptr + 3) = ArgList - 4;
            *(_WORD *)(code_ptr + 7) = 18119;
            code_ptr[9] = -56;
            *(_DWORD *)(code_ptr + 10) = 32;
            *((_WORD *)code_ptr + 7) = 18059;
            code_ptr[16] = -60;
            *(_WORD *)(code_ptr + 17) = 26241;
            code_ptr[19] = -60;
            *((_DWORD *)code_ptr + 5) = -64;
            *((_WORD *)code_ptr + 12) = -7999;
            code_ptr[26] = 2;
            code_ptr[27] = 37;
            *((_DWORD *)code_ptr + 7) = 63;
            *((_WORD *)code_ptr + 16) = 17929;
            code_ptr[34] = -60;
            code_ptr[35] = -72;
            *((_DWORD *)code_ptr + 9) = (char *)recomp_code_base + 128;
            *((_WORD *)code_ptr + 20) = 8447;
            code_ptr[42] = 79;
            code_ptr += 43;
            goto LABEL_422;
          case 0xDu:
            dword_4FF9E8 |= 0x2000u;
            goto LABEL_422;
          case 0x10u:
            v31 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v31 )
              goto LABEL_422;
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = -120;
            goto LABEL_75;
          case 0x11u:
            *(_WORD *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(code_ptr + 3) = 18057;
            code_ptr[5] = -120;
            code_ptr[6] = 79;
            code_ptr += 7;
            goto LABEL_422;
          case 0x12u:
            v31 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v31 )
              goto LABEL_422;
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = -124;
LABEL_75:
            *(_WORD *)(code_ptr + 3) = 18057;
            code_ptr[5] = v31;
            goto LABEL_253;
          case 0x13u:
            *(_WORD *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(code_ptr + 3) = 18057;
            code_ptr[5] = -124;
            code_ptr[6] = 79;
            code_ptr += 7;
            goto LABEL_422;
          case 0x18u:
            *(_WORD *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(code_ptr + 3) = 28407;
            goto LABEL_81;
          case 0x19u:
            *(_WORD *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(code_ptr + 3) = 26359;
LABEL_81:
            code_ptr[5] = 4 * (BYTE2(v7) & 0x1F);
            *((_WORD *)code_ptr + 3) = 18057;
            code_ptr[8] = -124;
            *(_WORD *)(code_ptr + 9) = 22153;
            code_ptr[11] = -120;
            code_ptr[12] = 79;
            code_ptr += 13;
            goto LABEL_422;
          case 0x1Au:
            *(_WORD *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            code_ptr[3] = -103;
            *((_WORD *)code_ptr + 2) = 20107;
            code_ptr[6] = 4 * (BYTE2(v7) & 0x1F);
            *(_WORD *)(code_ptr + 7) = -13947;
            *(_WORD *)(code_ptr + 9) = 2676;
            *(_WORD *)(code_ptr + 11) = -1545;
            *(_WORD *)(code_ptr + 13) = 18057;
            code_ptr[15] = -124;
            *((_WORD *)code_ptr + 8) = 22153;
            code_ptr[18] = -120;
            *(_WORD *)(code_ptr + 19) = 6123;
            *(_WORD *)(code_ptr + 21) = 18057;
            code_ptr[23] = -120;
            code_ptr[24] = -70;
            *(_DWORD *)(code_ptr + 25) = -1;
            code_ptr[29] = -87;
            *(_DWORD *)(code_ptr + 30) = 0x80000000;
            *((_WORD *)code_ptr + 17) = 1396;
            code_ptr[36] = -70;
            *(_DWORD *)(code_ptr + 37) = 1;
            *(_WORD *)(code_ptr + 41) = 22153;
            code_ptr[43] = -124;
            code_ptr[44] = 79;
            code_ptr += 45;
            goto LABEL_422;
          case 0x1Bu:
            *(_WORD *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(code_ptr + 3) = -11727;
            *(_WORD *)(code_ptr + 5) = 20107;
            code_ptr[7] = 4 * (BYTE2(v7) & 0x1F);
            *((_WORD *)code_ptr + 4) = -13947;
            *((_WORD *)code_ptr + 5) = 2676;
            *((_WORD *)code_ptr + 6) = -3593;
            *((_WORD *)code_ptr + 7) = 18057;
            code_ptr[16] = -124;
            *(_WORD *)(code_ptr + 17) = 22153;
            code_ptr[19] = -120;
            *((_WORD *)code_ptr + 10) = 3051;
            *((_WORD *)code_ptr + 11) = 18057;
            code_ptr[24] = -120;
            code_ptr[25] = -70;
            *(_DWORD *)(code_ptr + 26) = -1;
            *((_WORD *)code_ptr + 15) = 22153;
            code_ptr[32] = -124;
            code_ptr[33] = 79;
            code_ptr += 34;
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
                *(_WORD *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(_WORD *)(code_ptr + 3) = 17921;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v32;
              *(_WORD *)(code_ptr + 3) = 17923;
              goto LABEL_118;
            }
            *(_WORD *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)code_ptr + 1) = 17923;
            code_ptr[4] = v14;
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
                *(_WORD *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(_WORD *)(code_ptr + 3) = 17961;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v33;
              *(_WORD *)(code_ptr + 3) = 17963;
              goto LABEL_118;
            }
            *(_WORD *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)code_ptr + 1) = 17963;
            code_ptr[4] = v14;
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
                *(_WORD *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(_WORD *)(code_ptr + 3) = 17953;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v34;
              *(_WORD *)(code_ptr + 3) = 17955;
              goto LABEL_118;
            }
            *(_WORD *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)code_ptr + 1) = 17955;
            code_ptr[4] = v14;
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
                *(_WORD *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(_WORD *)(code_ptr + 3) = 17929;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v35;
              *(_WORD *)(code_ptr + 3) = 17931;
              goto LABEL_118;
            }
            *(_WORD *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)code_ptr + 1) = 17931;
            code_ptr[4] = v14;
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
                *(_WORD *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(_WORD *)(code_ptr + 3) = 17969;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v36;
              *(_WORD *)(code_ptr + 3) = 17971;
LABEL_118:
              code_ptr[5] = v14;
              *((_WORD *)code_ptr + 3) = 18057;
              code_ptr[8] = v13;
              code_ptr[9] = 79;
              code_ptr += 10;
            }
            else
            {
              *(_WORD *)code_ptr = -16335;
              if ( v14 )
              {
                *((_WORD *)code_ptr + 1) = 17971;
                code_ptr[4] = v14;
                goto LABEL_273;
              }
LABEL_121:
              *((_WORD *)code_ptr + 1) = 18057;
              code_ptr[4] = v13;
              code_ptr[5] = 79;
              code_ptr += 6;
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
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = v38;
              *(_WORD *)(code_ptr + 3) = 17931;
              code_ptr[5] = v39;
              *((_WORD *)code_ptr + 3) = -12041;
              *((_WORD *)code_ptr + 4) = 18057;
              code_ptr[10] = v37;
              code_ptr[11] = 79;
              code_ptr += 12;
              goto LABEL_422;
            }
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = v39;
            *(_WORD *)(code_ptr + 3) = -12041;
            break;
          case 0x2Au:
            v40 = 4 * ((v7 >> 11) & 0x1F);
            if ( v40 )
            {
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
              *(_WORD *)(code_ptr + 3) = 17979;
              code_ptr[5] = 4 * (BYTE2(v7) & 0x1F);
              *((_WORD *)code_ptr + 3) = -25585;
              code_ptr[8] = -64;
              code_ptr[9] = 37;
              *(_DWORD *)(code_ptr + 10) = 1;
              *((_WORD *)code_ptr + 7) = 18057;
              code_ptr[16] = v40;
              code_ptr[17] = 79;
              code_ptr += 18;
            }
            goto LABEL_422;
          case 0x2Bu:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(code_ptr + 3) = 17979;
            code_ptr[5] = 4 * (BYTE2(v7) & 0x1F);
            *((_WORD *)code_ptr + 3) = -28145;
            code_ptr[8] = -64;
            code_ptr[9] = 37;
            *(_DWORD *)(code_ptr + 10) = 1;
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
            code_ptr[2] = -44;
            *(_WORD *)(code_ptr + 3) = -14345;
            *(_DWORD *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(_WORD *)code_ptr = -16335;
            code_ptr[2] = 79;
            *(_WORD *)(code_ptr + 3) = 17977;
            code_ptr[5] = v42;
            code_ptr[6] = 124;
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
            code_ptr[2] = -44;
            *(_WORD *)(code_ptr + 3) = -14345;
            *(_DWORD *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(_WORD *)code_ptr = -16335;
            code_ptr[2] = 79;
            *(_WORD *)(code_ptr + 3) = 17977;
            code_ptr[5] = v44;
            code_ptr[6] = 125;
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
            code_ptr[2] = -44;
            *(_WORD *)(code_ptr + 3) = -14345;
            *(_DWORD *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(_WORD *)code_ptr = 18119;
            code_ptr[2] = 124;
            *(_DWORD *)(code_ptr + 3) = (ArgList + 4) | 0x80000000;
            *(_WORD *)(code_ptr + 7) = -16335;
            code_ptr[9] = 79;
            *((_WORD *)code_ptr + 5) = 17977;
            code_ptr[12] = v47;
            code_ptr[13] = 124;
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
            code_ptr[2] = -44;
            *(_WORD *)(code_ptr + 3) = -14345;
            *(_DWORD *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(_WORD *)code_ptr = 18119;
            code_ptr[2] = 124;
            *(_DWORD *)(code_ptr + 3) = (ArgList + 4) | 0x80000000;
            *(_WORD *)(code_ptr + 7) = -16335;
            code_ptr[9] = 79;
            *((_WORD *)code_ptr + 5) = 17977;
            code_ptr[12] = v49;
            code_ptr[13] = 125;
LABEL_151:
            code_ptr[14] = 7;
            code_ptr[15] = -72;
            if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
              v50 = (ArgList & 0x7FFFF) + 0x200000;
            else
              v50 = ArgList & 0x1FFFFF;
            *((_DWORD *)code_ptr + 4) = (char *)recomp_code_base + v50;
            *((_WORD *)code_ptr + 10) = 8447;
            v151 = code_ptr + 22;
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
          if ( !byte_455946 || ((v51 ^ (ArgList - 4)) & 0xFFFFFF) != 0 )
          {
            *(_WORD *)code_ptr = 32267;
            code_ptr[2] = -44;
            *(_WORD *)(code_ptr + 3) = -14345;
            *(_DWORD *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            v52 = code_ptr + 10;
            code_ptr += 11;
            patch_offset_ptr = (int)v52;
            *code_ptr++ = 79;
            dynarec_compile(ArgList, 1u);
            *code_ptr = -72;
            if ( (v51 & 0xFFF00000 | ArgList & 0xF0000000) == 0xBFC00000 )
              v53 = (v51 & 0x7FFFF) + 0x200000;
            else
              v53 = v51 & 0x1FFFFF;
            *(_DWORD *)(code_ptr + 1) = (char *)recomp_code_base + v53;
            *(_WORD *)(code_ptr + 5) = 8447;
            code_ptr += 7;
            *(_BYTE *)patch_offset_ptr = (_BYTE)code_ptr - patch_offset_ptr - 1;
            *(_WORD *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(_DWORD *)(code_ptr + 3) = ArgList - 4;
            *(_WORD *)(code_ptr + 7) = 32393;
            code_ptr[9] = -112;
            code_ptr[10] = -24;
            *(_DWORD *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
            *(_WORD *)(code_ptr + 15) = -14345;
            *(_DWORD *)(code_ptr + 17) = 0x40000000;
            code_ptr[21] = 116;
            code_ptr[22] = 8;
            *(_WORD *)(code_ptr + 23) = -14463;
            *(_DWORD *)(code_ptr + 25) = cpu_speed_scale;
            *(_WORD *)(code_ptr + 29) = 8447;
            *(_WORD *)(code_ptr + 31) = -2175;
            *(_DWORD *)(code_ptr + 33) = 0x80000000;
            *(_WORD *)(code_ptr + 37) = 8447;
            code_ptr += 39;
            ArgList = v51 | ArgList & 0xF0000000;
          }
        }
        goto LABEL_422;
      case 3u:
        if ( a2 != 1 )
        {
          *(_WORD *)code_ptr = 32267;
          code_ptr[2] = -44;
          *(_WORD *)(code_ptr + 3) = -14345;
          *(_DWORD *)(code_ptr + 5) = 0x80000000;
          code_ptr[9] = 117;
          v54 = 4 * (v7 & 0x3FFFFFF);
          patch_offset_ptr = (int)(code_ptr + 10);
          code_ptr += 11;
          *code_ptr = 79;
          *(_WORD *)(code_ptr + 1) = 18119;
          code_ptr[3] = 124;
          if ( (ArgList & 0xF0000000) != 0 )
            *((_DWORD *)code_ptr + 1) = ArgList + 4;
          else
            *((_DWORD *)code_ptr + 1) = (ArgList + 4) | 0x80000000;
          code_ptr += 8;
          dynarec_compile(ArgList, 1u);
          *code_ptr = -72;
          if ( (v54 & 0xFFF00000 | ArgList & 0xF0000000) == 0xBFC00000 )
            v55 = (v54 & 0x7FFFF) + 0x200000;
          else
            v55 = v54 & 0x1FFFFF;
          *(_DWORD *)(code_ptr + 1) = (char *)recomp_code_base + v55;
          *(_WORD *)(code_ptr + 5) = 8447;
          code_ptr += 7;
          *(_BYTE *)patch_offset_ptr = (_BYTE)code_ptr - patch_offset_ptr - 1;
          *(_WORD *)code_ptr = 18119;
          code_ptr[2] = 0x80;
          *(_DWORD *)(code_ptr + 3) = ArgList - 4;
          *(_WORD *)(code_ptr + 7) = 32393;
          code_ptr[9] = -112;
          code_ptr[10] = -24;
          *(_DWORD *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
          *(_WORD *)(code_ptr + 15) = -14345;
          *(_DWORD *)(code_ptr + 17) = 0x40000000;
          code_ptr[21] = 116;
          code_ptr[22] = 8;
          *(_WORD *)(code_ptr + 23) = -14463;
          *(_DWORD *)(code_ptr + 25) = cpu_speed_scale;
          *(_WORD *)(code_ptr + 29) = 8447;
          *(_WORD *)(code_ptr + 31) = -2175;
          *(_DWORD *)(code_ptr + 33) = 0x80000000;
          *(_WORD *)(code_ptr + 37) = 8447;
          ArgList = v54 | ArgList & 0xF0000000;
          code_ptr += 39;
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
        code_ptr[2] = -44;
        *(_WORD *)(code_ptr + 3) = -14345;
        *(_DWORD *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        v60 = code_ptr + 11;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        if ( v59 )
        {
          *(_WORD *)v60 = 18059;
          code_ptr[2] = v59;
          v61 = code_ptr + 3;
        }
        else
        {
          *(_WORD *)v60 = -16335;
          v61 = code_ptr + 2;
        }
        code_ptr = v61;
        *v61 = 79;
        *(_WORD *)(code_ptr + 1) = 17977;
        code_ptr[3] = v58;
        code_ptr[4] = 116;
        goto LABEL_436;
      case 5u:
        if ( a2 == 1
          || byte_455946
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
        *(_WORD *)code_ptr = 32267;
        code_ptr[2] = -44;
        *(_WORD *)(code_ptr + 3) = -14345;
        *(_DWORD *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        v66 = code_ptr + 11;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        if ( v65 )
        {
          *(_WORD *)v66 = 18059;
          code_ptr[2] = v65;
          v67 = code_ptr + 3;
        }
        else
        {
          *(_WORD *)v66 = -16335;
          v67 = code_ptr + 2;
        }
        code_ptr = v67;
        *v67 = 79;
        *(_WORD *)(code_ptr + 1) = 17977;
        code_ptr[3] = v64;
        code_ptr[4] = 117;
LABEL_436:
        code_ptr[5] = 7;
        code_ptr[6] = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v154 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v154 = ArgList & 0x1FFFFF;
        *(_DWORD *)(code_ptr + 7) = (char *)recomp_code_base + v154;
        *(_WORD *)(code_ptr + 11) = 8447;
        code_ptr += 13;
        dynarec_compile(ArgList, 1u);
        if ( !v7 )
          v7 = 1;
        *code_ptr = -72;
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
        code_ptr[2] = -44;
        *(_WORD *)(code_ptr + 3) = -14345;
        *(_DWORD *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        *(_WORD *)code_ptr = -16335;
        code_ptr[2] = 79;
        *(_WORD *)(code_ptr + 3) = 17977;
        code_ptr[5] = v69;
        code_ptr[6] = 126;
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
        code_ptr[2] = -44;
        *(_WORD *)(code_ptr + 3) = -14345;
        *(_DWORD *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        *(_WORD *)code_ptr = -16335;
        code_ptr[2] = 79;
        *(_WORD *)(code_ptr + 3) = 17977;
        code_ptr[5] = v71;
        code_ptr[6] = 127;
LABEL_141:
        code_ptr[7] = 7;
        code_ptr[8] = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v45 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v45 = ArgList & 0x1FFFFF;
        *(_DWORD *)(code_ptr + 9) = (char *)recomp_code_base + v45;
        *(_WORD *)(code_ptr + 13) = 8447;
        v151 = code_ptr + 15;
LABEL_428:
        code_ptr = v151;
        dynarec_compile(ArgList, 1u);
        if ( !v7 )
          v7 = 1;
        *code_ptr = -72;
        v152 = ArgList + 4 * v7;
        if ( (v152 & 0xFFF00000) == 0xBFC00000 )
          v153 = (v152 & 0x7FFFF) + 0x200000;
        else
          v153 = v152 & 0x1FFFFF;
LABEL_447:
        *(_DWORD *)(code_ptr + 1) = (char *)recomp_code_base + v153;
        *(_WORD *)(code_ptr + 5) = 8447;
        code_ptr += 7;
        *(_BYTE *)patch_offset_ptr = (_BYTE)code_ptr - patch_offset_ptr - 1;
        *(_WORD *)code_ptr = 18119;
        code_ptr[2] = 0x80;
        *(_DWORD *)(code_ptr + 3) = ArgList - 4;
        *(_WORD *)(code_ptr + 7) = 32393;
        code_ptr[9] = -112;
        code_ptr[10] = -24;
        *(_DWORD *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
        *(_WORD *)(code_ptr + 15) = -14345;
        *(_DWORD *)(code_ptr + 17) = 0x40000000;
        code_ptr[21] = 116;
        code_ptr[22] = 8;
        *(_WORD *)(code_ptr + 23) = -14463;
        *(_DWORD *)(code_ptr + 25) = cpu_speed_scale;
        *(_WORD *)(code_ptr + 29) = 8447;
        *(_WORD *)(code_ptr + 31) = -2175;
        *(_DWORD *)(code_ptr + 33) = 0x80000000;
        *(_WORD *)(code_ptr + 37) = 8447;
LABEL_63:
        code_ptr += 39;
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
          *(_WORD *)code_ptr = 18049;
          goto LABEL_197;
        }
        if ( v74 )
        {
          *(_WORD *)code_ptr = 18059;
          code_ptr[2] = v74;
          v75 = code_ptr + 3;
        }
        else
        {
          *(_WORD *)code_ptr = -16335;
          v75 = code_ptr + 2;
        }
        code_ptr = v75;
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
          *(_WORD *)code_ptr = 18059;
          code_ptr[2] = v78;
          code_ptr[3] = 61;
          *((_DWORD *)code_ptr + 1) = v7;
          *((_WORD *)code_ptr + 4) = -25585;
          code_ptr[10] = -64;
          code_ptr[11] = 37;
          *((_DWORD *)code_ptr + 3) = 1;
          *((_WORD *)code_ptr + 8) = 18057;
          code_ptr[18] = v79;
          code_ptr[19] = 79;
          code_ptr += 20;
        }
        goto LABEL_422;
      case 0xBu:
        v80 = 4 * (BYTE2(v7) & 0x1F);
        if ( v80 )
        {
          *(_WORD *)code_ptr = 18059;
          code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
          code_ptr[3] = 61;
          *((_DWORD *)code_ptr + 1) = (unsigned __int16)v7;
          *((_WORD *)code_ptr + 4) = -28145;
          code_ptr[10] = -64;
          code_ptr[11] = 37;
          *((_DWORD *)code_ptr + 3) = 1;
          *((_WORD *)code_ptr + 8) = 18057;
          code_ptr[18] = v80;
          code_ptr[19] = 79;
          code_ptr += 20;
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
          *(_WORD *)code_ptr = 26241;
          goto LABEL_197;
        }
        if ( v82 )
        {
          *(_WORD *)code_ptr = 18059;
          code_ptr[2] = v82;
          v83 = code_ptr + 3;
          code_ptr += 3;
        }
        else
        {
          *(_WORD *)code_ptr = -16335;
          v83 = code_ptr + 2;
          code_ptr += 2;
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
          *(_WORD *)code_ptr = 20097;
          goto LABEL_197;
        }
        if ( v85 )
        {
          *(_WORD *)code_ptr = 18059;
          code_ptr[2] = v85;
          v86 = code_ptr + 3;
          code_ptr += 3;
        }
        else
        {
          *(_WORD *)code_ptr = -16335;
          v86 = code_ptr + 2;
          code_ptr += 2;
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
          *(_WORD *)code_ptr = 30337;
LABEL_197:
          code_ptr[2] = v37;
          *(_DWORD *)(code_ptr + 3) = v7;
          code_ptr[7] = 79;
          code_ptr += 8;
        }
        else
        {
          if ( v88 )
          {
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = v88;
            v89 = code_ptr + 3;
            code_ptr += 3;
          }
          else
          {
            *(_WORD *)code_ptr = -16335;
            v89 = code_ptr + 2;
            code_ptr += 2;
          }
          *v89 = 53;
LABEL_202:
          *(_DWORD *)(code_ptr + 1) = v7;
LABEL_203:
          *(_WORD *)(code_ptr + 5) = 18057;
          code_ptr[7] = v37;
          code_ptr[8] = 79;
          code_ptr += 9;
        }
        goto LABEL_422;
      case 0xFu:
        v13 = 4 * (BYTE2(v7) & 0x1F);
        if ( v13 )
        {
          *code_ptr = -72;
          *(_DWORD *)(code_ptr + 1) = (unsigned __int16)v7 << 16;
LABEL_273:
          *(_WORD *)(code_ptr + 5) = 18057;
          code_ptr[7] = v13;
          code_ptr[8] = 79;
          code_ptr += 9;
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
              *(_WORD *)code_ptr = 32393;
              code_ptr[2] = -112;
              code_ptr[3] = 87;
              code_ptr[4] = 86;
              *(_WORD *)(code_ptr + 5) = 18119;
              code_ptr[7] = -116;
              *((_DWORD *)code_ptr + 2) = v7;
              v92 = op_MTC0;
LABEL_242:
              code_ptr[12] = -24;
LABEL_243:
              *(_DWORD *)(code_ptr + 13) = v92 - code_ptr - 17;
              code_ptr[17] = 94;
              code_ptr[18] = 95;
              code_ptr[19] = 79;
              code_ptr += 20;
            }
            else
            {
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = 4 * (BYTE2(v7) & 0x1F);
              *(_WORD *)(code_ptr + 3) = 18057;
              code_ptr[5] = (v91 & 0x3F) - 108;
              code_ptr[6] = 79;
              code_ptr += 7;
              if ( v91 == 48 || v91 == 52 )
              {
                *(_WORD *)code_ptr = 18059;
                code_ptr[2] = -60;
                code_ptr[3] = 37;
                *((_DWORD *)code_ptr + 1) = 257;
                code_ptr[8] = 61;
                *(_DWORD *)(code_ptr + 9) = 257;
                code_ptr[13] = 117;
                code_ptr[14] = 50;
                *(_WORD *)(code_ptr + 15) = 18059;
                code_ptr[17] = -56;
                code_ptr[18] = 37;
                *(_DWORD *)(code_ptr + 19) = 256;
                code_ptr[23] = 61;
                *((_DWORD *)code_ptr + 6) = 256;
                code_ptr[28] = 117;
                code_ptr[29] = 35;
                *((_WORD *)code_ptr + 15) = 18119;
                code_ptr[32] = -52;
                *(_DWORD *)(code_ptr + 33) = ArgList;
                *(_WORD *)(code_ptr + 37) = 18059;
                code_ptr[39] = -60;
                *((_WORD *)code_ptr + 20) = 26241;
                code_ptr[42] = -60;
                *(_DWORD *)(code_ptr + 43) = -256;
                *(_WORD *)(code_ptr + 47) = -7999;
                code_ptr[49] = 2;
                code_ptr[50] = 37;
                *(_DWORD *)(code_ptr + 51) = 63;
                *(_WORD *)(code_ptr + 55) = 17929;
                code_ptr[57] = -60;
                code_ptr[58] = -72;
                *(_DWORD *)(code_ptr + 59) = (char *)recomp_code_base + 128;
                *(_WORD *)(code_ptr + 63) = 8447;
                code_ptr += 65;
              }
              if ( v91 == 48 )
              {
                *code_ptr = -95;
                *(_DWORD *)(code_ptr + 1) = int_reg;
                *(_WORD *)(code_ptr + 5) = 1315;
                *(_DWORD *)(code_ptr + 7) = &int_mask;
                code_ptr[11] = -87;
                *((_DWORD *)code_ptr + 3) = 1019;
                code_ptr[16] = 116;
                code_ptr[17] = 22;
                *((_WORD *)code_ptr + 9) = 18059;
                code_ptr[20] = -60;
                code_ptr[21] = 37;
                *(_DWORD *)(code_ptr + 22) = 1025;
                code_ptr[26] = 61;
                *(_DWORD *)(code_ptr + 27) = 1025;
                code_ptr[31] = 117;
                code_ptr[32] = 7;
                *(_WORD *)(code_ptr + 33) = 18119;
                code_ptr[35] = -44;
                *((_DWORD *)code_ptr + 9) = 0x80000000;
                code_ptr += 40;
              }
            }
          }
          else
          {
            if ( v90 != 16 )
              fatal_error_with_message_box(" COP0 Opcode %02x UNK \n", (v7 >> 21) & 0x1F);
            *(_WORD *)v2 = 18059;
            code_ptr[2] = -60;
            *(_WORD *)(code_ptr + 3) = 26241;
            code_ptr[5] = -60;
            *(_DWORD *)(code_ptr + 6) = -16;
            *((_WORD *)code_ptr + 5) = -5951;
            code_ptr[12] = 2;
            code_ptr[13] = 37;
            *(_DWORD *)(code_ptr + 14) = 15;
            *((_WORD *)code_ptr + 9) = 17929;
            code_ptr[20] = -60;
            code_ptr[21] = 79;
            code_ptr += 22;
            *code_ptr = -95;
            *(_DWORD *)(code_ptr + 1) = int_reg;
            *(_WORD *)(code_ptr + 5) = 1315;
            *(_DWORD *)(code_ptr + 7) = &int_mask;
            code_ptr[11] = -87;
            *((_DWORD *)code_ptr + 3) = 1019;
            code_ptr[16] = 116;
            code_ptr[17] = 22;
            *((_WORD *)code_ptr + 9) = 18059;
            code_ptr[20] = -60;
            code_ptr[21] = 37;
            *(_DWORD *)(code_ptr + 22) = 1025;
            code_ptr[26] = 61;
            *(_DWORD *)(code_ptr + 27) = 1025;
            code_ptr[31] = 117;
            code_ptr[32] = 7;
            *(_WORD *)(code_ptr + 33) = 18119;
            code_ptr[35] = -44;
            *((_DWORD *)code_ptr + 9) = 0x80000000;
            code_ptr += 40;
          }
        }
        else
        {
          v93 = (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
          v94 = 4 * (BYTE2(v7) & 0x1F);
          if ( (_BYTE)v93 == 12 )
          {
            *(_WORD *)v2 = 32393;
            code_ptr[2] = -112;
            code_ptr[3] = 87;
            code_ptr[4] = 86;
            *(_WORD *)(code_ptr + 5) = 18119;
            code_ptr[7] = -116;
            *((_DWORD *)code_ptr + 2) = v7;
            code_ptr[12] = -24;
            *(_DWORD *)(code_ptr + 13) = (char *)op_MFC0 - (char *)code_ptr - 17;
            code_ptr[17] = 94;
            code_ptr[18] = 95;
            code_ptr[19] = 79;
            code_ptr += 20;
          }
          else if ( v94 )
          {
            *(_WORD *)code_ptr = 18059;
            code_ptr[2] = (v93 & 0x3F) - 108;
            *(_WORD *)(code_ptr + 3) = 18057;
            code_ptr[5] = v94;
LABEL_253:
            code_ptr[6] = 79;
            code_ptr += 7;
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
              *(_DWORD *)(code_ptr + 19) = (char *)&gte_regs + (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
              *(_WORD *)(code_ptr + 23) = 18057;
              code_ptr[25] = 4 * (BYTE2(v7) & 0x1F);
              code_ptr[26] = 79;
              *(_WORD *)code_ptr = 18059;
              code_ptr[2] = 8;
              *(_WORD *)(code_ptr + 3) = 17979;
              code_ptr[5] = 120;
              *((_WORD *)code_ptr + 3) = -25585;
              code_ptr[8] = -64;
              code_ptr[9] = 37;
              *(_DWORD *)(code_ptr + 10) = 1;
              *((_WORD *)code_ptr + 7) = 18057;
              code_ptr[16] = 12;
              code_ptr[17] = 79;
              code_ptr += 27;
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
              v2 = code_ptr;
LABEL_265:
              v37 = 4 * (BYTE2(v7) & 0x1F);
              v96 = 4 * ((v7 >> 11) & 0x1F);
              if ( v37 )
              {
                if ( v96 != 124 && v96 != 116 )
                {
                  *v2 = -95;
                  *(_DWORD *)(code_ptr + 1) = (char *)&gte_regs + (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
                  goto LABEL_203;
                }
                *(_WORD *)v2 = 32393;
                code_ptr[2] = -112;
                code_ptr[3] = 87;
                code_ptr[4] = 86;
                *(_WORD *)(code_ptr + 5) = 18119;
                code_ptr[7] = -116;
                *((_DWORD *)code_ptr + 2) = v7;
                code_ptr[12] = -24;
                v92 = gte_exec_opcode;
                goto LABEL_243;
              }
              *v2 = 79;
              ++code_ptr;
            }
            goto LABEL_422;
          case 2u:
            v13 = 4 * (BYTE2(v7) & 0x1F);
            if ( v13 )
            {
              *v2 = -95;
              *(_DWORD *)(code_ptr + 1) = (char *)gte_regs.ctrl + (unsigned __int8)(4 * ((v7 >> 11) & 0x1F));
              goto LABEL_273;
            }
LABEL_33:
            *v2 = 79;
            ++code_ptr;
            goto LABEL_422;
          case 4u:
            v97 = (v7 >> 11) & 0x1F;
            if ( v97 >= 0xEu && v97 <= 0x13u || v97 == 28 )
              goto LABEL_304;
            *v2 = 79;
            *(_WORD *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * (BYTE2(v7) & 0x1F);
            if ( v97 == 1 || v97 == 3 || v97 == 5 || v97 == 8 || v97 == 9 || v97 == 10 || v97 == 11 )
            {
              *((_WORD *)code_ptr + 2) = -16625;
              v98 = &gte_regs.data[v97];
              goto LABEL_286;
            }
            code_ptr[4] = -93;
            *(_DWORD *)(code_ptr + 5) = (char *)&gte_regs + v97 * 4;
            code_ptr += 9;
            goto LABEL_422;
          case 6u:
            *v2 = 79;
            v99 = (v7 >> 11) & 0x1F;
            *(_WORD *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * (BYTE2(v7) & 0x1F);
            if ( v99 == 4 || v99 == 12 || v99 == 20 || v99 == 26 || v99 == 27 || v99 == 29 || v99 == 30 )
            {
              *((_WORD *)code_ptr + 2) = -16625;
              v98 = &gte_regs.ctrl[v99];
LABEL_286:
              code_ptr[6] = -64;
              code_ptr[7] = -93;
              *((_DWORD *)code_ptr + 2) = v98;
              code_ptr += 12;
            }
            else
            {
              code_ptr[4] = -93;
              *(_DWORD *)(code_ptr + 5) = &gte_regs.ctrl[v99];
              code_ptr += 9;
            }
            goto LABEL_422;
          default:
            v100 = v7 & 0x1FFFFFF;
            if ( (v7 & 0x1FFFFFF) > 0x280030 )
            {
              if ( v100 != 20971526 )
                goto LABEL_304;
              *(_WORD *)v2 = 1479;
              *(_DWORD *)(code_ptr + 2) = &gte_regs.ctrl[31];
              *(_DWORD *)(code_ptr + 6) = 0;
              *((_WORD *)code_ptr + 5) = -16625;
              code_ptr[12] = 5;
              *(_DWORD *)(code_ptr + 13) = &gte_regs.data[13].s16.lo;
              *(_WORD *)(code_ptr + 17) = -16625;
              code_ptr[19] = 13;
              *((_DWORD *)code_ptr + 5) = &gte_regs.data[14].s16.lo;
              *((_WORD *)code_ptr + 12) = -16625;
              code_ptr[26] = 21;
              *(_DWORD *)(code_ptr + 27) = &gte_regs.data[12];
              *(_WORD *)(code_ptr + 31) = -16085;
              *(_WORD *)(code_ptr + 33) = -20721;
              code_ptr[35] = -62;
              *((_WORD *)code_ptr + 18) = -10101;
              *((_WORD *)code_ptr + 19) = -16625;
              code_ptr[40] = 5;
              *(_DWORD *)(code_ptr + 41) = &gte_regs.data[12].s16.lo;
              *(_WORD *)(code_ptr + 45) = -16625;
              code_ptr[47] = 21;
              *((_DWORD *)code_ptr + 12) = &gte_regs.data[13];
              *((_WORD *)code_ptr + 26) = -14293;
              *((_WORD *)code_ptr + 27) = -20721;
              code_ptr[56] = -54;
              *(_WORD *)(code_ptr + 57) = -9981;
              *(_WORD *)(code_ptr + 59) = -16625;
              code_ptr[61] = 13;
              *(_DWORD *)(code_ptr + 62) = &gte_regs.data[13].s16.lo;
              *((_WORD *)code_ptr + 33) = -16625;
              code_ptr[68] = 21;
              *(_DWORD *)(code_ptr + 69) = &gte_regs.data[14];
              *(_WORD *)(code_ptr + 73) = -16085;
              *(_WORD *)(code_ptr + 75) = -20721;
              code_ptr[77] = -62;
              *((_WORD *)code_ptr + 39) = -10237;
              *((_WORD *)code_ptr + 40) = -15477;
              code_ptr[82] = -93;
              *(_DWORD *)(code_ptr + 83) = &gte_regs.data[24];
              *(_WORD *)(code_ptr + 87) = 32653;
              code_ptr[89] = -4;
              code_ptr += 90;
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
                  code_ptr[2] = -112;
                  code_ptr[3] = 87;
                  code_ptr[4] = 86;
                  *(_WORD *)(code_ptr + 5) = 18119;
                  code_ptr[7] = -116;
                  *((_DWORD *)code_ptr + 2) = v7;
                  v92 = gte_exec_opcode;
                  goto LABEL_242;
                }
                v101 = gte_rtps;
              }
              *v2 = -24;
              *(_DWORD *)(code_ptr + 1) = (char *)v101 - (char *)code_ptr - 5;
              *(_WORD *)(code_ptr + 5) = 32653;
              code_ptr[7] = -4;
              code_ptr += 8;
            }
LABEL_422:
            if ( v157 )
              return v158;
            v2 = code_ptr;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v103;
          v105 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v103;
          v105 = code_ptr + 3;
        }
        code_ptr = v105;
        *v105 = -24;
        *(_DWORD *)(code_ptr + 1) = (_BYTE *)recomp_buffer - code_ptr + 187;
        if ( !v104 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        *(_WORD *)(code_ptr + 5) = -16881;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v107;
          v108 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v107;
          v108 = code_ptr + 3;
        }
        code_ptr = v108;
        *v108 = -24;
        *(_DWORD *)(code_ptr + 1) = (_BYTE *)recomp_buffer - code_ptr + 315;
        if ( v104 )
        {
          *(_WORD *)(code_ptr + 5) = -16625;
LABEL_314:
          code_ptr[7] = -64;
          *((_WORD *)code_ptr + 4) = 18057;
          code_ptr[10] = v104;
          code_ptr += 11;
        }
        else
        {
          code_ptr += 5;
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
        *(_DWORD *)(code_ptr + 1) = v7;
        *(_WORD *)(code_ptr + 5) = 17923;
        code_ptr[7] = v110;
        *((_WORD *)code_ptr + 4) = -10101;
        *((_WORD *)code_ptr + 5) = -7295;
        *((_DWORD *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(_DWORD *)(code_ptr + 17) = -4;
        code_ptr[21] = -24;
        *(_DWORD *)(code_ptr + 22) = (_BYTE *)recomp_buffer - code_ptr + 422;
        if ( !v111 )
        {
          code_ptr += 26;
          goto LABEL_422;
        }
        *((_WORD *)code_ptr + 13) = 3211;
        code_ptr[28] = -99;
        *(_DWORD *)(code_ptr + 29) = byte_4558BC;
        *(_WORD *)(code_ptr + 33) = 20001;
        code_ptr[35] = v111;
        *((_WORD *)code_ptr + 18) = 3211;
        code_ptr[38] = -99;
        *(_DWORD *)(code_ptr + 39) = byte_4558CC;
        *(_WORD *)(code_ptr + 43) = -7981;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v113;
          v115 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v113;
          v115 = code_ptr + 3;
        }
        code_ptr = v115;
        v116 = adjust_timing == 0;
        *v115 = -87;
        *(_DWORD *)(code_ptr + 1) = 1602224128;
        code_ptr[5] = 117;
        if ( v116 )
        {
          code_ptr[6] = 17;
          code_ptr[7] = 37;
          *((_DWORD *)code_ptr + 2) = 0x1FFFFF;
          code_ptr[12] = 5;
          *(_DWORD *)(code_ptr + 13) = ram;
          *(_WORD *)(code_ptr + 17) = 32653;
          code_ptr[19] = -byte_455945;
          *((_WORD *)code_ptr + 10) = 139;
          code_ptr[22] = -21;
          code_ptr[23] = 5;
          code_ptr[24] = -24;
          *(_DWORD *)(code_ptr + 25) = (_BYTE *)recomp_buffer - code_ptr + 419;
          if ( v114 )
          {
            *(_WORD *)(code_ptr + 29) = 18057;
            code_ptr[31] = v114;
            code_ptr += 32;
          }
          else
          {
            code_ptr += 29;
          }
        }
        else
        {
          code_ptr[6] = 22;
          code_ptr[7] = 37;
          *((_DWORD *)code_ptr + 2) = 0x1FFFFF;
          code_ptr[12] = 5;
          *(_DWORD *)(code_ptr + 13) = ram;
          *(_WORD *)(code_ptr + 17) = 7563;
          *(_DWORD *)(code_ptr + 19) = &byte_455945;
          *(_WORD *)(code_ptr + 23) = -1237;
          *(_WORD *)(code_ptr + 25) = 139;
          code_ptr[27] = -21;
          code_ptr[28] = 5;
          code_ptr[29] = -24;
          *(_DWORD *)(code_ptr + 30) = (_BYTE *)recomp_buffer - code_ptr + 414;
          if ( v114 )
          {
            *((_WORD *)code_ptr + 17) = 18057;
            code_ptr[36] = v114;
            code_ptr += 37;
          }
          else
          {
            code_ptr += 34;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v118;
          v120 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v118;
          v120 = code_ptr + 3;
        }
        code_ptr = v120;
        *v120 = -24;
        *(_DWORD *)(code_ptr + 1) = (_BYTE *)recomp_buffer - code_ptr + 187;
        if ( !v119 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        code_ptr[5] = 37;
        *(_DWORD *)(code_ptr + 6) = 255;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v122;
          v123 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v122;
          v123 = code_ptr + 3;
        }
        code_ptr = v123;
        *v123 = -24;
        *(_DWORD *)(code_ptr + 1) = (_BYTE *)recomp_buffer - code_ptr + 315;
        if ( !v119 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        code_ptr[5] = 37;
        *(_DWORD *)(code_ptr + 6) = 0xFFFF;
LABEL_354:
        *((_WORD *)code_ptr + 5) = 18057;
        code_ptr[12] = v119;
        goto LABEL_355;
      case 0x26u:
        v124 = BYTE2(v7) & 0x1F;
        v125 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v111 = 4 * v124;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(_DWORD *)(code_ptr + 1) = v7;
        *(_WORD *)(code_ptr + 5) = 17923;
        code_ptr[7] = v125;
        *((_WORD *)code_ptr + 4) = -10101;
        *((_WORD *)code_ptr + 5) = -7295;
        *((_DWORD *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(_DWORD *)(code_ptr + 17) = -4;
        code_ptr[21] = -24;
        *(_DWORD *)(code_ptr + 22) = (_BYTE *)recomp_buffer - code_ptr + 422;
        if ( v111 )
        {
          *((_WORD *)code_ptr + 13) = 0xC8B;
          code_ptr[28] = 0x9D;
          *(_DWORD *)(code_ptr + 29) = byte_4558DC;
          *(_WORD *)(code_ptr + 33) = 0x4E21;
          code_ptr[35] = v111;
          *((_WORD *)code_ptr + 18) = 0xC8B;
          code_ptr[38] = 0x9D;
          *(_DWORD *)(code_ptr + 39) = byte_4558EC;
          *(_WORD *)(code_ptr + 43) = 0xE8D3;
LABEL_328:
          *(_WORD *)(code_ptr + 45) = 0x4609;
          code_ptr[47] = v111;
          code_ptr += 48;
        }
        else
        {
          code_ptr += 26;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v127;
          v129 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v127;
          v129 = code_ptr + 3;
        }
        code_ptr = v129;
        *(_WORD *)v129 = 24203;
        code_ptr[2] = v128;
        *(_WORD *)(code_ptr + 3) = -7295;
        *(_DWORD *)(code_ptr + 5) = 255;
        code_ptr[9] = -24;
        *(_DWORD *)(code_ptr + 10) = (_BYTE *)recomp_buffer - code_ptr + 562;
        code_ptr += 14;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v131;
          v133 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v131;
          v133 = code_ptr + 3;
        }
        code_ptr = v133;
        *(_WORD *)v133 = 24203;
        code_ptr[2] = v132;
        *(_WORD *)(code_ptr + 3) = -7295;
        *(_DWORD *)(code_ptr + 5) = 0xFFFF;
        code_ptr[9] = -24;
        *(_DWORD *)(code_ptr + 10) = (_BYTE *)recomp_buffer - code_ptr + 754;
        code_ptr += 14;
        goto LABEL_422;
      case 0x2Au:
        v134 = BYTE2(v7) & 0x1F;
        v135 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (unsigned __int16)v7;
        v136 = 4 * v134;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(_DWORD *)(code_ptr + 1) = v7;
        *(_WORD *)(code_ptr + 5) = 17923;
        code_ptr[7] = v135;
        *((_WORD *)code_ptr + 4) = -10101;
        *((_WORD *)code_ptr + 5) = -7295;
        *((_DWORD *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(_DWORD *)(code_ptr + 17) = -4;
        code_ptr[21] = 80;
        code_ptr[22] = -24;
        *(_DWORD *)(code_ptr + 23) = (_BYTE *)recomp_buffer - code_ptr + 421;
        *(_WORD *)(code_ptr + 27) = 3211;
        code_ptr[29] = -99;
        *(_DWORD *)(code_ptr + 30) = byte_4558FC;
        *((_WORD *)code_ptr + 17) = -16093;
        *((_WORD *)code_ptr + 18) = 3211;
        code_ptr[38] = -99;
        *(_DWORD *)(code_ptr + 39) = byte_45590C;
        *(_WORD *)(code_ptr + 43) = 24203;
        code_ptr[45] = v136;
        *((_WORD *)code_ptr + 23) = -5165;
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
          *(_DWORD *)(code_ptr + 1) = v7;
          *(_WORD *)(code_ptr + 5) = 17923;
          code_ptr[7] = v138;
          v140 = code_ptr + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          code_ptr[2] = v138;
          v140 = code_ptr + 3;
        }
        code_ptr = v140;
        *(_WORD *)v140 = 24203;
        code_ptr[2] = v139;
        code_ptr[3] = -24;
        *((_DWORD *)code_ptr + 1) = (_BYTE *)recomp_buffer - code_ptr + 952;
        v141 = code_ptr + 8;
        code_ptr += 8;
        if ( a2 != 1 )
        {
          *v141 = -72;
          if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
            v142 = (ArgList & 0x7FFFF) + 0x200000;
          else
            v142 = ArgList & 0x1FFFFF;
          *(_DWORD *)(code_ptr + 1) = (char *)recomp_code_base + v142;
          *(_WORD *)(code_ptr + 5) = 8447;
          code_ptr += 7;
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
        *(_DWORD *)(code_ptr + 1) = v7;
        *(_WORD *)(code_ptr + 5) = 17923;
        code_ptr[7] = v144;
        *((_WORD *)code_ptr + 4) = -10101;
        *((_WORD *)code_ptr + 5) = -7295;
        *((_DWORD *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(_DWORD *)(code_ptr + 17) = -4;
        code_ptr[21] = 80;
        code_ptr[22] = -24;
        *(_DWORD *)(code_ptr + 23) = (_BYTE *)recomp_buffer - code_ptr + 421;
        *(_WORD *)(code_ptr + 27) = 3211;
        code_ptr[29] = -99;
        *(_DWORD *)(code_ptr + 30) = byte_45591C;
        *((_WORD *)code_ptr + 17) = -16093;
        *((_WORD *)code_ptr + 18) = 3211;
        code_ptr[38] = -99;
        *(_DWORD *)(code_ptr + 39) = byte_45592C;
        *(_WORD *)(code_ptr + 43) = 24203;
        code_ptr[45] = v145;
        *((_WORD *)code_ptr + 23) = -7213;
LABEL_384:
        *((_WORD *)code_ptr + 24) = -10229;
        code_ptr[50] = 88;
        code_ptr[51] = -24;
        *((_DWORD *)code_ptr + 13) = (_BYTE *)recomp_buffer - code_ptr + 904;
        code_ptr += 56;
        goto LABEL_422;
      case 0x32u:
        v146 = 4 * (BYTE2(v7) & 0x1F);
        v147 = (unsigned __int16)v7;
        if ( (v7 & 0x8000) != 0 )
          v147 = v7 | 0xFFFF0000;
        if ( v146 >= 0x38u && v146 <= 0x4Cu || v146 == 112 )
        {
          *(_WORD *)v2 = 32393;
          code_ptr[2] = -112;
          code_ptr[3] = 87;
          code_ptr[4] = 86;
          *(_WORD *)(code_ptr + 5) = 18119;
          code_ptr[7] = -116;
          *((_DWORD *)code_ptr + 2) = v7;
          v148 = op_LWC2;
          goto LABEL_414;
        }
        *v2 = -72;
        *(_DWORD *)(code_ptr + 1) = v147;
        *(_WORD *)(code_ptr + 5) = 17923;
        code_ptr[7] = 4 * ((v7 >> 21) & 0x1F);
        code_ptr[8] = -24;
        *(_DWORD *)(code_ptr + 9) = (_BYTE *)recomp_buffer - code_ptr + 435;
        if ( v146 == 28 )
        {
LABEL_355:
          code_ptr += 13;
        }
        else if ( v146 == 4 || v146 == 12 || v146 == 20 || v146 == 32 || v146 == 36 || v146 == 40 || v146 == 44 )
        {
          *(_WORD *)(code_ptr + 13) = -16625;
          code_ptr[15] = -64;
          code_ptr[16] = -93;
          *(_DWORD *)(code_ptr + 17) = (char *)&gte_regs + v146;
          code_ptr += 21;
        }
        else
        {
          code_ptr[13] = -93;
          *(_DWORD *)(code_ptr + 14) = (char *)&gte_regs + v146;
          code_ptr += 18;
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
          code_ptr[2] = -112;
          code_ptr[3] = 87;
          code_ptr[4] = 86;
          *(_WORD *)(code_ptr + 5) = 18119;
          code_ptr[7] = -116;
          *((_DWORD *)code_ptr + 2) = v7;
          v148 = op_SWC2;
LABEL_414:
          code_ptr[12] = -24;
          *(_DWORD *)(code_ptr + 13) = v148 - code_ptr - 17;
          code_ptr[17] = 94;
          code_ptr[18] = 95;
          *(_WORD *)(code_ptr + 19) = 32653;
          code_ptr[21] = -5;
          code_ptr += 22;
        }
        else
        {
          *v2 = -72;
          *(_DWORD *)(code_ptr + 1) = v150;
          *(_WORD *)(code_ptr + 5) = 7563;
          *(_DWORD *)(code_ptr + 7) = (char *)&gte_regs + (unsigned __int8)(4 * (BYTE2(v7) & 0x1F));
          *(_WORD *)(code_ptr + 11) = 17923;
          code_ptr[13] = 4 * ((v7 >> 21) & 0x1F);
          code_ptr[14] = -24;
          *(_DWORD *)(code_ptr + 15) = (_BYTE *)recomp_buffer - code_ptr + 941;
          code_ptr += 19;
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
  *(_DWORD *)(code_ptr + 1) = (char *)recomp_code_base + v156;
  *(_WORD *)(code_ptr + 5) = 8447;
  code_ptr += 7;
  return v158 - 1;
}
