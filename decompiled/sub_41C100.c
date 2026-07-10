#include "pch.h"
int __cdecl sub_41C100(FILE *Stream, int a2)
{
  int result; // eax

  fseek(Stream, 0, 2);
  result = ftell(Stream) - 2048;
  if ( a2 != result )
    return dump_log(console_log_handle, " ePSXe: (Demo bugged header) Real: %x Load: %x \n", result, a2);
  return result;
}
