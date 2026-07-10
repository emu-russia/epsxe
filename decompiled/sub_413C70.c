#include "pch.h"
char sub_413C70()
{
  int v0; // eax
  int v1; // ecx
  int v2; // edx
  int v3; // esi
  int v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax

  v0 = unk_8A7FB4
     + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v1 = unk_8A7FB8
     + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v2 = unk_8A7FBC
     + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  unk_8A7F64 = v0;
  unk_8A7F68 = v1;
  unk_8A7F6C = v2;
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
    {
      word_8A7F24 = unk_8A7FB4
                  + (((__int16)word_8A7F2C * unk_8A7FC4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
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
    word_8A7F24 = 0;
  }
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      word_8A7F28 = v1;
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
    word_8A7F28 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      word_8A7F2C = v2;
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
    word_8A7F2C = 0;
  }
  v3 = ((__int16)word_8A7F28 * BYTE1(unk_8A7F18)) >> 8;
  v4 = ((__int16)word_8A7F2C * BYTE2(unk_8A7F18)) >> 8;
  v5 = gte_clamp(-2130706432, unk_8A7FD4 - (((__int16)word_8A7F24 * (unsigned __int8)unk_8A7F18) >> 8));
  unk_8A7F64 = v6 + ((unk_8A7F20 * v5) >> 12);
  unk_8A7F68 = v3 + ((unk_8A7F20 * gte_clamp(-2139095040, unk_8A7FD8 - v3)) >> 12);
  v7 = v4 + ((unk_8A7F20 * gte_clamp(0x400000, unk_8A7FDC - v4)) >> 12);
  unk_8A7F6C = v7;
  if ( unk_8A7F64 >= 0 )
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
    word_8A7F24 = 0;
  }
  if ( unk_8A7F68 >= 0 )
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
    word_8A7F28 = 0;
  }
  if ( v7 >= 0 )
  {
    if ( v7 <= 0x7FFF )
    {
      word_8A7F2C = v7;
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
    word_8A7F2C = 0;
  }
  unk_8A7F50 = unk_8A7F54;
  v8 = unk_8A7F68 >> 4;
  v9 = v7 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = unk_8A7F64 >> 4;
  unk_8A8008 = unk_8A7F68 >> 4;
  unk_8A800C = v9;
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
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
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
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      BYTE2(unk_8A7F58) = v9;
    }
    else
    {
      unk_8A7FFC |= 0x80000u;
      LOBYTE(v9) = HIBYTE(unk_8A7F18);
      BYTE2(unk_8A7F58) = -1;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  else
  {
    LOBYTE(v9) = unk_8A7FFC;
    BYTE2(unk_8A7F58) = 0;
    unk_8A7FFC |= 0x80000u;
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  return v9;
}
