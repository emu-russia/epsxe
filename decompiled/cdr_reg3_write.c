#include "pch.h"
void __cdecl cdr_reg3_write(char a1)
{
  if ( g_cdr_param_fifo_count )
  {
    if ( a1 == 32 )
      g_cdr_param_fifo_count = 0;
  }
  else
  {
    g_cdr_status_regs[65] |= 0x40u;
    if ( g_cdr_status_regs[64] != 1 || (g_cdr_status_regs[64] = 2, a1 != 7) )
      g_cdr_status_regs[64] = 0;
    if ( g_cdr_irq_pending && a1 == 7 )
    {
      if ( g_cdr_status_regs[62] == 1 && g_cdr_retry_count )
        --g_cdr_retry_count;
      g_cdr_status_regs[62] = 0;
      if ( (unsigned __int8)g_cdr_response_index >= (unsigned __int8)g_cdr_response_size && g_cdr_status_regs[63] )
      {
        if ( g_cdr_status_regs[60] )
        {
          qmemcpy(g_cdr_response_fifo, &g_cdr_primary_response, (unsigned __int8)g_cdr_status_regs[60]);
          g_cdr_response_size = g_cdr_status_regs[60];
          g_cdr_response_index = 0;
          g_cdr_status_regs[60] = 0;
          g_cdr_irq_pending = 1;
        }
        g_cdr_status_regs[62] = g_cdr_status_regs[63];
        g_cdr_status_regs[63] = 0;
        if ( g_cdr_irq_mode != 24 )
          irq_cdrom_assert_int();
        if ( g_cdr_secondary_response_size )
        {
          if ( g_cdr_secondary_response_index )
          {
            qmemcpy(&g_cdr_primary_response, &g_cdr_secondary_response, (unsigned __int8)g_cdr_secondary_response_index);
            g_cdr_status_regs[60] = g_cdr_secondary_response_index;
            g_cdr_irq_pending = 1;
            g_cdr_secondary_response_index = 0;
          }
          g_cdr_status_regs[63] = g_cdr_secondary_response_size;
          g_cdr_secondary_response_size = 0;
        }
      }
    }
  }
}
