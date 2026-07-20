#include "pch.h"
void __cdecl sio_write_data_byte(int a1, char a2)
{
  LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFB;
  sio_tx_fifo_data[(unsigned __int8)--sio_tx_fifo[0]] = a2;
  if ( !sio_tx_fifo[0] )
  {
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFE;
    if ( (sio0_control_reg & 1) != 0 )
    {
      sio_command(sio_tx_fifo_data);
      LOBYTE(sio0_mode_reg) = sio0_mode_reg | 5;
      sio_tx_fifo[0] = sio_tx_fifo[2];
      if ( (sio0_control_reg & 0x400) != 0 )
      {
        BYTE1(sio0_mode_reg) |= 2u;
        sio_assert_int();
      }
    }
  }
}
