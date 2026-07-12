#include "pch.h"
unsigned __int8 __cdecl sub_4337F0(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 *a4,
        unsigned __int8 *a5,
        unsigned __int8 *a6)
{
  unsigned __int8 v6; // bl
  unsigned int v7; // esi
  unsigned __int8 result; // al
  unsigned int v9; // ecx
  unsigned int v10; // et2
  unsigned int v11; // [esp+10h] [ebp-8h] BYREF
  int v12; // [esp+14h] [ebp-4h]

  v6 = 0;
  LOBYTE(v12) = 0;
  v7 = (a3 & 0xF) % 10
     + 75 * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) % 10 + 10 * (a1 >> 4))))
     + 10 * (a3 >> 4);
  sub_431110(&v11, (unsigned __int8 *)(8 * (unsigned __int8)dword_4FD9BC + 5262504));
  if ( v11 > v7 )
  {
    result = dword_4FD9BC;
    if ( (_BYTE)dword_4FD9BC )
    {
      while ( 1 )
      {
        sub_431110(&v11, (unsigned __int8 *)(8 * (unsigned __int8)v12 + 5262512));
        if ( v11 > v7 )
          break;
        result = dword_4FD9BC;
        LOBYTE(v12) = ++v6;
        if ( v6 >= (unsigned __int8)dword_4FD9BC )
          return result;
      }
      v9 = v11 % 0x4B;
      v10 = v11 / 0x4B % 0x3C;
      *a4 = v11 / 0x4B / 0x3C;
      *a5 = v10;
      *a6 = v9;
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
