#include "pch.h"
int __cdecl sub_42CF40(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dword_50AE80, 4396);
  word_50BF7E = (unsigned __int8)byte_50BF68;
  word_50BF80 = (unsigned __int8)byte_50BF68;
  word_4FD87C = (unsigned __int8)byte_50BF69;
  word_50BF82 = (unsigned __int8)byte_50BF67;
  if ( byte_50AF4D )
    return cdrom_play_cdda_cb((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
  else
    return cdrom_stop_cb();
}
