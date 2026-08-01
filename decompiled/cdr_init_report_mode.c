#include "pch.h"
__int16 cdr_init_report_mode()
{
  __int16 result; // ax

  g_cdr_irq_enabled = 1;
  word_50BF82 = 0;
  g_cdr_spindown_counter = 0;
  g_cdr_dma_active = 0;
  if ( country_setting == 1 )
    LOBYTE(result) = g_cdr_status_regs[72] < 0 ? 104 : -48;
  else
    LOBYTE(result) = g_cdr_status_regs[72] < 0 ? 104 : -47;
  g_cdr_region_code = result;
  result = (unsigned __int8)result;
  g_cdr_read_ahead_sectors = result;
  g_cdr_delay_counter = (unsigned __int8)result;
  if ( !g_cdr_status_regs[70] )
  {
    result = 3 * (unsigned __int8)result;
    g_cdr_delay_counter = result;
  }
  return result;
}
