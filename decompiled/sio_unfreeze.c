#include "pch.h"
void __cdecl sio_unfreeze(int a1, int a2)
{
  char *v2; // edi
  _DWORD v3[2]; // [esp+8h] [ebp-40h] BYREF
  __int16 v4; // [esp+10h] [ebp-38h]
  char v5; // [esp+12h] [ebp-36h]

  v2 = (char *)malloc(0x40104u);
  sub_438CA0(a2, (char *)v3, 7);
  sub_438CA0(a2, byte_526600, 532);
  sub_438CA0(a2, (char *)&byte_516560, 132);
  memcard2_save();
  sub_438CA0(a2, v2, 262404);
  sub_438CA0(a2, (char *)v3, 64);
  dword_516540 = v3[1];
  dword_4557AC = v3[0];
  LOWORD(dword_4FC480) = v4;
  multitap_1 = v5 & 1;
  free(v2);
}
