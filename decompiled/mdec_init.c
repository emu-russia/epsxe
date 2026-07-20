#include "pch.h"
int mdec_init()
{
  *(_DWORD *)mdec_command = 0;
  mdec_param_count = 0;
  mdec_timer_count = 0;
  mdec_out_addr = 0;
  mdec_in_ptr = 0;
  mdec_status = 0;
  mdec_timer = -1;
  mdec_param_word = 0;
  mdec_bit15_flag = 0;
  mdec_init_pointers();
  return mdec_init_color_tables();
}
