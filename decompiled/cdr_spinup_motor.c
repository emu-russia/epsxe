#include "pch.h"
void cdr_spinup_motor()
{
  g_cdr_status_regs[68] = 0;
  g_cdr_status_regs[69] = 2;
  g_cdr_last_lba_read = 0;
  if ( g_cdr_status_regs[62] )
  {
    g_cdr_status_regs[63] = 2;
    LOBYTE(g_cdr_primary_response) = 16;
    g_cdr_status_regs[60] = 1;
  }
  else
  {
    g_cdr_status_regs[62] = 2;
    g_cdr_response_fifo[0] = 16;
    g_cdr_response_size = 1;
    g_cdr_response_index = 0;
    g_cdr_irq_pending = 1;
    irq_cdrom_assert_int();
  }
}
