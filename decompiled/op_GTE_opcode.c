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
  unsigned int v27; // ecx
  unsigned __int8 v28; // bl
  unsigned __int8 v29; // cl
  unsigned __int8 v30; // al
  int v31; // edx
  int v32; // ecx
  int v33; // edx
  int v34; // esi
  int v35; // edx
  int v36; // edi
  int v37; // ebp
  int v38; // ebx
  int v39; // ecx
  int v40; // ecx
  int v41; // ebp
  int v42; // edx
  int v43; // esi
  int v44; // esi
  int v45; // edx
  int v46; // edi
  int v47; // ebp
  int v48; // ebx
  int v49; // ecx
  int v50; // ebp
  int v51; // ebx
  int v52; // edi
  int v53; // edx
  int v54; // esi
  int v55; // edi
  int v56; // ebp
  int v57; // ecx
  int v58; // edx
  int v59; // esi
  int v60; // edi
  int v61; // ebx
  int v62; // ecx
  int v63; // edx
  int v64; // ecx
  int v65; // edx
  int v66; // ebp
  int v67; // edi
  int v68; // edx
  int v69; // edi
  int v70; // edi
  int v71; // ebx
  int v72; // esi
  int v73; // edx
  int v74; // edi
  int v75; // esi
  int v76; // ebp
  int v77; // edx
  int v78; // edi
  int v79; // ebp
  int v80; // ebx
  int v81; // ecx
  int v82; // edx
  int v83; // edi
  int v84; // esi
  int v85; // ebp
  int v86; // ebx
  int v87; // ecx
  int v88; // ebp
  int v89; // ebx
  int v90; // ecx
  int v91; // edi
  int v92; // ebp
  int v93; // ecx
  int v94; // edx
  int v95; // edi
  int v96; // ebx
  int v97; // esi
  int v98; // ecx
  int v99; // edx
  int v100; // edi
  int v101; // ebx
  int v102; // esi
  int v103; // eax
  int v104; // ecx
  int v105; // edx
  int v106; // edx
  int v107; // ebx
  int v108; // edi
  int v109; // ebp
  int v110; // esi
  int v111; // edi
  int v112; // ebp
  int v113; // ecx
  int v114; // edx
  int v115; // edx
  int v116; // ebp
  int v117; // edi
  int v118; // edx
  int v119; // esi
  int v120; // edi
  int v121; // ebp
  int v122; // ecx
  int v123; // edx
  int v124; // edx
  int v125; // ebp
  int v126; // edi
  int v127; // edx
  int v128; // esi
  int v129; // edi
  int v130; // ebp
  int v131; // ecx
  int v132; // edx
  int v133; // esi
  int v134; // edi
  int v135; // ebx
  int v136; // ecx
  int v137; // edx
  int v138; // ecx
  int v139; // edx
  int v140; // ebx
  int v141; // edi
  int v142; // esi
  int v143; // edi
  int v144; // ebp
  int v145; // ecx
  int v146; // edx
  int v147; // edx
  int v148; // ebp
  int v149; // edi
  int v150; // edx
  int v151; // edi
  int v152; // ebx
  int v153; // ecx
  int v154; // edx
  int v155; // edi
  int v156; // ebp
  int v157; // ecx
  int v158; // edx
  int v159; // edi
  int v160; // ebp
  int v161; // ecx
  int v162; // edx
  int v163; // edi
  int v164; // ebx
  int v165; // ecx
  int v166; // edx
  int v167; // edi
  int v168; // ebx
  int v169; // ecx
  int v170; // edx
  int v171; // edi
  int v172; // ebp
  int v173; // esi
  int v174; // ecx
  int v175; // edx
  int v176; // edi
  int v177; // ebx
  int v178; // ecx
  int v179; // edx
  int v180; // edi
  int v181; // ebp
  int v182; // ecx
  int v183; // edx
  int v184; // ecx
  int v185; // ecx

  LOBYTE(v26) = cpu_opcode;
  v27 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  switch ( v27 )
  {
    case 0u:
      v28 = BYTE2(cpu_opcode) & 0x1F;
      v29 = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      unk_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      unk_8A8001 = v29;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        if ( v29 == 31 )
        {
          v26 = (unsigned __int8)sub_414EE0(unk_8A7F78);
          cpu_gpr[v28] = v26;
        }
        else
        {
          if ( v29 == 29 )
          {
            sub_410400((unsigned __int16)word_8A7F2C);
            sub_410400((unsigned __int16)word_8A7F28);
            v30 = sub_410400((unsigned __int16)word_8A7F24);
            v28 = unk_8A7EE0;
            unk_8A7F74 = v30 | v31;
          }
          LOBYTE(v26) = v28;
          cpu_gpr[v28] = unk_8A7F00[v29];
        }
      }
      return v26;
    case 2u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      unk_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      unk_8A8000 = v26;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        v26 = BYTE2(cpu_opcode) & 0x1F;
        cpu_gpr[v26] = unk_8A7F80[(unsigned __int16)cpu_opcode >> 11];
      }
      return v26;
    case 4u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      unk_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      unk_8A8001 = v26;
      v32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      unk_8A7F00[(unsigned __int8)v26] = v32;
      if ( (unsigned __int8)v26 >= 0x10u && (unsigned __int8)v26 <= 0x13u )
        unk_8A7F00[(unsigned __int8)v26] = (unsigned __int16)v32;
      switch ( (_BYTE)v26 )
      {
        case 0xE:
          unk_8A7F3C = v32;
          break;
        case 0xF:
          LOBYTE(v26) = unk_8A7F34;
          unk_8A7F30 = unk_8A7F34;
          unk_8A7F34 = unk_8A7F38;
          unk_8A7F38 = v32;
          break;
        case 0x1C:
          v26 = ((unsigned __int16)unk_8A7F70 >> 3) & 0xF80;
          word_8A7F24 = (unk_8A7F70 & 0x1F) << 7;
          word_8A7F28 = 4 * (unk_8A7F70 & 0x3E0);
          word_8A7F2C = v26;
          break;
      }
      return v26;
    case 6u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      unk_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      v33 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      unk_8A8000 = v26;
      unk_8A7F80[(unsigned __int8)v26] = v33;
      return v26;
    default:
      v26 = cpu_opcode & 0x1FFFFFF;
      unk_8A7FFC = 0;
      if ( (cpu_opcode & 0x1FFFFFFu) <= 0x48A412 )
      {
        if ( v26 == 4760594 )
        {
          v120 = unk_8A7F0A;
          v121 = unk_8A7F08;
          v119 = unk_8A7F0C;
          v26 = unk_8A7FB4
              + ((unk_8A7F0C * unk_8A7F84 + unk_8A7F0A * SHIWORD(unk_8A7F80[0]) + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12);
          v122 = unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86;
          v123 = unk_8A7F0C * unk_8A7F8A;
          goto LABEL_314;
        }
        if ( v26 <= 0x432012 )
        {
          if ( v26 == 4399122 )
          {
            v26 = unk_8A7F10 * unk_8A7FA0 + unk_8A7FB4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F14 * unk_8A7FA4;
            v40 = unk_8A7F10 * unk_8A7FA6 + unk_8A7FB8 + unk_8A7F12 * unk_8A7FA8 + unk_8A7F14 * unk_8A7FAA;
            v42 = unk_8A7F10 * unk_8A7FAC + unk_8A7FBC + unk_8A7F12 * unk_8A7FAE + unk_8A7F14 * unk_8A7FB0;
            v43 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= 0x416012 )
          {
            if ( v26 == 4284434 )
            {
              v60 = unk_8A7F12;
              v61 = unk_8A7F10;
              v59 = unk_8A7F14;
              v26 = unk_8A7F14 * unk_8A7F84 + unk_8A7F12 * SHIWORD(unk_8A7F80[0]) + unk_8A7F10 * SLOWORD(unk_8A7F80[0]);
              v62 = unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86;
              v63 = unk_8A7F14 * unk_8A7F8A;
              goto LABEL_80;
            }
            if ( v26 <= 0x408012 )
            {
              if ( v26 == 4227090 )
              {
                v35 = unk_8A7F0A;
                v36 = unk_8A7F08;
                v34 = unk_8A7F0C;
                v26 = unk_8A7F08 * SLOWORD(unk_8A7F80[0])
                    + unk_8A7F94
                    + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                    + unk_8A7F0C * unk_8A7F84;
                v37 = unk_8A7F98 + unk_8A7F0A * unk_8A7F88;
                v38 = unk_8A7F08 * unk_8A7F86;
                v39 = unk_8A7F0C * unk_8A7F8A;
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
                    v26 = (__int16)unk_8A7F38 * (SHIWORD(unk_8A7F30) - SHIWORD(unk_8A7F34));
                    unk_8A7F60 = v26
                               + (__int16)unk_8A7F34 * (SHIWORD(unk_8A7F38) - SHIWORD(unk_8A7F30))
                               + (__int16)unk_8A7F30 * (SHIWORD(unk_8A7F34) - SHIWORD(unk_8A7F38));
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
                  v34 = unk_8A7F04;
                  v35 = SHIWORD(unk_8A7F00[0]);
                  v36 = SLOWORD(unk_8A7F00[0]);
                  goto LABEL_42;
                }
                v44 = unk_8A7F04;
                v45 = SHIWORD(unk_8A7F00[0]);
                v46 = SLOWORD(unk_8A7F00[0]);
LABEL_52:
                v26 = v46 * SLOWORD(unk_8A7F80[0]) + unk_8A7F94 + v45 * SHIWORD(unk_8A7F80[0]) + v44 * unk_8A7F84;
                v47 = unk_8A7F98 + v46 * unk_8A7F86;
                v48 = v44 * unk_8A7F8A;
                v49 = v45 * unk_8A7F88;
LABEL_53:
                v40 = v48 + v47 + v49;
                v50 = unk_8A7F9C;
LABEL_54:
                v51 = v46 * unk_8A7F8C;
                v52 = v45 * unk_8A7F8E;
                v53 = unk_8A7F90;
LABEL_55:
                v42 = v51 + v50 + v52 + v44 * v53;
                v43 = 0;
                goto LABEL_56;
              }
              if ( v26 <= 0x404412 )
              {
                if ( v26 != 0x404412 )
                {
                  if ( v26 == 0x402012 )
                  {
                    v35 = SHIWORD(unk_8A7F00[0]);
                    v36 = SLOWORD(unk_8A7F00[0]);
                    v34 = unk_8A7F04;
                    v26 = SLOWORD(unk_8A7F00[0]) * SLOWORD(unk_8A7F80[0])
                        + unk_8A7FB4
                        + SHIWORD(unk_8A7F00[0]) * SHIWORD(unk_8A7F80[0])
                        + unk_8A7F04 * unk_8A7F84;
                    v40 = unk_8A7F04 * unk_8A7F8A
                        + unk_8A7FB8
                        + SLOWORD(unk_8A7F00[0]) * unk_8A7F86
                        + SHIWORD(unk_8A7F00[0]) * unk_8A7F88;
                    v41 = unk_8A7FBC;
                    goto LABEL_44;
                  }
                  if ( v26 != 4203538 )
                  {
                    if ( v26 != 4210706 )
                      goto LABEL_630;
                    v35 = SHIWORD(unk_8A7F00[0]);
                    v36 = SLOWORD(unk_8A7F00[0]);
                    v34 = unk_8A7F04;
                    v26 = SLOWORD(unk_8A7F00[0]) * SLOWORD(unk_8A7F80[0])
                        + unk_8A7FD4
                        + SHIWORD(unk_8A7F00[0]) * SHIWORD(unk_8A7F80[0])
                        + unk_8A7F04 * unk_8A7F84;
                    v40 = unk_8A7F04 * unk_8A7F8A
                        + unk_8A7FD8
                        + SLOWORD(unk_8A7F00[0]) * unk_8A7F86
                        + SHIWORD(unk_8A7F00[0]) * unk_8A7F88;
                    v41 = unk_8A7FDC;
                    goto LABEL_44;
                  }
                  v45 = SHIWORD(unk_8A7F00[0]);
                  v46 = SLOWORD(unk_8A7F00[0]);
                  v44 = unk_8A7F04;
                  v26 = SLOWORD(unk_8A7F00[0]) * SLOWORD(unk_8A7F80[0])
                      + unk_8A7FB4
                      + SHIWORD(unk_8A7F00[0]) * SHIWORD(unk_8A7F80[0])
                      + unk_8A7F04 * unk_8A7F84;
                  v40 = unk_8A7F04 * unk_8A7F8A
                      + unk_8A7FB8
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7F86
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7F88;
                  v50 = unk_8A7FBC;
                  goto LABEL_54;
                }
                v44 = unk_8A7F04;
                v45 = SHIWORD(unk_8A7F00[0]);
                v46 = SLOWORD(unk_8A7F00[0]);
                goto LABEL_138;
              }
              if ( v26 != 4218898 )
              {
                if ( v26 != 4219922 )
                  goto LABEL_630;
                v54 = unk_8A7F04;
                v55 = SHIWORD(unk_8A7F00[0]);
                v56 = SLOWORD(unk_8A7F00[0]);
                goto LABEL_72;
              }
              v59 = unk_8A7F04;
              v60 = SHIWORD(unk_8A7F00[0]);
              v61 = SLOWORD(unk_8A7F00[0]);
              goto LABEL_79;
            }
            if ( v26 > (unsigned int)&loc_40E412 )
            {
              if ( v26 > (unsigned int)&loc_412411 + 1 )
              {
                if ( (_UNKNOWN *)v26 == &loc_414012 )
                {
                  v35 = unk_8A7F12;
                  v36 = unk_8A7F10;
                  v34 = unk_8A7F14;
                  v26 = unk_8A7F10 * SLOWORD(unk_8A7F80[0])
                      + unk_8A7FD4
                      + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                      + unk_8A7F14 * unk_8A7F84;
                  v40 = unk_8A7F10 * unk_8A7F86 + unk_8A7FD8 + unk_8A7F12 * unk_8A7F88 + unk_8A7F14 * unk_8A7F8A;
                  v41 = unk_8A7FDC;
                  goto LABEL_44;
                }
                if ( (char *)v26 != byte_414412 )
                  goto LABEL_630;
                v45 = unk_8A7F12;
                v46 = unk_8A7F10;
                v44 = unk_8A7F14;
                v26 = unk_8A7F10 * SLOWORD(unk_8A7F80[0])
                    + unk_8A7FD4
                    + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                    + unk_8A7F14 * unk_8A7F84;
                v40 = unk_8A7F10 * unk_8A7F86 + unk_8A7FD8 + unk_8A7F12 * unk_8A7F88 + unk_8A7F14 * unk_8A7F8A;
                v50 = unk_8A7FDC;
                goto LABEL_54;
              }
              if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_412411 + 1) )
              {
                v45 = unk_8A7F12;
                v46 = unk_8A7F10;
                v44 = unk_8A7F14;
                v26 = unk_8A7F10 * SLOWORD(unk_8A7F80[0])
                    + unk_8A7FB4
                    + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                    + unk_8A7F14 * unk_8A7F84;
                v40 = unk_8A7F10 * unk_8A7F86 + unk_8A7FB8 + unk_8A7F12 * unk_8A7F88 + unk_8A7F14 * unk_8A7F8A;
                v50 = unk_8A7FBC;
                goto LABEL_54;
              }
              if ( v26 == 4259858 )
              {
                v35 = unk_8A7F12;
                v36 = unk_8A7F10;
                v34 = unk_8A7F14;
                v26 = unk_8A7F10 * SLOWORD(unk_8A7F80[0])
                    + unk_8A7F94
                    + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                    + unk_8A7F14 * unk_8A7F84;
                v37 = unk_8A7F98 + unk_8A7F12 * unk_8A7F88;
                v38 = unk_8A7F10 * unk_8A7F86;
                v39 = unk_8A7F14 * unk_8A7F8A;
                goto LABEL_43;
              }
              if ( (_UNKNOWN *)v26 != &loc_410412 )
              {
                if ( (_UNKNOWN *)v26 != (_UNKNOWN *)((char *)&loc_41200E + 4) )
                  goto LABEL_630;
                v35 = unk_8A7F12;
                v36 = unk_8A7F10;
                v34 = unk_8A7F14;
                v26 = unk_8A7F10 * SLOWORD(unk_8A7F80[0])
                    + unk_8A7FB4
                    + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                    + unk_8A7F14 * unk_8A7F84;
                v40 = unk_8A7F10 * unk_8A7F86 + unk_8A7FB8 + unk_8A7F12 * unk_8A7F88 + unk_8A7F14 * unk_8A7F8A;
                v41 = unk_8A7FBC;
                goto LABEL_44;
              }
              v45 = unk_8A7F12;
              v46 = unk_8A7F10;
              v44 = unk_8A7F14;
              v26 = unk_8A7F10 * SLOWORD(unk_8A7F80[0])
                  + unk_8A7F94
                  + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                  + unk_8A7F14 * unk_8A7F84;
              v47 = unk_8A7F98 + unk_8A7F12 * unk_8A7F88;
              v48 = unk_8A7F10 * unk_8A7F86;
              v49 = unk_8A7F14 * unk_8A7F8A;
              goto LABEL_53;
            }
            if ( (_UNKNOWN *)v26 != &loc_40E412 )
            {
              if ( v26 <= 0x40C012 )
              {
                if ( v26 == 4243474 )
                {
                  v35 = unk_8A7F0A;
                  v36 = unk_8A7F08;
                  v34 = unk_8A7F0C;
                  v26 = unk_8A7F08 * SLOWORD(unk_8A7F80[0])
                      + unk_8A7FD4
                      + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                      + unk_8A7F0C * unk_8A7F84;
                  v40 = unk_8A7F08 * unk_8A7F86 + unk_8A7FD8 + unk_8A7F0A * unk_8A7F88 + unk_8A7F0C * unk_8A7F8A;
                  v41 = unk_8A7FDC;
                  goto LABEL_44;
                }
                if ( (_UNKNOWN *)v26 != &loc_408412 )
                {
                  if ( (_UNKNOWN *)v26 == &loc_40A012 )
                  {
                    v35 = unk_8A7F0A;
                    v36 = unk_8A7F08;
                    v34 = unk_8A7F0C;
                    v26 = unk_8A7F08 * SLOWORD(unk_8A7F80[0])
                        + unk_8A7FB4
                        + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                        + unk_8A7F0C * unk_8A7F84;
                    v40 = unk_8A7F08 * unk_8A7F86 + unk_8A7FB8 + unk_8A7F0A * unk_8A7F88 + unk_8A7F0C * unk_8A7F8A;
                    v41 = unk_8A7FBC;
                    goto LABEL_44;
                  }
                  if ( v26 != 4236306 )
                    goto LABEL_630;
                  v45 = unk_8A7F0A;
                  v46 = unk_8A7F08;
                  v44 = unk_8A7F0C;
                  v26 = unk_8A7F08 * SLOWORD(unk_8A7F80[0])
                      + unk_8A7FB4
                      + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                      + unk_8A7F0C * unk_8A7F84;
                  v40 = unk_8A7F08 * unk_8A7F86 + unk_8A7FB8 + unk_8A7F0A * unk_8A7F88 + unk_8A7F0C * unk_8A7F8A;
                  v50 = unk_8A7FBC;
                  goto LABEL_54;
                }
                v45 = unk_8A7F0A;
                v46 = unk_8A7F08;
                v44 = unk_8A7F0C;
                v26 = unk_8A7F08 * SLOWORD(unk_8A7F80[0])
                    + unk_8A7F94
                    + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                    + unk_8A7F0C * unk_8A7F84;
                v47 = unk_8A7F98 + unk_8A7F0A * unk_8A7F88;
                v48 = unk_8A7F08 * unk_8A7F86;
                v49 = unk_8A7F0C * unk_8A7F8A;
                goto LABEL_53;
              }
              if ( v26 == 4244498 )
              {
                v45 = unk_8A7F0A;
                v46 = unk_8A7F08;
                v44 = unk_8A7F0C;
                v26 = unk_8A7F08 * SLOWORD(unk_8A7F80[0])
                    + unk_8A7FD4
                    + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                    + unk_8A7F0C * unk_8A7F84;
                v40 = unk_8A7F08 * unk_8A7F86 + unk_8A7FD8 + unk_8A7F0A * unk_8A7F88 + unk_8A7F0C * unk_8A7F8A;
                v50 = unk_8A7FDC;
                goto LABEL_54;
              }
              if ( v26 != 4251666 )
                goto LABEL_630;
              v60 = unk_8A7F0A;
              v61 = unk_8A7F08;
              v59 = unk_8A7F0C;
              v26 = unk_8A7F0C * unk_8A7F84 + unk_8A7F0A * SHIWORD(unk_8A7F80[0]) + unk_8A7F08 * SLOWORD(unk_8A7F80[0]);
              v62 = unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86;
              v63 = unk_8A7F0C * unk_8A7F8A;
              goto LABEL_80;
            }
            v54 = unk_8A7F0C;
            v55 = unk_8A7F0A;
            v56 = unk_8A7F08;
LABEL_98:
            v26 = v54 * unk_8A7F84 + v55 * SHIWORD(unk_8A7F80[0]) + v56 * SLOWORD(unk_8A7F80[0]);
            v57 = v55 * unk_8A7F88 + v56 * unk_8A7F86;
            v58 = v54 * unk_8A7F8A;
            goto LABEL_99;
          }
          if ( v26 <= 0x424012 )
          {
            if ( v26 == 4341778 )
            {
              v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA0
                  + unk_8A7FD4
                  + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                  + unk_8A7F04 * unk_8A7FA4;
              v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA6
                  + unk_8A7FD8
                  + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                  + unk_8A7F04 * unk_8A7FAA;
              v42 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC
                  + unk_8A7FDC
                  + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE
                  + unk_8A7F04 * unk_8A7FB0;
              v43 = -32768;
            }
            else
            {
              if ( v26 <= 0x41C412 )
              {
                if ( v26 == 4310034 )
                {
                  v44 = (__int16)word_8A7F2C;
                  v45 = (__int16)word_8A7F28;
                  v46 = (__int16)word_8A7F24;
LABEL_138:
                  v26 = v46 * SLOWORD(unk_8A7F80[0]) + unk_8A7FD4 + v45 * SHIWORD(unk_8A7F80[0]) + v44 * unk_8A7F84;
                  v40 = v44 * unk_8A7F8A + unk_8A7FD8 + v46 * unk_8A7F86 + v45 * unk_8A7F88;
                  v50 = unk_8A7FDC;
                  goto LABEL_54;
                }
                if ( v26 > (unsigned int)&loc_41A012 )
                {
                  if ( (_UNKNOWN *)v26 != (_UNKNOWN *)((char *)&loc_41A40D + 5) )
                  {
                    if ( v26 != 4309010 )
                      goto LABEL_630;
                    v35 = (__int16)word_8A7F28;
                    v36 = (__int16)word_8A7F24;
                    v34 = (__int16)word_8A7F2C;
                    v26 = (__int16)word_8A7F24 * SLOWORD(unk_8A7F80[0])
                        + unk_8A7FD4
                        + (__int16)word_8A7F28 * SHIWORD(unk_8A7F80[0])
                        + (__int16)word_8A7F2C * unk_8A7F84;
                    v40 = (__int16)word_8A7F2C * unk_8A7F8A
                        + unk_8A7FD8
                        + (__int16)word_8A7F24 * unk_8A7F86
                        + (__int16)word_8A7F28 * unk_8A7F88;
                    v41 = unk_8A7FDC;
                    goto LABEL_44;
                  }
                  v45 = (__int16)word_8A7F28;
                  v46 = (__int16)word_8A7F24;
                  v44 = (__int16)word_8A7F2C;
                  v26 = (__int16)word_8A7F24 * SLOWORD(unk_8A7F80[0])
                      + unk_8A7FB4
                      + (__int16)word_8A7F28 * SHIWORD(unk_8A7F80[0])
                      + (__int16)word_8A7F2C * unk_8A7F84;
                  v40 = (__int16)word_8A7F2C * unk_8A7F8A
                      + unk_8A7FB8
                      + (__int16)word_8A7F24 * unk_8A7F86
                      + (__int16)word_8A7F28 * unk_8A7F88;
                  v50 = unk_8A7FBC;
                  goto LABEL_54;
                }
                if ( (_UNKNOWN *)v26 == &loc_41A012 )
                {
                  v35 = (__int16)word_8A7F28;
                  v36 = (__int16)word_8A7F24;
                  v34 = (__int16)word_8A7F2C;
                  v26 = (__int16)word_8A7F24 * SLOWORD(unk_8A7F80[0])
                      + unk_8A7FB4
                      + (__int16)word_8A7F28 * SHIWORD(unk_8A7F80[0])
                      + (__int16)word_8A7F2C * unk_8A7F84;
                  v40 = (__int16)word_8A7F2C * unk_8A7F8A
                      + unk_8A7FB8
                      + (__int16)word_8A7F24 * unk_8A7F86
                      + (__int16)word_8A7F28 * unk_8A7F88;
                  v41 = unk_8A7FBC;
                  goto LABEL_44;
                }
                if ( (_UNKNOWN *)v26 != &loc_416412 )
                {
                  if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_418011 + 1) )
                  {
                    v34 = (__int16)word_8A7F2C;
                    v35 = (__int16)word_8A7F28;
                    v36 = (__int16)word_8A7F24;
LABEL_42:
                    v26 = v36 * SLOWORD(unk_8A7F80[0]) + unk_8A7F94 + v35 * SHIWORD(unk_8A7F80[0]) + v34 * unk_8A7F84;
                    v37 = unk_8A7F98 + v36 * unk_8A7F86;
                    v38 = v34 * unk_8A7F8A;
                    v39 = v35 * unk_8A7F88;
LABEL_43:
                    v40 = v38 + v37 + v39;
                    v41 = unk_8A7F9C;
LABEL_44:
                    v42 = v36 * unk_8A7F8C + v41 + v35 * unk_8A7F8E + v34 * unk_8A7F90;
                    v43 = -32768;
                    goto LABEL_56;
                  }
                  if ( (_UNKNOWN *)v26 != (_UNKNOWN *)((char *)&loc_418411 + 1) )
                    goto LABEL_630;
                  v44 = (__int16)word_8A7F2C;
                  v45 = (__int16)word_8A7F28;
                  v46 = (__int16)word_8A7F24;
                  goto LABEL_52;
                }
                v54 = unk_8A7F14;
                v55 = unk_8A7F12;
                v56 = unk_8A7F10;
                goto LABEL_98;
              }
              if ( v26 > 0x420412 )
              {
                if ( (_UNKNOWN *)v26 != &loc_422012 )
                {
                  if ( (_UNKNOWN *)v26 != &loc_422412 )
                    goto LABEL_630;
                  v44 = unk_8A7F04;
                  v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA0
                      + unk_8A7FB4
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                      + unk_8A7F04 * unk_8A7FA4;
                  v51 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
                  v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA6
                      + unk_8A7FB8
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                      + unk_8A7F04 * unk_8A7FAA;
                  v52 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
                  v50 = unk_8A7FBC;
                  v53 = unk_8A7FB0;
                  goto LABEL_55;
                }
                v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA0
                    + unk_8A7FB4
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                    + unk_8A7F04 * unk_8A7FA4;
                v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA6
                    + unk_8A7FB8
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                    + unk_8A7F04 * unk_8A7FAA;
                v42 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC
                    + unk_8A7FBC
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE
                    + unk_8A7F04 * unk_8A7FB0;
                v43 = -32768;
              }
              else
              {
                if ( v26 == 4326418 )
                {
                  v44 = unk_8A7F04;
                  v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA0
                      + unk_8A7F94
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                      + unk_8A7F04 * unk_8A7FA4;
                  v51 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
                  v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA6
                      + unk_8A7F98
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                      + unk_8A7F04 * unk_8A7FAA;
                  v52 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
                  v50 = unk_8A7F9C;
                  v53 = unk_8A7FB0;
                  goto LABEL_55;
                }
                if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_41E010 + 2) )
                {
                  v59 = (__int16)word_8A7F2C;
                  v60 = (__int16)word_8A7F28;
                  v61 = (__int16)word_8A7F24;
LABEL_79:
                  v26 = v59 * unk_8A7F84 + v60 * SHIWORD(unk_8A7F80[0]) + v61 * SLOWORD(unk_8A7F80[0]);
                  v62 = v61 * unk_8A7F86 + v59 * unk_8A7F8A;
                  v63 = v60 * unk_8A7F88;
LABEL_80:
                  v40 = v63 + v62;
                  v42 = v59 * unk_8A7F90 + v60 * unk_8A7F8E + v61 * unk_8A7F8C;
                  v43 = -32768;
                  goto LABEL_56;
                }
                if ( v26 == 4318226 )
                {
                  v54 = (__int16)word_8A7F2C;
                  v55 = (__int16)word_8A7F28;
                  v56 = (__int16)word_8A7F24;
LABEL_72:
                  v26 = v54 * unk_8A7F84 + v55 * SHIWORD(unk_8A7F80[0]) + v56 * SLOWORD(unk_8A7F80[0]);
                  v57 = v56 * unk_8A7F86 + v54 * unk_8A7F8A;
                  v58 = v55 * unk_8A7F88;
LABEL_99:
                  v64 = v58 + v57;
                  v65 = v56 * unk_8A7F8C;
                  v66 = v55 * unk_8A7F8E;
                  v67 = unk_8A7F90;
LABEL_100:
                  v68 = v66 + v65;
                  v69 = v54 * v67;
LABEL_101:
                  v42 = v69 + v68;
                  goto LABEL_102;
                }
                if ( (_UNKNOWN *)v26 != &loc_420012 )
                  goto LABEL_630;
                v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA0
                    + unk_8A7F94
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                    + unk_8A7F04 * unk_8A7FA4;
                v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA6
                    + unk_8A7F98
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                    + unk_8A7F04 * unk_8A7FAA;
                v42 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC
                    + unk_8A7F9C
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE
                    + unk_8A7F04 * unk_8A7FB0;
                v43 = -32768;
              }
            }
