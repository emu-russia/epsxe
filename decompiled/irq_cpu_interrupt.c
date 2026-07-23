#include "pch.h"
unsigned int irq_cpu_interrupt()
{
  unsigned int result; // eax

  result = *(_DWORD *)int_reg;
  if ( (*(_DWORD *)int_reg & int_mask) != 0 )
  {
    result = dword_50C2A4;
    if ( (dword_50C2A4 & 0x401) == 0x401 )
    {
      result = dword_50C2A4 & 0xFFFFFFC0;
      dword_50C2AC = *(_DWORD *)reg_pc;
      dword_50C2A8 = 1024;
      *(_DWORD *)reg_pc = 0x80000080;
      dword_50C2A4 = dword_50C2A4 & 0xFFFFFFC0 | (4 * (dword_50C2A4 & 0xF));
    }
  }
  return result;
}
