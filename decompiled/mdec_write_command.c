#include "pch.h"
__int16 __cdecl mdec_write_command(unsigned int a1)
{
  __int16 result; // ax

  *(_DWORD *)mdec_command = a1;
  if ( (a1 & 0xF5FF0000) == 0x30000000 )
    mdec_param_word = (unsigned __int16)a1;
  result = (a1 >> 10) & 0x8000;
  mdec_bit15_flag = result;
  return result;
}
