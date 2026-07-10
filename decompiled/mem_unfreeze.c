#include "pch.h"
int __cdecl sub_41D340(int a1, int a2)
{
  _BYTE v3[16]; // [esp+4h] [ebp-10h] BYREF

  sub_438CA0(a2, v3, 7);
  sub_438CA0(a2, ram_0, 0x200000);
  sub_438CA0(a2, &byte_876EA0, 0x20000);
  return sub_438CA0(a2, &dcache, 4096);
}
