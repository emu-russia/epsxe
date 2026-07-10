#include "pch.h"
int clear_regs()
{
  reg_pc = 0xBFC00000;
  memset(cpu_gpr, 0, 0x80u);
  memset(dword_50C274, 0, 0x40u);
  dword_50C270 = 0;
  dword_50C360 = 0;
  dword_50C364 = 0;
  cpu_LO = 0;
  cpu_HI = 0;
  return 0;
}
