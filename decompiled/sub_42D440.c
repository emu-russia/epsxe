#include "pch.h"
_BYTE *__cdecl sub_42D440(char a1, _BYTE *a2)
{
  _BYTE *result; // eax
  __int16 v3; // ax
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // eax

  if ( a1 )
  {
    result = a2;
    a2[7] = 0;
    a2[6] = 0;
    a2[5] = 0;
    a2[4] = -1;
    a2[3] = -1;
    a2[2] = 90;
    *a2 = 0;
    if ( a1 == 1 )
    {
      a2[1] = -1;
      a2[8] = -1;
    }
    else
    {
      a2[8] = 0;
      a2[1] = 99;
    }
  }
  else
  {
    *a2 = 0;
    a2[1] = 99;
    a2[2] = 90;
    *(_WORD *)(a2 + 3) = -1;
    a2[8] = 0;
    a2[7] = 0;
    a2[6] = 0;
    a2[5] = 0;
    v3 = dword_4FD8F4 / 2 + HIWORD(dword_4FD980);
    LOWORD(dword_4FD980) = dword_4FD8F0 / 2 + dword_4FD980;
    HIWORD(dword_4FD980) = v3;
    if ( (__int16)dword_4FD980 <= 511 )
    {
      if ( (dword_4FD980 & 0x8000u) != 0 )
        LOWORD(dword_4FD980) = 0;
    }
    else
    {
      LOWORD(dword_4FD980) = 511;
    }
    if ( v3 <= 255 )
    {
      if ( v3 < 0 )
        HIWORD(dword_4FD980) = 0;
    }
    else
    {
      HIWORD(dword_4FD980) = 255;
    }
    if ( (dword_50AB60 & 1) != 0 )
      a2[4] &= ~0x20u;
    if ( (dword_50AB60 & 2) != 0 )
      a2[3] &= ~8u;
    if ( (dword_50AB60 & 4) != 0 )
      a2[4] &= ~0x40u;
    *(_WORD *)(a2 + 5) = dword_4FD980;
    a2[7] = BYTE2(dword_4FD980);
    if ( (dword_4FD980 & 0x100) != 0 )
    {
      v4 = (__int16)dword_4FD980 + ((__int16)dword_4FD980 - 255) / 2;
      v5 = SHIWORD(dword_4FD980) - 40;
      if ( v4 <= 511 )
      {
        if ( v4 < 0 )
          v4 = 0;
      }
      else
      {
        v4 = 511;
      }
      if ( v5 <= 255 )
      {
        if ( v5 < 0 )
          v5 = 0;
        return gpu_cursor(0, v4, v5);
      }
      else
      {
        return gpu_cursor(0, v4, 255);
      }
    }
    else
    {
      v6 = (__int16)dword_4FD980 - (255 - (__int16)dword_4FD980) / 2;
      v7 = SHIWORD(dword_4FD980) - 40;
      if ( v6 <= 511 )
      {
        if ( v6 < 0 )
          v6 = 0;
      }
      else
      {
        v6 = 511;
      }
      if ( v7 <= 255 )
      {
        if ( v7 < 0 )
          v7 = 0;
        return gpu_cursor(0, v6, v7);
      }
      else
      {
        return gpu_cursor(0, v6, 255);
      }
    }
  }
  return result;
}
