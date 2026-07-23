char *__cdecl dynarec_recompile_block(int a1)
{
  unsigned int v1; // eax
  int v2; // eax

  v1 = a1 - (_DWORD)dword_5164C4;
  if ( (unsigned int)(a1 - (_DWORD)dword_5164C4) >= 0x200000 )
    v1 -= 0x40600000;
  *(_DWORD *)reg_pc = v1;
  dynarec_compile(v1, 20480);
  if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v2 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v2 = *(_DWORD *)reg_pc & 0x1FFFFF;
  return (char *)dword_5164C4 + v2;
}

char *dynarec_hw_update()
{
  int v0; // eax
  unsigned int v2; // ecx
  int v3; // eax
  int v4; // eax
  unsigned int v5; // edx
  char v6; // al
  int v7; // edx
  int v8; // eax
  int v9; // eax

  dword_50C2B4[0] = 0;
  if ( (hw_update_counter & 0xC0000000) == 0x80000000 )
  {
    if ( (*(_DWORD *)int_reg & int_mask) != 0 )
      irq_cpu_interrupt();
    if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
      v0 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
    else
      v0 = *(_DWORD *)reg_pc & 0x1FFFFF;
    return (char *)dword_5164C4 + v0;
  }
  else
  {
    if ( (++dword_4FC4EC & 0x1F) == 0 )
      spu_async_update_cb(32 * dword_455940);
    mdec_timer_handler();
    gpu_sub_42E450();
    gpu_sub_42E650();
    hw_update_counter = dword_455940;
    ++dword_50C364;
    sub_42CA70();
    sub_42C9A0();
    if ( (int_reg[0] & 4) == 0 && sub_42C8B0() )
      *(_DWORD *)int_reg |= 4u;
    if ( dword_50C210 && (int_reg[1] & 2) == 0 )
    {
      *(_DWORD *)int_reg |= 0x200u;
      --dword_50C210;
    }
    if ( *(_DWORD *)dword_4FD878 )
    {
      *(_DWORD *)int_reg |= *(_DWORD *)dword_4FD878;
      *(_DWORD *)dword_4FD878 = 0;
    }
    else if ( *(_DWORD *)dword_4FD874 )
    {
      *(_DWORD *)dword_4FD878 = 128;
      *(_DWORD *)dword_4FD870 = *(_DWORD *)dword_4FD874;
      *(_DWORD *)dword_4FD874 = 0;
    }
    if ( sio_transfer_pending )
    {
      sio_transfer_pending = 0;
      sio_trigger_rx_ready_irq();
    }
    else if ( dword_4FD868 )
    {
      sio_transfer_pending = 128;
      sio_transfer_timeout = dword_4FD868;
      dword_4FD868 = 0;
    }
    v2 = dword_455940;
    v3 = 512;
    if ( (dword_50BFD4[0] & 0x100) == 0 )
      v3 = dword_455940;
    dword_50BFD0[0] += v3;
    if ( dword_50BFD0[0] >= (unsigned int)dword_50BFDC[0] )
    {
      dword_50BFD0[0] = 0;
      if ( (dword_50BFD4[0] & 0x50) == 0x50 )
        *(_DWORD *)int_reg |= 0x10u;
    }
    v4 = 1;
    if ( (dword_50BFE4 & 0x100) == 0 )
      v4 = dword_455940;
    dword_50BFE0 += v4;
    if ( dword_50BFE0 >= (unsigned int)dword_50BFEC )
    {
      dword_50BFE0 = 0;
      if ( (dword_50BFE4 & 0x50) == 0x50 )
        *(_DWORD *)int_reg |= 0x20u;
    }
    if ( (dword_50BFF4 & 1) == 0 && xenogears_trick_enabled )
    {
      if ( (dword_50BFF4 & 0x200) != 0 )
        v2 = (unsigned int)dword_455940 >> 3;
      v5 = v2 + dword_50BFF0;
      dword_50BFF0 = v5;
      if ( v5 >= dword_50BFFC )
      {
        dword_50BFF0 = v5 - dword_50BFFC;
        if ( (dword_50BFF4 & 0x50) == 0x50 )
          *(_DWORD *)int_reg |= 0x40u;
      }
    }
    v6 = int_mask;
    if ( dword_50C364 == dword_45593C - (byte_4FC4E6 != 0 ? 32 : 1) )
    {
      v7 = *(_DWORD *)int_reg | 1;
      *(_DWORD *)int_reg |= 1u;
      if ( (int_mask & 0x200) != 0 && forcespu && (dword_50C360 & 3) == 0 )
        *(_DWORD *)int_reg = v7 | 0x200;
    }
    if ( (int_mask & *(_DWORD *)int_reg) != 0 )
    {
      irq_cpu_interrupt();
      v6 = int_mask;
    }
    if ( dword_50C364 >= (unsigned int)dword_45593C )
    {
      dword_50C364 = 0;
      ++dword_50C360;
      ++dword_50C000;
      *(_DWORD *)int_reg |= 1u;
      if ( (v6 & 1) != 0 )
        irq_cpu_interrupt();
      gpu_frame_update();
      if ( reset_flag )
      {
        if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
          v8 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
        else
          v8 = *(_DWORD *)reg_pc & 0x1FFFFF;
        **(_DWORD **)((char *)dword_5164C4 + v8) = 195;
      }
      if ( byte_4FC4E4 )
      {
        byte_4FC4E4 = 0;
        dynarec_invalidate();
      }
      if ( (dword_50C360 & 0x3F) == 0 )
        sub_42CE40();
      sio_memcard_auto_save();
    }
    if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
      v9 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
    else
      v9 = *(_DWORD *)reg_pc & 0x1FFFFF;
    return (char *)dword_5164C4 + v9;
  }
}

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

  v2 = dword_4FC4E0;
  v3 = a2;
  v4 = 0;
  v157 = 0;
  v158 = 0;
  v159 = nullptr;
  if ( a2 != 1 && dword_4FC4E0 - (_BYTE *)dword_5164C0 >= 2080768 )
  {
    do
    {
      *(_DWORD *)((char *)dword_5164C4 + v4) = dword_5164C0;
      v4 += 4;
    }
    while ( v4 < 0x280000 );
    v3 = a2;
    dword_4FC4E0 = (uint8_t *)dword_5164C0 + 1216;
    v2 = (uint8_t *)dword_5164C0 + 1216;
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
      v2 = dword_4FC4E0;
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
      v2 = dword_4FC4E0;
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
            dword_4FC4E0[2] = v15;
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
            dword_4FC4E0[2] = v16;
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
              dword_4FC4E0[2] = v17;
              *(_WORD *)(dword_4FC4E0 + 3) = -1855;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = 32449;
LABEL_45:
            dword_4FC4E0[2] = v13;
            dword_4FC4E0[3] = v14;
            dword_4FC4E0[4] = 79;
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
              dword_4FC4E0[2] = v19;
              *(_WORD *)(dword_4FC4E0 + 3) = -7807;
              *(_DWORD *)(dword_4FC4E0 + 5) = 31;
              *(_WORD *)(dword_4FC4E0 + 9) = 26323;
              goto LABEL_50;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            dword_4FC4E0[2] = v20;
            *(_WORD *)(dword_4FC4E0 + 3) = 20107;
            dword_4FC4E0[5] = v19;
            *((_WORD *)dword_4FC4E0 + 3) = -7807;
            *((_DWORD *)dword_4FC4E0 + 2) = 31;
            *((_WORD *)dword_4FC4E0 + 6) = -7981;
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
              dword_4FC4E0[2] = v21;
              *(_WORD *)(dword_4FC4E0 + 3) = -7807;
              *(_DWORD *)(dword_4FC4E0 + 5) = 31;
              *(_WORD *)(dword_4FC4E0 + 9) = 28371;
              goto LABEL_50;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            dword_4FC4E0[2] = v22;
            *(_WORD *)(dword_4FC4E0 + 3) = 20107;
            dword_4FC4E0[5] = v21;
            *((_WORD *)dword_4FC4E0 + 3) = -7807;
            *((_DWORD *)dword_4FC4E0 + 2) = 31;
            *((_WORD *)dword_4FC4E0 + 6) = -5933;
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
              dword_4FC4E0[2] = v23;
              *(_WORD *)(dword_4FC4E0 + 3) = -7807;
              *(_DWORD *)(dword_4FC4E0 + 5) = 31;
              *(_WORD *)(dword_4FC4E0 + 9) = 32467;
LABEL_50:
              dword_4FC4E0[11] = v18;
              dword_4FC4E0[12] = 79;
              dword_4FC4E0 += 13;
            }
            else
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = v24;
              *(_WORD *)(dword_4FC4E0 + 3) = 20107;
              dword_4FC4E0[5] = v23;
              *((_WORD *)dword_4FC4E0 + 3) = -7807;
              *((_DWORD *)dword_4FC4E0 + 2) = 31;
              *((_WORD *)dword_4FC4E0 + 6) = -1837;
