#include "pch.h"
int sio_reset()
{
  sio0_mode_reg = 5;
  sio0_control_reg = 0;
  LOWORD(byte_52670C) = 0;
  BYTE2(byte_52670C) = 1;
  MEMORY[0x52680F] = 0;
  LOBYTE(dword_526810) = 0;
  sub_421B40();
  memcard_load();
  return sub_42D620(0);
}
