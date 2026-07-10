#include "pch.h"
char __cdecl sub_430820(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        _BYTE *a5,
        _BYTE *a6,
        _BYTE *a7)
{
  unsigned int v7; // ebp
  unsigned __int8 v8; // dl
  int v9; // eax
  unsigned int v10; // edi
  unsigned int v11; // esi
  unsigned __int8 v13; // [esp+Ch] [ebp-4h]

  v7 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4) + (a3 & 0xF) - 150;
  v8 = HIBYTE(word_505540);
  v13 = 0;
  v9 = (unsigned __int8)byte_505544[3 * HIBYTE(word_505540)];
  if ( 75
     * ((unsigned __int8)byte_505543[3 * HIBYTE(word_505540)]
      + 60 * (unsigned int)(unsigned __int8)byte_505542[3 * HIBYTE(word_505540)])
     + v9
     - 150 > v7 )
  {
    if ( HIBYTE(word_505540) )
    {
      while ( 1 )
      {
        v10 = 75 * ((unsigned __int8)byte_505546[3 * v13] + 60 * (unsigned __int8)byte_505545[3 * v13])
            + (unsigned __int8)byte_505547[3 * v13]
            - 150;
        if ( v13 + 1 < HIBYTE(word_505540) )
        {
          v10 -= v10 % 0x4B;
          v8 = HIBYTE(word_505540);
        }
        if ( v10 > v7 )
          break;
        if ( ++v13 >= v8 )
          goto LABEL_8;
      }
      v11 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4))))
          + 10 * (a3 >> 4)
          + (a3 & 0xF)
          + (75 * ((unsigned __int8)byte_505543[3 * v13] + 60 * (unsigned __int8)byte_505542[3 * v13])
           + (unsigned int)(unsigned __int8)byte_505544[3 * v13]
           - 150)
          % 0x4B
          - (75 * ((unsigned __int8)byte_505543[3 * v13] + 60 * (unsigned __int8)byte_505542[3 * v13])
           + (unsigned __int8)byte_505544[3 * v13]);
      *a4 = (v13 + 1) % 10 + 16 * ((v13 + 1) / 10);
      *a5 = v11 / 0x4B / 0x3C % 0xA + 16 * (v11 / 0x4B / 0x3C / 0xA);
      *a6 = v11 / 0x4B % 0x3C % 0xA + 16 * (v11 / 0x4B % 0x3C / 0xA);
      LOBYTE(v9) = v11 % 0x4B % 0xA + 16 * (v11 % 0x4B / 0xA);
      *a7 = v9;
    }
    else
    {
LABEL_8:
      *a4 = -86;
      LOBYTE(v9) = (_BYTE)a4;
    }
  }
  else
  {
    *a4 = -86;
  }
  return v9;
}
