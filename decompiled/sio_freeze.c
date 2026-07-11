#include "pch.h"
int __cdecl sio_freeze(const char *a1, int a2)
{
  char Buffer[64]; // [esp+8h] [ebp-40h] BYREF

  sprintf(Buffer, "%s", a1);
  *(_DWORD *)&Buffer[3] = 263532;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)byte_526600, 0x214u);
  gzwrite(a2, (unsigned __int8 *)byte_516560, 0x84u);
  gzwrite(a2, (unsigned __int8 *)byte_526860, 0x40104u);
  memset(Buffer, 0, sizeof(Buffer));
  *(_DWORD *)&Buffer[4] = dword_516540;
  *(_WORD *)&Buffer[8] = dword_4FC480;
  *(_DWORD *)Buffer = dword_4557AC;
  Buffer[10] = multitap_1 & 1;
  return gzwrite(a2, (unsigned __int8 *)Buffer, 0x40u);
}
