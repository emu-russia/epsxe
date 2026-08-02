#include "pch.h"
char gpu_dma6_interrupt()
{
  char result; // al

  result = gpu_dma6_delay_counter;
  if ( gpu_dma6_delay_counter <= 0 )
  {
    if ( !gpu_dma6_delay_counter )
    {
      *(_DWORD *)gpu_dma6_status &= ~0x1000000u;
      gpu_dma6_delay_counter = -1;
      return irq_dma_assert_int(6u);
    }
  }
  else
  {
    return --gpu_dma6_delay_counter;
  }
  return result;
}
