#include "pch.h"
int __cdecl cont_set_default(unsigned __int8 a1)
{
  int result; // eax

  if ( a1 == 1 )
  {
    Keys1[0] = 203;
    Keys1[1] = 205;
    Keys1[2] = 200;
    Keys1[3] = 208;
    Keys1[4] = 32;
    Keys1[5] = 45;
    Keys1[6] = 44;
    Keys1[7] = 31;
    Keys1[8] = 17;
    Keys1[9] = 18;
    Keys1[10] = 19;
    Keys1[11] = 20;
    Keys1[12] = 47;
    Keys1[13] = 46;
    Keys1[14] = 16;
    Keys1[15] = 21;
  }
  else if ( a1 > 1u && a1 < 4u )
  {
    memset(&word_455FA8[16 * a1], 0, 0x20u);
    return 0;
  }
  return result;
}
