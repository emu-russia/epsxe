#include "pch.h"
void cdr_play_tick()
{
  char v0; // cl

  if ( g_cdr_status_regs[70] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)g_cdr_delay_counter )
    {
      v0 = g_cdr_status_regs[72];
      if ( (g_cdr_status_regs[72] & 4) == 4 )
      {
        if ( g_cdr_status_regs[62] )
        {
          if ( g_cdr_status_regs[62] != 1 )
          {
            if ( (g_cdr_status_regs[72] & 2) != 0 )
              g_cdr_status_regs[63] = 1;
            LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[70] | 0x22;
            g_cdr_status_regs[60] = 1;
          }
        }
        else
        {
          g_cdr_status_regs[62] = 1;
          g_cdr_response_fifo[0] = g_cdr_status_regs[70] | 0x22;
          if ( (g_cdr_status_regs[72] & 2) != 0 )
          {
            g_cdr_response_size = 1;
          }
          else
          {
            g_cdr_response_fifo[1] = 1;
            g_cdr_response_fifo[2] = 0x80;
            if ( report_mode_enabled )
              g_cdr_response_fifo[3] = cdr_bcd_to_hex(g_cdr_cur_msf_pos);
            else
              g_cdr_response_fifo[3] = 0;
            LOBYTE(g_cdr_response_extra) = cdr_bcd_to_hex(BYTE1(g_cdr_cur_msf_pos));
            BYTE1(g_cdr_response_extra) = cdr_bcd_to_hex(BYTE2(g_cdr_cur_msf_pos));
            g_cdr_response_size = 6;
          }
          g_cdr_response_index = 0;
          g_cdr_irq_pending = 1;
          irq_cdrom_assert_int();
          v0 = g_cdr_status_regs[72];
        }
      }
      if ( (v0 & 2) == 2
        && g_cdr_seek_target_msf == (_BYTE)g_cdr_cur_msf_pos
        && word_50BF7B == *(_WORD *)((char *)&g_cdr_cur_msf_pos + 1)
        && loaded_file_type != 3 )
      {
        g_cdr_status_regs[62] = 4;
        g_cdr_response_fifo[0] = 2;
        g_cdr_response_size = 1;
        g_cdr_response_index = 0;
        g_cdr_irq_pending = 1;
        cdrom_stop_cb();
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[65] &= 0x3Fu;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
      }
      word_50BF82 = 0;
      cdr_increment_msf();
    }
  }
  else if ( g_cdr_status_regs[67] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)g_cdr_delay_counter )
    {
      word_50BF82 = 0;
      if ( !g_cdr_retry_count )
      {
        cdr_read_data_sector();
        g_cdr_data_bytes_transferred = (g_cdr_status_regs[72] & 0x20) != 0 ? 12 : 24;
        cdr_increment_msf();
        g_cdr_delay_counter = g_cdr_read_ahead_sectors;
        if ( (g_cdr_xa_buffer[2] & 0xF) != 4 || (g_cdr_status_regs[72] & 0x40) != 0x40 )
        {
          if ( g_cdr_status_regs[62] )
          {
            if ( g_cdr_status_regs[62] == 1 )
              return;
            if ( !g_cdr_status_regs[63] )
            {
              g_cdr_status_regs[63] = 1;
              LOBYTE(g_cdr_primary_response) = 34;
              g_cdr_status_regs[60] = 1;
              ++g_cdr_retry_count;
              return;
            }
          }
          else if ( !g_cdr_status_regs[63] )
          {
            g_cdr_status_regs[62] = 1;
            g_cdr_response_fifo[0] = 34;
            g_cdr_response_size = 1;
            g_cdr_response_index = 0;
            g_cdr_irq_pending = 1;
            irq_cdrom_assert_int();
            ++g_cdr_retry_count;
            return;
          }
          g_cdr_secondary_response_size = 1;
          g_cdr_secondary_response_index = 1;
          LOBYTE(g_cdr_secondary_response) = 34;
          ++g_cdr_retry_count;
        }
      }
    }
  }
}
