#include "pch.h"
int clear_cpu_regs()
{
  *(_DWORD *)reg_pc = 0xBFC00000;
  memset(cpu_gpr, 0, 0x80u);
  memset(cop0_regs, 0, 0x40u);
  hw_update_counter = 0;
  dword_50C360 = 0;
  dword_50C364 = 0;
  cpu_LO = 0;
  cpu_HI = 0;
  return 0;
}
