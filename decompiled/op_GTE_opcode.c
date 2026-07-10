#include "pch.h"
char op_GTE_opcode()
{
  int v0; // eax
  int v1; // edx
  int v2; // eax
  int v3; // edx
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  unsigned int v26; // eax
  unsigned __int8 v27; // bl
  unsigned __int8 v28; // cl
  unsigned __int8 v29; // al
  int v30; // edx
  int v31; // ecx
  int v32; // edx
  int v33; // esi
  int v34; // edx
  int v35; // edi
  int v36; // ebp
  int v37; // ebx
  int v38; // ecx
  int v39; // ecx
  int v40; // ebp
  int v41; // edx
  int v42; // esi
  int v43; // esi
  int v44; // edx
  int v45; // edi
  int v46; // ebp
  int v47; // ebx
  int v48; // ecx
  int v49; // ebp
  int v50; // ebx
  int v51; // edi
  int v52; // edx
  int v53; // esi
  int v54; // edi
  int v55; // ebp
  int v56; // ecx
  int v57; // edx
  int v58; // esi
  int v59; // edi
  int v60; // ebx
  int v61; // ecx
  int v62; // edx
  int v63; // ecx
  int v64; // edx
  int v65; // ebp
  int v66; // edi
  int v67; // edx
  int v68; // edi
  int v69; // edi
  int v70; // ebx
  int v71; // esi
  int v72; // edx
  int v73; // edi
  int v74; // esi
  int v75; // ebp
  int v76; // edx
  int v77; // edi
  int v78; // ebp
  int v79; // ebx
  int v80; // ecx
  int v81; // edx
  int v82; // edi
  int v83; // esi
  int v84; // ebp
  int v85; // ebx
  int v86; // ecx
  int v87; // ebp
  int v88; // ebx
  int v89; // ecx
  int v90; // edi
  int v91; // ebp
  int v92; // ecx
  int v93; // edx
  int v94; // edi
  int v95; // ebx
  int v96; // esi
  int v97; // ecx
  int v98; // edx
  int v99; // edi
  int v100; // ebx
  int v101; // esi
  int v102; // eax
  int v103; // ecx
  int v104; // edx
  int v105; // edx
  int v106; // ebx
  int v107; // edi
  int v108; // ebp
  int v109; // esi
  int v110; // edi
  int v111; // ebp
  int v112; // ecx
  int v113; // edx
  int v114; // edx
  int v115; // ebp
  int v116; // edi
  int v117; // edx
  int v118; // esi
  int v119; // edi
  int v120; // ebp
  int v121; // ecx
  int v122; // edx
  int v123; // edx
  int v124; // ebp
  int v125; // edi
  int v126; // edx
  int v127; // esi
  int v128; // edi
  int v129; // ebp
  int v130; // ecx
  int v131; // edx
  int v132; // esi
  int v133; // edi
  int v134; // ebx
  int v135; // ecx
  int v136; // edx
  int v137; // ecx
  int v138; // edx
  int v139; // ebx
  int v140; // edi
  int v141; // esi
  int v142; // edi
  int v143; // ebp
  int v144; // ecx
  int v145; // edx
  int v146; // edx
  int v147; // ebp
  int v148; // edi
  int v149; // edx
  int v150; // edi
  int v151; // ebx
  int v152; // ecx
  int v153; // edx
  int v154; // edi
  int v155; // ebp
  int v156; // ecx
  int v157; // edx
  int v158; // edi
  int v159; // ebp
  int v160; // ecx
  int v161; // edx
  int v162; // edi
  int v163; // ebx
  int v164; // ecx
  int v165; // edx
  int v166; // edi
  int v167; // ebx
  int v168; // ecx
  int v169; // edx
  int v170; // edi
  int v171; // ebp
  int v172; // esi
  int v173; // ecx
  int v174; // edx
  int v175; // edi
  int v176; // ebx
  int v177; // ecx
  int v178; // edx
  int v179; // edi
  int v180; // ebp
  int v181; // ecx
  int v182; // edx
  int v183; // ecx
  int v184; // ecx

  LOBYTE(v26) = cpu_opcode;
  switch ( ((unsigned int)cpu_opcode >> 21) & 0x1F )
  {
    case 0u:
      v27 = BYTE2(cpu_opcode) & 0x1F;
      v28 = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      byte_8A8001 = v28;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        if ( v28 == 31 )
        {
          v26 = (unsigned __int8)sub_414EE0(dword_8A7F78);
          cpu_gpr[v27] = v26;
        }
        else
        {
          if ( v28 == 29 )
          {
            sub_410400((unsigned __int16)word_8A7F2C[0]);
            sub_410400((unsigned __int16)word_8A7F28[0]);
            v29 = sub_410400((unsigned __int16)word_8A7F24[0]);
            v27 = byte_8A7EE0;
            dword_8A7F74 = v29 | v30;
          }
          LOBYTE(v26) = v27;
          cpu_gpr[v27] = *(_DWORD *)&word_8A7F00[4 * v28];
        }
      }
      return v26;
    case 2u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      byte_8A8000 = v26;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        v26 = BYTE2(cpu_opcode) & 0x1F;
        cpu_gpr[v26] = *(_DWORD *)&word_8A7F80[2 * ((unsigned __int16)cpu_opcode >> 11)];
      }
      return v26;
    case 4u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      byte_8A8001 = v26;
      v31 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      *(_DWORD *)&word_8A7F00[4 * (unsigned __int8)v26] = v31;
      if ( (unsigned __int8)v26 >= 0x10u && (unsigned __int8)v26 <= 0x13u )
        *(_DWORD *)&word_8A7F00[4 * (unsigned __int8)v26] = (unsigned __int16)v31;
      switch ( (_BYTE)v26 )
      {
        case 0xE:
          unk_8A7F3C = v31;
          break;
        case 0xF:
          LOBYTE(v26) = word_8A7F34;
          *(_DWORD *)&word_8A7F30 = *(_DWORD *)&word_8A7F34;
          *(_DWORD *)&word_8A7F34 = *(_DWORD *)&word_8A7F38;
          *(_DWORD *)&word_8A7F38 = v31;
          break;
        case 0x1C:
          v26 = (dword_8A7F70[0] >> 3) & 0xF80;
          *(_DWORD *)word_8A7F24 = (dword_8A7F70[0] & 0x1F) << 7;
          *(_DWORD *)word_8A7F28 = 4 * (dword_8A7F70[0] & 0x3E0);
          *(_DWORD *)word_8A7F2C = v26;
          break;
      }
      return v26;
    case 6u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      v32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      byte_8A8000 = v26;
      *(_DWORD *)&word_8A7F80[2 * (unsigned __int8)v26] = v32;
      return v26;
    default:
      v26 = cpu_opcode & 0x1FFFFFF;
      dword_8A7FFC = 0;
      if ( (cpu_opcode & 0x1FFFFFFu) <= 0x48A412 )
      {
        if ( v26 == 4760594 )
        {
          v119 = word_8A7F0A;
          v120 = word_8A7F08;
          v118 = word_8A7F0C;
          v26 = dword_8A7FB4
              + ((word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12);
          v121 = word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86;
          v122 = word_8A7F0C * word_8A7F8A;
          goto LABEL_314;
        }
        if ( v26 <= 0x432012 )
        {
          if ( v26 == 4399122 )
          {
            v26 = word_8A7F10 * word_8A7FA0 + dword_8A7FB4 + word_8A7F12 * word_8A7FA2 + word_8A7F14 * word_8A7FA4;
            v39 = word_8A7F10 * word_8A7FA6 + dword_8A7FB8 + word_8A7F12 * word_8A7FA8 + word_8A7F14 * word_8A7FAA;
            v41 = word_8A7F10 * word_8A7FAC + dword_8A7FBC + word_8A7F12 * word_8A7FAE + word_8A7F14 * word_8A7FB0;
            v42 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= 0x416012 )
          {
            if ( v26 == 4284434 )
            {
              v59 = word_8A7F12;
              v60 = word_8A7F10;
              v58 = word_8A7F14;
              v26 = word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0];
              v61 = word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86;
              v62 = word_8A7F14 * word_8A7F8A;
              goto LABEL_80;
            }
            if ( v26 <= 0x408012 )
            {
              if ( v26 == 4227090 )
              {
                v34 = word_8A7F0A;
                v35 = word_8A7F08;
                v33 = word_8A7F0C;
                v26 = word_8A7F08 * word_8A7F80[0]
                    + dword_8A7F94
                    + word_8A7F0A * word_8A7F82
                    + word_8A7F0C * word_8A7F84;
                v36 = dword_8A7F98 + word_8A7F0A * word_8A7F88;
                v37 = word_8A7F08 * word_8A7F86;
                v38 = word_8A7F0C * word_8A7F8A;
                goto LABEL_43;
              }
              if ( v26 <= 0x400412 )
              {
                if ( v26 != 0x400412 )
                {
                  if ( v26 <= 0x198001 )
                  {
                    if ( v26 == 0x198001 )
                      goto LABEL_37;
                    if ( v26 != 0x140006 )
                    {
                      if ( v26 != 0x180001 )
                      {
                        if ( v26 != 0x18041B )
                          goto LABEL_630;
LABEL_602:
                        LOBYTE(v26) = sub_412D70();
                        return v26;
                      }
LABEL_37:
                      LOBYTE(v26) = gte_optimized_sub1();
                      return v26;
                    }
LABEL_612:
                    v26 = word_8A7F38 * (unk_8A7F32 - unk_8A7F36);
                    unk_8A7F60 = v26 + word_8A7F34 * (unk_8A7F3A - unk_8A7F32) + word_8A7F30 * (unk_8A7F36 - unk_8A7F3A);
                    return v26;
                  }
                  if ( v26 == 0x280030 )
                  {
                    LOBYTE(v26) = sub_40FE00();
                    return v26;
                  }
                  if ( v26 == 0x400006 )
                    goto LABEL_612;
                  if ( v26 != 0x400012 )
                    goto LABEL_630;
                  v33 = word_8A7F04;
                  v34 = word_8A7F02;
                  v35 = *(__int16 *)word_8A7F00;
                  goto LABEL_42;
                }
                v43 = word_8A7F04;
                v44 = word_8A7F02;
                v45 = *(__int16 *)word_8A7F00;
LABEL_52:
                v26 = v45 * word_8A7F80[0] + dword_8A7F94 + v44 * word_8A7F82 + v43 * word_8A7F84;
                v46 = dword_8A7F98 + v45 * word_8A7F86;
                v47 = v43 * word_8A7F8A;
                v48 = v44 * word_8A7F88;
LABEL_53:
                v39 = v47 + v46 + v48;
                v49 = dword_8A7F9C;
LABEL_54:
                v50 = v45 * word_8A7F8C;
                v51 = v44 * word_8A7F8E;
                v52 = word_8A7F90;
LABEL_55:
                v41 = v50 + v49 + v51 + v43 * v52;
                v42 = 0;
                goto LABEL_56;
              }
              if ( v26 <= 0x404412 )
              {
                if ( v26 != 0x404412 )
                {
                  if ( v26 == 0x402012 )
                  {
                    v34 = word_8A7F02;
                    v35 = *(__int16 *)word_8A7F00;
                    v33 = word_8A7F04;
                    v26 = *(__int16 *)word_8A7F00 * word_8A7F80[0]
                        + dword_8A7FB4
                        + word_8A7F02 * word_8A7F82
                        + word_8A7F04 * word_8A7F84;
                    v39 = word_8A7F04 * word_8A7F8A
                        + dword_8A7FB8
                        + *(__int16 *)word_8A7F00 * word_8A7F86
                        + word_8A7F02 * word_8A7F88;
                    v40 = dword_8A7FBC;
                    goto LABEL_44;
                  }
                  if ( v26 != 4203538 )
                  {
                    if ( v26 != 4210706 )
                      goto LABEL_630;
                    v34 = word_8A7F02;
                    v35 = *(__int16 *)word_8A7F00;
                    v33 = word_8A7F04;
                    v26 = *(__int16 *)word_8A7F00 * word_8A7F80[0]
                        + dword_8A7FD4
                        + word_8A7F02 * word_8A7F82
                        + word_8A7F04 * word_8A7F84;
                    v39 = word_8A7F04 * word_8A7F8A
                        + dword_8A7FD8
                        + *(__int16 *)word_8A7F00 * word_8A7F86
                        + word_8A7F02 * word_8A7F88;
                    v40 = dword_8A7FDC;
                    goto LABEL_44;
                  }
                  v44 = word_8A7F02;
                  v45 = *(__int16 *)word_8A7F00;
                  v43 = word_8A7F04;
                  v26 = *(__int16 *)word_8A7F00 * word_8A7F80[0]
                      + dword_8A7FB4
                      + word_8A7F02 * word_8A7F82
                      + word_8A7F04 * word_8A7F84;
                  v39 = word_8A7F04 * word_8A7F8A
                      + dword_8A7FB8
                      + *(__int16 *)word_8A7F00 * word_8A7F86
                      + word_8A7F02 * word_8A7F88;
                  v49 = dword_8A7FBC;
                  goto LABEL_54;
                }
                v43 = word_8A7F04;
                v44 = word_8A7F02;
                v45 = *(__int16 *)word_8A7F00;
                goto LABEL_138;
              }
              if ( v26 != 4218898 )
              {
                if ( v26 != 4219922 )
                  goto LABEL_630;
                v53 = word_8A7F04;
                v54 = word_8A7F02;
                v55 = *(__int16 *)word_8A7F00;
                goto LABEL_72;
              }
              v58 = word_8A7F04;
              v59 = word_8A7F02;
              v60 = *(__int16 *)word_8A7F00;
              goto LABEL_79;
            }
            if ( v26 > 0x40E412 )
            {
              if ( v26 > 0x412412 )
              {
                if ( v26 == 4276242 )
                {
                  v34 = word_8A7F12;
                  v35 = word_8A7F10;
                  v33 = word_8A7F14;
                  v26 = word_8A7F10 * word_8A7F80[0]
                      + dword_8A7FD4
                      + word_8A7F12 * word_8A7F82
                      + word_8A7F14 * word_8A7F84;
                  v39 = word_8A7F10 * word_8A7F86 + dword_8A7FD8 + word_8A7F12 * word_8A7F88 + word_8A7F14 * word_8A7F8A;
                  v40 = dword_8A7FDC;
                  goto LABEL_44;
                }
                if ( v26 != 4277266 )
                  goto LABEL_630;
                v44 = word_8A7F12;
                v45 = word_8A7F10;
                v43 = word_8A7F14;
                v26 = word_8A7F10 * word_8A7F80[0]
                    + dword_8A7FD4
                    + word_8A7F12 * word_8A7F82
                    + word_8A7F14 * word_8A7F84;
                v39 = word_8A7F10 * word_8A7F86 + dword_8A7FD8 + word_8A7F12 * word_8A7F88 + word_8A7F14 * word_8A7F8A;
                v49 = dword_8A7FDC;
                goto LABEL_54;
              }
              if ( v26 == 4269074 )
              {
                v44 = word_8A7F12;
                v45 = word_8A7F10;
                v43 = word_8A7F14;
                v26 = word_8A7F10 * word_8A7F80[0]
                    + dword_8A7FB4
                    + word_8A7F12 * word_8A7F82
                    + word_8A7F14 * word_8A7F84;
                v39 = word_8A7F10 * word_8A7F86 + dword_8A7FB8 + word_8A7F12 * word_8A7F88 + word_8A7F14 * word_8A7F8A;
                v49 = dword_8A7FBC;
                goto LABEL_54;
              }
              if ( v26 == 4259858 )
              {
                v34 = word_8A7F12;
                v35 = word_8A7F10;
                v33 = word_8A7F14;
                v26 = word_8A7F10 * word_8A7F80[0]
                    + dword_8A7F94
                    + word_8A7F12 * word_8A7F82
                    + word_8A7F14 * word_8A7F84;
                v36 = dword_8A7F98 + word_8A7F12 * word_8A7F88;
                v37 = word_8A7F10 * word_8A7F86;
                v38 = word_8A7F14 * word_8A7F8A;
                goto LABEL_43;
              }
              if ( v26 != 4260882 )
              {
                if ( v26 != 4268050 )
                  goto LABEL_630;
                v34 = word_8A7F12;
                v35 = word_8A7F10;
                v33 = word_8A7F14;
                v26 = word_8A7F10 * word_8A7F80[0]
                    + dword_8A7FB4
                    + word_8A7F12 * word_8A7F82
                    + word_8A7F14 * word_8A7F84;
                v39 = word_8A7F10 * word_8A7F86 + dword_8A7FB8 + word_8A7F12 * word_8A7F88 + word_8A7F14 * word_8A7F8A;
                v40 = dword_8A7FBC;
                goto LABEL_44;
              }
              v44 = word_8A7F12;
              v45 = word_8A7F10;
              v43 = word_8A7F14;
              v26 = word_8A7F10 * word_8A7F80[0] + dword_8A7F94 + word_8A7F12 * word_8A7F82 + word_8A7F14 * word_8A7F84;
              v46 = dword_8A7F98 + word_8A7F12 * word_8A7F88;
              v47 = word_8A7F10 * word_8A7F86;
              v48 = word_8A7F14 * word_8A7F8A;
              goto LABEL_53;
            }
            if ( v26 != 4252690 )
            {
              if ( v26 <= 0x40C012 )
              {
                if ( v26 == 4243474 )
                {
                  v34 = word_8A7F0A;
                  v35 = word_8A7F08;
                  v33 = word_8A7F0C;
                  v26 = word_8A7F08 * word_8A7F80[0]
                      + dword_8A7FD4
                      + word_8A7F0A * word_8A7F82
                      + word_8A7F0C * word_8A7F84;
                  v39 = word_8A7F08 * word_8A7F86 + dword_8A7FD8 + word_8A7F0A * word_8A7F88 + word_8A7F0C * word_8A7F8A;
                  v40 = dword_8A7FDC;
                  goto LABEL_44;
                }
                if ( v26 != 4228114 )
                {
                  if ( v26 == 4235282 )
                  {
                    v34 = word_8A7F0A;
                    v35 = word_8A7F08;
                    v33 = word_8A7F0C;
                    v26 = word_8A7F08 * word_8A7F80[0]
                        + dword_8A7FB4
                        + word_8A7F0A * word_8A7F82
                        + word_8A7F0C * word_8A7F84;
                    v39 = word_8A7F08 * word_8A7F86
                        + dword_8A7FB8
                        + word_8A7F0A * word_8A7F88
                        + word_8A7F0C * word_8A7F8A;
                    v40 = dword_8A7FBC;
                    goto LABEL_44;
                  }
                  if ( v26 != 4236306 )
                    goto LABEL_630;
                  v44 = word_8A7F0A;
                  v45 = word_8A7F08;
                  v43 = word_8A7F0C;
                  v26 = word_8A7F08 * word_8A7F80[0]
                      + dword_8A7FB4
                      + word_8A7F0A * word_8A7F82
                      + word_8A7F0C * word_8A7F84;
                  v39 = word_8A7F08 * word_8A7F86 + dword_8A7FB8 + word_8A7F0A * word_8A7F88 + word_8A7F0C * word_8A7F8A;
                  v49 = dword_8A7FBC;
                  goto LABEL_54;
                }
                v44 = word_8A7F0A;
                v45 = word_8A7F08;
                v43 = word_8A7F0C;
                v26 = word_8A7F08 * word_8A7F80[0]
                    + dword_8A7F94
                    + word_8A7F0A * word_8A7F82
                    + word_8A7F0C * word_8A7F84;
                v46 = dword_8A7F98 + word_8A7F0A * word_8A7F88;
                v47 = word_8A7F08 * word_8A7F86;
                v48 = word_8A7F0C * word_8A7F8A;
                goto LABEL_53;
              }
              if ( v26 == 4244498 )
              {
                v44 = word_8A7F0A;
                v45 = word_8A7F08;
                v43 = word_8A7F0C;
                v26 = word_8A7F08 * word_8A7F80[0]
                    + dword_8A7FD4
                    + word_8A7F0A * word_8A7F82
                    + word_8A7F0C * word_8A7F84;
                v39 = word_8A7F08 * word_8A7F86 + dword_8A7FD8 + word_8A7F0A * word_8A7F88 + word_8A7F0C * word_8A7F8A;
                v49 = dword_8A7FDC;
                goto LABEL_54;
              }
              if ( v26 != 4251666 )
                goto LABEL_630;
              v59 = word_8A7F0A;
              v60 = word_8A7F08;
              v58 = word_8A7F0C;
              v26 = word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0];
              v61 = word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86;
              v62 = word_8A7F0C * word_8A7F8A;
              goto LABEL_80;
            }
            v53 = word_8A7F0C;
            v54 = word_8A7F0A;
            v55 = word_8A7F08;
LABEL_98:
            v26 = v53 * word_8A7F84 + v54 * word_8A7F82 + v55 * word_8A7F80[0];
            v56 = v54 * word_8A7F88 + v55 * word_8A7F86;
            v57 = v53 * word_8A7F8A;
            goto LABEL_99;
          }
          if ( v26 <= 0x424012 )
          {
            if ( v26 == 4341778 )
            {
              v26 = *(__int16 *)word_8A7F00 * word_8A7FA0
                  + dword_8A7FD4
                  + word_8A7F02 * word_8A7FA2
                  + word_8A7F04 * word_8A7FA4;
              v39 = *(__int16 *)word_8A7F00 * word_8A7FA6
                  + dword_8A7FD8
                  + word_8A7F02 * word_8A7FA8
                  + word_8A7F04 * word_8A7FAA;
              v41 = *(__int16 *)word_8A7F00 * word_8A7FAC
                  + dword_8A7FDC
                  + word_8A7F02 * word_8A7FAE
                  + word_8A7F04 * word_8A7FB0;
              v42 = -32768;
            }
            else
            {
              if ( v26 <= 0x41C412 )
              {
                if ( v26 == 4310034 )
                {
                  v43 = word_8A7F2C[0];
                  v44 = word_8A7F28[0];
                  v45 = word_8A7F24[0];
LABEL_138:
                  v26 = v45 * word_8A7F80[0] + dword_8A7FD4 + v44 * word_8A7F82 + v43 * word_8A7F84;
                  v39 = v43 * word_8A7F8A + dword_8A7FD8 + v45 * word_8A7F86 + v44 * word_8A7F88;
                  v49 = dword_8A7FDC;
                  goto LABEL_54;
                }
                if ( v26 > 0x41A012 )
                {
                  if ( v26 != 4301842 )
                  {
                    if ( v26 != 4309010 )
                      goto LABEL_630;
                    v34 = word_8A7F28[0];
                    v35 = word_8A7F24[0];
                    v33 = word_8A7F2C[0];
                    v26 = word_8A7F24[0] * word_8A7F80[0]
                        + dword_8A7FD4
                        + word_8A7F28[0] * word_8A7F82
                        + word_8A7F2C[0] * word_8A7F84;
                    v39 = word_8A7F2C[0] * word_8A7F8A
                        + dword_8A7FD8
                        + word_8A7F24[0] * word_8A7F86
                        + word_8A7F28[0] * word_8A7F88;
                    v40 = dword_8A7FDC;
                    goto LABEL_44;
                  }
                  v44 = word_8A7F28[0];
                  v45 = word_8A7F24[0];
                  v43 = word_8A7F2C[0];
                  v26 = word_8A7F24[0] * word_8A7F80[0]
                      + dword_8A7FB4
                      + word_8A7F28[0] * word_8A7F82
                      + word_8A7F2C[0] * word_8A7F84;
                  v39 = word_8A7F2C[0] * word_8A7F8A
                      + dword_8A7FB8
                      + word_8A7F24[0] * word_8A7F86
                      + word_8A7F28[0] * word_8A7F88;
                  v49 = dword_8A7FBC;
                  goto LABEL_54;
                }
                if ( v26 == 4300818 )
                {
                  v34 = word_8A7F28[0];
                  v35 = word_8A7F24[0];
                  v33 = word_8A7F2C[0];
                  v26 = word_8A7F24[0] * word_8A7F80[0]
                      + dword_8A7FB4
                      + word_8A7F28[0] * word_8A7F82
                      + word_8A7F2C[0] * word_8A7F84;
                  v39 = word_8A7F2C[0] * word_8A7F8A
                      + dword_8A7FB8
                      + word_8A7F24[0] * word_8A7F86
                      + word_8A7F28[0] * word_8A7F88;
                  v40 = dword_8A7FBC;
                  goto LABEL_44;
                }
                if ( v26 != 4285458 )
                {
                  if ( v26 == 4292626 )
                  {
                    v33 = word_8A7F2C[0];
                    v34 = word_8A7F28[0];
                    v35 = word_8A7F24[0];
LABEL_42:
                    v26 = v35 * word_8A7F80[0] + dword_8A7F94 + v34 * word_8A7F82 + v33 * word_8A7F84;
                    v36 = dword_8A7F98 + v35 * word_8A7F86;
                    v37 = v33 * word_8A7F8A;
                    v38 = v34 * word_8A7F88;
LABEL_43:
                    v39 = v37 + v36 + v38;
                    v40 = dword_8A7F9C;
LABEL_44:
                    v41 = v35 * word_8A7F8C + v40 + v34 * word_8A7F8E + v33 * word_8A7F90;
                    v42 = -32768;
                    goto LABEL_56;
                  }
                  if ( v26 != 4293650 )
                    goto LABEL_630;
                  v43 = word_8A7F2C[0];
                  v44 = word_8A7F28[0];
                  v45 = word_8A7F24[0];
                  goto LABEL_52;
                }
                v53 = word_8A7F14;
                v54 = word_8A7F12;
                v55 = word_8A7F10;
                goto LABEL_98;
              }
              if ( v26 > 0x420412 )
              {
                if ( v26 != 4333586 )
                {
                  if ( v26 != 4334610 )
                    goto LABEL_630;
                  v43 = word_8A7F04;
                  v26 = *(__int16 *)word_8A7F00 * word_8A7FA0
                      + dword_8A7FB4
                      + word_8A7F02 * word_8A7FA2
                      + word_8A7F04 * word_8A7FA4;
                  v50 = *(__int16 *)word_8A7F00 * word_8A7FAC;
                  v39 = *(__int16 *)word_8A7F00 * word_8A7FA6
                      + dword_8A7FB8
                      + word_8A7F02 * word_8A7FA8
                      + word_8A7F04 * word_8A7FAA;
                  v51 = word_8A7F02 * word_8A7FAE;
                  v49 = dword_8A7FBC;
                  v52 = word_8A7FB0;
                  goto LABEL_55;
                }
                v26 = *(__int16 *)word_8A7F00 * word_8A7FA0
                    + dword_8A7FB4
                    + word_8A7F02 * word_8A7FA2
                    + word_8A7F04 * word_8A7FA4;
                v39 = *(__int16 *)word_8A7F00 * word_8A7FA6
                    + dword_8A7FB8
                    + word_8A7F02 * word_8A7FA8
                    + word_8A7F04 * word_8A7FAA;
                v41 = *(__int16 *)word_8A7F00 * word_8A7FAC
                    + dword_8A7FBC
                    + word_8A7F02 * word_8A7FAE
                    + word_8A7F04 * word_8A7FB0;
                v42 = -32768;
              }
              else
              {
                switch ( v26 )
                {
                  case 0x420412u:
                    v43 = word_8A7F04;
                    v26 = *(__int16 *)word_8A7F00 * word_8A7FA0
                        + dword_8A7F94
                        + word_8A7F02 * word_8A7FA2
                        + word_8A7F04 * word_8A7FA4;
                    v50 = *(__int16 *)word_8A7F00 * word_8A7FAC;
                    v39 = *(__int16 *)word_8A7F00 * word_8A7FA6
                        + dword_8A7F98
                        + word_8A7F02 * word_8A7FA8
                        + word_8A7F04 * word_8A7FAA;
                    v51 = word_8A7F02 * word_8A7FAE;
                    v49 = dword_8A7F9C;
                    v52 = word_8A7FB0;
                    goto LABEL_55;
                  case 0x41E012u:
                    v58 = word_8A7F2C[0];
                    v59 = word_8A7F28[0];
                    v60 = word_8A7F24[0];
LABEL_79:
                    v26 = v58 * word_8A7F84 + v59 * word_8A7F82 + v60 * word_8A7F80[0];
                    v61 = v60 * word_8A7F86 + v58 * word_8A7F8A;
                    v62 = v59 * word_8A7F88;
LABEL_80:
                    v39 = v62 + v61;
                    v41 = v58 * word_8A7F90 + v59 * word_8A7F8E + v60 * word_8A7F8C;
                    v42 = -32768;
                    goto LABEL_56;
                  case 0x41E412u:
                    v53 = word_8A7F2C[0];
                    v54 = word_8A7F28[0];
                    v55 = word_8A7F24[0];
LABEL_72:
                    v26 = v53 * word_8A7F84 + v54 * word_8A7F82 + v55 * word_8A7F80[0];
                    v56 = v55 * word_8A7F86 + v53 * word_8A7F8A;
                    v57 = v54 * word_8A7F88;
LABEL_99:
                    v63 = v57 + v56;
                    v64 = v55 * word_8A7F8C;
                    v65 = v54 * word_8A7F8E;
                    v66 = word_8A7F90;
LABEL_100:
                    v67 = v65 + v64;
                    v68 = v53 * v66;
LABEL_101:
                    v41 = v68 + v67;
                    goto LABEL_102;
                }
                if ( v26 != 4325394 )
                  goto LABEL_630;
                v26 = *(__int16 *)word_8A7F00 * word_8A7FA0
                    + dword_8A7F94
                    + word_8A7F02 * word_8A7FA2
                    + word_8A7F04 * word_8A7FA4;
                v39 = *(__int16 *)word_8A7F00 * word_8A7FA6
                    + dword_8A7F98
                    + word_8A7F02 * word_8A7FA8
                    + word_8A7F04 * word_8A7FAA;
                v41 = *(__int16 *)word_8A7F00 * word_8A7FAC
                    + dword_8A7F9C
                    + word_8A7F02 * word_8A7FAE
                    + word_8A7F04 * word_8A7FB0;
                v42 = -32768;
              }
            }
LABEL_56:
            dword_8A7F64 = v26;
            dword_8A7F68 = v39;
            dword_8A7F6C = v41;
            if ( (int)v26 >= v42 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F24 = v26;
              }
              else
              {
                dword_8A7FFC = -2130706432;
                *(_DWORD *)word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC = -2130706432;
              *(_DWORD *)word_8A7F24 = v42;
            }
            if ( v39 >= v42 )
            {
              if ( v39 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F28 = v39;
              }
              else
              {
                dword_8A7FFC |= 0x80800000;
                *(_DWORD *)word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= 0x80800000;
              *(_DWORD *)word_8A7F28 = v42;
            }
            if ( v41 >= v42 )
            {
LABEL_541:
              if ( v41 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F2C = v41;
              }
              else
              {
                *(_DWORD *)word_8A7F2C = 0x7FFF;
                LOBYTE(v26) = dword_8A7FFC;
                dword_8A7FFC |= 0x400000u;
              }
              return v26;
            }
LABEL_558:
            *(_DWORD *)word_8A7F2C = v42;
            LOBYTE(v26) = dword_8A7FFC;
            dword_8A7FFC |= 0x400000u;
            return v26;
          }
          if ( v26 > 0x42A412 )
          {
            if ( v26 > 0x42E412 )
            {
              if ( v26 != 4390930 )
              {
                if ( v26 != 4391954 )
                  goto LABEL_630;
                v43 = word_8A7F14;
                v26 = word_8A7F10 * word_8A7FA0 + dword_8A7F94 + word_8A7F12 * word_8A7FA2 + word_8A7F14 * word_8A7FA4;
                v50 = word_8A7F10 * word_8A7FAC;
                v39 = word_8A7F10 * word_8A7FA6 + dword_8A7F98 + word_8A7F12 * word_8A7FA8 + word_8A7F14 * word_8A7FAA;
                v51 = word_8A7F12 * word_8A7FAE;
                v49 = dword_8A7F9C;
                v52 = word_8A7FB0;
                goto LABEL_55;
              }
              v26 = word_8A7F10 * word_8A7FA0 + dword_8A7F94 + word_8A7F12 * word_8A7FA2 + word_8A7F14 * word_8A7FA4;
              v39 = word_8A7F10 * word_8A7FA6 + dword_8A7F98 + word_8A7F12 * word_8A7FA8 + word_8A7F14 * word_8A7FAA;
              v41 = word_8A7F10 * word_8A7FAC + dword_8A7F9C + word_8A7F12 * word_8A7FAE + word_8A7F14 * word_8A7FB0;
              v42 = -32768;
            }
            else
            {
              switch ( v26 )
              {
                case 0x42E412u:
                  v53 = word_8A7F0C;
                  v26 = word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0;
                  v63 = word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6;
                  v64 = word_8A7F08 * word_8A7FAC;
                  v65 = word_8A7F0A * word_8A7FAE;
                  v66 = word_8A7FB0;
                  goto LABEL_100;
                case 0x42C012u:
                  v26 = word_8A7F08 * word_8A7FA0 + dword_8A7FD4 + word_8A7F0A * word_8A7FA2 + word_8A7F0C * word_8A7FA4;
                  v39 = word_8A7F08 * word_8A7FA6 + dword_8A7FD8 + word_8A7F0A * word_8A7FA8 + word_8A7F0C * word_8A7FAA;
                  v41 = word_8A7F08 * word_8A7FAC + dword_8A7FDC + word_8A7F0A * word_8A7FAE + word_8A7F0C * word_8A7FB0;
                  v42 = -32768;
                  break;
                case 0x42C412u:
                  v43 = word_8A7F0C;
                  v26 = word_8A7F08 * word_8A7FA0 + dword_8A7FD4 + word_8A7F0A * word_8A7FA2 + word_8A7F0C * word_8A7FA4;
                  v50 = word_8A7F08 * word_8A7FAC;
                  v39 = word_8A7F08 * word_8A7FA6 + dword_8A7FD8 + word_8A7F0A * word_8A7FA8 + word_8A7F0C * word_8A7FAA;
                  v51 = word_8A7F0A * word_8A7FAE;
                  v49 = dword_8A7FDC;
                  v52 = word_8A7FB0;
                  goto LABEL_55;
                case 0x42E012u:
                  v26 = word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0;
                  v39 = word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6;
                  v41 = word_8A7F0C * word_8A7FB0 + word_8A7F0A * word_8A7FAE + word_8A7F08 * word_8A7FAC;
                  v42 = -32768;
                  break;
                default:
                  goto LABEL_630;
              }
            }
            goto LABEL_56;
          }
          if ( v26 == 4367378 )
          {
            v43 = word_8A7F0C;
            v26 = word_8A7F08 * word_8A7FA0 + dword_8A7FB4 + word_8A7F0A * word_8A7FA2 + word_8A7F0C * word_8A7FA4;
            v50 = word_8A7F08 * word_8A7FAC;
            v39 = word_8A7F08 * word_8A7FA6 + dword_8A7FB8 + word_8A7F0A * word_8A7FA8 + word_8A7F0C * word_8A7FAA;
            v51 = word_8A7F0A * word_8A7FAE;
            v49 = dword_8A7FBC;
            v52 = word_8A7FB0;
            goto LABEL_55;
          }
          if ( v26 > 0x428012 )
          {
            if ( v26 == 4359186 )
            {
              v43 = word_8A7F0C;
              v26 = word_8A7F08 * word_8A7FA0 + dword_8A7F94 + word_8A7F0A * word_8A7FA2 + word_8A7F0C * word_8A7FA4;
              v50 = word_8A7F08 * word_8A7FAC;
              v39 = word_8A7F08 * word_8A7FA6 + dword_8A7F98 + word_8A7F0A * word_8A7FA8 + word_8A7F0C * word_8A7FAA;
              v51 = word_8A7F0A * word_8A7FAE;
              v49 = dword_8A7F9C;
              v52 = word_8A7FB0;
              goto LABEL_55;
            }
            if ( v26 != 4366354 )
              goto LABEL_630;
            v26 = word_8A7F08 * word_8A7FA0 + dword_8A7FB4 + word_8A7F0A * word_8A7FA2 + word_8A7F0C * word_8A7FA4;
            v39 = word_8A7F08 * word_8A7FA6 + dword_8A7FB8 + word_8A7F0A * word_8A7FA8 + word_8A7F0C * word_8A7FAA;
            v41 = word_8A7F08 * word_8A7FAC + dword_8A7FBC + word_8A7F0A * word_8A7FAE + word_8A7F0C * word_8A7FB0;
            v42 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4358162 )
          {
            v26 = word_8A7F08 * word_8A7FA0 + dword_8A7F94 + word_8A7F0A * word_8A7FA2 + word_8A7F0C * word_8A7FA4;
            v39 = word_8A7F08 * word_8A7FA6 + dword_8A7F98 + word_8A7F0A * word_8A7FA8 + word_8A7F0C * word_8A7FAA;
            v41 = word_8A7F08 * word_8A7FAC + dword_8A7F9C + word_8A7F0A * word_8A7FAE + word_8A7F0C * word_8A7FB0;
            v42 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4342802 )
          {
            v43 = word_8A7F04;
            v26 = *(__int16 *)word_8A7F00 * word_8A7FA0
                + dword_8A7FD4
                + word_8A7F02 * word_8A7FA2
                + word_8A7F04 * word_8A7FA4;
            v50 = *(__int16 *)word_8A7F00 * word_8A7FAC;
            v39 = *(__int16 *)word_8A7F00 * word_8A7FA6
                + dword_8A7FD8
                + word_8A7F02 * word_8A7FA8
                + word_8A7F04 * word_8A7FAA;
            v51 = word_8A7F02 * word_8A7FAE;
            v49 = dword_8A7FDC;
            v52 = word_8A7FB0;
            goto LABEL_55;
          }
          if ( v26 != 4349970 )
          {
            if ( v26 != 4350994 )
              goto LABEL_630;
            v53 = word_8A7F04;
            v26 = word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0;
            v63 = word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6;
            v64 = *(__int16 *)word_8A7F00 * word_8A7FAC;
            v65 = word_8A7F02 * word_8A7FAE;
            v66 = word_8A7FB0;
            goto LABEL_100;
          }
          v69 = word_8A7F02;
          v70 = *(__int16 *)word_8A7F00;
          v71 = word_8A7F04;
          v26 = word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0;
LABEL_214:
          v39 = v71 * word_8A7FAA + v69 * word_8A7FA8 + v70 * word_8A7FA6;
          v41 = v71 * word_8A7FB0 + v69 * word_8A7FAE + v70 * word_8A7FAC;
          v42 = -32768;
          goto LABEL_56;
        }
        if ( v26 <= 0x44E412 )
        {
          if ( v26 != 4514834 )
          {
            if ( v26 <= 0x440412 )
            {
              if ( v26 != 4457490 )
              {
                if ( v26 <= 0x43A012 )
                {
                  if ( v26 == 4431890 )
                  {
                    v26 = word_8A7F24[0] * word_8A7FA0
                        + dword_8A7FB4
                        + word_8A7F28[0] * word_8A7FA2
                        + word_8A7F2C[0] * word_8A7FA4;
                    v39 = word_8A7F24[0] * word_8A7FA6
                        + dword_8A7FB8
                        + word_8A7F28[0] * word_8A7FA8
                        + word_8A7F2C[0] * word_8A7FAA;
                    v41 = word_8A7F24[0] * word_8A7FAC
                        + dword_8A7FBC
                        + word_8A7F28[0] * word_8A7FAE
                        + word_8A7F2C[0] * word_8A7FB0;
                    v42 = -32768;
                  }
                  else if ( v26 > 0x436012 )
                  {
                    if ( v26 == 4416530 )
                    {
                      v53 = word_8A7F14;
                      v26 = word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0;
                      v63 = word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6;
                      v64 = word_8A7F10 * word_8A7FAC;
                      v65 = word_8A7F12 * word_8A7FAE;
                      v66 = word_8A7FB0;
                      goto LABEL_100;
                    }
                    if ( v26 != 4423698 )
                    {
                      if ( v26 != 4424722 )
                        goto LABEL_630;
                      v43 = word_8A7F2C[0];
                      v26 = word_8A7F24[0] * word_8A7FA0
                          + dword_8A7F94
                          + word_8A7F28[0] * word_8A7FA2
                          + word_8A7F2C[0] * word_8A7FA4;
                      v50 = word_8A7F24[0] * word_8A7FAC;
                      v39 = word_8A7F24[0] * word_8A7FA6
                          + dword_8A7F98
                          + word_8A7F28[0] * word_8A7FA8
                          + word_8A7F2C[0] * word_8A7FAA;
                      v51 = word_8A7F28[0] * word_8A7FAE;
                      v49 = dword_8A7F9C;
                      v52 = word_8A7FB0;
                      goto LABEL_55;
                    }
                    v26 = word_8A7F24[0] * word_8A7FA0
                        + dword_8A7F94
                        + word_8A7F28[0] * word_8A7FA2
                        + word_8A7F2C[0] * word_8A7FA4;
                    v39 = word_8A7F24[0] * word_8A7FA6
                        + dword_8A7F98
                        + word_8A7F28[0] * word_8A7FA8
                        + word_8A7F2C[0] * word_8A7FAA;
                    v41 = word_8A7F24[0] * word_8A7FAC
                        + dword_8A7F9C
                        + word_8A7F28[0] * word_8A7FAE
                        + word_8A7F2C[0] * word_8A7FB0;
                    v42 = -32768;
                  }
                  else
                  {
                    switch ( v26 )
                    {
                      case 0x436012u:
                        v26 = word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0;
                        v39 = word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6;
                        v41 = word_8A7F14 * word_8A7FB0 + word_8A7F12 * word_8A7FAE + word_8A7F10 * word_8A7FAC;
                        v42 = -32768;
                        break;
                      case 0x432412u:
                        v43 = word_8A7F14;
                        v26 = word_8A7F10 * word_8A7FA0
                            + dword_8A7FB4
                            + word_8A7F12 * word_8A7FA2
                            + word_8A7F14 * word_8A7FA4;
                        v50 = word_8A7F10 * word_8A7FAC;
                        v39 = word_8A7F10 * word_8A7FA6
                            + dword_8A7FB8
                            + word_8A7F12 * word_8A7FA8
                            + word_8A7F14 * word_8A7FAA;
                        v51 = word_8A7F12 * word_8A7FAE;
                        v49 = dword_8A7FBC;
                        v52 = word_8A7FB0;
                        goto LABEL_55;
                      case 0x434012u:
                        v26 = word_8A7F10 * word_8A7FA0
                            + dword_8A7FD4
                            + word_8A7F12 * word_8A7FA2
                            + word_8A7F14 * word_8A7FA4;
                        v39 = word_8A7F10 * word_8A7FA6
                            + dword_8A7FD8
                            + word_8A7F12 * word_8A7FA8
                            + word_8A7F14 * word_8A7FAA;
                        v41 = word_8A7F10 * word_8A7FAC
                            + dword_8A7FDC
                            + word_8A7F12 * word_8A7FAE
                            + word_8A7F14 * word_8A7FB0;
                        v42 = -32768;
                        break;
                      case 0x434412u:
                        v43 = word_8A7F14;
                        v26 = word_8A7F10 * word_8A7FA0
                            + dword_8A7FD4
                            + word_8A7F12 * word_8A7FA2
                            + word_8A7F14 * word_8A7FA4;
                        v50 = word_8A7F10 * word_8A7FAC;
                        v39 = word_8A7F10 * word_8A7FA6
                            + dword_8A7FD8
                            + word_8A7F12 * word_8A7FA8
                            + word_8A7F14 * word_8A7FAA;
                        v51 = word_8A7F12 * word_8A7FAE;
                        v49 = dword_8A7FDC;
                        v52 = word_8A7FB0;
                        goto LABEL_55;
                      default:
                        goto LABEL_630;
                    }
                  }
                  goto LABEL_56;
                }
                if ( v26 <= 0x43E012 )
                {
                  if ( v26 != 4448274 )
                  {
                    if ( v26 == 4432914 )
                    {
                      v43 = word_8A7F2C[0];
                      v26 = word_8A7F24[0] * word_8A7FA0
                          + dword_8A7FB4
                          + word_8A7F28[0] * word_8A7FA2
                          + word_8A7F2C[0] * word_8A7FA4;
                      v50 = word_8A7F24[0] * word_8A7FAC;
                      v39 = word_8A7F24[0] * word_8A7FA6
                          + dword_8A7FB8
                          + word_8A7F28[0] * word_8A7FA8
                          + word_8A7F2C[0] * word_8A7FAA;
                      v51 = word_8A7F28[0] * word_8A7FAE;
                      v49 = dword_8A7FBC;
                      v52 = word_8A7FB0;
                      goto LABEL_55;
                    }
                    if ( v26 != 4440082 )
                    {
                      if ( v26 != 4441106 )
                        goto LABEL_630;
                      v43 = word_8A7F2C[0];
                      v26 = word_8A7F24[0] * word_8A7FA0
                          + dword_8A7FD4
                          + word_8A7F28[0] * word_8A7FA2
                          + word_8A7F2C[0] * word_8A7FA4;
                      v50 = word_8A7F24[0] * word_8A7FAC;
                      v39 = word_8A7F24[0] * word_8A7FA6
                          + dword_8A7FD8
                          + word_8A7F28[0] * word_8A7FA8
                          + word_8A7F2C[0] * word_8A7FAA;
                      v51 = word_8A7F28[0] * word_8A7FAE;
                      v49 = dword_8A7FDC;
                      v52 = word_8A7FB0;
                      goto LABEL_55;
                    }
                    v26 = word_8A7F24[0] * word_8A7FA0
                        + dword_8A7FD4
                        + word_8A7F28[0] * word_8A7FA2
                        + word_8A7F2C[0] * word_8A7FA4;
                    v39 = word_8A7F24[0] * word_8A7FA6
                        + dword_8A7FD8
                        + word_8A7F28[0] * word_8A7FA8
                        + word_8A7F2C[0] * word_8A7FAA;
                    v41 = word_8A7F24[0] * word_8A7FAC
                        + dword_8A7FDC
                        + word_8A7F28[0] * word_8A7FAE
                        + word_8A7F2C[0] * word_8A7FB0;
                    v42 = -32768;
                    goto LABEL_56;
                  }
                  v69 = word_8A7F28[0];
                  v70 = word_8A7F24[0];
                  v71 = word_8A7F2C[0];
                  v26 = word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0;
                  goto LABEL_214;
                }
                if ( v26 == 4449298 )
                {
                  v53 = word_8A7F2C[0];
                  v26 = word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0;
                  v63 = word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6;
                  v64 = word_8A7F24[0] * word_8A7FAC;
                  v65 = word_8A7F28[0] * word_8A7FAE;
                  v66 = word_8A7FB0;
                  goto LABEL_100;
                }
                if ( v26 != 4456466 )
                  goto LABEL_630;
                v72 = word_8A7F02;
                v73 = *(__int16 *)word_8A7F00;
                v74 = word_8A7F04;
                v26 = *(__int16 *)word_8A7F00 * word_8A7FC0
                    + dword_8A7F94
                    + word_8A7F02 * word_8A7FC2
                    + word_8A7F04 * word_8A7FC4;
                v39 = *(__int16 *)word_8A7F00 * word_8A7FC6
                    + dword_8A7F98
                    + word_8A7F02 * word_8A7FC8
                    + word_8A7F04 * word_8A7FCA;
                v75 = dword_8A7F9C;
LABEL_282:
                v41 = v73 * word_8A7FCC + v75 + v72 * word_8A7FCE + v74 * word_8A7FD0;
                v42 = -32768;
                goto LABEL_56;
              }
              v76 = word_8A7F02;
              v77 = *(__int16 *)word_8A7F00;
              v43 = word_8A7F04;
              v26 = *(__int16 *)word_8A7F00 * word_8A7FC0
                  + dword_8A7F94
                  + word_8A7F02 * word_8A7FC2
                  + word_8A7F04 * word_8A7FC4;
              v39 = *(__int16 *)word_8A7F00 * word_8A7FC6
                  + dword_8A7F98
                  + word_8A7F02 * word_8A7FC8
                  + word_8A7F04 * word_8A7FCA;
              v49 = dword_8A7F9C;
LABEL_287:
              v50 = v77 * word_8A7FCC;
              v51 = v76 * word_8A7FCE;
              v52 = word_8A7FD0;
              goto LABEL_55;
            }
            if ( v26 <= 0x448012 )
            {
              if ( v26 == 4489234 )
              {
                v26 = word_8A7F08 * word_8A7FC0 + dword_8A7F94 + word_8A7F0A * word_8A7FC2 + word_8A7F0C * word_8A7FC4;
                v39 = word_8A7F0A * word_8A7FC8 + dword_8A7F98 + word_8A7F0C * word_8A7FCA + word_8A7F08 * word_8A7FC6;
                v41 = word_8A7F08 * word_8A7FCC + dword_8A7F9C + word_8A7F0A * word_8A7FCE + word_8A7F0C * word_8A7FD0;
                v42 = -32768;
                goto LABEL_56;
              }
              if ( v26 <= 0x444412 )
              {
                if ( v26 != 4473874 )
                {
                  if ( v26 != 4464658 )
                  {
                    if ( v26 == 4465682 )
                    {
                      v76 = word_8A7F02;
                      v77 = *(__int16 *)word_8A7F00;
                      v43 = word_8A7F04;
                      v26 = *(__int16 *)word_8A7F00 * word_8A7FC0
                          + dword_8A7FB4
                          + word_8A7F02 * word_8A7FC2
                          + word_8A7F04 * word_8A7FC4;
                      v39 = *(__int16 *)word_8A7F00 * word_8A7FC6
                          + dword_8A7FB8
                          + word_8A7F02 * word_8A7FC8
                          + word_8A7F04 * word_8A7FCA;
                      v49 = dword_8A7FBC;
                      goto LABEL_287;
                    }
                    if ( v26 != 4472850 )
                      goto LABEL_630;
                    v72 = word_8A7F02;
                    v73 = *(__int16 *)word_8A7F00;
                    v74 = word_8A7F04;
                    v26 = *(__int16 *)word_8A7F00 * word_8A7FC0
                        + dword_8A7FD4
                        + word_8A7F02 * word_8A7FC2
                        + word_8A7F04 * word_8A7FC4;
                    v78 = dword_8A7FD8 + word_8A7F02 * word_8A7FC8;
                    v79 = *(__int16 *)word_8A7F00 * word_8A7FC6;
                    v80 = word_8A7F04 * word_8A7FCA;
LABEL_281:
                    v39 = v79 + v78 + v80;
                    v75 = dword_8A7FDC;
                    goto LABEL_282;
                  }
                  v81 = word_8A7F02;
                  v82 = *(__int16 *)word_8A7F00;
                  v83 = word_8A7F04;
                  v26 = *(__int16 *)word_8A7F00 * word_8A7FC0
                      + dword_8A7FB4
                      + word_8A7F02 * word_8A7FC2
                      + word_8A7F04 * word_8A7FC4;
                  v84 = dword_8A7FB8 + word_8A7F02 * word_8A7FC8;
                  v85 = *(__int16 *)word_8A7F00 * word_8A7FC6;
                  v86 = word_8A7F04 * word_8A7FCA;
LABEL_277:
                  v39 = v85 + v84 + v86;
                  v41 = v82 * word_8A7FCC + dword_8A7FBC + v81 * word_8A7FCE + v83 * word_8A7FD0;
                  v42 = -32768;
                  goto LABEL_56;
                }
                v76 = word_8A7F02;
                v77 = *(__int16 *)word_8A7F00;
                v43 = word_8A7F04;
                v26 = *(__int16 *)word_8A7F00 * word_8A7FC0
                    + dword_8A7FD4
                    + word_8A7F02 * word_8A7FC2
                    + word_8A7F04 * word_8A7FC4;
                v87 = dword_8A7FD8 + word_8A7F02 * word_8A7FC8;
                v88 = *(__int16 *)word_8A7F00 * word_8A7FC6;
                v89 = word_8A7F04 * word_8A7FCA;
LABEL_286:
                v39 = v88 + v87 + v89;
                v49 = dword_8A7FDC;
                goto LABEL_287;
              }
              if ( v26 != 4481042 )
              {
                if ( v26 != 4482066 )
                  goto LABEL_630;
                v90 = word_8A7F02;
                v91 = *(__int16 *)word_8A7F00;
                v53 = word_8A7F04;
                v26 = word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0;
                v92 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
                v93 = word_8A7F04 * word_8A7FCA;
                goto LABEL_302;
              }
              v94 = word_8A7F02;
              v95 = *(__int16 *)word_8A7F00;
              v96 = word_8A7F04;
              v26 = word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0;
              v97 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
              v98 = word_8A7F04 * word_8A7FCA;
LABEL_305:
              v39 = v98 + v97;
              v41 = v96 * word_8A7FD0 + v94 * word_8A7FCE + v95 * word_8A7FCC;
              v42 = -32768;
              goto LABEL_56;
            }
            if ( v26 <= 0x44C012 )
            {
              switch ( v26 )
              {
                case 0x44C012u:
                  v26 = word_8A7F08 * word_8A7FC0 + dword_8A7FD4 + word_8A7F0A * word_8A7FC2 + word_8A7F0C * word_8A7FC4;
                  v39 = word_8A7F0A * word_8A7FC8 + dword_8A7FD8 + word_8A7F0C * word_8A7FCA + word_8A7F08 * word_8A7FC6;
                  v41 = word_8A7F08 * word_8A7FCC + dword_8A7FDC + word_8A7F0A * word_8A7FCE + word_8A7F0C * word_8A7FD0;
                  v42 = -32768;
                  goto LABEL_56;
                case 0x448412u:
                  v76 = word_8A7F0A;
                  v77 = word_8A7F08;
                  v43 = word_8A7F0C;
                  v26 = word_8A7F08 * word_8A7FC0 + dword_8A7F94 + word_8A7F0A * word_8A7FC2 + word_8A7F0C * word_8A7FC4;
                  v39 = word_8A7F0A * word_8A7FC8 + dword_8A7F98 + word_8A7F0C * word_8A7FCA + word_8A7F08 * word_8A7FC6;
                  v49 = dword_8A7F9C;
                  break;
                case 0x44A012u:
                  v26 = word_8A7F08 * word_8A7FC0 + dword_8A7FB4 + word_8A7F0A * word_8A7FC2 + word_8A7F0C * word_8A7FC4;
                  v39 = word_8A7F0A * word_8A7FC8 + dword_8A7FB8 + word_8A7F0C * word_8A7FCA + word_8A7F08 * word_8A7FC6;
                  v41 = word_8A7F08 * word_8A7FCC + dword_8A7FBC + word_8A7F0A * word_8A7FCE + word_8A7F0C * word_8A7FD0;
                  v42 = -32768;
                  goto LABEL_56;
                case 0x44A412u:
                  v76 = word_8A7F0A;
                  v77 = word_8A7F08;
                  v43 = word_8A7F0C;
                  v26 = word_8A7F08 * word_8A7FC0 + dword_8A7FB4 + word_8A7F0A * word_8A7FC2 + word_8A7F0C * word_8A7FC4;
                  v39 = word_8A7F0A * word_8A7FC8 + dword_8A7FB8 + word_8A7F0C * word_8A7FCA + word_8A7F08 * word_8A7FC6;
                  v49 = dword_8A7FBC;
                  break;
                default:
                  goto LABEL_630;
              }
              goto LABEL_287;
            }
            if ( v26 != 4506642 )
            {
              if ( v26 != 4513810 )
                goto LABEL_630;
              v94 = word_8A7F0A;
              v95 = word_8A7F08;
              v96 = word_8A7F0C;
              v26 = word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0;
              goto LABEL_304;
            }
            v43 = word_8A7F0C;
            v76 = word_8A7F0A;
            v77 = word_8A7F08;
LABEL_285:
            v26 = v77 * word_8A7FC0 + dword_8A7FD4 + v76 * word_8A7FC2 + v43 * word_8A7FC4;
            v87 = dword_8A7FD8 + v43 * word_8A7FCA;
            v88 = v76 * word_8A7FC8;
            v89 = v77 * word_8A7FC6;
            goto LABEL_286;
          }
          v90 = word_8A7F0A;
          v91 = word_8A7F08;
          v53 = word_8A7F0C;
          v26 = word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0;
LABEL_301:
          v92 = v53 * word_8A7FCA + v90 * word_8A7FC8;
          v93 = v91 * word_8A7FC6;
LABEL_302:
          v63 = v93 + v92;
          v64 = v91 * word_8A7FCC;
          v65 = v90 * word_8A7FCE;
          v66 = word_8A7FD0;
          goto LABEL_100;
        }
        if ( v26 <= 0x45C412 )
        {
          if ( v26 == 4572178 )
          {
            v43 = word_8A7F2C[0];
            v76 = word_8A7F28[0];
            v77 = word_8A7F24[0];
            goto LABEL_285;
          }
          if ( v26 > 0x456012 )
          {
            if ( v26 > 0x45A012 )
            {
              if ( v26 == 4563986 )
              {
                v76 = word_8A7F28[0];
                v77 = word_8A7F24[0];
                v43 = word_8A7F2C[0];
                v26 = word_8A7F24[0] * word_8A7FC0
                    + dword_8A7FB4
                    + word_8A7F28[0] * word_8A7FC2
                    + word_8A7F2C[0] * word_8A7FC4;
                v39 = word_8A7F28[0] * word_8A7FC8
                    + dword_8A7FB8
                    + word_8A7F2C[0] * word_8A7FCA
                    + word_8A7F24[0] * word_8A7FC6;
                v49 = dword_8A7FBC;
                goto LABEL_287;
              }
              if ( v26 != 4571154 )
                goto LABEL_630;
              v72 = word_8A7F28[0];
              v73 = word_8A7F24[0];
              v74 = word_8A7F2C[0];
              v26 = word_8A7F24[0] * word_8A7FC0
                  + dword_8A7FD4
                  + word_8A7F28[0] * word_8A7FC2
                  + word_8A7F2C[0] * word_8A7FC4;
              v78 = dword_8A7FD8 + word_8A7F2C[0] * word_8A7FCA;
              v79 = word_8A7F28[0] * word_8A7FC8;
              v80 = word_8A7F24[0] * word_8A7FC6;
              goto LABEL_281;
            }
            if ( v26 == 4562962 )
            {
              v81 = word_8A7F28[0];
              v82 = word_8A7F24[0];
              v83 = word_8A7F2C[0];
              v26 = word_8A7F24[0] * word_8A7FC0
                  + dword_8A7FB4
                  + word_8A7F28[0] * word_8A7FC2
                  + word_8A7F2C[0] * word_8A7FC4;
              v84 = dword_8A7FB8 + word_8A7F2C[0] * word_8A7FCA;
              v85 = word_8A7F28[0] * word_8A7FC8;
              v86 = word_8A7F24[0] * word_8A7FC6;
              goto LABEL_277;
            }
            if ( v26 != 4547602 )
            {
              if ( v26 == 4554770 )
              {
                v26 = word_8A7F24[0] * word_8A7FC0
                    + dword_8A7F94
                    + word_8A7F28[0] * word_8A7FC2
                    + word_8A7F2C[0] * word_8A7FC4;
                v39 = word_8A7F28[0] * word_8A7FC8
                    + dword_8A7F98
                    + word_8A7F2C[0] * word_8A7FCA
                    + word_8A7F24[0] * word_8A7FC6;
                v41 = word_8A7F24[0] * word_8A7FCC
                    + dword_8A7F9C
                    + word_8A7F28[0] * word_8A7FCE
                    + word_8A7F2C[0] * word_8A7FD0;
                v42 = -32768;
                goto LABEL_56;
              }
              if ( v26 != 4555794 )
                goto LABEL_630;
              v76 = word_8A7F28[0];
              v77 = word_8A7F24[0];
              v43 = word_8A7F2C[0];
              v26 = word_8A7F24[0] * word_8A7FC0
                  + dword_8A7F94
                  + word_8A7F28[0] * word_8A7FC2
                  + word_8A7F2C[0] * word_8A7FC4;
              v39 = word_8A7F28[0] * word_8A7FC8
                  + dword_8A7F98
                  + word_8A7F2C[0] * word_8A7FCA
                  + word_8A7F24[0] * word_8A7FC6;
              v49 = dword_8A7F9C;
              goto LABEL_287;
            }
            v90 = word_8A7F12;
            v91 = word_8A7F10;
            v53 = word_8A7F14;
            v26 = word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0;
            goto LABEL_301;
          }
          if ( v26 != 4546578 )
          {
            if ( v26 <= 0x452412 )
            {
              switch ( v26 )
              {
                case 0x452412u:
                  v76 = word_8A7F12;
                  v77 = word_8A7F10;
                  v43 = word_8A7F14;
                  v26 = word_8A7F10 * word_8A7FC0 + dword_8A7FB4 + word_8A7F12 * word_8A7FC2 + word_8A7F14 * word_8A7FC4;
                  v39 = word_8A7F12 * word_8A7FC8 + dword_8A7FB8 + word_8A7F14 * word_8A7FCA + word_8A7F10 * word_8A7FC6;
                  v49 = dword_8A7FBC;
                  break;
                case 0x450012u:
                  v26 = word_8A7F10 * word_8A7FC0 + dword_8A7F94 + word_8A7F12 * word_8A7FC2 + word_8A7F14 * word_8A7FC4;
                  v39 = word_8A7F12 * word_8A7FC8 + dword_8A7F98 + word_8A7F14 * word_8A7FCA + word_8A7F10 * word_8A7FC6;
                  v41 = word_8A7F10 * word_8A7FCC + dword_8A7F9C + word_8A7F12 * word_8A7FCE + word_8A7F14 * word_8A7FD0;
                  v42 = -32768;
                  goto LABEL_56;
                case 0x450412u:
                  v76 = word_8A7F12;
                  v77 = word_8A7F10;
                  v43 = word_8A7F14;
                  v26 = word_8A7F10 * word_8A7FC0 + dword_8A7F94 + word_8A7F12 * word_8A7FC2 + word_8A7F14 * word_8A7FC4;
                  v39 = word_8A7F12 * word_8A7FC8 + dword_8A7F98 + word_8A7F14 * word_8A7FCA + word_8A7F10 * word_8A7FC6;
                  v49 = dword_8A7F9C;
                  break;
                case 0x452012u:
                  v26 = word_8A7F10 * word_8A7FC0 + dword_8A7FB4 + word_8A7F12 * word_8A7FC2 + word_8A7F14 * word_8A7FC4;
                  v39 = word_8A7F12 * word_8A7FC8 + dword_8A7FB8 + word_8A7F14 * word_8A7FCA + word_8A7F10 * word_8A7FC6;
                  v41 = word_8A7F10 * word_8A7FCC + dword_8A7FBC + word_8A7F12 * word_8A7FCE + word_8A7F14 * word_8A7FD0;
                  v42 = -32768;
                  goto LABEL_56;
                default:
                  goto LABEL_630;
              }
              goto LABEL_287;
            }
            if ( v26 == 4538386 )
            {
              v26 = word_8A7F10 * word_8A7FC0 + dword_8A7FD4 + word_8A7F12 * word_8A7FC2 + word_8A7F14 * word_8A7FC4;
              v39 = word_8A7F12 * word_8A7FC8 + dword_8A7FD8 + word_8A7F14 * word_8A7FCA + word_8A7F10 * word_8A7FC6;
              v41 = word_8A7F10 * word_8A7FCC + dword_8A7FDC + word_8A7F12 * word_8A7FCE + word_8A7F14 * word_8A7FD0;
              v42 = -32768;
              goto LABEL_56;
            }
            if ( v26 != 4539410 )
              goto LABEL_630;
            v43 = word_8A7F14;
            v76 = word_8A7F12;
            v77 = word_8A7F10;
            goto LABEL_285;
          }
          v94 = word_8A7F12;
          v95 = word_8A7F10;
          v96 = word_8A7F14;
          v26 = word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0;
LABEL_304:
          v97 = v96 * word_8A7FCA + v94 * word_8A7FC8;
          v98 = v95 * word_8A7FC6;
          goto LABEL_305;
        }
        if ( v26 <= 0x484012 )
        {
          if ( v26 == 4734994 )
          {
            v26 = dword_8A7FD4
                + ((word_8A7F04 * word_8A7F84 + word_8A7F02 * word_8A7F82 + *(__int16 *)word_8A7F00 * word_8A7F80[0]) >> 12);
            v39 = dword_8A7FD8
                + ((word_8A7F02 * word_8A7F88 + *(__int16 *)word_8A7F00 * word_8A7F86 + word_8A7F04 * word_8A7F8A) >> 12);
            v41 = dword_8A7FDC
                + ((word_8A7F04 * word_8A7F90 + word_8A7F02 * word_8A7F8E + *(__int16 *)word_8A7F00 * word_8A7F8C) >> 12);
            v42 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= 0x480412 )
          {
            if ( v26 != 4719634 )
            {
              if ( v26 == 4579346 )
              {
                v94 = word_8A7F28[0];
                v95 = word_8A7F24[0];
                v96 = word_8A7F2C[0];
                v26 = word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0;
                goto LABEL_304;
              }
              if ( v26 == 4580370 )
              {
                v90 = word_8A7F28[0];
                v91 = word_8A7F24[0];
                v53 = word_8A7F2C[0];
                v26 = word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0;
                goto LABEL_301;
              }
              if ( v26 != 4718610 )
                goto LABEL_630;
              v99 = word_8A7F02;
              v100 = *(__int16 *)word_8A7F00;
              v101 = word_8A7F04;
              v102 = word_8A7F04 * word_8A7F84 + word_8A7F02 * word_8A7F82 + *(__int16 *)word_8A7F00 * word_8A7F80[0];
              goto LABEL_296;
            }
            v109 = word_8A7F04;
            v110 = word_8A7F02;
            v111 = *(__int16 *)word_8A7F00;
LABEL_307:
            v26 = dword_8A7F94 + ((v109 * word_8A7F84 + v110 * word_8A7F82 + v111 * word_8A7F80[0]) >> 12);
            v112 = v111 * word_8A7F86 + v109 * word_8A7F8A;
            v113 = v110 * word_8A7F88;
LABEL_308:
            v63 = dword_8A7F98 + ((v113 + v112) >> 12);
            v114 = v111 * word_8A7F8C;
            v115 = v110 * word_8A7F8E;
            v116 = word_8A7F90;
            goto LABEL_309;
          }
          if ( v26 == 4726802 )
          {
            v26 = dword_8A7FB4
                + ((word_8A7F04 * word_8A7F84 + word_8A7F02 * word_8A7F82 + *(__int16 *)word_8A7F00 * word_8A7F80[0]) >> 12);
            v39 = dword_8A7FB8
                + ((word_8A7F02 * word_8A7F88 + *(__int16 *)word_8A7F00 * word_8A7F86 + word_8A7F04 * word_8A7F8A) >> 12);
            v41 = dword_8A7FBC
                + ((word_8A7F04 * word_8A7F90 + word_8A7F02 * word_8A7F8E + *(__int16 *)word_8A7F00 * word_8A7F8C) >> 12);
            v42 = -32768;
            goto LABEL_56;
          }
          if ( v26 != 4727826 )
            goto LABEL_630;
          v118 = word_8A7F04;
          v119 = word_8A7F02;
          v120 = *(__int16 *)word_8A7F00;
          goto LABEL_313;
        }
        if ( v26 > 0x488012 )
        {
          if ( v26 != 4752402 )
          {
            if ( v26 != 4759570 )
              goto LABEL_630;
            v101 = word_8A7F0C;
            v26 = dword_8A7FB4
                + ((word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12);
            v108 = dword_8A7FBC;
            v39 = dword_8A7FB8
                + ((word_8A7F0C * word_8A7F8A + word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86) >> 12);
            v105 = word_8A7F08 * word_8A7F8C;
            v106 = word_8A7F0A * word_8A7F8E;
            v107 = word_8A7F90;
            goto LABEL_299;
          }
          v110 = word_8A7F0A;
          v111 = word_8A7F08;
          v109 = word_8A7F0C;
          v26 = dword_8A7F94
              + ((word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12);
          v112 = word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86;
          v113 = word_8A7F0C * word_8A7F8A;
          goto LABEL_308;
        }
        if ( v26 == 4751378 )
        {
          v99 = word_8A7F0A;
          v100 = word_8A7F08;
          v101 = word_8A7F0C;
          v26 = dword_8A7F94
              + ((word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12);
          v103 = word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86;
          v104 = word_8A7F0C * word_8A7F8A;
          goto LABEL_297;
        }
        if ( v26 != 4736018 )
        {
          if ( v26 != 4743186 )
          {
            if ( v26 != 4744210 )
              goto LABEL_630;
            v127 = word_8A7F04;
            v128 = word_8A7F02;
            v129 = *(__int16 *)word_8A7F00;
LABEL_324:
            v130 = v129 * word_8A7F86 + v127 * word_8A7F8A;
            v26 = (v127 * word_8A7F84 + v128 * word_8A7F82 + v129 * word_8A7F80[0]) >> 12;
            v131 = v128 * word_8A7F88;
LABEL_325:
            v63 = (v131 + v130) >> 12;
            v41 = (v127 * word_8A7F90 + v128 * word_8A7F8E + v129 * word_8A7F8C) >> 12;
            goto LABEL_102;
          }
          v132 = word_8A7F04;
          v133 = word_8A7F02;
          v134 = *(__int16 *)word_8A7F00;
          goto LABEL_327;
        }
        v141 = word_8A7F04;
        v142 = word_8A7F02;
        v143 = *(__int16 *)word_8A7F00;
LABEL_331:
        v26 = dword_8A7FD4 + ((v141 * word_8A7F84 + v142 * word_8A7F82 + v143 * word_8A7F80[0]) >> 12);
        v144 = v143 * word_8A7F86 + v141 * word_8A7F8A;
        v145 = v142 * word_8A7F88;
LABEL_332:
        v63 = dword_8A7FD8 + ((v145 + v144) >> 12);
        v146 = v143 * word_8A7F8C;
        v147 = v142 * word_8A7F8E;
        v148 = word_8A7F90;
        goto LABEL_333;
      }
      if ( v26 <= 0x4C4012 )
      {
        if ( v26 != 4997138 )
        {
          if ( v26 <= 0x4A8012 )
          {
            if ( v26 == 4882450 )
            {
              v101 = word_8A7F0C;
              v26 = dword_8A7F94
                  + ((word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12);
              v39 = dword_8A7F98
                  + ((word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12);
              v105 = word_8A7F08 * word_8A7FAC;
              v106 = word_8A7F0A * word_8A7FAE;
              v107 = word_8A7FB0;
              goto LABEL_298;
            }
            if ( v26 <= 0x49A012 )
            {
              if ( v26 == 4825106 )
              {
                v101 = word_8A7F2C[0];
                v26 = dword_8A7FB4
                    + ((word_8A7F2C[0] * word_8A7F84 + word_8A7F28[0] * word_8A7F82 + word_8A7F24[0] * word_8A7F80[0]) >> 12);
                v108 = dword_8A7FBC;
                v39 = dword_8A7FB8
                    + ((word_8A7F28[0] * word_8A7F88 + word_8A7F24[0] * word_8A7F86 + word_8A7F2C[0] * word_8A7F8A) >> 12);
                v105 = word_8A7F24[0] * word_8A7F8C;
                v106 = word_8A7F28[0] * word_8A7F8E;
                v107 = word_8A7F90;
                goto LABEL_299;
              }
              if ( v26 > 0x492412 )
              {
                if ( v26 > 0x496412 )
                {
                  if ( v26 == 4816914 )
                  {
                    v99 = word_8A7F28[0];
                    v100 = word_8A7F24[0];
                    v101 = word_8A7F2C[0];
                    v102 = word_8A7F2C[0] * word_8A7F84 + word_8A7F28[0] * word_8A7F82 + word_8A7F24[0] * word_8A7F80[0];
LABEL_296:
                    v26 = dword_8A7F94 + (v102 >> 12);
                    v103 = v100 * word_8A7F86 + v101 * word_8A7F8A;
                    v104 = v99 * word_8A7F88;
LABEL_297:
                    v39 = dword_8A7F98 + ((v104 + v103) >> 12);
                    v105 = v100 * word_8A7F8C;
                    v106 = v99 * word_8A7F8E;
                    v107 = word_8A7F90;
LABEL_298:
                    v108 = dword_8A7F9C;
LABEL_299:
                    v41 = v108 + ((v101 * v107 + v106 + v105) >> 12);
                    v42 = -32768;
                    goto LABEL_56;
                  }
                  if ( v26 != 4817938 )
                    goto LABEL_630;
                  v109 = word_8A7F2C[0];
                  v110 = word_8A7F28[0];
                  v111 = word_8A7F24[0];
                  goto LABEL_307;
                }
                if ( v26 == 4809746 )
                {
                  v128 = word_8A7F12;
                  v129 = word_8A7F10;
                  v127 = word_8A7F14;
                  v130 = word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86;
                  v26 = (word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12;
                  v131 = word_8A7F14 * word_8A7F8A;
                  goto LABEL_325;
                }
                if ( v26 == 4800530 )
                {
                  v101 = word_8A7F14;
                  v26 = dword_8A7FD4
                      + ((word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12);
                  v108 = dword_8A7FDC;
                  v39 = dword_8A7FD8
                      + ((word_8A7F14 * word_8A7F8A + word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86) >> 12);
                  v105 = word_8A7F10 * word_8A7F8C;
                  v106 = word_8A7F12 * word_8A7F8E;
                  v107 = word_8A7F90;
                  goto LABEL_299;
                }
                if ( v26 != 4801554 )
                {
                  if ( v26 != 4808722 )
                    goto LABEL_630;
                  v133 = word_8A7F12;
                  v134 = word_8A7F10;
                  v132 = word_8A7F14;
                  v135 = word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86;
                  v26 = (word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12;
                  v136 = word_8A7F14 * word_8A7F8A;
                  goto LABEL_328;
                }
                v142 = word_8A7F12;
                v143 = word_8A7F10;
                v141 = word_8A7F14;
                v26 = dword_8A7FD4
                    + ((word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12);
                v144 = word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86;
                v145 = word_8A7F14 * word_8A7F8A;
              }
              else
              {
                if ( v26 == 4793362 )
                {
                  v119 = word_8A7F12;
                  v120 = word_8A7F10;
                  v118 = word_8A7F14;
                  v26 = dword_8A7FB4
                      + ((word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12);
                  v121 = word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86;
                  v122 = word_8A7F14 * word_8A7F8A;
                  goto LABEL_314;
                }
                if ( v26 > 0x48E412 )
                {
                  if ( v26 == 4784146 )
                  {
                    v99 = word_8A7F12;
                    v100 = word_8A7F10;
                    v101 = word_8A7F14;
                    v26 = dword_8A7F94
                        + ((word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12);
                    v103 = word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86;
                    v104 = word_8A7F14 * word_8A7F8A;
                    goto LABEL_297;
                  }
                  if ( v26 != 4785170 )
                  {
                    if ( v26 != 4792338 )
                      goto LABEL_630;
                    v101 = word_8A7F14;
                    v26 = dword_8A7FB4
                        + ((word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12);
                    v108 = dword_8A7FBC;
                    v39 = dword_8A7FB8
                        + ((word_8A7F14 * word_8A7F8A + word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86) >> 12);
                    v105 = word_8A7F10 * word_8A7F8C;
                    v106 = word_8A7F12 * word_8A7F8E;
                    v107 = word_8A7F90;
                    goto LABEL_299;
                  }
                  v110 = word_8A7F12;
                  v111 = word_8A7F10;
                  v109 = word_8A7F14;
                  v26 = dword_8A7F94
                      + ((word_8A7F14 * word_8A7F84 + word_8A7F12 * word_8A7F82 + word_8A7F10 * word_8A7F80[0]) >> 12);
                  v112 = word_8A7F12 * word_8A7F88 + word_8A7F10 * word_8A7F86;
                  v113 = word_8A7F14 * word_8A7F8A;
                  goto LABEL_308;
                }
                if ( v26 == 4776978 )
                {
                  v128 = word_8A7F0A;
                  v129 = word_8A7F08;
                  v127 = word_8A7F0C;
                  v130 = word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86;
                  v26 = (word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12;
                  v131 = word_8A7F0C * word_8A7F8A;
                  goto LABEL_325;
                }
                if ( v26 == 4767762 )
                {
                  v101 = word_8A7F0C;
                  v26 = dword_8A7FD4
                      + ((word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12);
                  v108 = dword_8A7FDC;
                  v39 = dword_8A7FD8
                      + ((word_8A7F0C * word_8A7F8A + word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86) >> 12);
                  v105 = word_8A7F08 * word_8A7F8C;
                  v106 = word_8A7F0A * word_8A7F8E;
                  v107 = word_8A7F90;
                  goto LABEL_299;
                }
                if ( v26 != 4768786 )
                {
                  if ( v26 != 4775954 )
                    goto LABEL_630;
                  v133 = word_8A7F0A;
                  v134 = word_8A7F08;
                  v132 = word_8A7F0C;
                  v135 = word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86;
                  v26 = (word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12;
                  v136 = word_8A7F0C * word_8A7F8A;
                  goto LABEL_328;
                }
                v142 = word_8A7F0A;
                v143 = word_8A7F08;
                v141 = word_8A7F0C;
                v26 = dword_8A7FD4
                    + ((word_8A7F0C * word_8A7F84 + word_8A7F0A * word_8A7F82 + word_8A7F08 * word_8A7F80[0]) >> 12);
                v144 = word_8A7F0A * word_8A7F88 + word_8A7F08 * word_8A7F86;
                v145 = word_8A7F0C * word_8A7F8A;
              }
              goto LABEL_332;
            }
            if ( v26 <= 0x4A0412 )
            {
              if ( v26 == 4850706 )
              {
                v109 = word_8A7F04;
                v26 = dword_8A7F94
                    + ((word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12);
                v63 = dword_8A7F98
                    + ((word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12);
                v114 = *(__int16 *)word_8A7F00 * word_8A7FAC;
                v115 = word_8A7F02 * word_8A7FAE;
                v116 = word_8A7FB0;
                goto LABEL_309;
              }
              if ( v26 > 0x49E012 )
              {
                if ( v26 != 4842514 )
                {
                  if ( v26 != 4849682 )
                    goto LABEL_630;
                  v101 = word_8A7F04;
                  v26 = dword_8A7F94
                      + ((word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12);
                  v39 = dword_8A7F98
                      + ((word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12);
                  v105 = *(__int16 *)word_8A7F00 * word_8A7FAC;
                  v106 = word_8A7F02 * word_8A7FAE;
                  v107 = word_8A7FB0;
                  goto LABEL_298;
                }
                v127 = word_8A7F2C[0];
                v128 = word_8A7F28[0];
                v129 = word_8A7F24[0];
                goto LABEL_324;
              }
              switch ( v26 )
              {
                case 0x49E012u:
                  v132 = word_8A7F2C[0];
                  v133 = word_8A7F28[0];
                  v134 = word_8A7F24[0];
LABEL_327:
                  v135 = v134 * word_8A7F86 + v132 * word_8A7F8A;
                  v26 = (v132 * word_8A7F84 + v133 * word_8A7F82 + v134 * word_8A7F80[0]) >> 12;
                  v136 = v133 * word_8A7F88;
LABEL_328:
                  v137 = v136 + v135;
                  v138 = v134 * word_8A7F8C;
                  v139 = v133 * word_8A7F8E;
                  v140 = word_8A7F90;
LABEL_329:
                  v39 = v137 >> 12;
                  v41 = (v132 * v140 + v139 + v138) >> 12;
                  v42 = -32768;
                  goto LABEL_56;
                case 0x49A412u:
                  v118 = word_8A7F2C[0];
                  v119 = word_8A7F28[0];
                  v120 = word_8A7F24[0];
LABEL_313:
                  v26 = dword_8A7FB4 + ((v118 * word_8A7F84 + v119 * word_8A7F82 + v120 * word_8A7F80[0]) >> 12);
                  v121 = v120 * word_8A7F86 + v118 * word_8A7F8A;
                  v122 = v119 * word_8A7F88;
LABEL_314:
                  v63 = dword_8A7FB8 + ((v122 + v121) >> 12);
                  v123 = v120 * word_8A7F8C;
                  v124 = v119 * word_8A7F8E;
                  v125 = word_8A7F90;
                  goto LABEL_315;
                case 0x49C012u:
                  v101 = word_8A7F2C[0];
                  v26 = dword_8A7FD4
                      + ((word_8A7F2C[0] * word_8A7F84 + word_8A7F28[0] * word_8A7F82 + word_8A7F24[0] * word_8A7F80[0]) >> 12);
                  v108 = dword_8A7FDC;
                  v39 = dword_8A7FD8
                      + ((word_8A7F28[0] * word_8A7F88 + word_8A7F24[0] * word_8A7F86 + word_8A7F2C[0] * word_8A7F8A) >> 12);
                  v105 = word_8A7F24[0] * word_8A7F8C;
                  v106 = word_8A7F28[0] * word_8A7F8E;
                  v107 = word_8A7F90;
                  goto LABEL_299;
              }
              if ( v26 != 4834322 )
                goto LABEL_630;
              v141 = word_8A7F2C[0];
              v142 = word_8A7F28[0];
              v143 = word_8A7F24[0];
              goto LABEL_331;
            }
            if ( v26 <= 0x4A4412 )
            {
              if ( v26 == 4867090 )
              {
                v141 = word_8A7F04;
                v26 = dword_8A7FD4
                    + ((word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12);
                v63 = dword_8A7FD8
                    + ((word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12);
                v146 = *(__int16 *)word_8A7F00 * word_8A7FAC;
                v147 = word_8A7F02 * word_8A7FAE;
                v148 = word_8A7FB0;
                goto LABEL_333;
              }
              if ( v26 == 4857874 )
              {
                v101 = word_8A7F04;
                v26 = dword_8A7FB4
                    + ((word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12);
                v108 = dword_8A7FBC;
                v39 = dword_8A7FB8
                    + ((word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12);
                v105 = *(__int16 *)word_8A7F00 * word_8A7FAC;
                v106 = word_8A7F02 * word_8A7FAE;
                v107 = word_8A7FB0;
                goto LABEL_299;
              }
              if ( v26 != 4858898 )
              {
                if ( v26 != 4866066 )
                  goto LABEL_630;
                v101 = word_8A7F04;
                v26 = dword_8A7FD4
                    + ((word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12);
                v108 = dword_8A7FDC;
                v39 = dword_8A7FD8
                    + ((word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12);
                v105 = *(__int16 *)word_8A7F00 * word_8A7FAC;
                v106 = word_8A7F02 * word_8A7FAE;
                v107 = word_8A7FB0;
                goto LABEL_299;
              }
              v118 = word_8A7F04;
              v26 = dword_8A7FB4
                  + ((word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12);
              v63 = dword_8A7FB8
                  + ((word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12);
              v123 = *(__int16 *)word_8A7F00 * word_8A7FAC;
              v124 = word_8A7F02 * word_8A7FAE;
              v125 = word_8A7FB0;
LABEL_315:
              v126 = v118 * v125 + v124 + v123;
              v68 = dword_8A7FBC;
              v67 = v126 >> 12;
              goto LABEL_101;
            }
            if ( v26 == 4874258 )
            {
              v132 = word_8A7F04;
              v137 = word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6;
              v138 = *(__int16 *)word_8A7F00 * word_8A7FAC;
              v26 = (word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12;
              v139 = word_8A7F02 * word_8A7FAE;
              v140 = word_8A7FB0;
              goto LABEL_329;
            }
            if ( v26 != 4875282 )
              goto LABEL_630;
            v26 = (word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12;
            v63 = (word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12;
            v41 = (word_8A7F04 * word_8A7FB0 + word_8A7F02 * word_8A7FAE + *(__int16 *)word_8A7F00 * word_8A7FAC) >> 12;
LABEL_102:
            dword_8A7F64 = v26;
            dword_8A7F68 = v63;
            dword_8A7F6C = v41;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F24 = v26;
              }
              else
              {
                dword_8A7FFC = -2130706432;
                *(_DWORD *)word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC = -2130706432;
              *(_DWORD *)word_8A7F24 = 0;
            }
            if ( v63 >= 0 )
            {
              if ( v63 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F28 = v63;
              }
              else
              {
                dword_8A7FFC |= 0x80800000;
                *(_DWORD *)word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= 0x80800000;
              *(_DWORD *)word_8A7F28 = 0;
            }
            if ( v41 >= 0 )
              goto LABEL_541;
LABEL_573:
            LOBYTE(v26) = dword_8A7FFC;
            *(_DWORD *)word_8A7F2C = 0;
            dword_8A7FFC |= 0x400000u;
            return v26;
          }
          if ( v26 <= 0x4B6012 )
          {
            if ( v26 == 4939794 )
            {
              v132 = word_8A7F14;
              v137 = word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6;
              v138 = word_8A7F10 * word_8A7FAC;
              v26 = (word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12;
              v139 = word_8A7F12 * word_8A7FAE;
              v140 = word_8A7FB0;
              goto LABEL_329;
            }
            if ( v26 <= 0x4AE412 )
            {
              if ( v26 == 4908050 )
              {
                v26 = (word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12;
                v63 = (word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12;
                v41 = (word_8A7F0C * word_8A7FB0 + word_8A7F0A * word_8A7FAE + word_8A7F08 * word_8A7FAC) >> 12;
                goto LABEL_102;
              }
              if ( v26 <= 0x4AC012 )
              {
                switch ( v26 )
                {
                  case 0x4AC012u:
                    v101 = word_8A7F0C;
                    v26 = dword_8A7FD4
                        + ((word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12);
                    v108 = dword_8A7FDC;
                    v39 = dword_8A7FD8
                        + ((word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12);
                    v105 = word_8A7F08 * word_8A7FAC;
                    v106 = word_8A7F0A * word_8A7FAE;
                    v107 = word_8A7FB0;
                    goto LABEL_299;
                  case 0x4A8412u:
                    v109 = word_8A7F0C;
                    v26 = dword_8A7F94
                        + ((word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12);
                    v63 = dword_8A7F98
                        + ((word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12);
                    v114 = word_8A7F08 * word_8A7FAC;
                    v115 = word_8A7F0A * word_8A7FAE;
                    v116 = word_8A7FB0;
                    goto LABEL_309;
                  case 0x4AA012u:
                    v101 = word_8A7F0C;
                    v26 = dword_8A7FB4
                        + ((word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12);
                    v108 = dword_8A7FBC;
                    v39 = dword_8A7FB8
                        + ((word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12);
                    v105 = word_8A7F08 * word_8A7FAC;
                    v106 = word_8A7F0A * word_8A7FAE;
                    v107 = word_8A7FB0;
                    goto LABEL_299;
                }
                if ( v26 != 4891666 )
                  goto LABEL_630;
                v118 = word_8A7F0C;
                v26 = dword_8A7FB4
                    + ((word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12);
                v63 = dword_8A7FB8
                    + ((word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12);
                v123 = word_8A7F08 * word_8A7FAC;
                v124 = word_8A7F0A * word_8A7FAE;
                v125 = word_8A7FB0;
                goto LABEL_315;
              }
              if ( v26 != 4899858 )
              {
                if ( v26 != 4907026 )
                  goto LABEL_630;
                v132 = word_8A7F0C;
                v137 = word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6;
                v138 = word_8A7F08 * word_8A7FAC;
                v26 = (word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12;
                v139 = word_8A7F0A * word_8A7FAE;
                v140 = word_8A7FB0;
                goto LABEL_329;
              }
              v141 = word_8A7F0C;
              v26 = dword_8A7FD4
                  + ((word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12);
              v63 = dword_8A7FD8
                  + ((word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12);
              v146 = word_8A7F08 * word_8A7FAC;
              v147 = word_8A7F0A * word_8A7FAE;
              v148 = word_8A7FB0;
LABEL_333:
              v149 = v141 * v148 + v147 + v146;
              v68 = dword_8A7FDC;
              v67 = v149 >> 12;
              goto LABEL_101;
            }
            if ( v26 > 0x4B2412 )
            {
              if ( v26 == 4931602 )
              {
                v101 = word_8A7F14;
                v26 = dword_8A7FD4
                    + ((word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12);
                v108 = dword_8A7FDC;
                v39 = dword_8A7FD8
                    + ((word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12);
                v105 = word_8A7F10 * word_8A7FAC;
                v106 = word_8A7F12 * word_8A7FAE;
                v107 = word_8A7FB0;
                goto LABEL_299;
              }
              if ( v26 != 4932626 )
                goto LABEL_630;
              v141 = word_8A7F14;
              v26 = dword_8A7FD4
                  + ((word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12);
              v63 = dword_8A7FD8
                  + ((word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12);
              v146 = word_8A7F10 * word_8A7FAC;
              v147 = word_8A7F12 * word_8A7FAE;
              v148 = word_8A7FB0;
              goto LABEL_333;
            }
            if ( v26 == 4924434 )
            {
              v118 = word_8A7F14;
              v26 = dword_8A7FB4
                  + ((word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12);
              v63 = dword_8A7FB8
                  + ((word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12);
              v123 = word_8A7F10 * word_8A7FAC;
              v124 = word_8A7F12 * word_8A7FAE;
              v125 = word_8A7FB0;
              goto LABEL_315;
            }
            if ( v26 == 4915218 )
            {
              v101 = word_8A7F14;
              v26 = dword_8A7F94
                  + ((word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12);
              v39 = dword_8A7F98
                  + ((word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12);
              v105 = word_8A7F10 * word_8A7FAC;
              v106 = word_8A7F12 * word_8A7FAE;
              v107 = word_8A7FB0;
              goto LABEL_298;
            }
            if ( v26 != 4916242 )
            {
              if ( v26 != 4923410 )
                goto LABEL_630;
              v101 = word_8A7F14;
              v26 = dword_8A7FB4
                  + ((word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12);
              v108 = dword_8A7FBC;
              v39 = dword_8A7FB8
                  + ((word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12);
              v105 = word_8A7F10 * word_8A7FAC;
              v106 = word_8A7F12 * word_8A7FAE;
              v107 = word_8A7FB0;
              goto LABEL_299;
            }
            v109 = word_8A7F14;
            v26 = dword_8A7F94
                + ((word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12);
            v63 = dword_8A7F98
                + ((word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12);
            v114 = word_8A7F10 * word_8A7FAC;
            v115 = word_8A7F12 * word_8A7FAE;
            v116 = word_8A7FB0;
LABEL_309:
            v117 = v109 * v116 + v115 + v114;
            v68 = dword_8A7F9C;
            v67 = v117 >> 12;
            goto LABEL_101;
          }
          if ( v26 <= 0x4BC412 )
          {
            if ( v26 == 4965394 )
            {
              v141 = word_8A7F2C[0];
              v26 = dword_8A7FD4
                  + ((word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12);
              v63 = dword_8A7FD8
                  + ((word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6) >> 12);
              v146 = word_8A7F24[0] * word_8A7FAC;
              v147 = word_8A7F28[0] * word_8A7FAE;
              v148 = word_8A7FB0;
              goto LABEL_333;
            }
            if ( v26 > 0x4BA012 )
            {
              if ( v26 != 4957202 )
              {
                if ( v26 != 4964370 )
                  goto LABEL_630;
                v101 = word_8A7F2C[0];
                v26 = dword_8A7FD4
                    + ((word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12);
                v108 = dword_8A7FDC;
                v39 = dword_8A7FD8
                    + ((word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6) >> 12);
                v105 = word_8A7F24[0] * word_8A7FAC;
                v106 = word_8A7F28[0] * word_8A7FAE;
                v107 = word_8A7FB0;
                goto LABEL_299;
              }
              v118 = word_8A7F2C[0];
              v26 = dword_8A7FB4
                  + ((word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12);
              v63 = dword_8A7FB8
                  + ((word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6) >> 12);
              v123 = word_8A7F24[0] * word_8A7FAC;
              v124 = word_8A7F28[0] * word_8A7FAE;
              v125 = word_8A7FB0;
              goto LABEL_315;
            }
            switch ( v26 )
            {
              case 0x4BA012u:
                v101 = word_8A7F2C[0];
                v26 = dword_8A7FB4
                    + ((word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12);
                v108 = dword_8A7FBC;
                v39 = dword_8A7FB8
                    + ((word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6) >> 12);
                v105 = word_8A7F24[0] * word_8A7FAC;
                v106 = word_8A7F28[0] * word_8A7FAE;
                v107 = word_8A7FB0;
                goto LABEL_299;
              case 0x4B6412u:
                v26 = (word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12;
                v63 = (word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12;
                v41 = (word_8A7F14 * word_8A7FB0 + word_8A7F12 * word_8A7FAE + word_8A7F10 * word_8A7FAC) >> 12;
                goto LABEL_102;
              case 0x4B8012u:
                v101 = word_8A7F2C[0];
                v26 = dword_8A7F94
                    + ((word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12);
                v39 = dword_8A7F98
                    + ((word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6) >> 12);
                v105 = word_8A7F24[0] * word_8A7FAC;
                v106 = word_8A7F28[0] * word_8A7FAE;
                v107 = word_8A7FB0;
                goto LABEL_298;
            }
            if ( v26 != 4949010 )
              goto LABEL_630;
            v109 = word_8A7F2C[0];
            v26 = dword_8A7F94
                + ((word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12);
            v63 = dword_8A7F98
                + ((word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6) >> 12);
            v114 = word_8A7F24[0] * word_8A7FAC;
            v115 = word_8A7F28[0] * word_8A7FAE;
            v116 = word_8A7FB0;
            goto LABEL_309;
          }
          if ( v26 <= 0x4C0412 )
          {
            if ( v26 != 4981778 )
            {
              if ( v26 == 4972562 )
              {
                v132 = word_8A7F2C[0];
                v137 = word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6;
                v138 = word_8A7F24[0] * word_8A7FAC;
                v26 = (word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12;
                v139 = word_8A7F28[0] * word_8A7FAE;
                v140 = word_8A7FB0;
                goto LABEL_329;
              }
              if ( v26 == 4973586 )
              {
                v26 = (word_8A7F2C[0] * word_8A7FA4 + word_8A7F28[0] * word_8A7FA2 + word_8A7F24[0] * word_8A7FA0) >> 12;
                v63 = (word_8A7F2C[0] * word_8A7FAA + word_8A7F28[0] * word_8A7FA8 + word_8A7F24[0] * word_8A7FA6) >> 12;
                v41 = (word_8A7F2C[0] * word_8A7FB0 + word_8A7F28[0] * word_8A7FAE + word_8A7F24[0] * word_8A7FAC) >> 12;
                goto LABEL_102;
              }
              if ( v26 != 4980754 )
                goto LABEL_630;
              v150 = word_8A7F02;
              v151 = *(__int16 *)word_8A7F00;
              v101 = word_8A7F04;
              v26 = dword_8A7F94
                  + ((word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12);
              v152 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
              v153 = word_8A7F04 * word_8A7FCA;
LABEL_528:
              v39 = dword_8A7F98 + ((v153 + v152) >> 12);
              v105 = v151 * word_8A7FCC;
              v106 = v150 * word_8A7FCE;
              v107 = word_8A7FD0;
              goto LABEL_298;
            }
            v154 = word_8A7F02;
            v155 = *(__int16 *)word_8A7F00;
            v109 = word_8A7F04;
            v26 = dword_8A7F94
                + ((word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12);
            v156 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
            v157 = word_8A7F04 * word_8A7FCA;
            goto LABEL_526;
          }
          if ( (int *)v26 != (int *)((char *)&spu_ram[93124] + 2) )
          {
            if ( (int *)v26 != (int *)((char *)&spu_ram[93380] + 2) )
              goto LABEL_630;
            v158 = word_8A7F02;
            v159 = *(__int16 *)word_8A7F00;
            v118 = word_8A7F04;
            v26 = dword_8A7FB4
                + ((word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12);
            v160 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
            v161 = word_8A7F04 * word_8A7FCA;
            goto LABEL_506;
          }
          v162 = word_8A7F02;
          v163 = *(__int16 *)word_8A7F00;
          v101 = word_8A7F04;
          v26 = dword_8A7FB4
              + ((word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12);
          v164 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
          v165 = word_8A7F04 * word_8A7FCA;
LABEL_530:
          v108 = dword_8A7FBC;
          v39 = dword_8A7FB8 + ((v165 + v164) >> 12);
          v105 = v163 * word_8A7FCC;
          v106 = v162 * word_8A7FCE;
          v107 = word_8A7FD0;
          goto LABEL_299;
        }
        v166 = word_8A7F02;
        v167 = *(__int16 *)word_8A7F00;
        v101 = word_8A7F04;
        v26 = dword_8A7FD4
            + ((word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12);
        v168 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
        v169 = word_8A7F04 * word_8A7FCA;
LABEL_519:
        v108 = dword_8A7FDC;
        v39 = dword_8A7FD8 + ((v169 + v168) >> 12);
        v105 = v167 * word_8A7FCC;
        v106 = v166 * word_8A7FCE;
        v107 = word_8A7FD0;
        goto LABEL_299;
      }
      if ( v26 <= 0x680029 )
      {
        if ( v26 == 6815785 )
        {
          LOBYTE(v26) = sub_410420();
          return v26;
        }
        if ( v26 <= 0x4D2412 )
        {
          if ( v26 == 5055506 )
          {
            v158 = word_8A7F12;
            v159 = word_8A7F10;
            v118 = word_8A7F14;
            v26 = dword_8A7FB4
                + ((word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0) >> 12);
            v160 = word_8A7F14 * word_8A7FCA + word_8A7F12 * word_8A7FC8;
            v161 = word_8A7F10 * word_8A7FC6;
LABEL_506:
            v63 = dword_8A7FB8 + ((v161 + v160) >> 12);
            v123 = v159 * word_8A7FCC;
            v124 = v158 * word_8A7FCE;
            v125 = word_8A7FD0;
            goto LABEL_315;
          }
          if ( v26 <= 0x4CC012 )
          {
            if ( v26 == 5029906 )
            {
              v101 = word_8A7F0C;
              v26 = dword_8A7FD4
                  + ((word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0) >> 12);
              v108 = dword_8A7FDC;
              v39 = dword_8A7FD8
                  + ((word_8A7F08 * word_8A7FC6 + word_8A7F0C * word_8A7FCA + word_8A7F0A * word_8A7FC8) >> 12);
              v105 = word_8A7F08 * word_8A7FCC;
              v106 = word_8A7F0A * word_8A7FCE;
              v107 = word_8A7FD0;
              goto LABEL_299;
            }
            if ( v26 > 0x4C8012 )
            {
              if ( v26 == 5014546 )
              {
                v109 = word_8A7F0C;
                v26 = dword_8A7F94
                    + ((word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0) >> 12);
                v63 = dword_8A7F98
                    + ((word_8A7F08 * word_8A7FC6 + word_8A7F0C * word_8A7FCA + word_8A7F0A * word_8A7FC8) >> 12);
                v114 = word_8A7F08 * word_8A7FCC;
                v115 = word_8A7F0A * word_8A7FCE;
                v116 = word_8A7FD0;
                goto LABEL_309;
              }
              if ( v26 == 5021714 )
              {
                v101 = word_8A7F0C;
                v26 = dword_8A7FB4
                    + ((word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0) >> 12);
                v108 = dword_8A7FBC;
                v39 = dword_8A7FB8
                    + ((word_8A7F08 * word_8A7FC6 + word_8A7F0C * word_8A7FCA + word_8A7F0A * word_8A7FC8) >> 12);
                v105 = word_8A7F08 * word_8A7FCC;
                v106 = word_8A7F0A * word_8A7FCE;
                v107 = word_8A7FD0;
                goto LABEL_299;
              }
              if ( v26 != 5022738 )
                goto LABEL_630;
              v118 = word_8A7F0C;
              v26 = dword_8A7FB4
                  + ((word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0) >> 12);
              v63 = dword_8A7FB8
                  + ((word_8A7F08 * word_8A7FC6 + word_8A7F0C * word_8A7FCA + word_8A7F0A * word_8A7FC8) >> 12);
              v123 = word_8A7F08 * word_8A7FCC;
              v124 = word_8A7F0A * word_8A7FCE;
              v125 = word_8A7FD0;
              goto LABEL_315;
            }
            if ( v26 == 5013522 )
            {
              v101 = word_8A7F0C;
              v26 = dword_8A7F94
                  + ((word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0) >> 12);
              v39 = dword_8A7F98
                  + ((word_8A7F08 * word_8A7FC6 + word_8A7F0C * word_8A7FCA + word_8A7F0A * word_8A7FC8) >> 12);
              v105 = word_8A7F08 * word_8A7FCC;
              v106 = word_8A7F0A * word_8A7FCE;
              v107 = word_8A7FD0;
              goto LABEL_298;
            }
            if ( v26 != 4998162 )
            {
              if ( v26 != 5005330 )
              {
                if ( v26 != 5006354 )
                  goto LABEL_630;
                v170 = word_8A7F02;
                v171 = *(__int16 *)word_8A7F00;
                v172 = word_8A7F04;
                v173 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
                v26 = (word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12;
                v174 = word_8A7F04 * word_8A7FCA;
                goto LABEL_522;
              }
              v175 = word_8A7F02;
              v176 = *(__int16 *)word_8A7F00;
              v132 = word_8A7F04;
              v177 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
              v26 = (word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12;
              v178 = word_8A7F04 * word_8A7FCA;
LABEL_516:
              v137 = v178 + v177;
              v138 = v176 * word_8A7FCC;
              v139 = v175 * word_8A7FCE;
              v140 = word_8A7FD0;
              goto LABEL_329;
            }
            v179 = word_8A7F02;
            v180 = *(__int16 *)word_8A7F00;
            v141 = word_8A7F04;
            v26 = dword_8A7FD4
                + ((word_8A7F04 * word_8A7FC4 + word_8A7F02 * word_8A7FC2 + *(__int16 *)word_8A7F00 * word_8A7FC0) >> 12);
            v181 = word_8A7F02 * word_8A7FC8 + *(__int16 *)word_8A7F00 * word_8A7FC6;
            v182 = word_8A7F04 * word_8A7FCA;
LABEL_537:
            v63 = dword_8A7FD8 + ((v182 + v181) >> 12);
            v146 = v180 * word_8A7FCC;
            v147 = v179 * word_8A7FCE;
            v148 = word_8A7FD0;
            goto LABEL_333;
          }
          if ( v26 > 0x4D0012 )
          {
            if ( v26 != 5047314 )
            {
              if ( v26 != 5054482 )
                goto LABEL_630;
              v101 = word_8A7F14;
              v26 = dword_8A7FB4
                  + ((word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0) >> 12);
              v108 = dword_8A7FBC;
              v39 = dword_8A7FB8
                  + ((word_8A7F10 * word_8A7FC6 + word_8A7F14 * word_8A7FCA + word_8A7F12 * word_8A7FC8) >> 12);
              v105 = word_8A7F10 * word_8A7FCC;
              v106 = word_8A7F12 * word_8A7FCE;
              v107 = word_8A7FD0;
              goto LABEL_299;
            }
            v109 = word_8A7F14;
            v26 = dword_8A7F94
                + ((word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0) >> 12);
            v63 = dword_8A7F98
                + ((word_8A7F10 * word_8A7FC6 + word_8A7F14 * word_8A7FCA + word_8A7F12 * word_8A7FC8) >> 12);
            v114 = word_8A7F10 * word_8A7FCC;
            v115 = word_8A7F12 * word_8A7FCE;
            v116 = word_8A7FD0;
            goto LABEL_309;
          }
          if ( v26 == 5046290 )
          {
            v101 = word_8A7F14;
            v26 = dword_8A7F94
                + ((word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0) >> 12);
            v39 = dword_8A7F98
                + ((word_8A7F10 * word_8A7FC6 + word_8A7F14 * word_8A7FCA + word_8A7F12 * word_8A7FC8) >> 12);
            v105 = word_8A7F10 * word_8A7FCC;
            v106 = word_8A7F12 * word_8A7FCE;
            v107 = word_8A7FD0;
            goto LABEL_298;
          }
          if ( v26 == 5030930 )
          {
            v141 = word_8A7F0C;
            v26 = dword_8A7FD4
                + ((word_8A7F0C * word_8A7FC4 + word_8A7F0A * word_8A7FC2 + word_8A7F08 * word_8A7FC0) >> 12);
            v63 = dword_8A7FD8
                + ((word_8A7F08 * word_8A7FC6 + word_8A7F0C * word_8A7FCA + word_8A7F0A * word_8A7FC8) >> 12);
            v146 = word_8A7F08 * word_8A7FCC;
            v147 = word_8A7F0A * word_8A7FCE;
            v148 = word_8A7FD0;
            goto LABEL_333;
          }
          if ( v26 != 5038098 )
          {
            if ( v26 != 5039122 )
              goto LABEL_630;
            v172 = word_8A7F0C;
            v170 = word_8A7F0A;
            v171 = word_8A7F08;
            goto LABEL_521;
          }
          v132 = word_8A7F0C;
          v175 = word_8A7F0A;
          v176 = word_8A7F08;
          goto LABEL_515;
        }
        if ( v26 <= 0x4DA012 )
        {
          if ( v26 == 5087250 )
          {
            v162 = word_8A7F28[0];
            v163 = word_8A7F24[0];
            v101 = word_8A7F2C[0];
            v26 = dword_8A7FB4
                + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
            v164 = word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8;
            v165 = word_8A7F24[0] * word_8A7FC6;
            goto LABEL_530;
          }
          if ( v26 > 0x4D6412 )
          {
            if ( v26 == 5079058 )
            {
              v150 = word_8A7F28[0];
              v151 = word_8A7F24[0];
              v101 = word_8A7F2C[0];
              v26 = dword_8A7F94
                  + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
              v152 = word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8;
              v153 = word_8A7F24[0] * word_8A7FC6;
              goto LABEL_528;
            }
            if ( v26 != 5080082 )
              goto LABEL_630;
            v154 = word_8A7F28[0];
            v155 = word_8A7F24[0];
            v109 = word_8A7F2C[0];
            v26 = dword_8A7F94
                + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
            v156 = word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8;
            v157 = word_8A7F24[0] * word_8A7FC6;
LABEL_526:
            v63 = dword_8A7F98 + ((v157 + v156) >> 12);
            v114 = v155 * word_8A7FCC;
            v115 = v154 * word_8A7FCE;
            v116 = word_8A7FD0;
            goto LABEL_309;
          }
          switch ( v26 )
          {
            case 0x4D6412u:
              v172 = word_8A7F14;
              v170 = word_8A7F12;
              v171 = word_8A7F10;
LABEL_521:
              v173 = v172 * word_8A7FCA + v170 * word_8A7FC8;
              v26 = (v172 * word_8A7FC4 + v170 * word_8A7FC2 + v171 * word_8A7FC0) >> 12;
              v174 = v171 * word_8A7FC6;
LABEL_522:
              v63 = (v174 + v173) >> 12;
              v41 = (v172 * word_8A7FD0 + v170 * word_8A7FCE + v171 * word_8A7FCC) >> 12;
              goto LABEL_102;
            case 0x4D4012u:
              v166 = word_8A7F12;
              v167 = word_8A7F10;
              v101 = word_8A7F14;
              v26 = dword_8A7FD4
                  + ((word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0) >> 12);
              v168 = word_8A7F14 * word_8A7FCA + word_8A7F12 * word_8A7FC8;
              v169 = word_8A7F10 * word_8A7FC6;
              goto LABEL_519;
            case 0x4D4412u:
              v141 = word_8A7F14;
              v26 = dword_8A7FD4
                  + ((word_8A7F14 * word_8A7FC4 + word_8A7F12 * word_8A7FC2 + word_8A7F10 * word_8A7FC0) >> 12);
              v63 = dword_8A7FD8
                  + ((word_8A7F10 * word_8A7FC6 + word_8A7F14 * word_8A7FCA + word_8A7F12 * word_8A7FC8) >> 12);
              v146 = word_8A7F10 * word_8A7FCC;
              v147 = word_8A7F12 * word_8A7FCE;
              v148 = word_8A7FD0;
              goto LABEL_333;
          }
          if ( v26 != 5070866 )
            goto LABEL_630;
          v132 = word_8A7F14;
          v175 = word_8A7F12;
          v176 = word_8A7F10;
LABEL_515:
          v177 = v132 * word_8A7FCA + v175 * word_8A7FC8;
          v26 = (v132 * word_8A7FC4 + v175 * word_8A7FC2 + v176 * word_8A7FC0) >> 12;
          v178 = v176 * word_8A7FC6;
          goto LABEL_516;
        }
        if ( v26 <= 0x4DE012 )
        {
          switch ( v26 )
          {
            case 0x4DE012u:
              v26 = (word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12;
              v183 = (word_8A7F24[0] * word_8A7FC6 + word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8) >> 12;
              v41 = (word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12;
              v42 = -32768;
              dword_8A7F64 = v26;
              dword_8A7F68 = v183;
              dword_8A7F6C = v41;
              if ( (int)v26 >= -32768 )
              {
                if ( (int)v26 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F24 = (word_8A7F2C[0] * word_8A7FC4
                                          + word_8A7F28[0] * word_8A7FC2
                                          + word_8A7F24[0] * word_8A7FC0) >> 12;
                }
                else
                {
                  dword_8A7FFC = -2130706432;
                  *(_DWORD *)word_8A7F24 = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC = -2130706432;
                *(_DWORD *)word_8A7F24 = -32768;
              }
              if ( v183 >= -32768 )
              {
                if ( v183 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F28 = v183;
                }
                else
                {
                  dword_8A7FFC |= 0x80800000;
                  *(_DWORD *)word_8A7F28 = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC |= 0x80800000;
                *(_DWORD *)word_8A7F28 = -32768;
              }
              if ( v41 >= -32768 )
                goto LABEL_541;
              goto LABEL_558;
            case 0x4DA412u:
              v26 = dword_8A7FB4
                  + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
              v63 = dword_8A7FB8
                  + ((word_8A7F24[0] * word_8A7FC6 + word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8) >> 12);
              v68 = dword_8A7FBC;
              v67 = (word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12;
              goto LABEL_101;
            case 0x4DC012u:
              v26 = dword_8A7FD4
                  + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
              v39 = dword_8A7FD8
                  + ((word_8A7F24[0] * word_8A7FC6 + word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8) >> 12);
              v41 = dword_8A7FDC
                  + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
              v42 = -32768;
              goto LABEL_56;
          }
          if ( v26 != 5096466 )
            goto LABEL_630;
          v179 = word_8A7F28[0];
          v180 = word_8A7F24[0];
          v141 = word_8A7F2C[0];
          v26 = dword_8A7FD4
              + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
          v181 = word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8;
          v182 = word_8A7F24[0] * word_8A7FC6;
          goto LABEL_537;
        }
        if ( v26 == 5104658 )
        {
          v26 = (word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12;
          v184 = (word_8A7F24[0] * word_8A7FC6 + word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8) >> 12;
          v41 = (word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12;
          dword_8A7F64 = v26;
          dword_8A7F68 = v184;
          dword_8A7F6C = v41;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              *(_DWORD *)word_8A7F24 = (word_8A7F2C[0] * word_8A7FC4
                                      + word_8A7F28[0] * word_8A7FC2
                                      + word_8A7F24[0] * word_8A7FC0) >> 12;
            }
            else
            {
              dword_8A7FFC = -2130706432;
              *(_DWORD *)word_8A7F24 = 0x7FFF;
            }
          }
          else
          {
            dword_8A7FFC = -2130706432;
            *(_DWORD *)word_8A7F24 = 0;
          }
          if ( v184 >= 0 )
          {
            if ( v184 <= 0x7FFF )
            {
              *(_DWORD *)word_8A7F28 = v184;
            }
            else
            {
              dword_8A7FFC |= 0x80800000;
              *(_DWORD *)word_8A7F28 = 0x7FFF;
            }
          }
          else
          {
            dword_8A7FFC |= 0x80800000;
            *(_DWORD *)word_8A7F28 = 0;
          }
          if ( v41 >= 0 )
            goto LABEL_541;
          goto LABEL_573;
        }
        if ( v26 != 5767213 )
          goto LABEL_630;
LABEL_694:
        unk_8A7F60 = word_8A7FF4 * (unk_8A7F44 + unk_8A7F48 + unk_8A7F4C);
        v26 = (int)unk_8A7F60 >> 12;
        if ( (int)unk_8A7F60 >> 12 >= 0 )
        {
          if ( (int)v26 <= 0xFFFF )
          {
            word_8A7F1C = (int)unk_8A7F60 >> 12;
          }
          else
          {
            dword_8A7FFC |= 0x80040000;
            word_8A7F1C = -1;
          }
        }
        else
        {
          dword_8A7FFC |= 0x80040000;
          word_8A7F1C = 0;
        }
        return v26;
      }
      if ( v26 > 0x118043F )
      {
        if ( v26 <= 0x178000C )
        {
          if ( v26 == 24641548 )
          {
            LOBYTE(v26) = sub_4145C0();
            return v26;
          }
          if ( v26 <= 0x158002D )
          {
            if ( v26 != 22544429 )
            {
              if ( v26 == 19399700 )
              {
                LOBYTE(v26) = sub_413C70();
                return v26;
              }
              if ( v26 == 20448284 )
              {
                LOBYTE(v26) = sub_414030();
                return v26;
              }
              if ( v26 != 20971526 )
                goto LABEL_630;
              goto LABEL_612;
            }
            goto LABEL_694;
          }
          if ( v26 != 23593006 )
          {
            if ( v26 == 24117260 )
            {
              LOBYTE(v26) = sub_4144A0();
              return v26;
            }
            goto LABEL_630;
          }
          goto LABEL_699;
        }
        if ( v26 > 0x198003D )
        {
          if ( v26 != 0x1A0003E )
          {
            if ( v26 == 0x1A8003E )
            {
              v22 = ((word_8A7F20 * word_8A7F28[0]) >> 12) + dword_8A7F68;
              v23 = ((word_8A7F20 * word_8A7F2C[0]) >> 12) + dword_8A7F6C;
              dword_8A7F64 += (word_8A7F20 * word_8A7F24[0]) >> 12;
              dword_8A7F68 = v22;
              dword_8A7F6C = v23;
              if ( dword_8A7F64 >= -32768 )
              {
                if ( dword_8A7F64 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F24 = dword_8A7F64;
                }
                else
                {
                  dword_8A7FFC |= 0x81000000;
                  *(_DWORD *)word_8A7F24 = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC |= 0x81000000;
                *(_DWORD *)word_8A7F24 = -32768;
              }
              if ( v22 >= -32768 )
              {
                if ( v22 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F28 = v22;
                }
                else
                {
                  dword_8A7FFC |= 0x80800000;
                  *(_DWORD *)word_8A7F28 = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC |= 0x80800000;
                *(_DWORD *)word_8A7F28 = -32768;
              }
              if ( v23 >= -32768 )
              {
                if ( v23 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F2C = v23;
                }
                else
                {
                  dword_8A7FFC |= 0x400000u;
                  *(_DWORD *)word_8A7F2C = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC |= 0x400000u;
                *(_DWORD *)word_8A7F2C = -32768;
              }
              unk_8A7F50 = unk_8A7F54;
              v26 = dword_8A7F64 >> 4;
              unk_8A7F54 = unk_8A7F58;
              v24 = v22 >> 4;
              v25 = v23 >> 4;
              unk_8A8004 = dword_8A7F64 >> 4;
              unk_8A8008 = v24;
              unk_8A800C = v25;
              if ( dword_8A7F64 >> 4 >= 0 )
              {
                if ( (int)v26 <= 255 )
                {
                  unk_8A7F58 = dword_8A7F64 >> 4;
                }
                else
                {
                  dword_8A7FFC |= 0x200000u;
                  unk_8A7F58 = -1;
                }
              }
              else
              {
                dword_8A7FFC |= 0x200000u;
                unk_8A7F58 = 0;
              }
              if ( v24 >= 0 )
              {
                if ( v24 <= 255 )
                {
                  unk_8A7F59 = v24;
                }
                else
                {
                  dword_8A7FFC |= 0x100000u;
                  unk_8A7F59 = -1;
                }
              }
              else
              {
                dword_8A7FFC |= 0x100000u;
                unk_8A7F59 = 0;
              }
              if ( v25 >= 0 )
              {
                if ( v25 <= 255 )
                {
                  unk_8A7F5A = v25;
                }
                else
                {
                  dword_8A7FFC |= 0x80000u;
                  LOBYTE(v26) = byte_8A7F1B;
                  unk_8A7F5A = -1;
                }
                unk_8A7F5B = byte_8A7F1B;
              }
              else
              {
                LOBYTE(v26) = dword_8A7FFC;
                dword_8A7FFC |= 0x80000u;
                unk_8A7F5A = 0;
                unk_8A7F5B = byte_8A7F1B;
              }
              return v26;
            }
            goto LABEL_630;
          }
        }
        else
        {
          switch ( v26 )
          {
            case 0x198003Du:
              goto LABEL_735;
            case 0x1780010u:
              goto LABEL_626;
            case 0x190003Du:
              goto LABEL_704;
          }
          if ( v26 != 26214462 )
            goto LABEL_630;
        }
        v18 = word_8A7F20 * word_8A7F28[0] + dword_8A7F68;
        v19 = word_8A7F20 * word_8A7F2C[0] + dword_8A7F6C;
        dword_8A7F64 += word_8A7F20 * word_8A7F24[0];
        dword_8A7F68 = v18;
        dword_8A7F6C = v19;
        if ( dword_8A7F64 >= -32768 )
        {
          if ( dword_8A7F64 <= 0x7FFF )
          {
            *(_DWORD *)word_8A7F24 = dword_8A7F64;
          }
          else
          {
            dword_8A7FFC |= 0x81000000;
            *(_DWORD *)word_8A7F24 = 0x7FFF;
          }
        }
        else
        {
          dword_8A7FFC |= 0x81000000;
          *(_DWORD *)word_8A7F24 = -32768;
        }
        if ( v18 >= -32768 )
        {
          if ( v18 <= 0x7FFF )
          {
            *(_DWORD *)word_8A7F28 = v18;
          }
          else
          {
            dword_8A7FFC |= 0x80800000;
            *(_DWORD *)word_8A7F28 = 0x7FFF;
          }
        }
        else
        {
          dword_8A7FFC |= 0x80800000;
          *(_DWORD *)word_8A7F28 = -32768;
        }
        if ( v19 >= -32768 )
        {
          if ( v19 <= 0x7FFF )
          {
            *(_DWORD *)word_8A7F2C = v19;
          }
          else
          {
            dword_8A7FFC |= 0x400000u;
            *(_DWORD *)word_8A7F2C = 0x7FFF;
          }
        }
        else
        {
          dword_8A7FFC |= 0x400000u;
          *(_DWORD *)word_8A7F2C = -32768;
        }
        unk_8A7F50 = unk_8A7F54;
        v26 = dword_8A7F64 >> 4;
        unk_8A7F54 = unk_8A7F58;
        v20 = v18 >> 4;
        v21 = v19 >> 4;
        unk_8A8004 = dword_8A7F64 >> 4;
        unk_8A8008 = v20;
        unk_8A800C = v21;
        if ( dword_8A7F64 >> 4 >= 0 )
        {
          if ( (int)v26 <= 255 )
          {
            unk_8A7F58 = dword_8A7F64 >> 4;
          }
          else
          {
            dword_8A7FFC |= 0x200000u;
            unk_8A7F58 = -1;
          }
        }
        else
        {
          dword_8A7FFC |= 0x200000u;
          unk_8A7F58 = 0;
        }
        if ( v20 >= 0 )
        {
          if ( v20 <= 255 )
          {
            unk_8A7F59 = v20;
          }
          else
          {
            dword_8A7FFC |= 0x100000u;
            unk_8A7F59 = -1;
          }
        }
        else
        {
          dword_8A7FFC |= 0x100000u;
          unk_8A7F59 = 0;
        }
        if ( v21 >= 0 )
        {
          if ( v21 <= 255 )
          {
            unk_8A7F5A = v21;
          }
          else
          {
            dword_8A7FFC |= 0x80000u;
            LOBYTE(v26) = byte_8A7F1B;
            unk_8A7F5A = -1;
          }
          unk_8A7F5B = byte_8A7F1B;
        }
        else
        {
          LOBYTE(v26) = dword_8A7FFC;
          dword_8A7FFC |= 0x80000u;
          unk_8A7F5A = 0;
          unk_8A7F5B = byte_8A7F1B;
        }
        return v26;
      }
      if ( v26 == 18351167 )
      {
        LOBYTE(v26) = sub_4131C0();
        return v26;
      }
      if ( v26 <= 0xA80428 )
      {
        if ( v26 == 11011112 )
        {
          v26 = (word_8A7F24[0] * word_8A7F24[0]) >> 12;
          v6 = (word_8A7F28[0] * word_8A7F28[0]) >> 12;
          v7 = (word_8A7F2C[0] * word_8A7F2C[0]) >> 12;
          dword_8A7F64 = v26;
          dword_8A7F68 = v6;
          dword_8A7F6C = v7;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              *(_DWORD *)word_8A7F24 = (word_8A7F24[0] * word_8A7F24[0]) >> 12;
            }
            else
            {
              dword_8A7FFC |= 0x81000000;
              *(_DWORD *)word_8A7F24 = 0x7FFF;
            }
          }
          else
          {
            dword_8A7FFC |= 0x81000000;
            *(_DWORD *)word_8A7F24 = 0;
          }
          if ( v6 >= 0 )
          {
            if ( v6 <= 0x7FFF )
            {
              *(_DWORD *)word_8A7F28 = (word_8A7F28[0] * word_8A7F28[0]) >> 12;
            }
            else
            {
              dword_8A7FFC |= 0x80800000;
              *(_DWORD *)word_8A7F28 = 0x7FFF;
            }
          }
          else
          {
            dword_8A7FFC |= 0x80800000;
            *(_DWORD *)word_8A7F28 = 0;
          }
          if ( v7 >= 0 )
          {
            if ( v7 <= 0x7FFF )
            {
              *(_DWORD *)word_8A7F2C = (word_8A7F2C[0] * word_8A7F2C[0]) >> 12;
            }
            else
            {
              dword_8A7FFC |= 0x400000u;
              *(_DWORD *)word_8A7F2C = 0x7FFF;
            }
          }
          else
          {
            dword_8A7FFC |= 0x400000u;
            *(_DWORD *)word_8A7F2C = 0;
          }
          return v26;
        }
        if ( v26 <= 0x980011 )
        {
          if ( v26 == 9961489 )
          {
            dword_8A7F64 = word_8A7F24[0]
                         + ((word_8A7F20 * gte_clamp(-2130706432, dword_8A7FD4 - word_8A7F24[0])) >> 12);
            dword_8A7F68 = word_8A7F28[0]
                         + ((word_8A7F20 * gte_clamp(-2139095040, dword_8A7FD8 - word_8A7F28[0])) >> 12);
            v0 = gte_clamp(0x400000, dword_8A7FDC - word_8A7F2C[0]);
            v2 = word_8A7F2C[0] + ((word_8A7F20 * v0) >> 12);
            dword_8A7F6C = v2;
            if ( dword_8A7F64 >= -32768 )
            {
              if ( dword_8A7F64 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F24 = dword_8A7F64;
              }
              else
              {
                dword_8A7FFC |= v1;
                *(_DWORD *)word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= v1;
              *(_DWORD *)word_8A7F24 = -32768;
            }
            if ( dword_8A7F68 >= -32768 )
            {
              if ( dword_8A7F68 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F28 = dword_8A7F68;
              }
              else
              {
                dword_8A7FFC |= 0x80800000;
                *(_DWORD *)word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= 0x80800000;
              *(_DWORD *)word_8A7F28 = -32768;
            }
            if ( v2 >= -32768 )
            {
              if ( v2 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F2C = v2;
              }
              else
              {
                dword_8A7FFC |= 0x400000u;
                *(_DWORD *)word_8A7F2C = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= 0x400000u;
              *(_DWORD *)word_8A7F2C = -32768;
            }
            unk_8A7F50 = unk_8A7F54;
            v3 = dword_8A7F68 >> 4;
            v26 = v2 >> 4;
            unk_8A7F54 = unk_8A7F58;
            unk_8A8004 = dword_8A7F64 >> 4;
            unk_8A8008 = dword_8A7F68 >> 4;
            unk_8A800C = v26;
            if ( dword_8A7F64 >> 4 >= 0 )
            {
              if ( dword_8A7F64 >> 4 <= 255 )
              {
                unk_8A7F58 = dword_8A7F64 >> 4;
              }
              else
              {
                dword_8A7FFC |= 0x200000u;
                unk_8A7F58 = -1;
              }
            }
            else
            {
              dword_8A7FFC |= 0x200000u;
              unk_8A7F58 = 0;
            }
            if ( v3 >= 0 )
            {
              if ( v3 <= 255 )
              {
                unk_8A7F59 = dword_8A7F68 >> 4;
              }
              else
              {
                dword_8A7FFC |= 0x100000u;
                unk_8A7F59 = -1;
              }
            }
            else
            {
              dword_8A7FFC |= 0x100000u;
              unk_8A7F59 = 0;
            }
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 255 )
              {
                unk_8A7F5A = v26;
              }
              else
              {
                dword_8A7FFC |= 0x80000u;
                LOBYTE(v26) = byte_8A7F1B;
                unk_8A7F5A = -1;
              }
              unk_8A7F5B = byte_8A7F1B;
            }
            else
            {
              LOBYTE(v26) = dword_8A7FFC;
              dword_8A7FFC |= 0x80000u;
              unk_8A7F5A = 0;
              unk_8A7F5B = byte_8A7F1B;
            }
            return v26;
          }
          if ( (int *)v26 != (int *)((char *)&ram[205947] + 2) )
          {
            if ( (int *)v26 != &ram[468084] )
            {
              if ( v26 != 9437245 )
                goto LABEL_630;
LABEL_704:
              v8 = word_8A7F20 * word_8A7F24[0];
              v9 = word_8A7F20 * word_8A7F28[0];
              v10 = word_8A7F20 * word_8A7F2C[0];
              dword_8A7F64 = v8;
              dword_8A7F68 = v9;
              dword_8A7F6C = v10;
              if ( v8 >= -32768 )
              {
                if ( v8 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F24 = word_8A7F20 * word_8A7F24[0];
                }
                else
                {
                  dword_8A7FFC |= 0x81000000;
                  *(_DWORD *)word_8A7F24 = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC |= 0x81000000;
                *(_DWORD *)word_8A7F24 = -32768;
              }
              if ( v9 >= -32768 )
              {
                if ( v9 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F28 = word_8A7F20 * word_8A7F28[0];
                }
                else
                {
                  dword_8A7FFC |= 0x80800000;
                  *(_DWORD *)word_8A7F28 = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC |= 0x80800000;
                *(_DWORD *)word_8A7F28 = -32768;
              }
              if ( v10 >= -32768 )
              {
                if ( v10 <= 0x7FFF )
                {
                  *(_DWORD *)word_8A7F2C = word_8A7F20 * word_8A7F2C[0];
                }
                else
                {
                  dword_8A7FFC |= 0x400000u;
                  *(_DWORD *)word_8A7F2C = 0x7FFF;
                }
              }
              else
              {
                dword_8A7FFC |= 0x400000u;
                *(_DWORD *)word_8A7F2C = -32768;
              }
              unk_8A7F50 = unk_8A7F54;
              v26 = v8 >> 4;
              unk_8A7F54 = unk_8A7F58;
              v11 = v9 >> 4;
              v12 = v10 >> 4;
              unk_8A8004 = v26;
              unk_8A8008 = v11;
              unk_8A800C = v12;
              if ( (v26 & 0x80000000) == 0 )
              {
                if ( (int)v26 <= 255 )
                {
                  unk_8A7F58 = v26;
                }
                else
                {
                  dword_8A7FFC |= 0x200000u;
                  unk_8A7F58 = -1;
                }
              }
              else
              {
                dword_8A7FFC |= 0x200000u;
                unk_8A7F58 = 0;
              }
              if ( v11 >= 0 )
              {
                if ( v11 <= 255 )
                {
                  unk_8A7F59 = v11;
                }
                else
                {
                  dword_8A7FFC |= 0x100000u;
                  unk_8A7F59 = -1;
                }
              }
              else
              {
                dword_8A7FFC |= 0x100000u;
                unk_8A7F59 = 0;
              }
              if ( v12 >= 0 )
              {
                if ( v12 <= 255 )
                {
                  unk_8A7F5A = v12;
                }
                else
                {
                  LOBYTE(v26) = dword_8A7FFC;
                  dword_8A7FFC |= 0x80000u;
                  unk_8A7F5A = -1;
                }
                unk_8A7F5B = byte_8A7F1B;
              }
              else
              {
                dword_8A7FFC |= 0x80000u;
                unk_8A7F5A = 0;
                unk_8A7F5B = byte_8A7F1B;
                LOBYTE(v26) = byte_8A7F1B;
              }
              return v26;
            }
LABEL_626:
            LOBYTE(v26) = sub_410690();
            return v26;
          }
LABEL_699:
          unk_8A7F60 = word_8A7FF8 * (unk_8A7F40 + unk_8A7F44 + unk_8A7F48 + unk_8A7F4C);
          v26 = (int)unk_8A7F60 >> 12;
          if ( (int)unk_8A7F60 >> 12 >= 0 )
          {
            if ( (int)v26 <= 0xFFFF )
            {
              word_8A7F1C = (int)unk_8A7F60 >> 12;
            }
            else
            {
              dword_8A7FFC |= 0x80040000;
              word_8A7F1C = -1;
            }
          }
          else
          {
            dword_8A7FFC |= 0x80040000;
            word_8A7F1C = 0;
          }
          return v26;
        }
        if ( v26 != 9961533 )
        {
          if ( v26 == 10486824 )
          {
            v26 = word_8A7F24[0] * word_8A7F24[0];
            v4 = word_8A7F28[0] * word_8A7F28[0];
            v5 = word_8A7F2C[0] * word_8A7F2C[0];
            dword_8A7F64 = v26;
            dword_8A7F68 = v4;
            dword_8A7F6C = v5;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F24 = word_8A7F24[0] * word_8A7F24[0];
              }
              else
              {
                dword_8A7FFC |= 0x81000000;
                *(_DWORD *)word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= 0x81000000;
              *(_DWORD *)word_8A7F24 = 0;
            }
            if ( v4 >= 0 )
            {
              if ( v4 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F28 = word_8A7F28[0] * word_8A7F28[0];
              }
              else
              {
                dword_8A7FFC |= 0x80800000;
                *(_DWORD *)word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= 0x80800000;
              *(_DWORD *)word_8A7F28 = 0;
            }
            if ( v5 >= 0 )
            {
              if ( v5 <= 0x7FFF )
              {
                *(_DWORD *)word_8A7F2C = word_8A7F2C[0] * word_8A7F2C[0];
              }
              else
              {
                dword_8A7FFC |= 0x400000u;
                *(_DWORD *)word_8A7F2C = 0x7FFF;
              }
            }
            else
            {
              dword_8A7FFC |= 0x400000u;
              *(_DWORD *)word_8A7F2C = 0;
            }
            return v26;
          }
          goto LABEL_630;
        }
LABEL_735:
        v13 = (word_8A7F20 * word_8A7F24[0]) >> 12;
        v14 = (word_8A7F20 * word_8A7F28[0]) >> 12;
        v15 = (word_8A7F20 * word_8A7F2C[0]) >> 12;
        dword_8A7F64 = v13;
        dword_8A7F68 = v14;
        dword_8A7F6C = v15;
        if ( v13 >= -32768 )
        {
          if ( v13 <= 0x7FFF )
          {
            *(_DWORD *)word_8A7F24 = (word_8A7F20 * word_8A7F24[0]) >> 12;
          }
          else
          {
            dword_8A7FFC |= 0x81000000;
            *(_DWORD *)word_8A7F24 = 0x7FFF;
          }
        }
        else
        {
          dword_8A7FFC |= 0x81000000;
          *(_DWORD *)word_8A7F24 = -32768;
        }
        if ( v14 >= -32768 )
        {
          if ( v14 <= 0x7FFF )
          {
            *(_DWORD *)word_8A7F28 = (word_8A7F20 * word_8A7F28[0]) >> 12;
          }
          else
          {
            dword_8A7FFC |= 0x80800000;
            *(_DWORD *)word_8A7F28 = 0x7FFF;
          }
        }
        else
        {
          dword_8A7FFC |= 0x80800000;
          *(_DWORD *)word_8A7F28 = -32768;
        }
        if ( v15 >= -32768 )
        {
          if ( v15 <= 0x7FFF )
          {
            *(_DWORD *)word_8A7F2C = (word_8A7F20 * word_8A7F2C[0]) >> 12;
          }
          else
          {
            dword_8A7FFC |= 0x400000u;
            *(_DWORD *)word_8A7F2C = 0x7FFF;
          }
        }
        else
        {
          dword_8A7FFC |= 0x400000u;
          *(_DWORD *)word_8A7F2C = -32768;
        }
        unk_8A7F50 = unk_8A7F54;
        v26 = v13 >> 4;
        unk_8A7F54 = unk_8A7F58;
        v16 = v14 >> 4;
        v17 = v15 >> 4;
        unk_8A8004 = v26;
        unk_8A8008 = v16;
        unk_8A800C = v17;
        if ( (v26 & 0x80000000) == 0 )
        {
          if ( (int)v26 <= 255 )
          {
            unk_8A7F58 = v26;
          }
          else
          {
            dword_8A7FFC |= 0x200000u;
            unk_8A7F58 = -1;
          }
        }
        else
        {
          dword_8A7FFC |= 0x200000u;
          unk_8A7F58 = 0;
        }
        if ( v16 >= 0 )
        {
          if ( v16 <= 255 )
          {
            unk_8A7F59 = v16;
          }
          else
          {
            dword_8A7FFC |= 0x100000u;
            unk_8A7F59 = -1;
          }
        }
        else
        {
          dword_8A7FFC |= 0x100000u;
          unk_8A7F59 = 0;
        }
        if ( v17 >= 0 )
        {
          if ( v17 <= 255 )
          {
            unk_8A7F5A = v17;
          }
          else
          {
            LOBYTE(v26) = dword_8A7FFC;
            dword_8A7FFC |= 0x80000u;
            unk_8A7F5A = -1;
          }
          unk_8A7F5B = byte_8A7F1B;
        }
        else
        {
          dword_8A7FFC |= 0x80000u;
          unk_8A7F5A = 0;
          unk_8A7F5B = byte_8A7F1B;
          LOBYTE(v26) = byte_8A7F1B;
        }
        return v26;
      }
      if ( v26 <= 0xF8002A )
      {
        switch ( v26 )
        {
          case 0xF8002Au:
            LOBYTE(v26) = sub_412B10();
            return v26;
          case 0xC8041Eu:
            LOBYTE(v26) = sub_410D20();
            return v26;
          case 0xD80420u:
            LOBYTE(v26) = sub_4110A0();
            return v26;
          case 0xE80413u:
            LOBYTE(v26) = sub_411980();
            return v26;
        }
        goto LABEL_630;
      }
      if ( v26 == 0xF80416 )
      {
        LOBYTE(v26) = sub_411E50();
        return v26;
      }
      if ( v26 == 0x108041B )
        goto LABEL_602;
LABEL_630:
      if ( byte_4F8318 )
        LOBYTE(v26) = dbg_print("CODE [%07x]\n", v26);
      return v26;
  }
}
