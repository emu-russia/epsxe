#include "pch.h"
int __cdecl sio_read_word(int a1)
{
  char v2; // al
  unsigned __int16 v3; // bx
  char v4; // al
  unsigned __int8 v5; // al
  int v6; // ebx
  unsigned __int8 v7; // al

  if ( a1 == 0x1F801040 )
  {
    sio_read_data_byte();
    HIBYTE(v3) = v2;
    sio_read_data_byte();
    LOBYTE(v3) = v4;
    sio_read_data_byte();
    v6 = (v5 | (v3 << 8)) << 8;
    sio_read_data_byte();
    return v6 | v7;
  }
  else if ( a1 == 0x1F801044 )
  {
    if ( sio_transfer_pending )
    {
      if ( hw_update_counter < (unsigned int)sio_transfer_timeout )
      {
        sio_transfer_pending = 0;
        sio_trigger_rx_ready_irq();
      }
    }
    return (unsigned __int16)sio0_mode_reg;
  }
  else
  {
    return 0;
  }
}
