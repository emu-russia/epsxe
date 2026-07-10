#include "pch.h"
char sub_414030()
{
  int v0; // eax
  int v1; // ecx
  int v2; // edx
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // edx

  v0 = dword_8A7FB4
     + (((__int16)word_8A7F2C * word_8A7FC4 + (__int16)word_8A7F28 * word_8A7FC2 + (__int16)word_8A7F24 * word_8A7FC0) >> 12);
  v1 = dword_8A7FB8
     + (((__int16)word_8A7F2C * word_8A7FCA + (__int16)word_8A7F28 * word_8A7FC8 + (__int16)word_8A7F24 * word_8A7FC6) >> 12);
  v2 = dword_8A7FBC
     + (((__int16)word_8A7F2C * word_8A7FD0 + (__int16)word_8A7F28 * word_8A7FCE + (__int16)word_8A7F24 * word_8A7FCC) >> 12);
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
    {
      word_8A7F24 = dword_8A7FB4
                  + (((__int16)word_8A7F2C * word_8A7FC4
                    + (__int16)word_8A7F28 * word_8A7FC2
                    + (__int16)word_8A7F24 * word_8A7FC0) >> 12);
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
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
      dword_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
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
      dword_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v3 = ((__int16)word_8A7F24 * (unsigned __int8)word_8A7F18) >> 8;
  dword_8A7F64 = v3;
  v4 = ((__int16)word_8A7F28 * BYTE1(word_8A7F18)) >> 8;
  dword_8A7F68 = v4;
  v5 = ((__int16)word_8A7F2C * BYTE2(word_8A7F18)) >> 8;
  dword_8A7F6C = v5;
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      word_8A7F24 = ((__int16)word_8A7F24 * (unsigned __int8)word_8A7F18) >> 8;
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    word_8A7F24 = 0;
  }
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      word_8A7F28 = ((__int16)word_8A7F28 * BYTE1(word_8A7F18)) >> 8;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      word_8A7F2C = ((__int16)word_8A7F2C * BYTE2(word_8A7F18)) >> 8;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v6 = v3 >> 4;
  unk_8A7F50 = unk_8A7F54;
  v7 = v4 >> 4;
  v8 = v5 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = v6;
  unk_8A8008 = v7;
  unk_8A800C = v8;
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      LOBYTE(unk_8A7F58) = v6;
    }
    else
    {
      dword_8A7FFC |= 0x200000u;
      LOBYTE(unk_8A7F58) = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x200000u;
    LOBYTE(unk_8A7F58) = 0;
  }
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      BYTE1(unk_8A7F58) = v7;
    }
    else
    {
      dword_8A7FFC |= 0x100000u;
      BYTE1(unk_8A7F58) = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x100000u;
    BYTE1(unk_8A7F58) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      BYTE2(unk_8A7F58) = v8;
    }
    else
    {
      LOBYTE(v6) = dword_8A7FFC;
      dword_8A7FFC |= 0x80000u;
      BYTE2(unk_8A7F58) = -1;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(word_8A7F18);
  }
  else
  {
    dword_8A7FFC |= 0x80000u;
    BYTE2(unk_8A7F58) = 0;
    HIBYTE(unk_8A7F58) = HIBYTE(word_8A7F18);
    LOBYTE(v6) = HIBYTE(word_8A7F18);
  }
  return v6;
}
