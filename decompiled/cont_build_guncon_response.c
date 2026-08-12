#include "pch.h"
_BYTE *__cdecl cont_build_guncon_response(char a1, _BYTE *a2)
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
    v3 = mouse_delta_y / 2 + HIWORD(guncon_position);
    LOWORD(guncon_position) = mouse_delta_x / 2 + guncon_position;
    HIWORD(guncon_position) = v3;
    if ( (__int16)guncon_position <= 511 )
    {
      if ( (guncon_position & 0x8000u) != 0 )
        LOWORD(guncon_position) = 0;
    }
    else
    {
      LOWORD(guncon_position) = 511;
    }
    if ( v3 <= 255 )
    {
      if ( v3 < 0 )
        HIWORD(guncon_position) = 0;
    }
    else
    {
      HIWORD(guncon_position) = 255;
    }
    if ( (mouse_buttons_state & 1) != 0 )
      a2[4] &= ~0x20u;
    if ( (mouse_buttons_state & 2) != 0 )
      a2[3] &= ~8u;
    if ( (mouse_buttons_state & 4) != 0 )
      a2[4] &= ~0x40u;
    *(_WORD *)(a2 + 5) = guncon_position;
    a2[7] = BYTE2(guncon_position);
    if ( (guncon_position & 0x100) != 0 )
    {
      v4 = (__int16)guncon_position + ((__int16)guncon_position - 255) / 2;
      v5 = SHIWORD(guncon_position) - 40;
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
      v6 = (__int16)guncon_position - (255 - (__int16)guncon_position) / 2;
      v7 = SHIWORD(guncon_position) - 40;
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
