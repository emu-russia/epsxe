#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static unsigned char lwl_mask_table[16] = {0xff, 0xff, 0xff, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
static unsigned char lwl_shift_table[16] = {0x18, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
static unsigned char lwr_mask_table[16] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0xff, 0xff, 0xff};
static unsigned char lwr_shift_table[16] = {0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0};
static unsigned char swl_mask_table[12] = {0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff};
static unsigned char swl_shift_table[16] = {0x18, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
static unsigned char swr_mask_table[15] = {0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xff, 0xff};
static unsigned char swr_shift_table[16] = {0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0};
static unsigned char recomp_hw_write_template = 0x81;
static unsigned char recomp_hw_write_tail_byte = 0xf1;
unsigned char cd_extra_setting;
static uint8_t *code_ptr;
unsigned int cpu_speed_scale = 0x86a;
static unsigned int recomp_code_base_addr = 0x0;
static unsigned int recomp_buffer_addr = 0x0;
static unsigned int recomp_buffer_addr_2 = 0x0;
static unsigned int recomp_metadata_addr = 0x0;
static unsigned int recomp_buffer_addr_3 = 0x0;
static unsigned int recomp_special_flags;
unsigned int rcnt2_mode;
unsigned int rcnt2_compare;
static unsigned int cpu_recomp_state[0xb];
static unsigned int patch_offset_ptr;
unsigned int recomp_buffer;
unsigned int recomp_code_base;
unsigned int recomp_metadata;
static unsigned short recomp_hw_write_tail_word = 0x7503;


/* static prototypes for internal functions */
static int dynarec_compile(unsigned int pc, int max_insns);

static char * dynarec_recompile_block(int code_addr)
{
  unsigned int offset;
  int block_addr;

  offset = code_addr - (uint32_t)recomp_code_base;
  if ( (unsigned int)(code_addr - (uint32_t)recomp_code_base) >= 0x200000 )
    offset -= 0x40600000;
  *(uint32_t *)reg_pc = offset;
  dynarec_compile(offset, 0x5000u);
  if ( (*(uint32_t *)reg_pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
    block_addr = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
  else
    block_addr = *(uint32_t *)reg_pc & 0x1FFFFF;
  return (char *)recomp_code_base + block_addr;
}

static char *dynarec_hw_update()
{
  int ret_offset;
  unsigned int counter_inc;
  int rcnt0_inc;
  int rcnt1_inc;
  unsigned int rcnt2_count;
  char mask;
  int irq_bits;
  int patch_offset;
  int pc_offset;

  cpu_recomp_state[0] = 0;
  if ( (hw_update_counter & 0xC0000000) == 0x80000000 )
  {
    if ( (*(uint32_t *)int_reg & int_mask) != 0 )
      irq_cpu_interrupt();
    if ( (*(uint32_t *)reg_pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
      ret_offset = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
    else
      ret_offset = *(uint32_t *)reg_pc & 0x1FFFFF;
    return (char *)recomp_code_base + ret_offset;
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
    counter_inc = cpu_speed_scale;
    rcnt0_inc = 512;
    if ( (rcnt_mode[0] & 0x100) == 0 )
      rcnt0_inc = cpu_speed_scale;
    rcnt_counter[0] += rcnt0_inc;
    if ( rcnt_counter[0] >= (unsigned int)rcnt_compare[0] )
    {
      rcnt_counter[0] = 0;
      if ( (rcnt_mode[0] & 0x50) == 0x50 )
        *(uint32_t *)int_reg |= 0x10u;
    }
    rcnt1_inc = 1;
    if ( (rcnt1_mode & 0x100) == 0 )
      rcnt1_inc = cpu_speed_scale;
    rcnt1_counter += rcnt1_inc;
    if ( rcnt1_counter >= (unsigned int)rcnt1_compare )
    {
      rcnt1_counter = 0;
      if ( (rcnt1_mode & 0x50) == 0x50 )
        *(uint32_t *)int_reg |= 0x20u;
    }
    if ( (rcnt2_mode & 1) == 0 && xenogears_trick_enabled )
    {
      if ( (rcnt2_mode & 0x200) != 0 )
        counter_inc = (unsigned int)cpu_speed_scale >> 3;
      rcnt2_count = counter_inc + rcnt2_counter;
      rcnt2_counter = rcnt2_count;
      if ( rcnt2_count >= rcnt2_compare )
      {
        rcnt2_counter = rcnt2_count - rcnt2_compare;
        if ( (rcnt2_mode & 0x50) == 0x50 )
          *(uint32_t *)int_reg |= 0x40u;
      }
    }
    mask = int_mask;
    if ( scanline_counter == video_scanlines - (cd_extra_setting != 0 ? 32 : 1) )
    {
      irq_bits = *(uint32_t *)int_reg | 1;
      *(uint32_t *)int_reg |= 1u;
      if ( (int_mask & 0x200) != 0 && forcespu && (frame_counter & 3) == 0 )
        *(uint32_t *)int_reg = irq_bits | 0x200;
    }
    if ( (int_mask & *(uint32_t *)int_reg) != 0 )
    {
      irq_cpu_interrupt();
      mask = int_mask;
    }
    if ( scanline_counter >= (unsigned int)video_scanlines )
    {
      scanline_counter = 0;
      ++frame_counter;
      ++rcnt3_counter;
      *(uint32_t *)int_reg |= 1u;
      if ( (mask & 1) != 0 )
        irq_cpu_interrupt();
      gpu_frame_update();
      if ( reset_flag )
      {
        if ( (*(uint32_t *)reg_pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
          patch_offset = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
        else
          patch_offset = *(uint32_t *)reg_pc & 0x1FFFFF;
        **(uint32_t **)((char *)recomp_code_base + patch_offset) = 195;
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
    if ( (*(uint32_t *)reg_pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
      pc_offset = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
    else
      pc_offset = *(uint32_t *)reg_pc & 0x1FFFFF;
    return (char *)recomp_code_base + pc_offset;
  }
}

static int dynarec_compile(unsigned int pc, int max_insns)
{
  uint8_t *insn_start;
  unsigned int limit;
  unsigned int clear_index;
  unsigned int offset;
  unsigned int insn;
  uint8_t index;
  int cheat_id;
  uint8_t next_index;
  uint32_t *cheat_ptr;
  int cheat_count;
  uint8_t dest_off;
  uint8_t reg2_off;
  uint8_t rt_off;
  uint8_t rt_off2;
  uint8_t rt_off3;
  uint8_t rd_off;
  uint8_t rs_off;
  uint8_t rt_off4;
  uint8_t rs_off2;
  uint8_t rt_off5;
  uint8_t rs_off3;
  uint8_t rt_off6;
  int ret_val;
  uint8_t rs_off4;
  uint8_t rd_off2;
  uint8_t *code2;
  int jump_target;
  uint8_t *code3;
  uint8_t rd_off3;
  uint8_t rs_off5;
  uint8_t rs_off6;
  uint8_t rs_off7;
  uint8_t rs_off8;
  uint8_t rs_off9;
  uint8_t dest_off2;
  uint8_t rs_off10;
  uint8_t rt_off7;
  uint8_t rd_off4;
  char rs_idx;
  uint8_t rs_off11;
  char rs_idx2;
  uint8_t rs_off12;
  unsigned int target_offset;
  char rs_idx3;
  uint8_t rs_off13;
  char rs_idx4;
  uint8_t rs_off14;
  unsigned int target_offset2;
  int jump_word;
  uint8_t *patch_ptr;
  int target_offset3;
  int jump_word2;
  int target_offset4;
  char rs_idx5;
  char rt_idx;
  uint8_t rs_off15;
  uint8_t rt_off8;
  uint8_t *code4;
  uint8_t *code5;
  char rs_idx6;
  char rt_idx2;
  uint8_t rs_off16;
  uint8_t rt_off9;
  uint8_t *code6;
  uint8_t *code7;
  char rs_idx7;
  uint8_t rs_off17;
  char rs_idx8;
  uint8_t rs_off18;
  char rs_idx9;
  char rt_idx3;
  uint8_t rs_off19;
  uint8_t *code8;
  char rs_idx10;
  char rt_idx4;
  uint8_t rs_off20;
  uint8_t rt_off10;
  uint8_t rt_off11;
  char rs_idx11;
  uint8_t rs_off21;
  uint8_t *code9;
  char rs_idx12;
  uint8_t rs_off22;
  uint8_t *code10;
  char rs_idx13;
  uint8_t rs_off23;
  uint8_t *code11;
  int cop0_sel;
  char cop0_off;
  uint8_t *handler;
  int cop0_off2;
  uint8_t rt_off12;
  int branch_offset;
  char cop2_off;
  uint8_t gte_idx;
  GTE_REG *gte_ptr;
  uint8_t gte_idx2;
  int gte_opcode;
  int (*gte_handler)();
  char rt_idx5;
  uint8_t base_off;
  uint8_t rt_off13;
  uint8_t *code12;
  char rt_idx6;
  uint8_t base_off2;
  uint8_t *code13;
  char rt_idx7;
  uint8_t base_off3;
  uint8_t rt_off14;
  char rt_idx8;
  uint8_t base_off4;
  uint8_t rt_off15;
  uint8_t *code14;
  bool fast_timing;
  char rt_idx9;
  uint8_t base_off5;
  uint8_t rt_off16;
  uint8_t *code15;
  char rt_idx10;
  uint8_t base_off6;
  uint8_t *code16;
  char rt_idx11;
  uint8_t base_off7;
  char rt_idx12;
  uint8_t base_off8;
  uint8_t rt_off17;
  uint8_t *code17;
  char rt_idx13;
  uint8_t base_off9;
  uint8_t rt_off18;
  uint8_t *code18;
  char rt_idx14;
  uint8_t base_off10;
  uint8_t rt_off19;
  char rt_idx15;
  uint8_t base_off11;
  uint8_t rt_off20;
  uint8_t *code19;
  uint8_t *code20;
  unsigned int target_offset5;
  char rt_idx16;
  uint8_t base_off12;
  uint8_t rt_off21;
  uint8_t gte_off;
  unsigned int disp;
  uint8_t *cop2_handler;
  char gte_off2;
  unsigned int disp2;
  uint8_t *code21;
  int target_pc2;
  int target_offset6;
  unsigned int target_offset7;
  int target_pc;
  unsigned int target_offset8;
  char slot_flag;
  int insn_count;
  uint8_t *block_start;
  uint8_t cheat_index;

  insn_start = code_ptr;
  limit = max_insns;
  clear_index = 0;
  slot_flag = 0;
  insn_count = 0;
  block_start = nullptr;
  if ( max_insns != 1 && code_ptr - (uint8_t *)recomp_buffer >= 2080768 )
  {
    do
    {
      *(uint32_t *)((char *)recomp_code_base + clear_index) = recomp_buffer;
      clear_index += 4;
    }
    while ( clear_index < 0x280000 );
    limit = max_insns;
    code_ptr = (uint8_t *)recomp_buffer + 1216;
    insn_start = (uint8_t *)recomp_buffer + 1216;
  }
  if ( cpu_gpr[0] )
    fatal_error_with_message_box(" dohh zero reg != 0\n");
  while ( 1 )
  {
    if ( limit == 1 )
      slot_flag = 1;
    if ( ++insn_count > limit )
      fatal_error_with_message_box(" ePSXe (error) recompile block too large \n");
    offset = (pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE ? (pc & 0x7FFFF) + 0x200000 : pc & 0x1FFFFF;
    if ( *(LPVOID *)((char *)recomp_code_base + offset) != recomp_buffer && !slot_flag )
      break;
    insn = *(uint32_t *)((uint16_t)pc + mem_read_hooks[HIWORD(pc)]);
    if ( max_insns != 1 )
    {
      *(uint32_t *)((char *)recomp_code_base + offset) = insn_start;
      if ( insn_count == 1 )
        block_start = code_ptr;
      *(uint32_t *)((char *)recomp_metadata + offset) = block_start;
      insn_start = code_ptr;
    }
    if ( active_mini_cheat_count )
    {
      index = 0;
      cheat_index = 0;
      do
      {
        cheat_id = mini_cheat_id_array[2 * cheat_index];
        if ( (cheat_id & 0x1FFFFF) == pc )
        {
          insn = mini_cheat_attr_array[2 * cheat_index];
          if ( (cheat_id & 0xF0000000) == 0 )
          {
            next_index = index + 1;
            if ( (uint8_t)(index + 1) < (uint8_t)active_mini_cheat_count )
            {
              cheat_ptr = (uint32_t *)(8 * next_index + 5991868);
              cheat_count = (uint8_t)(active_mini_cheat_count - next_index);
              do
              {
                *(cheat_ptr - 1) = cheat_ptr[1];
                *cheat_ptr = cheat_ptr[2];
                cheat_ptr += 2;
                --cheat_count;
              }
              while ( cheat_count );
            }
            --active_mini_cheat_count;
          }
        }
        cheat_index = ++index;
      }
      while ( index < (uint8_t)active_mini_cheat_count );
      insn_start = code_ptr;
    }
    pc += 4;
    switch ( insn >> 26 )
    {
      case 0u:
        switch ( insn & 0x3F )
        {
          case 0u:
            if ( !insn )
              goto LABEL_33;
            dest_off = 4 * ((insn >> 11) & 0x1F);
            reg2_off = (insn >> 6) & 0x1F;
            rt_off = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rt_off == dest_off )
            {
              *(uint16_t *)code_ptr = 26305;
              goto LABEL_45;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = rt_off;
            *(uint16_t *)(code_ptr + 3) = -7999;
            goto LABEL_118;
          case 2u:
            dest_off = 4 * ((insn >> 11) & 0x1F);
            reg2_off = (insn >> 6) & 0x1F;
            rt_off2 = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rt_off2 == dest_off )
            {
              *(uint16_t *)code_ptr = 28353;
              goto LABEL_45;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = rt_off2;
            *(uint16_t *)(code_ptr + 3) = -5951;
            goto LABEL_118;
          case 3u:
            dest_off = 4 * ((insn >> 11) & 0x1F);
            reg2_off = (insn >> 6) & 0x1F;
            rt_off3 = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rt_off3 != dest_off )
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rt_off3;
              *(uint16_t *)(code_ptr + 3) = -1855;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = 32449;
LABEL_45:
            code_ptr[2] = dest_off;
            code_ptr[3] = reg2_off;
            code_ptr[4] = 79;
            code_ptr += 5;
            goto LABEL_422;
          case 4u:
            rd_off = 4 * ((insn >> 11) & 0x1F);
            rs_off = 4 * ((insn >> 21) & 0x1F);
            rt_off4 = 4 * (BYTE2(insn) & 0x1F);
            if ( !rd_off )
              goto LABEL_422;
            if ( rt_off4 == rd_off )
            {
              *(uint16_t *)code_ptr = 20107;
              code_ptr[2] = rs_off;
              *(uint16_t *)(code_ptr + 3) = -7807;
              *(uint32_t *)(code_ptr + 5) = 31;
              *(uint16_t *)(code_ptr + 9) = 26323;
              goto LABEL_50;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = rt_off4;
            *(uint16_t *)(code_ptr + 3) = 20107;
            code_ptr[5] = rs_off;
            *((uint16_t *)code_ptr + 3) = -7807;
            *((uint32_t *)code_ptr + 2) = 31;
            *((uint16_t *)code_ptr + 6) = -7981;
            goto LABEL_130;
          case 6u:
            rd_off = 4 * ((insn >> 11) & 0x1F);
            rs_off2 = 4 * ((insn >> 21) & 0x1F);
            rt_off5 = 4 * (BYTE2(insn) & 0x1F);
            if ( !rd_off )
              goto LABEL_422;
            if ( rt_off5 == rd_off )
            {
              *(uint16_t *)code_ptr = 20107;
              code_ptr[2] = rs_off2;
              *(uint16_t *)(code_ptr + 3) = -7807;
              *(uint32_t *)(code_ptr + 5) = 31;
              *(uint16_t *)(code_ptr + 9) = 28371;
              goto LABEL_50;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = rt_off5;
            *(uint16_t *)(code_ptr + 3) = 20107;
            code_ptr[5] = rs_off2;
            *((uint16_t *)code_ptr + 3) = -7807;
            *((uint32_t *)code_ptr + 2) = 31;
            *((uint16_t *)code_ptr + 6) = -5933;
            goto LABEL_130;
          case 7u:
            rd_off = 4 * ((insn >> 11) & 0x1F);
            rs_off3 = 4 * ((insn >> 21) & 0x1F);
            rt_off6 = 4 * (BYTE2(insn) & 0x1F);
            if ( !rd_off )
              goto LABEL_422;
            if ( rt_off6 == rd_off )
            {
              *(uint16_t *)code_ptr = 20107;
              code_ptr[2] = rs_off3;
              *(uint16_t *)(code_ptr + 3) = -7807;
              *(uint32_t *)(code_ptr + 5) = 31;
              *(uint16_t *)(code_ptr + 9) = 32467;
LABEL_50:
              code_ptr[11] = rd_off;
              code_ptr[12] = 79;
              code_ptr += 13;
            }
            else
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rt_off6;
              *(uint16_t *)(code_ptr + 3) = 20107;
              code_ptr[5] = rs_off3;
              *((uint16_t *)code_ptr + 3) = -7807;
              *((uint32_t *)code_ptr + 2) = 31;
              *((uint16_t *)code_ptr + 6) = -1837;
LABEL_130:
              *((uint16_t *)code_ptr + 7) = 18057;
              code_ptr[16] = rd_off;
              code_ptr[17] = 79;
              code_ptr += 18;
            }
            goto LABEL_422;
          case 8u:
            if ( max_insns == 1 )
              goto LABEL_422;
            *(uint16_t *)insn_start = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = 0xC7F7;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *code_ptr = 79;
            *(uint16_t *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * ((insn >> 21) & 0x1F);
            code_ptr[4] = -24;
            *(uint32_t *)(code_ptr + 5) = (uint8_t *)recomp_buffer - code_ptr + 119;
            code_ptr[9] = 80;
            code_ptr += 10;
            dynarec_compile(pc, 1u);
            *code_ptr = 88;
            *(uint16_t *)(code_ptr + 1) = 8447;
            code_ptr += 3;
            *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(uint32_t *)(code_ptr + 3) = pc - 4;
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
            if ( max_insns == 1 )
              goto LABEL_422;
            *(uint16_t *)insn_start = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = 0xC7F7;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            rs_off4 = 4 * ((insn >> 21) & 0x1F);
            rd_off2 = 4 * ((insn >> 11) & 0x1F);
            code2 = code_ptr + 11;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            if ( rd_off2 == rs_off4 )
              recomp_special_flags |= 0x800000u;
            *code2 = 79;
            if ( rd_off2 )
            {
              *(uint16_t *)(code_ptr + 1) = 18119;
              code_ptr[3] = rd_off2;
              jump_target = pc + 4;
              if ( (pc & 0xF0000000) == 0 )
                jump_target |= 0x80000000;
              *((uint32_t *)code_ptr + 1) = jump_target;
              *((uint16_t *)code_ptr + 4) = 18059;
              code_ptr[10] = rs_off4;
              code_ptr[11] = -24;
              *((uint32_t *)code_ptr + 3) = (uint8_t *)recomp_buffer - code_ptr + 112;
              code_ptr[16] = 80;
              code3 = code_ptr + 17;
            }
            else
            {
              *(uint16_t *)(code_ptr + 1) = 18059;
              code_ptr[3] = rs_off4;
              code_ptr[4] = -24;
              *(uint32_t *)(code_ptr + 5) = (uint8_t *)recomp_buffer - code_ptr + 119;
              code_ptr[9] = 80;
              code3 = code_ptr + 10;
            }
            code_ptr = code3;
            dynarec_compile(pc, 1u);
            *code_ptr = 88;
            *(uint16_t *)(code_ptr + 1) = 8447;
            code_ptr += 3;
            *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(uint32_t *)(code_ptr + 3) = pc - 4;
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
            *(uint16_t *)insn_start = 18119;
            code_ptr[2] = -44;
            *(uint32_t *)(code_ptr + 3) = 0;
            code_ptr += 7;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = -52;
            *(uint32_t *)(code_ptr + 3) = pc - 4;
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
            rd_off3 = 4 * ((insn >> 11) & 0x1F);
            if ( !rd_off3 )
              goto LABEL_422;
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = -120;
            goto LABEL_75;
          case 0x11u:
            *(uint16_t *)insn_start = 18059;
            code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 18057;
            code_ptr[5] = -120;
            code_ptr[6] = 79;
            code_ptr += 7;
            goto LABEL_422;
          case 0x12u:
            rd_off3 = 4 * ((insn >> 11) & 0x1F);
            if ( !rd_off3 )
              goto LABEL_422;
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = -124;
LABEL_75:
            *(uint16_t *)(code_ptr + 3) = 18057;
            code_ptr[5] = rd_off3;
            goto LABEL_253;
          case 0x13u:
            *(uint16_t *)insn_start = 18059;
            code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 18057;
            code_ptr[5] = -124;
            code_ptr[6] = 79;
            code_ptr += 7;
            goto LABEL_422;
          case 0x18u:
            *(uint16_t *)insn_start = 18059;
            code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 28407;
            goto LABEL_81;
          case 0x19u:
            *(uint16_t *)insn_start = 18059;
            code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 26359;
LABEL_81:
            code_ptr[5] = 4 * (BYTE2(insn) & 0x1F);
            *((uint16_t *)code_ptr + 3) = 18057;
            code_ptr[8] = -124;
            *(uint16_t *)(code_ptr + 9) = 22153;
            code_ptr[11] = -120;
            code_ptr[12] = 79;
            code_ptr += 13;
            goto LABEL_422;
          case 0x1Au:
            *(uint16_t *)insn_start = 18059;
            code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
            code_ptr[3] = -103;
            *((uint16_t *)code_ptr + 2) = 20107;
            code_ptr[6] = 4 * (BYTE2(insn) & 0x1F);
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
            *(uint16_t *)insn_start = 18059;
            code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = -11727;
            *(uint16_t *)(code_ptr + 5) = 20107;
            code_ptr[7] = 4 * (BYTE2(insn) & 0x1F);
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
            dest_off = 4 * ((insn >> 11) & 0x1F);
            rs_off5 = 4 * ((insn >> 21) & 0x1F);
            reg2_off = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rs_off5 )
            {
              if ( rs_off5 == dest_off )
              {
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = reg2_off;
                *(uint16_t *)(code_ptr + 3) = 17921;
                code_ptr[5] = dest_off;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rs_off5;
              *(uint16_t *)(code_ptr + 3) = 17923;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !reg2_off )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17923;
            code_ptr[4] = reg2_off;
            goto LABEL_273;
          case 0x22u:
          case 0x23u:
            dest_off = 4 * ((insn >> 11) & 0x1F);
            rs_off6 = 4 * ((insn >> 21) & 0x1F);
            reg2_off = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rs_off6 )
            {
              if ( rs_off6 == dest_off )
              {
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = reg2_off;
                *(uint16_t *)(code_ptr + 3) = 17961;
                code_ptr[5] = dest_off;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rs_off6;
              *(uint16_t *)(code_ptr + 3) = 17963;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !reg2_off )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17963;
            code_ptr[4] = reg2_off;
            goto LABEL_273;
          case 0x24u:
            dest_off = 4 * ((insn >> 11) & 0x1F);
            rs_off7 = 4 * ((insn >> 21) & 0x1F);
            reg2_off = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rs_off7 )
            {
              if ( rs_off7 == dest_off )
              {
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = reg2_off;
                *(uint16_t *)(code_ptr + 3) = 17953;
                code_ptr[5] = dest_off;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rs_off7;
              *(uint16_t *)(code_ptr + 3) = 17955;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !reg2_off )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17955;
            code_ptr[4] = reg2_off;
            goto LABEL_273;
          case 0x25u:
            dest_off = 4 * ((insn >> 11) & 0x1F);
            rs_off8 = 4 * ((insn >> 21) & 0x1F);
            reg2_off = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rs_off8 )
            {
              if ( rs_off8 == dest_off )
              {
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = reg2_off;
                *(uint16_t *)(code_ptr + 3) = 17929;
                code_ptr[5] = dest_off;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rs_off8;
              *(uint16_t *)(code_ptr + 3) = 17931;
              goto LABEL_118;
            }
            *(uint16_t *)code_ptr = -16335;
            if ( !reg2_off )
              goto LABEL_121;
            *((uint16_t *)code_ptr + 1) = 17931;
            code_ptr[4] = reg2_off;
            goto LABEL_273;
          case 0x26u:
            dest_off = 4 * ((insn >> 11) & 0x1F);
            rs_off9 = 4 * ((insn >> 21) & 0x1F);
            reg2_off = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off )
              goto LABEL_422;
            if ( rs_off9 )
            {
              if ( rs_off9 == dest_off )
              {
                *(uint16_t *)code_ptr = 18059;
                code_ptr[2] = reg2_off;
                *(uint16_t *)(code_ptr + 3) = 17969;
                code_ptr[5] = dest_off;
                goto LABEL_253;
              }
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rs_off9;
              *(uint16_t *)(code_ptr + 3) = 17971;
LABEL_118:
              code_ptr[5] = reg2_off;
              *((uint16_t *)code_ptr + 3) = 18057;
              code_ptr[8] = dest_off;
              code_ptr[9] = 79;
              code_ptr += 10;
            }
            else
            {
              *(uint16_t *)code_ptr = -16335;
              if ( reg2_off )
              {
                *((uint16_t *)code_ptr + 1) = 17971;
                code_ptr[4] = reg2_off;
                goto LABEL_273;
              }
LABEL_121:
              *((uint16_t *)code_ptr + 1) = 18057;
              code_ptr[4] = dest_off;
              code_ptr[5] = 79;
              code_ptr += 6;
            }
            goto LABEL_422;
          case 0x27u:
            dest_off2 = 4 * ((insn >> 11) & 0x1F);
            rs_off10 = 4 * ((insn >> 21) & 0x1F);
            rt_off7 = 4 * (BYTE2(insn) & 0x1F);
            if ( !dest_off2 )
              goto LABEL_422;
            if ( rs_off10 )
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = rs_off10;
              *(uint16_t *)(code_ptr + 3) = 17931;
              code_ptr[5] = rt_off7;
              *((uint16_t *)code_ptr + 3) = -12041;
              *((uint16_t *)code_ptr + 4) = 18057;
              code_ptr[10] = dest_off2;
              code_ptr[11] = 79;
              code_ptr += 12;
              goto LABEL_422;
            }
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = rt_off7;
            *(uint16_t *)(code_ptr + 3) = -12041;
            break;
          case 0x2Au:
            rd_off4 = 4 * ((insn >> 11) & 0x1F);
            if ( rd_off4 )
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
              *(uint16_t *)(code_ptr + 3) = 17979;
              code_ptr[5] = 4 * (BYTE2(insn) & 0x1F);
              *((uint16_t *)code_ptr + 3) = -25585;
              code_ptr[8] = -64;
              code_ptr[9] = 37;
              *(uint32_t *)(code_ptr + 10) = 1;
              *((uint16_t *)code_ptr + 7) = 18057;
              code_ptr[16] = rd_off4;
              code_ptr[17] = 79;
              code_ptr += 18;
            }
            goto LABEL_422;
          case 0x2Bu:
            rd_off = 4 * ((insn >> 11) & 0x1F);
            if ( !rd_off )
              goto LABEL_422;
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
            *(uint16_t *)(code_ptr + 3) = 17979;
            code_ptr[5] = 4 * (BYTE2(insn) & 0x1F);
            *((uint16_t *)code_ptr + 3) = -28145;
            code_ptr[8] = -64;
            code_ptr[9] = 37;
            *(uint32_t *)(code_ptr + 10) = 1;
            goto LABEL_130;
          default:
            fatal_error_with_message_box(
              "SPEC Opcode %02x UNK (PC %08x) (%08x) (%d,%d)\n",
              insn & 0x3F,
              pc - 4,
              *(uint32_t *)reg_pc,
              frame_counter,
              scanline_counter);
            return ret_val;
        }
        goto LABEL_203;
      case 1u:
        switch ( HIWORD(insn) & 0x1F )
        {
          case 0:
            if ( max_insns == 1 )
              goto LABEL_422;
            rs_idx = (insn >> 21) & 0x1F;
            insn = (uint16_t)insn;
            rs_off11 = 4 * rs_idx;
            if ( (insn & 0x8000) != 0 )
              insn |= 0xFFFF0000;
            *(uint16_t *)insn_start = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = -16335;
            code_ptr[2] = 79;
            *(uint16_t *)(code_ptr + 3) = 17977;
            code_ptr[5] = rs_off11;
            code_ptr[6] = 124;
            goto LABEL_141;
          case 1:
            if ( max_insns == 1 )
              goto LABEL_422;
            rs_idx2 = (insn >> 21) & 0x1F;
            insn = (uint16_t)insn;
            rs_off12 = 4 * rs_idx2;
            if ( (insn & 0x8000) != 0 )
              insn |= 0xFFFF0000;
            *(uint16_t *)insn_start = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = -16335;
            code_ptr[2] = 79;
            *(uint16_t *)(code_ptr + 3) = 17977;
            code_ptr[5] = rs_off12;
            code_ptr[6] = 125;
            goto LABEL_141;
          case 0x10:
            if ( max_insns == 1 )
              goto LABEL_422;
            rs_idx3 = (insn >> 21) & 0x1F;
            insn = (uint16_t)insn;
            rs_off13 = 4 * rs_idx3;
            if ( (insn & 0x8000) != 0 )
              insn |= 0xFFFF0000;
            *(uint16_t *)insn_start = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 124;
            *(uint32_t *)(code_ptr + 3) = (pc + 4) | 0x80000000;
            *(uint16_t *)(code_ptr + 7) = -16335;
            code_ptr[9] = 79;
            *((uint16_t *)code_ptr + 5) = 17977;
            code_ptr[12] = rs_off13;
            code_ptr[13] = 124;
            goto LABEL_151;
          case 0x11:
            if ( max_insns == 1 )
              goto LABEL_422;
            rs_idx4 = (insn >> 21) & 0x1F;
            insn = (uint16_t)insn;
            rs_off14 = 4 * rs_idx4;
            if ( (insn & 0x8000) != 0 )
              insn |= 0xFFFF0000;
            *(uint16_t *)insn_start = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_offset_ptr = (int)(code_ptr + 10);
            code_ptr += 11;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 124;
            *(uint32_t *)(code_ptr + 3) = (pc + 4) | 0x80000000;
            *(uint16_t *)(code_ptr + 7) = -16335;
            code_ptr[9] = 79;
            *((uint16_t *)code_ptr + 5) = 17977;
            code_ptr[12] = rs_off14;
            code_ptr[13] = 125;
LABEL_151:
            code_ptr[14] = 7;
            code_ptr[15] = -72;
            if ( (pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
              target_offset2 = (pc & 0x7FFFF) + 0x200000;
            else
              target_offset2 = pc & 0x1FFFFF;
            *((uint32_t *)code_ptr + 4) = (char *)recomp_code_base + target_offset2;
            *((uint16_t *)code_ptr + 10) = 8447;
            code21 = code_ptr + 22;
            break;
          default:
            fatal_error_with_message_box(" REGIM Opcode %02x UNK PC[%08x]\n", 1, pc - 4);
            return ret_val;
        }
        goto LABEL_428;
      case 2u:
        if ( max_insns != 1 )
        {
          jump_word = 4 * (insn & 0x3FFFFFF);
          if ( !cpu_overclock_setting || ((jump_word ^ (pc - 4)) & 0xFFFFFF) != 0 )
          {
            *(uint16_t *)code_ptr = 32267;
            code_ptr[2] = -44;
            *(uint16_t *)(code_ptr + 3) = -14345;
            *(uint32_t *)(code_ptr + 5) = 0x80000000;
            code_ptr[9] = 117;
            patch_ptr = code_ptr + 10;
            code_ptr += 11;
            patch_offset_ptr = (int)patch_ptr;
            *code_ptr++ = 79;
            dynarec_compile(pc, 1u);
            *code_ptr = -72;
            if ( (jump_word & 0xFFF00000 | pc & 0xF0000000) == PSX_BIOS_UNCACHED_BASE )
              target_offset3 = (jump_word & 0x7FFFF) + 0x200000;
            else
              target_offset3 = jump_word & 0x1FFFFF;
            *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + target_offset3;
            *(uint16_t *)(code_ptr + 5) = 8447;
            code_ptr += 7;
            *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
            *(uint16_t *)code_ptr = 18119;
            code_ptr[2] = 0x80;
            *(uint32_t *)(code_ptr + 3) = pc - 4;
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
            pc = jump_word | pc & 0xF0000000;
          }
        }
        goto LABEL_422;
      case 3u:
        if ( max_insns != 1 )
        {
          *(uint16_t *)code_ptr = 32267;
          code_ptr[2] = -44;
          *(uint16_t *)(code_ptr + 3) = -14345;
          *(uint32_t *)(code_ptr + 5) = 0x80000000;
          code_ptr[9] = 117;
          jump_word2 = 4 * (insn & 0x3FFFFFF);
          patch_offset_ptr = (int)(code_ptr + 10);
          code_ptr += 11;
          *code_ptr = 79;
          *(uint16_t *)(code_ptr + 1) = 18119;
          code_ptr[3] = 124;
          if ( (pc & 0xF0000000) != 0 )
            *((uint32_t *)code_ptr + 1) = pc + 4;
          else
            *((uint32_t *)code_ptr + 1) = (pc + 4) | 0x80000000;
          code_ptr += 8;
          dynarec_compile(pc, 1u);
          *code_ptr = -72;
          if ( (jump_word2 & 0xFFF00000 | pc & 0xF0000000) == PSX_BIOS_UNCACHED_BASE )
            target_offset4 = (jump_word2 & 0x7FFFF) + 0x200000;
          else
            target_offset4 = jump_word2 & 0x1FFFFF;
          *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + target_offset4;
          *(uint16_t *)(code_ptr + 5) = 8447;
          code_ptr += 7;
          *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
          *(uint16_t *)code_ptr = 18119;
          code_ptr[2] = 0x80;
          *(uint32_t *)(code_ptr + 3) = pc - 4;
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
          pc = jump_word2 | pc & 0xF0000000;
          code_ptr += 39;
        }
        goto LABEL_422;
      case 4u:
        if ( max_insns == 1 )
          goto LABEL_422;
        rs_idx5 = (insn >> 21) & 0x1F;
        rt_idx = BYTE2(insn) & 0x1F;
        insn = (uint16_t)insn;
        rs_off15 = 4 * rs_idx5;
        rt_off8 = 4 * rt_idx;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *(uint16_t *)insn_start = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        code4 = code_ptr + 11;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        if ( rt_off8 )
        {
          *(uint16_t *)code4 = 18059;
          code_ptr[2] = rt_off8;
          code5 = code_ptr + 3;
        }
        else
        {
          *(uint16_t *)code4 = -16335;
          code5 = code_ptr + 2;
        }
        code_ptr = code5;
        *code5 = 79;
        *(uint16_t *)(code_ptr + 1) = 17977;
        code_ptr[3] = rs_off15;
        code_ptr[4] = 116;
        goto LABEL_436;
      case 5u:
        if ( max_insns == 1
          || cpu_overclock_setting
          && insn == 339804155
          && *(uint32_t *)((uint16_t)(pc - 8) + mem_read_hooks[(pc - 8) >> 16]) == 4395045
          && !*(uint32_t *)((uint16_t)(pc - 12) + mem_read_hooks[(pc - 12) >> 16])
          && (*(uint32_t *)((uint16_t)(pc - 16) + mem_read_hooks[(pc - 16) >> 16]) & 0xFFFF0000) == 0x8C830000
          && (*(uint32_t *)((uint16_t)(pc - 20) + mem_read_hooks[(pc - 20) >> 16]) & 0xFFFF0000) == 0x8CA20000 )
        {
          goto LABEL_422;
        }
        rs_idx6 = (insn >> 21) & 0x1F;
        rt_idx2 = BYTE2(insn) & 0x1F;
        insn = (uint16_t)insn;
        rs_off16 = 4 * rs_idx6;
        rt_off9 = 4 * rt_idx2;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *(uint16_t *)code_ptr = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        code6 = code_ptr + 11;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        if ( rt_off9 )
        {
          *(uint16_t *)code6 = 18059;
          code_ptr[2] = rt_off9;
          code7 = code_ptr + 3;
        }
        else
        {
          *(uint16_t *)code6 = -16335;
          code7 = code_ptr + 2;
        }
        code_ptr = code7;
        *code7 = 79;
        *(uint16_t *)(code_ptr + 1) = 17977;
        code_ptr[3] = rs_off16;
        code_ptr[4] = 117;
LABEL_436:
        code_ptr[5] = 7;
        code_ptr[6] = -72;
        if ( (pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
          target_offset7 = (pc & 0x7FFFF) + 0x200000;
        else
          target_offset7 = pc & 0x1FFFFF;
        *(uint32_t *)(code_ptr + 7) = (char *)recomp_code_base + target_offset7;
        *(uint16_t *)(code_ptr + 11) = 8447;
        code_ptr += 13;
        dynarec_compile(pc, 1u);
        if ( !insn )
          insn = 1;
        *code_ptr = -72;
        target_pc = pc + 4 * insn;
        if ( (target_pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
          target_offset6 = (target_pc & 0x7FFFF) + 0x200000;
        else
          target_offset6 = target_pc & 0x1FFFFF;
        goto LABEL_447;
      case 6u:
        if ( max_insns == 1 )
          goto LABEL_422;
        rs_idx7 = (insn >> 21) & 0x1F;
        insn = (uint16_t)insn;
        rs_off17 = 4 * rs_idx7;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *(uint16_t *)insn_start = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        *(uint16_t *)code_ptr = -16335;
        code_ptr[2] = 79;
        *(uint16_t *)(code_ptr + 3) = 17977;
        code_ptr[5] = rs_off17;
        code_ptr[6] = 126;
        goto LABEL_141;
      case 7u:
        if ( max_insns == 1 )
          goto LABEL_422;
        rs_idx8 = (insn >> 21) & 0x1F;
        insn = (uint16_t)insn;
        rs_off18 = 4 * rs_idx8;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *(uint16_t *)insn_start = 32267;
        code_ptr[2] = -44;
        *(uint16_t *)(code_ptr + 3) = -14345;
        *(uint32_t *)(code_ptr + 5) = 0x80000000;
        code_ptr[9] = 117;
        patch_offset_ptr = (int)(code_ptr + 10);
        code_ptr += 11;
        *(uint16_t *)code_ptr = -16335;
        code_ptr[2] = 79;
        *(uint16_t *)(code_ptr + 3) = 17977;
        code_ptr[5] = rs_off18;
        code_ptr[6] = 127;
LABEL_141:
        code_ptr[7] = 7;
        code_ptr[8] = -72;
        if ( (pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
          target_offset = (pc & 0x7FFFF) + 0x200000;
        else
          target_offset = pc & 0x1FFFFF;
        *(uint32_t *)(code_ptr + 9) = (char *)recomp_code_base + target_offset;
        *(uint16_t *)(code_ptr + 13) = 8447;
        code21 = code_ptr + 15;
LABEL_428:
        code_ptr = code21;
        dynarec_compile(pc, 1u);
        if ( !insn )
          insn = 1;
        *code_ptr = -72;
        target_pc2 = pc + 4 * insn;
        if ( (target_pc2 & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
          target_offset6 = (target_pc2 & 0x7FFFF) + 0x200000;
        else
          target_offset6 = target_pc2 & 0x1FFFFF;
LABEL_447:
        *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + target_offset6;
        *(uint16_t *)(code_ptr + 5) = 8447;
        code_ptr += 7;
        *(uint8_t *)patch_offset_ptr = (uint8_t)code_ptr - patch_offset_ptr - 1;
        *(uint16_t *)code_ptr = 18119;
        code_ptr[2] = 0x80;
        *(uint32_t *)(code_ptr + 3) = pc - 4;
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
        return insn_count;
      case 8u:
      case 9u:
        rs_idx9 = (insn >> 21) & 0x1F;
        rt_idx3 = BYTE2(insn) & 0x1F;
        insn = (uint16_t)insn;
        rs_off19 = 4 * rs_idx9;
        dest_off2 = 4 * rt_idx3;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( !dest_off2 )
          goto LABEL_422;
        if ( rs_off19 == dest_off2 )
        {
          *(uint16_t *)code_ptr = 18049;
          goto LABEL_197;
        }
        if ( rs_off19 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = rs_off19;
          code8 = code_ptr + 3;
        }
        else
        {
          *(uint16_t *)code_ptr = -16335;
          code8 = code_ptr + 2;
        }
        code_ptr = code8;
        *code8 = 5;
        goto LABEL_202;
      case 0xAu:
        rs_idx10 = (insn >> 21) & 0x1F;
        rt_idx4 = BYTE2(insn) & 0x1F;
        insn = (uint16_t)insn;
        rs_off20 = 4 * rs_idx10;
        rt_off10 = 4 * rt_idx4;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( rt_off10 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = rs_off20;
          code_ptr[3] = 61;
          *((uint32_t *)code_ptr + 1) = insn;
          *((uint16_t *)code_ptr + 4) = -25585;
          code_ptr[10] = -64;
          code_ptr[11] = 37;
          *((uint32_t *)code_ptr + 3) = 1;
          *((uint16_t *)code_ptr + 8) = 18057;
          code_ptr[18] = rt_off10;
          code_ptr[19] = 79;
          code_ptr += 20;
        }
        goto LABEL_422;
      case 0xBu:
        rt_off11 = 4 * (BYTE2(insn) & 0x1F);
        if ( rt_off11 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = 4 * ((insn >> 21) & 0x1F);
          code_ptr[3] = 61;
          *((uint32_t *)code_ptr + 1) = (uint16_t)insn;
          *((uint16_t *)code_ptr + 4) = -28145;
          code_ptr[10] = -64;
          code_ptr[11] = 37;
          *((uint32_t *)code_ptr + 3) = 1;
          *((uint16_t *)code_ptr + 8) = 18057;
          code_ptr[18] = rt_off11;
          code_ptr[19] = 79;
          code_ptr += 20;
        }
        goto LABEL_422;
      case 0xCu:
        rs_idx11 = (insn >> 21) & 0x1F;
        dest_off2 = 4 * (BYTE2(insn) & 0x1F);
        insn = (uint16_t)insn;
        rs_off21 = 4 * rs_idx11;
        if ( !dest_off2 )
          goto LABEL_422;
        if ( rs_off21 == dest_off2 )
        {
          *(uint16_t *)code_ptr = 26241;
          goto LABEL_197;
        }
        if ( rs_off21 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = rs_off21;
          code9 = code_ptr + 3;
          code_ptr += 3;
        }
        else
        {
          *(uint16_t *)code_ptr = -16335;
          code9 = code_ptr + 2;
          code_ptr += 2;
        }
        *code9 = 37;
        goto LABEL_202;
      case 0xDu:
        rs_idx12 = (insn >> 21) & 0x1F;
        dest_off2 = 4 * (BYTE2(insn) & 0x1F);
        insn = (uint16_t)insn;
        rs_off22 = 4 * rs_idx12;
        if ( !dest_off2 )
          goto LABEL_422;
        if ( rs_off22 == dest_off2 )
        {
          *(uint16_t *)code_ptr = 20097;
          goto LABEL_197;
        }
        if ( rs_off22 )
        {
          *(uint16_t *)code_ptr = 18059;
          code_ptr[2] = rs_off22;
          code10 = code_ptr + 3;
          code_ptr += 3;
        }
        else
        {
          *(uint16_t *)code_ptr = -16335;
          code10 = code_ptr + 2;
          code_ptr += 2;
        }
        *code10 = 13;
        goto LABEL_202;
      case 0xEu:
        rs_idx13 = (insn >> 21) & 0x1F;
        dest_off2 = 4 * (BYTE2(insn) & 0x1F);
        insn = (uint16_t)insn;
        rs_off23 = 4 * rs_idx13;
        if ( !dest_off2 )
          goto LABEL_422;
        if ( rs_off23 == dest_off2 )
        {
          *(uint16_t *)code_ptr = 30337;
LABEL_197:
          code_ptr[2] = dest_off2;
          *(uint32_t *)(code_ptr + 3) = insn;
          code_ptr[7] = 79;
          code_ptr += 8;
        }
        else
        {
          if ( rs_off23 )
          {
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = rs_off23;
            code11 = code_ptr + 3;
            code_ptr += 3;
          }
          else
          {
            *(uint16_t *)code_ptr = -16335;
            code11 = code_ptr + 2;
            code_ptr += 2;
          }
          *code11 = 53;
LABEL_202:
          *(uint32_t *)(code_ptr + 1) = insn;
LABEL_203:
          *(uint16_t *)(code_ptr + 5) = 18057;
          code_ptr[7] = dest_off2;
          code_ptr[8] = 79;
          code_ptr += 9;
        }
        goto LABEL_422;
      case 0xFu:
        dest_off = 4 * (BYTE2(insn) & 0x1F);
        if ( dest_off )
        {
          *code_ptr = -72;
          *(uint32_t *)(code_ptr + 1) = (uint16_t)insn << 16;
LABEL_273:
          *(uint16_t *)(code_ptr + 5) = 18057;
          code_ptr[7] = dest_off;
          code_ptr[8] = 79;
          code_ptr += 9;
        }
        goto LABEL_422;
      case 0x10u:
        cop0_sel = (insn >> 21) & 0x1F;
        if ( cop0_sel )
        {
          if ( cop0_sel == 4 )
          {
            cop0_off = 4 * ((insn >> 11) & 0x1F);
            if ( pc == 548880 )
              ui_error("bye pie\n");
            if ( cop0_off == 12 )
            {
              *(uint16_t *)code_ptr = 32393;
              code_ptr[2] = -112;
              code_ptr[3] = 87;
              code_ptr[4] = 86;
              *(uint16_t *)(code_ptr + 5) = 18119;
              code_ptr[7] = -116;
              *((uint32_t *)code_ptr + 2) = insn;
              handler = op_MTC0;
LABEL_242:
              code_ptr[12] = -24;
LABEL_243:
              *(uint32_t *)(code_ptr + 13) = handler - code_ptr - 17;
              code_ptr[17] = 94;
              code_ptr[18] = 95;
              code_ptr[19] = 79;
              code_ptr += 20;
            }
            else
            {
              *(uint16_t *)code_ptr = 18059;
              code_ptr[2] = 4 * (BYTE2(insn) & 0x1F);
              *(uint16_t *)(code_ptr + 3) = 18057;
              code_ptr[5] = (cop0_off & 0x3F) - 108;
              code_ptr[6] = 79;
              code_ptr += 7;
              if ( cop0_off == 48 || cop0_off == 52 )
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
                *(uint32_t *)(code_ptr + 33) = pc;
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
              if ( cop0_off == 48 )
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
            if ( cop0_sel != 16 )
              fatal_error_with_message_box(" COP0 Opcode %02x UNK \n", (insn >> 21) & 0x1F);
            *(uint16_t *)insn_start = 18059;
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
          cop0_off2 = (uint8_t)(4 * ((insn >> 11) & 0x1F));
          rt_off12 = 4 * (BYTE2(insn) & 0x1F);
          if ( (uint8_t)cop0_off2 == 12 )
          {
            *(uint16_t *)insn_start = 32393;
            code_ptr[2] = -112;
            code_ptr[3] = 87;
            code_ptr[4] = 86;
            *(uint16_t *)(code_ptr + 5) = 18119;
            code_ptr[7] = -116;
            *((uint32_t *)code_ptr + 2) = insn;
            code_ptr[12] = -24;
            *(uint32_t *)(code_ptr + 13) = (char *)op_MFC0 - (char *)code_ptr - 17;
            code_ptr[17] = 94;
            code_ptr[18] = 95;
            code_ptr[19] = 79;
            code_ptr += 20;
          }
          else if ( rt_off12 )
          {
            *(uint16_t *)code_ptr = 18059;
            code_ptr[2] = (cop0_off2 & 0x3F) - 108;
            *(uint16_t *)(code_ptr + 3) = 18057;
            code_ptr[5] = rt_off12;
LABEL_253:
            code_ptr[6] = 79;
            code_ptr += 7;
          }
        }
        goto LABEL_422;
      case 0x12u:
        switch ( (insn >> 21) & 0x1F )
        {
          case 0u:
            if ( (insn == 1208125440 || insn == 1208127488 || insn == 1208129536)
              && *(uint32_t *)((uint16_t)pc + mem_read_hooks[HIWORD(pc)]) == 6166570 )
            {
              insn_start[18] = -95;
              *(uint32_t *)(code_ptr + 19) = (char *)&gte_regs + (uint8_t)(4 * ((insn >> 11) & 0x1F));
              *(uint16_t *)(code_ptr + 23) = 18057;
              code_ptr[25] = 4 * (BYTE2(insn) & 0x1F);
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
              pc += 4;
              goto LABEL_422;
            }
            if ( max_insns != 1 )
              goto LABEL_265;
            branch_offset = (uint16_t)*(uint32_t *)((uint16_t)(pc - 8) + mem_read_hooks[(pc - 8) >> 16]);
            if ( (branch_offset & 0x8000) != 0 )
              branch_offset |= 0xFFFF0000;
            if ( *(uint32_t *)((uint16_t)(pc + 4 * branch_offset - 4) + mem_read_hooks[(pc + 4 * branch_offset - 4) >> 16]) != 1216872448 )
            {
              insn_start = code_ptr;
LABEL_265:
              dest_off2 = 4 * (BYTE2(insn) & 0x1F);
              cop2_off = 4 * ((insn >> 11) & 0x1F);
              if ( dest_off2 )
              {
                if ( cop2_off != 124 && cop2_off != 116 )
                {
                  *insn_start = -95;
                  *(uint32_t *)(code_ptr + 1) = (char *)&gte_regs + (uint8_t)(4 * ((insn >> 11) & 0x1F));
                  goto LABEL_203;
                }
                *(uint16_t *)insn_start = 32393;
                code_ptr[2] = -112;
                code_ptr[3] = 87;
                code_ptr[4] = 86;
                *(uint16_t *)(code_ptr + 5) = 18119;
                code_ptr[7] = -116;
                *((uint32_t *)code_ptr + 2) = insn;
                code_ptr[12] = -24;
                handler = gte_exec_opcode;
                goto LABEL_243;
              }
              *insn_start = 79;
              ++code_ptr;
            }
            goto LABEL_422;
          case 2u:
            dest_off = 4 * (BYTE2(insn) & 0x1F);
            if ( dest_off )
            {
              *insn_start = -95;
              *(uint32_t *)(code_ptr + 1) = (char *)gte_regs.ctrl + (uint8_t)(4 * ((insn >> 11) & 0x1F));
              goto LABEL_273;
            }
LABEL_33:
            *insn_start = 79;
            ++code_ptr;
            goto LABEL_422;
          case 4u:
            gte_idx = (insn >> 11) & 0x1F;
            if ( gte_idx >= 0xEu && gte_idx <= 0x13u || gte_idx == 28 )
              goto LABEL_304;
            *insn_start = 79;
            *(uint16_t *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * (BYTE2(insn) & 0x1F);
            if ( gte_idx == 1 || gte_idx == 3 || gte_idx == 5 || gte_idx == 8 || gte_idx == 9 || gte_idx == 10 || gte_idx == 11 )
            {
              *((uint16_t *)code_ptr + 2) = -16625;
              gte_ptr = &gte_regs.data[gte_idx];
              goto LABEL_286;
            }
            code_ptr[4] = -93;
            *(uint32_t *)(code_ptr + 5) = (char *)&gte_regs + gte_idx * 4;
            code_ptr += 9;
            goto LABEL_422;
          case 6u:
            *insn_start = 79;
            gte_idx2 = (insn >> 11) & 0x1F;
            *(uint16_t *)(code_ptr + 1) = 18059;
            code_ptr[3] = 4 * (BYTE2(insn) & 0x1F);
            if ( gte_idx2 == 4 || gte_idx2 == 12 || gte_idx2 == 20 || gte_idx2 == 26 || gte_idx2 == 27 || gte_idx2 == 29 || gte_idx2 == 30 )
            {
              *((uint16_t *)code_ptr + 2) = -16625;
              gte_ptr = &gte_regs.ctrl[gte_idx2];
LABEL_286:
              code_ptr[6] = -64;
              code_ptr[7] = -93;
              *((uint32_t *)code_ptr + 2) = gte_ptr;
              code_ptr += 12;
            }
            else
            {
              code_ptr[4] = -93;
              *(uint32_t *)(code_ptr + 5) = &gte_regs.ctrl[gte_idx2];
              code_ptr += 9;
            }
            goto LABEL_422;
          default:
            gte_opcode = insn & 0x1FFFFFF;
            if ( (insn & 0x1FFFFFF) > 0x280030 )
            {
              if ( gte_opcode != 20971526 )
                goto LABEL_304;
              *(uint16_t *)insn_start = 1479;
              *(uint32_t *)(code_ptr + 2) = &gte_regs.ctrl[GTE_CTRL_FLAG];
              *(uint32_t *)(code_ptr + 6) = 0;
              *((uint16_t *)code_ptr + 5) = -16625;
              code_ptr[12] = 5;
              *(uint32_t *)(code_ptr + 13) = &gte_regs.data[GTE_DATA_SXY1].s16.lo;
              *(uint16_t *)(code_ptr + 17) = -16625;
              code_ptr[19] = 13;
              *((uint32_t *)code_ptr + 5) = &gte_regs.data[GTE_DATA_SXY2].s16.lo;
              *((uint16_t *)code_ptr + 12) = -16625;
              code_ptr[26] = 21;
              *(uint32_t *)(code_ptr + 27) = &gte_regs.data[GTE_DATA_SXY0];
              *(uint16_t *)(code_ptr + 31) = -16085;
              *(uint16_t *)(code_ptr + 33) = -20721;
              code_ptr[35] = -62;
              *((uint16_t *)code_ptr + 18) = -10101;
              *((uint16_t *)code_ptr + 19) = -16625;
              code_ptr[40] = 5;
              *(uint32_t *)(code_ptr + 41) = &gte_regs.data[GTE_DATA_SXY0].s16.lo;
              *(uint16_t *)(code_ptr + 45) = -16625;
              code_ptr[47] = 21;
              *((uint32_t *)code_ptr + 12) = &gte_regs.data[GTE_DATA_SXY1];
              *((uint16_t *)code_ptr + 26) = -14293;
              *((uint16_t *)code_ptr + 27) = -20721;
              code_ptr[56] = -54;
              *(uint16_t *)(code_ptr + 57) = -9981;
              *(uint16_t *)(code_ptr + 59) = -16625;
              code_ptr[61] = 13;
              *(uint32_t *)(code_ptr + 62) = &gte_regs.data[GTE_DATA_SXY1].s16.lo;
              *((uint16_t *)code_ptr + 33) = -16625;
              code_ptr[68] = 21;
              *(uint32_t *)(code_ptr + 69) = &gte_regs.data[GTE_DATA_SXY2];
              *(uint16_t *)(code_ptr + 73) = -16085;
              *(uint16_t *)(code_ptr + 75) = -20721;
              code_ptr[77] = -62;
              *((uint16_t *)code_ptr + 39) = -10237;
              *((uint16_t *)code_ptr + 40) = -15477;
              code_ptr[82] = -93;
              *(uint32_t *)(code_ptr + 83) = &gte_regs.data[GTE_DATA_MAC0];
              *(uint16_t *)(code_ptr + 87) = 32653;
              code_ptr[89] = -4;
              code_ptr += 90;
            }
            else
            {
              if ( (insn & 0x1FFFFFF) == 0x280030 )
              {
                gte_handler = gte_rtpt;
              }
              else
              {
                if ( gte_opcode != 1572865 && gte_opcode != 1671169 )
                {
LABEL_304:
                  *(uint16_t *)insn_start = 32393;
                  code_ptr[2] = -112;
                  code_ptr[3] = 87;
                  code_ptr[4] = 86;
                  *(uint16_t *)(code_ptr + 5) = 18119;
                  code_ptr[7] = -116;
                  *((uint32_t *)code_ptr + 2) = insn;
                  handler = gte_exec_opcode;
                  goto LABEL_242;
                }
                gte_handler = gte_rtps;
              }
              *insn_start = -24;
              *(uint32_t *)(code_ptr + 1) = (char *)gte_handler - (char *)code_ptr - 5;
              *(uint16_t *)(code_ptr + 5) = 32653;
              code_ptr[7] = -4;
              code_ptr += 8;
            }
LABEL_422:
            if ( slot_flag )
              return insn_count;
            insn_start = code_ptr;
            limit = max_insns;
            break;
        }
        break;
      case 0x20u:
        rt_idx5 = BYTE2(insn) & 0x1F;
        base_off = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off13 = 4 * rt_idx5;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off;
          code12 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off;
          code12 = code_ptr + 3;
        }
        code_ptr = code12;
        *code12 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 187;
        if ( !rt_off13 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        *(uint16_t *)(code_ptr + 5) = -16881;
        goto LABEL_314;
      case 0x21u:
        rt_idx6 = BYTE2(insn) & 0x1F;
        base_off2 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off13 = 4 * rt_idx6;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off2;
          code13 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off2;
          code13 = code_ptr + 3;
        }
        code_ptr = code13;
        *code13 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 315;
        if ( rt_off13 )
        {
          *(uint16_t *)(code_ptr + 5) = -16625;
LABEL_314:
          code_ptr[7] = -64;
          *((uint16_t *)code_ptr + 4) = 18057;
          code_ptr[10] = rt_off13;
          code_ptr += 11;
        }
        else
        {
          code_ptr += 5;
        }
        goto LABEL_422;
      case 0x22u:
        rt_idx7 = BYTE2(insn) & 0x1F;
        base_off3 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off14 = 4 * rt_idx7;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *insn_start = -72;
        *(uint32_t *)(code_ptr + 1) = insn;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = base_off3;
        *((uint16_t *)code_ptr + 4) = -10101;
        *((uint16_t *)code_ptr + 5) = -7295;
        *((uint32_t *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(uint32_t *)(code_ptr + 17) = -4;
        code_ptr[21] = -24;
        *(uint32_t *)(code_ptr + 22) = (uint8_t *)recomp_buffer - code_ptr + 422;
        if ( !rt_off14 )
        {
          code_ptr += 26;
          goto LABEL_422;
        }
        *((uint16_t *)code_ptr + 13) = 3211;
        code_ptr[28] = -99;
        *(uint32_t *)(code_ptr + 29) = lwl_mask_table;
        *(uint16_t *)(code_ptr + 33) = 20001;
        code_ptr[35] = rt_off14;
        *((uint16_t *)code_ptr + 18) = 3211;
        code_ptr[38] = -99;
        *(uint32_t *)(code_ptr + 39) = lwl_shift_table;
        *(uint16_t *)(code_ptr + 43) = -7981;
        goto LABEL_328;
      case 0x23u:
        rt_idx8 = BYTE2(insn) & 0x1F;
        base_off4 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off15 = 4 * rt_idx8;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off4;
          code14 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off4;
          code14 = code_ptr + 3;
        }
        code_ptr = code14;
        fast_timing = adjust_timing == 0;
        *code14 = -87;
        *(uint32_t *)(code_ptr + 1) = 1602224128;
        code_ptr[5] = 117;
        if ( fast_timing )
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
          if ( rt_off15 )
          {
            *(uint16_t *)(code_ptr + 29) = 18057;
            code_ptr[31] = rt_off15;
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
          if ( rt_off15 )
          {
            *((uint16_t *)code_ptr + 17) = 18057;
            code_ptr[36] = rt_off15;
            code_ptr += 37;
          }
          else
          {
            code_ptr += 34;
          }
        }
        goto LABEL_422;
      case 0x24u:
        if ( max_insns == 1
          && insn == -1820196858
          && *(uint32_t *)((uint16_t)(pc - 8) + mem_read_hooks[(pc - 8) >> 16]) == 65011720
          && *(uint32_t *)((uint16_t)(pc + 128) + mem_read_hooks[(pc + 128) >> 16]) == 608305167 )
        {
          dbg_print(" * warning: skullmonkeys trick enabled. \n");
          goto LABEL_422;
        }
        rt_idx9 = BYTE2(insn) & 0x1F;
        base_off5 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off16 = 4 * rt_idx9;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off5;
          code15 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off5;
          code15 = code_ptr + 3;
        }
        code_ptr = code15;
        *code15 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 187;
        if ( !rt_off16 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        code_ptr[5] = 37;
        *(uint32_t *)(code_ptr + 6) = 255;
        goto LABEL_354;
      case 0x25u:
        rt_idx10 = BYTE2(insn) & 0x1F;
        base_off6 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off16 = 4 * rt_idx10;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off6;
          code16 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off6;
          code16 = code_ptr + 3;
        }
        code_ptr = code16;
        *code16 = -24;
        *(uint32_t *)(code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 315;
        if ( !rt_off16 )
        {
          code_ptr += 5;
          goto LABEL_422;
        }
        code_ptr[5] = 37;
        *(uint32_t *)(code_ptr + 6) = 0xFFFF;
LABEL_354:
        *((uint16_t *)code_ptr + 5) = 18057;
        code_ptr[12] = rt_off16;
        goto LABEL_355;
      case 0x26u:
        rt_idx11 = BYTE2(insn) & 0x1F;
        base_off7 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off14 = 4 * rt_idx11;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *insn_start = -72;
        *(uint32_t *)(code_ptr + 1) = insn;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = base_off7;
        *((uint16_t *)code_ptr + 4) = -10101;
        *((uint16_t *)code_ptr + 5) = -7295;
        *((uint32_t *)code_ptr + 3) = 3;
        code_ptr[16] = 37;
        *(uint32_t *)(code_ptr + 17) = -4;
        code_ptr[21] = -24;
        *(uint32_t *)(code_ptr + 22) = (uint8_t *)recomp_buffer - code_ptr + 422;
        if ( rt_off14 )
        {
          *((uint16_t *)code_ptr + 13) = 0xC8B;
          code_ptr[28] = 0x9D;
          *(uint32_t *)(code_ptr + 29) = lwr_mask_table;
          *(uint16_t *)(code_ptr + 33) = 0x4E21;
          code_ptr[35] = rt_off14;
          *((uint16_t *)code_ptr + 18) = 0xC8B;
          code_ptr[38] = 0x9D;
          *(uint32_t *)(code_ptr + 39) = lwr_shift_table;
          *(uint16_t *)(code_ptr + 43) = 0xE8D3;
LABEL_328:
          *(uint16_t *)(code_ptr + 45) = 0x4609;
          code_ptr[47] = rt_off14;
          code_ptr += 48;
        }
        else
        {
          code_ptr += 26;
        }
        goto LABEL_422;
      case 0x28u:
        rt_idx12 = BYTE2(insn) & 0x1F;
        base_off8 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off17 = 4 * rt_idx12;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off8;
          code17 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off8;
          code17 = code_ptr + 3;
        }
        code_ptr = code17;
        *(uint16_t *)code17 = 24203;
        code_ptr[2] = rt_off17;
        *(uint16_t *)(code_ptr + 3) = -7295;
        *(uint32_t *)(code_ptr + 5) = 255;
        code_ptr[9] = -24;
        *(uint32_t *)(code_ptr + 10) = (uint8_t *)recomp_buffer - code_ptr + 562;
        code_ptr += 14;
        goto LABEL_422;
      case 0x29u:
        rt_idx13 = BYTE2(insn) & 0x1F;
        base_off9 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off18 = 4 * rt_idx13;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off9;
          code18 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off9;
          code18 = code_ptr + 3;
        }
        code_ptr = code18;
        *(uint16_t *)code18 = 24203;
        code_ptr[2] = rt_off18;
        *(uint16_t *)(code_ptr + 3) = -7295;
        *(uint32_t *)(code_ptr + 5) = 0xFFFF;
        code_ptr[9] = -24;
        *(uint32_t *)(code_ptr + 10) = (uint8_t *)recomp_buffer - code_ptr + 754;
        code_ptr += 14;
        goto LABEL_422;
      case 0x2Au:
        rt_idx14 = BYTE2(insn) & 0x1F;
        base_off10 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off19 = 4 * rt_idx14;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *insn_start = -72;
        *(uint32_t *)(code_ptr + 1) = insn;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = base_off10;
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
        code_ptr[45] = rt_off19;
        *((uint16_t *)code_ptr + 23) = -5165;
        goto LABEL_384;
      case 0x2Bu:
        rt_idx15 = BYTE2(insn) & 0x1F;
        base_off11 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off20 = 4 * rt_idx15;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        if ( insn )
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = insn;
          *(uint16_t *)(code_ptr + 5) = 17923;
          code_ptr[7] = base_off11;
          code19 = code_ptr + 8;
        }
        else
        {
          *(uint16_t *)insn_start = 18059;
          code_ptr[2] = base_off11;
          code19 = code_ptr + 3;
        }
        code_ptr = code19;
        *(uint16_t *)code19 = 24203;
        code_ptr[2] = rt_off20;
        code_ptr[3] = -24;
        *((uint32_t *)code_ptr + 1) = (uint8_t *)recomp_buffer - code_ptr + 952;
        code20 = code_ptr + 8;
        code_ptr += 8;
        if ( max_insns != 1 )
        {
          *code20 = -72;
          if ( (pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
            target_offset5 = (pc & 0x7FFFF) + 0x200000;
          else
            target_offset5 = pc & 0x1FFFFF;
          *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + target_offset5;
          *(uint16_t *)(code_ptr + 5) = 8447;
          code_ptr += 7;
        }
        goto LABEL_422;
      case 0x2Eu:
        rt_idx16 = BYTE2(insn) & 0x1F;
        base_off12 = 4 * ((insn >> 21) & 0x1F);
        insn = (uint16_t)insn;
        rt_off21 = 4 * rt_idx16;
        if ( (insn & 0x8000) != 0 )
          insn |= 0xFFFF0000;
        *insn_start = -72;
        *(uint32_t *)(code_ptr + 1) = insn;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = base_off12;
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
        code_ptr[45] = rt_off21;
        *((uint16_t *)code_ptr + 23) = -7213;
LABEL_384:
        *((uint16_t *)code_ptr + 24) = -10229;
        code_ptr[50] = 88;
        code_ptr[51] = -24;
        *((uint32_t *)code_ptr + 13) = (uint8_t *)recomp_buffer - code_ptr + 904;
        code_ptr += 56;
        goto LABEL_422;
      case 0x32u:
        gte_off = 4 * (BYTE2(insn) & 0x1F);
        disp = (uint16_t)insn;
        if ( (insn & 0x8000) != 0 )
          disp = insn | 0xFFFF0000;
        if ( gte_off >= 0x38u && gte_off <= 0x4Cu || gte_off == 112 )
        {
          *(uint16_t *)insn_start = 32393;
          code_ptr[2] = -112;
          code_ptr[3] = 87;
          code_ptr[4] = 86;
          *(uint16_t *)(code_ptr + 5) = 18119;
          code_ptr[7] = -116;
          *((uint32_t *)code_ptr + 2) = insn;
          cop2_handler = op_LWC2;
          goto LABEL_414;
        }
        *insn_start = -72;
        *(uint32_t *)(code_ptr + 1) = disp;
        *(uint16_t *)(code_ptr + 5) = 17923;
        code_ptr[7] = 4 * ((insn >> 21) & 0x1F);
        code_ptr[8] = -24;
        *(uint32_t *)(code_ptr + 9) = (uint8_t *)recomp_buffer - code_ptr + 435;
        if ( gte_off == 28 )
        {
LABEL_355:
          code_ptr += 13;
        }
        else if ( gte_off == 4 || gte_off == 12 || gte_off == 20 || gte_off == 32 || gte_off == 36 || gte_off == 40 || gte_off == 44 )
        {
          *(uint16_t *)(code_ptr + 13) = -16625;
          code_ptr[15] = -64;
          code_ptr[16] = -93;
          *(uint32_t *)(code_ptr + 17) = (char *)&gte_regs + gte_off;
          code_ptr += 21;
        }
        else
        {
          code_ptr[13] = -93;
          *(uint32_t *)(code_ptr + 14) = (char *)&gte_regs + gte_off;
          code_ptr += 18;
        }
        goto LABEL_422;
      case 0x3Au:
        gte_off2 = 4 * (BYTE2(insn) & 0x1F);
        disp2 = (uint16_t)insn;
        if ( (insn & 0x8000) != 0 )
          disp2 = insn | 0xFFFF0000;
        if ( gte_off2 == 124 || gte_off2 == 116 )
        {
          *(uint16_t *)insn_start = 32393;
          code_ptr[2] = -112;
          code_ptr[3] = 87;
          code_ptr[4] = 86;
          *(uint16_t *)(code_ptr + 5) = 18119;
          code_ptr[7] = -116;
          *((uint32_t *)code_ptr + 2) = insn;
          cop2_handler = op_SWC2;
LABEL_414:
          code_ptr[12] = -24;
          *(uint32_t *)(code_ptr + 13) = cop2_handler - code_ptr - 17;
          code_ptr[17] = 94;
          code_ptr[18] = 95;
          *(uint16_t *)(code_ptr + 19) = 32653;
          code_ptr[21] = -5;
          code_ptr += 22;
        }
        else
        {
          *insn_start = -72;
          *(uint32_t *)(code_ptr + 1) = disp2;
          *(uint16_t *)(code_ptr + 5) = 7563;
          *(uint32_t *)(code_ptr + 7) = (char *)&gte_regs + (uint8_t)(4 * (BYTE2(insn) & 0x1F));
          *(uint16_t *)(code_ptr + 11) = 17923;
          code_ptr[13] = 4 * ((insn >> 21) & 0x1F);
          code_ptr[14] = -24;
          *(uint32_t *)(code_ptr + 15) = (uint8_t *)recomp_buffer - code_ptr + 941;
          code_ptr += 19;
        }
        goto LABEL_422;
      default:
        fatal_error_with_message_box(
          " Opcode %02x UNK (PC %08x) (%d,%d)\n",
          insn >> 26,
          pc - 4,
          frame_counter,
          scanline_counter);
        return ret_val;
    }
  }
  if ( insn_count == 1 )
    fatal_error_with_message_box(" 1 compiled and??? pc %04x n:%d t:%d\n", pc, limit, 1);
  if ( limit == 1 )
    fatal_error_with_message_box("dynarec problem (slot_in and recompiled) [%08x] [%d]\n", pc, 1);
  *insn_start = -72;
  if ( (pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
    target_offset8 = (pc & 0x7FFFF) + 0x200000;
  else
    target_offset8 = pc & 0x1FFFFF;
  *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + target_offset8;
  *(uint16_t *)(code_ptr + 5) = 8447;
  code_ptr += 7;
  return insn_count - 1;
}

unsigned int dynarec_invalidate_range(int addr, int count)
{
  int offset;
  char *base;
  LPVOID fill_value;
  int remaining;
  LPVOID prev;
  unsigned int start;
  unsigned int current;
  unsigned int end;

  if ( (addr & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
    offset = (addr & 0x7FFFC) + 0x200000;
  else
    offset = addr & 0x1FFFFC;
  base = (char *)recomp_code_base;
  fill_value = recomp_buffer;
  if ( *(LPVOID *)((char *)recomp_code_base + offset) != recomp_buffer )
  {
    remaining = ((uint8_t *)recomp_buffer - (uint8_t *)recomp_metadata) >> 2;
    *(uint32_t *)((char *)recomp_code_base + offset) = recomp_buffer;
    if ( remaining )
    {
      while ( 1 )
      {
        base = (char *)recomp_code_base;
        fill_value = recomp_buffer;
        prev = *(LPVOID *)((char *)recomp_code_base + offset - 4);
        offset -= 4;
        if ( prev == recomp_buffer )
          break;
        --remaining;
        *(uint32_t *)((char *)recomp_code_base + offset) = recomp_buffer;
        if ( !remaining )
          goto LABEL_8;
      }
    }
    else
    {
LABEL_8:
      fill_value = recomp_buffer;
      base = (char *)recomp_code_base;
    }
  }
  if ( (addr & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
    start = (addr & 0x7FFFC) + 0x200000;
  else
    start = addr & 0x1FFFFC;
  current = start;
  end = start + 4 * count;
  if ( start < end )
  {
    while ( 1 )
    {
      *(uint32_t *)&base[current] = fill_value;
      current += 4;
      if ( current >= end )
        break;
      fill_value = recomp_buffer;
      base = (char *)recomp_code_base;
    }
  }
  return current;
}

uint8_t *dynarec_init()
{
  unsigned int raw_buf;
  unsigned int index;
  uint8_t *tail1;
  uint8_t *tail2;
  uint8_t *tail3;
  uint8_t *end;

  if ( !recomp_buffer )
  {
    raw_buf = (unsigned int)malloc(0x200040u);
    recomp_buffer = (LPVOID)raw_buf;
    if ( !raw_buf )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
    if ( (raw_buf & 0x3F) != 0 )
      recomp_buffer = (LPVOID)((raw_buf & 0xFFFFFFC0) + 64);
    recomp_code_base = malloc(0x280000u);
    if ( !recomp_code_base )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
    recomp_metadata = malloc(0x280000u);
    if ( !recomp_metadata )
      fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
  }
  for ( index = 0; index < 0x280000; index += 4 )
    *(uint32_t *)((char *)recomp_code_base + index) = recomp_buffer;
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
  *(uint32_t *)(code_ptr + 10) = PSX_BIOS_UNCACHED_BASE;
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
  *(uint32_t *)(code_ptr + 7) = PSX_BIOS_BASE;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = PSX_HW_BASE;
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
  *(uint32_t *)(code_ptr + 7) = PSX_BIOS_BASE;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = PSX_HW_BASE;
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
  *(uint32_t *)(code_ptr + 7) = PSX_BIOS_BASE;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = PSX_HW_BASE;
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
  tail1 = code_ptr + 55;
  qmemcpy(code_ptr + 55, &recomp_hw_write_template, 0x3Cu);
  tail1 += 60;
  *(uint16_t *)tail1 = recomp_hw_write_tail_word;
  tail1[2] = recomp_hw_write_tail_byte;
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
  *(uint32_t *)(code_ptr + 7) = PSX_BIOS_BASE;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = PSX_HW_BASE;
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
  tail2 = code_ptr + 56;
  qmemcpy(code_ptr + 56, &recomp_hw_write_template, 0x3Cu);
  tail2 += 60;
  *(uint16_t *)tail2 = recomp_hw_write_tail_word;
  tail2[2] = recomp_hw_write_tail_byte;
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
  *(uint32_t *)(code_ptr + 7) = PSX_BIOS_BASE;
  *(uint16_t *)(code_ptr + 11) = 0xFA81;
  *(uint32_t *)(code_ptr + 13) = PSX_HW_BASE;
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
  tail3 = code_ptr + 55;
  qmemcpy(code_ptr + 55, &recomp_hw_write_template, 0x3Cu);
  tail3 += 60;
  *(uint16_t *)tail3 = recomp_hw_write_tail_word;
  tail3[2] = recomp_hw_write_tail_byte;
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
  end = code_ptr + 192;
  code_ptr += 192;
  return end;
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
  int offset;
  int64_t code_addr;
  int64_t result;

  *code_ptr = 0xBF;
  *(uint32_t *)(code_ptr + 1) = cpu_speed_scale;
  code_ptr[5] = 0xBE;
  *(uint32_t *)(code_ptr + 6) = cpu_gpr;
  code_ptr[10] = 0xB8;
  if ( (*(uint32_t *)reg_pc & 0xFFF00000) == PSX_BIOS_UNCACHED_BASE )
    offset = (*(uint32_t *)reg_pc & 0x7FFFF) + 0x200000;
  else
    offset = *(uint32_t *)reg_pc & 0x1FFFFF;
  LODWORD(code_addr) = (char *)recomp_code_base + offset;
  *(uint32_t *)(code_ptr + 11) = code_addr;
  HIDWORD(code_addr) = code_ptr;
  *(uint16_t *)(code_ptr + 15) = 8447;
  code_ptr += 64;
  spu_async_update_counter = 0;
  result = code_addr;
  ((void (*)(void))((char *)recomp_buffer + 1152))();
  return result;
}

char *dynarec_invalidate()
{
  unsigned int index;

  for ( index = 0; index < 0x280000; index += 4 )
    *(uint32_t *)((char *)recomp_code_base + index) = recomp_buffer;
  code_ptr = (uint8_t *)recomp_buffer + 1216;
  return (char *)recomp_buffer + 1216;
}

void nullsub_1()
{
  ;
}
