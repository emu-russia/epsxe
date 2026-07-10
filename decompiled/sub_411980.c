#include "pch.h"
char sub_411980()
{
  int v0; // edi
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // esi
  int v8; // edi
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // edx
  int v13; // eax

  v0 = unk_8A7F04 * unk_8A7FB0;
  v1 = (unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12;
  v2 = (unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12;
  v3 = (v0 + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE + SLOWORD(unk_8A7F00[0]) * unk_8A7FAC) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      word_8A7F24 = (unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12;
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
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      word_8A7F28 = (unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12;
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
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      word_8A7F2C = (v0 + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE + SLOWORD(unk_8A7F00[0]) * unk_8A7FAC) >> 12;
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
  v4 = unk_8A7FB4
     + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v5 = unk_8A7FB8
     + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v6 = unk_8A7FBC
     + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  unk_8A7F64 = v4;
  unk_8A7F68 = v5;
  unk_8A7F6C = v6;
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
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
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      word_8A7F28 = v5;
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
  if ( v6 >= 0 )
  {
    if ( v6 <= 0x7FFF )
    {
      word_8A7F2C = v6;
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
  v7 = ((__int16)word_8A7F28 * BYTE1(unk_8A7F18)) >> 8;
  v8 = ((__int16)word_8A7F2C * BYTE2(unk_8A7F18)) >> 8;
  v9 = gte_clamp(-2130706432, unk_8A7FD4 - (((__int16)word_8A7F24 * (unsigned __int8)unk_8A7F18) >> 8));
  unk_8A7F64 = v10 + ((unk_8A7F20 * v9) >> 12);
  unk_8A7F68 = v7 + ((unk_8A7F20 * gte_clamp(-2139095040, unk_8A7FD8 - v7)) >> 12);
  v11 = v8 + ((unk_8A7F20 * gte_clamp(0x400000, unk_8A7FDC - v8)) >> 12);
  unk_8A7F6C = v11;
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
  if ( v11 >= 0 )
  {
    if ( v11 <= 0x7FFF )
    {
      word_8A7F2C = v11;
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
  v12 = unk_8A7F68 >> 4;
  v13 = v11 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = unk_8A7F64 >> 4;
  unk_8A8008 = unk_8A7F68 >> 4;
  unk_8A800C = v13;
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
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
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
  if ( v13 >= 0 )
  {
    if ( v13 <= 255 )
    {
      BYTE2(unk_8A7F58) = v13;
    }
    else
    {
      unk_8A7FFC |= 0x80000u;
      LOBYTE(v13) = HIBYTE(unk_8A7F18);
      BYTE2(unk_8A7F58) = -1;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  else
  {
    LOBYTE(v13) = unk_8A7FFC;
    BYTE2(unk_8A7F58) = 0;
    unk_8A7FFC |= 0x80000u;
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  return v13;
}