LABEL_56:
            unk_8A7F64 = v26;
            unk_8A7F68 = v40;
            unk_8A7F6C = v42;
            if ( (int)v26 >= v43 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                word_8A7F24 = v26;
              }
              else
              {
                unk_8A7FFC = -2130706432;
                word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC = -2130706432;
              word_8A7F24 = v43;
            }
            if ( v40 >= v43 )
            {
              if ( v40 <= 0x7FFF )
              {
                word_8A7F28 = v40;
              }
              else
              {
                unk_8A7FFC |= 0x80800000;
                word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x80800000;
              word_8A7F28 = v43;
            }
            if ( v42 >= v43 )
            {
LABEL_541:
              if ( v42 <= 0x7FFF )
              {
                word_8A7F2C = v42;
              }
              else
              {
                word_8A7F2C = 0x7FFF;
                LOBYTE(v26) = unk_8A7FFC;
                unk_8A7FFC |= 0x400000u;
              }
              return v26;
            }
LABEL_558:
            word_8A7F2C = v43;
            LOBYTE(v26) = unk_8A7FFC;
            unk_8A7FFC |= 0x400000u;
            return v26;
          }
          if ( v26 > (unsigned int)&loc_42A411 + 1 )
          {
            if ( v26 > 0x42E412 )
            {
              if ( v26 != 4390930 )
              {
                if ( (_UNKNOWN *)v26 != (_UNKNOWN *)((char *)&loc_43040D + 5) )
                  goto LABEL_630;
                v44 = unk_8A7F14;
                v26 = unk_8A7F10 * unk_8A7FA0 + unk_8A7F94 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F14 * unk_8A7FA4;
                v51 = unk_8A7F10 * unk_8A7FAC;
                v40 = unk_8A7F10 * unk_8A7FA6 + unk_8A7F98 + unk_8A7F12 * unk_8A7FA8 + unk_8A7F14 * unk_8A7FAA;
                v52 = unk_8A7F12 * unk_8A7FAE;
                v50 = unk_8A7F9C;
                v53 = unk_8A7FB0;
                goto LABEL_55;
              }
              v26 = unk_8A7F10 * unk_8A7FA0 + unk_8A7F94 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F14 * unk_8A7FA4;
              v40 = unk_8A7F10 * unk_8A7FA6 + unk_8A7F98 + unk_8A7F12 * unk_8A7FA8 + unk_8A7F14 * unk_8A7FAA;
              v42 = unk_8A7F10 * unk_8A7FAC + unk_8A7F9C + unk_8A7F12 * unk_8A7FAE + unk_8A7F14 * unk_8A7FB0;
              v43 = -32768;
            }
            else
            {
              if ( v26 == 4383762 )
              {
                v54 = unk_8A7F0C;
                v26 = unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0;
                v64 = unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6;
                v65 = unk_8A7F08 * unk_8A7FAC;
                v66 = unk_8A7F0A * unk_8A7FAE;
                v67 = unk_8A7FB0;
                goto LABEL_100;
              }
              if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_42C011 + 1) )
              {
                v26 = unk_8A7F08 * unk_8A7FA0 + unk_8A7FD4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F0C * unk_8A7FA4;
                v40 = unk_8A7F08 * unk_8A7FA6 + unk_8A7FD8 + unk_8A7F0A * unk_8A7FA8 + unk_8A7F0C * unk_8A7FAA;
                v42 = unk_8A7F08 * unk_8A7FAC + unk_8A7FDC + unk_8A7F0A * unk_8A7FAE + unk_8A7F0C * unk_8A7FB0;
                v43 = -32768;
              }
              else
              {
                if ( (_UNKNOWN **)v26 == (_UNKNOWN **)((char *)&jpt_42B743[14] + 2) )
                {
                  v44 = unk_8A7F0C;
                  v26 = unk_8A7F08 * unk_8A7FA0 + unk_8A7FD4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F0C * unk_8A7FA4;
                  v51 = unk_8A7F08 * unk_8A7FAC;
                  v40 = unk_8A7F08 * unk_8A7FA6 + unk_8A7FD8 + unk_8A7F0A * unk_8A7FA8 + unk_8A7F0C * unk_8A7FAA;
                  v52 = unk_8A7F0A * unk_8A7FAE;
                  v50 = unk_8A7FDC;
                  v53 = unk_8A7FB0;
                  goto LABEL_55;
                }
                if ( v26 != 4382738 )
                  goto LABEL_630;
                v26 = unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0;
                v40 = unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6;
                v42 = unk_8A7F0C * unk_8A7FB0 + unk_8A7F0A * unk_8A7FAE + unk_8A7F08 * unk_8A7FAC;
                v43 = -32768;
              }
            }
            goto LABEL_56;
          }
          if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_42A411 + 1) )
          {
            v44 = unk_8A7F0C;
            v26 = unk_8A7F08 * unk_8A7FA0 + unk_8A7FB4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F0C * unk_8A7FA4;
            v51 = unk_8A7F08 * unk_8A7FAC;
            v40 = unk_8A7F08 * unk_8A7FA6 + unk_8A7FB8 + unk_8A7F0A * unk_8A7FA8 + unk_8A7F0C * unk_8A7FAA;
            v52 = unk_8A7F0A * unk_8A7FAE;
            v50 = unk_8A7FBC;
            v53 = unk_8A7FB0;
            goto LABEL_55;
          }
          if ( v26 > 0x428012 )
          {
            if ( v26 == 4359186 )
            {
              v44 = unk_8A7F0C;
              v26 = unk_8A7F08 * unk_8A7FA0 + unk_8A7F94 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F0C * unk_8A7FA4;
              v51 = unk_8A7F08 * unk_8A7FAC;
              v40 = unk_8A7F08 * unk_8A7FA6 + unk_8A7F98 + unk_8A7F0A * unk_8A7FA8 + unk_8A7F0C * unk_8A7FAA;
              v52 = unk_8A7F0A * unk_8A7FAE;
              v50 = unk_8A7F9C;
              v53 = unk_8A7FB0;
              goto LABEL_55;
            }
            if ( (_UNKNOWN *)v26 != (_UNKNOWN *)((char *)&loc_42A00F + 3) )
              goto LABEL_630;
            v26 = unk_8A7F08 * unk_8A7FA0 + unk_8A7FB4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F0C * unk_8A7FA4;
            v40 = unk_8A7F08 * unk_8A7FA6 + unk_8A7FB8 + unk_8A7F0A * unk_8A7FA8 + unk_8A7F0C * unk_8A7FAA;
            v42 = unk_8A7F08 * unk_8A7FAC + unk_8A7FBC + unk_8A7F0A * unk_8A7FAE + unk_8A7F0C * unk_8A7FB0;
            v43 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4358162 )
          {
            v26 = unk_8A7F08 * unk_8A7FA0 + unk_8A7F94 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F0C * unk_8A7FA4;
            v40 = unk_8A7F08 * unk_8A7FA6 + unk_8A7F98 + unk_8A7F0A * unk_8A7FA8 + unk_8A7F0C * unk_8A7FAA;
            v42 = unk_8A7F08 * unk_8A7FAC + unk_8A7F9C + unk_8A7F0A * unk_8A7FAE + unk_8A7F0C * unk_8A7FB0;
            v43 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4342802 )
          {
            v44 = unk_8A7F04;
            v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA0
                + unk_8A7FD4
                + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                + unk_8A7F04 * unk_8A7FA4;
            v51 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
            v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FA6
                + unk_8A7FD8
                + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                + unk_8A7F04 * unk_8A7FAA;
            v52 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
            v50 = unk_8A7FDC;
            v53 = unk_8A7FB0;
            goto LABEL_55;
          }
          if ( v26 != 4349970 )
          {
            if ( (_UNKNOWN *)v26 != &loc_426412 )
              goto LABEL_630;
            v54 = unk_8A7F04;
            v26 = unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0;
            v64 = unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6;
            v65 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
            v66 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
            v67 = unk_8A7FB0;
            goto LABEL_100;
          }
          v70 = SHIWORD(unk_8A7F00[0]);
          v71 = SLOWORD(unk_8A7F00[0]);
          v72 = unk_8A7F04;
          v26 = unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0;
