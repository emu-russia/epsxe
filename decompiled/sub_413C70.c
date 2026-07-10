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

  v0 = dword_8A7FB4
     + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v1 = dword_8A7FB8
     + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v2 = dword_8A7FBC
     + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  dword_8A7F64 = v0;
  dword_8A7F68 = v1;
  dword_8A7F6C = v2;
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
  v3 = (word_8A7F28[0] * HIBYTE(word_8A7F18)) >> 8;
  v4 = (word_8A7F2C[0] * (unsigned __int8)byte_8A7F1A) >> 8;
  v5 = gte_clamp(-2130706432, dword_8A7FD4 - ((word_8A7F24[0] * (unsigned __int8)word_8A7F18) >> 8));
  dword_8A7F64 = v6 + ((word_8A7F20 * v5) >> 12);
  dword_8A7F68 = v3 + ((word_8A7F20 * gte_clamp(-2139095040, dword_8A7FD8 - v3)) >> 12);
  v7 = v4 + ((word_8A7F20 * gte_clamp(0x400000, dword_8A7FDC - v4)) >> 12);
  dword_8A7F6C = v7;
  if ( dword_8A7F64 >= 0 )
  {
    if ( dword_8A7F64 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = dword_8A7F64;
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
  if ( dword_8A7F68 >= 0 )
  {
    if ( dword_8A7F68 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = dword_8A7F68;
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
  if ( v7 >= 0 )
  {
    if ( v7 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v7;
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
  unk_8A7F50 = unk_8A7F54;
  v8 = dword_8A7F68 >> 4;
  v9 = v7 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = dword_8A7F64 >> 4;
  unk_8A8008 = dword_8A7F68 >> 4;
  unk_8A800C = v9;
  if ( dword_8A7F64 >> 4 >= 0 )
  {
    if ( dword_8A7F64 >> 4 <= 255 )
    {
      unk_8A7F58 = dword_8A7F64 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x200000u;
      unk_8A7F58 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x200000u;
    unk_8A7F58 = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      unk_8A7F59 = dword_8A7F68 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x100000u;
      unk_8A7F59 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x100000u;
    unk_8A7F59 = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      unk_8A7F5A = v9;
    }
    else
    {
      dword_8A7FFC |= 0x80000u;
      LOBYTE(v9) = byte_8A7F1B;
      unk_8A7F5A = -1;
    }
    unk_8A7F5B = byte_8A7F1B;
  }
  else
  {
    LOBYTE(v9) = dword_8A7FFC;
    unk_8A7F5A = 0;
    dword_8A7FFC |= 0x80000u;
    unk_8A7F5B = byte_8A7F1B;
  }
  return v9;
}
