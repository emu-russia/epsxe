#include "pch.h"
char sub_410690()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax

  v0 = 16 * BYTE1(unk_8A7F18);
  v1 = 16 * BYTE2(unk_8A7F18);
  v2 = gte_clamp(-2130706432, unk_8A7FD4 - 16 * (unsigned __int8)unk_8A7F18);
  unk_8A7F64 = v3 + ((unk_8A7F20 * v2) >> 12);
  unk_8A7F68 = v0 + ((unk_8A7F20 * gte_clamp(-2139095040, unk_8A7FD8 - v0)) >> 12);
  v4 = v1 + ((unk_8A7F20 * gte_clamp(0x400000, unk_8A7FDC - v1)) >> 12);
  unk_8A7F6C = v4;
  if ( unk_8A7F64 >= -32768 )
  {
    if ( unk_8A7F64 <= 0x7FFF )
    {
      word_8A7F24 = unk_8A7F64;
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = -32768;
  }
  if ( unk_8A7F68 >= -32768 )
  {
    if ( unk_8A7F68 <= 0x7FFF )
    {
      word_8A7F28 = unk_8A7F68;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = -32768;
  }
  if ( v4 >= -32768 )
  {
    if ( v4 <= 0x7FFF )
    {
      word_8A7F2C = v4;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = -32768;
  }
  unk_8A7F50 = unk_8A7F54;
  v5 = unk_8A7F68 >> 4;
  v6 = v4 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = unk_8A7F64 >> 4;
  unk_8A8008 = unk_8A7F68 >> 4;
  unk_8A800C = v6;
  if ( unk_8A7F64 >> 4 >= 0 )
  {
    if ( unk_8A7F64 >> 4 <= 255 )
    {
      LOBYTE(unk_8A7F58) = unk_8A7F64 >> 4;
    }
    else
    {
      unk_8A7FFC |= 0x200000u;
      LOBYTE(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x200000u;
    LOBYTE(unk_8A7F58) = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 255 )
    {
      BYTE1(unk_8A7F58) = unk_8A7F68 >> 4;
    }
    else
    {
      unk_8A7FFC |= 0x100000u;
      BYTE1(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x100000u;
    BYTE1(unk_8A7F58) = 0;
  }
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      BYTE2(unk_8A7F58) = v6;
    }
    else
    {
      unk_8A7FFC |= 0x80000u;
      LOBYTE(v6) = HIBYTE(unk_8A7F18);
      BYTE2(unk_8A7F58) = -1;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  else
  {
    LOBYTE(v6) = unk_8A7FFC;
    BYTE2(unk_8A7F58) = 0;
    unk_8A7FFC |= 0x80000u;
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  return v6;
}
