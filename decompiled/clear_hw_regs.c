#include "pch.h"
char clear_hw_regs()
{
  unsigned int i; // eax
  unsigned int j; // eax
  unsigned int k; // eax

  for ( i = 0; i < 48; i += 3 )
  {
    dword_50C150[i] = 0;
    dword_50C154[i] = 0;
    dword_50C158[i] = 0;
  }
  for ( j = 0; j < 16; j += 4 )
  {
    dword_50BFD0[j] = 0;
    dword_50BFD4[j] = 0;
    dword_50BFD8[j] = 0;
    dword_50BFDC[j] = 0;
  }
  for ( k = 0; k < 80; k += 5 )
  {
    dword_50C010[k] = 0;
    dword_50C014[k] = 0;
    dword_50C018[k] = 0;
    dword_50C01C[k] = 0;
  }
  dword_50C210 = 0;
  byte_50C214 = -1;
  byte_50C215 = -1;
  dword_4FD864 = 0;
  dword_4FD868 = 0;
  dword_4FD86C = 0;
  *(_DWORD *)dword_4FD870 = 0;
  *(_DWORD *)dword_4FD874 = 0;
  *(_DWORD *)dword_4FD878 = 0;
  return -1;
}
