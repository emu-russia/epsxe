#include "pch.h"
bool __cdecl W2k_send_subchannel_command(int a1)
{
  __int16 v2; // [esp+0h] [ebp-Ch] BYREF
  char v3; // [esp+2h] [ebp-Ah]
  char v4; // [esp+3h] [ebp-9h]
  char v5; // [esp+4h] [ebp-8h]
  char v6; // [esp+5h] [ebp-7h]
  __int16 v7; // [esp+6h] [ebp-6h]
  __int16 v8; // [esp+8h] [ebp-4h]

  v7 = 0;
  v8 = 0;
  v3 = HIBYTE(a1);
  v4 = BYTE2(a1);
  v2 = 43;
  v5 = BYTE1(a1);
  v6 = a1;
  return W2k_send_scsi_command(&v2, 0xAu, 0, 0);
}
