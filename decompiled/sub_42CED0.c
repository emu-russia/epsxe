#include "pch.h"
int __cdecl sub_42CED0(int a1, int a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  sub_438CA0(a2, v3, 7);
  sub_438CA0(a2, (char *)&dword_50AE80, 4396);
  word_4FD87C = (unsigned __int8)byte_50BF69;
  if ( byte_50AF4D )
    return cdrom_play_cdda_cb((unsigned __int8)dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
  else
    return cdrom_stop_cb();
}
