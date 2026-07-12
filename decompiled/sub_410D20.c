#include "pch.h"
char sub_410D20()
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

  v0 = word_8A7F04 * word_8A7FB0;
  v1 = (word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12;
  v2 = (word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12;
  v3 = (v0 + word_8A7F02 * word_8A7FAE + *(__int16 *)word_8A7F00 * word_8A7FAC) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = (word_8A7F04 * word_8A7FA4
                              + word_8A7F02 * word_8A7FA2
                              + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12;
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
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = (word_8A7F04 * word_8A7FAA
                              + word_8A7F02 * word_8A7FA8
                              + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12;
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
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (v0 + word_8A7F02 * word_8A7FAE + *(__int16 *)word_8A7F00 * word_8A7FAC) >> 12;
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
  v4 = dword_8A7FB4
     + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v5 = dword_8A7FB8
     + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v6 = dword_8A7FBC
     + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  dword_8A7F64 = v4;
  dword_8A7F68 = v5;
  dword_8A7F6C = v6;
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
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
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = v5;
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
  if ( v6 >= 0 )
  {
    if ( v6 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v6;
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
  v7 = v4 >> 4;
  dword_8A7F50 = dword_8A7F54;
  v8 = v5 >> 4;
  v9 = v6 >> 4;
  dword_8A7F54 = dword_8A7F58;
  dword_8A8004 = v7;
  dword_8A8008 = v8;
  dword_8A800C = v9;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      LOBYTE(dword_8A7F58) = v7;
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
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      BYTE1(dword_8A7F58) = v8;
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
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      BYTE2(dword_8A7F58) = v9;
    }
    else
    {
      LOBYTE(v7) = dword_8A7FFC;
      BYTE2(dword_8A7F58) = -1;
      dword_8A7FFC |= 0x80000u;
    }
    HIBYTE(dword_8A7F58) = byte_8A7F1B;
  }
  else
  {
    dword_8A7FFC |= 0x80000u;
    BYTE2(dword_8A7F58) = 0;
    HIBYTE(dword_8A7F58) = byte_8A7F1B;
    LOBYTE(v7) = byte_8A7F1B;
  }
  return v7;
}
