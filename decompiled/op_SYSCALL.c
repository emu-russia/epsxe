#include "pch.h"
unsigned int op_SYSCALL()
{
  unsigned int result; // eax

  dword_50C2AC = *(_DWORD *)reg_pc - 4;
  result = dword_50C2A4 & 0xFFFFFFC0;
  dword_50C2A8 = 32;
  dword_50C2A4 = dword_50C2A4 & 0xFFFFFFC0 | (4 * (dword_50C2A4 & 0xF));
  *(_DWORD *)reg_pc = 0x80000080;
  return result;
}
