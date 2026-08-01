#include "pch.h"
int cdr_get_response_status()
{
  if ( g_cdr_irq_mode == 24 )
    return 0;
  else
    return (unsigned __int8)g_cdr_status_regs[62];
}
