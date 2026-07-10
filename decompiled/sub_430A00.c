#include "pch.h"
unsigned __int8 __cdecl sub_430A00(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 *a4,
        unsigned __int8 *a5,
        unsigned __int8 *a6)
{
  unsigned __int8 v6; // bl
  unsigned int v7; // ecx
  unsigned __int8 result; // al
  unsigned int v9; // eax
  unsigned __int8 v10; // [esp+8h] [ebp-8h]

  v6 = 0;
  v7 = (a3 & 0xF) + 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4);
  v10 = 0;
  if ( 75
     * ((unsigned __int8)byte_505543[3 * HIBYTE(word_505540)]
      + 60 * (unsigned __int8)byte_505542[3 * HIBYTE(word_505540)])
     + (unsigned int)(unsigned __int8)byte_505544[3 * HIBYTE(word_505540)]
     - 150 > v7 )
  {
    result = HIBYTE(word_505540);
    if ( HIBYTE(word_505540) )
    {
      while ( 1 )
      {
        v9 = 75 * ((unsigned __int8)byte_505546[3 * v10] + 60 * (unsigned __int8)byte_505545[3 * v10])
           + (unsigned __int8)byte_505547[3 * v10]
           - 150;
        if ( v9 > v7 )
          break;
        result = HIBYTE(word_505540);
        v10 = ++v6;
        if ( v6 >= HIBYTE(word_505540) )
          return result;
      }
      *a4 = v9 / 0x4B / 0x3C;
      *a5 = v9 / 0x4B % 0x3C;
      *a6 = v9 % 0x4B;
      return (unsigned __int8)a5;
    }
  }
  else
  {
    *a4 = a1;
    *a5 = a2;
    *a6 = a3;
    return a2;
  }
  return result;
}
