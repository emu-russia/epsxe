#include "pch.h"
char gte_exec_opcode()
{
  int v0; // eax
  int v1; // edx
  GTE_REG v2; // eax
  int32_t v3; // edx
  GTE_REG v4; // ecx
  GTE_REG v5; // edx
  int v6; // ecx
  int v7; // edx
  GTE_REG v8; // eax
  GTE_REG v9; // ecx
  GTE_REG v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  GTE_REG v18; // ecx
  GTE_REG v19; // edx
  int v20; // ecx
  int v21; // edx
  GTE_REG v22; // ecx
  GTE_REG v23; // edx
  int v24; // ecx
  int v25; // edx
  unsigned int v26; // eax
  unsigned __int8 v27; // bl
  unsigned __int8 v28; // cl
  unsigned __int8 v29; // al
  int v30; // edx
  GTE_REG v31; // ecx
  GTE_REG v32; // edx
  int v33; // esi
  int v34; // edx
  int v35; // edi
  uint32_t v36; // ebp
  int v37; // ebx
  int v38; // ecx
  int v39; // ecx
  GTE_REG v40; // ebp
  int v41; // edx
  GTE_REG v42; // esi
  int v43; // esi
  int v44; // edx
  int v45; // edi
  uint32_t v46; // ebp
  int v47; // ebx
  int v48; // ecx
  GTE_REG v49; // ebp
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
  GTE_REG v68; // edi
  int v69; // edi
  int v70; // ebx
  int v71; // esi
  int v72; // edx
  int v73; // edi
  int v74; // esi
  GTE_REG v75; // ebp
  int v76; // edx
  int v77; // edi
  uint32_t v78; // ebp
  int v79; // ebx
  int v80; // ecx
  int v81; // edx
  int v82; // edi
  int v83; // esi
  uint32_t v84; // ebp
  int v85; // ebx
  int v86; // ecx
  uint32_t v87; // ebp
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
  GTE_REG v108; // ebp
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
  int lo; // edi
  int hi; // ebp
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
          v26 = (unsigned __int8)gte_count_leading_bits(gte_regs.data[30].s32);
          cpu_gpr[v27] = v26;
        }
        else
        {
          if ( v28 == 29 )
          {
            gte_convert_to_5bit(gte_regs.data[11].u16.hi);
            gte_convert_to_5bit(gte_regs.data[10].u16.hi);
            v29 = gte_convert_to_5bit(gte_regs.data[9].u16.hi);
            v27 = byte_8A7EE0;
            gte_regs.data[29].u32 = v29 | v30;
          }
          LOBYTE(v26) = v27;
          cpu_gpr[v27] = gte_regs.data[v28].s32;
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
        cpu_gpr[v26] = gte_regs.ctrl[(unsigned __int16)cpu_opcode >> 11].s32;
      }
      return v26;
    case 4u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      byte_8A8001 = v26;
      v31.u32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      gte_regs.data[(unsigned __int8)v26] = v31;
      if ( (unsigned __int8)v26 >= 0x10u && (unsigned __int8)v26 <= 0x13u )
        gte_regs.data[(unsigned __int8)v26].u32 = v31.u16.hi;
      switch ( (_BYTE)v26 )
      {
        case 0xE:
          gte_regs.data[15] = v31;
          break;
        case 0xF:
          LOBYTE(v26) = gte_regs.data[13].u16.hi;
          gte_regs.data[12].u32 = gte_regs.data[13].u32;
          gte_regs.data[13].u32 = gte_regs.data[14].u32;
          gte_regs.data[14] = v31;
          break;
        case 0x1C:
          v26 = (gte_regs.data[28].u16.hi >> 3) & 0xF80;
          gte_regs.data[9].u32 = (gte_regs.data[28].u16.hi & 0x1F) << 7;
          gte_regs.data[10].u32 = 4 * (gte_regs.data[28].u16.hi & 0x3E0);
          gte_regs.data[11].u32 = v26;
          break;
      }
      return v26;
    case 6u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      v32.u32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      byte_8A8000 = v26;
      gte_regs.ctrl[(unsigned __int8)v26] = v32;
      return v26;
    default:
      v26 = cpu_opcode & 0x1FFFFFF;
      gte_regs.ctrl[31].u32 = 0;
      if ( (cpu_opcode & 0x1FFFFFFu) <= 0x48A412 )
      {
        if ( v26 == 4760594 )
        {
          lo = gte_regs.data[2].s16.lo;
          hi = gte_regs.data[2].s16.hi;
          v118 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.ctrl[13].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          v121 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          v122 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_314;
        }
        if ( v26 <= 0x432012 )
        {
          if ( v26 == 4399122 )
          {
            v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
            v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
            v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[15].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= 0x416012 )
          {
            if ( v26 == 4284434 )
            {
              v59 = gte_regs.data[4].s16.lo;
              v60 = gte_regs.data[4].s16.hi;
              v58 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi;
              v61 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
              v62 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_80;
            }
            if ( v26 <= 0x408012 )
            {
              if ( v26 == 4227090 )
              {
                v34 = gte_regs.data[2].s16.lo;
                v35 = gte_regs.data[2].s16.hi;
                v33 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                v36 = gte_regs.ctrl[6].u32 + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi;
                v37 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                v38 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
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
                        LOBYTE(v26) = gte_nccs();
                        return v26;
                      }
LABEL_37:
                      LOBYTE(v26) = gte_rtps();
                      return v26;
                    }
LABEL_612:
                    v26 = gte_regs.data[14].s16.hi * (gte_regs.data[12].s16.lo - gte_regs.data[13].s16.lo);
                    gte_regs.data[24].u32 = v26
                                          + gte_regs.data[13].s16.hi
                                          * (gte_regs.data[14].s16.lo - gte_regs.data[12].s16.lo)
                                          + gte_regs.data[12].s16.hi
                                          * (gte_regs.data[13].s16.lo - gte_regs.data[14].s16.lo);
                    return v26;
                  }
                  if ( v26 == 0x280030 )
                  {
                    LOBYTE(v26) = gte_rtpt();
                    return v26;
                  }
                  if ( v26 == 0x400006 )
                    goto LABEL_612;
                  if ( v26 != 0x400012 )
                    goto LABEL_630;
                  v33 = gte_regs.data[1].s16.hi;
                  v34 = gte_regs.data[0].s16.lo;
                  v35 = gte_regs.data[0].s16.hi;
                  goto LABEL_42;
                }
                v43 = gte_regs.data[1].s16.hi;
                v44 = gte_regs.data[0].s16.lo;
                v45 = gte_regs.data[0].s16.hi;
LABEL_52:
                v26 = v45 * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + v44 * gte_regs.ctrl[0].s16.lo
                    + v43 * gte_regs.ctrl[1].s16.hi;
                v46 = gte_regs.ctrl[6].u32 + v45 * gte_regs.ctrl[1].s16.lo;
                v47 = v43 * gte_regs.ctrl[2].s16.lo;
                v48 = v44 * gte_regs.ctrl[2].s16.hi;
LABEL_53:
                v39 = v47 + v46 + v48;
                v49 = gte_regs.ctrl[7];
LABEL_54:
                v50 = v45 * gte_regs.ctrl[3].s16.hi;
                v51 = v44 * gte_regs.ctrl[3].s16.lo;
                v52 = gte_regs.ctrl[4].s16.hi;
LABEL_55:
                v41 = v50 + v49.u32 + v51 + v43 * v52;
                v42.u32 = 0;
                goto LABEL_56;
              }
              if ( v26 <= 0x404412 )
              {
                if ( v26 != 0x404412 )
                {
                  if ( v26 == 0x402012 )
                  {
                    v34 = gte_regs.data[0].s16.lo;
                    v35 = gte_regs.data[0].s16.hi;
                    v33 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                    v40 = gte_regs.ctrl[15];
                    goto LABEL_44;
                  }
                  if ( v26 != 4203538 )
                  {
                    if ( v26 != 4210706 )
                      goto LABEL_630;
                    v34 = gte_regs.data[0].s16.lo;
                    v35 = gte_regs.data[0].s16.hi;
                    v33 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                    v40 = gte_regs.ctrl[23];
                    goto LABEL_44;
                  }
                  v44 = gte_regs.data[0].s16.lo;
                  v45 = gte_regs.data[0].s16.hi;
                  v43 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                  v49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                v43 = gte_regs.data[1].s16.hi;
                v44 = gte_regs.data[0].s16.lo;
                v45 = gte_regs.data[0].s16.hi;
                goto LABEL_138;
              }
              if ( v26 != 4218898 )
              {
                if ( v26 != 4219922 )
                  goto LABEL_630;
                v53 = gte_regs.data[1].s16.hi;
                v54 = gte_regs.data[0].s16.lo;
                v55 = gte_regs.data[0].s16.hi;
                goto LABEL_72;
              }
              v58 = gte_regs.data[1].s16.hi;
              v59 = gte_regs.data[0].s16.lo;
              v60 = gte_regs.data[0].s16.hi;
              goto LABEL_79;
            }
            if ( v26 > 0x40E412 )
            {
              if ( v26 > 0x412412 )
              {
                if ( v26 == 4276242 )
                {
                  v34 = gte_regs.data[4].s16.lo;
                  v35 = gte_regs.data[4].s16.hi;
                  v33 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  v40 = gte_regs.ctrl[23];
                  goto LABEL_44;
                }
                if ( v26 != 4277266 )
                  goto LABEL_630;
                v44 = gte_regs.data[4].s16.lo;
                v45 = gte_regs.data[4].s16.hi;
                v43 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[22].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                v49 = gte_regs.ctrl[23];
                goto LABEL_54;
              }
              if ( v26 == 4269074 )
              {
                v44 = gte_regs.data[4].s16.lo;
                v45 = gte_regs.data[4].s16.hi;
                v43 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                v49 = gte_regs.ctrl[15];
                goto LABEL_54;
              }
              if ( v26 == 4259858 )
              {
                v34 = gte_regs.data[4].s16.lo;
                v35 = gte_regs.data[4].s16.hi;
                v33 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v36 = gte_regs.ctrl[6].u32 + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi;
                v37 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                v38 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_43;
              }
              if ( v26 != 4260882 )
              {
                if ( v26 != 4268050 )
                  goto LABEL_630;
                v34 = gte_regs.data[4].s16.lo;
                v35 = gte_regs.data[4].s16.hi;
                v33 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                v40 = gte_regs.ctrl[15];
                goto LABEL_44;
              }
              v44 = gte_regs.data[4].s16.lo;
              v45 = gte_regs.data[4].s16.hi;
              v43 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
              v46 = gte_regs.ctrl[6].u32 + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi;
              v47 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
              v48 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_53;
            }
            if ( v26 != 4252690 )
            {
              if ( v26 <= 0x40C012 )
              {
                if ( v26 == 4243474 )
                {
                  v34 = gte_regs.data[2].s16.lo;
                  v35 = gte_regs.data[2].s16.hi;
                  v33 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  v40 = gte_regs.ctrl[23];
                  goto LABEL_44;
                }
                if ( v26 != 4228114 )
                {
                  if ( v26 == 4235282 )
                  {
                    v34 = gte_regs.data[2].s16.lo;
                    v35 = gte_regs.data[2].s16.hi;
                    v33 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                    v40 = gte_regs.ctrl[15];
                    goto LABEL_44;
                  }
                  if ( v26 != 4236306 )
                    goto LABEL_630;
                  v44 = gte_regs.data[2].s16.lo;
                  v45 = gte_regs.data[2].s16.hi;
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  v49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                v44 = gte_regs.data[2].s16.lo;
                v45 = gte_regs.data[2].s16.hi;
                v43 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                v46 = gte_regs.ctrl[6].u32 + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi;
                v47 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                v48 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_53;
              }
              if ( v26 == 4244498 )
              {
                v44 = gte_regs.data[2].s16.lo;
                v45 = gte_regs.data[2].s16.hi;
                v43 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[22].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                v49 = gte_regs.ctrl[23];
                goto LABEL_54;
              }
              if ( v26 != 4251666 )
                goto LABEL_630;
              v59 = gte_regs.data[2].s16.lo;
              v60 = gte_regs.data[2].s16.hi;
              v58 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi;
              v61 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
              v62 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_80;
            }
            v53 = gte_regs.data[3].s16.hi;
            v54 = gte_regs.data[2].s16.lo;
            v55 = gte_regs.data[2].s16.hi;
LABEL_98:
            v26 = v53 * gte_regs.ctrl[1].s16.hi + v54 * gte_regs.ctrl[0].s16.lo + v55 * gte_regs.ctrl[0].s16.hi;
            v56 = v54 * gte_regs.ctrl[2].s16.hi + v55 * gte_regs.ctrl[1].s16.lo;
            v57 = v53 * gte_regs.ctrl[2].s16.lo;
            goto LABEL_99;
          }
          if ( v26 <= 0x424012 )
          {
            if ( v26 == 4341778 )
            {
              v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
              v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[22].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
              v41 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                  + gte_regs.ctrl[23].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
              v42.u32 = -32768;
            }
            else
            {
              if ( v26 <= 0x41C412 )
              {
                if ( v26 == 4310034 )
                {
                  v43 = gte_regs.data[11].s16.hi;
                  v44 = gte_regs.data[10].s16.hi;
                  v45 = gte_regs.data[9].s16.hi;
LABEL_138:
                  v26 = v45 * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + v44 * gte_regs.ctrl[0].s16.lo
                      + v43 * gte_regs.ctrl[1].s16.hi;
                  v39 = v43 * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[22].u32
                      + v45 * gte_regs.ctrl[1].s16.lo
                      + v44 * gte_regs.ctrl[2].s16.hi;
                  v49 = gte_regs.ctrl[23];
                  goto LABEL_54;
                }
                if ( v26 > 0x41A012 )
                {
                  if ( v26 != 4301842 )
                  {
                    if ( v26 != 4309010 )
                      goto LABEL_630;
                    v34 = gte_regs.data[10].s16.hi;
                    v35 = gte_regs.data[9].s16.hi;
                    v33 = gte_regs.data[11].s16.hi;
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                    v40 = gte_regs.ctrl[23];
                    goto LABEL_44;
                  }
                  v44 = gte_regs.data[10].s16.hi;
                  v45 = gte_regs.data[9].s16.hi;
                  v43 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                  v49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                if ( v26 == 4300818 )
                {
                  v34 = gte_regs.data[10].s16.hi;
                  v35 = gte_regs.data[9].s16.hi;
                  v33 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                  v40 = gte_regs.ctrl[15];
                  goto LABEL_44;
                }
                if ( v26 != 4285458 )
                {
                  if ( v26 == 4292626 )
                  {
                    v33 = gte_regs.data[11].s16.hi;
                    v34 = gte_regs.data[10].s16.hi;
                    v35 = gte_regs.data[9].s16.hi;
LABEL_42:
                    v26 = v35 * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[5].u32
                        + v34 * gte_regs.ctrl[0].s16.lo
                        + v33 * gte_regs.ctrl[1].s16.hi;
                    v36 = gte_regs.ctrl[6].u32 + v35 * gte_regs.ctrl[1].s16.lo;
                    v37 = v33 * gte_regs.ctrl[2].s16.lo;
                    v38 = v34 * gte_regs.ctrl[2].s16.hi;
LABEL_43:
                    v39 = v37 + v36 + v38;
                    v40 = gte_regs.ctrl[7];
LABEL_44:
                    v41 = v35 * gte_regs.ctrl[3].s16.hi
                        + v40.u32
                        + v34 * gte_regs.ctrl[3].s16.lo
                        + v33 * gte_regs.ctrl[4].s16.hi;
                    v42.u32 = -32768;
                    goto LABEL_56;
                  }
                  if ( v26 != 4293650 )
                    goto LABEL_630;
                  v43 = gte_regs.data[11].s16.hi;
                  v44 = gte_regs.data[10].s16.hi;
                  v45 = gte_regs.data[9].s16.hi;
                  goto LABEL_52;
                }
                v53 = gte_regs.data[5].s16.hi;
                v54 = gte_regs.data[4].s16.lo;
                v55 = gte_regs.data[4].s16.hi;
                goto LABEL_98;
              }
              if ( v26 > 0x420412 )
              {
                if ( v26 != 4333586 )
                {
                  if ( v26 != 4334610 )
                    goto LABEL_630;
                  v43 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                  v50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                  v51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v49 = gte_regs.ctrl[15];
                  v52 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_55;
                }
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                v41 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                    + gte_regs.ctrl[15].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
                v42.u32 = -32768;
              }
              else
              {
                switch ( v26 )
                {
                  case 0x420412u:
                    v43 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[5].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[6].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v49 = gte_regs.ctrl[7];
                    v52 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_55;
                  case 0x41E012u:
                    v58 = gte_regs.data[11].s16.hi;
                    v59 = gte_regs.data[10].s16.hi;
                    v60 = gte_regs.data[9].s16.hi;
LABEL_79:
                    v26 = v58 * gte_regs.ctrl[1].s16.hi + v59 * gte_regs.ctrl[0].s16.lo + v60 * gte_regs.ctrl[0].s16.hi;
                    v61 = v60 * gte_regs.ctrl[1].s16.lo + v58 * gte_regs.ctrl[2].s16.lo;
                    v62 = v59 * gte_regs.ctrl[2].s16.hi;
LABEL_80:
                    v39 = v62 + v61;
                    v41 = v58 * gte_regs.ctrl[4].s16.hi + v59 * gte_regs.ctrl[3].s16.lo + v60 * gte_regs.ctrl[3].s16.hi;
                    v42.u32 = -32768;
                    goto LABEL_56;
                  case 0x41E412u:
                    v53 = gte_regs.data[11].s16.hi;
                    v54 = gte_regs.data[10].s16.hi;
                    v55 = gte_regs.data[9].s16.hi;
LABEL_72:
                    v26 = v53 * gte_regs.ctrl[1].s16.hi + v54 * gte_regs.ctrl[0].s16.lo + v55 * gte_regs.ctrl[0].s16.hi;
                    v56 = v55 * gte_regs.ctrl[1].s16.lo + v53 * gte_regs.ctrl[2].s16.lo;
                    v57 = v54 * gte_regs.ctrl[2].s16.hi;
LABEL_99:
                    v63 = v57 + v56;
                    v64 = v55 * gte_regs.ctrl[3].s16.hi;
                    v65 = v54 * gte_regs.ctrl[3].s16.lo;
                    v66 = gte_regs.ctrl[4].s16.hi;
LABEL_100:
                    v67 = v65 + v64;
                    v68.u32 = v53 * v66;
LABEL_101:
                    v41 = v68.u32 + v67;
                    goto LABEL_102;
                }
                if ( v26 != 4325394 )
                  goto LABEL_630;
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                v41 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
                v42.u32 = -32768;
              }
            }
LABEL_56:
            gte_regs.data[25].u32 = v26;
            gte_regs.data[26].u32 = v39;
            gte_regs.data[27].u32 = v41;
            if ( (int)v26 >= v42.s32 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = v26;
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9] = v42;
            }
            if ( v39 >= v42.s32 )
            {
              if ( v39 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = v39;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10] = v42;
            }
            if ( v41 >= v42.s32 )
            {
LABEL_541:
              if ( v41 <= 0x7FFF )
              {
                gte_regs.data[11].u32 = v41;
              }
              else
              {
                gte_regs.data[11].u32 = 0x7FFF;
                LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
                gte_regs.ctrl[31].u32 |= 0x400000u;
              }
              return v26;
            }
LABEL_558:
            gte_regs.data[11] = v42;
            LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
            gte_regs.ctrl[31].u32 |= 0x400000u;
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
                v43 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                v50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                v51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                v49 = gte_regs.ctrl[7];
                v52 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_55;
              }
              v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
              v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
              v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                  + gte_regs.ctrl[7].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
              v42.u32 = -32768;
            }
            else
            {
              switch ( v26 )
              {
                case 0x42E412u:
                  v53 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi;
                  v63 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                  v64 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v65 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v66 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_100;
                case 0x42C012u:
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
                  v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                      + gte_regs.ctrl[23].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
                  v42.u32 = -32768;
                  break;
                case 0x42C412u:
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
                  v50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
                  v51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v49 = gte_regs.ctrl[23];
                  v52 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_55;
                case 0x42E012u:
                  v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi;
                  v39 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                  v41 = gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v42.u32 = -32768;
                  break;
                default:
                  goto LABEL_630;
              }
            }
            goto LABEL_56;
          }
          if ( v26 == 4367378 )
          {
            v43 = gte_regs.data[3].s16.hi;
            v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            v50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
            v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            v51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
            v49 = gte_regs.ctrl[15];
            v52 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_55;
          }
          if ( v26 > 0x428012 )
          {
            if ( v26 == 4359186 )
            {
              v43 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
              v50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
              v51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              v49 = gte_regs.ctrl[7];
              v52 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_55;
            }
            if ( v26 != 4366354 )
              goto LABEL_630;
            v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[15].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4358162 )
          {
            v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[5].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[6].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[7].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4342802 )
          {
            v43 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[21].u32
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
            v50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
            v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[22].u32
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
            v51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
            v49 = gte_regs.ctrl[23];
            v52 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_55;
          }
          if ( v26 != 4349970 )
          {
            if ( v26 != 4350994 )
              goto LABEL_630;
            v53 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi;
            v63 = gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo;
            v64 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
            v65 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
            v66 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_100;
          }
          v69 = gte_regs.data[0].s16.lo;
          v70 = gte_regs.data[0].s16.hi;
          v71 = gte_regs.data[1].s16.hi;
          v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
              + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
              + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi;