LABEL_130:
              *((_WORD *)dword_4FC4E0 + 7) = 18057;
              dword_4FC4E0[16] = v18;
              dword_4FC4E0[17] = 79;
              dword_4FC4E0 += 18;
            }
            goto LABEL_422;
          case 8u:
            if ( a2 == 1 )
              goto LABEL_422;
            *(_WORD *)v2 = 32267;
            dword_4FC4E0[2] = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            dword_4FC4E0[9] = 117;
            dword_5164CC = (int)(dword_4FC4E0 + 10);
            dword_4FC4E0 += 11;
            *dword_4FC4E0 = 79;
            *(_WORD *)(dword_4FC4E0 + 1) = 18059;
            dword_4FC4E0[3] = 4 * ((v7 >> 21) & 0x1F);
            dword_4FC4E0[4] = -24;
            *(_DWORD *)(dword_4FC4E0 + 5) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 119;
            dword_4FC4E0[9] = 80;
            dword_4FC4E0 += 10;
            dynarec_compile(ArgList, 1u);
            *dword_4FC4E0 = 88;
            *(_WORD *)(dword_4FC4E0 + 1) = 8447;
            dword_4FC4E0 += 3;
            *(_BYTE *)dword_5164CC = (_BYTE)dword_4FC4E0 - dword_5164CC - 1;
            *(_WORD *)dword_4FC4E0 = 18119;
            dword_4FC4E0[2] = 0x80;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 32393;
            dword_4FC4E0[9] = -112;
            dword_4FC4E0[10] = -24;
            *(_DWORD *)(dword_4FC4E0 + 11) = (char *)dynarec_hw_update - (char *)dword_4FC4E0 - 15;
            *(_WORD *)(dword_4FC4E0 + 15) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
            dword_4FC4E0[21] = 116;
            dword_4FC4E0[22] = 8;
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
            dword_4FC4E0[2] = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            dword_4FC4E0[9] = 117;
            v26 = 4 * ((v7 >> 21) & 0x1F);
            v27 = 4 * ((v7 >> 11) & 0x1F);
            v28 = dword_4FC4E0 + 11;
            dword_5164CC = (int)(dword_4FC4E0 + 10);
            dword_4FC4E0 += 11;
            if ( v27 == v26 )
              dword_4FF9E8 |= 0x800000u;
            *v28 = 79;
            if ( v27 )
            {
              *(_WORD *)(dword_4FC4E0 + 1) = 18119;
              dword_4FC4E0[3] = v27;
              v29 = ArgList + 4;
              if ( (ArgList & 0xF0000000) == 0 )
                v29 |= 0x80000000;
              *((_DWORD *)dword_4FC4E0 + 1) = v29;
              *((_WORD *)dword_4FC4E0 + 4) = 18059;
              dword_4FC4E0[10] = v26;
              dword_4FC4E0[11] = -24;
              *((_DWORD *)dword_4FC4E0 + 3) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 112;
              dword_4FC4E0[16] = 80;
              v30 = dword_4FC4E0 + 17;
            }
            else
            {
              *(_WORD *)(dword_4FC4E0 + 1) = 18059;
              dword_4FC4E0[3] = v26;
              dword_4FC4E0[4] = -24;
              *(_DWORD *)(dword_4FC4E0 + 5) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 119;
              dword_4FC4E0[9] = 80;
              v30 = dword_4FC4E0 + 10;
            }
            dword_4FC4E0 = v30;
            dynarec_compile(ArgList, 1u);
            *dword_4FC4E0 = 88;
            *(_WORD *)(dword_4FC4E0 + 1) = 8447;
            dword_4FC4E0 += 3;
            *(_BYTE *)dword_5164CC = (_BYTE)dword_4FC4E0 - dword_5164CC - 1;
            *(_WORD *)dword_4FC4E0 = 18119;
            dword_4FC4E0[2] = 0x80;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 32393;
            dword_4FC4E0[9] = -112;
            dword_4FC4E0[10] = -24;
            *(_DWORD *)(dword_4FC4E0 + 11) = (char *)dynarec_hw_update - (char *)dword_4FC4E0 - 15;
            *(_WORD *)(dword_4FC4E0 + 15) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
            dword_4FC4E0[21] = 116;
            dword_4FC4E0[22] = 8;
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
            dword_4FC4E0[2] = -44;
            *(_DWORD *)(dword_4FC4E0 + 3) = 0;
            dword_4FC4E0 += 7;
            *(_WORD *)dword_4FC4E0 = 18119;
            dword_4FC4E0[2] = -52;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 18119;
            dword_4FC4E0[9] = -56;
            *(_DWORD *)(dword_4FC4E0 + 10) = 32;
            *((_WORD *)dword_4FC4E0 + 7) = 18059;
            dword_4FC4E0[16] = -60;
            *(_WORD *)(dword_4FC4E0 + 17) = 26241;
            dword_4FC4E0[19] = -60;
            *((_DWORD *)dword_4FC4E0 + 5) = -64;
            *((_WORD *)dword_4FC4E0 + 12) = -7999;
            dword_4FC4E0[26] = 2;
            dword_4FC4E0[27] = 37;
            *((_DWORD *)dword_4FC4E0 + 7) = 63;
            *((_WORD *)dword_4FC4E0 + 16) = 17929;
            dword_4FC4E0[34] = -60;
            dword_4FC4E0[35] = -72;
            *((_DWORD *)dword_4FC4E0 + 9) = (char *)dword_5164C4 + 128;
            *((_WORD *)dword_4FC4E0 + 20) = 8447;
            dword_4FC4E0[42] = 79;
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
            dword_4FC4E0[2] = -120;
            goto LABEL_75;
          case 0x11u:
            *(_WORD *)v2 = 18059;
            dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            dword_4FC4E0[5] = -120;
            dword_4FC4E0[6] = 79;
            dword_4FC4E0 += 7;
            goto LABEL_422;
          case 0x12u:
            v31 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v31 )
              goto LABEL_422;
            *(_WORD *)dword_4FC4E0 = 18059;
            dword_4FC4E0[2] = -124;
LABEL_75:
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            dword_4FC4E0[5] = v31;
            goto LABEL_253;
          case 0x13u:
            *(_WORD *)v2 = 18059;
            dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            dword_4FC4E0[5] = -124;
            dword_4FC4E0[6] = 79;
            dword_4FC4E0 += 7;
            goto LABEL_422;
          case 0x18u:
            *(_WORD *)v2 = 18059;
            dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 28407;
            goto LABEL_81;
          case 0x19u:
            *(_WORD *)v2 = 18059;
            dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 26359;
LABEL_81:
            dword_4FC4E0[5] = 4 * (BYTE2(v7) & 0x1F);
            *((_WORD *)dword_4FC4E0 + 3) = 18057;
            dword_4FC4E0[8] = -124;
            *(_WORD *)(dword_4FC4E0 + 9) = 22153;
            dword_4FC4E0[11] = -120;
            dword_4FC4E0[12] = 79;
            dword_4FC4E0 += 13;
            goto LABEL_422;
          case 0x1Au:
            *(_WORD *)v2 = 18059;
            dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
            dword_4FC4E0[3] = -103;
            *((_WORD *)dword_4FC4E0 + 2) = 20107;
            dword_4FC4E0[6] = 4 * (BYTE2(v7) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 7) = -13947;
            *(_WORD *)(dword_4FC4E0 + 9) = 2676;
            *(_WORD *)(dword_4FC4E0 + 11) = -1545;
            *(_WORD *)(dword_4FC4E0 + 13) = 18057;
            dword_4FC4E0[15] = -124;
            *((_WORD *)dword_4FC4E0 + 8) = 22153;
            dword_4FC4E0[18] = -120;
            *(_WORD *)(dword_4FC4E0 + 19) = 6123;
            *(_WORD *)(dword_4FC4E0 + 21) = 18057;
            dword_4FC4E0[23] = -120;
            dword_4FC4E0[24] = -70;
            *(_DWORD *)(dword_4FC4E0 + 25) = -1;
            dword_4FC4E0[29] = -87;
            *(_DWORD *)(dword_4FC4E0 + 30) = 0x80000000;
            *((_WORD *)dword_4FC4E0 + 17) = 1396;
            dword_4FC4E0[36] = -70;
            *(_DWORD *)(dword_4FC4E0 + 37) = 1;
            *(_WORD *)(dword_4FC4E0 + 41) = 22153;
            dword_4FC4E0[43] = -124;
            dword_4FC4E0[44] = 79;
            dword_4FC4E0 += 45;
            goto LABEL_422;
          case 0x1Bu:
            *(_WORD *)v2 = 18059;
            dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = -11727;
            *(_WORD *)(dword_4FC4E0 + 5) = 20107;
            dword_4FC4E0[7] = 4 * (BYTE2(v7) & 0x1F);
            *((_WORD *)dword_4FC4E0 + 4) = -13947;
            *((_WORD *)dword_4FC4E0 + 5) = 2676;
            *((_WORD *)dword_4FC4E0 + 6) = -3593;
            *((_WORD *)dword_4FC4E0 + 7) = 18057;
            dword_4FC4E0[16] = -124;
            *(_WORD *)(dword_4FC4E0 + 17) = 22153;
            dword_4FC4E0[19] = -120;
            *((_WORD *)dword_4FC4E0 + 10) = 3051;
            *((_WORD *)dword_4FC4E0 + 11) = 18057;
            dword_4FC4E0[24] = -120;
            dword_4FC4E0[25] = -70;
            *(_DWORD *)(dword_4FC4E0 + 26) = -1;
            *((_WORD *)dword_4FC4E0 + 15) = 22153;
            dword_4FC4E0[32] = -124;
            dword_4FC4E0[33] = 79;
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
                dword_4FC4E0[2] = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17921;
                dword_4FC4E0[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = v32;
              *(_WORD *)(dword_4FC4E0 + 3) = 17923;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)dword_4FC4E0 + 1) = 17923;
            dword_4FC4E0[4] = v14;
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
                dword_4FC4E0[2] = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17961;
                dword_4FC4E0[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = v33;
              *(_WORD *)(dword_4FC4E0 + 3) = 17963;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)dword_4FC4E0 + 1) = 17963;
            dword_4FC4E0[4] = v14;
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
                dword_4FC4E0[2] = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17953;
                dword_4FC4E0[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = v34;
              *(_WORD *)(dword_4FC4E0 + 3) = 17955;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)dword_4FC4E0 + 1) = 17955;
            dword_4FC4E0[4] = v14;
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
                dword_4FC4E0[2] = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17929;
                dword_4FC4E0[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = v35;
              *(_WORD *)(dword_4FC4E0 + 3) = 17931;
              goto LABEL_118;
            }
            *(_WORD *)dword_4FC4E0 = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((_WORD *)dword_4FC4E0 + 1) = 17931;
            dword_4FC4E0[4] = v14;
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
                dword_4FC4E0[2] = v14;
                *(_WORD *)(dword_4FC4E0 + 3) = 17969;
                dword_4FC4E0[5] = v13;
                goto LABEL_253;
              }
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = v36;
              *(_WORD *)(dword_4FC4E0 + 3) = 17971;
LABEL_118:
              dword_4FC4E0[5] = v14;
              *((_WORD *)dword_4FC4E0 + 3) = 18057;
              dword_4FC4E0[8] = v13;
              dword_4FC4E0[9] = 79;
              dword_4FC4E0 += 10;
            }
            else
            {
              *(_WORD *)dword_4FC4E0 = -16335;
              if ( v14 )
              {
                *((_WORD *)dword_4FC4E0 + 1) = 17971;
                dword_4FC4E0[4] = v14;
                goto LABEL_273;
              }
LABEL_121:
              *((_WORD *)dword_4FC4E0 + 1) = 18057;
              dword_4FC4E0[4] = v13;
              dword_4FC4E0[5] = 79;
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
              dword_4FC4E0[2] = v38;
              *(_WORD *)(dword_4FC4E0 + 3) = 17931;
              dword_4FC4E0[5] = v39;
              *((_WORD *)dword_4FC4E0 + 3) = -12041;
              *((_WORD *)dword_4FC4E0 + 4) = 18057;
              dword_4FC4E0[10] = v37;
              dword_4FC4E0[11] = 79;
              dword_4FC4E0 += 12;
              goto LABEL_422;
            }
            *(_WORD *)dword_4FC4E0 = 18059;
            dword_4FC4E0[2] = v39;
            *(_WORD *)(dword_4FC4E0 + 3) = -12041;
            break;
          case 0x2Au:
            v40 = 4 * ((v7 >> 11) & 0x1F);
            if ( v40 )
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
              *(_WORD *)(dword_4FC4E0 + 3) = 17979;
              dword_4FC4E0[5] = 4 * (BYTE2(v7) & 0x1F);
              *((_WORD *)dword_4FC4E0 + 3) = -25585;
              dword_4FC4E0[8] = -64;
              dword_4FC4E0[9] = 37;
              *(_DWORD *)(dword_4FC4E0 + 10) = 1;
              *((_WORD *)dword_4FC4E0 + 7) = 18057;
              dword_4FC4E0[16] = v40;
              dword_4FC4E0[17] = 79;
              dword_4FC4E0 += 18;
            }
            goto LABEL_422;
          case 0x2Bu:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            *(_WORD *)dword_4FC4E0 = 18059;
            dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
            *(_WORD *)(dword_4FC4E0 + 3) = 17979;
            dword_4FC4E0[5] = 4 * (BYTE2(v7) & 0x1F);
            *((_WORD *)dword_4FC4E0 + 3) = -28145;
            dword_4FC4E0[8] = -64;
            dword_4FC4E0[9] = 37;
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
            dword_4FC4E0[2] = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            dword_4FC4E0[9] = 117;
            dword_5164CC = (int)(dword_4FC4E0 + 10);
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = -16335;
            dword_4FC4E0[2] = 79;
            *(_WORD *)(dword_4FC4E0 + 3) = 17977;
            dword_4FC4E0[5] = v42;
            dword_4FC4E0[6] = 124;
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
            dword_4FC4E0[2] = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            dword_4FC4E0[9] = 117;
            dword_5164CC = (int)(dword_4FC4E0 + 10);
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = -16335;
            dword_4FC4E0[2] = 79;
            *(_WORD *)(dword_4FC4E0 + 3) = 17977;
            dword_4FC4E0[5] = v44;
            dword_4FC4E0[6] = 125;
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
            dword_4FC4E0[2] = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            dword_4FC4E0[9] = 117;
            dword_5164CC = (int)(dword_4FC4E0 + 10);
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = 18119;
            dword_4FC4E0[2] = 124;
            *(_DWORD *)(dword_4FC4E0 + 3) = (ArgList + 4) | 0x80000000;
            *(_WORD *)(dword_4FC4E0 + 7) = -16335;
            dword_4FC4E0[9] = 79;
            *((_WORD *)dword_4FC4E0 + 5) = 17977;
            dword_4FC4E0[12] = v47;
            dword_4FC4E0[13] = 124;
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
            dword_4FC4E0[2] = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            dword_4FC4E0[9] = 117;
            dword_5164CC = (int)(dword_4FC4E0 + 10);
            dword_4FC4E0 += 11;
            *(_WORD *)dword_4FC4E0 = 18119;
            dword_4FC4E0[2] = 124;
            *(_DWORD *)(dword_4FC4E0 + 3) = (ArgList + 4) | 0x80000000;
            *(_WORD *)(dword_4FC4E0 + 7) = -16335;
            dword_4FC4E0[9] = 79;
            *((_WORD *)dword_4FC4E0 + 5) = 17977;
            dword_4FC4E0[12] = v49;
            dword_4FC4E0[13] = 125;
