#include "pch.h"
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
    return (char *)recomp_code_base + v0;
  }
  else
  {
    if ( (++dword_4FC4EC & 0x1F) == 0 )
      spu_async_update_cb(32 * cpu_speed_scale);
    mdec_timer_handler();
    gpu_sub_42E450();
    gpu_sub_42E650();
    hw_update_counter = cpu_speed_scale;
    ++dword_50C364;
    cdr_play_tick();
    cdr_process_delays();
    if ( (int_reg[0] & 4) == 0 && cdr_get_response_status() )
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
    v2 = cpu_speed_scale;
    v3 = 512;
    if ( (dword_50BFD4[0] & 0x100) == 0 )
      v3 = cpu_speed_scale;
    dword_50BFD0[0] += v3;
    if ( dword_50BFD0[0] >= (unsigned int)dword_50BFDC[0] )
    {
      dword_50BFD0[0] = 0;
      if ( (dword_50BFD4[0] & 0x50) == 0x50 )
        *(_DWORD *)int_reg |= 0x10u;
    }
    v4 = 1;
    if ( (dword_50BFE4 & 0x100) == 0 )
      v4 = cpu_speed_scale;
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
        v2 = (unsigned int)cpu_speed_scale >> 3;
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
        **(_DWORD **)((char *)recomp_code_base + v8) = 195;
      }
      if ( byte_4FC4E4 )
      {
        byte_4FC4E4 = 0;
        dynarec_invalidate();
      }
      if ( (dword_50C360 & 0x3F) == 0 )
        cdr_update_motor_status();
      sio_memcard_auto_save();
    }
    if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0xBFC00000 )
      v9 = (*(_DWORD *)reg_pc & 0x7FFFF) + 0x200000;
    else
      v9 = *(_DWORD *)reg_pc & 0x1FFFFF;
    return (char *)recomp_code_base + v9;
  }
}
