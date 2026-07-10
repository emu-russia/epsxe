#include "pch.h"
char reopen_console_log()
{
  FILE *v0; // eax

  LOBYTE(v0) = byte_4FF9F2;
  if ( byte_4FF9F2 )
  {
    LOBYTE(v0) = (_BYTE)console_log_handle;
    if ( !console_log_handle )
    {
      v0 = fopen(aConsoleLog, aW);
      console_log_handle = v0;
    }
  }
  return (char)v0;
}