LABEL_151:
            dword_4FC4E0[14] = 7;
            dword_4FC4E0[15] = -72;
            if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
              v50 = (ArgList & 0x7FFFF) + 0x200000;
            else
              v50 = ArgList & 0x1FFFFF;
            *((_DWORD *)dword_4FC4E0 + 4) = (char *)dword_5164C4 + v50;
            *((_WORD *)dword_4FC4E0 + 10) = 8447;
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
          if ( !byte_455946 || ((v51 ^ (ArgList - 4)) & 0xFFFFFF) != 0 )
          {
            *(_WORD *)dword_4FC4E0 = 32267;
            dword_4FC4E0[2] = -44;
            *(_WORD *)(dword_4FC4E0 + 3) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
            dword_4FC4E0[9] = 117;
            v52 = dword_4FC4E0 + 10;
            dword_4FC4E0 += 11;
            dword_5164CC = (int)v52;
            *dword_4FC4E0++ = 79;
            dynarec_compile(ArgList, 1u);
            *dword_4FC4E0 = -72;
            if ( (v51 & 0xFFF00000 | ArgList & 0xF0000000) == 0xBFC00000 )
              v53 = (v51 & 0x7FFFF) + 0x200000;
            else
              v53 = v51 & 0x1FFFFF;
            *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v53;
            *(_WORD *)(dword_4FC4E0 + 5) = 8447;
            dword_4FC4E0 += 7;
            *(_BYTE *)dword_5164CC = (_BYTE)dword_4FC4E0 - dword_5164CC - 1;
            *(_WORD *)dword_4FC4E0 = 18119;
            dword_4FC4E0[2] = 0x80;
            *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
            *(_WORD *)(dword_4FC4E0 + 7) = 32393;
            dword_4FC4E0[9] = -112;
            dword_4FC4E0[10] = -24;
            *(_DWORD *)(dword_4FC4E0 + 11) = (char *)dynarec_hw_update - (char *)dword_4FC4E0 - 15;
            *(_WORD *)(dword_4FC4E0 + 15) = -14345;
            *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
            dword_4FC4E0[21] = 116;
            dword_4FC4E0[22] = 8;
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
          dword_4FC4E0[2] = -44;
          *(_WORD *)(dword_4FC4E0 + 3) = -14345;
          *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
          dword_4FC4E0[9] = 117;
          v54 = 4 * (v7 & 0x3FFFFFF);
          dword_5164CC = (int)(dword_4FC4E0 + 10);
          dword_4FC4E0 += 11;
          *dword_4FC4E0 = 79;
          *(_WORD *)(dword_4FC4E0 + 1) = 18119;
          dword_4FC4E0[3] = 124;
          if ( (ArgList & 0xF0000000) != 0 )
            *((_DWORD *)dword_4FC4E0 + 1) = ArgList + 4;
          else
            *((_DWORD *)dword_4FC4E0 + 1) = (ArgList + 4) | 0x80000000;
          dword_4FC4E0 += 8;
          dynarec_compile(ArgList, 1u);
          *dword_4FC4E0 = -72;
          if ( (v54 & 0xFFF00000 | ArgList & 0xF0000000) == 0xBFC00000 )
            v55 = (v54 & 0x7FFFF) + 0x200000;
          else
            v55 = v54 & 0x1FFFFF;
          *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v55;
          *(_WORD *)(dword_4FC4E0 + 5) = 8447;
          dword_4FC4E0 += 7;
          *(_BYTE *)dword_5164CC = (_BYTE)dword_4FC4E0 - dword_5164CC - 1;
          *(_WORD *)dword_4FC4E0 = 18119;
          dword_4FC4E0[2] = 0x80;
          *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
          *(_WORD *)(dword_4FC4E0 + 7) = 32393;
          dword_4FC4E0[9] = -112;
          dword_4FC4E0[10] = -24;
          *(_DWORD *)(dword_4FC4E0 + 11) = (char *)dynarec_hw_update - (char *)dword_4FC4E0 - 15;
          *(_WORD *)(dword_4FC4E0 + 15) = -14345;
          *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
          dword_4FC4E0[21] = 116;
          dword_4FC4E0[22] = 8;
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
        dword_4FC4E0[2] = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        dword_4FC4E0[9] = 117;
        v60 = dword_4FC4E0 + 11;
        dword_5164CC = (int)(dword_4FC4E0 + 10);
        dword_4FC4E0 += 11;
        if ( v59 )
        {
          *(_WORD *)v60 = 18059;
          dword_4FC4E0[2] = v59;
          v61 = dword_4FC4E0 + 3;
        }
        else
        {
          *(_WORD *)v60 = -16335;
          v61 = dword_4FC4E0 + 2;
        }
        dword_4FC4E0 = v61;
        *v61 = 79;
        *(_WORD *)(dword_4FC4E0 + 1) = 17977;
        dword_4FC4E0[3] = v58;
        dword_4FC4E0[4] = 116;
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
        *(_WORD *)dword_4FC4E0 = 32267;
        dword_4FC4E0[2] = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        dword_4FC4E0[9] = 117;
        v66 = dword_4FC4E0 + 11;
        dword_5164CC = (int)(dword_4FC4E0 + 10);
        dword_4FC4E0 += 11;
        if ( v65 )
        {
          *(_WORD *)v66 = 18059;
          dword_4FC4E0[2] = v65;
          v67 = dword_4FC4E0 + 3;
        }
        else
        {
          *(_WORD *)v66 = -16335;
          v67 = dword_4FC4E0 + 2;
        }
        dword_4FC4E0 = v67;
        *v67 = 79;
        *(_WORD *)(dword_4FC4E0 + 1) = 17977;
        dword_4FC4E0[3] = v64;
        dword_4FC4E0[4] = 117;
LABEL_436:
        dword_4FC4E0[5] = 7;
        dword_4FC4E0[6] = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v154 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v154 = ArgList & 0x1FFFFF;
        *(_DWORD *)(dword_4FC4E0 + 7) = (char *)dword_5164C4 + v154;
        *(_WORD *)(dword_4FC4E0 + 11) = 8447;
        dword_4FC4E0 += 13;
        dynarec_compile(ArgList, 1u);
        if ( !v7 )
          v7 = 1;
        *dword_4FC4E0 = -72;
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
        dword_4FC4E0[2] = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        dword_4FC4E0[9] = 117;
        dword_5164CC = (int)(dword_4FC4E0 + 10);
        dword_4FC4E0 += 11;
        *(_WORD *)dword_4FC4E0 = -16335;
        dword_4FC4E0[2] = 79;
        *(_WORD *)(dword_4FC4E0 + 3) = 17977;
        dword_4FC4E0[5] = v69;
        dword_4FC4E0[6] = 126;
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
        dword_4FC4E0[2] = -44;
        *(_WORD *)(dword_4FC4E0 + 3) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0x80000000;
        dword_4FC4E0[9] = 117;
        dword_5164CC = (int)(dword_4FC4E0 + 10);
        dword_4FC4E0 += 11;
        *(_WORD *)dword_4FC4E0 = -16335;
        dword_4FC4E0[2] = 79;
        *(_WORD *)(dword_4FC4E0 + 3) = 17977;
        dword_4FC4E0[5] = v71;
        dword_4FC4E0[6] = 127;
LABEL_141:
        dword_4FC4E0[7] = 7;
        dword_4FC4E0[8] = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v45 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v45 = ArgList & 0x1FFFFF;
        *(_DWORD *)(dword_4FC4E0 + 9) = (char *)dword_5164C4 + v45;
        *(_WORD *)(dword_4FC4E0 + 13) = 8447;
        v151 = dword_4FC4E0 + 15;
LABEL_428:
        dword_4FC4E0 = v151;
        dynarec_compile(ArgList, 1u);
        if ( !v7 )
          v7 = 1;
        *dword_4FC4E0 = -72;
        v152 = ArgList + 4 * v7;
        if ( (v152 & 0xFFF00000) == 0xBFC00000 )
          v153 = (v152 & 0x7FFFF) + 0x200000;
        else
          v153 = v152 & 0x1FFFFF;
LABEL_447:
        *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dword_5164C4 + v153;
        *(_WORD *)(dword_4FC4E0 + 5) = 8447;
        dword_4FC4E0 += 7;
        *(_BYTE *)dword_5164CC = (_BYTE)dword_4FC4E0 - dword_5164CC - 1;
        *(_WORD *)dword_4FC4E0 = 18119;
        dword_4FC4E0[2] = 0x80;
        *(_DWORD *)(dword_4FC4E0 + 3) = ArgList - 4;
        *(_WORD *)(dword_4FC4E0 + 7) = 32393;
        dword_4FC4E0[9] = -112;
        dword_4FC4E0[10] = -24;
        *(_DWORD *)(dword_4FC4E0 + 11) = (char *)dynarec_hw_update - (char *)dword_4FC4E0 - 15;
        *(_WORD *)(dword_4FC4E0 + 15) = -14345;
        *(_DWORD *)(dword_4FC4E0 + 17) = 0x40000000;
        dword_4FC4E0[21] = 116;
        dword_4FC4E0[22] = 8;
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
          dword_4FC4E0[2] = v74;
          v75 = dword_4FC4E0 + 3;
        }
        else
        {
          *(_WORD *)dword_4FC4E0 = -16335;
          v75 = dword_4FC4E0 + 2;
        }
        dword_4FC4E0 = v75;
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
          dword_4FC4E0[2] = v78;
          dword_4FC4E0[3] = 61;
          *((_DWORD *)dword_4FC4E0 + 1) = v7;
          *((_WORD *)dword_4FC4E0 + 4) = -25585;
          dword_4FC4E0[10] = -64;
          dword_4FC4E0[11] = 37;
          *((_DWORD *)dword_4FC4E0 + 3) = 1;
          *((_WORD *)dword_4FC4E0 + 8) = 18057;
          dword_4FC4E0[18] = v79;
          dword_4FC4E0[19] = 79;
          dword_4FC4E0 += 20;
        }
        goto LABEL_422;
      case 0xBu:
        v80 = 4 * (BYTE2(v7) & 0x1F);
        if ( v80 )
        {
          *(_WORD *)dword_4FC4E0 = 18059;
          dword_4FC4E0[2] = 4 * ((v7 >> 21) & 0x1F);
          dword_4FC4E0[3] = 61;
          *((_DWORD *)dword_4FC4E0 + 1) = (unsigned __int16)v7;
          *((_WORD *)dword_4FC4E0 + 4) = -28145;
          dword_4FC4E0[10] = -64;
          dword_4FC4E0[11] = 37;
          *((_DWORD *)dword_4FC4E0 + 3) = 1;
          *((_WORD *)dword_4FC4E0 + 8) = 18057;
          dword_4FC4E0[18] = v80;
          dword_4FC4E0[19] = 79;
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
          dword_4FC4E0[2] = v82;
          v83 = dword_4FC4E0 + 3;
          dword_4FC4E0 += 3;
        }
        else
        {
          *(_WORD *)dword_4FC4E0 = -16335;
          v83 = dword_4FC4E0 + 2;
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
          dword_4FC4E0[2] = v85;
          v86 = dword_4FC4E0 + 3;
          dword_4FC4E0 += 3;
        }
        else
        {
          *(_WORD *)dword_4FC4E0 = -16335;
          v86 = dword_4FC4E0 + 2;
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
          dword_4FC4E0[2] = v37;
          *(_DWORD *)(dword_4FC4E0 + 3) = v7;
          dword_4FC4E0[7] = 79;
          dword_4FC4E0 += 8;
        }
        else
        {
          if ( v88 )
          {
            *(_WORD *)dword_4FC4E0 = 18059;
            dword_4FC4E0[2] = v88;
            v89 = dword_4FC4E0 + 3;
            dword_4FC4E0 += 3;
          }
          else
          {
            *(_WORD *)dword_4FC4E0 = -16335;
            v89 = dword_4FC4E0 + 2;
            dword_4FC4E0 += 2;
          }
          *v89 = 53;
LABEL_202:
          *(_DWORD *)(dword_4FC4E0 + 1) = v7;
LABEL_203:
          *(_WORD *)(dword_4FC4E0 + 5) = 18057;
          dword_4FC4E0[7] = v37;
          dword_4FC4E0[8] = 79;
          dword_4FC4E0 += 9;
        }
        goto LABEL_422;
      case 0xFu:
        v13 = 4 * (BYTE2(v7) & 0x1F);
        if ( v13 )
        {
          *dword_4FC4E0 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = (unsigned __int16)v7 << 16;
LABEL_273:
          *(_WORD *)(dword_4FC4E0 + 5) = 18057;
          dword_4FC4E0[7] = v13;
          dword_4FC4E0[8] = 79;
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
              dword_4FC4E0[2] = -112;
              dword_4FC4E0[3] = 87;
              dword_4FC4E0[4] = 86;
              *(_WORD *)(dword_4FC4E0 + 5) = 18119;
              dword_4FC4E0[7] = -116;
              *((_DWORD *)dword_4FC4E0 + 2) = v7;
              v92 = op_MTC0;
LABEL_242:
              dword_4FC4E0[12] = -24;
LABEL_243:
              *(_DWORD *)(dword_4FC4E0 + 13) = v92 - dword_4FC4E0 - 17;
              dword_4FC4E0[17] = 94;
              dword_4FC4E0[18] = 95;
              dword_4FC4E0[19] = 79;
              dword_4FC4E0 += 20;
            }
            else
            {
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = 4 * (BYTE2(v7) & 0x1F);
              *(_WORD *)(dword_4FC4E0 + 3) = 18057;
              dword_4FC4E0[5] = (v91 & 0x3F) - 108;
              dword_4FC4E0[6] = 79;
              dword_4FC4E0 += 7;
              if ( v91 == 48 || v91 == 52 )
              {
                *(_WORD *)dword_4FC4E0 = 18059;
                dword_4FC4E0[2] = -60;
                dword_4FC4E0[3] = 37;
                *((_DWORD *)dword_4FC4E0 + 1) = 257;
                dword_4FC4E0[8] = 61;
                *(_DWORD *)(dword_4FC4E0 + 9) = 257;
                dword_4FC4E0[13] = 117;
                dword_4FC4E0[14] = 50;
                *(_WORD *)(dword_4FC4E0 + 15) = 18059;
                dword_4FC4E0[17] = -56;
                dword_4FC4E0[18] = 37;
                *(_DWORD *)(dword_4FC4E0 + 19) = 256;
                dword_4FC4E0[23] = 61;
                *((_DWORD *)dword_4FC4E0 + 6) = 256;
                dword_4FC4E0[28] = 117;
                dword_4FC4E0[29] = 35;
                *((_WORD *)dword_4FC4E0 + 15) = 18119;
                dword_4FC4E0[32] = -52;
                *(_DWORD *)(dword_4FC4E0 + 33) = ArgList;
                *(_WORD *)(dword_4FC4E0 + 37) = 18059;
                dword_4FC4E0[39] = -60;
                *((_WORD *)dword_4FC4E0 + 20) = 26241;
                dword_4FC4E0[42] = -60;
                *(_DWORD *)(dword_4FC4E0 + 43) = -256;
                *(_WORD *)(dword_4FC4E0 + 47) = -7999;
                dword_4FC4E0[49] = 2;
                dword_4FC4E0[50] = 37;
                *(_DWORD *)(dword_4FC4E0 + 51) = 63;
                *(_WORD *)(dword_4FC4E0 + 55) = 17929;
                dword_4FC4E0[57] = -60;
                dword_4FC4E0[58] = -72;
                *(_DWORD *)(dword_4FC4E0 + 59) = (char *)dword_5164C4 + 128;
                *(_WORD *)(dword_4FC4E0 + 63) = 8447;
                dword_4FC4E0 += 65;
              }
              if ( v91 == 48 )
              {
                *dword_4FC4E0 = -95;
                *(_DWORD *)(dword_4FC4E0 + 1) = int_reg;
                *(_WORD *)(dword_4FC4E0 + 5) = 1315;
                *(_DWORD *)(dword_4FC4E0 + 7) = &int_mask;
                dword_4FC4E0[11] = -87;
                *((_DWORD *)dword_4FC4E0 + 3) = 1019;
                dword_4FC4E0[16] = 116;
                dword_4FC4E0[17] = 22;
                *((_WORD *)dword_4FC4E0 + 9) = 18059;
                dword_4FC4E0[20] = -60;
                dword_4FC4E0[21] = 37;
                *(_DWORD *)(dword_4FC4E0 + 22) = 1025;
                dword_4FC4E0[26] = 61;
                *(_DWORD *)(dword_4FC4E0 + 27) = 1025;
                dword_4FC4E0[31] = 117;
                dword_4FC4E0[32] = 7;
                *(_WORD *)(dword_4FC4E0 + 33) = 18119;
                dword_4FC4E0[35] = -44;
                *((_DWORD *)dword_4FC4E0 + 9) = 0x80000000;
                dword_4FC4E0 += 40;
              }
            }
          }
          else
          {
            if ( v90 != 16 )
              fatal_error_with_message_box(" COP0 Opcode %02x UNK \n", (v7 >> 21) & 0x1F);
            *(_WORD *)v2 = 18059;
            dword_4FC4E0[2] = -60;
            *(_WORD *)(dword_4FC4E0 + 3) = 26241;
            dword_4FC4E0[5] = -60;
            *(_DWORD *)(dword_4FC4E0 + 6) = -16;
            *((_WORD *)dword_4FC4E0 + 5) = -5951;
            dword_4FC4E0[12] = 2;
            dword_4FC4E0[13] = 37;
            *(_DWORD *)(dword_4FC4E0 + 14) = 15;
            *((_WORD *)dword_4FC4E0 + 9) = 17929;
            dword_4FC4E0[20] = -60;
            dword_4FC4E0[21] = 79;
            dword_4FC4E0 += 22;
            *dword_4FC4E0 = -95;
            *(_DWORD *)(dword_4FC4E0 + 1) = int_reg;
            *(_WORD *)(dword_4FC4E0 + 5) = 1315;
            *(_DWORD *)(dword_4FC4E0 + 7) = &int_mask;
            dword_4FC4E0[11] = -87;
            *((_DWORD *)dword_4FC4E0 + 3) = 1019;
            dword_4FC4E0[16] = 116;
            dword_4FC4E0[17] = 22;
            *((_WORD *)dword_4FC4E0 + 9) = 18059;
            dword_4FC4E0[20] = -60;
            dword_4FC4E0[21] = 37;
            *(_DWORD *)(dword_4FC4E0 + 22) = 1025;
            dword_4FC4E0[26] = 61;
            *(_DWORD *)(dword_4FC4E0 + 27) = 1025;
            dword_4FC4E0[31] = 117;
            dword_4FC4E0[32] = 7;
            *(_WORD *)(dword_4FC4E0 + 33) = 18119;
            dword_4FC4E0[35] = -44;
            *((_DWORD *)dword_4FC4E0 + 9) = 0x80000000;
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
            dword_4FC4E0[2] = -112;
            dword_4FC4E0[3] = 87;
            dword_4FC4E0[4] = 86;
            *(_WORD *)(dword_4FC4E0 + 5) = 18119;
            dword_4FC4E0[7] = -116;
            *((_DWORD *)dword_4FC4E0 + 2) = v7;
            dword_4FC4E0[12] = -24;
            *(_DWORD *)(dword_4FC4E0 + 13) = (char *)op_MFC0 - (char *)dword_4FC4E0 - 17;
            dword_4FC4E0[17] = 94;
            dword_4FC4E0[18] = 95;
            dword_4FC4E0[19] = 79;
            dword_4FC4E0 += 20;
          }
          else if ( v94 )
          {
            *(_WORD *)dword_4FC4E0 = 18059;
            dword_4FC4E0[2] = (v93 & 0x3F) - 108;
            *(_WORD *)(dword_4FC4E0 + 3) = 18057;
            dword_4FC4E0[5] = v94;
LABEL_253:
            dword_4FC4E0[6] = 79;
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
              dword_4FC4E0[25] = 4 * (BYTE2(v7) & 0x1F);
              dword_4FC4E0[26] = 79;
              *(_WORD *)dword_4FC4E0 = 18059;
              dword_4FC4E0[2] = 8;
              *(_WORD *)(dword_4FC4E0 + 3) = 17979;
              dword_4FC4E0[5] = 120;
              *((_WORD *)dword_4FC4E0 + 3) = -25585;
              dword_4FC4E0[8] = -64;
              dword_4FC4E0[9] = 37;
              *(_DWORD *)(dword_4FC4E0 + 10) = 1;
              *((_WORD *)dword_4FC4E0 + 7) = 18057;
              dword_4FC4E0[16] = 12;
              dword_4FC4E0[17] = 79;
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
              v2 = dword_4FC4E0;
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
                dword_4FC4E0[2] = -112;
                dword_4FC4E0[3] = 87;
                dword_4FC4E0[4] = 86;
                *(_WORD *)(dword_4FC4E0 + 5) = 18119;
                dword_4FC4E0[7] = -116;
                *((_DWORD *)dword_4FC4E0 + 2) = v7;
                dword_4FC4E0[12] = -24;
                v92 = gte_exec_opcode;
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
            dword_4FC4E0[3] = 4 * (BYTE2(v7) & 0x1F);
            if ( v97 == 1 || v97 == 3 || v97 == 5 || v97 == 8 || v97 == 9 || v97 == 10 || v97 == 11 )
            {
              *((_WORD *)dword_4FC4E0 + 2) = -16625;
              v98 = &gte_regs.data[v97];
              goto LABEL_286;
            }
            dword_4FC4E0[4] = -93;
            *(_DWORD *)(dword_4FC4E0 + 5) = (char *)&gte_regs + v97 * 4;
            dword_4FC4E0 += 9;
            goto LABEL_422;
          case 6u:
            *v2 = 79;
            v99 = (v7 >> 11) & 0x1F;
            *(_WORD *)(dword_4FC4E0 + 1) = 18059;
            dword_4FC4E0[3] = 4 * (BYTE2(v7) & 0x1F);
            if ( v99 == 4 || v99 == 12 || v99 == 20 || v99 == 26 || v99 == 27 || v99 == 29 || v99 == 30 )
            {
              *((_WORD *)dword_4FC4E0 + 2) = -16625;
              v98 = &gte_regs.ctrl[v99];
LABEL_286:
              dword_4FC4E0[6] = -64;
              dword_4FC4E0[7] = -93;
              *((_DWORD *)dword_4FC4E0 + 2) = v98;
              dword_4FC4E0 += 12;
            }
            else
            {
              dword_4FC4E0[4] = -93;
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
              *((_WORD *)dword_4FC4E0 + 5) = -16625;
              dword_4FC4E0[12] = 5;
              *(_DWORD *)(dword_4FC4E0 + 13) = &gte_regs.data[13].s16.lo;
              *(_WORD *)(dword_4FC4E0 + 17) = -16625;
              dword_4FC4E0[19] = 13;
              *((_DWORD *)dword_4FC4E0 + 5) = &gte_regs.data[14].s16.lo;
              *((_WORD *)dword_4FC4E0 + 12) = -16625;
              dword_4FC4E0[26] = 21;
              *(_DWORD *)(dword_4FC4E0 + 27) = &gte_regs.data[12];
              *(_WORD *)(dword_4FC4E0 + 31) = -16085;
              *(_WORD *)(dword_4FC4E0 + 33) = -20721;
              dword_4FC4E0[35] = -62;
              *((_WORD *)dword_4FC4E0 + 18) = -10101;
              *((_WORD *)dword_4FC4E0 + 19) = -16625;
              dword_4FC4E0[40] = 5;
              *(_DWORD *)(dword_4FC4E0 + 41) = &gte_regs.data[12].s16.lo;
              *(_WORD *)(dword_4FC4E0 + 45) = -16625;
              dword_4FC4E0[47] = 21;
              *((_DWORD *)dword_4FC4E0 + 12) = &gte_regs.data[13];
              *((_WORD *)dword_4FC4E0 + 26) = -14293;
              *((_WORD *)dword_4FC4E0 + 27) = -20721;
              dword_4FC4E0[56] = -54;
              *(_WORD *)(dword_4FC4E0 + 57) = -9981;
              *(_WORD *)(dword_4FC4E0 + 59) = -16625;
              dword_4FC4E0[61] = 13;
              *(_DWORD *)(dword_4FC4E0 + 62) = &gte_regs.data[13].s16.lo;
              *((_WORD *)dword_4FC4E0 + 33) = -16625;
              dword_4FC4E0[68] = 21;
              *(_DWORD *)(dword_4FC4E0 + 69) = &gte_regs.data[14];
              *(_WORD *)(dword_4FC4E0 + 73) = -16085;
              *(_WORD *)(dword_4FC4E0 + 75) = -20721;
              dword_4FC4E0[77] = -62;
              *((_WORD *)dword_4FC4E0 + 39) = -10237;
              *((_WORD *)dword_4FC4E0 + 40) = -15477;
              dword_4FC4E0[82] = -93;
              *(_DWORD *)(dword_4FC4E0 + 83) = &gte_regs.data[24];
              *(_WORD *)(dword_4FC4E0 + 87) = 32653;
              dword_4FC4E0[89] = -4;
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
                  dword_4FC4E0[2] = -112;
                  dword_4FC4E0[3] = 87;
                  dword_4FC4E0[4] = 86;
                  *(_WORD *)(dword_4FC4E0 + 5) = 18119;
                  dword_4FC4E0[7] = -116;
                  *((_DWORD *)dword_4FC4E0 + 2) = v7;
                  v92 = gte_exec_opcode;
                  goto LABEL_242;
                }
                v101 = gte_rtps;
              }
              *v2 = -24;
              *(_DWORD *)(dword_4FC4E0 + 1) = (char *)v101 - (char *)dword_4FC4E0 - 5;
              *(_WORD *)(dword_4FC4E0 + 5) = 32653;
              dword_4FC4E0[7] = -4;
              dword_4FC4E0 += 8;
            }