LABEL_214:
          v40 = v72 * unk_8A7FAA + v70 * unk_8A7FA8 + v71 * unk_8A7FA6;
          v42 = v72 * unk_8A7FB0 + v70 * unk_8A7FAE + v71 * unk_8A7FAC;
          v43 = -32768;
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
                if ( v26 <= (unsigned int)&loc_43A011 + 1 )
                {
                  if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_43A011 + 1) )
                  {
                    v26 = (__int16)word_8A7F24 * unk_8A7FA0
                        + unk_8A7FB4
                        + (__int16)word_8A7F28 * unk_8A7FA2
                        + (__int16)word_8A7F2C * unk_8A7FA4;
                    v40 = (__int16)word_8A7F24 * unk_8A7FA6
                        + unk_8A7FB8
                        + (__int16)word_8A7F28 * unk_8A7FA8
                        + (__int16)word_8A7F2C * unk_8A7FAA;
                    v42 = (__int16)word_8A7F24 * unk_8A7FAC
                        + unk_8A7FBC
                        + (__int16)word_8A7F28 * unk_8A7FAE
                        + (__int16)word_8A7F2C * unk_8A7FB0;
                    v43 = -32768;
                  }
                  else if ( v26 > (unsigned int)&loc_43600F + 3 )
                  {
                    if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_436411 + 1) )
                    {
                      v54 = unk_8A7F14;
                      v26 = unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0;
                      v64 = unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6;
                      v65 = unk_8A7F10 * unk_8A7FAC;
                      v66 = unk_8A7F12 * unk_8A7FAE;
                      v67 = unk_8A7FB0;
                      goto LABEL_100;
                    }
                    if ( v26 != 4423698 )
                    {
                      if ( v26 != 4424722 )
                        goto LABEL_630;
                      v44 = (__int16)word_8A7F2C;
                      v26 = (__int16)word_8A7F24 * unk_8A7FA0
                          + unk_8A7F94
                          + (__int16)word_8A7F28 * unk_8A7FA2
                          + (__int16)word_8A7F2C * unk_8A7FA4;
                      v51 = (__int16)word_8A7F24 * unk_8A7FAC;
                      v40 = (__int16)word_8A7F24 * unk_8A7FA6
                          + unk_8A7F98
                          + (__int16)word_8A7F28 * unk_8A7FA8
                          + (__int16)word_8A7F2C * unk_8A7FAA;
                      v52 = (__int16)word_8A7F28 * unk_8A7FAE;
                      v50 = unk_8A7F9C;
                      v53 = unk_8A7FB0;
                      goto LABEL_55;
                    }
                    v26 = (__int16)word_8A7F24 * unk_8A7FA0
                        + unk_8A7F94
                        + (__int16)word_8A7F28 * unk_8A7FA2
                        + (__int16)word_8A7F2C * unk_8A7FA4;
                    v40 = (__int16)word_8A7F24 * unk_8A7FA6
                        + unk_8A7F98
                        + (__int16)word_8A7F28 * unk_8A7FA8
                        + (__int16)word_8A7F2C * unk_8A7FAA;
                    v42 = (__int16)word_8A7F24 * unk_8A7FAC
                        + unk_8A7F9C
                        + (__int16)word_8A7F28 * unk_8A7FAE
                        + (__int16)word_8A7F2C * unk_8A7FB0;
                    v43 = -32768;
                  }
                  else if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_43600F + 3) )
                  {
                    v26 = unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0;
                    v40 = unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6;
                    v42 = unk_8A7F14 * unk_8A7FB0 + unk_8A7F12 * unk_8A7FAE + unk_8A7F10 * unk_8A7FAC;
                    v43 = -32768;
                  }
                  else
                  {
                    if ( (_UNKNOWN *)v26 == (_UNKNOWN *)((char *)&loc_432410 + 2) )
                    {
                      v44 = unk_8A7F14;
                      v26 = unk_8A7F10 * unk_8A7FA0 + unk_8A7FB4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F14 * unk_8A7FA4;
                      v51 = unk_8A7F10 * unk_8A7FAC;
                      v40 = unk_8A7F10 * unk_8A7FA6 + unk_8A7FB8 + unk_8A7F12 * unk_8A7FA8 + unk_8A7F14 * unk_8A7FAA;
                      v52 = unk_8A7F12 * unk_8A7FAE;
                      v50 = unk_8A7FBC;
                      v53 = unk_8A7FB0;
                      goto LABEL_55;
                    }
                    if ( (_UNKNOWN *)v26 != (_UNKNOWN *)((char *)&loc_434011 + 1) )
                    {
                      if ( (_UNKNOWN *)v26 != &loc_434412 )
                        goto LABEL_630;
                      v44 = unk_8A7F14;
                      v26 = unk_8A7F10 * unk_8A7FA0 + unk_8A7FD4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F14 * unk_8A7FA4;
                      v51 = unk_8A7F10 * unk_8A7FAC;
                      v40 = unk_8A7F10 * unk_8A7FA6 + unk_8A7FD8 + unk_8A7F12 * unk_8A7FA8 + unk_8A7F14 * unk_8A7FAA;
                      v52 = unk_8A7F12 * unk_8A7FAE;
                      v50 = unk_8A7FDC;
                      v53 = unk_8A7FB0;
                      goto LABEL_55;
                    }
                    v26 = unk_8A7F10 * unk_8A7FA0 + unk_8A7FD4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F14 * unk_8A7FA4;
                    v40 = unk_8A7F10 * unk_8A7FA6 + unk_8A7FD8 + unk_8A7F12 * unk_8A7FA8 + unk_8A7F14 * unk_8A7FAA;
                    v42 = unk_8A7F10 * unk_8A7FAC + unk_8A7FDC + unk_8A7F12 * unk_8A7FAE + unk_8A7F14 * unk_8A7FB0;
                    v43 = -32768;
                  }
                  goto LABEL_56;
                }
                if ( v26 <= 0x43E012 )
                {
                  if ( v26 != 4448274 )
                  {
                    if ( v26 == 4432914 )
                    {
                      v44 = (__int16)word_8A7F2C;
                      v26 = (__int16)word_8A7F24 * unk_8A7FA0
                          + unk_8A7FB4
                          + (__int16)word_8A7F28 * unk_8A7FA2
                          + (__int16)word_8A7F2C * unk_8A7FA4;
                      v51 = (__int16)word_8A7F24 * unk_8A7FAC;
                      v40 = (__int16)word_8A7F24 * unk_8A7FA6
                          + unk_8A7FB8
                          + (__int16)word_8A7F28 * unk_8A7FA8
                          + (__int16)word_8A7F2C * unk_8A7FAA;
                      v52 = (__int16)word_8A7F28 * unk_8A7FAE;
                      v50 = unk_8A7FBC;
                      v53 = unk_8A7FB0;
                      goto LABEL_55;
                    }
                    if ( (_UNKNOWN *)v26 != &loc_43C012 )
                    {
                      if ( (_UNKNOWN *)v26 != &loc_43C412 )
                        goto LABEL_630;
                      v44 = (__int16)word_8A7F2C;
                      v26 = (__int16)word_8A7F24 * unk_8A7FA0
                          + unk_8A7FD4
                          + (__int16)word_8A7F28 * unk_8A7FA2
                          + (__int16)word_8A7F2C * unk_8A7FA4;
                      v51 = (__int16)word_8A7F24 * unk_8A7FAC;
                      v40 = (__int16)word_8A7F24 * unk_8A7FA6
                          + unk_8A7FD8
                          + (__int16)word_8A7F28 * unk_8A7FA8
                          + (__int16)word_8A7F2C * unk_8A7FAA;
                      v52 = (__int16)word_8A7F28 * unk_8A7FAE;
                      v50 = unk_8A7FDC;
                      v53 = unk_8A7FB0;
                      goto LABEL_55;
                    }
                    v26 = (__int16)word_8A7F24 * unk_8A7FA0
                        + unk_8A7FD4
                        + (__int16)word_8A7F28 * unk_8A7FA2
                        + (__int16)word_8A7F2C * unk_8A7FA4;
                    v40 = (__int16)word_8A7F24 * unk_8A7FA6
                        + unk_8A7FD8
                        + (__int16)word_8A7F28 * unk_8A7FA8
                        + (__int16)word_8A7F2C * unk_8A7FAA;
                    v42 = (__int16)word_8A7F24 * unk_8A7FAC
                        + unk_8A7FDC
                        + (__int16)word_8A7F28 * unk_8A7FAE
                        + (__int16)word_8A7F2C * unk_8A7FB0;
                    v43 = -32768;
                    goto LABEL_56;
                  }
                  v70 = (__int16)word_8A7F28;
                  v71 = (__int16)word_8A7F24;
                  v72 = (__int16)word_8A7F2C;
                  v26 = (__int16)word_8A7F2C * unk_8A7FA4
                      + (__int16)word_8A7F28 * unk_8A7FA2
                      + (__int16)word_8A7F24 * unk_8A7FA0;
                  goto LABEL_214;
                }
                if ( (_UNKNOWN *)v26 == &loc_43E412 )
                {
                  v54 = (__int16)word_8A7F2C;
                  v26 = (__int16)word_8A7F2C * unk_8A7FA4
                      + (__int16)word_8A7F28 * unk_8A7FA2
                      + (__int16)word_8A7F24 * unk_8A7FA0;
                  v64 = (__int16)word_8A7F2C * unk_8A7FAA
                      + (__int16)word_8A7F28 * unk_8A7FA8
                      + (__int16)word_8A7F24 * unk_8A7FA6;
                  v65 = (__int16)word_8A7F24 * unk_8A7FAC;
                  v66 = (__int16)word_8A7F28 * unk_8A7FAE;
                  v67 = unk_8A7FB0;
                  goto LABEL_100;
                }
                if ( v26 != 4456466 )
                  goto LABEL_630;
                v73 = SHIWORD(unk_8A7F00[0]);
                v74 = SLOWORD(unk_8A7F00[0]);
                v75 = unk_8A7F04;
                v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC0
                    + unk_8A7F94
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                    + unk_8A7F04 * unk_8A7FC4;
                v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC6
                    + unk_8A7F98
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FC8
                    + unk_8A7F04 * unk_8A7FCA;
                v76 = unk_8A7F9C;
LABEL_282:
                v42 = v74 * unk_8A7FCC + v76 + v73 * unk_8A7FCE + v75 * unk_8A7FD0;
                v43 = -32768;
                goto LABEL_56;
              }
              v77 = SHIWORD(unk_8A7F00[0]);
              v78 = SLOWORD(unk_8A7F00[0]);
              v44 = unk_8A7F04;
              v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC0
                  + unk_8A7F94
                  + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                  + unk_8A7F04 * unk_8A7FC4;
              v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC6
                  + unk_8A7F98
                  + SHIWORD(unk_8A7F00[0]) * unk_8A7FC8
                  + unk_8A7F04 * unk_8A7FCA;
              v50 = unk_8A7F9C;
LABEL_287:
              v51 = v78 * unk_8A7FCC;
              v52 = v77 * unk_8A7FCE;
              v53 = unk_8A7FD0;
              goto LABEL_55;
            }
            if ( v26 <= 0x448012 )
            {
              if ( v26 == 4489234 )
              {
                v26 = unk_8A7F08 * unk_8A7FC0 + unk_8A7F94 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F0C * unk_8A7FC4;
                v40 = unk_8A7F0A * unk_8A7FC8 + unk_8A7F98 + unk_8A7F0C * unk_8A7FCA + unk_8A7F08 * unk_8A7FC6;
                v42 = unk_8A7F08 * unk_8A7FCC + unk_8A7F9C + unk_8A7F0A * unk_8A7FCE + unk_8A7F0C * unk_8A7FD0;
                v43 = -32768;
                goto LABEL_56;
              }
              if ( v26 <= (unsigned int)&loc_444410 + 2 )
              {
                if ( (_UNKNOWN *)v26 != (_UNKNOWN *)((char *)&loc_444410 + 2) )
                {
                  if ( v26 != 4464658 )
                  {
                    if ( v26 == 4465682 )
                    {
                      v77 = SHIWORD(unk_8A7F00[0]);
                      v78 = SLOWORD(unk_8A7F00[0]);
                      v44 = unk_8A7F04;
                      v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC0
                          + unk_8A7FB4
                          + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                          + unk_8A7F04 * unk_8A7FC4;
                      v40 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC6
                          + unk_8A7FB8
                          + SHIWORD(unk_8A7F00[0]) * unk_8A7FC8
                          + unk_8A7F04 * unk_8A7FCA;
                      v50 = unk_8A7FBC;
                      goto LABEL_287;
                    }
                    if ( v26 != 4472850 )
                      goto LABEL_630;
                    v73 = SHIWORD(unk_8A7F00[0]);
                    v74 = SLOWORD(unk_8A7F00[0]);
                    v75 = unk_8A7F04;
                    v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC0
                        + unk_8A7FD4
                        + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                        + unk_8A7F04 * unk_8A7FC4;
                    v79 = unk_8A7FD8 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC8;
                    v80 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
                    v81 = unk_8A7F04 * unk_8A7FCA;
LABEL_281:
                    v40 = v80 + v79 + v81;
                    v76 = unk_8A7FDC;
                    goto LABEL_282;
                  }
                  v82 = SHIWORD(unk_8A7F00[0]);
                  v83 = SLOWORD(unk_8A7F00[0]);
                  v84 = unk_8A7F04;
                  v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC0
                      + unk_8A7FB4
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                      + unk_8A7F04 * unk_8A7FC4;
                  v85 = unk_8A7FB8 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC8;
                  v86 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
                  v87 = unk_8A7F04 * unk_8A7FCA;
LABEL_277:
                  v40 = v86 + v85 + v87;
                  v42 = v83 * unk_8A7FCC + unk_8A7FBC + v82 * unk_8A7FCE + v84 * unk_8A7FD0;
                  v43 = -32768;
                  goto LABEL_56;
                }
                v77 = SHIWORD(unk_8A7F00[0]);
                v78 = SLOWORD(unk_8A7F00[0]);
                v44 = unk_8A7F04;
                v26 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC0
                    + unk_8A7FD4
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                    + unk_8A7F04 * unk_8A7FC4;
                v88 = unk_8A7FD8 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC8;
                v89 = SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
                v90 = unk_8A7F04 * unk_8A7FCA;
LABEL_286:
                v40 = v89 + v88 + v90;
                v50 = unk_8A7FDC;
                goto LABEL_287;
              }
              if ( (_UNKNOWN *)v26 != &loc_446012 )
              {
                if ( (_UNKNOWN *)v26 != &loc_446412 )
                  goto LABEL_630;
                v91 = SHIWORD(unk_8A7F00[0]);
                v92 = SLOWORD(unk_8A7F00[0]);
                v54 = unk_8A7F04;
                v26 = unk_8A7F04 * unk_8A7FC4
                    + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                    + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0;
                v93 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
                v94 = unk_8A7F04 * unk_8A7FCA;
                goto LABEL_302;
              }
              v95 = SHIWORD(unk_8A7F00[0]);
              v96 = SLOWORD(unk_8A7F00[0]);
              v97 = unk_8A7F04;
              v26 = unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0;
              v98 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
              v99 = unk_8A7F04 * unk_8A7FCA;
LABEL_305:
              v40 = v99 + v98;
              v42 = v97 * unk_8A7FD0 + v95 * unk_8A7FCE + v96 * unk_8A7FCC;
              v43 = -32768;
              goto LABEL_56;
            }
            if ( v26 <= 0x44C012 )
            {
              if ( v26 == 4505618 )
              {
                v26 = unk_8A7F08 * unk_8A7FC0 + unk_8A7FD4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F0C * unk_8A7FC4;
                v40 = unk_8A7F0A * unk_8A7FC8 + unk_8A7FD8 + unk_8A7F0C * unk_8A7FCA + unk_8A7F08 * unk_8A7FC6;
                v42 = unk_8A7F08 * unk_8A7FCC + unk_8A7FDC + unk_8A7F0A * unk_8A7FCE + unk_8A7F0C * unk_8A7FD0;
                v43 = -32768;
                goto LABEL_56;
              }
              if ( v26 == 4490258 )
              {
                v77 = unk_8A7F0A;
                v78 = unk_8A7F08;
                v44 = unk_8A7F0C;
                v26 = unk_8A7F08 * unk_8A7FC0 + unk_8A7F94 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F0C * unk_8A7FC4;
                v40 = unk_8A7F0A * unk_8A7FC8 + unk_8A7F98 + unk_8A7F0C * unk_8A7FCA + unk_8A7F08 * unk_8A7FC6;
                v50 = unk_8A7F9C;
              }
              else
              {
                if ( (_UNKNOWN *)v26 == &unk_44A012 )
                {
                  v26 = unk_8A7F08 * unk_8A7FC0 + unk_8A7FB4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F0C * unk_8A7FC4;
                  v40 = unk_8A7F0A * unk_8A7FC8 + unk_8A7FB8 + unk_8A7F0C * unk_8A7FCA + unk_8A7F08 * unk_8A7FC6;
                  v42 = unk_8A7F08 * unk_8A7FCC + unk_8A7FBC + unk_8A7F0A * unk_8A7FCE + unk_8A7F0C * unk_8A7FD0;
                  v43 = -32768;
                  goto LABEL_56;
                }
                if ( v26 != 4498450 )
                  goto LABEL_630;
                v77 = unk_8A7F0A;
                v78 = unk_8A7F08;
                v44 = unk_8A7F0C;
                v26 = unk_8A7F08 * unk_8A7FC0 + unk_8A7FB4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F0C * unk_8A7FC4;
                v40 = unk_8A7F0A * unk_8A7FC8 + unk_8A7FB8 + unk_8A7F0C * unk_8A7FCA + unk_8A7F08 * unk_8A7FC6;
                v50 = unk_8A7FBC;
              }
              goto LABEL_287;
            }
            if ( v26 != 4506642 )
            {
              if ( v26 != 4513810 )
                goto LABEL_630;
              v95 = unk_8A7F0A;
              v96 = unk_8A7F08;
              v97 = unk_8A7F0C;
              v26 = unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0;
              goto LABEL_304;
            }
            v44 = unk_8A7F0C;
            v77 = unk_8A7F0A;
            v78 = unk_8A7F08;
