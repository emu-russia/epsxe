#include "pch.h"
int __cdecl sio_freeze(const char *a1, int a2)
{
  char Buffer[64]; // [esp+8h] [ebp-40h] BYREF

  sprintf(Buffer, "%s", a1);
  *(_DWORD *)&Buffer[3] = 263532;
  sub_438F70(a2, (int)Buffer, 7);
  sub_438F70(a2, (int)byte_526600, 532);
  sub_438F70(a2, (int)byte_516560, 132);
  sub_438F70(a2, (int)byte_526860, 262404);
  memset(Buffer, 0, sizeof(Buffer));
  *(_DWORD *)&Buffer[4] = dword_516540;
  *(_WORD *)&Buffer[8] = dword_4FC480;
  *(_DWORD *)Buffer = dword_4557AC;
  Buffer[10] = multitap_1 & 1;
  return sub_438F70(a2, (int)Buffer, 64);
}
