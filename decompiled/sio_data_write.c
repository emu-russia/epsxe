#include "pch.h"
char __cdecl sub_421F50(int a1, char a2)
{
  char result; // al

  LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFB;
  LOBYTE(byte_52670C) = byte_52670C - 1;
  byte_52660C[(unsigned __int8)byte_52670C] = a2;
  result = byte_52670C;
  if ( !(_BYTE)byte_52670C )
  {
    result = sio0_control_reg;
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFE;
    if ( (sio0_control_reg & 1) != 0 )
    {
      sio_command(byte_52660C);
      result = sio0_control_reg;
      LOBYTE(sio0_mode_reg) = sio0_mode_reg | 5;
      LOBYTE(byte_52670C) = BYTE2(byte_52670C);
      if ( (sio0_control_reg & 0x400) != 0 )
      {
        BYTE1(sio0_mode_reg) |= 2u;
        return sio_assert_int();
      }
    }
  }
  return result;
}