LABEL_285:
            v26 = v78 * unk_8A7FC0 + unk_8A7FD4 + v77 * unk_8A7FC2 + v44 * unk_8A7FC4;
            v88 = unk_8A7FD8 + v44 * unk_8A7FCA;
            v89 = v77 * unk_8A7FC8;
            v90 = v78 * unk_8A7FC6;
            goto LABEL_286;
          }
          v91 = unk_8A7F0A;
          v92 = unk_8A7F08;
          v54 = unk_8A7F0C;
          v26 = unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0;
LABEL_301:
          v93 = v54 * unk_8A7FCA + v91 * unk_8A7FC8;
          v94 = v92 * unk_8A7FC6;
LABEL_302:
          v64 = v94 + v93;
          v65 = v92 * unk_8A7FCC;
          v66 = v91 * unk_8A7FCE;
          v67 = unk_8A7FD0;
          goto LABEL_100;
        }
        if ( v26 <= (unsigned int)&unk_45C412 )
        {
          if ( (_UNKNOWN *)v26 == &unk_45C412 )
          {
            v44 = (__int16)word_8A7F2C;
            v77 = (__int16)word_8A7F28;
            v78 = (__int16)word_8A7F24;
            goto LABEL_285;
          }
          if ( v26 > (unsigned int)&word_456012 )
          {
            if ( v26 > 0x45A012 )
            {
              if ( v26 == 4563986 )
              {
                v77 = (__int16)word_8A7F28;
                v78 = (__int16)word_8A7F24;
                v44 = (__int16)word_8A7F2C;
                v26 = (__int16)word_8A7F24 * unk_8A7FC0
                    + unk_8A7FB4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F2C * unk_8A7FC4;
                v40 = (__int16)word_8A7F28 * unk_8A7FC8
                    + unk_8A7FB8
                    + (__int16)word_8A7F2C * unk_8A7FCA
                    + (__int16)word_8A7F24 * unk_8A7FC6;
                v50 = unk_8A7FBC;
                goto LABEL_287;
              }
              if ( v26 != 4571154 )
                goto LABEL_630;
              v73 = (__int16)word_8A7F28;
              v74 = (__int16)word_8A7F24;
              v75 = (__int16)word_8A7F2C;
              v26 = (__int16)word_8A7F24 * unk_8A7FC0
                  + unk_8A7FD4
                  + (__int16)word_8A7F28 * unk_8A7FC2
                  + (__int16)word_8A7F2C * unk_8A7FC4;
              v79 = unk_8A7FD8 + (__int16)word_8A7F2C * unk_8A7FCA;
              v80 = (__int16)word_8A7F28 * unk_8A7FC8;
              v81 = (__int16)word_8A7F24 * unk_8A7FC6;
              goto LABEL_281;
            }
            if ( v26 == 4562962 )
            {
              v82 = (__int16)word_8A7F28;
              v83 = (__int16)word_8A7F24;
              v84 = (__int16)word_8A7F2C;
              v26 = (__int16)word_8A7F24 * unk_8A7FC0
                  + unk_8A7FB4
                  + (__int16)word_8A7F28 * unk_8A7FC2
                  + (__int16)word_8A7F2C * unk_8A7FC4;
              v85 = unk_8A7FB8 + (__int16)word_8A7F2C * unk_8A7FCA;
              v86 = (__int16)word_8A7F28 * unk_8A7FC8;
              v87 = (__int16)word_8A7F24 * unk_8A7FC6;
              goto LABEL_277;
            }
            if ( v26 != 4547602 )
            {
              if ( v26 == 4554770 )
              {
                v26 = (__int16)word_8A7F24 * unk_8A7FC0
                    + unk_8A7F94
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F2C * unk_8A7FC4;
                v40 = (__int16)word_8A7F28 * unk_8A7FC8
                    + unk_8A7F98
                    + (__int16)word_8A7F2C * unk_8A7FCA
                    + (__int16)word_8A7F24 * unk_8A7FC6;
                v42 = (__int16)word_8A7F24 * unk_8A7FCC
                    + unk_8A7F9C
                    + (__int16)word_8A7F28 * unk_8A7FCE
                    + (__int16)word_8A7F2C * unk_8A7FD0;
                v43 = -32768;
                goto LABEL_56;
              }
              if ( (_UNKNOWN **)v26 != &off_458412 )
                goto LABEL_630;
              v77 = (__int16)word_8A7F28;
              v78 = (__int16)word_8A7F24;
              v44 = (__int16)word_8A7F2C;
              v26 = (__int16)word_8A7F24 * unk_8A7FC0
                  + unk_8A7F94
                  + (__int16)word_8A7F28 * unk_8A7FC2
                  + (__int16)word_8A7F2C * unk_8A7FC4;
              v40 = (__int16)word_8A7F28 * unk_8A7FC8
                  + unk_8A7F98
                  + (__int16)word_8A7F2C * unk_8A7FCA
                  + (__int16)word_8A7F24 * unk_8A7FC6;
              v50 = unk_8A7F9C;
              goto LABEL_287;
            }
            v91 = unk_8A7F12;
            v92 = unk_8A7F10;
            v54 = unk_8A7F14;
            v26 = unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0;
            goto LABEL_301;
          }
          if ( (__int16 *)v26 != &word_456012 )
          {
            if ( v26 <= (unsigned int)&unk_452412 )
            {
              if ( (_UNKNOWN *)v26 == &unk_452412 )
              {
                v77 = unk_8A7F12;
                v78 = unk_8A7F10;
                v44 = unk_8A7F14;
                v26 = unk_8A7F10 * unk_8A7FC0 + unk_8A7FB4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F14 * unk_8A7FC4;
                v40 = unk_8A7F12 * unk_8A7FC8 + unk_8A7FB8 + unk_8A7F14 * unk_8A7FCA + unk_8A7F10 * unk_8A7FC6;
                v50 = unk_8A7FBC;
              }
              else
              {
                if ( v26 == 4522002 )
                {
                  v26 = unk_8A7F10 * unk_8A7FC0 + unk_8A7F94 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F14 * unk_8A7FC4;
                  v40 = unk_8A7F12 * unk_8A7FC8 + unk_8A7F98 + unk_8A7F14 * unk_8A7FCA + unk_8A7F10 * unk_8A7FC6;
                  v42 = unk_8A7F10 * unk_8A7FCC + unk_8A7F9C + unk_8A7F12 * unk_8A7FCE + unk_8A7F14 * unk_8A7FD0;
                  v43 = -32768;
                  goto LABEL_56;
                }
                if ( v26 != 4523026 )
                {
                  if ( v26 != 0x452012 )
                    goto LABEL_630;
                  v26 = unk_8A7F10 * unk_8A7FC0 + unk_8A7FB4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F14 * unk_8A7FC4;
                  v40 = unk_8A7F12 * unk_8A7FC8 + unk_8A7FB8 + unk_8A7F14 * unk_8A7FCA + unk_8A7F10 * unk_8A7FC6;
                  v42 = unk_8A7F10 * unk_8A7FCC + unk_8A7FBC + unk_8A7F12 * unk_8A7FCE + unk_8A7F14 * unk_8A7FD0;
                  v43 = -32768;
                  goto LABEL_56;
                }
                v77 = unk_8A7F12;
                v78 = unk_8A7F10;
                v44 = unk_8A7F14;
                v26 = unk_8A7F10 * unk_8A7FC0 + unk_8A7F94 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F14 * unk_8A7FC4;
                v40 = unk_8A7F12 * unk_8A7FC8 + unk_8A7F98 + unk_8A7F14 * unk_8A7FCA + unk_8A7F10 * unk_8A7FC6;
                v50 = unk_8A7F9C;
              }
              goto LABEL_287;
            }
            if ( v26 == 4538386 )
            {
              v26 = unk_8A7F10 * unk_8A7FC0 + unk_8A7FD4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F14 * unk_8A7FC4;
              v40 = unk_8A7F12 * unk_8A7FC8 + unk_8A7FD8 + unk_8A7F14 * unk_8A7FCA + unk_8A7F10 * unk_8A7FC6;
              v42 = unk_8A7F10 * unk_8A7FCC + unk_8A7FDC + unk_8A7F12 * unk_8A7FCE + unk_8A7F14 * unk_8A7FD0;
              v43 = -32768;
              goto LABEL_56;
            }
            if ( v26 != 4539410 )
              goto LABEL_630;
            v44 = unk_8A7F14;
            v77 = unk_8A7F12;
            v78 = unk_8A7F10;
            goto LABEL_285;
          }
          v95 = unk_8A7F12;
          v96 = unk_8A7F10;
          v97 = unk_8A7F14;
          v26 = unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0;
LABEL_304:
          v98 = v97 * unk_8A7FCA + v95 * unk_8A7FC8;
          v99 = v96 * unk_8A7FC6;
          goto LABEL_305;
        }
        if ( v26 <= (unsigned int)&MEMORY[0x484012] )
        {
          if ( (_UNKNOWN *)v26 == &MEMORY[0x484012] )
          {
            v26 = unk_8A7FD4
                + ((unk_8A7F04 * unk_8A7F84
                  + SHIWORD(unk_8A7F00[0]) * SHIWORD(unk_8A7F80[0])
                  + SLOWORD(unk_8A7F00[0]) * SLOWORD(unk_8A7F80[0])) >> 12);
            v40 = unk_8A7FD8
                + ((SHIWORD(unk_8A7F00[0]) * unk_8A7F88 + SLOWORD(unk_8A7F00[0]) * unk_8A7F86 + unk_8A7F04 * unk_8A7F8A) >> 12);
            v42 = unk_8A7FDC
                + ((unk_8A7F04 * unk_8A7F90 + SHIWORD(unk_8A7F00[0]) * unk_8A7F8E + SLOWORD(unk_8A7F00[0]) * unk_8A7F8C) >> 12);
            v43 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= (unsigned int)&MEMORY[0x480412] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x480412] )
            {
              if ( (_UNKNOWN *)v26 == &unk_45E012 )
              {
                v95 = (__int16)word_8A7F28;
                v96 = (__int16)word_8A7F24;
                v97 = (__int16)word_8A7F2C;
                v26 = (__int16)word_8A7F2C * unk_8A7FC4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F24 * unk_8A7FC0;
                goto LABEL_304;
              }
              if ( (_UNKNOWN *)v26 == &unk_45E412 )
              {
                v91 = (__int16)word_8A7F28;
                v92 = (__int16)word_8A7F24;
                v54 = (__int16)word_8A7F2C;
                v26 = (__int16)word_8A7F2C * unk_8A7FC4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F24 * unk_8A7FC0;
                goto LABEL_301;
              }
              if ( (_UNKNOWN *)v26 != &MEMORY[0x480012] )
                goto LABEL_630;
              v100 = SHIWORD(unk_8A7F00[0]);
              v101 = SLOWORD(unk_8A7F00[0]);
              v102 = unk_8A7F04;
              v103 = unk_8A7F04 * unk_8A7F84
                   + SHIWORD(unk_8A7F00[0]) * SHIWORD(unk_8A7F80[0])
                   + SLOWORD(unk_8A7F00[0]) * SLOWORD(unk_8A7F80[0]);
              goto LABEL_296;
            }
            v110 = unk_8A7F04;
            v111 = SHIWORD(unk_8A7F00[0]);
            v112 = SLOWORD(unk_8A7F00[0]);
LABEL_307:
            v26 = unk_8A7F94
                + ((v110 * unk_8A7F84 + v111 * SHIWORD(unk_8A7F80[0]) + v112 * SLOWORD(unk_8A7F80[0])) >> 12);
            v113 = v112 * unk_8A7F86 + v110 * unk_8A7F8A;
            v114 = v111 * unk_8A7F88;
LABEL_308:
            v64 = unk_8A7F98 + ((v114 + v113) >> 12);
            v115 = v112 * unk_8A7F8C;
            v116 = v111 * unk_8A7F8E;
            v117 = unk_8A7F90;
            goto LABEL_309;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x482012] )
          {
            v26 = unk_8A7FB4
                + ((unk_8A7F04 * unk_8A7F84
                  + SHIWORD(unk_8A7F00[0]) * SHIWORD(unk_8A7F80[0])
                  + SLOWORD(unk_8A7F00[0]) * SLOWORD(unk_8A7F80[0])) >> 12);
            v40 = unk_8A7FB8
                + ((SHIWORD(unk_8A7F00[0]) * unk_8A7F88 + SLOWORD(unk_8A7F00[0]) * unk_8A7F86 + unk_8A7F04 * unk_8A7F8A) >> 12);
            v42 = unk_8A7FBC
                + ((unk_8A7F04 * unk_8A7F90 + SHIWORD(unk_8A7F00[0]) * unk_8A7F8E + SLOWORD(unk_8A7F00[0]) * unk_8A7F8C) >> 12);
            v43 = -32768;
            goto LABEL_56;
          }
          if ( (_UNKNOWN *)v26 != &MEMORY[0x482412] )
            goto LABEL_630;
          v119 = unk_8A7F04;
          v120 = SHIWORD(unk_8A7F00[0]);
          v121 = SLOWORD(unk_8A7F00[0]);
          goto LABEL_313;
        }
        if ( v26 > (unsigned int)&MEMORY[0x488012] )
        {
          if ( (_UNKNOWN *)v26 != &MEMORY[0x488412] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x48A012] )
              goto LABEL_630;
            v102 = unk_8A7F0C;
            v26 = unk_8A7FB4
                + ((unk_8A7F0C * unk_8A7F84 + unk_8A7F0A * SHIWORD(unk_8A7F80[0]) + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12);
            v109 = unk_8A7FBC;
            v40 = unk_8A7FB8 + ((unk_8A7F0C * unk_8A7F8A + unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86) >> 12);
            v106 = unk_8A7F08 * unk_8A7F8C;
            v107 = unk_8A7F0A * unk_8A7F8E;
            v108 = unk_8A7F90;
            goto LABEL_299;
          }
          v111 = unk_8A7F0A;
          v112 = unk_8A7F08;
          v110 = unk_8A7F0C;
          v26 = unk_8A7F94
              + ((unk_8A7F0C * unk_8A7F84 + unk_8A7F0A * SHIWORD(unk_8A7F80[0]) + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12);
          v113 = unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86;
          v114 = unk_8A7F0C * unk_8A7F8A;
          goto LABEL_308;
        }
        if ( (_UNKNOWN *)v26 == &MEMORY[0x488012] )
        {
          v100 = unk_8A7F0A;
          v101 = unk_8A7F08;
          v102 = unk_8A7F0C;
          v26 = unk_8A7F94
              + ((unk_8A7F0C * unk_8A7F84 + unk_8A7F0A * SHIWORD(unk_8A7F80[0]) + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12);
          v104 = unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86;
          v105 = unk_8A7F0C * unk_8A7F8A;
          goto LABEL_297;
        }
        if ( (_UNKNOWN *)v26 != &MEMORY[0x484412] )
        {
          if ( (_UNKNOWN *)v26 != &MEMORY[0x486012] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x486412] )
              goto LABEL_630;
            v128 = unk_8A7F04;
            v129 = SHIWORD(unk_8A7F00[0]);
            v130 = SLOWORD(unk_8A7F00[0]);
LABEL_324:
            v131 = v130 * unk_8A7F86 + v128 * unk_8A7F8A;
            v26 = (v128 * unk_8A7F84 + v129 * SHIWORD(unk_8A7F80[0]) + v130 * SLOWORD(unk_8A7F80[0])) >> 12;
            v132 = v129 * unk_8A7F88;
LABEL_325:
            v64 = (v132 + v131) >> 12;
            v42 = (v128 * unk_8A7F90 + v129 * unk_8A7F8E + v130 * unk_8A7F8C) >> 12;
            goto LABEL_102;
          }
          v133 = unk_8A7F04;
          v134 = SHIWORD(unk_8A7F00[0]);
          v135 = SLOWORD(unk_8A7F00[0]);
          goto LABEL_327;
        }
        v142 = unk_8A7F04;
        v143 = SHIWORD(unk_8A7F00[0]);
        v144 = SLOWORD(unk_8A7F00[0]);
LABEL_331:
        v26 = unk_8A7FD4 + ((v142 * unk_8A7F84 + v143 * SHIWORD(unk_8A7F80[0]) + v144 * SLOWORD(unk_8A7F80[0])) >> 12);
        v145 = v144 * unk_8A7F86 + v142 * unk_8A7F8A;
        v146 = v143 * unk_8A7F88;
