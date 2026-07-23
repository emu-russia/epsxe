#include "pch.h"
int sub_42AFD0()
{
  int result; // eax

  result = hw_update_counter;
  if ( hw_update_counter < 0 )
  {
    result = 0;
    hw_update_counter = 0;
LABEL_3:
    *(_DWORD *)dword_4FD874 = cpu_speed_scale + result - 535;
    *(_DWORD *)dword_4FD878 = 0;
    return result;
  }
  if ( (unsigned int)hw_update_counter <= 0x217 )
    goto LABEL_3;
  *(_DWORD *)dword_4FD870 = hw_update_counter - 535;
  *(_DWORD *)dword_4FD878 = 128;
  return hw_update_counter - 535;
}
