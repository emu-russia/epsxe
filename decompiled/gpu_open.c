#include "pch.h"
int gpu_open()
{
  GPUopen(hOutputWnd);
  gpu_closed = 0;
  diShutdownDirectInput();
  hDlgInput = (int)hOutputWnd;
  hInst_For_DInput = (int)dword_50AE4C;
  if ( diInitDirectInput() == 1 )
    dbg_print_no_flush(" * Direct input init ok. \n");
  else
    dbg_print_no_flush(" * Direct input init error. \n");
  return diUpdateJoystickStates();
}
