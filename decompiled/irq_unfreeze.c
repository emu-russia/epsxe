#include "pch.h"
int __cdecl irq_unfreeze(int a1, _DWORD *a2)
{
  char v3[64]; // [esp+4h] [ebp-40h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dword_4FD870, 4);
  gzread(a2, dword_4FD874, 4);
  gzread(a2, dword_4FD878, 4);
  gzread(a2, int_reg, 656);
  sio_transfer_timeout = dword_50C218;
  dword_4FD868 = dword_50C21C;
  sio_transfer_pending = dword_50C220[0];
  return dword_50C220[0];
}
