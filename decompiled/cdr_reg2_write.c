#include "pch.h"
char __cdecl cdr_reg2_write(char a1)
{
  char result; // al

  result = g_cdr_param_fifo_count;
  if ( !g_cdr_param_fifo_count )
  {
    result = g_cdr_status_regs[64];
    if ( g_cdr_status_regs[64] == 2 )
    {
      if ( a1 == 7 && g_cdr_status_regs[61] )
      {
        g_cdr_irq_pending = 1;
        g_cdr_status_regs[61] = 0;
        g_cdr_status_regs[64] = 0;
        return result;
      }
      goto LABEL_7;
    }
    if ( g_cdr_status_regs[64] )
    {
LABEL_7:
      g_cdr_irq_mode = a1;
      g_cdr_status_regs[64] = 0;
      return result;
    }
    result = g_cdr_status_regs[61];
    *((_BYTE *)&g_cdr_param_fifo + (unsigned __int8)g_cdr_status_regs[61]++) = a1;
    g_cdr_status_regs[64] = 0;
  }
  return result;
}
