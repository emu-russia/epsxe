#include "pch.h"
int (__stdcall *sio_reset())(_DWORD)
{
  sio0_mode_reg = 5;
  sio0_control_reg = 0;
  byte_52670C[0] = 0;
  byte_52670C[1] = 0;
  byte_52670C[2] = 1;
  byte_52670C[259] = 0;
  LOBYTE(dword_526810) = 0;
  sub_421B40();
  memcard_load();
  return sub_42D620(0);
}
