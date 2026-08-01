#include "pch.h"
char cdr_update_motor_status()
{
  char result; // al

  result = g_cdr_status_regs[69];
  if ( g_cdr_status_regs[69] == 1 )
  {
    g_cdr_status_regs[68] = 1;
    g_cdr_status_regs[69] = 0;
    return 0;
  }
  else if ( g_cdr_status_regs[69] )
  {
    return --g_cdr_status_regs[69];
  }
  return result;
}
