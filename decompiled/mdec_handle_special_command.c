#include "pch.h"
int __cdecl mdec_handle_special_command(int a1)
{
  int result; // eax

  if ( a1 == 0x80000000 )
  {
    mdec_in_ptr = mdec_out_addr;
    return mdec_out_addr;
  }
  return result;
}