LABEL_214:
          v39 = v71 * gte_regs.ctrl[10].s16.lo + v69 * gte_regs.ctrl[10].s16.hi + v70 * gte_regs.ctrl[9].s16.lo;
          v41 = v71 * gte_regs.ctrl[12].s16.hi + v69 * gte_regs.ctrl[11].s16.lo + v70 * gte_regs.ctrl[11].s16.hi;
          v42.u32 = -32768;
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
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[15].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    v42.u32 = -32768;
                  }
                  else if ( v26 > 0x436012 )
                  {
                    if ( v26 == 4416530 )
                    {
                      v53 = gte_regs.data[5].s16.hi;
                      v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi;
                      v63 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
                      v64 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v65 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                      v66 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_100;
                    }
                    if ( v26 != 4423698 )
                    {
                      if ( v26 != 4424722 )
                        goto LABEL_630;
                      v43 = gte_regs.data[11].s16.hi;
                      v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[5].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      v50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[6].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      v51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      v49 = gte_regs.ctrl[7];
                      v52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[5].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[6].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[7].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    v42.u32 = -32768;
                  }
                  else
                  {
                    switch ( v26 )
                    {
                      case 0x436012u:
                        v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi;
                        v39 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
                        v41 = gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        v42.u32 = -32768;
                        break;
                      case 0x432412u:
                        v43 = gte_regs.data[5].s16.hi;
                        v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[13].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        v50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[14].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        v51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                        v49 = gte_regs.ctrl[15];
                        v52 = gte_regs.ctrl[12].s16.hi;
                        goto LABEL_55;
                      case 0x434012u:
                        v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[21].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[22].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                            + gte_regs.ctrl[23].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
                        v42.u32 = -32768;
                        break;
                      case 0x434412u:
                        v43 = gte_regs.data[5].s16.hi;
                        v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[21].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        v50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[22].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        v51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                        v49 = gte_regs.ctrl[23];
                        v52 = gte_regs.ctrl[12].s16.hi;
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
                      v43 = gte_regs.data[11].s16.hi;
                      v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[13].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      v50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[14].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      v51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      v49 = gte_regs.ctrl[15];
                      v52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    if ( v26 != 4440082 )
                    {
                      if ( v26 != 4441106 )
                        goto LABEL_630;
                      v43 = gte_regs.data[11].s16.hi;
                      v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[21].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      v50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[22].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      v51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      v49 = gte_regs.ctrl[23];
                      v52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[23].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    v42.u32 = -32768;
                    goto LABEL_56;
                  }
                  v69 = gte_regs.data[10].s16.hi;
                  v70 = gte_regs.data[9].s16.hi;
                  v71 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi;
                  goto LABEL_214;
                }
                if ( v26 == 4449298 )
                {
                  v53 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi;
                  v63 = gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo;
                  v64 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v65 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                  v66 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_100;
                }
                if ( v26 != 4456466 )
                  goto LABEL_630;
                v72 = gte_regs.data[0].s16.lo;
                v73 = gte_regs.data[0].s16.hi;
                v74 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                v75 = gte_regs.ctrl[7];
LABEL_282:
                v41 = v73 * gte_regs.ctrl[19].s16.hi
                    + v75.u32
                    + v72 * gte_regs.ctrl[19].s16.lo
                    + v74 * gte_regs.ctrl[20].s16.hi;
                v42.u32 = -32768;
                goto LABEL_56;
              }
              v76 = gte_regs.data[0].s16.lo;
              v77 = gte_regs.data[0].s16.hi;
              v43 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
              v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
              v49 = gte_regs.ctrl[7];
LABEL_287:
              v50 = v77 * gte_regs.ctrl[19].s16.hi;
              v51 = v76 * gte_regs.ctrl[19].s16.lo;
              v52 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_55;
            }
            if ( v26 <= 0x448012 )
            {
              if ( v26 == 4489234 )
              {
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                v42.u32 = -32768;
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
                      v76 = gte_regs.data[0].s16.lo;
                      v77 = gte_regs.data[0].s16.hi;
                      v43 = gte_regs.data[1].s16.hi;
                      v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                          + gte_regs.ctrl[13].u32
                          + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                          + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                      v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                          + gte_regs.ctrl[14].u32
                          + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                          + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                      v49 = gte_regs.ctrl[15];
                      goto LABEL_287;
                    }
                    if ( v26 != 4472850 )
                      goto LABEL_630;
                    v72 = gte_regs.data[0].s16.lo;
                    v73 = gte_regs.data[0].s16.hi;
                    v74 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                    v78 = gte_regs.ctrl[22].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                    v79 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                    v80 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_281:
                    v39 = v79 + v78 + v80;
                    v75 = gte_regs.ctrl[23];
                    goto LABEL_282;
                  }
                  v81 = gte_regs.data[0].s16.lo;
                  v82 = gte_regs.data[0].s16.hi;
                  v83 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v84 = gte_regs.ctrl[14].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                  v85 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v86 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_277:
                  v39 = v85 + v84 + v86;
                  v41 = v82 * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + v81 * gte_regs.ctrl[19].s16.lo
                      + v83 * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                }
                v76 = gte_regs.data[0].s16.lo;
                v77 = gte_regs.data[0].s16.hi;
                v43 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                v87 = gte_regs.ctrl[22].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                v88 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                v89 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_286:
                v39 = v88 + v87 + v89;
                v49 = gte_regs.ctrl[23];
                goto LABEL_287;
              }
              if ( v26 != 4481042 )
              {
                if ( v26 != 4482066 )
                  goto LABEL_630;
                v90 = gte_regs.data[0].s16.lo;
                v91 = gte_regs.data[0].s16.hi;
                v53 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi;
                v92 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                v93 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                goto LABEL_302;
              }
              v94 = gte_regs.data[0].s16.lo;
              v95 = gte_regs.data[0].s16.hi;
              v96 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi;
              v97 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              v98 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_305:
              v39 = v98 + v97;
              v41 = v96 * gte_regs.ctrl[20].s16.hi + v94 * gte_regs.ctrl[19].s16.lo + v95 * gte_regs.ctrl[19].s16.hi;
              v42.u32 = -32768;
              goto LABEL_56;
            }
            if ( v26 <= 0x44C012 )
            {
              switch ( v26 )
              {
                case 0x44C012u:
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[23].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x448412u:
                  v76 = gte_regs.data[2].s16.lo;
                  v77 = gte_regs.data[2].s16.hi;
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[7];
                  break;
                case 0x44A012u:
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x44A412u:
                  v76 = gte_regs.data[2].s16.lo;
                  v77 = gte_regs.data[2].s16.hi;
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[15];
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
              v94 = gte_regs.data[2].s16.lo;
              v95 = gte_regs.data[2].s16.hi;
              v96 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi;
              goto LABEL_304;
            }
            v43 = gte_regs.data[3].s16.hi;
            v76 = gte_regs.data[2].s16.lo;
            v77 = gte_regs.data[2].s16.hi;
LABEL_285:
            v26 = v77 * gte_regs.ctrl[16].s16.hi
                + gte_regs.ctrl[21].u32
                + v76 * gte_regs.ctrl[16].s16.lo
                + v43 * gte_regs.ctrl[17].s16.hi;
            v87 = gte_regs.ctrl[22].u32 + v43 * gte_regs.ctrl[18].s16.lo;
            v88 = v76 * gte_regs.ctrl[18].s16.hi;
            v89 = v77 * gte_regs.ctrl[17].s16.lo;
            goto LABEL_286;
          }
          v90 = gte_regs.data[2].s16.lo;
          v91 = gte_regs.data[2].s16.hi;
          v53 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi;
