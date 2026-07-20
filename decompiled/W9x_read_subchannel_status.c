#include "pch.h"
char __cdecl W9x_read_subchannel_status(BYTE *a1)
{
  _DWORD v2[2]; // [esp+0h] [ebp-Ch] BYREF
  char v3[4]; // [esp+8h] [ebp-4h]

  v2[1] = 0;
  v3[1] = 0;
  *(_DWORD *)a1 = 0;
  *((_DWORD *)a1 + 1) = 0;
  *((_DWORD *)a1 + 2) = 0;
  *((_DWORD *)a1 + 3) = 0;
  v2[0] = 20972098;
  v3[0] = 16;
  return W9x_exec_scsi_cmd(v2, 0xAu, a1, 0x10u);
}
