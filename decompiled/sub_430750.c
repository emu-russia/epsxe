#include "pch.h"
char __cdecl sub_430750(char a1, char a2)
{
  unsigned __int8 v3; // [esp+4h] [ebp-4h]

  v3 = 0;
  if ( !HIBYTE(word_505540) )
    return 0;
  while ( a1 != byte_505542[3 * v3] || a2 != byte_505543[3 * v3] )
  {
    if ( ++v3 >= HIBYTE(word_505540) )
      return 0;
  }
  return byte_505544[3 * v3];
}