LABEL_301:
          v92 = v53 * gte_regs.ctrl[18].s16.lo + v90 * gte_regs.ctrl[18].s16.hi;
          v93 = v91 * gte_regs.ctrl[17].s16.lo;
LABEL_302:
          v63 = v93 + v92;
          v64 = v91 * gte_regs.ctrl[19].s16.hi;
          v65 = v90 * gte_regs.ctrl[19].s16.lo;
          v66 = gte_regs.ctrl[20].s16.hi;
          goto LABEL_100;
        }
        if ( v26 <= 0x45C412 )
        {
          if ( v26 == 4572178 )
          {
            v43 = gte_regs.data[11].s16.hi;
            v76 = gte_regs.data[10].s16.hi;
            v77 = gte_regs.data[9].s16.hi;
            goto LABEL_285;
          }
          if ( v26 > 0x456012 )
          {
            if ( v26 > 0x45A012 )
            {
              if ( v26 == 4563986 )
              {
                v76 = gte_regs.data[10].s16.hi;
                v77 = gte_regs.data[9].s16.hi;
                v43 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
                v49 = gte_regs.ctrl[15];
                goto LABEL_287;
              }
              if ( v26 != 4571154 )
                goto LABEL_630;
              v72 = gte_regs.data[10].s16.hi;
              v73 = gte_regs.data[9].s16.hi;
              v74 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              v78 = gte_regs.ctrl[22].u32 + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo;
              v79 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              v80 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_281;
            }
            if ( v26 == 4562962 )
            {
              v81 = gte_regs.data[10].s16.hi;
              v82 = gte_regs.data[9].s16.hi;
              v83 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[13].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              v84 = gte_regs.ctrl[14].u32 + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo;
              v85 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              v86 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_277;
            }
            if ( v26 != 4547602 )
            {
              if ( v26 == 4554770 )
              {
                v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
                v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi;
                v42.u32 = -32768;
                goto LABEL_56;
              }
              if ( v26 != 4555794 )
                goto LABEL_630;
              v76 = gte_regs.data[10].s16.hi;
              v77 = gte_regs.data[9].s16.hi;
              v43 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              v39 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              v49 = gte_regs.ctrl[7];
              goto LABEL_287;
            }
            v90 = gte_regs.data[4].s16.lo;
            v91 = gte_regs.data[4].s16.hi;
            v53 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi;
            goto LABEL_301;
          }
          if ( v26 != 4546578 )
          {
            if ( v26 <= 0x452412 )
            {
              switch ( v26 )
              {
                case 0x452412u:
                  v76 = gte_regs.data[4].s16.lo;
                  v77 = gte_regs.data[4].s16.hi;
                  v43 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[15];
                  break;
                case 0x450012u:
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[7].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x450412u:
                  v76 = gte_regs.data[4].s16.lo;
                  v77 = gte_regs.data[4].s16.hi;
                  v43 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[7];
                  break;
                case 0x452012u:
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                default:
                  goto LABEL_630;
              }
              goto LABEL_287;
            }
            if ( v26 == 4538386 )
            {
              v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
              v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.ctrl[22].u32
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
              v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                  + gte_regs.ctrl[23].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
              v42.u32 = -32768;
              goto LABEL_56;
            }
            if ( v26 != 4539410 )
              goto LABEL_630;
            v43 = gte_regs.data[5].s16.hi;
            v76 = gte_regs.data[4].s16.lo;
            v77 = gte_regs.data[4].s16.hi;
            goto LABEL_285;
          }
          v94 = gte_regs.data[4].s16.lo;
          v95 = gte_regs.data[4].s16.hi;
          v96 = gte_regs.data[5].s16.hi;
          v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi;
LABEL_304:
          v97 = v96 * gte_regs.ctrl[18].s16.lo + v94 * gte_regs.ctrl[18].s16.hi;
          v98 = v95 * gte_regs.ctrl[17].s16.lo;
          goto LABEL_305;
        }
        if ( v26 <= 0x484012 )
        {
          if ( v26 == 4734994 )
          {
            v26 = gte_regs.ctrl[21].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            v39 = gte_regs.ctrl[22].u32
                + ((gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
            v41 = gte_regs.ctrl[23].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[4].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[3].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[3].s16.hi) >> 12);
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= 0x480412 )
          {
            if ( v26 != 4719634 )
            {
              if ( v26 == 4579346 )
              {
                v94 = gte_regs.data[10].s16.hi;
                v95 = gte_regs.data[9].s16.hi;
                v96 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi;
                goto LABEL_304;
              }
              if ( v26 == 4580370 )
              {
                v90 = gte_regs.data[10].s16.hi;
                v91 = gte_regs.data[9].s16.hi;
                v53 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi;
                goto LABEL_301;
              }
              if ( v26 != 4718610 )
                goto LABEL_630;
              v99 = gte_regs.data[0].s16.lo;
              v100 = gte_regs.data[0].s16.hi;
              v101 = gte_regs.data[1].s16.hi;
              v102 = gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi;
              goto LABEL_296;
            }
            v109 = gte_regs.data[1].s16.hi;
            v110 = gte_regs.data[0].s16.lo;
            v111 = gte_regs.data[0].s16.hi;
LABEL_307:
            v26 = gte_regs.ctrl[5].u32
                + ((v109 * gte_regs.ctrl[1].s16.hi + v110 * gte_regs.ctrl[0].s16.lo + v111 * gte_regs.ctrl[0].s16.hi) >> 12);
            v112 = v111 * gte_regs.ctrl[1].s16.lo + v109 * gte_regs.ctrl[2].s16.lo;
            v113 = v110 * gte_regs.ctrl[2].s16.hi;
LABEL_308:
            v63 = gte_regs.ctrl[6].u32 + ((v113 + v112) >> 12);
            v114 = v111 * gte_regs.ctrl[3].s16.hi;
            v115 = v110 * gte_regs.ctrl[3].s16.lo;
            v116 = gte_regs.ctrl[4].s16.hi;
            goto LABEL_309;
          }
          if ( v26 == 4726802 )
          {
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            v39 = gte_regs.ctrl[14].u32
                + ((gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
            v41 = gte_regs.ctrl[15].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[4].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[3].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[3].s16.hi) >> 12);
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 != 4727826 )
            goto LABEL_630;
          v118 = gte_regs.data[1].s16.hi;
          lo = gte_regs.data[0].s16.lo;
          hi = gte_regs.data[0].s16.hi;
          goto LABEL_313;
        }
        if ( v26 > 0x488012 )
        {
          if ( v26 != 4752402 )
          {
            if ( v26 != 4759570 )
              goto LABEL_630;
            v101 = gte_regs.data[3].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            v108 = gte_regs.ctrl[15];
            v39 = gte_regs.ctrl[14].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
            v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[3].s16.hi;
            v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[3].s16.lo;
            v107 = gte_regs.ctrl[4].s16.hi;
            goto LABEL_299;
          }
          v110 = gte_regs.data[2].s16.lo;
          v111 = gte_regs.data[2].s16.hi;
          v109 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.ctrl[5].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          v112 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          v113 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_308;
        }
        if ( v26 == 4751378 )
        {
          v99 = gte_regs.data[2].s16.lo;
          v100 = gte_regs.data[2].s16.hi;
          v101 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.ctrl[5].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          v103 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          v104 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_297;
        }
        if ( v26 != 4736018 )
        {
          if ( v26 != 4743186 )
          {
            if ( v26 != 4744210 )
              goto LABEL_630;
            v127 = gte_regs.data[1].s16.hi;
            v128 = gte_regs.data[0].s16.lo;
            v129 = gte_regs.data[0].s16.hi;
LABEL_324:
            v130 = v129 * gte_regs.ctrl[1].s16.lo + v127 * gte_regs.ctrl[2].s16.lo;
            v26 = (v127 * gte_regs.ctrl[1].s16.hi + v128 * gte_regs.ctrl[0].s16.lo + v129 * gte_regs.ctrl[0].s16.hi) >> 12;
            v131 = v128 * gte_regs.ctrl[2].s16.hi;
LABEL_325:
            v63 = (v131 + v130) >> 12;
            v41 = (v127 * gte_regs.ctrl[4].s16.hi + v128 * gte_regs.ctrl[3].s16.lo + v129 * gte_regs.ctrl[3].s16.hi) >> 12;
            goto LABEL_102;
          }
          v132 = gte_regs.data[1].s16.hi;
          v133 = gte_regs.data[0].s16.lo;
          v134 = gte_regs.data[0].s16.hi;
          goto LABEL_327;
        }
        v141 = gte_regs.data[1].s16.hi;
        v142 = gte_regs.data[0].s16.lo;
        v143 = gte_regs.data[0].s16.hi;
