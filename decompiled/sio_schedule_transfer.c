#include "pch.h"
char __cdecl sio_schedule_transfer(char a1, char *a2)
{
  int v2; // eax

  LOBYTE(v2) = a1;
  if ( !a1 )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg | 2;
  sio_tx_fifo[(unsigned __int8)sio_rx_fifo_count + 3] = *a2;
  LOBYTE(sio_rx_fifo_count) = sio_rx_fifo_count + 1;
  if ( a1 )
  {
    LOBYTE(v2) = sio0_control_reg;
    if ( (sio0_control_reg & 0x1000) != 0 )
    {
      sub_42AFD0();
      v2 = hw_update_counter;
      if ( hw_update_counter >= 0 )
      {
        if ( (unsigned int)hw_update_counter > 0x1F9 )
        {
          sio_transfer_timeout = hw_update_counter - 505;
          sio_transfer_pending = 128;
          LOBYTE(v2) = hw_update_counter + 7;
          return v2;
        }
      }
      else
      {
        v2 = 0;
        hw_update_counter = 0;
      }
      dword_4FD868 = cpu_speed_scale + v2 - 505;
      sio_transfer_pending = 0;
    }
  }
  return v2;
}
