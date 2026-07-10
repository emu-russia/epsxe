#include "pch.h"
unsigned int op_SYSCALL()
{
  unsigned int result; // eax

  dword_50C2AC = reg_pc - 4;
  result = dword_50C2A4 & 0xFFFFFFC0;
  dword_50C2A8 = 32;
  dword_50C2A4 = dword_50C2A4 & 0xFFFFFFC0 | (4 * (dword_50C2A4 & 0xF));
  reg_pc = -2147483520;
  return result;
}