LABEL_331:
        v26 = gte_regs.ctrl[21].u32
            + ((v141 * gte_regs.ctrl[1].s16.hi + v142 * gte_regs.ctrl[0].s16.lo + v143 * gte_regs.ctrl[0].s16.hi) >> 12);
        v144 = v143 * gte_regs.ctrl[1].s16.lo + v141 * gte_regs.ctrl[2].s16.lo;
        v145 = v142 * gte_regs.ctrl[2].s16.hi;
LABEL_332:
        v63 = gte_regs.ctrl[22].u32 + ((v145 + v144) >> 12);
        v146 = v143 * gte_regs.ctrl[3].s16.hi;
        v147 = v142 * gte_regs.ctrl[3].s16.lo;
        v148 = gte_regs.ctrl[4].s16.hi;
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
              v101 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v39 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              v107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_298;
            }
            if ( v26 <= 0x49A012 )
            {
              if ( v26 == 4825106 )
              {
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[3].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[3].s16.lo;
                v107 = gte_regs.ctrl[4].s16.hi;
                goto LABEL_299;
              }
              if ( v26 > 0x492412 )
              {
                if ( v26 > 0x496412 )
                {
                  if ( v26 == 4816914 )
                  {
                    v99 = gte_regs.data[10].s16.hi;
                    v100 = gte_regs.data[9].s16.hi;
                    v101 = gte_regs.data[11].s16.hi;
                    v102 = gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                         + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                         + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi;
LABEL_296:
                    v26 = gte_regs.ctrl[5].u32 + (v102 >> 12);
                    v103 = v100 * gte_regs.ctrl[1].s16.lo + v101 * gte_regs.ctrl[2].s16.lo;
                    v104 = v99 * gte_regs.ctrl[2].s16.hi;
LABEL_297:
                    v39 = gte_regs.ctrl[6].u32 + ((v104 + v103) >> 12);
                    v105 = v100 * gte_regs.ctrl[3].s16.hi;
                    v106 = v99 * gte_regs.ctrl[3].s16.lo;
                    v107 = gte_regs.ctrl[4].s16.hi;
LABEL_298:
                    v108 = gte_regs.ctrl[7];
LABEL_299:
                    v41 = v108.u32 + ((v101 * v107 + v106 + v105) >> 12);
                    v42.u32 = -32768;
                    goto LABEL_56;
                  }
                  if ( v26 != 4817938 )
                    goto LABEL_630;
                  v109 = gte_regs.data[11].s16.hi;
                  v110 = gte_regs.data[10].s16.hi;
                  v111 = gte_regs.data[9].s16.hi;
                  goto LABEL_307;
                }
                if ( v26 == 4809746 )
                {
                  v128 = gte_regs.data[4].s16.lo;
                  v129 = gte_regs.data[4].s16.hi;
                  v127 = gte_regs.data[5].s16.hi;
                  v130 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v131 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_325;
                }
                if ( v26 == 4800530 )
                {
                  v101 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v108 = gte_regs.ctrl[23];
                  v39 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                  v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[3].s16.hi;
                  v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[3].s16.lo;
                  v107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
                }
                if ( v26 != 4801554 )
                {
                  if ( v26 != 4808722 )
                    goto LABEL_630;
                  v133 = gte_regs.data[4].s16.lo;
                  v134 = gte_regs.data[4].s16.hi;
                  v132 = gte_regs.data[5].s16.hi;
                  v135 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v136 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_328;
                }
                v142 = gte_regs.data[4].s16.lo;
                v143 = gte_regs.data[4].s16.hi;
                v141 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                v144 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                v145 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              }
              else
              {
                if ( v26 == 4793362 )
                {
                  lo = gte_regs.data[4].s16.lo;
                  hi = gte_regs.data[4].s16.hi;
                  v118 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.ctrl[13].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v121 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v122 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_314;
                }
                if ( v26 > 0x48E412 )
                {
                  if ( v26 == 4784146 )
                  {
                    v99 = gte_regs.data[4].s16.lo;
                    v100 = gte_regs.data[4].s16.hi;
                    v101 = gte_regs.data[5].s16.hi;
                    v26 = gte_regs.ctrl[5].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                    v103 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                         + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                    v104 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                    goto LABEL_297;
                  }
                  if ( v26 != 4785170 )
                  {
                    if ( v26 != 4792338 )
                      goto LABEL_630;
                    v101 = gte_regs.data[5].s16.hi;
                    v26 = gte_regs.ctrl[13].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                    v108 = gte_regs.ctrl[15];
                    v39 = gte_regs.ctrl[14].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                    v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[3].s16.hi;
                    v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[3].s16.lo;
                    v107 = gte_regs.ctrl[4].s16.hi;
                    goto LABEL_299;
                  }
                  v110 = gte_regs.data[4].s16.lo;
                  v111 = gte_regs.data[4].s16.hi;
                  v109 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.ctrl[5].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v112 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v113 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_308;
                }
                if ( v26 == 4776978 )
                {
                  v128 = gte_regs.data[2].s16.lo;
                  v129 = gte_regs.data[2].s16.hi;
                  v127 = gte_regs.data[3].s16.hi;
                  v130 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v131 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_325;
                }
                if ( v26 == 4767762 )
                {
                  v101 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v108 = gte_regs.ctrl[23];
                  v39 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                  v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[3].s16.hi;
                  v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[3].s16.lo;
                  v107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
                }
                if ( v26 != 4768786 )
                {
                  if ( v26 != 4775954 )
                    goto LABEL_630;
                  v133 = gte_regs.data[2].s16.lo;
                  v134 = gte_regs.data[2].s16.hi;
                  v132 = gte_regs.data[3].s16.hi;
                  v135 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v136 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_328;
                }
                v142 = gte_regs.data[2].s16.lo;
                v143 = gte_regs.data[2].s16.hi;
                v141 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                v144 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                v145 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
              }
              goto LABEL_332;
            }
            if ( v26 <= 0x4A0412 )
            {
              if ( v26 == 4850706 )
              {
                v109 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v63 = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v114 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v115 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v116 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_309;
              }
              if ( v26 > 0x49E012 )
              {
                if ( v26 != 4842514 )
                {
                  if ( v26 != 4849682 )
                    goto LABEL_630;
                  v101 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.ctrl[5].u32
                      + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                  v39 = gte_regs.ctrl[6].u32
                      + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                  v105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v107 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_298;
                }
                v127 = gte_regs.data[11].s16.hi;
                v128 = gte_regs.data[10].s16.hi;
                v129 = gte_regs.data[9].s16.hi;
                goto LABEL_324;
              }
              switch ( v26 )
              {
                case 0x49E012u:
                  v132 = gte_regs.data[11].s16.hi;
                  v133 = gte_regs.data[10].s16.hi;
                  v134 = gte_regs.data[9].s16.hi;
LABEL_327:
                  v135 = v134 * gte_regs.ctrl[1].s16.lo + v132 * gte_regs.ctrl[2].s16.lo;
                  v26 = (v132 * gte_regs.ctrl[1].s16.hi + v133 * gte_regs.ctrl[0].s16.lo
                                                        + v134 * gte_regs.ctrl[0].s16.hi) >> 12;
                  v136 = v133 * gte_regs.ctrl[2].s16.hi;
LABEL_328:
                  v137 = v136 + v135;
                  v138 = v134 * gte_regs.ctrl[3].s16.hi;
                  v139 = v133 * gte_regs.ctrl[3].s16.lo;
                  v140 = gte_regs.ctrl[4].s16.hi;
LABEL_329:
                  v39 = v137 >> 12;
                  v41 = (v132 * v140 + v139 + v138) >> 12;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x49A412u:
                  v118 = gte_regs.data[11].s16.hi;
                  lo = gte_regs.data[10].s16.hi;
                  hi = gte_regs.data[9].s16.hi;
LABEL_313:
                  v26 = gte_regs.ctrl[13].u32
                      + ((v118 * gte_regs.ctrl[1].s16.hi + lo * gte_regs.ctrl[0].s16.lo + hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v121 = hi * gte_regs.ctrl[1].s16.lo + v118 * gte_regs.ctrl[2].s16.lo;
                  v122 = lo * gte_regs.ctrl[2].s16.hi;
LABEL_314:
                  v63 = gte_regs.ctrl[14].u32 + ((v122 + v121) >> 12);
                  v123 = hi * gte_regs.ctrl[3].s16.hi;
                  v124 = lo * gte_regs.ctrl[3].s16.lo;
                  v125 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_315;
                case 0x49C012u:
                  v101 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v108 = gte_regs.ctrl[23];
                  v39 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
                  v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[3].s16.hi;
                  v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[3].s16.lo;
                  v107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
              }
              if ( v26 != 4834322 )
                goto LABEL_630;
              v141 = gte_regs.data[11].s16.hi;
              v142 = gte_regs.data[10].s16.hi;
              v143 = gte_regs.data[9].s16.hi;
              goto LABEL_331;
            }
            if ( v26 <= 0x4A4412 )
            {
              if ( v26 == 4867090 )
              {
                v141 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v63 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v146 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v147 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v148 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_333;
              }
              if ( v26 == 4857874 )
              {
                v101 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              if ( v26 != 4858898 )
              {
                if ( v26 != 4866066 )
                  goto LABEL_630;
                v101 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[23];
                v39 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              v118 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v123 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
              v124 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
              v125 = gte_regs.ctrl[12].s16.hi;
LABEL_315:
              v126 = v118 * v125 + v124 + v123;
              v68 = gte_regs.ctrl[15];
              v67 = v126 >> 12;
              goto LABEL_101;
            }
            if ( v26 == 4874258 )
            {
              v132 = gte_regs.data[1].s16.hi;
              v137 = gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo;
              v138 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
              v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
              v139 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
              v140 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_329;
            }
            if ( v26 != 4875282 )
              goto LABEL_630;
            v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
            v63 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
            v41 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
LABEL_102:
            gte_regs.data[25].u32 = v26;
            gte_regs.data[26].u32 = v63;
            gte_regs.data[27].u32 = v41;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = v26;
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9].u32 = 0;
            }
            if ( v63 >= 0 )
            {
              if ( v63 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = v63;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0;
            }
            if ( v41 >= 0 )
              goto LABEL_541;
LABEL_573:
            LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
            gte_regs.data[11].u32 = 0;
            gte_regs.ctrl[31].u32 |= 0x400000u;
            return v26;
          }
          if ( v26 <= 0x4B6012 )
          {
            if ( v26 == 4939794 )
            {
              v132 = gte_regs.data[5].s16.hi;
              v137 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                   + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
              v138 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                   + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
              v139 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v140 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_329;
            }
            if ( v26 <= 0x4AE412 )
            {
              if ( v26 == 4908050 )
              {
                v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v63 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                v41 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              }
              if ( v26 <= 0x4AC012 )
              {
                switch ( v26 )
                {
                  case 0x4AC012u:
                    v101 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.ctrl[21].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    v108 = gte_regs.ctrl[23];
                    v39 = gte_regs.ctrl[22].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v107 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_299;
                  case 0x4A8412u:
                    v109 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.ctrl[5].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    v63 = gte_regs.ctrl[6].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    v114 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v115 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v116 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_309;
                  case 0x4AA012u:
                    v101 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.ctrl[13].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    v108 = gte_regs.ctrl[15];
                    v39 = gte_regs.ctrl[14].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v107 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_299;
                }
                if ( v26 != 4891666 )
                  goto LABEL_630;
                v118 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v63 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v123 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                v124 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                v125 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_315;
              }
              if ( v26 != 4899858 )
              {
                if ( v26 != 4907026 )
                  goto LABEL_630;
                v132 = gte_regs.data[3].s16.hi;
                v137 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                v138 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v139 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                v140 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_329;
              }
              v141 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v146 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              v147 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              v148 = gte_regs.ctrl[12].s16.hi;
LABEL_333:
              v149 = v141 * v148 + v147 + v146;
              v68 = gte_regs.ctrl[23];
              v67 = v149 >> 12;
              goto LABEL_101;
            }
            if ( v26 > 0x4B2412 )
            {
              if ( v26 == 4931602 )
              {
                v101 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[23];
                v39 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              if ( v26 != 4932626 )
                goto LABEL_630;
              v141 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v146 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v147 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v148 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_333;
            }
            if ( v26 == 4924434 )
            {
              v118 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v123 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v124 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v125 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_315;
            }
            if ( v26 == 4915218 )
            {
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v39 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_298;
            }
            if ( v26 != 4916242 )
            {
              if ( v26 != 4923410 )
                goto LABEL_630;
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v108 = gte_regs.ctrl[15];
              v39 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_299;
            }
            v109 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
            v63 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
            v114 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
            v115 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
            v116 = gte_regs.ctrl[12].s16.hi;
LABEL_309:
            v117 = v109 * v116 + v115 + v114;
            v68 = gte_regs.ctrl[7];
            v67 = v117 >> 12;
            goto LABEL_101;
          }
          if ( v26 <= 0x4BC412 )
          {
            if ( v26 == 4965394 )
            {
              v141 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v146 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
              v147 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
              v148 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_333;
            }
            if ( v26 > 0x4BA012 )
            {
              if ( v26 != 4957202 )
              {
                if ( v26 != 4964370 )
                  goto LABEL_630;
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[23];
                v39 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              v118 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v123 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
              v124 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
              v125 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_315;
            }
            switch ( v26 )
            {
              case 0x4BA012u:
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              case 0x4B6412u:
                v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v63 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                v41 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              case 0x4B8012u:
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v39 = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_298;
            }
            if ( v26 != 4949010 )
              goto LABEL_630;
            v109 = gte_regs.data[11].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
            v63 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
            v114 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
            v115 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
            v116 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_309;
          }
          if ( v26 <= 0x4C0412 )
          {
            if ( v26 != 4981778 )
            {
              if ( v26 == 4972562 )
              {
                v132 = gte_regs.data[11].s16.hi;
                v137 = gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo;
                v138 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v139 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v140 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_329;
              }
              if ( v26 == 4973586 )
              {
                v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v63 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                v41 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              }
              if ( v26 != 4980754 )
                goto LABEL_630;
              v150 = gte_regs.data[0].s16.lo;
              v151 = gte_regs.data[0].s16.hi;
              v101 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v152 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              v153 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_528:
              v39 = gte_regs.ctrl[6].u32 + ((v153 + v152) >> 12);
              v105 = v151 * gte_regs.ctrl[19].s16.hi;
              v106 = v150 * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_298;
            }
            v154 = gte_regs.data[0].s16.lo;
            v155 = gte_regs.data[0].s16.hi;
            v109 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v156 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            v157 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
            goto LABEL_526;
          }
          if ( (int *)v26 != (int *)((char *)&spu_ram[93124] + 2) )
          {
            if ( (int *)v26 != (int *)((char *)&spu_ram[93380] + 2) )
              goto LABEL_630;
            v158 = gte_regs.data[0].s16.lo;
            v159 = gte_regs.data[0].s16.hi;
            v118 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v160 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            v161 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
            goto LABEL_506;
          }
          v162 = gte_regs.data[0].s16.lo;
          v163 = gte_regs.data[0].s16.hi;
          v101 = gte_regs.data[1].s16.hi;
          v26 = gte_regs.ctrl[13].u32
              + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
          v164 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
          v165 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_530:
          v108 = gte_regs.ctrl[15];
          v39 = gte_regs.ctrl[14].u32 + ((v165 + v164) >> 12);
          v105 = v163 * gte_regs.ctrl[19].s16.hi;
          v106 = v162 * gte_regs.ctrl[19].s16.lo;
          v107 = gte_regs.ctrl[20].s16.hi;
          goto LABEL_299;
        }
        v166 = gte_regs.data[0].s16.lo;
        v167 = gte_regs.data[0].s16.hi;
        v101 = gte_regs.data[1].s16.hi;
        v26 = gte_regs.ctrl[21].u32
            + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
        v168 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
        v169 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_519:
        v108 = gte_regs.ctrl[23];
        v39 = gte_regs.ctrl[22].u32 + ((v169 + v168) >> 12);
        v105 = v167 * gte_regs.ctrl[19].s16.hi;
        v106 = v166 * gte_regs.ctrl[19].s16.lo;
        v107 = gte_regs.ctrl[20].s16.hi;
        goto LABEL_299;
      }
      if ( v26 <= 0x680029 )
      {
        if ( v26 == 6815785 )
        {
          LOBYTE(v26) = gte_dcpl();
          return v26;
        }
        if ( v26 <= 0x4D2412 )
        {
          if ( v26 == 5055506 )
          {
            v158 = gte_regs.data[4].s16.lo;
            v159 = gte_regs.data[4].s16.hi;
            v118 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v160 = gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi;
            v161 = gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
LABEL_506:
            v63 = gte_regs.ctrl[14].u32 + ((v161 + v160) >> 12);
            v123 = v159 * gte_regs.ctrl[19].s16.hi;
            v124 = v158 * gte_regs.ctrl[19].s16.lo;
            v125 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_315;
          }
          if ( v26 <= 0x4CC012 )
          {
            if ( v26 == 5029906 )
            {
              v101 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v108 = gte_regs.ctrl[23];
              v39 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_299;
            }
            if ( v26 > 0x4C8012 )
            {
              if ( v26 == 5014546 )
              {
                v109 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
                v63 = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
                v114 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
                v115 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
                v116 = gte_regs.ctrl[20].s16.hi;
                goto LABEL_309;
              }
              if ( v26 == 5021714 )
              {
                v101 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
                v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
                v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
                v107 = gte_regs.ctrl[20].s16.hi;
                goto LABEL_299;
              }
              if ( v26 != 5022738 )
                goto LABEL_630;
              v118 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v123 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              v124 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              v125 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_315;
            }
            if ( v26 == 5013522 )
            {
              v101 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v39 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_298;
            }
            if ( v26 != 4998162 )
            {
              if ( v26 != 5005330 )
              {
                if ( v26 != 5006354 )
                  goto LABEL_630;
                v170 = gte_regs.data[0].s16.lo;
                v171 = gte_regs.data[0].s16.hi;
                v172 = gte_regs.data[1].s16.hi;
                v173 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                     + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                     + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                     + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
                v174 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                goto LABEL_522;
              }
              v175 = gte_regs.data[0].s16.lo;
              v176 = gte_regs.data[0].s16.hi;
              v132 = gte_regs.data[1].s16.hi;
              v177 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
              v178 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_516:
              v137 = v178 + v177;
              v138 = v176 * gte_regs.ctrl[19].s16.hi;
              v139 = v175 * gte_regs.ctrl[19].s16.lo;
              v140 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_329;
            }
            v179 = gte_regs.data[0].s16.lo;
            v180 = gte_regs.data[0].s16.hi;
            v141 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.ctrl[21].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v181 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            v182 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_537:
            v63 = gte_regs.ctrl[22].u32 + ((v182 + v181) >> 12);
            v146 = v180 * gte_regs.ctrl[19].s16.hi;
            v147 = v179 * gte_regs.ctrl[19].s16.lo;
            v148 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_333;
          }
          if ( v26 > 0x4D0012 )
          {
            if ( v26 != 5047314 )
            {
              if ( v26 != 5054482 )
                goto LABEL_630;
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v108 = gte_regs.ctrl[15];
              v39 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
              v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_299;
            }
            v109 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v63 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            v114 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
            v115 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
            v116 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_309;
          }
          if ( v26 == 5046290 )
          {
            v101 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v39 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
            v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
            v107 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_298;
          }
          if ( v26 == 5030930 )
          {
            v141 = gte_regs.data[3].s16.hi;
            v26 = gte_regs.ctrl[21].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v63 = gte_regs.ctrl[22].u32
                + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            v146 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
            v147 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
            v148 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_333;
          }
          if ( v26 != 5038098 )
          {
            if ( v26 != 5039122 )
              goto LABEL_630;
            v172 = gte_regs.data[3].s16.hi;
            v170 = gte_regs.data[2].s16.lo;
            v171 = gte_regs.data[2].s16.hi;
            goto LABEL_521;
          }
          v132 = gte_regs.data[3].s16.hi;
          v175 = gte_regs.data[2].s16.lo;
          v176 = gte_regs.data[2].s16.hi;
          goto LABEL_515;
        }
        if ( v26 <= 0x4DA012 )
        {
          if ( v26 == 5087250 )
          {
            v162 = gte_regs.data[10].s16.hi;
            v163 = gte_regs.data[9].s16.hi;
            v101 = gte_regs.data[11].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v164 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
            v165 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
            goto LABEL_530;
          }
          if ( v26 > 0x4D6412 )
          {
            if ( v26 == 5079058 )
            {
              v150 = gte_regs.data[10].s16.hi;
              v151 = gte_regs.data[9].s16.hi;
              v101 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v152 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              v153 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_528;
            }
            if ( v26 != 5080082 )
              goto LABEL_630;
            v154 = gte_regs.data[10].s16.hi;
            v155 = gte_regs.data[9].s16.hi;
            v109 = gte_regs.data[11].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v156 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
            v157 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
LABEL_526:
            v63 = gte_regs.ctrl[6].u32 + ((v157 + v156) >> 12);
            v114 = v155 * gte_regs.ctrl[19].s16.hi;
            v115 = v154 * gte_regs.ctrl[19].s16.lo;
            v116 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_309;
          }
          switch ( v26 )
          {
            case 0x4D6412u:
              v172 = gte_regs.data[5].s16.hi;
              v170 = gte_regs.data[4].s16.lo;
              v171 = gte_regs.data[4].s16.hi;
LABEL_521:
              v173 = v172 * gte_regs.ctrl[18].s16.lo + v170 * gte_regs.ctrl[18].s16.hi;
              v26 = (v172 * gte_regs.ctrl[17].s16.hi + v170 * gte_regs.ctrl[16].s16.lo + v171 * gte_regs.ctrl[16].s16.hi) >> 12;
              v174 = v171 * gte_regs.ctrl[17].s16.lo;
LABEL_522:
              v63 = (v174 + v173) >> 12;
              v41 = (v172 * gte_regs.ctrl[20].s16.hi + v170 * gte_regs.ctrl[19].s16.lo + v171 * gte_regs.ctrl[19].s16.hi) >> 12;
              goto LABEL_102;
            case 0x4D4012u:
              v166 = gte_regs.data[4].s16.lo;
              v167 = gte_regs.data[4].s16.hi;
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v168 = gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi;
              v169 = gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_519;
            case 0x4D4412u:
              v141 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v146 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
              v147 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
              v148 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_333;
          }
          if ( v26 != 5070866 )
            goto LABEL_630;
          v132 = gte_regs.data[5].s16.hi;
          v175 = gte_regs.data[4].s16.lo;
          v176 = gte_regs.data[4].s16.hi;
LABEL_515:
          v177 = v132 * gte_regs.ctrl[18].s16.lo + v175 * gte_regs.ctrl[18].s16.hi;
          v26 = (v132 * gte_regs.ctrl[17].s16.hi + v175 * gte_regs.ctrl[16].s16.lo + v176 * gte_regs.ctrl[16].s16.hi) >> 12;
          v178 = v176 * gte_regs.ctrl[17].s16.lo;
          goto LABEL_516;
        }
        if ( v26 <= 0x4DE012 )
        {
          switch ( v26 )
          {
            case 0x4DE012u:
              v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
              v183 = (gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12;
              v41 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
              v42.u32 = -32768;
              gte_regs.data[25].u32 = v26;
              gte_regs.data[26].u32 = v183;
              gte_regs.data[27].u32 = v41;
              if ( (int)v26 >= -32768 )
              {
                if ( (int)v26 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
                }
                else
                {
                  gte_regs.ctrl[31].u32 = -2130706432;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = -32768;
              }
              if ( v183 >= -32768 )
              {
                if ( v183 <= 0x7FFF )
                {
                  gte_regs.data[10].u32 = v183;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( v41 >= -32768 )
                goto LABEL_541;
              goto LABEL_558;
            case 0x4DA412u:
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12);
              v68 = gte_regs.ctrl[15];
              v67 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
              goto LABEL_101;
            case 0x4DC012u:
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v39 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12);
              v41 = gte_regs.ctrl[23].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
              v42.u32 = -32768;
              goto LABEL_56;
          }
          if ( v26 != 5096466 )
            goto LABEL_630;
          v179 = gte_regs.data[10].s16.hi;
          v180 = gte_regs.data[9].s16.hi;
          v141 = gte_regs.data[11].s16.hi;
          v26 = gte_regs.ctrl[21].u32
              + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
          v181 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
          v182 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
          goto LABEL_537;
        }
        if ( v26 == 5104658 )
        {
          v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
               + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
          v184 = (gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12;
          v41 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
               + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
          gte_regs.data[25].u32 = v26;
          gte_regs.data[26].u32 = v184;
          gte_regs.data[27].u32 = v41;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 = -2130706432;
            gte_regs.data[9].u32 = 0;
          }
          if ( v184 >= 0 )
          {
            if ( v184 <= 0x7FFF )
            {
              gte_regs.data[10].u32 = v184;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0;
          }
          if ( v41 >= 0 )
            goto LABEL_541;
          goto LABEL_573;
        }
        if ( v26 != 5767213 )
          goto LABEL_630;
LABEL_694:
        gte_regs.data[24].u32 = gte_regs.ctrl[29].s16.hi
                              * (gte_regs.data[17].u16.hi + gte_regs.data[18].u16.hi + gte_regs.data[19].u16.hi);
        v26 = gte_regs.data[24].s32 >> 12;
        if ( gte_regs.data[24].s32 >> 12 >= 0 )
        {
          if ( (int)v26 <= 0xFFFF )
          {
            gte_regs.data[7].u16.hi = gte_regs.data[24].s32 >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80040000;
            gte_regs.data[7].u16.hi = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80040000;
          gte_regs.data[7].u16.hi = 0;
        }
        return v26;
      }
      if ( v26 > 0x118043F )
      {
        if ( v26 <= 0x178000C )
        {
          if ( v26 == 24641548 )
          {
            LOBYTE(v26) = gte_op_shifted().u32;
            return v26;
          }
          if ( v26 <= 0x158002D )
          {
            if ( v26 != 22544429 )
            {
              if ( v26 == 19399700 )
              {
                LOBYTE(v26) = gte_cdp();
                return v26;
              }
              if ( v26 == 20448284 )
              {
                LOBYTE(v26) = gte_cc();
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
              LOBYTE(v26) = gte_op();
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
              v22.u32 = ((gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12) + gte_regs.data[26].u32;
              v23.u32 = ((gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12) + gte_regs.data[27].u32;
              gte_regs.data[25].u32 += (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
              gte_regs.data[26] = v22;
              gte_regs.data[27] = v23;
              if ( gte_regs.data[25].s32 >= -32768 )
              {
                if ( gte_regs.data[25].s32 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = gte_regs.data[25].u32;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x81000000;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = -32768;
              }
              if ( v22.s32 >= -32768 )
              {
                if ( v22.s32 <= 0x7FFF )
                {
                  gte_regs.data[10] = v22;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( v23.s32 >= -32768 )
              {
                if ( v23.s32 <= 0x7FFF )
                {
                  gte_regs.data[11] = v23;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x400000u;
                  gte_regs.data[11].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = -32768;
              }
              gte_regs.data[20].u32 = gte_regs.data[21].u32;
              v26 = gte_regs.data[25].s32 >> 4;
              gte_regs.data[21].u32 = gte_regs.data[22].u32;
              v24 = v22.s32 >> 4;
              v25 = v23.s32 >> 4;
              dword_8A8004 = gte_regs.data[25].s32 >> 4;
              dword_8A8008 = v24;
              dword_8A800C = v25;
              if ( gte_regs.data[25].s32 >> 4 >= 0 )
              {
                if ( (int)v26 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x200000u;
                  LOBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v24 >= 0 )
              {
                if ( v24 <= 255 )
                {
                  HIBYTE(gte_regs.data[22].u16.hi) = v24;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x100000u;
                  HIBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v25 >= 0 )
              {
                if ( v25 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].s16.lo) = v25;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80000u;
                  LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
                  LOBYTE(gte_regs.data[22].s16.lo) = -1;
                }
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              else
              {
                LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(gte_regs.data[22].s16.lo) = 0;
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
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
        v18.u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi + gte_regs.data[26].u32;
        v19.u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi + gte_regs.data[27].u32;
        gte_regs.data[25].u32 += gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
        gte_regs.data[26] = v18;
        gte_regs.data[27] = v19;
        if ( gte_regs.data[25].s32 >= -32768 )
        {
          if ( gte_regs.data[25].s32 <= 0x7FFF )
          {
            gte_regs.data[9].u32 = gte_regs.data[25].u32;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x81000000;
          gte_regs.data[9].u32 = -32768;
        }
        if ( v18.s32 >= -32768 )
        {
          if ( v18.s32 <= 0x7FFF )
          {
            gte_regs.data[10] = v18;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80800000;
          gte_regs.data[10].u32 = -32768;
        }
        if ( v19.s32 >= -32768 )
        {
          if ( v19.s32 <= 0x7FFF )
          {
            gte_regs.data[11] = v19;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x400000u;
          gte_regs.data[11].u32 = -32768;
        }
        gte_regs.data[20].u32 = gte_regs.data[21].u32;
        v26 = gte_regs.data[25].s32 >> 4;
        gte_regs.data[21].u32 = gte_regs.data[22].u32;
        v20 = v18.s32 >> 4;
        v21 = v19.s32 >> 4;
        dword_8A8004 = gte_regs.data[25].s32 >> 4;
        dword_8A8008 = v20;
        dword_8A800C = v21;
        if ( gte_regs.data[25].s32 >> 4 >= 0 )
        {
          if ( (int)v26 <= 255 )
          {
            LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x200000u;
            LOBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x200000u;
          LOBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v20 >= 0 )
        {
          if ( v20 <= 255 )
          {
            HIBYTE(gte_regs.data[22].u16.hi) = v20;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x100000u;
            HIBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x100000u;
          HIBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v21 >= 0 )
        {
          if ( v21 <= 255 )
          {
            LOBYTE(gte_regs.data[22].s16.lo) = v21;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80000u;
            LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
            LOBYTE(gte_regs.data[22].s16.lo) = -1;
          }
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        else
        {
          LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
          gte_regs.ctrl[31].u32 |= 0x80000u;
          LOBYTE(gte_regs.data[22].s16.lo) = 0;
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        return v26;
      }
      if ( v26 == 18351167 )
      {
        LOBYTE(v26) = gte_ncct();
        return v26;
      }
      if ( v26 <= 0xA80428 )
      {
        if ( v26 == 11011112 )
        {
          v26 = (gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi) >> 12;
          v6 = (gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi) >> 12;
          v7 = (gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi) >> 12;
          gte_regs.data[25].u32 = v26;
          gte_regs.data[26].u32 = v6;
          gte_regs.data[27].u32 = v7;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              gte_regs.data[9].u32 = (gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x81000000;
              gte_regs.data[9].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0;
          }
          if ( v6 >= 0 )
          {
            if ( v6 <= 0x7FFF )
            {
              gte_regs.data[10].u32 = (gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0;
          }
          if ( v7 >= 0 )
          {
            if ( v7 <= 0x7FFF )
            {
              gte_regs.data[11].u32 = (gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0;
          }
          return v26;
        }
        if ( v26 <= 0x980011 )
        {
          if ( v26 == 9961489 )
          {
            gte_regs.data[25].u32 = gte_regs.data[9].s16.hi
                                  + ((gte_regs.data[8].s16.hi
                                    * gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - gte_regs.data[9].s16.hi)) >> 12);
            gte_regs.data[26].u32 = gte_regs.data[10].s16.hi
                                  + ((gte_regs.data[8].s16.hi
                                    * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - gte_regs.data[10].s16.hi)) >> 12);
            v0 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - gte_regs.data[11].s16.hi);
            v2.u32 = gte_regs.data[11].s16.hi + ((gte_regs.data[8].s16.hi * v0) >> 12);
            gte_regs.data[27] = v2;
            if ( gte_regs.data[25].s32 >= -32768 )
            {
              if ( gte_regs.data[25].s32 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = gte_regs.data[25].u32;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= v1;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= v1;
              gte_regs.data[9].u32 = -32768;
            }
            if ( gte_regs.data[26].s32 >= -32768 )
            {
              if ( gte_regs.data[26].s32 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = gte_regs.data[26].u32;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = -32768;
            }
            if ( v2.s32 >= -32768 )
            {
              if ( v2.s32 <= 0x7FFF )
              {
                gte_regs.data[11] = v2;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = -32768;
            }
            gte_regs.data[20].u32 = gte_regs.data[21].u32;
            v3 = gte_regs.data[26].s32 >> 4;
            v26 = v2.s32 >> 4;
            gte_regs.data[21].u32 = gte_regs.data[22].u32;
            dword_8A8004 = gte_regs.data[25].s32 >> 4;
            dword_8A8008 = gte_regs.data[26].s32 >> 4;
            dword_8A800C = v26;
            if ( gte_regs.data[25].s32 >> 4 >= 0 )
            {
              if ( gte_regs.data[25].s32 >> 4 <= 255 )
              {
                LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = -1;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x200000u;
              LOBYTE(gte_regs.data[22].u16.hi) = 0;
            }
            if ( v3 >= 0 )
            {
              if ( v3 <= 255 )
              {
                HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = -1;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x100000u;
              HIBYTE(gte_regs.data[22].u16.hi) = 0;
            }
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 255 )
              {
                LOBYTE(gte_regs.data[22].s16.lo) = v26;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
                LOBYTE(gte_regs.data[22].s16.lo) = -1;
              }
              HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
            }
            else
            {
              LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
              gte_regs.ctrl[31].u32 |= 0x80000u;
              LOBYTE(gte_regs.data[22].s16.lo) = 0;
              HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
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
              v8.u32 = gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
              v9.u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi;
              v10.u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi;
              gte_regs.data[25] = v8;
              gte_regs.data[26] = v9;
              gte_regs.data[27] = v10;
              if ( v8.s32 >= -32768 )
              {
                if ( v8.s32 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x81000000;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = -32768;
              }
              if ( v9.s32 >= -32768 )
              {
                if ( v9.s32 <= 0x7FFF )
                {
                  gte_regs.data[10].u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( v10.s32 >= -32768 )
              {
                if ( v10.s32 <= 0x7FFF )
                {
                  gte_regs.data[11].u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x400000u;
                  gte_regs.data[11].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = -32768;
              }
              gte_regs.data[20].u32 = gte_regs.data[21].u32;
              v26 = v8.s32 >> 4;
              gte_regs.data[21].u32 = gte_regs.data[22].u32;
              v11 = v9.s32 >> 4;
              v12 = v10.s32 >> 4;
              dword_8A8004 = v26;
              dword_8A8008 = v11;
              dword_8A800C = v12;
              if ( (v26 & 0x80000000) == 0 )
              {
                if ( (int)v26 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].u16.hi) = v26;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x200000u;
                  LOBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v11 >= 0 )
              {
                if ( v11 <= 255 )
                {
                  HIBYTE(gte_regs.data[22].u16.hi) = v11;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x100000u;
                  HIBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v12 >= 0 )
              {
                if ( v12 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].s16.lo) = v12;
                }
                else
                {
                  LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
                  gte_regs.ctrl[31].u32 |= 0x80000u;
                  LOBYTE(gte_regs.data[22].s16.lo) = -1;
                }
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(gte_regs.data[22].s16.lo) = 0;
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
                LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
              }
              return v26;
            }
LABEL_626:
            LOBYTE(v26) = gte_dpcs();
            return v26;
          }
LABEL_699:
          gte_regs.data[24].u32 = gte_regs.ctrl[30].s16.hi
                                * (gte_regs.data[16].u16.hi
                                 + gte_regs.data[17].u16.hi
                                 + gte_regs.data[18].u16.hi
                                 + gte_regs.data[19].u16.hi);
          v26 = gte_regs.data[24].s32 >> 12;
          if ( gte_regs.data[24].s32 >> 12 >= 0 )
          {
            if ( (int)v26 <= 0xFFFF )
            {
              gte_regs.data[7].u16.hi = gte_regs.data[24].s32 >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80040000;
              gte_regs.data[7].u16.hi = -1;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80040000;
            gte_regs.data[7].u16.hi = 0;
          }
          return v26;
        }
        if ( v26 != 9961533 )
        {
          if ( v26 == 10486824 )
          {
            v26 = gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi;
            v4.u32 = gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi;
            v5.u32 = gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi;
            gte_regs.data[25].u32 = v26;
            gte_regs.data[26] = v4;
            gte_regs.data[27] = v5;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x81000000;
              gte_regs.data[9].u32 = 0;
            }
            if ( v4.s32 >= 0 )
            {
              if ( v4.s32 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0;
            }
            if ( v5.s32 >= 0 )
            {
              if ( v5.s32 <= 0x7FFF )
              {
                gte_regs.data[11].u32 = gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = 0;
            }
            return v26;
          }
          goto LABEL_630;
        }
LABEL_735:
        v13 = (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
        v14 = (gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12;
        v15 = (gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12;
        gte_regs.data[25].u32 = v13;
        gte_regs.data[26].u32 = v14;
        gte_regs.data[27].u32 = v15;
        if ( v13 >= -32768 )
        {
          if ( v13 <= 0x7FFF )
          {
            gte_regs.data[9].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x81000000;
          gte_regs.data[9].u32 = -32768;
        }
        if ( v14 >= -32768 )
        {
          if ( v14 <= 0x7FFF )
          {
            gte_regs.data[10].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80800000;
          gte_regs.data[10].u32 = -32768;
        }
        if ( v15 >= -32768 )
        {
          if ( v15 <= 0x7FFF )
          {
            gte_regs.data[11].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x400000u;
          gte_regs.data[11].u32 = -32768;
        }
        gte_regs.data[20].u32 = gte_regs.data[21].u32;
        v26 = v13 >> 4;
        gte_regs.data[21].u32 = gte_regs.data[22].u32;
        v16 = v14 >> 4;
        v17 = v15 >> 4;
        dword_8A8004 = v26;
        dword_8A8008 = v16;
        dword_8A800C = v17;
        if ( (v26 & 0x80000000) == 0 )
        {
          if ( (int)v26 <= 255 )
          {
            LOBYTE(gte_regs.data[22].u16.hi) = v26;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x200000u;
            LOBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x200000u;
          LOBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v16 >= 0 )
        {
          if ( v16 <= 255 )
          {
            HIBYTE(gte_regs.data[22].u16.hi) = v16;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x100000u;
            HIBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x100000u;
          HIBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v17 >= 0 )
        {
          if ( v17 <= 255 )
          {
            LOBYTE(gte_regs.data[22].s16.lo) = v17;
          }
          else
          {
            LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
            gte_regs.ctrl[31].u32 |= 0x80000u;
            LOBYTE(gte_regs.data[22].s16.lo) = -1;
          }
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80000u;
          LOBYTE(gte_regs.data[22].s16.lo) = 0;
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
          LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
        }
        return v26;
      }
      if ( v26 <= 0xF8002A )
      {
        switch ( v26 )
        {
          case 0xF8002Au:
            LOBYTE(v26) = gte_dpct().u32;
            return v26;
          case 0xC8041Eu:
            LOBYTE(v26) = gte_ncs();
            return v26;
          case 0xD80420u:
            LOBYTE(v26) = gte_nct();
            return v26;
          case 0xE80413u:
            LOBYTE(v26) = gte_ncds();
            return v26;
        }
        goto LABEL_630;
      }
      if ( v26 == 0xF80416 )
      {
        LOBYTE(v26) = gte_ncdt();
        return v26;
      }
      if ( v26 == 0x108041B )
        goto LABEL_602;
LABEL_630:
      if ( gtrace )
        LOBYTE(v26) = dbg_print("CODE [%07x]\n", v26);
      return v26;
  }
}
