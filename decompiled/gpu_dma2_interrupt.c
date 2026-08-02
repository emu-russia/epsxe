#include "pch.h"
char gpu_dma2_interrupt()
{
  char result; // al

  if ( gpu_dma2_state > -2 && gpu_dma2_state != 1 )
    --gpu_dma2_state;
  result = gpu_dma2_delay_counter;
  if ( gpu_dma2_delay_counter <= 0 )
  {
    if ( !gpu_dma2_delay_counter )
    {
      *(_DWORD *)gpu_dma_channel_status &= ~0x1000000u;
      gpu_dma2_delay_counter = -1;
      result = irq_dma_assert_int(2u);
      gpu_dma2_state = -2;
    }
  }
  else
  {
    return --gpu_dma2_delay_counter;
  }
  return result;
}
