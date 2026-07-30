#include "pch.h"
char check_and_clear_console_log_flush_pending()
{
  char result; // al

  result = console_log_flush_pending;
  if ( console_log_flush_pending )
    console_log_flush_pending = 0;
  return result;
}
