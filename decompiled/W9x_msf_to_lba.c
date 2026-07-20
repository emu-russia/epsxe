#include "pch.h"
char __cdecl W9x_msf_to_lba(
        unsigned int a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        _BYTE *a5,
        _BYTE *a6,
        _BYTE *a7)
{
  char v7; // bl
  int v8; // ebp
  unsigned int v9; // edi
  char result; // al
  unsigned int v11; // ecx
  unsigned __int8 v12; // [esp+10h] [ebp-4h]

  v12 = 0;
  v7 = dword_4FD9BC;
  v8 = (unsigned __int8)dword_4FD9BC;
  v9 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((unsigned __int8)(a1 & 0xF) % 10 + 10 * ((unsigned __int8)a1 >> 4))))
     + 10 * (a3 >> 4)
     - 150;
  W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * (unsigned __int8)dword_4FD9BC + 5262504));
  result = a1;
  if ( a1 > v9 )
  {
    if ( v7 )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * v12 + 5262512));
        if ( v12 + 1 < v8 )
          a1 -= a1 % 0x4B;
        if ( a1 > v9 )
          break;
        if ( ++v12 >= (unsigned __int8)dword_4FD9BC )
          goto LABEL_8;
      }
      W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * v12 + 5262504));
      v11 = v9 + a1 % 0x4B - a1;
      *a4 = (v12 + 1) % 10 + 16 * ((v12 + 1) / 10);
      *a5 = v11 / 0x4B / 0x3C % 0xA + 16 * (v11 / 0x4B / 0x3C / 0xA);
      *a6 = v11 / 0x4B % 0x3C % 0xA + 16 * (v11 / 0x4B % 0x3C / 0xA);
      result = v11 % 0x4B % 0xA + 16 * (v11 % 0x4B / 0xA);
      *a7 = result;
    }
    else
    {
LABEL_8:
      result = (char)a4;
      *a4 = -86;
    }
  }
  else
  {
    *a4 = -86;
  }
  return result;
}
