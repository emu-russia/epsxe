#include "pch.h"
char sub_437040()
{
  char result; // al

  result = console_log_flush_pending;
  if ( console_log_flush_pending )
    console_log_flush_pending = 0;
  return result;
}
