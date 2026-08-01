#include "pch.h"
int (__stdcall *sio_reset_all())(_DWORD)
{
  sio0_mode_reg = 5;
  sio0_control_reg = 0;
  sio_tx_fifo[0] = 0;
  sio_tx_fifo[1] = 0;
  sio_tx_fifo[2] = 1;
  sio_tx_fifo[259] = 0;
  LOBYTE(sio_rx_fifo_count) = 0;
  sio_reset_controller_state();
  sio_memcard_load();
  return cont_update_led_and_mode(0);
}
