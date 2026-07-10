#include "pch.h"
int (__stdcall *sub_42E3A0())(_DWORD, _DWORD)
{
  int v0; // eax

  v0 = GPUopen(hSaveLoadWnd);
  dbg_print(" * Gpu open[%d]... \n", v0);
  gpu_closed = 0;
  hDlgInput = (int)hSaveLoadWnd;
  hInst_For_DInput = (int)dword_50AE4C;
  if ( init_direct_input() == 1 )
    dbg_print_no_flush(aDirectInputIni);
  else
    dbg_print_no_flush(aDirectInputIni_0);
  sub_40F010();
  return do_GPUfreeze(0);
}
