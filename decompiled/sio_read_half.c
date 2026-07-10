#include "pch.h"
__int16 __cdecl sio_read_half(int a1)
{
  char v1; // al
  __int16 v2; // bx
  char v3; // al
  __int16 result; // ax

  switch ( a1 )
  {
    case 0x1F801040:
      sio_data_read();
      HIBYTE(v2) = v1;
      sio_data_read();
      LOBYTE(v2) = v3;
      result = v2;
      break;
    case 0x1F801044:
      if ( dword_4FD86C )
      {
        if ( dword_50C270 < (unsigned int)dword_4FD864 )
        {
          dword_4FD86C = 0;
          sub_421FD0();
        }
      }
      result = sio0_mode_reg;
      break;
    case 0x1F801048:
      result = HIWORD(sio0_mode_reg);
      break;
    case 0x1F80104A:
      result = sio0_control_reg;
      break;
    case 0x1F80104E:
      result = HIWORD(sio0_control_reg);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}
