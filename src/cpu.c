#include "pch.h"

uint32_t cpu_opcode;
uint32_t cpu_gpr[32];
uint32_t cpu_HI;
uint32_t cpu_LO;
unsigned char *reg_pc;

int cpu_clear_regs()
{
  *(_DWORD *)reg_pc = 0xBFC00000;
  memset(cpu_gpr, 0, 0x80u);
  memset(cop0_regs, 0, 0x40u);
  hw_update_counter = 0;
  dword_50C360 = 0;
  dword_50C364 = 0;
  cpu_LO = 0;
  cpu_HI = 0;
  return 0;
}

unsigned int cpu_load_bios_shell()
{
  int v0; // ecx
  unsigned int result; // eax
  int v2; // eax

  v0 = *(_DWORD *)reg_pc;
  result = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  for ( cpu_opcode = result; *(_DWORD *)reg_pc != 0x80030000; cpu_opcode = result )
  {
    *(_DWORD *)reg_pc = v0 + 4;
    cpu_main_table[result >> 26]();
    v2 = --hw_update_counter;
    if ( hw_update_counter < 0 )
    {
      hw_update_counter = cpu_speed_scale + v2;
      if ( ++dword_50C364 >= (unsigned int)video_scanlines )
      {
        dword_50C364 = 0;
        ++dword_50C360;
      }
    }
    v0 = *(_DWORD *)reg_pc;
    result = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  }
  return result;
}

int cpu_execute()
{
  unsigned int v0; // esi
  unsigned __int8 v1; // dl
  unsigned __int8 v2; // bl
  int v3; // edi
  int v4; // ecx
  unsigned __int8 v5; // cl
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // eax
  bool v9; // zf
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // ecx
  unsigned int v13; // esi
  int v14; // edx
  int result; // eax
  unsigned __int8 v16; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    while ( 1 )
    {
      v0 = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
      v1 = active_mini_cheat_count;
      cpu_opcode = v0;
      if ( active_mini_cheat_count )
      {
        v2 = 0;
        v16 = 0;
        v3 = *(_DWORD *)reg_pc & 0x1FFFFF;
        do
        {
          v4 = mini_cheat_id_array[2 * v16];
          if ( (v4 & 0x1FFFFF) == v3 )
          {
            v0 = mini_cheat_attr_array[2 * v16];
            if ( (v4 & 0xF0000000) == 0 )
            {
              v5 = v2 + 1;
              if ( (unsigned __int8)(v2 + 1) < v1 )
              {
                v6 = (_DWORD *)(8 * v5 + 5991868);
                v7 = (unsigned __int8)(v1 - v5);
                do
                {
                  *(v6 - 1) = v6[1];
                  *v6 = v6[2];
                  v6 += 2;
                  --v7;
                }
                while ( v7 );
                v2 = v16;
              }
              --v1;
            }
          }
          v16 = ++v2;
        }
        while ( v2 < v1 );
        active_mini_cheat_count = v1;
        cpu_opcode = v0;
      }
      if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0x1F800000 )
        ui_error("out of line\n");
      *(_DWORD *)reg_pc += 4;
      cpu_main_table[v0 >> 26]();
      cpu_gpr[0] = 0;
      if ( (*(_DWORD *)int_reg & int_mask & 0x3FB) != 0 && (dword_50C2A4 & 0x401) == 0x401 )
        irq_cpu_interrupt();
      v8 = --hw_update_counter;
      if ( hw_update_counter < 0 )
      {
        v9 = (((_BYTE)dword_4FC4EC + 1) & 0x1F) == 0;
        hw_update_counter = cpu_speed_scale + v8;
        ++dword_50C364;
        ++dword_4FC4EC;
        if ( v9 )
          spu_async_update_cb(32 * cpu_speed_scale);
        if ( mdectiming )
          mdec_timer_handler();
        gpu_dma2_interrupt();
        gpu_dma6_interrupt();
        cdr_play_tick();
        cdr_process_delays();
        if ( (int_reg[0] & 4) == 0 && cdr_get_response_status() )
          *(_DWORD *)int_reg |= 4u;
        if ( dword_50C210 && (*(_WORD *)int_reg & 0x200) == 0 )
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
        v10 = cpu_speed_scale;
        v11 = 512;
        if ( (dword_50BFD4[0] & 0x100) == 0 )
          v11 = cpu_speed_scale;
        dword_50BFD0[0] += v11;
        if ( dword_50BFD0[0] >= (unsigned int)dword_50BFDC[0] )
        {
          dword_50BFD0[0] = 0;
          if ( (dword_50BFD4[0] & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x10u;
        }
        v12 = 1;
        if ( (dword_50BFE4 & 0x100) == 0 )
          v12 = cpu_speed_scale;
        dword_50BFE0 += v12;
        if ( dword_50BFE0 >= (unsigned int)dword_50BFEC )
        {
          dword_50BFE0 = 0;
          if ( (dword_50BFE4 & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x20u;
        }
        if ( (dword_50BFF4 & 0x200) != 0 )
          v10 = (unsigned int)cpu_speed_scale >> 3;
        dword_50BFF0 += v10;
        if ( dword_50BFF0 >= (unsigned int)dword_50BFFC )
        {
          dword_50BFF0 = 0;
          if ( (dword_50BFF4 & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x40u;
        }
        v13 = video_scanlines;
        if ( dword_50C364 == video_scanlines - 22 )
        {
          v14 = *(_DWORD *)int_reg | 1;
          *(_DWORD *)int_reg |= 1u;
          if ( (int_mask & 0x200) != 0 && forcespu && (dword_50C360 & 3) == 0 )
            *(_DWORD *)int_reg = v14 | 0x200;
        }
        if ( (int_mask & *(_DWORD *)int_reg) != 0 )
          irq_cpu_interrupt();
        if ( dword_50C364 >= v13 )
          break;
      }
    }
    dword_50C364 = 0;
    ++dword_50C360;
    ++dword_50C000;
    gpu_frame_update();
    result = reset_flag;
    if ( reset_flag )
      break;
    if ( (dword_50C360 & 0x3F) == 0 )
      cdr_update_motor_status();
    sio_memcard_auto_save();
  }
  return result;
}

/* Decompiled globals (previously generated in src/_gen) */
unsigned int dword_4FC4EC;
unsigned int dword_4FD868;
unsigned int dword_50BFE0;
unsigned int dword_50BFE4;
unsigned int dword_50BFEC;
unsigned int dword_50BFF0;
unsigned int dword_50C000;
unsigned int dword_50C210;
unsigned int dword_50C360;
unsigned int dword_50C364;
