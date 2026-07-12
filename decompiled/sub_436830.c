#include "pch.h"
unsigned int __cdecl sub_436830(int a1, int a2, unsigned int a3, void *a4)
{
  unsigned __int8 v5; // [esp+8h] [ebp-126Ch]
  unsigned __int8 v6; // [esp+Ch] [ebp-1268h]
  unsigned __int8 v7; // [esp+10h] [ebp-1264h]
  _BYTE v8[4704]; // [esp+14h] [ebp-1260h] BYREF

  v7 = (a1 + 150) % 0x4Bu;
  v6 = (a1 + 150) / 0x4Bu / 0x3C;
  v5 = (a1 + 150) / 0x4Bu % 0x3C;
  if ( loaded_file_type == 3 )
  {
    sub_42FF60(v6, v5, v7, (int)v8);
  }
  else if ( loaded_file_type == 1 )
  {
    cdrom_read_data_cb(v6, v5, v7, v8);
  }
  qmemcpy(a4, &v8[a2], a3);
  return a3;
}
