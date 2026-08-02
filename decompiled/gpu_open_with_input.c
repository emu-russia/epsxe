#include "pch.h"
int (__stdcall *gpu_open_with_input())(_DWORD, _DWORD)
{
  int v0; // eax

  v0 = GPUopen(hOutputWnd);
  dbg_print(" * Gpu open[%d]... \n", v0);
  gpu_closed = 0;
  hDlgInput = (int)hOutputWnd;
  hInst_For_DInput = (int)gpu_hInstance;
  if ( diInitDirectInput() == 1 )
    dbg_print_no_flush(" * Direct input init ok. \n");
  else
    dbg_print_no_flush(" * Direct input init error. \n");
  diUpdateJoystickStates();
  return gpu_do_freeze(0);
}
