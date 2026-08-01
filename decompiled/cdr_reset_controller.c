#include "pch.h"
char cdr_reset_controller()
{
  g_cdr_response_size = 0;
  g_cdr_status_regs[60] = 0;
  g_cdr_response_index = 0;
  g_cdr_irq_pending = 0;
  g_cdr_status_regs[61] = 0;
  g_cdr_status_regs[62] = 0;
  g_cdr_status_regs[64] = 0;
  g_cdr_status_regs[72] = 0;
  g_cdr_last_lba_read = 0;
  g_cdr_data_bytes_transferred = 0;
  HIBYTE(g_cdr_registers) = 0;
  g_cdr_status_regs[70] = 0;
  g_cdr_dma_active = 0;
  g_cdr_status_regs[68] = 0;
  g_cdr_status_regs[69] = 0;
  g_cdr_param_fifo_count = 0;
  g_cdr_retry_count = 0;
  g_cdr_status_regs[65] = 17;
  g_cdr_status_regs[66] = 2;
  HIBYTE(g_cdr_cur_msf_pos) = 1;
  return cdr_set_nocd(nocd);
}
