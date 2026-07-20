#include "pch.h"
void sio_trigger_rx_ready_irq()
{
  LOWORD(sio0_mode_reg) = sio0_mode_reg | 0x202;
}
