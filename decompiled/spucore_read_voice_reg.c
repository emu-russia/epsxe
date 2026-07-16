#include "pch.h"
__int16 __cdecl spucore_read_voice_reg(int a1, int a2)
{
  int v2; // eax
  int v3; // ecx
  int *v4; // eax

  switch ( a2 )
  {
    case 4:
      LOWORD(v2) = (__int64)(*(float *)&dword_4655B0[74 * a1] * 4096.0) & 0x3FFF;
      break;
    case 6:
      LOWORD(v2) = dword_465574[74 * a1];
      break;
    case 12:
      if ( byte_4F75AA )
      {
        LOWORD(v2) = rand() & 1;
      }
      else
      {
        v3 = dword_46559C[74 * a1];
        v4 = &dword_46559C[74 * a1];
        if ( v3 <= 0xFFFFFF )
        {
          if ( v3 < 0 )
            *v4 = 0;
          return *v4 >> 9;
        }
        else
        {
          *v4 = 0xFFFFFF;
          return *v4 >> 9;
        }
      }
      break;
    default:
      LOWORD(v2) = 0;
      break;
  }
  return v2;
}
