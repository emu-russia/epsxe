#include "pch.h"
int __cdecl cdr_get_status(int a1)
{
  int result; // eax

  result = a1;
  g_cdr_status_regs[62] = a1;
  g_cdr_response_index = 0;
  g_cdr_response_size = 1;
  if ( a1 == 1 )
    g_cdr_response_fifo[0] = 2;
  return result;
}
