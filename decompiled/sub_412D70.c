#include "pch.h"
char sub_412D70()
{
  int v0; // edi
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  int v12; // edx

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
  v7 = ((__int16)word_8A7F24 * (unsigned __int8)unk_8A7F18) >> 8;
  unk_8A7F64 = v7;
  v8 = ((__int16)word_8A7F28 * BYTE1(unk_8A7F18)) >> 8;
  unk_8A7F68 = v8;
  v9 = ((__int16)word_8A7F2C * BYTE2(unk_8A7F18)) >> 8;
  unk_8A7F6C = v9;
  if ( v7 >= 0 )
  {
    if ( v7 <= 0x7FFF )
    {
      word_8A7F24 = ((__int16)word_8A7F24 * (unsigned __int8)unk_8A7F18) >> 8;
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
  if ( v8 >= 0 )
  {
    if ( v8 <= 0x7FFF )
    {
      word_8A7F28 = ((__int16)word_8A7F28 * BYTE1(unk_8A7F18)) >> 8;
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
  if ( v9 >= 0 )
  {
    if ( v9 <= 0x7FFF )
    {
      word_8A7F2C = ((__int16)word_8A7F2C * BYTE2(unk_8A7F18)) >> 8;
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
  v10 = v7 >> 4;
  unk_8A7F50 = unk_8A7F54;
  v11 = v8 >> 4;
  v12 = v9 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = v10;
  unk_8A8008 = v11;
  unk_8A800C = v12;
  if ( v10 >= 0 )
  {
    if ( v10 <= 255 )
    {
      LOBYTE(unk_8A7F58) = v10;
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
  if ( v11 >= 0 )
  {
    if ( v11 <= 255 )
    {
      BYTE1(unk_8A7F58) = v11;
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
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
    {
      BYTE2(unk_8A7F58) = v12;
    }
    else
    {
      LOBYTE(v10) = unk_8A7FFC;
      unk_8A7FFC |= 0x80000u;
      BYTE2(unk_8A7F58) = -1;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  else
  {
    unk_8A7FFC |= 0x80000u;
    BYTE2(unk_8A7F58) = 0;
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
    LOBYTE(v10) = HIBYTE(unk_8A7F18);
  }
  return v10;
}
