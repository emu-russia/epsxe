#include "pch.h"
int sub_42E8E0()
{
  GPUopen(dword_4FD98C);
  gpu_closed = 0;
  sub_40FAB0();
  dword_4F7A60 = (int)dword_4FD98C;
  dword_4F7A58 = (int)dword_50AE4C;
  if ( init_direct_input() == 1 )
    dbg_print_no_flush(aDirectInputIni);
  else
    dbg_print_no_flush(aDirectInputIni_0);
  return sub_40F010();
}