LABEL_422:
            if ( v157 )
              return v158;
            v2 = dword_4FC4E0;
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
          dword_4FC4E0[7] = v103;
          v105 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v103;
          v105 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v105;
        *v105 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 187;
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
          dword_4FC4E0[7] = v107;
          v108 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v107;
          v108 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v108;
        *v108 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 315;
        if ( v104 )
        {
          *(_WORD *)(dword_4FC4E0 + 5) = -16625;
LABEL_314:
          dword_4FC4E0[7] = -64;
          *((_WORD *)dword_4FC4E0 + 4) = 18057;
          dword_4FC4E0[10] = v104;
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
        dword_4FC4E0[7] = v110;
        *((_WORD *)dword_4FC4E0 + 4) = -10101;
        *((_WORD *)dword_4FC4E0 + 5) = -7295;
        *((_DWORD *)dword_4FC4E0 + 3) = 3;
        dword_4FC4E0[16] = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        dword_4FC4E0[21] = -24;
        *(_DWORD *)(dword_4FC4E0 + 22) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 422;
        if ( !v111 )
        {
          dword_4FC4E0 += 26;
          goto LABEL_422;
        }
        *((_WORD *)dword_4FC4E0 + 13) = 3211;
        dword_4FC4E0[28] = -99;
        *(_DWORD *)(dword_4FC4E0 + 29) = byte_4558BC;
        *(_WORD *)(dword_4FC4E0 + 33) = 20001;
        dword_4FC4E0[35] = v111;
        *((_WORD *)dword_4FC4E0 + 18) = 3211;
        dword_4FC4E0[38] = -99;
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
          dword_4FC4E0[7] = v113;
          v115 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v113;
          v115 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v115;
        v116 = adjust_timing == 0;
        *v115 = -87;
        *(_DWORD *)(dword_4FC4E0 + 1) = 1602224128;
        dword_4FC4E0[5] = 117;
        if ( v116 )
        {
          dword_4FC4E0[6] = 17;
          dword_4FC4E0[7] = 37;
          *((_DWORD *)dword_4FC4E0 + 2) = 0x1FFFFF;
          dword_4FC4E0[12] = 5;
          *(_DWORD *)(dword_4FC4E0 + 13) = ram;
          *(_WORD *)(dword_4FC4E0 + 17) = 32653;
          dword_4FC4E0[19] = -byte_455945;
          *((_WORD *)dword_4FC4E0 + 10) = 139;
          dword_4FC4E0[22] = -21;
          dword_4FC4E0[23] = 5;
          dword_4FC4E0[24] = -24;
          *(_DWORD *)(dword_4FC4E0 + 25) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 419;
          if ( v114 )
          {
            *(_WORD *)(dword_4FC4E0 + 29) = 18057;
            dword_4FC4E0[31] = v114;
            dword_4FC4E0 += 32;
          }
          else
          {
            dword_4FC4E0 += 29;
          }
        }
        else
        {
          dword_4FC4E0[6] = 22;
          dword_4FC4E0[7] = 37;
          *((_DWORD *)dword_4FC4E0 + 2) = 0x1FFFFF;
          dword_4FC4E0[12] = 5;
          *(_DWORD *)(dword_4FC4E0 + 13) = ram;
          *(_WORD *)(dword_4FC4E0 + 17) = 7563;
          *(_DWORD *)(dword_4FC4E0 + 19) = &byte_455945;
          *(_WORD *)(dword_4FC4E0 + 23) = -1237;
          *(_WORD *)(dword_4FC4E0 + 25) = 139;
          dword_4FC4E0[27] = -21;
          dword_4FC4E0[28] = 5;
          dword_4FC4E0[29] = -24;
          *(_DWORD *)(dword_4FC4E0 + 30) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 414;
          if ( v114 )
          {
            *((_WORD *)dword_4FC4E0 + 17) = 18057;
            dword_4FC4E0[36] = v114;
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
          dword_4FC4E0[7] = v118;
          v120 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v118;
          v120 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v120;
        *v120 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 187;
        if ( !v119 )
        {
          dword_4FC4E0 += 5;
          goto LABEL_422;
        }
        dword_4FC4E0[5] = 37;
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
          dword_4FC4E0[7] = v122;
          v123 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v122;
          v123 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v123;
        *v123 = -24;
        *(_DWORD *)(dword_4FC4E0 + 1) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 315;
        if ( !v119 )
        {
          dword_4FC4E0 += 5;
          goto LABEL_422;
        }
        dword_4FC4E0[5] = 37;
        *(_DWORD *)(dword_4FC4E0 + 6) = 0xFFFF;
LABEL_354:
        *((_WORD *)dword_4FC4E0 + 5) = 18057;
        dword_4FC4E0[12] = v119;
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
        dword_4FC4E0[7] = v125;
        *((_WORD *)dword_4FC4E0 + 4) = -10101;
        *((_WORD *)dword_4FC4E0 + 5) = -7295;
        *((_DWORD *)dword_4FC4E0 + 3) = 3;
        dword_4FC4E0[16] = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        dword_4FC4E0[21] = -24;
        *(_DWORD *)(dword_4FC4E0 + 22) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 422;
        if ( v111 )
        {
          *((_WORD *)dword_4FC4E0 + 13) = 0xC8B;
          dword_4FC4E0[28] = 0x9D;
          *(_DWORD *)(dword_4FC4E0 + 29) = byte_4558DC;
          *(_WORD *)(dword_4FC4E0 + 33) = 0x4E21;
          dword_4FC4E0[35] = v111;
          *((_WORD *)dword_4FC4E0 + 18) = 0xC8B;
          dword_4FC4E0[38] = 0x9D;
          *(_DWORD *)(dword_4FC4E0 + 39) = byte_4558EC;
          *(_WORD *)(dword_4FC4E0 + 43) = 0xE8D3;
LABEL_328:
          *(_WORD *)(dword_4FC4E0 + 45) = 0x4609;
          dword_4FC4E0[47] = v111;
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
          dword_4FC4E0[7] = v127;
          v129 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v127;
          v129 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v129;
        *(_WORD *)v129 = 24203;
        dword_4FC4E0[2] = v128;
        *(_WORD *)(dword_4FC4E0 + 3) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 5) = 255;
        dword_4FC4E0[9] = -24;
        *(_DWORD *)(dword_4FC4E0 + 10) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 562;
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
          dword_4FC4E0[7] = v131;
          v133 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v131;
          v133 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v133;
        *(_WORD *)v133 = 24203;
        dword_4FC4E0[2] = v132;
        *(_WORD *)(dword_4FC4E0 + 3) = -7295;
        *(_DWORD *)(dword_4FC4E0 + 5) = 0xFFFF;
        dword_4FC4E0[9] = -24;
        *(_DWORD *)(dword_4FC4E0 + 10) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 754;
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
        dword_4FC4E0[7] = v135;
        *((_WORD *)dword_4FC4E0 + 4) = -10101;
        *((_WORD *)dword_4FC4E0 + 5) = -7295;
        *((_DWORD *)dword_4FC4E0 + 3) = 3;
        dword_4FC4E0[16] = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        dword_4FC4E0[21] = 80;
        dword_4FC4E0[22] = -24;
        *(_DWORD *)(dword_4FC4E0 + 23) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 421;
        *(_WORD *)(dword_4FC4E0 + 27) = 3211;
        dword_4FC4E0[29] = -99;
        *(_DWORD *)(dword_4FC4E0 + 30) = byte_4558FC;
        *((_WORD *)dword_4FC4E0 + 17) = -16093;
        *((_WORD *)dword_4FC4E0 + 18) = 3211;
        dword_4FC4E0[38] = -99;
        *(_DWORD *)(dword_4FC4E0 + 39) = byte_45590C;
        *(_WORD *)(dword_4FC4E0 + 43) = 24203;
        dword_4FC4E0[45] = v136;
        *((_WORD *)dword_4FC4E0 + 23) = -5165;
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
          dword_4FC4E0[7] = v138;
          v140 = dword_4FC4E0 + 8;
        }
        else
        {
          *(_WORD *)v2 = 18059;
          dword_4FC4E0[2] = v138;
          v140 = dword_4FC4E0 + 3;
        }
        dword_4FC4E0 = v140;
        *(_WORD *)v140 = 24203;
        dword_4FC4E0[2] = v139;
        dword_4FC4E0[3] = -24;
        *((_DWORD *)dword_4FC4E0 + 1) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 952;
        v141 = dword_4FC4E0 + 8;
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
        dword_4FC4E0[7] = v144;
        *((_WORD *)dword_4FC4E0 + 4) = -10101;
        *((_WORD *)dword_4FC4E0 + 5) = -7295;
        *((_DWORD *)dword_4FC4E0 + 3) = 3;
        dword_4FC4E0[16] = 37;
        *(_DWORD *)(dword_4FC4E0 + 17) = -4;
        dword_4FC4E0[21] = 80;
        dword_4FC4E0[22] = -24;
        *(_DWORD *)(dword_4FC4E0 + 23) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 421;
        *(_WORD *)(dword_4FC4E0 + 27) = 3211;
        dword_4FC4E0[29] = -99;
        *(_DWORD *)(dword_4FC4E0 + 30) = byte_45591C;
        *((_WORD *)dword_4FC4E0 + 17) = -16093;
        *((_WORD *)dword_4FC4E0 + 18) = 3211;
        dword_4FC4E0[38] = -99;
        *(_DWORD *)(dword_4FC4E0 + 39) = byte_45592C;
        *(_WORD *)(dword_4FC4E0 + 43) = 24203;
        dword_4FC4E0[45] = v145;
        *((_WORD *)dword_4FC4E0 + 23) = -7213;
LABEL_384:
        *((_WORD *)dword_4FC4E0 + 24) = -10229;
        dword_4FC4E0[50] = 88;
        dword_4FC4E0[51] = -24;
        *((_DWORD *)dword_4FC4E0 + 13) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 904;
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
          dword_4FC4E0[2] = -112;
          dword_4FC4E0[3] = 87;
          dword_4FC4E0[4] = 86;
          *(_WORD *)(dword_4FC4E0 + 5) = 18119;
          dword_4FC4E0[7] = -116;
          *((_DWORD *)dword_4FC4E0 + 2) = v7;
          v148 = op_LWC2;
          goto LABEL_414;
        }
        *v2 = -72;
        *(_DWORD *)(dword_4FC4E0 + 1) = v147;
        *(_WORD *)(dword_4FC4E0 + 5) = 17923;
        dword_4FC4E0[7] = 4 * ((v7 >> 21) & 0x1F);
        dword_4FC4E0[8] = -24;
        *(_DWORD *)(dword_4FC4E0 + 9) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 435;
        if ( v146 == 28 )
        {
LABEL_355:
          dword_4FC4E0 += 13;
        }
        else if ( v146 == 4 || v146 == 12 || v146 == 20 || v146 == 32 || v146 == 36 || v146 == 40 || v146 == 44 )
        {
          *(_WORD *)(dword_4FC4E0 + 13) = -16625;
          dword_4FC4E0[15] = -64;
          dword_4FC4E0[16] = -93;
          *(_DWORD *)(dword_4FC4E0 + 17) = (char *)&gte_regs + v146;
          dword_4FC4E0 += 21;
        }
        else
        {
          dword_4FC4E0[13] = -93;
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
          dword_4FC4E0[2] = -112;
          dword_4FC4E0[3] = 87;
          dword_4FC4E0[4] = 86;
          *(_WORD *)(dword_4FC4E0 + 5) = 18119;
          dword_4FC4E0[7] = -116;
          *((_DWORD *)dword_4FC4E0 + 2) = v7;
          v148 = op_SWC2;
LABEL_414:
          dword_4FC4E0[12] = -24;
          *(_DWORD *)(dword_4FC4E0 + 13) = v148 - dword_4FC4E0 - 17;
          dword_4FC4E0[17] = 94;
          dword_4FC4E0[18] = 95;
          *(_WORD *)(dword_4FC4E0 + 19) = 32653;
          dword_4FC4E0[21] = -5;
          dword_4FC4E0 += 22;
        }
        else
        {
          *v2 = -72;
          *(_DWORD *)(dword_4FC4E0 + 1) = v150;
          *(_WORD *)(dword_4FC4E0 + 5) = 7563;
          *(_DWORD *)(dword_4FC4E0 + 7) = (char *)&gte_regs + (unsigned __int8)(4 * (BYTE2(v7) & 0x1F));
          *(_WORD *)(dword_4FC4E0 + 11) = 17923;
          dword_4FC4E0[13] = 4 * ((v7 >> 21) & 0x1F);
          dword_4FC4E0[14] = -24;
          *(_DWORD *)(dword_4FC4E0 + 15) = (_BYTE *)dword_5164C0 - dword_4FC4E0 + 941;
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

unsigned int __cdecl sub_4281B0(int a1, int a2)
{
  int v2; // eax
  char *v3; // esi
  LPVOID v4; // ecx
  int v5; // edx
  LPVOID v6; // ebp
  unsigned int v7; // edi
  unsigned int result; // eax
  unsigned int v9; // edx

  if ( (a1 & 0xFFF00000) == 0xBFC00000 )
    v2 = (a1 & 0x7FFFC) + 0x200000;
  else
    v2 = a1 & 0x1FFFFC;
  v3 = (char *)dword_5164C4;
  v4 = dword_5164C0;
  if ( *(LPVOID *)((char *)dword_5164C4 + v2) != dword_5164C0 )
  {
    v5 = ((_BYTE *)dword_5164C0 - (_BYTE *)dword_5164C8) >> 2;
    *(_DWORD *)((char *)dword_5164C4 + v2) = dword_5164C0;
    if ( v5 )
    {
      while ( 1 )
      {
        v3 = (char *)dword_5164C4;
        v4 = dword_5164C0;
        v6 = *(LPVOID *)((char *)dword_5164C4 + v2 - 4);
        v2 -= 4;
        if ( v6 == dword_5164C0 )
          break;
        --v5;
        *(_DWORD *)((char *)dword_5164C4 + v2) = dword_5164C0;
        if ( !v5 )
          goto LABEL_8;
      }
    }
    else
    {
LABEL_8:
      v4 = dword_5164C0;
      v3 = (char *)dword_5164C4;
    }
  }
  if ( (a1 & 0xFFF00000) == 0xBFC00000 )
    v7 = (a1 & 0x7FFFC) + 0x200000;
  else
    v7 = a1 & 0x1FFFFC;
  result = v7;
  v9 = v7 + 4 * a2;
  if ( v7 < v9 )
  {
    while ( 1 )
    {
      *(_DWORD *)&v3[result] = v4;
      result += 4;
      if ( result >= v9 )
        break;
      v4 = dword_5164C0;
      v3 = (char *)dword_5164C4;
    }
  }
  return result;
}

int dynarec_init()
{
  unsigned int v0; // eax
  unsigned int i; // eax
  int v2; // edi
  int v3; // edi
  int v4; // edi
  int result; // eax

  if ( !dword_5164C0 )
  {
    v0 = (unsigned int)malloc(0x200040u);
    dword_5164C0 = (LPVOID)v0;
    if ( !v0 )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
    if ( (v0 & 0x3F) != 0 )
      dword_5164C0 = (LPVOID)((v0 & 0xFFFFFFC0) + 64);
    dword_5164C4 = malloc(0x280000u);
    if ( !dword_5164C4 )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
    dword_5164C8 = malloc(0x280000u);
    if ( !dword_5164C8 )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
  }
  for ( i = 0; i < 0x280000; i += 4 )
    *(_DWORD *)((char *)dword_5164C4 + i) = dword_5164C0;
  memset(dword_5164C0, 0, 0x200000u);
  memset(dword_5164C8, 0, 0x280000u);
  dword_4FC4E0 = (int)dword_5164C0;
  *(_BYTE *)dword_5164C0 = 80;
  *(_BYTE *)(dword_4FC4E0 + 1) = -24;
  *(_DWORD *)(dword_4FC4E0 + 2) = (char *)dynarec_recompile_block - dword_4FC4E0 - 6;
  *(_WORD *)(dword_4FC4E0 + 6) = 0xC481;
  *(_DWORD *)(dword_4FC4E0 + 8) = 4;
  *(_WORD *)(dword_4FC4E0 + 12) = 8447;
  dword_4FC4E0 += 64;
  *(_BYTE *)dword_4FC4E0 = -24;
  *(_DWORD *)(dword_4FC4E0 + 1) = (char *)dynarec_hw_update - dword_4FC4E0 - 5;
  *(_WORD *)(dword_4FC4E0 + 5) = 0xC781;
  *(_DWORD *)(dword_4FC4E0 + 7) = dword_455940;
  *(_WORD *)(dword_4FC4E0 + 11) = 8447;
  dword_4FC4E0 += 64;
  *(_WORD *)dword_4FC4E0 = -15735;
  *(_WORD *)(dword_4FC4E0 + 2) = -7551;
  *(_DWORD *)(dword_4FC4E0 + 4) = 0xFFF00000;
  *(_WORD *)(dword_4FC4E0 + 8) = 0xFA81;
  *(_DWORD *)(dword_4FC4E0 + 10) = 0xBFC00000;
  *(_BYTE *)(dword_4FC4E0 + 14) = 116;
  *(_BYTE *)(dword_4FC4E0 + 15) = 11;
  *(_BYTE *)(dword_4FC4E0 + 16) = 37;
  *(_DWORD *)(dword_4FC4E0 + 17) = 2097148;
  *(_BYTE *)(dword_4FC4E0 + 21) = 5;
  *(_DWORD *)(dword_4FC4E0 + 22) = dword_5164C4;
  *(_BYTE *)(dword_4FC4E0 + 26) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 27) = 37;
  *(_DWORD *)(dword_4FC4E0 + 28) = 524284;
  *(_BYTE *)(dword_4FC4E0 + 32) = 5;
  *(_DWORD *)(dword_4FC4E0 + 33) = (char *)dword_5164C4 + 0x200000;
  *(_BYTE *)(dword_4FC4E0 + 37) = 0xC3;
  dword_4FC4E0 += 64;
  *(_WORD *)dword_4FC4E0 = -15735;
  *(_WORD *)(dword_4FC4E0 + 2) = 32653;
  *(_BYTE *)(dword_4FC4E0 + 4) = -5;
  *(_WORD *)(dword_4FC4E0 + 5) = -7551;
  *(_DWORD *)(dword_4FC4E0 + 7) = 532676608;
  *(_WORD *)(dword_4FC4E0 + 11) = 0xFA81;
  *(_DWORD *)(dword_4FC4E0 + 13) = 528482304;
  *(_BYTE *)(dword_4FC4E0 + 17) = 116;
  *(_BYTE *)(dword_4FC4E0 + 18) = 21;
  *(_WORD *)(dword_4FC4E0 + 19) = -14197;
  *(_WORD *)(dword_4FC4E0 + 21) = -5695;
  *(_BYTE *)(dword_4FC4E0 + 23) = 16;
  *(_BYTE *)(dword_4FC4E0 + 24) = 37;
  *(_DWORD *)(dword_4FC4E0 + 25) = 0xFFFF;
  *(_WORD *)(dword_4FC4E0 + 29) = 3211;
  *(_BYTE *)(dword_4FC4E0 + 31) = -115;
  *(_DWORD *)(dword_4FC4E0 + 32) = mem_read_hooks;
  *(_WORD *)(dword_4FC4E0 + 36) = 1162;
  *(_BYTE *)(dword_4FC4E0 + 38) = 8;
  *(_BYTE *)(dword_4FC4E0 + 39) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 40) = 37;
  *(_DWORD *)(dword_4FC4E0 + 41) = 0x1FFFFFFF;
  *(_BYTE *)(dword_4FC4E0 + 45) = 61;
  *(_DWORD *)(dword_4FC4E0 + 46) = 0x1F800FFF;
  *(_BYTE *)(dword_4FC4E0 + 50) = 127;
  *(_BYTE *)(dword_4FC4E0 + 51) = 12;
  *(_BYTE *)(dword_4FC4E0 + 52) = 37;
  *(_DWORD *)(dword_4FC4E0 + 53) = 4095;
  *(_WORD *)(dword_4FC4E0 + 57) = -32629;
  *(_DWORD *)(dword_4FC4E0 + 59) = dcache;
  *(_BYTE *)(dword_4FC4E0 + 63) = 0xC3;
  *(_WORD *)(dword_4FC4E0 + 64) = 32393;
  *(_BYTE *)(dword_4FC4E0 + 66) = -112;
  *(_BYTE *)(dword_4FC4E0 + 67) = 80;
  *(_BYTE *)(dword_4FC4E0 + 68) = -24;
  *(_DWORD *)(dword_4FC4E0 + 69) = (char *)&loc_422F00 - dword_4FC4E0 - 73;
  *(_WORD *)(dword_4FC4E0 + 73) = -15231;
  *(_DWORD *)(dword_4FC4E0 + 75) = 4;
  *(_BYTE *)(dword_4FC4E0 + 79) = 0xC3;
  dword_4FC4E0 += 128;
  *(_WORD *)dword_4FC4E0 = -15735;
  *(_WORD *)(dword_4FC4E0 + 2) = 32653;
  *(_BYTE *)(dword_4FC4E0 + 4) = -5;
  *(_WORD *)(dword_4FC4E0 + 5) = -7551;
  *(_DWORD *)(dword_4FC4E0 + 7) = 0x1FC00000;
  *(_WORD *)(dword_4FC4E0 + 11) = 0xFA81;
  *(_DWORD *)(dword_4FC4E0 + 13) = 0x1F800000;
  *(_BYTE *)(dword_4FC4E0 + 17) = 116;
  *(_BYTE *)(dword_4FC4E0 + 18) = 21;
  *(_WORD *)(dword_4FC4E0 + 19) = -14197;
  *(_WORD *)(dword_4FC4E0 + 21) = -5695;
  *(_BYTE *)(dword_4FC4E0 + 23) = 16;
  *(_BYTE *)(dword_4FC4E0 + 24) = 37;
  *(_DWORD *)(dword_4FC4E0 + 25) = 0xFFFF;
  *(_WORD *)(dword_4FC4E0 + 29) = 3211;
  *(_BYTE *)(dword_4FC4E0 + 31) = -115;
  *(_DWORD *)(dword_4FC4E0 + 32) = mem_read_hooks;
  *(_WORD *)(dword_4FC4E0 + 36) = 1163;
  *(_BYTE *)(dword_4FC4E0 + 38) = 8;
  *(_BYTE *)(dword_4FC4E0 + 39) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 40) = 37;
  *(_DWORD *)(dword_4FC4E0 + 41) = 0x1FFFFFFF;
  *(_BYTE *)(dword_4FC4E0 + 45) = 61;
  *(_DWORD *)(dword_4FC4E0 + 46) = 0x1F800FFF;
  *(_BYTE *)(dword_4FC4E0 + 50) = 127;
  *(_BYTE *)(dword_4FC4E0 + 51) = 12;
  *(_BYTE *)(dword_4FC4E0 + 52) = 37;
  *(_DWORD *)(dword_4FC4E0 + 53) = 4095;
  *(_WORD *)(dword_4FC4E0 + 57) = -32629;
  *(_DWORD *)(dword_4FC4E0 + 59) = dcache;
  *(_BYTE *)(dword_4FC4E0 + 63) = 0xC3;
  *(_WORD *)(dword_4FC4E0 + 64) = 32393;
  *(_BYTE *)(dword_4FC4E0 + 66) = -112;
  *(_BYTE *)(dword_4FC4E0 + 67) = 80;
  *(_BYTE *)(dword_4FC4E0 + 68) = -24;
  *(_DWORD *)(dword_4FC4E0 + 69) = (char *)hw_reg_read_half - dword_4FC4E0 - 73;
  *(_WORD *)(dword_4FC4E0 + 73) = -15231;
  *(_DWORD *)(dword_4FC4E0 + 75) = 4;
  *(_BYTE *)(dword_4FC4E0 + 79) = 0xC3;
  dword_4FC4E0 += 128;
  *(_WORD *)dword_4FC4E0 = -15735;
  *(_WORD *)(dword_4FC4E0 + 2) = 32653;
  *(_BYTE *)(dword_4FC4E0 + 4) = -5;
  *(_WORD *)(dword_4FC4E0 + 5) = -7551;
  *(_DWORD *)(dword_4FC4E0 + 7) = 0x1FC00000;
  *(_WORD *)(dword_4FC4E0 + 11) = 0xFA81;
  *(_DWORD *)(dword_4FC4E0 + 13) = 0x1F800000;
  *(_BYTE *)(dword_4FC4E0 + 17) = 116;
  *(_BYTE *)(dword_4FC4E0 + 18) = 21;
  *(_WORD *)(dword_4FC4E0 + 19) = -14197;
  *(_WORD *)(dword_4FC4E0 + 21) = -5695;
  *(_BYTE *)(dword_4FC4E0 + 23) = 16;
  *(_BYTE *)(dword_4FC4E0 + 24) = 37;
  *(_DWORD *)(dword_4FC4E0 + 25) = 0xFFFF;
  *(_WORD *)(dword_4FC4E0 + 29) = 3211;
  *(_BYTE *)(dword_4FC4E0 + 31) = -115;
  *(_DWORD *)(dword_4FC4E0 + 32) = mem_read_hooks;
  *(_WORD *)(dword_4FC4E0 + 36) = 1163;
  *(_BYTE *)(dword_4FC4E0 + 38) = 8;
  *(_BYTE *)(dword_4FC4E0 + 39) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 40) = 37;
  *(_DWORD *)(dword_4FC4E0 + 41) = 0x1FFFFFFF;
  *(_BYTE *)(dword_4FC4E0 + 45) = 61;
  *(_DWORD *)(dword_4FC4E0 + 46) = 528486399;
  *(_BYTE *)(dword_4FC4E0 + 50) = 127;
  *(_BYTE *)(dword_4FC4E0 + 51) = 12;
  *(_BYTE *)(dword_4FC4E0 + 52) = 37;
  *(_DWORD *)(dword_4FC4E0 + 53) = 4095;
  *(_WORD *)(dword_4FC4E0 + 57) = -32629;
  *(_DWORD *)(dword_4FC4E0 + 59) = dcache;
  *(_BYTE *)(dword_4FC4E0 + 63) = 0xC3;
  *(_WORD *)(dword_4FC4E0 + 64) = 32393;
  *(_BYTE *)(dword_4FC4E0 + 66) = -112;
  *(_BYTE *)(dword_4FC4E0 + 67) = 80;
  *(_BYTE *)(dword_4FC4E0 + 68) = -24;
  *(_DWORD *)(dword_4FC4E0 + 69) = (char *)hw_reg_read_word - dword_4FC4E0 - 73;
  *(_WORD *)(dword_4FC4E0 + 73) = -15231;
  *(_DWORD *)(dword_4FC4E0 + 75) = 4;
  *(_BYTE *)(dword_4FC4E0 + 79) = 0xC3;
  dword_4FC4E0 += 128;
  *(_WORD *)dword_4FC4E0 = 0xC289;
  *(_WORD *)(dword_4FC4E0 + 2) = 32653;
  *(_BYTE *)(dword_4FC4E0 + 4) = 0xFB;
  *(_WORD *)(dword_4FC4E0 + 5) = 0xE281;
  *(_DWORD *)(dword_4FC4E0 + 7) = 0x1FC00000;
  *(_WORD *)(dword_4FC4E0 + 11) = 0xFA81;
  *(_DWORD *)(dword_4FC4E0 + 13) = 0x1F800000;
  *(_BYTE *)(dword_4FC4E0 + 17) = 116;
  *(_BYTE *)(dword_4FC4E0 + 18) = 100;
  *(_WORD *)(dword_4FC4E0 + 19) = 3467;
  *(_DWORD *)(dword_4FC4E0 + 21) = &dword_50C2A4;
  *(_WORD *)(dword_4FC4E0 + 25) = 0xC1F7;
  *(_DWORD *)(dword_4FC4E0 + 27) = 0x10000;
  *(_BYTE *)(dword_4FC4E0 + 31) = 117;
  *(_BYTE *)(dword_4FC4E0 + 32) = 85;
  *(_WORD *)(dword_4FC4E0 + 33) = 0xC88B;
  *(_WORD *)(dword_4FC4E0 + 35) = 0xC289;
  *(_WORD *)(dword_4FC4E0 + 37) = 0xE9C1;
  *(_BYTE *)(dword_4FC4E0 + 39) = 16;
  *(_BYTE *)(dword_4FC4E0 + 40) = 37;
  *(_DWORD *)(dword_4FC4E0 + 41) = 0xFFFF;
  *(_WORD *)(dword_4FC4E0 + 45) = 3211;
  *(_BYTE *)(dword_4FC4E0 + 47) = -115;
  *(_DWORD *)(dword_4FC4E0 + 48) = mem_write_hooks;
  *(_WORD *)(dword_4FC4E0 + 52) = 7304;
  *(_BYTE *)(dword_4FC4E0 + 54) = 8;
  dword_45594F = (int)dword_5164C4;
  dword_455958 = (int)dword_5164C0;
  dword_455960 = (int)dword_5164C0;
  dword_455972 = (int)dword_5164C0;
  dword_455968 = (int)dword_5164C8;
  v2 = dword_4FC4E0 + 55;
  qmemcpy((void *)(dword_4FC4E0 + 55), &byte_455948, 0x3Cu);
  v2 += 60;
  *(_WORD *)v2 = word_455984;
  *(_BYTE *)(v2 + 2) = byte_455986;
  *(_BYTE *)(dword_4FC4E0 + 118) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 119) = 61;
  *(_DWORD *)(dword_4FC4E0 + 120) = 0x1F800FFF;
  *(_BYTE *)(dword_4FC4E0 + 124) = 127;
  *(_BYTE *)(dword_4FC4E0 + 125) = 12;
  *(_BYTE *)(dword_4FC4E0 + 126) = 37;
  *(_DWORD *)(dword_4FC4E0 + 127) = 4095;
  *(_WORD *)(dword_4FC4E0 + 131) = -26488;
  *(_DWORD *)(dword_4FC4E0 + 133) = dcache;
  *(_BYTE *)(dword_4FC4E0 + 137) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 138) = 83;
  *(_BYTE *)(dword_4FC4E0 + 139) = 80;
  *(_BYTE *)(dword_4FC4E0 + 140) = -24;
  *(_DWORD *)(dword_4FC4E0 + 141) = (char *)&loc_422730 - dword_4FC4E0 - 145;
  *(_WORD *)(dword_4FC4E0 + 145) = -15231;
  *(_DWORD *)(dword_4FC4E0 + 147) = 8;
  *(_BYTE *)(dword_4FC4E0 + 151) = 0xC3;
  dword_4FC4E0 += 192;
  *(_WORD *)dword_4FC4E0 = -15735;
  *(_WORD *)(dword_4FC4E0 + 2) = 32653;
  *(_BYTE *)(dword_4FC4E0 + 4) = -5;
  *(_WORD *)(dword_4FC4E0 + 5) = -7551;
  *(_DWORD *)(dword_4FC4E0 + 7) = 0x1FC00000;
  *(_WORD *)(dword_4FC4E0 + 11) = 0xFA81;
  *(_DWORD *)(dword_4FC4E0 + 13) = 0x1F800000;
  *(_BYTE *)(dword_4FC4E0 + 17) = 116;
  *(_BYTE *)(dword_4FC4E0 + 18) = 101;
  *(_WORD *)(dword_4FC4E0 + 19) = 3467;
  *(_DWORD *)(dword_4FC4E0 + 21) = &dword_50C2A4;
  *(_WORD *)(dword_4FC4E0 + 25) = -15881;
  *(_DWORD *)(dword_4FC4E0 + 27) = 0x10000;
  *(_BYTE *)(dword_4FC4E0 + 31) = 117;
  *(_BYTE *)(dword_4FC4E0 + 32) = 86;
  *(_WORD *)(dword_4FC4E0 + 33) = -14197;
  *(_WORD *)(dword_4FC4E0 + 35) = -15735;
  *(_WORD *)(dword_4FC4E0 + 37) = -5695;
  *(_BYTE *)(dword_4FC4E0 + 39) = 16;
  *(_BYTE *)(dword_4FC4E0 + 40) = 37;
  *(_DWORD *)(dword_4FC4E0 + 41) = 0xFFFF;
  *(_WORD *)(dword_4FC4E0 + 45) = 3211;
  *(_BYTE *)(dword_4FC4E0 + 47) = -115;
  *(_DWORD *)(dword_4FC4E0 + 48) = mem_write_hooks;
  *(_WORD *)(dword_4FC4E0 + 52) = -30362;
  *(_WORD *)(dword_4FC4E0 + 54) = 284;
  dword_45594F = (int)dword_5164C4;
  dword_455958 = (int)dword_5164C0;
  dword_455960 = (int)dword_5164C0;
  dword_455972 = (int)dword_5164C0;
  dword_455968 = (int)dword_5164C8;
  v3 = dword_4FC4E0 + 56;
  qmemcpy((void *)(dword_4FC4E0 + 56), &byte_455948, 0x3Cu);
  v3 += 60;
  *(_WORD *)v3 = word_455984;
  *(_BYTE *)(v3 + 2) = byte_455986;
  *(_BYTE *)(dword_4FC4E0 + 119) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 120) = 61;
  *(_DWORD *)(dword_4FC4E0 + 121) = 0x1F800FFF;
  *(_BYTE *)(dword_4FC4E0 + 125) = 127;
  *(_BYTE *)(dword_4FC4E0 + 126) = 13;
  *(_BYTE *)(dword_4FC4E0 + 127) = 37;
  *(_DWORD *)(dword_4FC4E0 + 128) = 4095;
  *(_BYTE *)(dword_4FC4E0 + 132) = 102;
  *(_WORD *)(dword_4FC4E0 + 133) = -26487;
  *(_DWORD *)(dword_4FC4E0 + 135) = dcache;
  *(_BYTE *)(dword_4FC4E0 + 139) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 140) = 83;
  *(_BYTE *)(dword_4FC4E0 + 141) = 80;
  *(_BYTE *)(dword_4FC4E0 + 142) = -24;
  *(_DWORD *)(dword_4FC4E0 + 143) = (char *)&loc_422830 - dword_4FC4E0 - 147;
  *(_WORD *)(dword_4FC4E0 + 147) = -15231;
  *(_DWORD *)(dword_4FC4E0 + 149) = 8;
  *(_BYTE *)(dword_4FC4E0 + 153) = 0xC3;
  dword_4FC4E0 += 192;
  *(_WORD *)dword_4FC4E0 = -15735;
  *(_WORD *)(dword_4FC4E0 + 2) = 32653;
  *(_BYTE *)(dword_4FC4E0 + 4) = -5;
  *(_WORD *)(dword_4FC4E0 + 5) = -7551;
  *(_DWORD *)(dword_4FC4E0 + 7) = 0x1FC00000;
  *(_WORD *)(dword_4FC4E0 + 11) = 0xFA81;
  *(_DWORD *)(dword_4FC4E0 + 13) = 0x1F800000;
  *(_BYTE *)(dword_4FC4E0 + 17) = 116;
  *(_BYTE *)(dword_4FC4E0 + 18) = 100;
  *(_WORD *)(dword_4FC4E0 + 19) = 3467;
  *(_DWORD *)(dword_4FC4E0 + 21) = &dword_50C2A4;
  *(_WORD *)(dword_4FC4E0 + 25) = -15881;
  *(_DWORD *)(dword_4FC4E0 + 27) = 0x10000;
  *(_BYTE *)(dword_4FC4E0 + 31) = 117;
  *(_BYTE *)(dword_4FC4E0 + 32) = 85;
  *(_WORD *)(dword_4FC4E0 + 33) = -14197;
  *(_WORD *)(dword_4FC4E0 + 35) = -15735;
  *(_WORD *)(dword_4FC4E0 + 37) = -5695;
  *(_BYTE *)(dword_4FC4E0 + 39) = 16;
  *(_BYTE *)(dword_4FC4E0 + 40) = 37;
  *(_DWORD *)(dword_4FC4E0 + 41) = 0xFFFF;
  *(_WORD *)(dword_4FC4E0 + 45) = 3211;
  *(_BYTE *)(dword_4FC4E0 + 47) = -115;
  *(_DWORD *)(dword_4FC4E0 + 48) = mem_write_hooks;
  *(_WORD *)(dword_4FC4E0 + 52) = 7305;
  *(_BYTE *)(dword_4FC4E0 + 54) = 8;
  dword_45594F = (int)dword_5164C4;
  dword_455958 = (int)dword_5164C0;
  dword_455960 = (int)dword_5164C0;
  dword_455972 = (int)dword_5164C0;
  dword_455968 = (int)dword_5164C8;
  v4 = dword_4FC4E0 + 55;
  qmemcpy((void *)(dword_4FC4E0 + 55), &byte_455948, 0x3Cu);
  v4 += 60;
  *(_WORD *)v4 = word_455984;
  *(_BYTE *)(v4 + 2) = byte_455986;
  *(_BYTE *)(dword_4FC4E0 + 118) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 119) = 61;
  *(_DWORD *)(dword_4FC4E0 + 120) = 0x1F800FFF;
  *(_BYTE *)(dword_4FC4E0 + 124) = 127;
  *(_BYTE *)(dword_4FC4E0 + 125) = 12;
  *(_BYTE *)(dword_4FC4E0 + 126) = 37;
  *(_DWORD *)(dword_4FC4E0 + 127) = 4095;
  *(_WORD *)(dword_4FC4E0 + 131) = 0x9889;
  *(_DWORD *)(dword_4FC4E0 + 133) = dcache;
  *(_BYTE *)(dword_4FC4E0 + 137) = 0xC3;
  *(_BYTE *)(dword_4FC4E0 + 138) = 83;
  *(_BYTE *)(dword_4FC4E0 + 139) = 80;
  *(_BYTE *)(dword_4FC4E0 + 140) = 0xE8;
  *(_DWORD *)(dword_4FC4E0 + 141) = (char *)hw_reg_write_word - dword_4FC4E0 - 145;
  *(_WORD *)(dword_4FC4E0 + 145) = 0xC481;
  *(_DWORD *)(dword_4FC4E0 + 147) = 8;
  *(_BYTE *)(dword_4FC4E0 + 151) = 0xC3;
  result = dword_4FC4E0 + 192;
  dword_4FC4E0 += 192;
  return result;
}

