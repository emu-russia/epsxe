#include "pch.h"
int __cdecl cont_set_default(unsigned __int8 a1)
{
  int result; // eax

  if ( a1 == 1 )
  {
    word_455FC8[0] = 203;
    word_455FCA = 205;
    word_455FCC = 200;
    word_455FCE = 208;
    word_455FD0 = 32;
    word_455FD2 = 45;
    word_455FD4 = 44;
    word_455FD6 = 31;
    word_455FD8 = 17;
    word_455FDA = 18;
    word_455FDC = 19;
    word_455FDE = 20;
    word_455FE0 = 47;
    word_455FE2 = 46;
    word_455FE4 = 16;
    word_455FE6 = 21;
  }
  else if ( a1 > 1u && a1 < 4u )
  {
    memset(&word_455FA8[16 * a1], 0, 0x20u);
    return 0;
  }
  return result;
}
