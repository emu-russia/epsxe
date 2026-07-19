#include "pch.h"
_DWORD *W9x_cdrom_gettrackinfo()
{
  char v0; // bl
  bool v1; // al
  unsigned __int8 v3; // bl
  int v4; // esi
  unsigned int v5; // [esp+8h] [ebp-1Ch] BYREF
  int v6; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h] BYREF
  _DWORD v9[3]; // [esp+18h] [ebp-Ch] BYREF

  v9[0] = 0x43;
  v9[1] = 0x3000000;
  v9[2] = 0x24;
  v0 = 10;
  v1 = 1;
  while ( v1 )
  {
    memset(byte_504CA0, 0, 0x324u);
    v1 = W9x_exec_scsi_cmd(v9, 0xAu, byte_504CA0, 0x324u) != 0;
    if ( !++v0 )
    {
      if ( v1 )
        return (_DWORD *)dbg_print(" * Cdrom gettrackinfo error.\n");
      break;
    }
  }
  dbg_print(" * First/Last track: %d %d\n", (unsigned __int8)byte_504CA2, (unsigned __int8)byte_504CA3);
  v3 = 0;
  LOBYTE(v7) = byte_504CA3 - byte_504CA2 + 1;
  LOBYTE(dword_4FD9BC) = v7;
  LOBYTE(v6) = 0;
  if ( byte_504CA3 - byte_504CA2 != 0xFF )
  {
    do
    {
      v4 = (unsigned __int8)v6;
      dbg_print(" * Track %d: ", (unsigned __int8)byte_504CA6[8 * (unsigned __int8)v6]);
      if ( (byte_504CA5[8 * v4] & 4) != 0 )
      {
        dbg_print("(DATA)  -");
      }
      else
      {
        dbg_print("(AUDIO) -");
        if ( !v3 )
          nocd = 2;
      }
      sub_431110(&v5, (unsigned __int8 *)(8 * v4 + 5262504));
      v5 += 150;
      dbg_print(" Start %d: (%02d,%02d,%02d) - ", v4, (unsigned __int8)(v5 / 0x4B / 0x3C), v5 / 0x4B % 0x3C, v5 % 0x4B);
      sub_431110(&v5, (unsigned __int8 *)(8 * v4 + 5262504));
      sub_431110(&v8, (unsigned __int8 *)(8 * v4 + 5262512));
      dbg_print(" Length %02d:%02d\n", (v8 - v5) / 0x4B / 0x3C, (v8 - v5) / 0x4B % 0x3C);
      LOBYTE(v6) = ++v3;
    }
    while ( v3 < (unsigned __int8)v7 );
  }
  return sub_431110(&v8, (unsigned __int8 *)(8 * (unsigned __int8)v7 + 5262504));
}
