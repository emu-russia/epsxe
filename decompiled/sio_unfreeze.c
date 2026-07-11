#include "pch.h"
void __cdecl sio_unfreeze(int a1, _DWORD *a2)
{
  char *v2; // edi
  char v3[4]; // [esp+8h] [ebp-40h] BYREF
  int v4; // [esp+Ch] [ebp-3Ch]
  __int16 v5; // [esp+10h] [ebp-38h]
  char v6; // [esp+12h] [ebp-36h]

  v2 = (char *)malloc(0x40104u);
  gzread(a2, v3, 7);
  gzread(a2, byte_526600, 532);
  gzread(a2, byte_516560, 132);
  memcard12_save();
  gzread(a2, v2, 262404);
  gzread(a2, v3, 64);
  dword_516540 = v4;
  dword_4557AC = *(_DWORD *)v3;
  LOWORD(dword_4FC480) = v5;
  multitap_1 = v6 & 1;
  free(v2);
}