LABEL_332:
        v64 = unk_8A7FD8 + ((v146 + v145) >> 12);
        v147 = v144 * unk_8A7F8C;
        v148 = v143 * unk_8A7F8E;
        v149 = unk_8A7F90;
        goto LABEL_333;
      }
      if ( v26 <= (unsigned int)&MEMORY[0x4C4012] )
      {
        if ( (_UNKNOWN *)v26 != &MEMORY[0x4C4012] )
        {
          if ( v26 <= (unsigned int)&MEMORY[0x4A8012] )
          {
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4A8012] )
            {
              v102 = unk_8A7F0C;
              v26 = unk_8A7F94 + ((unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12);
              v40 = unk_8A7F98 + ((unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12);
              v106 = unk_8A7F08 * unk_8A7FAC;
              v107 = unk_8A7F0A * unk_8A7FAE;
              v108 = unk_8A7FB0;
              goto LABEL_298;
            }
            if ( v26 <= (unsigned int)&MEMORY[0x49A012] )
            {
              if ( (_UNKNOWN *)v26 == &MEMORY[0x49A012] )
              {
                v102 = (__int16)word_8A7F2C;
                v26 = unk_8A7FB4
                    + (((__int16)word_8A7F2C * unk_8A7F84
                      + (__int16)word_8A7F28 * SHIWORD(unk_8A7F80[0])
                      + (__int16)word_8A7F24 * SLOWORD(unk_8A7F80[0])) >> 12);
                v109 = unk_8A7FBC;
                v40 = unk_8A7FB8
                    + (((__int16)word_8A7F28 * unk_8A7F88
                      + (__int16)word_8A7F24 * unk_8A7F86
                      + (__int16)word_8A7F2C * unk_8A7F8A) >> 12);
                v106 = (__int16)word_8A7F24 * unk_8A7F8C;
                v107 = (__int16)word_8A7F28 * unk_8A7F8E;
                v108 = unk_8A7F90;
                goto LABEL_299;
              }
              if ( v26 > (unsigned int)&MEMORY[0x492412] )
              {
                if ( v26 > (unsigned int)&MEMORY[0x496412] )
                {
                  if ( (_UNKNOWN *)v26 == &MEMORY[0x498012] )
                  {
                    v100 = (__int16)word_8A7F28;
                    v101 = (__int16)word_8A7F24;
                    v102 = (__int16)word_8A7F2C;
                    v103 = (__int16)word_8A7F2C * unk_8A7F84
                         + (__int16)word_8A7F28 * SHIWORD(unk_8A7F80[0])
                         + (__int16)word_8A7F24 * SLOWORD(unk_8A7F80[0]);
LABEL_296:
                    v26 = unk_8A7F94 + (v103 >> 12);
                    v104 = v101 * unk_8A7F86 + v102 * unk_8A7F8A;
                    v105 = v100 * unk_8A7F88;
LABEL_297:
                    v40 = unk_8A7F98 + ((v105 + v104) >> 12);
                    v106 = v101 * unk_8A7F8C;
                    v107 = v100 * unk_8A7F8E;
                    v108 = unk_8A7F90;
LABEL_298:
                    v109 = unk_8A7F9C;
LABEL_299:
                    v42 = v109 + ((v102 * v108 + v107 + v106) >> 12);
                    v43 = -32768;
                    goto LABEL_56;
                  }
                  if ( (_UNKNOWN *)v26 != &MEMORY[0x498412] )
                    goto LABEL_630;
                  v110 = (__int16)word_8A7F2C;
                  v111 = (__int16)word_8A7F28;
                  v112 = (__int16)word_8A7F24;
                  goto LABEL_307;
                }
                if ( (_UNKNOWN *)v26 == &MEMORY[0x496412] )
                {
                  v129 = unk_8A7F12;
                  v130 = unk_8A7F10;
                  v128 = unk_8A7F14;
                  v131 = unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86;
                  v26 = (unk_8A7F14 * unk_8A7F84
                       + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                       + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12;
                  v132 = unk_8A7F14 * unk_8A7F8A;
                  goto LABEL_325;
                }
                if ( (_UNKNOWN *)v26 == &MEMORY[0x494012] )
                {
                  v102 = unk_8A7F14;
                  v26 = unk_8A7FD4
                      + ((unk_8A7F14 * unk_8A7F84
                        + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                        + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12);
                  v109 = unk_8A7FDC;
                  v40 = unk_8A7FD8
                      + ((unk_8A7F14 * unk_8A7F8A + unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86) >> 12);
                  v106 = unk_8A7F10 * unk_8A7F8C;
                  v107 = unk_8A7F12 * unk_8A7F8E;
                  v108 = unk_8A7F90;
                  goto LABEL_299;
                }
                if ( (_UNKNOWN *)v26 != &MEMORY[0x494412] )
                {
                  if ( (_UNKNOWN *)v26 != &MEMORY[0x496012] )
                    goto LABEL_630;
                  v134 = unk_8A7F12;
                  v135 = unk_8A7F10;
                  v133 = unk_8A7F14;
                  v136 = unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86;
                  v26 = (unk_8A7F14 * unk_8A7F84
                       + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                       + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12;
                  v137 = unk_8A7F14 * unk_8A7F8A;
                  goto LABEL_328;
                }
                v143 = unk_8A7F12;
                v144 = unk_8A7F10;
                v142 = unk_8A7F14;
                v26 = unk_8A7FD4
                    + ((unk_8A7F14 * unk_8A7F84
                      + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                      + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12);
                v145 = unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86;
                v146 = unk_8A7F14 * unk_8A7F8A;
              }
              else
              {
                if ( (_UNKNOWN *)v26 == &MEMORY[0x492412] )
                {
                  v120 = unk_8A7F12;
                  v121 = unk_8A7F10;
                  v119 = unk_8A7F14;
                  v26 = unk_8A7FB4
                      + ((unk_8A7F14 * unk_8A7F84
                        + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                        + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12);
                  v122 = unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86;
                  v123 = unk_8A7F14 * unk_8A7F8A;
                  goto LABEL_314;
                }
                if ( v26 > (unsigned int)&MEMORY[0x48E412] )
                {
                  if ( (_UNKNOWN *)v26 == &MEMORY[0x490012] )
                  {
                    v100 = unk_8A7F12;
                    v101 = unk_8A7F10;
                    v102 = unk_8A7F14;
                    v26 = unk_8A7F94
                        + ((unk_8A7F14 * unk_8A7F84
                          + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                          + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12);
                    v104 = unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86;
                    v105 = unk_8A7F14 * unk_8A7F8A;
                    goto LABEL_297;
                  }
                  if ( (_UNKNOWN *)v26 != &MEMORY[0x490412] )
                  {
                    if ( (_UNKNOWN *)v26 != &MEMORY[0x492012] )
                      goto LABEL_630;
                    v102 = unk_8A7F14;
                    v26 = unk_8A7FB4
                        + ((unk_8A7F14 * unk_8A7F84
                          + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                          + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12);
                    v109 = unk_8A7FBC;
                    v40 = unk_8A7FB8
                        + ((unk_8A7F14 * unk_8A7F8A + unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86) >> 12);
                    v106 = unk_8A7F10 * unk_8A7F8C;
                    v107 = unk_8A7F12 * unk_8A7F8E;
                    v108 = unk_8A7F90;
                    goto LABEL_299;
                  }
                  v111 = unk_8A7F12;
                  v112 = unk_8A7F10;
                  v110 = unk_8A7F14;
                  v26 = unk_8A7F94
                      + ((unk_8A7F14 * unk_8A7F84
                        + unk_8A7F12 * SHIWORD(unk_8A7F80[0])
                        + unk_8A7F10 * SLOWORD(unk_8A7F80[0])) >> 12);
                  v113 = unk_8A7F12 * unk_8A7F88 + unk_8A7F10 * unk_8A7F86;
                  v114 = unk_8A7F14 * unk_8A7F8A;
                  goto LABEL_308;
                }
                if ( (_UNKNOWN *)v26 == &MEMORY[0x48E412] )
                {
                  v129 = unk_8A7F0A;
                  v130 = unk_8A7F08;
                  v128 = unk_8A7F0C;
                  v131 = unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86;
                  v26 = (unk_8A7F0C * unk_8A7F84
                       + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                       + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12;
                  v132 = unk_8A7F0C * unk_8A7F8A;
                  goto LABEL_325;
                }
                if ( (_UNKNOWN *)v26 == &MEMORY[0x48C012] )
                {
                  v102 = unk_8A7F0C;
                  v26 = unk_8A7FD4
                      + ((unk_8A7F0C * unk_8A7F84
                        + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                        + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12);
                  v109 = unk_8A7FDC;
                  v40 = unk_8A7FD8
                      + ((unk_8A7F0C * unk_8A7F8A + unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86) >> 12);
                  v106 = unk_8A7F08 * unk_8A7F8C;
                  v107 = unk_8A7F0A * unk_8A7F8E;
                  v108 = unk_8A7F90;
                  goto LABEL_299;
                }
                if ( (_UNKNOWN *)v26 != &MEMORY[0x48C412] )
                {
                  if ( (_UNKNOWN *)v26 != &MEMORY[0x48E012] )
                    goto LABEL_630;
                  v134 = unk_8A7F0A;
                  v135 = unk_8A7F08;
                  v133 = unk_8A7F0C;
                  v136 = unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86;
                  v26 = (unk_8A7F0C * unk_8A7F84
                       + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                       + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12;
                  v137 = unk_8A7F0C * unk_8A7F8A;
                  goto LABEL_328;
                }
                v143 = unk_8A7F0A;
                v144 = unk_8A7F08;
                v142 = unk_8A7F0C;
                v26 = unk_8A7FD4
                    + ((unk_8A7F0C * unk_8A7F84
                      + unk_8A7F0A * SHIWORD(unk_8A7F80[0])
                      + unk_8A7F08 * SLOWORD(unk_8A7F80[0])) >> 12);
                v145 = unk_8A7F0A * unk_8A7F88 + unk_8A7F08 * unk_8A7F86;
                v146 = unk_8A7F0C * unk_8A7F8A;
              }
              goto LABEL_332;
            }
            if ( v26 <= (unsigned int)&MEMORY[0x4A0412] )
            {
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4A0412] )
              {
                v110 = unk_8A7F04;
                v26 = unk_8A7F94
                    + ((unk_8A7F04 * unk_8A7FA4
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12);
                v64 = unk_8A7F98
                    + ((unk_8A7F04 * unk_8A7FAA
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12);
                v115 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
                v116 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
                v117 = unk_8A7FB0;
                goto LABEL_309;
              }
              if ( v26 > (unsigned int)&MEMORY[0x49E012] )
              {
                if ( (_UNKNOWN *)v26 != &MEMORY[0x49E412] )
                {
                  if ( (_UNKNOWN *)v26 != &MEMORY[0x4A0012] )
                    goto LABEL_630;
                  v102 = unk_8A7F04;
                  v26 = unk_8A7F94
                      + ((unk_8A7F04 * unk_8A7FA4
                        + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                        + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12);
                  v40 = unk_8A7F98
                      + ((unk_8A7F04 * unk_8A7FAA
                        + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                        + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12);
                  v106 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
                  v107 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
                  v108 = unk_8A7FB0;
                  goto LABEL_298;
                }
                v128 = (__int16)word_8A7F2C;
                v129 = (__int16)word_8A7F28;
                v130 = (__int16)word_8A7F24;
                goto LABEL_324;
              }
              if ( (_UNKNOWN *)v26 == &MEMORY[0x49E012] )
              {
                v133 = (__int16)word_8A7F2C;
                v134 = (__int16)word_8A7F28;
                v135 = (__int16)word_8A7F24;
LABEL_327:
                v136 = v135 * unk_8A7F86 + v133 * unk_8A7F8A;
                v26 = (v133 * unk_8A7F84 + v134 * SHIWORD(unk_8A7F80[0]) + v135 * SLOWORD(unk_8A7F80[0])) >> 12;
                v137 = v134 * unk_8A7F88;
LABEL_328:
                v138 = v137 + v136;
                v139 = v135 * unk_8A7F8C;
                v140 = v134 * unk_8A7F8E;
                v141 = unk_8A7F90;
LABEL_329:
                v40 = v138 >> 12;
                v42 = (v133 * v141 + v140 + v139) >> 12;
                v43 = -32768;
                goto LABEL_56;
              }
              if ( (_UNKNOWN *)v26 == &MEMORY[0x49A412] )
              {
                v119 = (__int16)word_8A7F2C;
                v120 = (__int16)word_8A7F28;
                v121 = (__int16)word_8A7F24;
LABEL_313:
                v26 = unk_8A7FB4
                    + ((v119 * unk_8A7F84 + v120 * SHIWORD(unk_8A7F80[0]) + v121 * SLOWORD(unk_8A7F80[0])) >> 12);
                v122 = v121 * unk_8A7F86 + v119 * unk_8A7F8A;
                v123 = v120 * unk_8A7F88;
LABEL_314:
                v64 = unk_8A7FB8 + ((v123 + v122) >> 12);
                v124 = v121 * unk_8A7F8C;
                v125 = v120 * unk_8A7F8E;
                v126 = unk_8A7F90;
                goto LABEL_315;
              }
              if ( (_UNKNOWN *)v26 == &MEMORY[0x49C012] )
              {
                v102 = (__int16)word_8A7F2C;
                v26 = unk_8A7FD4
                    + (((__int16)word_8A7F2C * unk_8A7F84
                      + (__int16)word_8A7F28 * SHIWORD(unk_8A7F80[0])
                      + (__int16)word_8A7F24 * SLOWORD(unk_8A7F80[0])) >> 12);
                v109 = unk_8A7FDC;
                v40 = unk_8A7FD8
                    + (((__int16)word_8A7F28 * unk_8A7F88
                      + (__int16)word_8A7F24 * unk_8A7F86
                      + (__int16)word_8A7F2C * unk_8A7F8A) >> 12);
                v106 = (__int16)word_8A7F24 * unk_8A7F8C;
                v107 = (__int16)word_8A7F28 * unk_8A7F8E;
                v108 = unk_8A7F90;
                goto LABEL_299;
              }
              if ( (_UNKNOWN *)v26 != &MEMORY[0x49C412] )
                goto LABEL_630;
              v142 = (__int16)word_8A7F2C;
              v143 = (__int16)word_8A7F28;
              v144 = (__int16)word_8A7F24;
              goto LABEL_331;
            }
            if ( v26 <= (unsigned int)&MEMORY[0x4A4412] )
            {
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4A4412] )
              {
                v142 = unk_8A7F04;
                v26 = unk_8A7FD4
                    + ((unk_8A7F04 * unk_8A7FA4
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12);
                v64 = unk_8A7FD8
                    + ((unk_8A7F04 * unk_8A7FAA
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12);
                v147 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
                v148 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
                v149 = unk_8A7FB0;
                goto LABEL_333;
              }
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4A2012] )
              {
                v102 = unk_8A7F04;
                v26 = unk_8A7FB4
                    + ((unk_8A7F04 * unk_8A7FA4
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12);
                v109 = unk_8A7FBC;
                v40 = unk_8A7FB8
                    + ((unk_8A7F04 * unk_8A7FAA
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12);
                v106 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
                v107 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
                v108 = unk_8A7FB0;
                goto LABEL_299;
              }
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4A2412] )
              {
                if ( (_UNKNOWN *)v26 != &MEMORY[0x4A4012] )
                  goto LABEL_630;
                v102 = unk_8A7F04;
                v26 = unk_8A7FD4
                    + ((unk_8A7F04 * unk_8A7FA4
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12);
                v109 = unk_8A7FDC;
                v40 = unk_8A7FD8
                    + ((unk_8A7F04 * unk_8A7FAA
                      + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                      + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12);
                v106 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
                v107 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
                v108 = unk_8A7FB0;
                goto LABEL_299;
              }
              v119 = unk_8A7F04;
              v26 = unk_8A7FB4
                  + ((unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2
                                              + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12);
              v64 = unk_8A7FB8
                  + ((unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8
                                              + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12);
              v124 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
              v125 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
              v126 = unk_8A7FB0;
LABEL_315:
              v127 = v119 * v126 + v125 + v124;
              v69 = unk_8A7FBC;
              v68 = v127 >> 12;
              goto LABEL_101;
            }
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4A6012] )
            {
              v133 = unk_8A7F04;
              v138 = unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6;
              v139 = SLOWORD(unk_8A7F00[0]) * unk_8A7FAC;
              v26 = (unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12;
              v140 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
              v141 = unk_8A7FB0;
              goto LABEL_329;
            }
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4A6412] )
              goto LABEL_630;
            v26 = (unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12;
            v64 = (unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12;
            v42 = (unk_8A7F04 * unk_8A7FB0 + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE + SLOWORD(unk_8A7F00[0]) * unk_8A7FAC) >> 12;
LABEL_102:
            unk_8A7F64 = v26;
            unk_8A7F68 = v64;
            unk_8A7F6C = v42;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                word_8A7F24 = v26;
              }
              else
              {
                unk_8A7FFC = -2130706432;
                word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC = -2130706432;
              word_8A7F24 = 0;
            }
            if ( v64 >= 0 )
            {
              if ( v64 <= 0x7FFF )
              {
                word_8A7F28 = v64;
              }
              else
              {
                unk_8A7FFC |= 0x80800000;
                word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x80800000;
              word_8A7F28 = 0;
            }
            if ( v42 >= 0 )
              goto LABEL_541;
LABEL_573:
            LOBYTE(v26) = unk_8A7FFC;
            word_8A7F2C = 0;
            unk_8A7FFC |= 0x400000u;
            return v26;
          }
          if ( v26 <= (unsigned int)&MEMORY[0x4B6012] )
          {
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4B6012] )
            {
              v133 = unk_8A7F14;
              v138 = unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6;
              v139 = unk_8A7F10 * unk_8A7FAC;
              v26 = (unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12;
              v140 = unk_8A7F12 * unk_8A7FAE;
              v141 = unk_8A7FB0;
              goto LABEL_329;
            }
            if ( v26 <= (unsigned int)&MEMORY[0x4AE412] )
            {
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4AE412] )
              {
                v26 = (unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12;
                v64 = (unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12;
                v42 = (unk_8A7F0C * unk_8A7FB0 + unk_8A7F0A * unk_8A7FAE + unk_8A7F08 * unk_8A7FAC) >> 12;
                goto LABEL_102;
              }
              if ( v26 <= (unsigned int)&MEMORY[0x4AC012] )
              {
                if ( (_UNKNOWN *)v26 == &MEMORY[0x4AC012] )
                {
                  v102 = unk_8A7F0C;
                  v26 = unk_8A7FD4
                      + ((unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12);
                  v109 = unk_8A7FDC;
                  v40 = unk_8A7FD8
                      + ((unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12);
                  v106 = unk_8A7F08 * unk_8A7FAC;
                  v107 = unk_8A7F0A * unk_8A7FAE;
                  v108 = unk_8A7FB0;
                  goto LABEL_299;
                }
                if ( (_UNKNOWN *)v26 == &MEMORY[0x4A8412] )
                {
                  v110 = unk_8A7F0C;
                  v26 = unk_8A7F94
                      + ((unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12);
                  v64 = unk_8A7F98
                      + ((unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12);
                  v115 = unk_8A7F08 * unk_8A7FAC;
                  v116 = unk_8A7F0A * unk_8A7FAE;
                  v117 = unk_8A7FB0;
                  goto LABEL_309;
                }
                if ( (_UNKNOWN *)v26 == &MEMORY[0x4AA012] )
                {
                  v102 = unk_8A7F0C;
                  v26 = unk_8A7FB4
                      + ((unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12);
                  v109 = unk_8A7FBC;
                  v40 = unk_8A7FB8
                      + ((unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12);
                  v106 = unk_8A7F08 * unk_8A7FAC;
                  v107 = unk_8A7F0A * unk_8A7FAE;
                  v108 = unk_8A7FB0;
                  goto LABEL_299;
                }
                if ( (_UNKNOWN *)v26 != &MEMORY[0x4AA412] )
                  goto LABEL_630;
                v119 = unk_8A7F0C;
                v26 = unk_8A7FB4 + ((unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12);
                v64 = unk_8A7FB8 + ((unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12);
                v124 = unk_8A7F08 * unk_8A7FAC;
                v125 = unk_8A7F0A * unk_8A7FAE;
                v126 = unk_8A7FB0;
                goto LABEL_315;
              }
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4AC412] )
              {
                if ( (_UNKNOWN *)v26 != &MEMORY[0x4AE012] )
                  goto LABEL_630;
                v133 = unk_8A7F0C;
                v138 = unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6;
                v139 = unk_8A7F08 * unk_8A7FAC;
                v26 = (unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12;
                v140 = unk_8A7F0A * unk_8A7FAE;
                v141 = unk_8A7FB0;
                goto LABEL_329;
              }
              v142 = unk_8A7F0C;
              v26 = unk_8A7FD4 + ((unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12);
              v64 = unk_8A7FD8 + ((unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12);
              v147 = unk_8A7F08 * unk_8A7FAC;
              v148 = unk_8A7F0A * unk_8A7FAE;
              v149 = unk_8A7FB0;
LABEL_333:
              v150 = v142 * v149 + v148 + v147;
              v69 = unk_8A7FDC;
              v68 = v150 >> 12;
              goto LABEL_101;
            }
            if ( v26 > (unsigned int)&MEMORY[0x4B2412] )
            {
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4B4012] )
              {
                v102 = unk_8A7F14;
                v26 = unk_8A7FD4 + ((unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12);
                v109 = unk_8A7FDC;
                v40 = unk_8A7FD8 + ((unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12);
                v106 = unk_8A7F10 * unk_8A7FAC;
                v107 = unk_8A7F12 * unk_8A7FAE;
                v108 = unk_8A7FB0;
                goto LABEL_299;
              }
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4B4412] )
                goto LABEL_630;
              v142 = unk_8A7F14;
              v26 = unk_8A7FD4 + ((unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12);
              v64 = unk_8A7FD8 + ((unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12);
              v147 = unk_8A7F10 * unk_8A7FAC;
              v148 = unk_8A7F12 * unk_8A7FAE;
              v149 = unk_8A7FB0;
              goto LABEL_333;
            }
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4B2412] )
            {
              v119 = unk_8A7F14;
              v26 = unk_8A7FB4 + ((unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12);
              v64 = unk_8A7FB8 + ((unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12);
              v124 = unk_8A7F10 * unk_8A7FAC;
              v125 = unk_8A7F12 * unk_8A7FAE;
              v126 = unk_8A7FB0;
              goto LABEL_315;
            }
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4B0012] )
            {
              v102 = unk_8A7F14;
              v26 = unk_8A7F94 + ((unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12);
              v40 = unk_8A7F98 + ((unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12);
              v106 = unk_8A7F10 * unk_8A7FAC;
              v107 = unk_8A7F12 * unk_8A7FAE;
              v108 = unk_8A7FB0;
              goto LABEL_298;
            }
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4B0412] )
            {
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4B2012] )
                goto LABEL_630;
              v102 = unk_8A7F14;
              v26 = unk_8A7FB4 + ((unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12);
              v109 = unk_8A7FBC;
              v40 = unk_8A7FB8 + ((unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12);
              v106 = unk_8A7F10 * unk_8A7FAC;
              v107 = unk_8A7F12 * unk_8A7FAE;
              v108 = unk_8A7FB0;
              goto LABEL_299;
            }
            v110 = unk_8A7F14;
            v26 = unk_8A7F94 + ((unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12);
            v64 = unk_8A7F98 + ((unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12);
            v115 = unk_8A7F10 * unk_8A7FAC;
            v116 = unk_8A7F12 * unk_8A7FAE;
            v117 = unk_8A7FB0;
LABEL_309:
            v118 = v110 * v117 + v116 + v115;
            v69 = unk_8A7F9C;
            v68 = v118 >> 12;
            goto LABEL_101;
          }
          if ( v26 <= (unsigned int)&MEMORY[0x4BC412] )
          {
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4BC412] )
            {
              v142 = (__int16)word_8A7F2C;
              v26 = unk_8A7FD4
                  + (((__int16)word_8A7F2C * unk_8A7FA4
                    + (__int16)word_8A7F28 * unk_8A7FA2
                    + (__int16)word_8A7F24 * unk_8A7FA0) >> 12);
              v64 = unk_8A7FD8
                  + (((__int16)word_8A7F2C * unk_8A7FAA
                    + (__int16)word_8A7F28 * unk_8A7FA8
                    + (__int16)word_8A7F24 * unk_8A7FA6) >> 12);
              v147 = (__int16)word_8A7F24 * unk_8A7FAC;
              v148 = (__int16)word_8A7F28 * unk_8A7FAE;
              v149 = unk_8A7FB0;
              goto LABEL_333;
            }
            if ( v26 > (unsigned int)&MEMORY[0x4BA012] )
            {
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4BA412] )
              {
                if ( (_UNKNOWN *)v26 != &MEMORY[0x4BC012] )
                  goto LABEL_630;
                v102 = (__int16)word_8A7F2C;
                v26 = unk_8A7FD4
                    + (((__int16)word_8A7F2C * unk_8A7FA4
                      + (__int16)word_8A7F28 * unk_8A7FA2
                      + (__int16)word_8A7F24 * unk_8A7FA0) >> 12);
                v109 = unk_8A7FDC;
                v40 = unk_8A7FD8
                    + (((__int16)word_8A7F2C * unk_8A7FAA
                      + (__int16)word_8A7F28 * unk_8A7FA8
                      + (__int16)word_8A7F24 * unk_8A7FA6) >> 12);
                v106 = (__int16)word_8A7F24 * unk_8A7FAC;
                v107 = (__int16)word_8A7F28 * unk_8A7FAE;
                v108 = unk_8A7FB0;
                goto LABEL_299;
              }
              v119 = (__int16)word_8A7F2C;
              v26 = unk_8A7FB4
                  + (((__int16)word_8A7F2C * unk_8A7FA4
                    + (__int16)word_8A7F28 * unk_8A7FA2
                    + (__int16)word_8A7F24 * unk_8A7FA0) >> 12);
              v64 = unk_8A7FB8
                  + (((__int16)word_8A7F2C * unk_8A7FAA
                    + (__int16)word_8A7F28 * unk_8A7FA8
                    + (__int16)word_8A7F24 * unk_8A7FA6) >> 12);
              v124 = (__int16)word_8A7F24 * unk_8A7FAC;
              v125 = (__int16)word_8A7F28 * unk_8A7FAE;
              v126 = unk_8A7FB0;
              goto LABEL_315;
            }
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4BA012] )
            {
              v102 = (__int16)word_8A7F2C;
              v26 = unk_8A7FB4
                  + (((__int16)word_8A7F2C * unk_8A7FA4
                    + (__int16)word_8A7F28 * unk_8A7FA2
                    + (__int16)word_8A7F24 * unk_8A7FA0) >> 12);
              v109 = unk_8A7FBC;
              v40 = unk_8A7FB8
                  + (((__int16)word_8A7F2C * unk_8A7FAA
                    + (__int16)word_8A7F28 * unk_8A7FA8
                    + (__int16)word_8A7F24 * unk_8A7FA6) >> 12);
              v106 = (__int16)word_8A7F24 * unk_8A7FAC;
              v107 = (__int16)word_8A7F28 * unk_8A7FAE;
              v108 = unk_8A7FB0;
              goto LABEL_299;
            }
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4B6412] )
            {
              v26 = (unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12;
              v64 = (unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12;
              v42 = (unk_8A7F14 * unk_8A7FB0 + unk_8A7F12 * unk_8A7FAE + unk_8A7F10 * unk_8A7FAC) >> 12;
              goto LABEL_102;
            }
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4B8012] )
            {
              v102 = (__int16)word_8A7F2C;
              v26 = unk_8A7F94
                  + (((__int16)word_8A7F2C * unk_8A7FA4
                    + (__int16)word_8A7F28 * unk_8A7FA2
                    + (__int16)word_8A7F24 * unk_8A7FA0) >> 12);
              v40 = unk_8A7F98
                  + (((__int16)word_8A7F2C * unk_8A7FAA
                    + (__int16)word_8A7F28 * unk_8A7FA8
                    + (__int16)word_8A7F24 * unk_8A7FA6) >> 12);
              v106 = (__int16)word_8A7F24 * unk_8A7FAC;
              v107 = (__int16)word_8A7F28 * unk_8A7FAE;
              v108 = unk_8A7FB0;
              goto LABEL_298;
            }
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4B8412] )
              goto LABEL_630;
            v110 = (__int16)word_8A7F2C;
            v26 = unk_8A7F94
                + (((__int16)word_8A7F2C * unk_8A7FA4
                  + (__int16)word_8A7F28 * unk_8A7FA2
                  + (__int16)word_8A7F24 * unk_8A7FA0) >> 12);
            v64 = unk_8A7F98
                + (((__int16)word_8A7F2C * unk_8A7FAA
                  + (__int16)word_8A7F28 * unk_8A7FA8
                  + (__int16)word_8A7F24 * unk_8A7FA6) >> 12);
            v115 = (__int16)word_8A7F24 * unk_8A7FAC;
            v116 = (__int16)word_8A7F28 * unk_8A7FAE;
            v117 = unk_8A7FB0;
            goto LABEL_309;
          }
          if ( v26 <= (unsigned int)&MEMORY[0x4C0412] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4C0412] )
            {
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4BE012] )
              {
                v133 = (__int16)word_8A7F2C;
                v138 = (__int16)word_8A7F2C * unk_8A7FAA
                     + (__int16)word_8A7F28 * unk_8A7FA8
                     + (__int16)word_8A7F24 * unk_8A7FA6;
                v139 = (__int16)word_8A7F24 * unk_8A7FAC;
                v26 = ((__int16)word_8A7F2C * unk_8A7FA4
                     + (__int16)word_8A7F28 * unk_8A7FA2
                     + (__int16)word_8A7F24 * unk_8A7FA0) >> 12;
                v140 = (__int16)word_8A7F28 * unk_8A7FAE;
                v141 = unk_8A7FB0;
                goto LABEL_329;
              }
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4BE412] )
              {
                v26 = ((__int16)word_8A7F2C * unk_8A7FA4
                     + (__int16)word_8A7F28 * unk_8A7FA2
                     + (__int16)word_8A7F24 * unk_8A7FA0) >> 12;
                v64 = ((__int16)word_8A7F2C * unk_8A7FAA
                     + (__int16)word_8A7F28 * unk_8A7FA8
                     + (__int16)word_8A7F24 * unk_8A7FA6) >> 12;
                v42 = ((__int16)word_8A7F2C * unk_8A7FB0
                     + (__int16)word_8A7F28 * unk_8A7FAE
                     + (__int16)word_8A7F24 * unk_8A7FAC) >> 12;
                goto LABEL_102;
              }
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4C0012] )
                goto LABEL_630;
              v151 = SHIWORD(unk_8A7F00[0]);
              v152 = SLOWORD(unk_8A7F00[0]);
              v102 = unk_8A7F04;
              v26 = unk_8A7F94
                  + ((unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                                              + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12);
              v153 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
              v154 = unk_8A7F04 * unk_8A7FCA;
LABEL_528:
              v40 = unk_8A7F98 + ((v154 + v153) >> 12);
              v106 = v152 * unk_8A7FCC;
              v107 = v151 * unk_8A7FCE;
              v108 = unk_8A7FD0;
              goto LABEL_298;
            }
            v155 = SHIWORD(unk_8A7F00[0]);
            v156 = SLOWORD(unk_8A7F00[0]);
            v110 = unk_8A7F04;
            v26 = unk_8A7F94
                + ((unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12);
            v157 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
            v158 = unk_8A7F04 * unk_8A7FCA;
            goto LABEL_526;
          }
          if ( (_UNKNOWN *)v26 != &MEMORY[0x4C2012] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4C2412] )
              goto LABEL_630;
            v159 = SHIWORD(unk_8A7F00[0]);
            v160 = SLOWORD(unk_8A7F00[0]);
            v119 = unk_8A7F04;
            v26 = unk_8A7FB4
                + ((unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12);
            v161 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
            v162 = unk_8A7F04 * unk_8A7FCA;
            goto LABEL_506;
          }
          v163 = SHIWORD(unk_8A7F00[0]);
          v164 = SLOWORD(unk_8A7F00[0]);
          v102 = unk_8A7F04;
          v26 = unk_8A7FB4
              + ((unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12);
          v165 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
          v166 = unk_8A7F04 * unk_8A7FCA;
LABEL_530:
          v109 = unk_8A7FBC;
          v40 = unk_8A7FB8 + ((v166 + v165) >> 12);
          v106 = v164 * unk_8A7FCC;
          v107 = v163 * unk_8A7FCE;
          v108 = unk_8A7FD0;
          goto LABEL_299;
        }
        v167 = SHIWORD(unk_8A7F00[0]);
        v168 = SLOWORD(unk_8A7F00[0]);
        v102 = unk_8A7F04;
        v26 = unk_8A7FD4
            + ((unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12);
        v169 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
        v170 = unk_8A7F04 * unk_8A7FCA;
LABEL_519:
        v109 = unk_8A7FDC;
        v40 = unk_8A7FD8 + ((v170 + v169) >> 12);
        v106 = v168 * unk_8A7FCC;
        v107 = v167 * unk_8A7FCE;
        v108 = unk_8A7FD0;
        goto LABEL_299;
      }
      if ( v26 <= (unsigned int)&MEMORY[0x680029] )
      {
        if ( (_UNKNOWN *)v26 == &MEMORY[0x680029] )
        {
          LOBYTE(v26) = sub_410420();
          return v26;
        }
        if ( v26 <= (unsigned int)&MEMORY[0x4D2412] )
        {
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4D2412] )
          {
            v159 = unk_8A7F12;
            v160 = unk_8A7F10;
            v119 = unk_8A7F14;
            v26 = unk_8A7FB4 + ((unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0) >> 12);
            v161 = unk_8A7F14 * unk_8A7FCA + unk_8A7F12 * unk_8A7FC8;
            v162 = unk_8A7F10 * unk_8A7FC6;
LABEL_506:
            v64 = unk_8A7FB8 + ((v162 + v161) >> 12);
            v124 = v160 * unk_8A7FCC;
            v125 = v159 * unk_8A7FCE;
            v126 = unk_8A7FD0;
            goto LABEL_315;
          }
          if ( v26 <= (unsigned int)&MEMORY[0x4CC012] )
          {
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4CC012] )
            {
              v102 = unk_8A7F0C;
              v26 = unk_8A7FD4 + ((unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0) >> 12);
              v109 = unk_8A7FDC;
              v40 = unk_8A7FD8 + ((unk_8A7F08 * unk_8A7FC6 + unk_8A7F0C * unk_8A7FCA + unk_8A7F0A * unk_8A7FC8) >> 12);
              v106 = unk_8A7F08 * unk_8A7FCC;
              v107 = unk_8A7F0A * unk_8A7FCE;
              v108 = unk_8A7FD0;
              goto LABEL_299;
            }
            if ( v26 > (unsigned int)&MEMORY[0x4C8012] )
            {
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4C8412] )
              {
                v110 = unk_8A7F0C;
                v26 = unk_8A7F94 + ((unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0) >> 12);
                v64 = unk_8A7F98 + ((unk_8A7F08 * unk_8A7FC6 + unk_8A7F0C * unk_8A7FCA + unk_8A7F0A * unk_8A7FC8) >> 12);
                v115 = unk_8A7F08 * unk_8A7FCC;
                v116 = unk_8A7F0A * unk_8A7FCE;
                v117 = unk_8A7FD0;
                goto LABEL_309;
              }
              if ( (_UNKNOWN *)v26 == &MEMORY[0x4CA012] )
              {
                v102 = unk_8A7F0C;
                v26 = unk_8A7FB4 + ((unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0) >> 12);
                v109 = unk_8A7FBC;
                v40 = unk_8A7FB8 + ((unk_8A7F08 * unk_8A7FC6 + unk_8A7F0C * unk_8A7FCA + unk_8A7F0A * unk_8A7FC8) >> 12);
                v106 = unk_8A7F08 * unk_8A7FCC;
                v107 = unk_8A7F0A * unk_8A7FCE;
                v108 = unk_8A7FD0;
                goto LABEL_299;
              }
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4CA412] )
                goto LABEL_630;
              v119 = unk_8A7F0C;
              v26 = unk_8A7FB4 + ((unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0) >> 12);
              v64 = unk_8A7FB8 + ((unk_8A7F08 * unk_8A7FC6 + unk_8A7F0C * unk_8A7FCA + unk_8A7F0A * unk_8A7FC8) >> 12);
              v124 = unk_8A7F08 * unk_8A7FCC;
              v125 = unk_8A7F0A * unk_8A7FCE;
              v126 = unk_8A7FD0;
              goto LABEL_315;
            }
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4C8012] )
            {
              v102 = unk_8A7F0C;
              v26 = unk_8A7F94 + ((unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0) >> 12);
              v40 = unk_8A7F98 + ((unk_8A7F08 * unk_8A7FC6 + unk_8A7F0C * unk_8A7FCA + unk_8A7F0A * unk_8A7FC8) >> 12);
              v106 = unk_8A7F08 * unk_8A7FCC;
              v107 = unk_8A7F0A * unk_8A7FCE;
              v108 = unk_8A7FD0;
              goto LABEL_298;
            }
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4C4412] )
            {
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4C6012] )
              {
                if ( (_UNKNOWN *)v26 != &MEMORY[0x4C6412] )
                  goto LABEL_630;
                v171 = SHIWORD(unk_8A7F00[0]);
                v172 = SLOWORD(unk_8A7F00[0]);
                v173 = unk_8A7F04;
                v174 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
                v26 = (unk_8A7F04 * unk_8A7FC4
                     + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2
                     + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12;
                v175 = unk_8A7F04 * unk_8A7FCA;
                goto LABEL_522;
              }
              v176 = SHIWORD(unk_8A7F00[0]);
              v177 = SLOWORD(unk_8A7F00[0]);
              v133 = unk_8A7F04;
              v178 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
              v26 = (unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12;
              v179 = unk_8A7F04 * unk_8A7FCA;
LABEL_516:
              v138 = v179 + v178;
              v139 = v177 * unk_8A7FCC;
              v140 = v176 * unk_8A7FCE;
              v141 = unk_8A7FD0;
              goto LABEL_329;
            }
            v180 = SHIWORD(unk_8A7F00[0]);
            v181 = SLOWORD(unk_8A7F00[0]);
            v142 = unk_8A7F04;
            v26 = unk_8A7FD4
                + ((unk_8A7F04 * unk_8A7FC4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FC2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC0) >> 12);
            v182 = SHIWORD(unk_8A7F00[0]) * unk_8A7FC8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FC6;
            v183 = unk_8A7F04 * unk_8A7FCA;
LABEL_537:
            v64 = unk_8A7FD8 + ((v183 + v182) >> 12);
            v147 = v181 * unk_8A7FCC;
            v148 = v180 * unk_8A7FCE;
            v149 = unk_8A7FD0;
            goto LABEL_333;
          }
          if ( v26 > (unsigned int)&MEMORY[0x4D0012] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4D0412] )
            {
              if ( (_UNKNOWN *)v26 != &MEMORY[0x4D2012] )
                goto LABEL_630;
              v102 = unk_8A7F14;
              v26 = unk_8A7FB4 + ((unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0) >> 12);
              v109 = unk_8A7FBC;
              v40 = unk_8A7FB8 + ((unk_8A7F10 * unk_8A7FC6 + unk_8A7F14 * unk_8A7FCA + unk_8A7F12 * unk_8A7FC8) >> 12);
              v106 = unk_8A7F10 * unk_8A7FCC;
              v107 = unk_8A7F12 * unk_8A7FCE;
              v108 = unk_8A7FD0;
              goto LABEL_299;
            }
            v110 = unk_8A7F14;
            v26 = unk_8A7F94 + ((unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0) >> 12);
            v64 = unk_8A7F98 + ((unk_8A7F10 * unk_8A7FC6 + unk_8A7F14 * unk_8A7FCA + unk_8A7F12 * unk_8A7FC8) >> 12);
            v115 = unk_8A7F10 * unk_8A7FCC;
            v116 = unk_8A7F12 * unk_8A7FCE;
            v117 = unk_8A7FD0;
            goto LABEL_309;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4D0012] )
          {
            v102 = unk_8A7F14;
            v26 = unk_8A7F94 + ((unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0) >> 12);
            v40 = unk_8A7F98 + ((unk_8A7F10 * unk_8A7FC6 + unk_8A7F14 * unk_8A7FCA + unk_8A7F12 * unk_8A7FC8) >> 12);
            v106 = unk_8A7F10 * unk_8A7FCC;
            v107 = unk_8A7F12 * unk_8A7FCE;
            v108 = unk_8A7FD0;
            goto LABEL_298;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4CC412] )
          {
            v142 = unk_8A7F0C;
            v26 = unk_8A7FD4 + ((unk_8A7F0C * unk_8A7FC4 + unk_8A7F0A * unk_8A7FC2 + unk_8A7F08 * unk_8A7FC0) >> 12);
            v64 = unk_8A7FD8 + ((unk_8A7F08 * unk_8A7FC6 + unk_8A7F0C * unk_8A7FCA + unk_8A7F0A * unk_8A7FC8) >> 12);
            v147 = unk_8A7F08 * unk_8A7FCC;
            v148 = unk_8A7F0A * unk_8A7FCE;
            v149 = unk_8A7FD0;
            goto LABEL_333;
          }
          if ( (_UNKNOWN *)v26 != &MEMORY[0x4CE012] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4CE412] )
              goto LABEL_630;
            v173 = unk_8A7F0C;
            v171 = unk_8A7F0A;
            v172 = unk_8A7F08;
            goto LABEL_521;
          }
          v133 = unk_8A7F0C;
          v176 = unk_8A7F0A;
          v177 = unk_8A7F08;
          goto LABEL_515;
        }
        if ( v26 <= (unsigned int)&MEMORY[0x4DA012] )
        {
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4DA012] )
          {
            v163 = (__int16)word_8A7F28;
            v164 = (__int16)word_8A7F24;
            v102 = (__int16)word_8A7F2C;
            v26 = unk_8A7FB4
                + (((__int16)word_8A7F2C * unk_8A7FC4
                  + (__int16)word_8A7F28 * unk_8A7FC2
                  + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
            v165 = (__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8;
            v166 = (__int16)word_8A7F24 * unk_8A7FC6;
            goto LABEL_530;
          }
          if ( v26 > (unsigned int)&MEMORY[0x4D6412] )
          {
            if ( (_UNKNOWN *)v26 == &MEMORY[0x4D8012] )
            {
              v151 = (__int16)word_8A7F28;
              v152 = (__int16)word_8A7F24;
              v102 = (__int16)word_8A7F2C;
              v26 = unk_8A7F94
                  + (((__int16)word_8A7F2C * unk_8A7FC4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
              v153 = (__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8;
              v154 = (__int16)word_8A7F24 * unk_8A7FC6;
              goto LABEL_528;
            }
            if ( (_UNKNOWN *)v26 != &MEMORY[0x4D8412] )
              goto LABEL_630;
            v155 = (__int16)word_8A7F28;
            v156 = (__int16)word_8A7F24;
            v110 = (__int16)word_8A7F2C;
            v26 = unk_8A7F94
                + (((__int16)word_8A7F2C * unk_8A7FC4
                  + (__int16)word_8A7F28 * unk_8A7FC2
                  + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
            v157 = (__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8;
            v158 = (__int16)word_8A7F24 * unk_8A7FC6;
LABEL_526:
            v64 = unk_8A7F98 + ((v158 + v157) >> 12);
            v115 = v156 * unk_8A7FCC;
            v116 = v155 * unk_8A7FCE;
            v117 = unk_8A7FD0;
            goto LABEL_309;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4D6412] )
          {
            v173 = unk_8A7F14;
            v171 = unk_8A7F12;
            v172 = unk_8A7F10;
LABEL_521:
            v174 = v173 * unk_8A7FCA + v171 * unk_8A7FC8;
            v26 = (v173 * unk_8A7FC4 + v171 * unk_8A7FC2 + v172 * unk_8A7FC0) >> 12;
            v175 = v172 * unk_8A7FC6;
LABEL_522:
            v64 = (v175 + v174) >> 12;
            v42 = (v173 * unk_8A7FD0 + v171 * unk_8A7FCE + v172 * unk_8A7FCC) >> 12;
            goto LABEL_102;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4D4012] )
          {
            v167 = unk_8A7F12;
            v168 = unk_8A7F10;
            v102 = unk_8A7F14;
            v26 = unk_8A7FD4 + ((unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0) >> 12);
            v169 = unk_8A7F14 * unk_8A7FCA + unk_8A7F12 * unk_8A7FC8;
            v170 = unk_8A7F10 * unk_8A7FC6;
            goto LABEL_519;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4D4412] )
          {
            v142 = unk_8A7F14;
            v26 = unk_8A7FD4 + ((unk_8A7F14 * unk_8A7FC4 + unk_8A7F12 * unk_8A7FC2 + unk_8A7F10 * unk_8A7FC0) >> 12);
            v64 = unk_8A7FD8 + ((unk_8A7F10 * unk_8A7FC6 + unk_8A7F14 * unk_8A7FCA + unk_8A7F12 * unk_8A7FC8) >> 12);
            v147 = unk_8A7F10 * unk_8A7FCC;
            v148 = unk_8A7F12 * unk_8A7FCE;
            v149 = unk_8A7FD0;
            goto LABEL_333;
          }
          if ( (_UNKNOWN *)v26 != &MEMORY[0x4D6012] )
            goto LABEL_630;
          v133 = unk_8A7F14;
          v176 = unk_8A7F12;
          v177 = unk_8A7F10;
LABEL_515:
          v178 = v133 * unk_8A7FCA + v176 * unk_8A7FC8;
          v26 = (v133 * unk_8A7FC4 + v176 * unk_8A7FC2 + v177 * unk_8A7FC0) >> 12;
          v179 = v177 * unk_8A7FC6;
          goto LABEL_516;
        }
        if ( v26 <= (unsigned int)&MEMORY[0x4DE012] )
        {
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4DE012] )
          {
            v26 = ((__int16)word_8A7F2C * unk_8A7FC4
                 + (__int16)word_8A7F28 * unk_8A7FC2
                 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12;
            v184 = ((__int16)word_8A7F24 * unk_8A7FC6
                  + (__int16)word_8A7F2C * unk_8A7FCA
                  + (__int16)word_8A7F28 * unk_8A7FC8) >> 12;
            v42 = ((__int16)word_8A7F2C * unk_8A7FD0
                 + (__int16)word_8A7F28 * unk_8A7FCE
                 + (__int16)word_8A7F24 * unk_8A7FCC) >> 12;
            v43 = -32768;
            unk_8A7F64 = v26;
            unk_8A7F68 = v184;
            unk_8A7F6C = v42;
            if ( (int)v26 >= -32768 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                word_8A7F24 = ((__int16)word_8A7F2C * unk_8A7FC4
                             + (__int16)word_8A7F28 * unk_8A7FC2
                             + (__int16)word_8A7F24 * unk_8A7FC0) >> 12;
              }
              else
              {
                unk_8A7FFC = -2130706432;
                word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC = -2130706432;
              word_8A7F24 = -32768;
            }
            if ( v184 >= -32768 )
            {
              if ( v184 <= 0x7FFF )
              {
                word_8A7F28 = v184;
              }
              else
              {
                unk_8A7FFC |= 0x80800000;
                word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x80800000;
              word_8A7F28 = -32768;
            }
            if ( v42 >= -32768 )
              goto LABEL_541;
            goto LABEL_558;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4DA412] )
          {
            v26 = unk_8A7FB4
                + (((__int16)word_8A7F2C * unk_8A7FC4
                  + (__int16)word_8A7F28 * unk_8A7FC2
                  + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
            v64 = unk_8A7FB8
                + (((__int16)word_8A7F24 * unk_8A7FC6
                  + (__int16)word_8A7F2C * unk_8A7FCA
                  + (__int16)word_8A7F28 * unk_8A7FC8) >> 12);
            v69 = unk_8A7FBC;
            v68 = ((__int16)word_8A7F2C * unk_8A7FD0
                 + (__int16)word_8A7F28 * unk_8A7FCE
                 + (__int16)word_8A7F24 * unk_8A7FCC) >> 12;
            goto LABEL_101;
          }
          if ( (_UNKNOWN *)v26 == &MEMORY[0x4DC012] )
          {
            v26 = unk_8A7FD4
                + (((__int16)word_8A7F2C * unk_8A7FC4
                  + (__int16)word_8A7F28 * unk_8A7FC2
                  + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
            v40 = unk_8A7FD8
                + (((__int16)word_8A7F24 * unk_8A7FC6
                  + (__int16)word_8A7F2C * unk_8A7FCA
                  + (__int16)word_8A7F28 * unk_8A7FC8) >> 12);
            v42 = unk_8A7FDC
                + (((__int16)word_8A7F2C * unk_8A7FD0
                  + (__int16)word_8A7F28 * unk_8A7FCE
                  + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
            v43 = -32768;
            goto LABEL_56;
          }
          if ( (_UNKNOWN *)v26 != &MEMORY[0x4DC412] )
            goto LABEL_630;
          v180 = (__int16)word_8A7F28;
          v181 = (__int16)word_8A7F24;
          v142 = (__int16)word_8A7F2C;
          v26 = unk_8A7FD4
              + (((__int16)word_8A7F2C * unk_8A7FC4
                + (__int16)word_8A7F28 * unk_8A7FC2
                + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
          v182 = (__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8;
          v183 = (__int16)word_8A7F24 * unk_8A7FC6;
          goto LABEL_537;
        }
        if ( (_UNKNOWN *)v26 == &MEMORY[0x4DE412] )
        {
          v26 = ((__int16)word_8A7F2C * unk_8A7FC4
               + (__int16)word_8A7F28 * unk_8A7FC2
               + (__int16)word_8A7F24 * unk_8A7FC0) >> 12;
          v185 = ((__int16)word_8A7F24 * unk_8A7FC6
                + (__int16)word_8A7F2C * unk_8A7FCA
                + (__int16)word_8A7F28 * unk_8A7FC8) >> 12;
          v42 = ((__int16)word_8A7F2C * unk_8A7FD0
               + (__int16)word_8A7F28 * unk_8A7FCE
               + (__int16)word_8A7F24 * unk_8A7FCC) >> 12;
          unk_8A7F64 = v26;
          unk_8A7F68 = v185;
          unk_8A7F6C = v42;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              word_8A7F24 = ((__int16)word_8A7F2C * unk_8A7FC4
                           + (__int16)word_8A7F28 * unk_8A7FC2
                           + (__int16)word_8A7F24 * unk_8A7FC0) >> 12;
            }
            else
            {
              unk_8A7FFC = -2130706432;
              word_8A7F24 = 0x7FFF;
            }
          }
          else
          {
            unk_8A7FFC = -2130706432;
            word_8A7F24 = 0;
          }
          if ( v185 >= 0 )
          {
            if ( v185 <= 0x7FFF )
            {
              word_8A7F28 = v185;
            }
            else
            {
              unk_8A7FFC |= 0x80800000;
              word_8A7F28 = 0x7FFF;
            }
          }
          else
          {
            unk_8A7FFC |= 0x80800000;
            word_8A7F28 = 0;
          }
          if ( v42 >= 0 )
            goto LABEL_541;
          goto LABEL_573;
        }
        if ( v26 != 5767213 )
          goto LABEL_630;
LABEL_694:
        unk_8A7F60 = unk_8A7FF4
                   * ((unsigned __int16)unk_8A7F44 + (unsigned __int16)unk_8A7F48 + (unsigned __int16)unk_8A7F4C);
        v26 = unk_8A7F60 >> 12;
        if ( unk_8A7F60 >> 12 >= 0 )
        {
          if ( (int)v26 <= 0xFFFF )
          {
            unk_8A7F1C = unk_8A7F60 >> 12;
          }
          else
          {
            unk_8A7FFC |= 0x80040000;
            unk_8A7F1C = -1;
          }
        }
        else
        {
          unk_8A7FFC |= 0x80040000;
          unk_8A7F1C = 0;
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
          if ( v26 != 27263038 )
          {
            if ( v26 == 27787326 )
            {
              v22 = ((unk_8A7F20 * (__int16)word_8A7F28) >> 12) + unk_8A7F68;
              v23 = ((unk_8A7F20 * (__int16)word_8A7F2C) >> 12) + unk_8A7F6C;
              unk_8A7F64 += (unk_8A7F20 * (__int16)word_8A7F24) >> 12;
              unk_8A7F68 = v22;
              unk_8A7F6C = v23;
              if ( unk_8A7F64 >= -32768 )
              {
                if ( unk_8A7F64 <= 0x7FFF )
                {
                  word_8A7F24 = unk_8A7F64;
                }
                else
                {
                  unk_8A7FFC |= 0x81000000;
                  word_8A7F24 = 0x7FFF;
                }
              }
              else
              {
                unk_8A7FFC |= 0x81000000;
                word_8A7F24 = -32768;
              }
              if ( v22 >= -32768 )
              {
                if ( v22 <= 0x7FFF )
                {
                  word_8A7F28 = v22;
                }
                else
                {
                  unk_8A7FFC |= 0x80800000;
                  word_8A7F28 = 0x7FFF;
                }
              }
              else
              {
                unk_8A7FFC |= 0x80800000;
                word_8A7F28 = -32768;
              }
              if ( v23 >= -32768 )
              {
                if ( v23 <= 0x7FFF )
                {
                  word_8A7F2C = v23;
                }
                else
                {
                  unk_8A7FFC |= 0x400000u;
                  word_8A7F2C = 0x7FFF;
                }
              }
              else
              {
                unk_8A7FFC |= 0x400000u;
                word_8A7F2C = -32768;
              }
              unk_8A7F50 = unk_8A7F54;
              v26 = unk_8A7F64 >> 4;
              unk_8A7F54 = unk_8A7F58;
              v24 = v22 >> 4;
              v25 = v23 >> 4;
              unk_8A8004 = unk_8A7F64 >> 4;
              unk_8A8008 = v24;
              unk_8A800C = v25;
              if ( unk_8A7F64 >> 4 >= 0 )
              {
                if ( (int)v26 <= 255 )
                {
                  LOBYTE(unk_8A7F58) = unk_8A7F64 >> 4;
                }
                else
                {
                  unk_8A7FFC |= 0x200000u;
                  LOBYTE(unk_8A7F58) = -1;
                }
              }
              else
              {
                unk_8A7FFC |= 0x200000u;
                LOBYTE(unk_8A7F58) = 0;
              }
              if ( v24 >= 0 )
              {
                if ( v24 <= 255 )
                {
                  BYTE1(unk_8A7F58) = v24;
                }
                else
                {
                  unk_8A7FFC |= 0x100000u;
                  BYTE1(unk_8A7F58) = -1;
                }
              }
              else
              {
                unk_8A7FFC |= 0x100000u;
                BYTE1(unk_8A7F58) = 0;
              }
              if ( v25 >= 0 )
              {
                if ( v25 <= 255 )
                {
                  BYTE2(unk_8A7F58) = v25;
                }
                else
                {
                  unk_8A7FFC |= 0x80000u;
                  LOBYTE(v26) = HIBYTE(unk_8A7F18);
                  BYTE2(unk_8A7F58) = -1;
                }
                HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
              }
              else
              {
                LOBYTE(v26) = unk_8A7FFC;
                unk_8A7FFC |= 0x80000u;
                BYTE2(unk_8A7F58) = 0;
                HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
              }
              return v26;
            }
            goto LABEL_630;
          }
        }
        else
        {
          if ( v26 == 26738749 )
            goto LABEL_735;
          v27 = v26 - 24641552;
          if ( v26 == 24641552 )
            goto LABEL_626;
          if ( v26 == 26214461 )
            goto LABEL_704;
          if ( v26 != 26214462 )
            goto LABEL_630;
        }
        v18 = unk_8A7F20 * (__int16)word_8A7F28 + unk_8A7F68;
        v19 = unk_8A7F20 * (__int16)word_8A7F2C + unk_8A7F6C;
        unk_8A7F64 += unk_8A7F20 * (__int16)word_8A7F24;
        unk_8A7F68 = v18;
        unk_8A7F6C = v19;
        if ( unk_8A7F64 >= -32768 )
        {
          if ( unk_8A7F64 <= 0x7FFF )
          {
            word_8A7F24 = unk_8A7F64;
          }
          else
          {
            unk_8A7FFC |= 0x81000000;
            word_8A7F24 = 0x7FFF;
          }
        }
        else
        {
          unk_8A7FFC |= 0x81000000;
          word_8A7F24 = -32768;
        }
        if ( v18 >= -32768 )
        {
          if ( v18 <= 0x7FFF )
          {
            word_8A7F28 = v18;
          }
          else
          {
            unk_8A7FFC |= 0x80800000;
            word_8A7F28 = 0x7FFF;
          }
        }
        else
        {
          unk_8A7FFC |= 0x80800000;
          word_8A7F28 = -32768;
        }
        if ( v19 >= -32768 )
        {
          if ( v19 <= 0x7FFF )
          {
            word_8A7F2C = v19;
          }
          else
          {
            unk_8A7FFC |= 0x400000u;
            word_8A7F2C = 0x7FFF;
          }
        }
        else
        {
          unk_8A7FFC |= 0x400000u;
          word_8A7F2C = -32768;
        }
        unk_8A7F50 = unk_8A7F54;
        v26 = unk_8A7F64 >> 4;
        unk_8A7F54 = unk_8A7F58;
        v20 = v18 >> 4;
        v21 = v19 >> 4;
        unk_8A8004 = unk_8A7F64 >> 4;
        unk_8A8008 = v20;
        unk_8A800C = v21;
        if ( unk_8A7F64 >> 4 >= 0 )
        {
          if ( (int)v26 <= 255 )
          {
            LOBYTE(unk_8A7F58) = unk_8A7F64 >> 4;
          }
          else
          {
            unk_8A7FFC |= 0x200000u;
            LOBYTE(unk_8A7F58) = -1;
          }
        }
        else
        {
          unk_8A7FFC |= 0x200000u;
          LOBYTE(unk_8A7F58) = 0;
        }
        if ( v20 >= 0 )
        {
          if ( v20 <= 255 )
          {
            BYTE1(unk_8A7F58) = v20;
          }
          else
          {
            unk_8A7FFC |= 0x100000u;
            BYTE1(unk_8A7F58) = -1;
          }
        }
        else
        {
          unk_8A7FFC |= 0x100000u;
          BYTE1(unk_8A7F58) = 0;
        }
        if ( v21 >= 0 )
        {
          if ( v21 <= 255 )
          {
            BYTE2(unk_8A7F58) = v21;
          }
          else
          {
            unk_8A7FFC |= 0x80000u;
            LOBYTE(v26) = HIBYTE(unk_8A7F18);
            BYTE2(unk_8A7F58) = -1;
          }
          HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
        }
        else
        {
          LOBYTE(v26) = unk_8A7FFC;
          unk_8A7FFC |= 0x80000u;
          BYTE2(unk_8A7F58) = 0;
          HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
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
          v26 = ((__int16)word_8A7F24 * (__int16)word_8A7F24) >> 12;
          v6 = ((__int16)word_8A7F28 * (__int16)word_8A7F28) >> 12;
          v7 = ((__int16)word_8A7F2C * (__int16)word_8A7F2C) >> 12;
          unk_8A7F64 = v26;
          unk_8A7F68 = v6;
          unk_8A7F6C = v7;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              word_8A7F24 = ((__int16)word_8A7F24 * (__int16)word_8A7F24) >> 12;
            }
            else
            {
              unk_8A7FFC |= 0x81000000;
              word_8A7F24 = 0x7FFF;
            }
          }
          else
          {
            unk_8A7FFC |= 0x81000000;
            word_8A7F24 = 0;
          }
          if ( v6 >= 0 )
          {
            if ( v6 <= 0x7FFF )
            {
              word_8A7F28 = ((__int16)word_8A7F28 * (__int16)word_8A7F28) >> 12;
            }
            else
            {
              unk_8A7FFC |= 0x80800000;
              word_8A7F28 = 0x7FFF;
            }
          }
          else
          {
            unk_8A7FFC |= 0x80800000;
            word_8A7F28 = 0;
          }
          if ( v7 >= 0 )
          {
            if ( v7 <= 0x7FFF )
            {
              word_8A7F2C = ((__int16)word_8A7F2C * (__int16)word_8A7F2C) >> 12;
            }
            else
            {
              unk_8A7FFC |= 0x400000u;
              word_8A7F2C = 0x7FFF;
            }
          }
          else
          {
            unk_8A7FFC |= 0x400000u;
            word_8A7F2C = 0;
          }
          return v26;
        }
        if ( v26 <= 0x980011 )
        {
          if ( v26 == 9961489 )
          {
            unk_8A7F64 = (__int16)word_8A7F24
                       + ((unk_8A7F20 * gte_clamp(-2130706432, unk_8A7FD4 - (__int16)word_8A7F24)) >> 12);
            unk_8A7F68 = (__int16)word_8A7F28
                       + ((unk_8A7F20 * gte_clamp(-2139095040, unk_8A7FD8 - (__int16)word_8A7F28)) >> 12);
            v0 = gte_clamp(0x400000, unk_8A7FDC - (__int16)word_8A7F2C);
            v2 = (__int16)word_8A7F2C + ((unk_8A7F20 * v0) >> 12);
            unk_8A7F6C = v2;
            if ( unk_8A7F64 >= -32768 )
            {
              if ( unk_8A7F64 <= 0x7FFF )
              {
                word_8A7F24 = unk_8A7F64;
              }
              else
              {
                unk_8A7FFC |= v1;
                word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= v1;
              word_8A7F24 = -32768;
            }
            if ( unk_8A7F68 >= -32768 )
            {
              if ( unk_8A7F68 <= 0x7FFF )
              {
                word_8A7F28 = unk_8A7F68;
              }
              else
              {
                unk_8A7FFC |= 0x80800000;
                word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x80800000;
              word_8A7F28 = -32768;
            }
            if ( v2 >= -32768 )
            {
              if ( v2 <= 0x7FFF )
              {
                word_8A7F2C = v2;
              }
              else
              {
                unk_8A7FFC |= 0x400000u;
                word_8A7F2C = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x400000u;
              word_8A7F2C = -32768;
            }
            unk_8A7F50 = unk_8A7F54;
            v3 = unk_8A7F68 >> 4;
            v26 = v2 >> 4;
            unk_8A7F54 = unk_8A7F58;
            unk_8A8004 = unk_8A7F64 >> 4;
            unk_8A8008 = unk_8A7F68 >> 4;
            unk_8A800C = v26;
            if ( unk_8A7F64 >> 4 >= 0 )
            {
              if ( unk_8A7F64 >> 4 <= 255 )
              {
                LOBYTE(unk_8A7F58) = unk_8A7F64 >> 4;
              }
              else
              {
                unk_8A7FFC |= 0x200000u;
                LOBYTE(unk_8A7F58) = -1;
              }
            }
            else
            {
              unk_8A7FFC |= 0x200000u;
              LOBYTE(unk_8A7F58) = 0;
            }
            if ( v3 >= 0 )
            {
              if ( v3 <= 255 )
              {
                BYTE1(unk_8A7F58) = unk_8A7F68 >> 4;
              }
              else
              {
                unk_8A7FFC |= 0x100000u;
                BYTE1(unk_8A7F58) = -1;
              }
            }
            else
            {
              unk_8A7FFC |= 0x100000u;
              BYTE1(unk_8A7F58) = 0;
            }
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 255 )
              {
                BYTE2(unk_8A7F58) = v26;
              }
              else
              {
                unk_8A7FFC |= 0x80000u;
                LOBYTE(v26) = HIBYTE(unk_8A7F18);
                BYTE2(unk_8A7F58) = -1;
              }
              HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
            }
            else
            {
              LOBYTE(v26) = unk_8A7FFC;
              unk_8A7FFC |= 0x80000u;
              BYTE2(unk_8A7F58) = 0;
              HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
            }
            return v26;
          }
          if ( (_UNKNOWN *)v26 != &MEMORY[0x68002E] )
          {
            if ( (_UNKNOWN *)v26 != &MEMORY[0x780010] )
            {
              if ( v26 != 9437245 )
                goto LABEL_630;
LABEL_704:
              v8 = unk_8A7F20 * (__int16)word_8A7F24;
              v9 = unk_8A7F20 * (__int16)word_8A7F28;
              v10 = unk_8A7F20 * (__int16)word_8A7F2C;
              unk_8A7F64 = v8;
              unk_8A7F68 = v9;
              unk_8A7F6C = v10;
              if ( v8 >= -32768 )
              {
                if ( v8 <= 0x7FFF )
                {
                  word_8A7F24 = unk_8A7F20 * (__int16)word_8A7F24;
                }
                else
                {
                  unk_8A7FFC |= 0x81000000;
                  word_8A7F24 = 0x7FFF;
                }
              }
              else
              {
                unk_8A7FFC |= 0x81000000;
                word_8A7F24 = -32768;
              }
              if ( v9 >= -32768 )
              {
                if ( v9 <= 0x7FFF )
                {
                  word_8A7F28 = unk_8A7F20 * (__int16)word_8A7F28;
                }
                else
                {
                  unk_8A7FFC |= 0x80800000;
                  word_8A7F28 = 0x7FFF;
                }
              }
              else
              {
                unk_8A7FFC |= 0x80800000;
                word_8A7F28 = -32768;
              }
              if ( v10 >= -32768 )
              {
                if ( v10 <= 0x7FFF )
                {
                  word_8A7F2C = unk_8A7F20 * (__int16)word_8A7F2C;
                }
                else
                {
                  unk_8A7FFC |= 0x400000u;
                  word_8A7F2C = 0x7FFF;
                }
              }
              else
              {
                unk_8A7FFC |= 0x400000u;
                word_8A7F2C = -32768;
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
                  LOBYTE(unk_8A7F58) = v26;
                }
                else
                {
                  unk_8A7FFC |= 0x200000u;
                  LOBYTE(unk_8A7F58) = -1;
                }
              }
              else
              {
                unk_8A7FFC |= 0x200000u;
                LOBYTE(unk_8A7F58) = 0;
              }
              if ( v11 >= 0 )
              {
                if ( v11 <= 255 )
                {
                  BYTE1(unk_8A7F58) = v11;
                }
                else
                {
                  unk_8A7FFC |= 0x100000u;
                  BYTE1(unk_8A7F58) = -1;
                }
              }
              else
              {
                unk_8A7FFC |= 0x100000u;
                BYTE1(unk_8A7F58) = 0;
              }
              if ( v12 >= 0 )
              {
                if ( v12 <= 255 )
                {
                  BYTE2(unk_8A7F58) = v12;
                }
                else
                {
                  LOBYTE(v26) = unk_8A7FFC;
                  unk_8A7FFC |= 0x80000u;
                  BYTE2(unk_8A7F58) = -1;
                }
                HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
              }
              else
              {
                unk_8A7FFC |= 0x80000u;
                BYTE2(unk_8A7F58) = 0;
                HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
                LOBYTE(v26) = HIBYTE(unk_8A7F18);
              }
              return v26;
            }
LABEL_626:
            LOBYTE(v26) = sub_410690(v27);
            return v26;
          }
LABEL_699:
          unk_8A7F60 = unk_8A7FF8
                     * ((unsigned __int16)unk_8A7F40
                      + (unsigned __int16)unk_8A7F44
                      + (unsigned __int16)unk_8A7F48
                      + (unsigned __int16)unk_8A7F4C);
          v26 = unk_8A7F60 >> 12;
          if ( unk_8A7F60 >> 12 >= 0 )
          {
            if ( (int)v26 <= 0xFFFF )
            {
              unk_8A7F1C = unk_8A7F60 >> 12;
            }
            else
            {
              unk_8A7FFC |= 0x80040000;
              unk_8A7F1C = -1;
            }
          }
          else
          {
            unk_8A7FFC |= 0x80040000;
            unk_8A7F1C = 0;
          }
          return v26;
        }
        if ( v26 != 9961533 )
        {
          if ( v26 == 10486824 )
          {
            v26 = (__int16)word_8A7F24 * (__int16)word_8A7F24;
            v4 = (__int16)word_8A7F28 * (__int16)word_8A7F28;
            v5 = (__int16)word_8A7F2C * (__int16)word_8A7F2C;
            unk_8A7F64 = v26;
            unk_8A7F68 = v4;
            unk_8A7F6C = v5;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                word_8A7F24 = (__int16)word_8A7F24 * (__int16)word_8A7F24;
              }
              else
              {
                unk_8A7FFC |= 0x81000000;
                word_8A7F24 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x81000000;
              word_8A7F24 = 0;
            }
            if ( v4 >= 0 )
            {
              if ( v4 <= 0x7FFF )
              {
                word_8A7F28 = (__int16)word_8A7F28 * (__int16)word_8A7F28;
              }
              else
              {
                unk_8A7FFC |= 0x80800000;
                word_8A7F28 = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x80800000;
              word_8A7F28 = 0;
            }
            if ( v5 >= 0 )
            {
              if ( v5 <= 0x7FFF )
              {
                word_8A7F2C = (__int16)word_8A7F2C * (__int16)word_8A7F2C;
              }
              else
              {
                unk_8A7FFC |= 0x400000u;
                word_8A7F2C = 0x7FFF;
              }
            }
            else
            {
              unk_8A7FFC |= 0x400000u;
              word_8A7F2C = 0;
            }
            return v26;
          }
          goto LABEL_630;
        }
LABEL_735:
        v13 = (unk_8A7F20 * (__int16)word_8A7F24) >> 12;
        v14 = (unk_8A7F20 * (__int16)word_8A7F28) >> 12;
        v15 = (unk_8A7F20 * (__int16)word_8A7F2C) >> 12;
        unk_8A7F64 = v13;
        unk_8A7F68 = v14;
        unk_8A7F6C = v15;
        if ( v13 >= -32768 )
        {
          if ( v13 <= 0x7FFF )
          {
            word_8A7F24 = (unk_8A7F20 * (__int16)word_8A7F24) >> 12;
          }
          else
          {
            unk_8A7FFC |= 0x81000000;
            word_8A7F24 = 0x7FFF;
          }
        }
        else
        {
          unk_8A7FFC |= 0x81000000;
          word_8A7F24 = -32768;
        }
        if ( v14 >= -32768 )
        {
          if ( v14 <= 0x7FFF )
          {
            word_8A7F28 = (unk_8A7F20 * (__int16)word_8A7F28) >> 12;
          }
          else
          {
            unk_8A7FFC |= 0x80800000;
            word_8A7F28 = 0x7FFF;
          }
        }
        else
        {
          unk_8A7FFC |= 0x80800000;
          word_8A7F28 = -32768;
        }
        if ( v15 >= -32768 )
        {
          if ( v15 <= 0x7FFF )
          {
            word_8A7F2C = (unk_8A7F20 * (__int16)word_8A7F2C) >> 12;
          }
          else
          {
            unk_8A7FFC |= 0x400000u;
            word_8A7F2C = 0x7FFF;
          }
        }
        else
        {
          unk_8A7FFC |= 0x400000u;
          word_8A7F2C = -32768;
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
            LOBYTE(unk_8A7F58) = v26;
          }
          else
          {
            unk_8A7FFC |= 0x200000u;
            LOBYTE(unk_8A7F58) = -1;
          }
        }
        else
        {
          unk_8A7FFC |= 0x200000u;
          LOBYTE(unk_8A7F58) = 0;
        }
        if ( v16 >= 0 )
        {
          if ( v16 <= 255 )
          {
            BYTE1(unk_8A7F58) = v16;
          }
          else
          {
            unk_8A7FFC |= 0x100000u;
            BYTE1(unk_8A7F58) = -1;
          }
        }
        else
        {
          unk_8A7FFC |= 0x100000u;
          BYTE1(unk_8A7F58) = 0;
        }
        if ( v17 >= 0 )
        {
          if ( v17 <= 255 )
          {
            BYTE2(unk_8A7F58) = v17;
          }
          else
          {
            LOBYTE(v26) = unk_8A7FFC;
            unk_8A7FFC |= 0x80000u;
            BYTE2(unk_8A7F58) = -1;
          }
          HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
        }
        else
        {
          unk_8A7FFC |= 0x80000u;
          BYTE2(unk_8A7F58) = 0;
          HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
          LOBYTE(v26) = HIBYTE(unk_8A7F18);
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
