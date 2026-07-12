#include "pch.h"
int gpu_open()
{
  GPUopen(hOutputWnd);
  gpu_closed = 0;
  sub_40FAB0();
  hDlgInput = (int)hOutputWnd;
  hInst_For_DInput = (int)dword_50AE4C;
  if ( init_direct_input() == 1 )
    dbg_print_no_flush(" * Direct input init ok. \n");
  else
    dbg_print_no_flush(" * Direct input init error. \n");
  return sub_40F010();
}
