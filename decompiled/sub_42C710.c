#include "pch.h"
char sub_42C710()
{
  __int16 v0; // bx
  int v1; // eax

  v0 = dword_50AF50;
  v1 = sub_42C6D0(dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
  if ( dword_50BF58 != v1 )
  {
    cdrom_read_data_cb((unsigned __int8)v0, HIBYTE(v0), BYTE2(dword_50AF50), byte_50AF56);
    dword_50BF58 = sub_42C6D0(dword_50AF50, BYTE1(dword_50AF50), BYTE2(dword_50AF50));
    LOBYTE(v1) = byte_50AF07[72];
    dword_50BF5C = (byte_50AF07[72] & 0x20) != 0 ? 12 : 24;
    if ( (byte_50AF66[2] & 0xF) == 4 )
    {
      LOBYTE(v1) = byte_50AF07[72] & 0x48;
      if ( (byte_50AF07[72] & 0x48) == 0x40
        || (_BYTE)v1 == 72
        && byte_50AF66[0] == (_BYTE)word_50AF54
        && (LOBYTE(v1) = byte_50AF66[1], byte_50AF66[1] == HIBYTE(word_50AF54)) )
      {
        LOBYTE(v1) = spu_play_adpcm_cb(byte_50AF66);
      }
    }
  }
  return v1;
}
