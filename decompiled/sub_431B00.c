#include "pch.h"
char __cdecl sub_431B00(_DWORD *a1)
{
  _DWORD v2[2]; // [esp+0h] [ebp-Ch] BYREF
  char v3[4]; // [esp+8h] [ebp-4h]

  v2[1] = 0;
  v3[1] = 0;
  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  v2[0] = 20972098;
  v3[0] = 16;
  return exec_scsi_cmd(v2, 0xAu, (int)a1, 16);
}
