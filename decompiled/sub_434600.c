#include "pch.h"
char __cdecl sub_434600(
        unsigned int a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        _BYTE *a5,
        _BYTE *a6,
        _BYTE *a7)
{
  unsigned __int8 v7; // bl
  unsigned int v8; // ebp
  char result; // al
  unsigned int v10; // ecx
  unsigned __int8 v11; // [esp+10h] [ebp-4h]

  v7 = 0;
  v11 = 0;
  v8 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((unsigned __int8)(a1 & 0xF) % 10 + 10 * ((unsigned __int8)a1 >> 4))))
     + 10 * (a3 >> 4)
     - 150;
  sub_431110(&a1, 8 * (unsigned __int8)byte_4FD9E3 + 5241928);
  if ( a1 > v8 && byte_4FD9E3 )
  {
    while ( 1 )
    {
      sub_431110(&a1, 8 * v11 + 5241936);
      if ( v11 + 1 < (unsigned __int8)byte_4FD9E3 )
        a1 -= a1 % 0x4B;
      if ( a1 > v8 )
        break;
      v11 = ++v7;
      if ( v7 >= (unsigned __int8)byte_4FD9E3 )
        goto LABEL_7;
    }
    sub_431110(&a1, 8 * v11 + 5241928);
    v10 = v8 + a1 % 0x4B - a1;
    *a4 = (v11 + 1) % 10 + 16 * ((v11 + 1) / 10);
    *a5 = v10 / 0x4B / 0x3C % 0xA + 16 * (v10 / 0x4B / 0x3C / 0xA);
    *a6 = v10 / 0x4B % 0x3C % 0xA + 16 * (v10 / 0x4B % 0x3C / 0xA);
    result = v10 % 0x4B % 0xA + 16 * (v10 % 0x4B / 0xA);
    *a7 = result;
  }
  else
  {
LABEL_7:
    result = (char)a4;
    *a4 = -86;
  }
  return result;
}
