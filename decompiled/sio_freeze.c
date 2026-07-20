#include "pch.h"
int __cdecl sio_freeze(const char *a1, int a2)
{
  char Buffer[64]; // [esp+8h] [ebp-40h] BYREF

  sprintf(Buffer, "%s", a1);
  *(_DWORD *)&Buffer[3] = 263532;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)byte_526600, 0x214u);
  gzwrite(a2, (unsigned __int8 *)sio_controller_state, 0x84u);
  gzwrite(a2, (unsigned __int8 *)sio_memcard_data_slot1, 0x40104u);
  memset(Buffer, 0, sizeof(Buffer));
  *(_DWORD *)&Buffer[4] = sio_multitap_state;
  *(_WORD *)&Buffer[8] = sio_multitap_slot_counter;
  *(_DWORD *)Buffer = sio_transfer_length;
  Buffer[10] = multitap_1 & 1;
  return gzwrite(a2, (unsigned __int8 *)Buffer, 0x40u);
}
