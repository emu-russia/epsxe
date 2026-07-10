#include "pch.h"
void __cdecl sio_data_write(int a1, char a2)
{
  LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFB;
  byte_52660C[(unsigned __int8)--byte_52670C[0]] = a2;
  if ( !byte_52670C[0] )
  {
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFE;
    if ( (sio0_control_reg & 1) != 0 )
    {
      sio_command(byte_52660C);
      LOBYTE(sio0_mode_reg) = sio0_mode_reg | 5;
      byte_52670C[0] = byte_52670C[2];
      if ( (sio0_control_reg & 0x400) != 0 )
      {
        BYTE1(sio0_mode_reg) |= 2u;
        sio_assert_int();
      }
    }
  }
}
