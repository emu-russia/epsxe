#include "pch.h"
unsigned int __cdecl W2k_track_to_msf(int a1, _BYTE *a2, _BYTE *a3, _BYTE *a4)
{
  unsigned int result; // eax
  unsigned int v5; // eax
  unsigned int v6; // et2

  result = (unsigned __int8)byte_4FD9E3;
  if ( (__int16)a1 <= (int)(unsigned __int8)byte_4FD9E3 )
  {
    if ( (_WORD)a1 )
      W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * (__int16)a1 + 5241920));
    else
      W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * (unsigned __int8)byte_4FD9E3 + 5241928));
    v5 = (a1 + 150) / 0x4Bu;
    *a4 = (a1 + 150) % 0x4Bu;
    v6 = v5 % 0x3C;
    result = v5 / 0x3C;
    *a3 = v6;
    *a2 = result;
  }
  return result;
}
