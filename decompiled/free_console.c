#include "pch.h"
char free_console()
{
  char result; // al

  result = console_allocated;
  if ( console_allocated )
    return FreeConsole();
  return result;
}
