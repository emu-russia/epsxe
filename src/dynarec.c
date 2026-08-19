#include "pch.h"

/* static prototypes for internal functions */
static int dynarec_compile(unsigned int ArgList, int a2);

static char * dynarec_recompile_block(int a1)
{
  unsigned int v1;
  int v2;

  v1 = a1 - (uint32_t)recomp_code_base;
  if ( (unsigned int)(a1 - (uint32_t)recomp_code_base) >= 0x200000 )
    v1 -= 0x40600000;
  *(uint32_t *)reg_pc = v1;
  dynarec_compile(v1, 0x5000u);
  if ( (*(uint32_t *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v2 = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v2 = *(uint32_t *)reg_pc & 0x1FFFFF;
  return (char *)recomp_code_base + v2;
}

static char *dynarec_hw_update()
{
  int v0;
  unsigned int v2;
  int v3;
  int v4;
  unsigned int v5;
  char v6;
  int v7;
  int v8;
  int v9;

  cpu_recomp_state[0] = 0;
  if ( (hw_update_counter & 0xC0000000) == 0x80000000 )
  {
    if ( (*(uint32_t *)int_reg & int_mask) != 0 )
      irq_cpu_interrupt();
    if ( (*(uint32_t *)reg_pc & 0xFFF00000) == 0xBFC00000 )
      v0 = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
    else
      v0 = *(uint32_t *)reg_pc & 0x1FFFFF;
    return (char *)recomp_code_base + v0;
  }
  else
  {
    if ( (++spu_async_update_counter & 0x1F) == 0 )
      spu_async_update_cb(32 * cpu_speed_scale);
    mdec_timer_handler();
    gpu_dma2_interrupt();
    gpu_dma6_interrupt();
    hw_update_counter = cpu_speed_scale;
    ++scanline_counter;
    cdr_play_tick();
    cdr_process_delays();
    if ( (int_reg[0] & 4) == 0 && cdr_get_response_status() )
      *(uint32_t *)int_reg |= 4u;
    if ( spu_irq_pending_count && (int_reg[1] & 2) == 0 )
    {
      *(uint32_t *)int_reg |= 0x200u;
      --spu_irq_pending_count;
    }
    if ( *(uint32_t *)sio_irq_pending )
    {
      *(uint32_t *)int_reg |= *(uint32_t *)sio_irq_pending;
      *(uint32_t *)sio_irq_pending = 0;
    }
    else if ( *(uint32_t *)sio_irq_delay_time )
    {
      *(uint32_t *)sio_irq_pending = 128;
      *(uint32_t *)sio_irq_timeout = *(uint32_t *)sio_irq_delay_time;
      *(uint32_t *)sio_irq_delay_time = 0;
    }
    if ( sio_transfer_pending )
    {
      sio_transfer_pending = 0;
      sio_trigger_rx_ready_irq();
    }
    else if ( sio_scheduled_transfer_timeout )
    {
      sio_transfer_pending = 128;
      sio_transfer_timeout = sio_scheduled_transfer_timeout;
      sio_scheduled_transfer_timeout = 0;
    }
    v2 = cpu_speed_scale;
    v3 = 512;
    if ( (rcnt_mode[0] & 0x100) == 0 )
      v3 = cpu_speed_scale;
    rcnt_counter[0] += v3;
    if ( rcnt_counter[0] >= (unsigned int)rcnt_compare[0] )
    {
      rcnt_counter[0] = 0;
      if ( (rcnt_mode[0] & 0x50) == 0x50 )
        *(uint32_t *)int_reg |= 0x10u;
    }
    v4 = 1;
    if ( (rcnt1_mode & 0x100) == 0 )
      v4 = cpu_speed_scale;
    rcnt1_counter += v4;
    if ( rcnt1_counter >= (unsigned int)rcnt1_compare )
    {
      rcnt1_counter = 0;
      if ( (rcnt1_mode & 0x50) == 0x50 )
        *(uint32_t *)int_reg |= 0x20u;
    }
    if ( (rcnt2_mode & 1) == 0 && xenogears_trick_enabled )
    {
      if ( (rcnt2_mode & 0x200) != 0 )
        v2 = (unsigned int)cpu_speed_scale >> 3;
      v5 = v2 + rcnt2_counter;
      rcnt2_counter = v5;
      if ( v5 >= rcnt2_compare )
      {
        rcnt2_counter = v5 - rcnt2_compare;
        if ( (rcnt2_mode & 0x50) == 0x50 )
          *(uint32_t *)int_reg |= 0x40u;
      }
    }
    v6 = int_mask;
    if ( scanline_counter == video_scanlines - (cd_extra_setting != 0 ? 32 : 1) )
    {
      v7 = *(uint32_t *)int_reg | 1;
      *(uint32_t *)int_reg |= 1u;
      if ( (int_mask & 0x200) != 0 && forcespu && (frame_counter & 3) == 0 )
        *(uint32_t *)int_reg = v7 | 0x200;
    }
    if ( (int_mask & *(uint32_t *)int_reg) != 0 )
    {
      irq_cpu_interrupt();
      v6 = int_mask;
    }
    if ( scanline_counter >= (unsigned int)video_scanlines )
    {
      scanline_counter = 0;
      ++frame_counter;
      ++rcnt3_counter;
      *(uint32_t *)int_reg |= 1u;
      if ( (v6 & 1) != 0 )
        irq_cpu_interrupt();
      gpu_frame_update();
      if ( reset_flag )
      {
        if ( (*(uint32_t *)reg_pc & 0xFFF00000) == 0xBFC00000 )
          v8 = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
        else
          v8 = *(uint32_t *)reg_pc & 0x1FFFFF;
        **(uint32_t **)((char *)recomp_code_base + v8) = 195;
      }
      if ( dynarec_clear_needed )
      {
        dynarec_clear_needed = 0;
        dynarec_invalidate();
      }
      if ( (frame_counter & 0x3F) == 0 )
        cdr_update_motor_status();
      sio_memcard_auto_save();
    }
    if ( (*(uint32_t *)reg_pc & 0xFFF00000) == 0xBFC00000 )
      v9 = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
    else
      v9 = *(uint32_t *)reg_pc & 0x1FFFFF;
    return (char *)recomp_code_base + v9;
  }
}

static int dynarec_compile(unsigned int ArgList, int a2)
{
  uint8_t *v2;
  unsigned int v3;
  unsigned int v4;
  unsigned int v6;
  unsigned int v7;
  uint8_t v8;
  int v9;
  uint8_t v10;
  uint32_t *v11;
  int v12;
  uint8_t v13;
  uint8_t v14;
  uint8_t v15;
  uint8_t v16;
  uint8_t v17;
  uint8_t v18;
  uint8_t v19;
  uint8_t v20;
  uint8_t v21;
  uint8_t v22;
  uint8_t v23;
  uint8_t v24;
  int result;
  uint8_t v26;
  uint8_t v27;
  uint8_t *v28;
  int v29;
  uint8_t *v30;
  uint8_t v31;
  uint8_t v32;
  uint8_t v33;
  uint8_t v34;
  uint8_t v35;
  uint8_t v36;
  uint8_t v37;
  uint8_t v38;
  uint8_t v39;
  uint8_t v40;
  char v41;
  uint8_t v42;
  char v43;
  uint8_t v44;
  unsigned int v45;
  char v46;
  uint8_t v47;
  char v48;
  uint8_t v49;
  unsigned int v50;
  int v51;
  uint8_t *v52;
  int v53;
  int v54;
  int v55;
  char v56;
  char v57;
  uint8_t v58;
  uint8_t v59;
  uint8_t *v60;
  uint8_t *v61;
  char v62;
  char v63;
  uint8_t v64;
  uint8_t v65;
  uint8_t *v66;
  uint8_t *v67;
  char v68;
  uint8_t v69;
  char v70;
  uint8_t v71;
  char v72;
  char v73;
  uint8_t v74;
  uint8_t *v75;
  char v76;
  char v77;
  uint8_t v78;
  uint8_t v79;
  uint8_t v80;
  char v81;
  uint8_t v82;
  uint8_t *v83;
  char v84;
  uint8_t v85;
  uint8_t *v86;
  char v87;
  uint8_t v88;
  uint8_t *v89;
  int v90;
  char v91;
  uint8_t *v92;
  int v93;
  uint8_t v94;
  int v95;
  char v96;
  uint8_t v97;
  GTE_REG *v98;
  uint8_t v99;
  int v100;
  int (*v101)();
  char v102;
  uint8_t v103;
  uint8_t v104;
  uint8_t *v105;
  char v106;
  uint8_t v107;
  uint8_t *v108;
  char v109;
  uint8_t v110;
  uint8_t v111;
  char v112;
  uint8_t v113;
  uint8_t v114;
  uint8_t *v115;
  bool v116;
  char v117;
  uint8_t v118;
  uint8_t v119;
  uint8_t *v120;
  char v121;
  uint8_t v122;
  uint8_t *v123;
  char v124;
  uint8_t v125;
  char v126;
  uint8_t v127;
  uint8_t v128;
  uint8_t *v129;
  char v130;
  uint8_t v131;
  uint8_t v132;
  uint8_t *v133;
  char v134;
  uint8_t v135;
  uint8_t v136;
  char v137;
  uint8_t v138;
  uint8_t v139;
  uint8_t *v140;
  uint8_t *v141;
  unsigned int v142;
  char v143;
  uint8_t v144;
  uint8_t v145;
  uint8_t v146;
  unsigned int v147;
  uint8_t *v148;
  char v149;
  unsigned int v150;
  uint8_t *v151;
  int v152;
  int v153;
  unsigned int v154;
  int v155;
  unsigned int v156;
  char v157;
  int v158;
  uint8_t *v159;
  uint8_t ArgLista;

  v2 = code_ptr;
  v3 = a2;
  v4 = 0;
  v157 = 0;
  v158 = 0;
  v159 = nullptr;
  if ( a2 != 1 && code_ptr - (uint8_t *)recomp_buffer >= 2080768 )
  {
    do
    {
      *(uint32_t *)((char *)recomp_code_base + v4) = recomp_buffer;
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
    v7 = *(uint32_t *)((uint16_t)ArgList + mem_read_hooks[HIWORD(ArgList)]);
    if ( a2 != 1 )
    {
      *(uint32_t *)((char *)recomp_code_base + v6) = v2;
      if ( v158 == 1 )
        v159 = code_ptr;
      *(uint32_t *)((char *)recomp_metadata + v6) = v159;
      v2 = code_ptr;
    }
    if ( active_mini_cheat_count )
    {
      v8 = 0;
      ArgLista = 0;
      do
      {
        v9 = mini_cheat_id_array[2 * ArgLista];
        if ( (v9 & 0x1FFFFF) == ArgList )
        {
          v7 = mini_cheat_attr_array[2 * ArgLista];
          if ( (v9 & 0xF0000000) == 0 )
          {
            v10 = v8 + 1;
            if ( (uint8_t)(v8 + 1) < (uint8_t)active_mini_cheat_count )
            {
              v11 = (uint32_t *)(8 * v10 + 5991868);
              v12 = (uint8_t)(active_mini_cheat_count - v10);
              do
              {
                *(v11 - 1) = v11[1];
                *v11 = v11[2];
                v11 += 2;
                --v12;
              }
              while ( v12 );
            }
            --active_mini_cheat_count;
          }
        }
        ArgLista = ++v8;
      }
      while ( v8 < (uint8_t)active_mini_cheat_count );
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
              *(uint16_t *)code_ptr = 26305;
              goto LABEL_45;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = v15;
            *(uint16_t *)(code_ptr + 3) = -7999;
            goto LABEL_118;
          case 2u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v14 = (v7 >> 6) & 0x1F;
            v16 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v16 == v13 )
            {
              *(uint16_t *)code_ptr = 28353;
              goto LABEL_45;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = v16;
            *(uint16_t *)(code_ptr + 3) = -5951;
            goto LABEL_118;
          case 3u:
            v13 = 4 * ((v7 >> 11) & 0x1F);
            v14 = (v7 >> 6) & 0x1F;
            v17 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v13 )
              goto LABEL_422;
            if ( v17 != v13 )
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v17;
              *(uint16_t *)(code_ptr + 3) = -1855;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = 32449;
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
              *(uint16_t *)code_ptr = 20107;
              code_ptr[2] = v19;
              *(uint16_t *)(code_ptr + 3) = -7807;
              *(uint32_t *)(code_ptr + 5) = 31;
              *(uint16_t *)(code_ptr + 9) = 26323;
              goto LABEL_50;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = v20;
            *(uint16_t *)(code_ptr + 3) = 20107;
            code_ptr[5] = v19;
            *((uint16_t *)code_ptr + 3) = -7807;
            *((uint32_t *)code_ptr + 2) = 31;
            *((uint16_t *)code_ptr + 6) = -7981;
            goto LABEL_130;
          case 6u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v21 = 4 * ((v7 >> 21) & 0x1F);
            v22 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v22 == v18 )
            {
              *(uint16_t *)code_ptr = 20107;
              code_ptr[2] = v21;
              *(uint16_t *)(code_ptr + 3) = -7807;
              *(uint32_t *)(code_ptr + 5) = 31;
              *(uint16_t *)(code_ptr + 9) = 28371;
              goto LABEL_50;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = v22;
            *(uint16_t *)(code_ptr + 3) = 20107;
            code_ptr[5] = v21;
            *((uint16_t *)code_ptr + 3) = -7807;
            *((uint32_t *)code_ptr + 2) = 31;
            *((uint16_t *)code_ptr + 6) = -5933;
            goto LABEL_130;
          case 7u:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            v23 = 4 * ((v7 >> 21) & 0x1F);
            v24 = 4 * (BYTE2(v7) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            if ( v24 == v18 )
            {
              *(uint16_t *)code_ptr = 20107;
              code_ptr[2] = v23;
              *(uint16_t *)(code_ptr + 3) = -7807;
              *(uint32_t *)(code_ptr + 5) = 31;
              *(uint16_t *)(code_ptr + 9) = 32467;
LABEL_50:
              code_ptr[11] = v18;
              code_ptr[12] = 79;
              code_ptr += 13;
            }
            else
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v24;
              *(uint16_t *)(code_ptr + 3) = 20107;
              code_ptr[5] = v23;
              *((uint16_t *)code_ptr + 3) = -7807;
              *((uint32_t *)code_ptr + 2) = 31;
              *((uint16_t *)code_ptr + 6) = -1837;
LABEL_130:
              *((uint16_t *)code_ptr + 7) = 18057;
              code_ptr[16] = v18;
              code_ptr[17] = 79;
              code_ptr += 18;
            }
            goto LABEL_422;
          case 8u:
            if ( a2 == 1 )
              goto LABEL_422;
            *(uint16_t *)v2 = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = 0xC7F7;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *code_ptr = 79;
            *(uint16_t *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * ((v7 >> 21) & 0x1F);
            code_ptr[4] = -24;
            *(uint32_t *)(code_ptr + 5) = (uint8_t *)recomp_buffer - code_ptr + 119;
            code_ptr[9] = 80;
            code_ptr += 10;
            dynarec_compile(ArgList, 1u);
            *code_ptr = 88;
            *(uint16_t *)(code_ptr + 1) = 8447;
            code_ptr += 3;
            *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(uint32_t *)(code_ptr + 3) = ArgList - 4;
            *(uint16_t *)(code_ptr + 7) = 32393;
            code_ptr[9] = -112;
            code_ptr[10] = -24;
            *(uint32_t *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
            *(uint16_t *)(code_ptr + 15) = 0xC7F7;
            *(uint32_t *)(code_ptr + 17) = 0x40000000;
            code_ptr[21] = 116;
            code_ptr[22] = 8;
            *(uint16_t *)(code_ptr + 23) = -14463;
            *(uint32_t *)(code_ptr + 25) = cpu_speed_scale;
            *(uint16_t *)(code_ptr + 29) = 8447;
            *(uint16_t *)(code_ptr + 31) = 0xF781;
            *(uint32_t *)(code_ptr + 33) = 0x80000000;
            goto LABEL_62;
          case 9u:
            if ( a2 == 1 )
              goto LABEL_422;
            *(uint16_t *)v2 = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = 0xC7F7;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            v26 = 4 * ((v7 >> 21) & 0x1F);
            v27 = 4 * ((v7 >> 11) & 0x1F);
            v28 = code_ptr + 11;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            if ( v27 == v26 )
              recomp_special_flags |= 0x800000u;
            *v28 = 79;
            if ( v27 )
            {
              *(uint16_t *)(code_ptr + 1) = 18119;
              code_ptr[3] = v27;
              v29 = ArgList + 4;
              if ( (ArgList & 0xF0000000) == 0 )
                v29 |= 0x80000000;
              *((uint32_t *)code_ptr + 1) = v29;
              *((uint16_t *)code_ptr + 4) = 18059;
              code_ptr[10] = v26;
              code_ptr[11] = -24;
              *((uint32_t *)code_ptr + 3) = (uint8_t *)recomp_buffer - code_ptr + 112;
              code_ptr[16] = 80;
              v30 = code_ptr + 17;
            }
            else
            {
              *(uint16_t *)(code_ptr + 1) = 18059;
              code_ptr[3] = v26;
              code_ptr[4] = -24;
              *(uint32_t *)(code_ptr + 5) = (uint8_t *)recomp_buffer - code_ptr + 119;
              code_ptr[9] = 80;
              v30 = code_ptr + 10;
            }
            code_ptr = v30;
            dynarec_compile(ArgList, 1u);
            *code_ptr = 88;
            *(uint16_t *)(code_ptr + 1) = 8447;
            code_ptr += 3;
            *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(uint32_t *)(code_ptr + 3) = ArgList - 4;
            *(uint16_t *)(code_ptr + 7) = 32393;
            code_ptr[9] = -112;
            code_ptr[10] = -24;
            *(uint32_t *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
            *(uint16_t *)(code_ptr + 15) = 0xC7F7;
            *(uint32_t *)(code_ptr + 17) = 0x40000000;
            code_ptr[21] = 116;
            code_ptr[22] = 8;
            *(uint16_t *)(code_ptr + 23) = -14463;
            *(uint32_t *)(code_ptr + 25) = cpu_speed_scale;
            *(uint16_t *)(code_ptr + 29) = 8447;
            *(uint16_t *)(code_ptr + 31) = -2175;
            *(uint32_t *)(code_ptr + 33) = 0x80000000;
LABEL_62:
            *(uint16_t *)(code_ptr + 37) = 8447;
            goto LABEL_63;
          case 0xCu:
            *(uint16_t *)v2 = 18119;
            code_ptr[2] = -44;
            *(uint32_t *)(code_ptr + 3) = 0;
            code_ptr += 7;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = -52;
            *(uint32_t *)(code_ptr + 3) = ArgList - 4;
            *(uint16_t *)(code_ptr + 7) = 18119;
            code_ptr[9] = -56;
            *(uint32_t *)(code_ptr + 10) = 32;
            *((uint16_t *)code_ptr + 7) = 18059;
            code_ptr[16] = -60;
            *(uint16_t *)(code_ptr + 17) = 26241;
            code_ptr[19] = -60;
            *((uint32_t *)code_ptr + 5) = -64;
            *((uint16_t *)code_ptr + 12) = -7999;
            code_ptr[26] = 2;
            code_ptr[27] = 37;
            *((uint32_t *)code_ptr + 7) = 63;
            *((uint16_t *)code_ptr + 16) = 17929;
            code_ptr[34] = -60;
            code_ptr[35] = -72;
            *((uint32_t *)code_ptr + 9) = (char *)recomp_code_base + 128;
            *((uint16_t *)code_ptr + 20) = 8447;
            code_ptr[42] = 79;
            code_ptr += 43;
            goto LABEL_422;
          case 0xDu:
            recomp_special_flags |= 0x2000u;
            goto LABEL_422;
          case 0x10u:
            v31 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v31 )
              goto LABEL_422;
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = -120;
            goto LABEL_75;
          case 0x11u:
            *(uint16_t *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 18057;
            code_ptr[5] = -120;
            code_ptr[6] = 79;
            code_ptr += 7;
            goto LABEL_422;
          case 0x12u:
            v31 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v31 )
              goto LABEL_422;
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = -124;
LABEL_75:
            *(uint16_t *)(code_ptr + 3) = 18057;
            code_ptr[5] = v31;
            goto LABEL_253;
          case 0x13u:
            *(uint16_t *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 18057;
            code_ptr[5] = -124;
            code_ptr[6] = 79;
            code_ptr += 7;
            goto LABEL_422;
          case 0x18u:
            *(uint16_t *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 28407;
            goto LABEL_81;
          case 0x19u:
            *(uint16_t *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 26359;
LABEL_81:
            code_ptr[5] = 4 * (BYTE2(v7) & 0x1F);
            *((uint16_t *)code_ptr + 3) = 18057;
            code_ptr[8] = -124;
            *(uint16_t *)(code_ptr + 9) = 22153;
            code_ptr[11] = -120;
            code_ptr[12] = 79;
            code_ptr += 13;
            goto LABEL_422;
          case 0x1Au:
            *(uint16_t *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            code_ptr[3] = -103;
            *((uint16_t *)code_ptr + 2) = 20107;
            code_ptr[6] = 4 * (BYTE2(v7) & 0x1F);
            *(uint16_t *)(code_ptr + 7) = -13947;
            *(uint16_t *)(code_ptr + 9) = 2676;
            *(uint16_t *)(code_ptr + 11) = -1545;
            *(uint16_t *)(code_ptr + 13) = 18057;
            code_ptr[15] = -124;
            *((uint16_t *)code_ptr + 8) = 22153;
            code_ptr[18] = -120;
            *(uint16_t *)(code_ptr + 19) = 6123;
            *(uint16_t *)(code_ptr + 21) = 18057;
            code_ptr[23] = -120;
            code_ptr[24] = -70;
            *(uint32_t *)(code_ptr + 25) = -1;
            code_ptr[29] = -87;
            *(uint32_t *)(code_ptr + 30) = 0x80000000;
            *((uint16_t *)code_ptr + 17) = 1396;
            code_ptr[36] = -70;
            *(uint32_t *)(code_ptr + 37) = 1;
            *(uint16_t *)(code_ptr + 41) = 22153;
            code_ptr[43] = -124;
            code_ptr[44] = 79;
            code_ptr += 45;
            goto LABEL_422;
          case 0x1Bu:
            *(uint16_t *)v2 = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = -11727;
            *(uint16_t *)(code_ptr + 5) = 20107;
            code_ptr[7] = 4 * (BYTE2(v7) & 0x1F);
            *((uint16_t *)code_ptr + 4) = -13947;
            *((uint16_t *)code_ptr + 5) = 2676;
            *((uint16_t *)code_ptr + 6) = -3593;
            *((uint16_t *)code_ptr + 7) = 18057;
            code_ptr[16] = -124;
            *(uint16_t *)(code_ptr + 17) = 22153;
            code_ptr[19] = -120;
            *((uint16_t *)code_ptr + 10) = 3051;
            *((uint16_t *)code_ptr + 11) = 18057;
            code_ptr[24] = -120;
            code_ptr[25] = -70;
            *(uint32_t *)(code_ptr + 26) = -1;
            *((uint16_t *)code_ptr + 15) = 22153;
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
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(uint16_t *)(code_ptr + 3) = 17921;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v32;
              *(uint16_t *)(code_ptr + 3) = 17923;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17923;
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
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(uint16_t *)(code_ptr + 3) = 17961;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v33;
              *(uint16_t *)(code_ptr + 3) = 17963;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17963;
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
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(uint16_t *)(code_ptr + 3) = 17953;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v34;
              *(uint16_t *)(code_ptr + 3) = 17955;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17955;
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
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(uint16_t *)(code_ptr + 3) = 17929;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v35;
              *(uint16_t *)(code_ptr + 3) = 17931;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !v14 )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17931;
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
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = v14;
                *(uint16_t *)(code_ptr + 3) = 17969;
                code_ptr[5] = v13;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v36;
              *(uint16_t *)(code_ptr + 3) = 17971;
LABEL_118:
              code_ptr[5] = v14;
              *((uint16_t *)code_ptr + 3) = 18057;
              code_ptr[8] = v13;
              code_ptr[9] = 79;
              code_ptr += 10;
            }
            else
            {
              *(uint16_t *)code_ptr = -16335;
              if ( v14 )
              {
                *((uint16_t *)code_ptr + 1) = 17971;
                code_ptr[4] = v14;
                goto LABEL_273;
              }
LABEL_121:
              *((uint16_t *)code_ptr + 1) = 18057;
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
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = v38;
              *(uint16_t *)(code_ptr + 3) = 17931;
              code_ptr[5] = v39;
              *((uint16_t *)code_ptr + 3) = -12041;
              *((uint16_t *)code_ptr + 4) = 18057;
              code_ptr[10] = v37;
              code_ptr[11] = 79;
              code_ptr += 12;
              goto LABEL_422;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = v39;
            *(uint16_t *)(code_ptr + 3) = -12041;
            break;
          case 0x2Au:
            v40 = 4 * ((v7 >> 11) & 0x1F);
            if ( v40 )
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
              *(uint16_t *)(code_ptr + 3) = 17979;
              code_ptr[5] = 4 * (BYTE2(v7) & 0x1F);
              *((uint16_t *)code_ptr + 3) = -25585;
              code_ptr[8] = -64;
              code_ptr[9] = 37;
              *(uint32_t *)(code_ptr + 10) = 1;
              *((uint16_t *)code_ptr + 7) = 18057;
              code_ptr[16] = v40;
              code_ptr[17] = 79;
              code_ptr += 18;
            }
            goto LABEL_422;
          case 0x2Bu:
            v18 = 4 * ((v7 >> 11) & 0x1F);
            if ( !v18 )
              goto LABEL_422;
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 17979;
            code_ptr[5] = 4 * (BYTE2(v7) & 0x1F);
            *((uint16_t *)code_ptr + 3) = -28145;
            code_ptr[8] = -64;
            code_ptr[9] = 37;
            *(uint32_t *)(code_ptr + 10) = 1;
            goto LABEL_130;
          default:
            fatal_error_with_message_box(
              "SPEC Opcode %02x UNK (PC %08x) (%08x) (%d,%d)\n",
              v7 & 0x3F,
              ArgList - 4,
              *(uint32_t *)reg_pc,
              frame_counter,
              scanline_counter);
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
            v7 = (uint16_t)v7;
            v42 = 4 * v41;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(uint16_t *)v2 = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = -16335;
            code_ptr[2] = 79;
            *(uint16_t *)(code_ptr + 3) = 17977;
            code_ptr[5] = v42;
            code_ptr[6] = 124;
            goto LABEL_141;
          case 1:
            if ( a2 == 1 )
              goto LABEL_422;
            v43 = (v7 >> 21) & 0x1F;
            v7 = (uint16_t)v7;
            v44 = 4 * v43;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(uint16_t *)v2 = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = -16335;
            code_ptr[2] = 79;
            *(uint16_t *)(code_ptr + 3) = 17977;
            code_ptr[5] = v44;
            code_ptr[6] = 125;
            goto LABEL_141;
          case 0x10:
            if ( a2 == 1 )
              goto LABEL_422;
            v46 = (v7 >> 21) & 0x1F;
            v7 = (uint16_t)v7;
            v47 = 4 * v46;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(uint16_t *)v2 = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 124;
            *(uint32_t *)(code_ptr + 3) = (ArgList + 4) | 0x80000000;
            *(uint16_t *)(code_ptr + 7) = -16335;
            code_ptr[9] = 79;
            *((uint16_t *)code_ptr + 5) = 17977;
            code_ptr[12] = v47;
            code_ptr[13] = 124;
            goto LABEL_151;
          case 0x11:
            if ( a2 == 1 )
              goto LABEL_422;
            v48 = (v7 >> 21) & 0x1F;
            v7 = (uint16_t)v7;
            v49 = 4 * v48;
            if ( (v7 & 0x8000) != 0 )
              v7 |= 0xFFFF0000;
            *(uint16_t *)v2 = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 124;
            *(uint32_t *)(code_ptr + 3) = (ArgList + 4) | 0x80000000;
            *(uint16_t *)(code_ptr + 7) = -16335;
            code_ptr[9] = 79;
            *((uint16_t *)code_ptr + 5) = 17977;
            code_ptr[12] = v49;
            code_ptr[13] = 125;
LABEL_151:
            code_ptr[14] = 7;
            code_ptr[15] = -72;
            if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
              v50 = (ArgList & 0x7FFFF) + 0x200000;
            else
              v50 = ArgList & 0x1FFFFF;
            *((uint32_t *)code_ptr + 4) = (char *)recomp_code_base + v50;
            *((uint16_t *)code_ptr + 10) = 8447;
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
          if ( !cpu_overclock_setting || ((v51 ^ (ArgList - 4)) & 0xFFFFFF) != 0 )
          {
            *(uint16_t *)code_ptr = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
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
            *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + v53;
            *(uint16_t *)(code_ptr + 5) = 8447;
            code_ptr += 7;
            *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(uint32_t *)(code_ptr + 3) = ArgList - 4;
            *(uint16_t *)(code_ptr + 7) = 32393;
            code_ptr[9] = -112;
            code_ptr[10] = -24;
            *(uint32_t *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
            *(uint16_t *)(code_ptr + 15) = -14345;
            *(uint32_t *)(code_ptr + 17) = 0x40000000;
            code_ptr[21] = 116;
            code_ptr[22] = 8;
            *(uint16_t *)(code_ptr + 23) = -14463;
            *(uint32_t *)(code_ptr + 25) = cpu_speed_scale;
            *(uint16_t *)(code_ptr + 29) = 8447;
            *(uint16_t *)(code_ptr + 31) = -2175;
            *(uint32_t *)(code_ptr + 33) = 0x80000000;
            *(uint16_t *)(code_ptr + 37) = 8447;
            code_ptr += 39;
            ArgList = v51 | ArgList & 0xF0000000;
          }
        }
        goto LABEL_422;
      case 3u:
        if ( a2 != 1 )
        {
          *(uint16_t *)code_ptr = 32267;
          code_ptr[2] = -44;
          *(uint16_t *)(code_ptr + 3) = -14345;
          *(uint32_t *)(code_ptr + 5) = 0x80000000;
          code_ptr[9] = 117;
          v54 = 4 * (v7 & 0x3FFFFFF);
          patch_offset_ptr = (int)(code_ptr + 10);
          code_ptr += 11;
          *code_ptr = 79;
          *(uint16_t *)(code_ptr + 1) = 18119;
          code_ptr[3] = 124;
          if ( (ArgList & 0xF0000000) != 0 )
            *((uint32_t *)code_ptr + 1) = ArgList + 4;
          else
            *((uint32_t *)code_ptr + 1) = (ArgList + 4) | 0x80000000;
          code_ptr += 8;
          dynarec_compile(ArgList, 1u);
          *code_ptr = -72;
          if ( (v54 & 0xFFF00000 | ArgList & 0xF0000000) == 0xBFC00000 )
            v55 = (v54 & 0x7FFFF) + 0x200000;
          else
            v55 = v54 & 0x1FFFFF;
          *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + v55;
          *(uint16_t *)(code_ptr + 5) = 8447;
          code_ptr += 7;
          *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
          *(uint16_t *)code_ptr = 18119;
          code_ptr[2] = 0x80;
          *(uint32_t *)(code_ptr + 3) = ArgList - 4;
          *(uint16_t *)(code_ptr + 7) = 32393;
          code_ptr[9] = -112;
          code_ptr[10] = -24;
          *(uint32_t *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
          *(uint16_t *)(code_ptr + 15) = -14345;
          *(uint32_t *)(code_ptr + 17) = 0x40000000;
          code_ptr[21] = 116;
          code_ptr[22] = 8;
          *(uint16_t *)(code_ptr + 23) = -14463;
          *(uint32_t *)(code_ptr + 25) = cpu_speed_scale;
          *(uint16_t *)(code_ptr + 29) = 8447;
          *(uint16_t *)(code_ptr + 31) = -2175;
          *(uint32_t *)(code_ptr + 33) = 0x80000000;
          *(uint16_t *)(code_ptr + 37) = 8447;
          ArgList = v54 | ArgList & 0xF0000000;
          code_ptr += 39;
        }
        goto LABEL_422;
      case 4u:
        if ( a2 == 1 )
          goto LABEL_422;
        v56 = (v7 >> 21) & 0x1F;
        v57 = BYTE2(v7) & 0x1F;
        v7 = (uint16_t)v7;
        v58 = 4 * v56;
        v59 = 4 * v57;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(uint16_t *)v2 = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        v60 = code_ptr + 11;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        if ( v59 )
        {
          *(uint16_t *)v60 = 18059;
          code_ptr[2] = v59;
          v61 = code_ptr + 3;
        }
        else
        {
          *(uint16_t *)v60 = -16335;
          v61 = code_ptr + 2;
        }
        code_ptr = v61;
        *v61 = 79;
        *(uint16_t *)(code_ptr + 1) = 17977;
        code_ptr[3] = v58;
        code_ptr[4] = 116;
        goto LABEL_436;
      case 5u:
        if ( a2 == 1
          || cpu_overclock_setting
          && v7 == 339804155
          && *(uint32_t *)((uint16_t)(ArgList - 8) + mem_read_hooks[(ArgList - 8) >> 16]) == 4395045
          && !*(uint32_t *)((uint16_t)(ArgList - 12) + mem_read_hooks[(ArgList - 12) >> 16])
          && (*(uint32_t *)((uint16_t)(ArgList - 16) + mem_read_hooks[(ArgList - 16) >> 16]) & 0xFFFF0000) == 0x8C830000
          && (*(uint32_t *)((uint16_t)(ArgList - 20) + mem_read_hooks[(ArgList - 20) >> 16]) & 0xFFFF0000) == 0x8CA20000 )
        {
          goto LABEL_422;
        }
        v62 = (v7 >> 21) & 0x1F;
        v63 = BYTE2(v7) & 0x1F;
        v7 = (uint16_t)v7;
        v64 = 4 * v62;
        v65 = 4 * v63;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(uint16_t *)code_ptr = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        v66 = code_ptr + 11;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        if ( v65 )
        {
          *(uint16_t *)v66 = 18059;
          code_ptr[2] = v65;
          v67 = code_ptr + 3;
        }
        else
        {
          *(uint16_t *)v66 = -16335;
          v67 = code_ptr + 2;
        }
        code_ptr = v67;
        *v67 = 79;
        *(uint16_t *)(code_ptr + 1) = 17977;
        code_ptr[3] = v64;
        code_ptr[4] = 117;
LABEL_436:
        code_ptr[5] = 7;
        code_ptr[6] = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v154 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v154 = ArgList & 0x1FFFFF;
        *(uint32_t *)(code_ptr + 7) = (char *)recomp_code_base + v154;
        *(uint16_t *)(code_ptr + 11) = 8447;
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
        v7 = (uint16_t)v7;
        v69 = 4 * v68;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(uint16_t *)v2 = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        *(uint16_t *)code_ptr = -16335;
        code_ptr[2] = 79;
        *(uint16_t *)(code_ptr + 3) = 17977;
        code_ptr[5] = v69;
        code_ptr[6] = 126;
        goto LABEL_141;
      case 7u:
        if ( a2 == 1 )
          goto LABEL_422;
        v70 = (v7 >> 21) & 0x1F;
        v7 = (uint16_t)v7;
        v71 = 4 * v70;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *(uint16_t *)v2 = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        *(uint16_t *)code_ptr = -16335;
        code_ptr[2] = 79;
        *(uint16_t *)(code_ptr + 3) = 17977;
        code_ptr[5] = v71;
        code_ptr[6] = 127;
LABEL_141:
        code_ptr[7] = 7;
        code_ptr[8] = -72;
        if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
          v45 = (ArgList & 0x7FFFF) + 0x200000;
        else
          v45 = ArgList & 0x1FFFFF;
        *(uint32_t *)(code_ptr + 9) = (char *)recomp_code_base + v45;
        *(uint16_t *)(code_ptr + 13) = 8447;
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
        *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + v153;
        *(uint16_t *)(code_ptr + 5) = 8447;
        code_ptr += 7;
        *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
        *(uint16_t *)code_ptr = 18119;
        code_ptr[2] = 0x80;
        *(uint32_t *)(code_ptr + 3) = ArgList - 4;
        *(uint16_t *)(code_ptr + 7) = 32393;
        code_ptr[9] = -112;
        code_ptr[10] = -24;
        *(uint32_t *)(code_ptr + 11) = (char *)dynarec_hw_update - (char *)code_ptr - 15;
        *(uint16_t *)(code_ptr + 15) = -14345;
        *(uint32_t *)(code_ptr + 17) = 0x40000000;
        code_ptr[21] = 116;
        code_ptr[22] = 8;
        *(uint16_t *)(code_ptr + 23) = -14463;
        *(uint32_t *)(code_ptr + 25) = cpu_speed_scale;
        *(uint16_t *)(code_ptr + 29) = 8447;
        *(uint16_t *)(code_ptr + 31) = -2175;
        *(uint32_t *)(code_ptr + 33) = 0x80000000;
        *(uint16_t *)(code_ptr + 37) = 8447;
LABEL_63:
        code_ptr += 39;
        return v158;
      case 8u:
      case 9u:
        v72 = (v7 >> 21) & 0x1F;
        v73 = BYTE2(v7) & 0x1F;
        v7 = (uint16_t)v7;
        v74 = 4 * v72;
        v37 = 4 * v73;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( !v37 )
          goto LABEL_422;
        if ( v74 == v37 )
        {
          *(uint16_t *)code_ptr = 18049;
          goto LABEL_197;
        }
        if ( v74 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = v74;
          v75 = code_ptr + 3;
        }
        else
        {
          *(uint16_t *)code_ptr = -16335;
          v75 = code_ptr + 2;
        }
        code_ptr = v75;
        *v75 = 5;
        goto LABEL_202;
      case 0xAu:
        v76 = (v7 >> 21) & 0x1F;
        v77 = BYTE2(v7) & 0x1F;
        v7 = (uint16_t)v7;
        v78 = 4 * v76;
        v79 = 4 * v77;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v79 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = v78;
          code_ptr[3] = 61;
          *((uint32_t *)code_ptr + 1) = v7;
          *((uint16_t *)code_ptr + 4) = -25585;
          code_ptr[10] = -64;
          code_ptr[11] = 37;
          *((uint32_t *)code_ptr + 3) = 1;
          *((uint16_t *)code_ptr + 8) = 18057;
          code_ptr[18] = v79;
          code_ptr[19] = 79;
          code_ptr += 20;
        }
        goto LABEL_422;
      case 0xBu:
        v80 = 4 * (BYTE2(v7) & 0x1F);
        if ( v80 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = 4 * ((v7 >> 21) & 0x1F);
          code_ptr[3] = 61;
          *((uint32_t *)code_ptr + 1) = (uint16_t)v7;
          *((uint16_t *)code_ptr + 4) = -28145;
          code_ptr[10] = -64;
          code_ptr[11] = 37;
          *((uint32_t *)code_ptr + 3) = 1;
          *((uint16_t *)code_ptr + 8) = 18057;
          code_ptr[18] = v80;
          code_ptr[19] = 79;
          code_ptr += 20;
        }
        goto LABEL_422;
      case 0xCu:
        v81 = (v7 >> 21) & 0x1F;
        v37 = 4 * (BYTE2(v7) & 0x1F);
        v7 = (uint16_t)v7;
        v82 = 4 * v81;
        if ( !v37 )
          goto LABEL_422;
        if ( v82 == v37 )
        {
          *(uint16_t *)code_ptr = 26241;
          goto LABEL_197;
        }
        if ( v82 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = v82;
          v83 = code_ptr + 3;
          code_ptr += 3;
        }
        else
        {
          *(uint16_t *)code_ptr = -16335;
          v83 = code_ptr + 2;
          code_ptr += 2;
        }
        *v83 = 37;
        goto LABEL_202;
      case 0xDu:
        v84 = (v7 >> 21) & 0x1F;
        v37 = 4 * (BYTE2(v7) & 0x1F);
        v7 = (uint16_t)v7;
        v85 = 4 * v84;
        if ( !v37 )
          goto LABEL_422;
        if ( v85 == v37 )
        {
          *(uint16_t *)code_ptr = 20097;
          goto LABEL_197;
        }
        if ( v85 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = v85;
          v86 = code_ptr + 3;
          code_ptr += 3;
        }
        else
        {
          *(uint16_t *)code_ptr = -16335;
          v86 = code_ptr + 2;
          code_ptr += 2;
        }
        *v86 = 13;
        goto LABEL_202;
      case 0xEu:
        v87 = (v7 >> 21) & 0x1F;
        v37 = 4 * (BYTE2(v7) & 0x1F);
        v7 = (uint16_t)v7;
        v88 = 4 * v87;
        if ( !v37 )
          goto LABEL_422;
        if ( v88 == v37 )
        {
          *(uint16_t *)code_ptr = 30337;
LABEL_197:
          code_ptr[2] = v37;
          *(uint32_t *)(code_ptr + 3) = v7;
          code_ptr[7] = 79;
          code_ptr += 8;
        }
        else
        {
          if ( v88 )
          {
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = v88;
            v89 = code_ptr + 3;
            code_ptr += 3;
          }
          else
          {
            *(uint16_t *)code_ptr = -16335;
            v89 = code_ptr + 2;
            code_ptr += 2;
          }
          *v89 = 53;
LABEL_202:
          *(uint32_t *)(code_ptr + 1) = v7;
LABEL_203:
          *(uint16_t *)(code_ptr + 5) = 18057;
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
          *(uint32_t *)(code_ptr + 1) = (uint16_t)v7 << 16;
LABEL_273:
          *(uint16_t *)(code_ptr + 5) = 18057;
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
              *(uint16_t *)code_ptr = 32393;
              code_ptr[2] = -112;
              code_ptr[3] = 87;
              code_ptr[4] = 86;
              *(uint16_t *)(code_ptr + 5) = 18119;
              code_ptr[7] = -116;
              *((uint32_t *)code_ptr + 2) = v7;
              v92 = op_MTC0;
LABEL_242:
              code_ptr[12] = -24;
LABEL_243:
              *(uint32_t *)(code_ptr + 13) = v92 - code_ptr - 17;
              code_ptr[17] = 94;
              code_ptr[18] = 95;
              code_ptr[19] = 79;
              code_ptr += 20;
            }
            else
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = 4 * (BYTE2(v7) & 0x1F);
              *(uint16_t *)(code_ptr + 3) = 18057;
              code_ptr[5] = (v91 & 0x3F) - 108;
              code_ptr[6] = 79;
              code_ptr += 7;
              if ( v91 == 48 || v91 == 52 )
              {
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = -60;
                code_ptr[3] = 37;
                *((uint32_t *)code_ptr + 1) = 257;
                code_ptr[8] = 61;
                *(uint32_t *)(code_ptr + 9) = 257;
                code_ptr[13] = 117;
                code_ptr[14] = 50;
                *(uint16_t *)(code_ptr + 15) = 18059;
                code_ptr[17] = -56;
                code_ptr[18] = 37;
                *(uint32_t *)(code_ptr + 19) = 256;
                code_ptr[23] = 61;
                *((uint32_t *)code_ptr + 6) = 256;
                code_ptr[28] = 117;
                code_ptr[29] = 35;
                *((uint16_t *)code_ptr + 15) = 18119;
                code_ptr[32] = -52;
                *(uint32_t *)(code_ptr + 33) = ArgList;
                *(uint16_t *)(code_ptr + 37) = 18059;
                code_ptr[39] = -60;
                *((uint16_t *)code_ptr + 20) = 26241;
                code_ptr[42] = -60;
                *(uint32_t *)(code_ptr + 43) = -256;
                *(uint16_t *)(code_ptr + 47) = -7999;
                code_ptr[49] = 2;
                code_ptr[50] = 37;
                *(uint32_t *)(code_ptr + 51) = 63;
                *(uint16_t *)(code_ptr + 55) = 17929;
                code_ptr[57] = -60;
                code_ptr[58] = -72;
                *(uint32_t *)(code_ptr + 59) = (char *)recomp_code_base + 128;
                *(uint16_t *)(code_ptr + 63) = 8447;
                code_ptr += 65;
              }
              if ( v91 == 48 )
              {
                *code_ptr = -95;
                *(uint32_t *)(code_ptr + 1) = int_reg;
                *(uint16_t *)(code_ptr + 5) = 1315;
                *(uint32_t *)(code_ptr + 7) = &int_mask;
                code_ptr[11] = -87;
                *((uint32_t *)code_ptr + 3) = 1019;
                code_ptr[16] = 116;
                code_ptr[17] = 22;
                *((uint16_t *)code_ptr + 9) = 18059;
                code_ptr[20] = -60;
                code_ptr[21] = 37;
                *(uint32_t *)(code_ptr + 22) = 1025;
                code_ptr[26] = 61;
                *(uint32_t *)(code_ptr + 27) = 1025;
                code_ptr[31] = 117;
                code_ptr[32] = 7;
                *(uint16_t *)(code_ptr + 33) = 18119;
                code_ptr[35] = -44;
                *((uint32_t *)code_ptr + 9) = 0x80000000;
                code_ptr += 40;
              }
            }
          }
          else
          {
            if ( v90 != 16 )
              fatal_error_with_message_box(" COP0 Opcode %02x UNK \n", (v7 >> 21) & 0x1F);
            *(uint16_t *)v2 = 18059;
            code_ptr[2] = -60;
            *(uint16_t *)(code_ptr + 3) = 26241;
            code_ptr[5] = -60;
            *(uint32_t *)(code_ptr + 6) = -16;
            *((uint16_t *)code_ptr + 5) = -5951;
            code_ptr[12] = 2;
            code_ptr[13] = 37;
            *(uint32_t *)(code_ptr + 14) = 15;
            *((uint16_t *)code_ptr + 9) = 17929;
            code_ptr[20] = -60;
            code_ptr[21] = 79;
            code_ptr += 22;
            *code_ptr = -95;
            *(uint32_t *)(code_ptr + 1) = int_reg;
            *(uint16_t *)(code_ptr + 5) = 1315;
            *(uint32_t *)(code_ptr + 7) = &int_mask;
            code_ptr[11] = -87;
            *((uint32_t *)code_ptr + 3) = 1019;
            code_ptr[16] = 116;
            code_ptr[17] = 22;
            *((uint16_t *)code_ptr + 9) = 18059;
            code_ptr[20] = -60;
            code_ptr[21] = 37;
            *(uint32_t *)(code_ptr + 22) = 1025;
            code_ptr[26] = 61;
            *(uint32_t *)(code_ptr + 27) = 1025;
            code_ptr[31] = 117;
            code_ptr[32] = 7;
            *(uint16_t *)(code_ptr + 33) = 18119;
            code_ptr[35] = -44;
            *((uint32_t *)code_ptr + 9) = 0x80000000;
            code_ptr += 40;
          }
        }
        else
        {
          v93 = (uint8_t)(4 * ((v7 >> 11) & 0x1F));
          v94 = 4 * (BYTE2(v7) & 0x1F);
          if ( (uint8_t)v93 == 12 )
          {
            *(uint16_t *)v2 = 32393;
            code_ptr[2] = -112;
            code_ptr[3] = 87;
            code_ptr[4] = 86;
            *(uint16_t *)(code_ptr + 5) = 18119;
            code_ptr[7] = -116;
            *((uint32_t *)code_ptr + 2) = v7;
            code_ptr[12] = -24;
            *(uint32_t *)(code_ptr + 13) = (char *)op_MFC0 - (char *)code_ptr - 17;
            code_ptr[17] = 94;
            code_ptr[18] = 95;
            code_ptr[19] = 79;
            code_ptr += 20;
          }
          else if ( v94 )
          {
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = (v93 & 0x3F) - 108;
            *(uint16_t *)(code_ptr + 3) = 18057;
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
              && *(uint32_t *)((uint16_t)ArgList + mem_read_hooks[HIWORD(ArgList)]) == 6166570 )
            {
              v2[18] = -95;
              *(uint32_t *)(code_ptr + 19) = (char *)&gte_regs + (uint8_t)(4 * ((v7 >> 11) & 0x1F));
              *(uint16_t *)(code_ptr + 23) = 18057;
              code_ptr[25] = 4 * (BYTE2(v7) & 0x1F);
              code_ptr[26] = 79;
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = 8;
              *(uint16_t *)(code_ptr + 3) = 17979;
              code_ptr[5] = 120;
              *((uint16_t *)code_ptr + 3) = -25585;
              code_ptr[8] = -64;
              code_ptr[9] = 37;
              *(uint32_t *)(code_ptr + 10) = 1;
              *((uint16_t *)code_ptr + 7) = 18057;
              code_ptr[16] = 12;
              code_ptr[17] = 79;
              code_ptr += 27;
              ArgList += 4;
              goto LABEL_422;
            }
            if ( a2 != 1 )
              goto LABEL_265;
            v95 = (uint16_t)*(uint32_t *)((uint16_t)(ArgList - 8) + mem_read_hooks[(ArgList - 8) >> 16]);
            if ( (v95 & 0x8000) != 0 )
              v95 |= 0xFFFF0000;
            if ( *(uint32_t *)((uint16_t)(ArgList + 4 * v95 - 4) + mem_read_hooks[(ArgList + 4 * v95 - 4) >> 16]) != 1216872448 )
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
                  *(uint32_t *)(code_ptr + 1) = (char *)&gte_regs + (uint8_t)(4 * ((v7 >> 11) & 0x1F));
                  goto LABEL_203;
                }
                *(uint16_t *)v2 = 32393;
                code_ptr[2] = -112;
                code_ptr[3] = 87;
                code_ptr[4] = 86;
                *(uint16_t *)(code_ptr + 5) = 18119;
                code_ptr[7] = -116;
                *((uint32_t *)code_ptr + 2) = v7;
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
              *(uint32_t *)(code_ptr + 1) = (char *)gte_regs.ctrl + (uint8_t)(4 * ((v7 >> 11) & 0x1F));
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
            *(uint16_t *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * (BYTE2(v7) & 0x1F);
            if ( v97 == 1 || v97 == 3 || v97 == 5 || v97 == 8 || v97 == 9 || v97 == 10 || v97 == 11 )
            {
              *((uint16_t *)code_ptr + 2) = -16625;
              v98 = &gte_regs.data[v97];
              goto LABEL_286;
            }
            code_ptr[4] = -93;
            *(uint32_t *)(code_ptr + 5) = (char *)&gte_regs + v97 * 4;
            code_ptr += 9;
            goto LABEL_422;
          case 6u:
            *v2 = 79;
            v99 = (v7 >> 11) & 0x1F;
            *(uint16_t *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * (BYTE2(v7) & 0x1F);
            if ( v99 == 4 || v99 == 12 || v99 == 20 || v99 == 26 || v99 == 27 || v99 == 29 || v99 == 30 )
            {
              *((uint16_t *)code_ptr + 2) = -16625;
              v98 = &gte_regs.ctrl[v99];
LABEL_286:
              code_ptr[6] = -64;
              code_ptr[7] = -93;
              *((uint32_t *)code_ptr + 2) = v98;
              code_ptr += 12;
            }
            else
            {
              code_ptr[4] = -93;
              *(uint32_t *)(code_ptr + 5) = &gte_regs.ctrl[v99];
              code_ptr += 9;
            }
            goto LABEL_422;
          default:
            v100 = v7 & 0x1FFFFFF;
            if ( (v7 & 0x1FFFFFF) > 0x280030 )
            {
              if ( v100 != 20971526 )
                goto LABEL_304;
              *(uint16_t *)v2 = 1479;
              *(uint32_t *)(code_ptr + 2) = &gte_regs.ctrl[31];
              *(uint32_t *)(code_ptr + 6) = 0;
              *((uint16_t *)code_ptr + 5) = -16625;
              code_ptr[12] = 5;
              *(uint32_t *)(code_ptr + 13) = &gte_regs.data[13].s16.lo;
              *(uint16_t *)(code_ptr + 17) = -16625;
              code_ptr[19] = 13;
              *((uint32_t *)code_ptr + 5) = &gte_regs.data[14].s16.lo;
              *((uint16_t *)code_ptr + 12) = -16625;
              code_ptr[26] = 21;
              *(uint32_t *)(code_ptr + 27) = &gte_regs.data[12];
              *(uint16_t *)(code_ptr + 31) = -16085;
              *(uint16_t *)(code_ptr + 33) = -20721;
              code_ptr[35] = -62;
              *((uint16_t *)code_ptr + 18) = -10101;
              *((uint16_t *)code_ptr + 19) = -16625;
              code_ptr[40] = 5;
              *(uint32_t *)(code_ptr + 41) = &gte_regs.data[12].s16.lo;
              *(uint16_t *)(code_ptr + 45) = -16625;
              code_ptr[47] = 21;
              *((uint32_t *)code_ptr + 12) = &gte_regs.data[13];
              *((uint16_t *)code_ptr + 26) = -14293;
              *((uint16_t *)code_ptr + 27) = -20721;
              code_ptr[56] = -54;
              *(uint16_t *)(code_ptr + 57) = -9981;
              *(uint16_t *)(code_ptr + 59) = -16625;
              code_ptr[61] = 13;
              *(uint32_t *)(code_ptr + 62) = &gte_regs.data[13].s16.lo;
              *((uint16_t *)code_ptr + 33) = -16625;
              code_ptr[68] = 21;
              *(uint32_t *)(code_ptr + 69) = &gte_regs.data[14];
              *(uint16_t *)(code_ptr + 73) = -16085;
              *(uint16_t *)(code_ptr + 75) = -20721;
              code_ptr[77] = -62;
              *((uint16_t *)code_ptr + 39) = -10237;
              *((uint16_t *)code_ptr + 40) = -15477;
              code_ptr[82] = -93;
              *(uint32_t *)(code_ptr + 83) = &gte_regs.data[24];
              *(uint16_t *)(code_ptr + 87) = 32653;
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
                  *(uint16_t *)v2 = 32393;
                  code_ptr[2] = -112;
                  code_ptr[3] = 87;
                  code_ptr[4] = 86;
                  *(uint16_t *)(code_ptr + 5) = 18119;
                  code_ptr[7] = -116;
                  *((uint32_t *)code_ptr + 2) = v7;
                  v92 = gte_exec_opcode;
                  goto LABEL_242;
                }
                v101 = gte_rtps;
              }
              *v2 = -24;
              *(uint32_t *)(code_ptr + 1) = (char *)v101 - (char *)code_ptr - 5;
              *(uint16_t *)(code_ptr + 5) = 32653;
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
        v7 = (uint16_t)v7;
        v104 = 4 * v102;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v103;
          v105 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v103;
          v105 = code_ptr + 3;
        }
        code_ptr = v105;
        *v105 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 187;
        if ( !v104 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        *(uint16_t *)(code_ptr + 5) = -16881;
        goto LABEL_314;
      case 0x21u:
        v106 = BYTE2(v7) & 0x1F;
        v107 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v104 = 4 * v106;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v107;
          v108 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v107;
          v108 = code_ptr + 3;
        }
        code_ptr = v108;
        *v108 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 315;
        if ( v104 )
        {
          *(uint16_t *)(code_ptr + 5) = -16625;
LABEL_314:
          code_ptr[7] = -64;
          *((uint16_t *)code_ptr + 4) = 18057;
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
        v7 = (uint16_t)v7;
        v111 = 4 * v109;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(uint32_t *)(code_ptr + 1) = v7;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = v110;
        *((uint16_t *)code_ptr + 4) = -10101;
        *((uint16_t *)code_ptr + 5) = -7295;
        *((uint32_t *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(uint32_t *)(code_ptr + 17) = -4;
        code_ptr[21] = -24;
        *(uint32_t *)(code_ptr + 22) = (uint8_t *)recomp_buffer - code_ptr + 422;
        if ( !v111 )
        {
          code_ptr += 26;
          goto LABEL_422;
        }
        *((uint16_t *)code_ptr + 13) = 3211;
        code_ptr[28] = -99;
        *(uint32_t *)(code_ptr + 29) = lwl_mask_table;
        *(uint16_t *)(code_ptr + 33) = 20001;
        code_ptr[35] = v111;
        *((uint16_t *)code_ptr + 18) = 3211;
        code_ptr[38] = -99;
        *(uint32_t *)(code_ptr + 39) = lwl_shift_table;
        *(uint16_t *)(code_ptr + 43) = -7981;
        goto LABEL_328;
      case 0x23u:
        v112 = BYTE2(v7) & 0x1F;
        v113 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v114 = 4 * v112;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v113;
          v115 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v113;
          v115 = code_ptr + 3;
        }
        code_ptr = v115;
        v116 = adjust_timing == 0;
        *v115 = -87;
        *(uint32_t *)(code_ptr + 1) = 1602224128;
        code_ptr[5] = 117;
        if ( v116 )
        {
          code_ptr[6] = 17;
          code_ptr[7] = 37;
          *((uint32_t *)code_ptr + 2) = 0x1FFFFF;
          code_ptr[12] = 5;
          *(uint32_t *)(code_ptr + 13) = ram;
          *(uint16_t *)(code_ptr + 17) = 32653;
          code_ptr[19] = -cd_speed;
          *((uint16_t *)code_ptr + 10) = 139;
          code_ptr[22] = -21;
          code_ptr[23] = 5;
          code_ptr[24] = -24;
          *(uint32_t *)(code_ptr + 25) = (uint8_t *)recomp_buffer - code_ptr + 419;
          if ( v114 )
          {
            *(uint16_t *)(code_ptr + 29) = 18057;
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
          *((uint32_t *)code_ptr + 2) = 0x1FFFFF;
          code_ptr[12] = 5;
          *(uint32_t *)(code_ptr + 13) = ram;
          *(uint16_t *)(code_ptr + 17) = 7563;
          *(uint32_t *)(code_ptr + 19) = &cd_speed;
          *(uint16_t *)(code_ptr + 23) = -1237;
          *(uint16_t *)(code_ptr + 25) = 139;
          code_ptr[27] = -21;
          code_ptr[28] = 5;
          code_ptr[29] = -24;
          *(uint32_t *)(code_ptr + 30) = (uint8_t *)recomp_buffer - code_ptr + 414;
          if ( v114 )
          {
            *((uint16_t *)code_ptr + 17) = 18057;
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
          && *(uint32_t *)((uint16_t)(ArgList - 8) + mem_read_hooks[(ArgList - 8) >> 16]) == 65011720
          && *(uint32_t *)((uint16_t)(ArgList + 128) + mem_read_hooks[(ArgList + 128) >> 16]) == 608305167 )
        {
          dbg_print(" * warning: skullmonkeys trick enabled. \n");
          goto LABEL_422;
        }
        v117 = BYTE2(v7) & 0x1F;
        v118 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v119 = 4 * v117;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v118;
          v120 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v118;
          v120 = code_ptr + 3;
        }
        code_ptr = v120;
        *v120 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 187;
        if ( !v119 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        code_ptr[5] = 37;
        *(uint32_t *)(code_ptr + 6) = 255;
        goto LABEL_354;
      case 0x25u:
        v121 = BYTE2(v7) & 0x1F;
        v122 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v119 = 4 * v121;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v122;
          v123 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v122;
          v123 = code_ptr + 3;
        }
        code_ptr = v123;
        *v123 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 315;
        if ( !v119 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        code_ptr[5] = 37;
        *(uint32_t *)(code_ptr + 6) = 0xFFFF;
LABEL_354:
        *((uint16_t *)code_ptr + 5) = 18057;
        code_ptr[12] = v119;
        goto LABEL_355;
      case 0x26u:
        v124 = BYTE2(v7) & 0x1F;
        v125 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v111 = 4 * v124;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(uint32_t *)(code_ptr + 1) = v7;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = v125;
        *((uint16_t *)code_ptr + 4) = -10101;
        *((uint16_t *)code_ptr + 5) = -7295;
        *((uint32_t *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(uint32_t *)(code_ptr + 17) = -4;
        code_ptr[21] = -24;
        *(uint32_t *)(code_ptr + 22) = (uint8_t *)recomp_buffer - code_ptr + 422;
        if ( v111 )
        {
          *((uint16_t *)code_ptr + 13) = 0xC8B;
          code_ptr[28] = 0x9D;
          *(uint32_t *)(code_ptr + 29) = lwr_mask_table;
          *(uint16_t *)(code_ptr + 33) = 0x4E21;
          code_ptr[35] = v111;
          *((uint16_t *)code_ptr + 18) = 0xC8B;
          code_ptr[38] = 0x9D;
          *(uint32_t *)(code_ptr + 39) = lwr_shift_table;
          *(uint16_t *)(code_ptr + 43) = 0xE8D3;
LABEL_328:
          *(uint16_t *)(code_ptr + 45) = 0x4609;
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
        v7 = (uint16_t)v7;
        v128 = 4 * v126;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v127;
          v129 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v127;
          v129 = code_ptr + 3;
        }
        code_ptr = v129;
        *(uint16_t *)v129 = 24203;
        code_ptr[2] = v128;
        *(uint16_t *)(code_ptr + 3) = -7295;
        *(uint32_t *)(code_ptr + 5) = 255;
        code_ptr[9] = -24;
        *(uint32_t *)(code_ptr + 10) = (uint8_t *)recomp_buffer - code_ptr + 562;
        code_ptr += 14;
        goto LABEL_422;
      case 0x29u:
        v130 = BYTE2(v7) & 0x1F;
        v131 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v132 = 4 * v130;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v131;
          v133 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v131;
          v133 = code_ptr + 3;
        }
        code_ptr = v133;
        *(uint16_t *)v133 = 24203;
        code_ptr[2] = v132;
        *(uint16_t *)(code_ptr + 3) = -7295;
        *(uint32_t *)(code_ptr + 5) = 0xFFFF;
        code_ptr[9] = -24;
        *(uint32_t *)(code_ptr + 10) = (uint8_t *)recomp_buffer - code_ptr + 754;
        code_ptr += 14;
        goto LABEL_422;
      case 0x2Au:
        v134 = BYTE2(v7) & 0x1F;
        v135 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v136 = 4 * v134;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(uint32_t *)(code_ptr + 1) = v7;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = v135;
        *((uint16_t *)code_ptr + 4) = -10101;
        *((uint16_t *)code_ptr + 5) = -7295;
        *((uint32_t *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(uint32_t *)(code_ptr + 17) = -4;
        code_ptr[21] = 80;
        code_ptr[22] = -24;
        *(uint32_t *)(code_ptr + 23) = (uint8_t *)recomp_buffer - code_ptr + 421;
        *(uint16_t *)(code_ptr + 27) = 3211;
        code_ptr[29] = -99;
        *(uint32_t *)(code_ptr + 30) = swl_mask_table;
        *((uint16_t *)code_ptr + 17) = -16093;
        *((uint16_t *)code_ptr + 18) = 3211;
        code_ptr[38] = -99;
        *(uint32_t *)(code_ptr + 39) = swl_shift_table;
        *(uint16_t *)(code_ptr + 43) = 24203;
        code_ptr[45] = v136;
        *((uint16_t *)code_ptr + 23) = -5165;
        goto LABEL_384;
      case 0x2Bu:
        v137 = BYTE2(v7) & 0x1F;
        v138 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v139 = 4 * v137;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        if ( v7 )
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v7;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = v138;
          v140 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)v2 = 18059;
          code_ptr[2] = v138;
          v140 = code_ptr + 3;
        }
        code_ptr = v140;
        *(uint16_t *)v140 = 24203;
        code_ptr[2] = v139;
        code_ptr[3] = -24;
        *((uint32_t *)code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 952;
        v141 = code_ptr + 8;
        code_ptr += 8;
        if ( a2 != 1 )
        {
          *v141 = -72;
          if ( (ArgList & 0xFFF00000) == 0xBFC00000 )
            v142 = (ArgList & 0x7FFFF) + 0x200000;
          else
            v142 = ArgList & 0x1FFFFF;
          *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + v142;
          *(uint16_t *)(code_ptr + 5) = 8447;
          code_ptr += 7;
        }
        goto LABEL_422;
      case 0x2Eu:
        v143 = BYTE2(v7) & 0x1F;
        v144 = 4 * ((v7 >> 21) & 0x1F);
        v7 = (uint16_t)v7;
        v145 = 4 * v143;
        if ( (v7 & 0x8000) != 0 )
          v7 |= 0xFFFF0000;
        *v2 = -72;
        *(uint32_t *)(code_ptr + 1) = v7;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = v144;
        *((uint16_t *)code_ptr + 4) = -10101;
        *((uint16_t *)code_ptr + 5) = -7295;
        *((uint32_t *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(uint32_t *)(code_ptr + 17) = -4;
        code_ptr[21] = 80;
        code_ptr[22] = -24;
        *(uint32_t *)(code_ptr + 23) = (uint8_t *)recomp_buffer - code_ptr + 421;
        *(uint16_t *)(code_ptr + 27) = 3211;
        code_ptr[29] = -99;
        *(uint32_t *)(code_ptr + 30) = swr_mask_table;
        *((uint16_t *)code_ptr + 17) = -16093;
        *((uint16_t *)code_ptr + 18) = 3211;
        code_ptr[38] = -99;
        *(uint32_t *)(code_ptr + 39) = swr_shift_table;
        *(uint16_t *)(code_ptr + 43) = 24203;
        code_ptr[45] = v145;
        *((uint16_t *)code_ptr + 23) = -7213;
LABEL_384:
        *((uint16_t *)code_ptr + 24) = -10229;
        code_ptr[50] = 88;
        code_ptr[51] = -24;
        *((uint32_t *)code_ptr + 13) = (uint8_t *)recomp_buffer - code_ptr + 904;
        code_ptr += 56;
        goto LABEL_422;
      case 0x32u:
        v146 = 4 * (BYTE2(v7) & 0x1F);
        v147 = (uint16_t)v7;
        if ( (v7 & 0x8000) != 0 )
          v147 = v7 | 0xFFFF0000;
        if ( v146 >= 0x38u && v146 <= 0x4Cu || v146 == 112 )
        {
          *(uint16_t *)v2 = 32393;
          code_ptr[2] = -112;
          code_ptr[3] = 87;
          code_ptr[4] = 86;
          *(uint16_t *)(code_ptr + 5) = 18119;
          code_ptr[7] = -116;
          *((uint32_t *)code_ptr + 2) = v7;
          v148 = op_LWC2;
          goto LABEL_414;
        }
        *v2 = -72;
        *(uint32_t *)(code_ptr + 1) = v147;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = 4 * ((v7 >> 21) & 0x1F);
        code_ptr[8] = -24;
        *(uint32_t *)(code_ptr + 9) = (uint8_t *)recomp_buffer - code_ptr + 435;
        if ( v146 == 28 )
        {
LABEL_355:
          code_ptr += 13;
        }
        else if ( v146 == 4 || v146 == 12 || v146 == 20 || v146 == 32 || v146 == 36 || v146 == 40 || v146 == 44 )
        {
          *(uint16_t *)(code_ptr + 13) = -16625;
          code_ptr[15] = -64;
          code_ptr[16] = -93;
          *(uint32_t *)(code_ptr + 17) = (char *)&gte_regs + v146;
          code_ptr += 21;
        }
        else
        {
          code_ptr[13] = -93;
          *(uint32_t *)(code_ptr + 14) = (char *)&gte_regs + v146;
          code_ptr += 18;
        }
        goto LABEL_422;
      case 0x3Au:
        v149 = 4 * (BYTE2(v7) & 0x1F);
        v150 = (uint16_t)v7;
        if ( (v7 & 0x8000) != 0 )
          v150 = v7 | 0xFFFF0000;
        if ( v149 == 124 || v149 == 116 )
        {
          *(uint16_t *)v2 = 32393;
          code_ptr[2] = -112;
          code_ptr[3] = 87;
          code_ptr[4] = 86;
          *(uint16_t *)(code_ptr + 5) = 18119;
          code_ptr[7] = -116;
          *((uint32_t *)code_ptr + 2) = v7;
          v148 = op_SWC2;
LABEL_414:
          code_ptr[12] = -24;
          *(uint32_t *)(code_ptr + 13) = v148 - code_ptr - 17;
          code_ptr[17] = 94;
          code_ptr[18] = 95;
          *(uint16_t *)(code_ptr + 19) = 32653;
          code_ptr[21] = -5;
          code_ptr += 22;
        }
        else
        {
          *v2 = -72;
          *(uint32_t *)(code_ptr + 1) = v150;
          *(uint16_t *)(code_ptr + 5) = 7563;
          *(uint32_t *)(code_ptr + 7) = (char *)&gte_regs + (uint8_t)(4 * (BYTE2(v7) & 0x1F));
          *(uint16_t *)(code_ptr + 11) = 17923;
          code_ptr[13] = 4 * ((v7 >> 21) & 0x1F);
          code_ptr[14] = -24;
          *(uint32_t *)(code_ptr + 15) = (uint8_t *)recomp_buffer - code_ptr + 941;
          code_ptr += 19;
        }
        goto LABEL_422;
      default:
        fatal_error_with_message_box(
          " Opcode %02x UNK (PC %08x) (%d,%d)\n",
          v7 >> 26,
          ArgList - 4,
          frame_counter,
          scanline_counter);
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
  *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + v156;
  *(uint16_t *)(code_ptr + 5) = 8447;
  code_ptr += 7;
  return v158 - 1;
}

unsigned int dynarec_invalidate_range(int a1, int a2)
{
  int v2;
  char *v3;
  LPVOID v4;
  int v5;
  LPVOID v6;
  unsigned int v7;
  unsigned int result;
  unsigned int v9;

  if ( (a1 & 0xFFF00000) == 0xBFC00000 )
    v2 = (a1 & 0x7FFFC) + 0x200000;
  else
    v2 = a1 & 0x1FFFFC;
  v3 = (char *)recomp_code_base;
  v4 = recomp_buffer;
  if ( *(LPVOID *)((char *)recomp_code_base + v2) != recomp_buffer )
  {
    v5 = ((uint8_t *)recomp_buffer - (uint8_t *)recomp_metadata) >> 2;
    *(uint32_t *)((char *)recomp_code_base + v2) = recomp_buffer;
    if ( v5 )
    {
      while ( 1 )
      {
        v3 = (char *)recomp_code_base;
        v4 = recomp_buffer;
        v6 = *(LPVOID *)((char *)recomp_code_base + v2 - 4);
        v2 -= 4;
        if ( v6 == recomp_buffer )
          break;
        --v5;
        *(uint32_t *)((char *)recomp_code_base + v2) = recomp_buffer;
        if ( !v5 )
          goto LABEL_8;
      }
    }
    else
    {
LABEL_8:
      v4 = recomp_buffer;
      v3 = (char *)recomp_code_base;
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
      *(uint32_t *)&v3[result] = v4;
      result += 4;
      if ( result >= v9 )
        break;
      v4 = recomp_buffer;
      v3 = (char *)recomp_code_base;
    }
  }
  return result;
}

uint8_t *dynarec_init()
{
  unsigned int v0;
  unsigned int i;
  uint8_t *v2;
  uint8_t *v3;
  uint8_t *v4;
  uint8_t *result;

  if ( !recomp_buffer )
  {
    v0 = (unsigned int)malloc(0x200040u);
    recomp_buffer = (LPVOID)v0;
    if ( !v0 )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
    if ( (v0 & 0x3F) != 0 )
      recomp_buffer = (LPVOID)((v0 & 0xFFFFFFC0) + 64);
    recomp_code_base = malloc(0x280000u);
    if ( !recomp_code_base )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
    recomp_metadata = malloc(0x280000u);
    if ( !recomp_metadata )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
  }
  for ( i = 0; i < 0x280000; i += 4 )
    *(uint32_t *)((char *)recomp_code_base + i) = recomp_buffer;
  memset(recomp_buffer, 0, 0x200000u);
  memset(recomp_metadata, 0, 0x280000u);
  code_ptr = (uint8_t *)recomp_buffer;
  *(uint8_t *)recomp_buffer = 80;
  code_ptr[1] = -24;
  *(uint32_t *)(code_ptr + 2) = (char *)dynarec_recompile_block - (char *)code_ptr - 6;
  *((uint16_t *)code_ptr + 3) = 0xC481;
  *((uint32_t *)code_ptr + 2) = 4;
  *((uint16_t *)code_ptr + 6) = 8447;
  code_ptr += 64;
  *code_ptr = -24;
  *(uint32_t *)(code_ptr + 1) = (char *)dynarec_hw_update - (char *)code_ptr - 5;
  *(uint16_t *)(code_ptr + 5) = 0xC781;
  *(uint32_t *)(code_ptr + 7) = cpu_speed_scale;
  *(uint16_t *)(code_ptr + 11) = 8447;
  code_ptr += 64;
  *(uint16_t *)code_ptr = -15735;
  *((uint16_t *)code_ptr + 1) = -7551;
  *((uint32_t *)code_ptr + 1) = 0xFFF00000;
  *((uint16_t *)code_ptr + 4) = 0xFA81;
  *(uint32_t *)(code_ptr + 10) = 0xBFC00000;
  code_ptr[14] = 116;
  code_ptr[15] = 11;
  code_ptr[16] = 37;
  *(uint32_t *)(code_ptr + 17) = 2097148;
  code_ptr[21] = 5;
  *(uint32_t *)(code_ptr + 22) = recomp_code_base;
  code_ptr[26] = 0xC3;
  code_ptr[27] = 37;
  *((uint32_t *)code_ptr + 7) = 524284;
  code_ptr[32] = 5;
  *(uint32_t *)(code_ptr + 33) = (char *)recomp_code_base + 0x200000;
  code_ptr[37] = 0xC3;
  code_ptr += 64;
  *(uint16_t *)code_ptr = -15735;
  *((uint16_t *)code_ptr + 1) = 32653;
  code_ptr[4] = -5;
  *(uint16_t *)(code_ptr + 5) = -7551;
  *(uint32_t *)(code_ptr + 7) = 532676608;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = 528482304;
  code_ptr[17] = 116;
  code_ptr[18] = 21;
  *(uint16_t *)(code_ptr + 19) = -14197;
  *(uint16_t *)(code_ptr + 21) = -5695;
  code_ptr[23] = 16;
  code_ptr[24] = 37;
  *(uint32_t *)(code_ptr + 25) = 0xFFFF;
  *(uint16_t *)(code_ptr + 29) = 3211;
  code_ptr[31] = -115;
  *((uint32_t *)code_ptr + 8) = mem_read_hooks;
  *((uint16_t *)code_ptr + 18) = 1162;
  code_ptr[38] = 8;
  code_ptr[39] = 0xC3;
  code_ptr[40] = 37;
  *(uint32_t *)(code_ptr + 41) = 0x1FFFFFFF;
  code_ptr[45] = 61;
  *(uint32_t *)(code_ptr + 46) = 0x1F800FFF;
  code_ptr[50] = 127;
  code_ptr[51] = 12;
  code_ptr[52] = 37;
  *(uint32_t *)(code_ptr + 53) = 4095;
  *(uint16_t *)(code_ptr + 57) = -32629;
  *(uint32_t *)(code_ptr + 59) = dcache;
  code_ptr[63] = 0xC3;
  *((uint16_t *)code_ptr + 32) = 32393;
  code_ptr[66] = -112;
  code_ptr[67] = 80;
  code_ptr[68] = -24;
  *(uint32_t *)(code_ptr + 69) = (char *)mem_hw_reg_read_byte - (char *)code_ptr - 73;
  *(uint16_t *)(code_ptr + 73) = -15231;
  *(uint32_t *)(code_ptr + 75) = 4;
  code_ptr[79] = 0xC3;
  code_ptr += 128;
  *(uint16_t *)code_ptr = -15735;
  *((uint16_t *)code_ptr + 1) = 32653;
  code_ptr[4] = -5;
  *(uint16_t *)(code_ptr + 5) = -7551;
  *(uint32_t *)(code_ptr + 7) = 0x1FC00000;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = 0x1F800000;
  code_ptr[17] = 116;
  code_ptr[18] = 21;
  *(uint16_t *)(code_ptr + 19) = -14197;
  *(uint16_t *)(code_ptr + 21) = -5695;
  code_ptr[23] = 16;
  code_ptr[24] = 37;
  *(uint32_t *)(code_ptr + 25) = 0xFFFF;
  *(uint16_t *)(code_ptr + 29) = 3211;
  code_ptr[31] = -115;
  *((uint32_t *)code_ptr + 8) = mem_read_hooks;
  *((uint16_t *)code_ptr + 18) = 1163;
  code_ptr[38] = 8;
  code_ptr[39] = 0xC3;
  code_ptr[40] = 37;
  *(uint32_t *)(code_ptr + 41) = 0x1FFFFFFF;
  code_ptr[45] = 61;
  *(uint32_t *)(code_ptr + 46) = 0x1F800FFF;
  code_ptr[50] = 127;
  code_ptr[51] = 12;
  code_ptr[52] = 37;
  *(uint32_t *)(code_ptr + 53) = 4095;
  *(uint16_t *)(code_ptr + 57) = -32629;
  *(uint32_t *)(code_ptr + 59) = dcache;
  code_ptr[63] = 0xC3;
  *((uint16_t *)code_ptr + 32) = 32393;
  code_ptr[66] = -112;
  code_ptr[67] = 80;
  code_ptr[68] = -24;
  *(uint32_t *)(code_ptr + 69) = (char *)hw_reg_read_half - (char *)code_ptr - 73;
  *(uint16_t *)(code_ptr + 73) = -15231;
  *(uint32_t *)(code_ptr + 75) = 4;
  code_ptr[79] = 0xC3;
  code_ptr += 128;
  *(uint16_t *)code_ptr = -15735;
  *((uint16_t *)code_ptr + 1) = 32653;
  code_ptr[4] = -5;
  *(uint16_t *)(code_ptr + 5) = -7551;
  *(uint32_t *)(code_ptr + 7) = 0x1FC00000;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = 0x1F800000;
  code_ptr[17] = 116;
  code_ptr[18] = 21;
  *(uint16_t *)(code_ptr + 19) = -14197;
  *(uint16_t *)(code_ptr + 21) = -5695;
  code_ptr[23] = 16;
  code_ptr[24] = 37;
  *(uint32_t *)(code_ptr + 25) = 0xFFFF;
  *(uint16_t *)(code_ptr + 29) = 3211;
  code_ptr[31] = -115;
  *((uint32_t *)code_ptr + 8) = mem_read_hooks;
  *((uint16_t *)code_ptr + 18) = 1163;
  code_ptr[38] = 8;
  code_ptr[39] = 0xC3;
  code_ptr[40] = 37;
  *(uint32_t *)(code_ptr + 41) = 0x1FFFFFFF;
  code_ptr[45] = 61;
  *(uint32_t *)(code_ptr + 46) = 528486399;
  code_ptr[50] = 127;
  code_ptr[51] = 12;
  code_ptr[52] = 37;
  *(uint32_t *)(code_ptr + 53) = 4095;
  *(uint16_t *)(code_ptr + 57) = -32629;
  *(uint32_t *)(code_ptr + 59) = dcache;
  code_ptr[63] = 0xC3;
  *((uint16_t *)code_ptr + 32) = 32393;
  code_ptr[66] = -112;
  code_ptr[67] = 80;
  code_ptr[68] = -24;
  *(uint32_t *)(code_ptr + 69) = (char *)hw_reg_read_word - (char *)code_ptr - 73;
  *(uint16_t *)(code_ptr + 73) = -15231;
  *(uint32_t *)(code_ptr + 75) = 4;
  code_ptr[79] = 0xC3;
  code_ptr += 128;
  *(uint16_t *)code_ptr = 0xC289;
  *((uint16_t *)code_ptr + 1) = 32653;
  code_ptr[4] = 0xFB;
  *(uint16_t *)(code_ptr + 5) = 0xE281;
  *(uint32_t *)(code_ptr + 7) = 0x1FC00000;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = 0x1F800000;
  code_ptr[17] = 116;
  code_ptr[18] = 100;
  *(uint16_t *)(code_ptr + 19) = 3467;
  *(uint32_t *)(code_ptr + 21) = &cop0_sr;
  *(uint16_t *)(code_ptr + 25) = 0xC1F7;
  *(uint32_t *)(code_ptr + 27) = 0x10000;
  code_ptr[31] = 117;
  code_ptr[32] = 85;
  *(uint16_t *)(code_ptr + 33) = 0xC88B;
  *(uint16_t *)(code_ptr + 35) = 0xC289;
  *(uint16_t *)(code_ptr + 37) = 0xE9C1;
  code_ptr[39] = 16;
  code_ptr[40] = 37;
  *(uint32_t *)(code_ptr + 41) = 0xFFFF;
  *(uint16_t *)(code_ptr + 45) = 3211;
  code_ptr[47] = -115;
  *((uint32_t *)code_ptr + 12) = mem_write_hooks;
  *((uint16_t *)code_ptr + 26) = 7304;
  code_ptr[54] = 8;
  recomp_code_base_addr = (int)recomp_code_base;
  recomp_buffer_addr = (int)recomp_buffer;
  recomp_buffer_addr_2 = (int)recomp_buffer;
  recomp_buffer_addr_3 = (int)recomp_buffer;
  recomp_metadata_addr = (int)recomp_metadata;
  v2 = code_ptr + 55;
  qmemcpy(code_ptr + 55, &recomp_hw_write_template, 0x3Cu);
  v2 += 60;
  *(uint16_t *)v2 = recomp_hw_write_tail_word;
  v2[2] = recomp_hw_write_tail_byte;
  code_ptr[118] = 0xC3;
  code_ptr[119] = 61;
  *((uint32_t *)code_ptr + 30) = 0x1F800FFF;
  code_ptr[124] = 127;
  code_ptr[125] = 12;
  code_ptr[126] = 37;
  *(uint32_t *)(code_ptr + 127) = 4095;
  *(uint16_t *)(code_ptr + 131) = -26488;
  *(uint32_t *)(code_ptr + 133) = dcache;
  code_ptr[137] = 0xC3;
  code_ptr[138] = 83;
  code_ptr[139] = 80;
  code_ptr[140] = -24;
  *(uint32_t *)(code_ptr + 141) = (char *)mem_hw_reg_write_byte - (char *)code_ptr - 145;
  *(uint16_t *)(code_ptr + 145) = -15231;
  *(uint32_t *)(code_ptr + 147) = 8;
  code_ptr[151] = 0xC3;
  code_ptr += 192;
  *(uint16_t *)code_ptr = -15735;
  *((uint16_t *)code_ptr + 1) = 32653;
  code_ptr[4] = -5;
  *(uint16_t *)(code_ptr + 5) = -7551;
  *(uint32_t *)(code_ptr + 7) = 0x1FC00000;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = 0x1F800000;
  code_ptr[17] = 116;
  code_ptr[18] = 101;
  *(uint16_t *)(code_ptr + 19) = 3467;
  *(uint32_t *)(code_ptr + 21) = &cop0_sr;
  *(uint16_t *)(code_ptr + 25) = -15881;
  *(uint32_t *)(code_ptr + 27) = 0x10000;
  code_ptr[31] = 117;
  code_ptr[32] = 86;
  *(uint16_t *)(code_ptr + 33) = -14197;
  *(uint16_t *)(code_ptr + 35) = -15735;
  *(uint16_t *)(code_ptr + 37) = -5695;
  code_ptr[39] = 16;
  code_ptr[40] = 37;
  *(uint32_t *)(code_ptr + 41) = 0xFFFF;
  *(uint16_t *)(code_ptr + 45) = 3211;
  code_ptr[47] = -115;
  *((uint32_t *)code_ptr + 12) = mem_write_hooks;
  *((uint16_t *)code_ptr + 26) = -30362;
  *((uint16_t *)code_ptr + 27) = 284;
  recomp_code_base_addr = (int)recomp_code_base;
  recomp_buffer_addr = (int)recomp_buffer;
  recomp_buffer_addr_2 = (int)recomp_buffer;
  recomp_buffer_addr_3 = (int)recomp_buffer;
  recomp_metadata_addr = (int)recomp_metadata;
  v3 = code_ptr + 56;
  qmemcpy(code_ptr + 56, &recomp_hw_write_template, 0x3Cu);
  v3 += 60;
  *(uint16_t *)v3 = recomp_hw_write_tail_word;
  v3[2] = recomp_hw_write_tail_byte;
  code_ptr[119] = 0xC3;
  code_ptr[120] = 61;
  *(uint32_t *)(code_ptr + 121) = 0x1F800FFF;
  code_ptr[125] = 127;
  code_ptr[126] = 13;
  code_ptr[127] = 37;
  *((uint32_t *)code_ptr + 32) = 4095;
  code_ptr[132] = 102;
  *(uint16_t *)(code_ptr + 133) = -26487;
  *(uint32_t *)(code_ptr + 135) = dcache;
  code_ptr[139] = 0xC3;
  code_ptr[140] = 83;
  code_ptr[141] = 80;
  code_ptr[142] = -24;
  *(uint32_t *)(code_ptr + 143) = (char *)mem_hw_reg_write_half - (char *)code_ptr - 147;
  *(uint16_t *)(code_ptr + 147) = -15231;
  *(uint32_t *)(code_ptr + 149) = 8;
  code_ptr[153] = 0xC3;
  code_ptr += 192;
  *(uint16_t *)code_ptr = -15735;
  *((uint16_t *)code_ptr + 1) = 32653;
  code_ptr[4] = -5;
  *(uint16_t *)(code_ptr + 5) = -7551;
  *(uint32_t *)(code_ptr + 7) = 0x1FC00000;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = 0x1F800000;
  code_ptr[17] = 116;
  code_ptr[18] = 100;
  *(uint16_t *)(code_ptr + 19) = 3467;
  *(uint32_t *)(code_ptr + 21) = &cop0_sr;
  *(uint16_t *)(code_ptr + 25) = -15881;
  *(uint32_t *)(code_ptr + 27) = 0x10000;
  code_ptr[31] = 117;
  code_ptr[32] = 85;
  *(uint16_t *)(code_ptr + 33) = -14197;
  *(uint16_t *)(code_ptr + 35) = -15735;
  *(uint16_t *)(code_ptr + 37) = -5695;
  code_ptr[39] = 16;
  code_ptr[40] = 37;
  *(uint32_t *)(code_ptr + 41) = 0xFFFF;
  *(uint16_t *)(code_ptr + 45) = 3211;
  code_ptr[47] = -115;
  *((uint32_t *)code_ptr + 12) = mem_write_hooks;
  *((uint16_t *)code_ptr + 26) = 7305;
  code_ptr[54] = 8;
  recomp_code_base_addr = (int)recomp_code_base;
  recomp_buffer_addr = (int)recomp_buffer;
  recomp_buffer_addr_2 = (int)recomp_buffer;
  recomp_buffer_addr_3 = (int)recomp_buffer;
  recomp_metadata_addr = (int)recomp_metadata;
  v4 = code_ptr + 55;
  qmemcpy(code_ptr + 55, &recomp_hw_write_template, 0x3Cu);
  v4 += 60;
  *(uint16_t *)v4 = recomp_hw_write_tail_word;
  v4[2] = recomp_hw_write_tail_byte;
  code_ptr[118] = 0xC3;
  code_ptr[119] = 61;
  *((uint32_t *)code_ptr + 30) = 0x1F800FFF;
  code_ptr[124] = 127;
  code_ptr[125] = 12;
  code_ptr[126] = 37;
  *(uint32_t *)(code_ptr + 127) = 4095;
  *(uint16_t *)(code_ptr + 131) = 0x9889;
  *(uint32_t *)(code_ptr + 133) = dcache;
  code_ptr[137] = 0xC3;
  code_ptr[138] = 83;
  code_ptr[139] = 80;
  code_ptr[140] = 0xE8;
  *(uint32_t *)(code_ptr + 141) = (char *)hw_reg_write_word - (char *)code_ptr - 145;
  *(uint16_t *)(code_ptr + 145) = 0xC481;
  *(uint32_t *)(code_ptr + 147) = 8;
  code_ptr[151] = 0xC3;
  result = code_ptr + 192;
  code_ptr += 192;
  return result;
}

void dynarec_deinit()
{
  if ( recomp_buffer )
    free(recomp_buffer);
  if ( recomp_code_base )
    free(recomp_code_base);
  if ( recomp_metadata )
    free(recomp_metadata);
}

int64_t dynarec_execute()
{
  int v0;
  int64_t v1;
  int64_t v3;

  *code_ptr = 0xBF;
  *(uint32_t *)(code_ptr + 1) = cpu_speed_scale;
  code_ptr[5] = 0xBE;
  *(uint32_t *)(code_ptr + 6) = cpu_gpr;
  code_ptr[10] = 0xB8;
  if ( (*(uint32_t *)reg_pc & 0xFFF00000) == 0xBFC00000 )
    v0 = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
  else
    v0 = *(uint32_t *)reg_pc & 0x1FFFFF;
  LODWORD(v1) = (char *)recomp_code_base + v0;
  *(uint32_t *)(code_ptr + 11) = v1;
  HIDWORD(v1) = code_ptr;
  *(uint16_t *)(code_ptr + 15) = 8447;
  code_ptr += 64;
  spu_async_update_counter = 0;
  v3 = v1;
  ((void (*)(void))((char *)recomp_buffer + 1152))();
  return v3;
}

char *dynarec_invalidate()
{
  unsigned int i;

  for ( i = 0; i < 0x280000; i += 4 )
    *(uint32_t *)((char *)recomp_code_base + i) = recomp_buffer;
  code_ptr = (uint8_t *)recomp_buffer + 1216;
  return (char *)recomp_buffer + 1216;
}

void nullsub_1()
{
  ;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char lwl_mask_table[16] = {0xff, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned char lwl_shift_table[16] = {0x18, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned char lwr_mask_table[16] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0xff};
unsigned char lwr_shift_table[16] = {0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0};
unsigned char swl_mask_table[12] = {0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff};
unsigned char swl_shift_table[16] = {0x18, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned char swr_mask_table[15] = {0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0xff};
unsigned char swr_shift_table[16] = {0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0};
unsigned char recomp_hw_write_template = 0x81;
unsigned char recomp_hw_write_tail_byte = 0xf1;
unsigned char cd_extra_setting;
uint8_t *code_ptr;
unsigned int cpu_speed_scale = 0x86a;
unsigned int recomp_code_base_addr = 0x0;
unsigned int recomp_buffer_addr = 0x0;
unsigned int recomp_buffer_addr_2 = 0x0;
unsigned int recomp_metadata_addr = 0x0;
unsigned int recomp_buffer_addr_3 = 0x0;
unsigned int recomp_special_flags;
unsigned int rcnt2_mode;
unsigned int rcnt2_compare;
unsigned int cpu_recomp_state[0xb];
unsigned int int_mask;
unsigned int int_reg[1];
unsigned int patch_offset_ptr;
unsigned int recomp_buffer;
unsigned int recomp_code_base;
unsigned int recomp_metadata;
unsigned short recomp_hw_write_tail_word = 0x7503;
