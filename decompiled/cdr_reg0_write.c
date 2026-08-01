#include "pch.h"
char __cdecl cdr_reg0_write(char a1)
{
  char result; // al

  result = g_cdr_param_fifo_count;
  if ( !g_cdr_param_fifo_count )
  {
    result = a1 - 1;
    if ( a1 == 1 )
    {
      g_cdr_irq_pending = 1;
    }
    else
    {
      result = a1 - 2;
      if ( a1 == 2 )
      {
        g_cdr_param_fifo_count = 1;
        g_cdr_status_regs[64] = a1 & 1;
        return result;
      }
    }
    g_cdr_status_regs[64] = a1 & 1;
  }
  return result;
}
