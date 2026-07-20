#include "pch.h"
__int16 __cdecl sio_read_halfword(int a1)
{
  char v1; // al
  __int16 v2; // bx
  char v3; // al
  __int16 result; // ax

  switch ( a1 )
  {
    case 0x1F801040:
      sio_read_data_byte();
      HIBYTE(v2) = v1;
      sio_read_data_byte();
      LOBYTE(v2) = v3;
      result = v2;
      break;
    case 0x1F801044:
      if ( sio_transfer_pending )
      {
        if ( hw_update_counter < (unsigned int)sio_transfer_timeout )
        {
          sio_transfer_pending = 0;
          sio_trigger_rx_ready_irq();
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
