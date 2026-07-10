#include "pch.h"
void __cdecl sub_41C100(FILE *Stream, int a2)
{
  int v2; // eax

  fseek(Stream, 0, 2);
  v2 = ftell(Stream) - 2048;
  if ( a2 != v2 )
    dump_log(console_log_handle, " ePSXe: (Demo bugged header) Real: %x Load: %x \n", v2, a2);
}
