#include "pch.h"
char cdr_process_delays()
{
  char result; // al

  result = g_cdr_status_regs[62];
  if ( !g_cdr_status_regs[62] && (g_cdr_status_regs[63] || (result = g_cdr_secondary_response_size) != 0) )
  {
    result = ++word_4FD87C;
    if ( (unsigned __int16)word_4FD87C >= (unsigned __int16)word_455FA6 )
    {
      cdr_queue_response();
      result = 10;
      word_4FD87C = 0;
      if ( (unsigned __int16)word_455FA6 > 0xAu )
        word_455FA6 = 10;
    }
  }
  return result;
}