void dynarec_deinit()
{
  if ( dword_5164C0 )
    free(dword_5164C0);
  if ( dword_5164C4 )
    free(dword_5164C4);
  if ( dword_5164C8 )
    free(dword_5164C8);
}

__int64 dynarec_execute()
{
  int v0; // eax
  __int64 v1; // rax
  __int64 v3; // [esp-20h] [ebp-2Ch]

  *(_BYTE *)dword_4FC4E0 = 0xBF;
  *(_DWORD *)(dword_4FC4E0 + 1) = dword_455940;
  *(_BYTE *)(dword_4FC4E0 + 5) = 0xBE;
  *(_DWORD *)(dword_4FC4E0 + 6) = cpu_gpr;
  *(_BYTE *)(dword_4FC4E0 + 10) = 0xB8;
  if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v0 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v0 = *(_DWORD *)reg_pc & 0x1FFFFF;
  LODWORD(v1) = (char *)dword_5164C4 + v0;
  *(_DWORD *)(dword_4FC4E0 + 11) = v1;
  HIDWORD(v1) = dword_4FC4E0;
  *(_WORD *)(dword_4FC4E0 + 15) = 8447;
  dword_4FC4E0 += 64;
  dword_4FC4EC = 0;
  v3 = v1;
  ((void (*)(void))((char *)dword_5164C0 + 1152))();
  return v3;
}

char *dynarec_invalidate()
{
  unsigned int i; // eax

  for ( i = 0; i < 0x280000; i += 4 )
    *(_DWORD *)((char *)dword_5164C4 + i) = dword_5164C0;
  dword_4FC4E0 = (int)dword_5164C0 + 1216;
  return (char *)dword_5164C0 + 1216;
}