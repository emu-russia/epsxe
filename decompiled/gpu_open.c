#include "pch.h"
int gpu_open()
{
  GPUopen(hSaveLoadWnd);
  gpu_closed = 0;
  sub_40FAB0();
  hDlgInput = (int)hSaveLoadWnd;
  hInst_For_DInput = (int)dword_50AE4C;
  if ( init_direct_input() == 1 )
    dbg_print_no_flush(aDirectInputIni);
  else
    dbg_print_no_flush(aDirectInputIni_0);
  return sub_40F010();
}
