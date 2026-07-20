#include "pch.h"
void sio_read_data_byte()
{
  if ( sio_transfer_pending && hw_update_counter < (unsigned int)sio_transfer_timeout )
  {
    sio_transfer_pending = 0;
    sio_trigger_rx_ready_irq();
  }
  if ( sio_tx_fifo[259] != (_BYTE)sio_rx_fifo_count && ++sio_tx_fifo[259] == (_BYTE)sio_rx_fifo_count )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFD;
}
