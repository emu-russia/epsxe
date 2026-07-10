#include "pch.h"
char __cdecl sub_4347A0(
        unsigned int a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        unsigned __int8 *a5,
        unsigned __int8 *a6)
{
  char v6; // bl
  unsigned int v7; // esi
  unsigned __int8 *v8; // ecx
  unsigned __int8 v9; // dl
  unsigned __int8 *v10; // eax
  unsigned int v11; // ecx
  unsigned int v12; // et2
  unsigned __int8 v14; // [esp+10h] [ebp-4h]

  v6 = a1;
  v14 = 0;
  v7 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((unsigned __int8)(a1 & 0xF) % 10 + 10 * ((unsigned __int8)a1 >> 4))))
     + 10 * (a3 >> 4);
  sub_431110(&a1, 8 * (unsigned __int8)byte_4FD9E3 + 5241928);
  if ( a1 > v7 )
  {
    LOBYTE(v10) = byte_4FD9E3;
    if ( byte_4FD9E3 )
    {
      while ( 1 )
      {
        sub_431110(&a1, 8 * v14 + 5241936);
        if ( a1 > v7 )
          break;
        LOBYTE(v10) = ++v14;
        if ( v14 >= (unsigned __int8)byte_4FD9E3 )
          return (char)v10;
      }
      v11 = a1 % 0x4B;
      v12 = a1 / 0x4B % 0x3C;
      *a4 = a1 / 0x4B / 0x3C;
      LOBYTE(v10) = (_BYTE)a5;
      *a5 = v12;
      *a6 = v11;
    }
  }
  else
  {
    v8 = a5;
    v9 = a2;
    *a4 = v6;
    v10 = a6;
    *v8 = v9;
    *v10 = a3;
  }
  return (char)v10;
}
