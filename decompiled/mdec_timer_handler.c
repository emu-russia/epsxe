#include "pch.h"
char mdec_timer_handler()
{
  char result; // al

  result = mdectiming;
  if ( mdectiming )
  {
    result = mdec_timer;
    if ( mdec_timer <= 0 )
    {
      if ( !mdec_timer )
      {
        mdec_status = 0;
        mdec_dma_status &= ~0x1000000u;
        mdec_timer = -1;
        irq_dma_assert_int(1u);
        result = mdec_timer;
      }
    }
    else
    {
      result = --mdec_timer;
    }
    if ( result < 0 )
    {
      if ( result <= -10 )
        mdec_timer_count = 0;
      else
        mdec_timer = --result;
    }
  }
  return result;
}
