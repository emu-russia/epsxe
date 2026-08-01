#include "pch.h"
void cdr_queue_response()
{
  if ( g_cdr_status_regs[63] )
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
  }
  if ( g_cdr_secondary_response_size )
  {
    if ( g_cdr_secondary_response_index )
    {
      qmemcpy(&g_cdr_primary_response, &g_cdr_secondary_response, (unsigned __int8)g_cdr_secondary_response_index);
      g_cdr_status_regs[60] = g_cdr_secondary_response_index;
      g_cdr_secondary_response_index = 0;
    }
    g_cdr_status_regs[63] = g_cdr_secondary_response_size;
    g_cdr_secondary_response_size = 0;
  }
}
