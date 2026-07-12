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
     + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v1 = dword_8A7FB8
     + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v2 = dword_8A7FBC
     + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = dword_8A7FB4
                             + ((word_8A7F2C[0] * word_8A7FC4
                               + word_8A7F28[0] * word_8A7FC2
                               + word_8A7F24[0] * word_8A7FC0) >> 12);
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = v1;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v2;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v3 = (word_8A7F24[0] * (unsigned __int8)word_8A7F18) >> 8;
  dword_8A7F64 = v3;
  v4 = (word_8A7F28[0] * HIBYTE(word_8A7F18)) >> 8;
  dword_8A7F68 = v4;
  v5 = (word_8A7F2C[0] * (unsigned __int8)byte_8A7F1A) >> 8;
  dword_8A7F6C = v5;
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = (word_8A7F24[0] * (unsigned __int8)word_8A7F18) >> 8;
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = (word_8A7F28[0] * HIBYTE(word_8A7F18)) >> 8;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (word_8A7F2C[0] * (unsigned __int8)byte_8A7F1A) >> 8;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v6 = v3 >> 4;
  dword_8A7F50 = dword_8A7F54;
  v7 = v4 >> 4;
  v8 = v5 >> 4;
  dword_8A7F54 = dword_8A7F58;
  dword_8A8004 = v6;
  dword_8A8008 = v7;
  dword_8A800C = v8;
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      LOBYTE(dword_8A7F58) = v6;
    }
    else
    {
      dword_8A7FFC |= 0x200000u;
      LOBYTE(dword_8A7F58) = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x200000u;
    LOBYTE(dword_8A7F58) = 0;
  }
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      BYTE1(dword_8A7F58) = v7;
    }
    else
    {
      dword_8A7FFC |= 0x100000u;
      BYTE1(dword_8A7F58) = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x100000u;
    BYTE1(dword_8A7F58) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      BYTE2(dword_8A7F58) = v8;
    }
    else
    {
      LOBYTE(v6) = dword_8A7FFC;
      dword_8A7FFC |= 0x80000u;
      BYTE2(dword_8A7F58) = -1;
    }
    HIBYTE(dword_8A7F58) = byte_8A7F1B;
  }
  else
  {
    dword_8A7FFC |= 0x80000u;
    BYTE2(dword_8A7F58) = 0;
    HIBYTE(dword_8A7F58) = byte_8A7F1B;
    LOBYTE(v6) = byte_8A7F1B;
  }
  return v6;
}
