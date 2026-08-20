#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
unsigned int spu_async_update_counter;
unsigned int sio_scheduled_transfer_timeout;
unsigned int rcnt1_counter;
unsigned int rcnt1_mode;
unsigned int rcnt1_compare;
unsigned int rcnt2_counter;
unsigned int rcnt3_counter;
unsigned int spu_irq_pending_count;
unsigned int frame_counter;
unsigned int scanline_counter;


uint32_t cpu_opcode;
cpu_registers cpu_regs;
unsigned char *reg_pc = (unsigned char *)&cpu_regs;

int cpu_clear_regs()
{
  *(uint32_t *)reg_pc = PSX_BIOS_UNCACHED_BASE;
  memset(cpu_gpr, 0, 0x80u);
  memset(cop0_regs, 0, 0x40u);
  hw_update_counter = 0;
  frame_counter = 0;
  scanline_counter = 0;
  cpu_LO = 0;
  cpu_HI = 0;
  return 0;
}

unsigned int cpu_load_bios_shell()
{
  int pc;
  unsigned int opcode;
  int counter;

  pc = *(uint32_t *)reg_pc;
  opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
  for ( cpu_opcode = opcode; *(uint32_t *)reg_pc != 0x80030000; cpu_opcode = opcode )
  {
    *(uint32_t *)reg_pc = pc + 4;
    cpu_main_table[opcode >> 26]();
    counter = --hw_update_counter;
    if ( hw_update_counter < 0 )
    {
      hw_update_counter = cpu_speed_scale + counter;
      if ( ++scanline_counter >= (unsigned int)video_scanlines )
      {
        scanline_counter = 0;
        ++frame_counter;
      }
    }
    pc = *(uint32_t *)reg_pc;
    opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
  }
  return opcode;
}

int cpu_execute()
{
  unsigned int opcode;
  uint8_t cheat_count;
  uint8_t index;
  int addr;
  int cheat;
  uint8_t next;
  uint32_t *entry;
  int count;
  int counter;
  bool spu_update;
  unsigned int rcnt2_inc;
  int rcnt_inc;
  int rcnt1_inc;
  unsigned int scanlines;
  int irq;
  int reset;
  uint8_t index2;

  while ( 1 )
  {
    while ( 1 )
    {
      opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
      cheat_count = active_mini_cheat_count;
      cpu_opcode = opcode;
      if ( active_mini_cheat_count )
      {
        index = 0;
        index2 = 0;
        addr = *(uint32_t *)reg_pc & 0x1FFFFF;
        do
        {
          cheat = mini_cheat_id_array[2 * index2];
          if ( (cheat & 0x1FFFFF) == addr )
          {
            opcode = mini_cheat_attr_array[2 * index2];
            if ( (cheat & 0xF0000000) == 0 )
            {
              next = index + 1;
              if ( (uint8_t)(index + 1) < cheat_count )
              {
                entry = (uint32_t *)(8 * next + 5991868);
                count = (uint8_t)(cheat_count - next);
                do
                {
                  *(entry - 1) = entry[1];
                  *entry = entry[2];
                  entry += 2;
                  --count;
                }
                while ( count );
                index = index2;
              }
              --cheat_count;
            }
          }
          index2 = ++index;
        }
        while ( index < cheat_count );
        active_mini_cheat_count = cheat_count;
        cpu_opcode = opcode;
      }
      if ( (*(uint32_t *)reg_pc & 0xFFF00000) == 0x1F800000 )
        ui_error("out of line\n");
      *(uint32_t *)reg_pc += 4;
      cpu_main_table[opcode >> 26]();
      cpu_gpr[0] = 0;
      if ( (*(uint32_t *)int_reg & int_mask & 0x3FB) != 0 && (cop0_sr & 0x401) == 0x401 )
        irq_cpu_interrupt();
      counter = --hw_update_counter;
      if ( hw_update_counter < 0 )
      {
        spu_update = (((uint8_t)spu_async_update_counter + 1) & 0x1F) == 0;
        hw_update_counter = cpu_speed_scale + counter;
        ++scanline_counter;
        ++spu_async_update_counter;
        if ( spu_update )
          spu_async_update_cb(32 * cpu_speed_scale);
        if ( mdectiming )
          mdec_timer_handler();
        gpu_dma2_interrupt();
        gpu_dma6_interrupt();
        cdr_play_tick();
        cdr_process_delays();
        if ( (int_reg[0] & 4) == 0 && cdr_get_response_status() )
          *(uint32_t *)int_reg |= 4u;
        if ( spu_irq_pending_count && (*(uint16_t *)int_reg & 0x200) == 0 )
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
        rcnt2_inc = cpu_speed_scale;
        rcnt_inc = 512;
        if ( (rcnt_mode[0] & 0x100) == 0 )
          rcnt_inc = cpu_speed_scale;
        rcnt_counter[0] += rcnt_inc;
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
        if ( (rcnt2_mode & 0x200) != 0 )
          rcnt2_inc = (unsigned int)cpu_speed_scale >> 3;
        rcnt2_counter += rcnt2_inc;
        if ( rcnt2_counter >= (unsigned int)rcnt2_compare )
        {
          rcnt2_counter = 0;
          if ( (rcnt2_mode & 0x50) == 0x50 )
            *(uint32_t *)int_reg |= 0x40u;
        }
        scanlines = video_scanlines;
        if ( scanline_counter == video_scanlines - 22 )
        {
          irq = *(uint32_t *)int_reg | 1;
          *(uint32_t *)int_reg |= 1u;
          if ( (int_mask & 0x200) != 0 && forcespu && (frame_counter & 3) == 0 )
            *(uint32_t *)int_reg = irq | 0x200;
        }
        if ( (int_mask & *(uint32_t *)int_reg) != 0 )
          irq_cpu_interrupt();
        if ( scanline_counter >= scanlines )
          break;
      }
    }
    scanline_counter = 0;
    ++frame_counter;
    ++rcnt3_counter;
    gpu_frame_update();
    reset = reset_flag;
    if ( reset_flag )
      break;
    if ( (frame_counter & 0x3F) == 0 )
      cdr_update_motor_status();
    sio_memcard_auto_save();
  }
  return reset;
}
