#include "pch.h"
char sub_410420()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax

  v0 = (HIBYTE(word_8A7F18) * word_8A7F28[0]) >> 8;
  v1 = ((unsigned __int8)byte_8A7F1A * word_8A7F2C[0]) >> 8;
  v2 = gte_clamp(-2130706432, dword_8A7FD4 - (((unsigned __int8)word_8A7F18 * word_8A7F24[0]) >> 8));
  dword_8A7F64 = v3 + ((word_8A7F20 * v2) >> 12);
  dword_8A7F68 = v0 + ((word_8A7F20 * gte_clamp(-2139095040, dword_8A7FD8 - v0)) >> 12);
  v4 = v1 + ((word_8A7F20 * gte_clamp(0x400000, dword_8A7FDC - v1)) >> 12);
  dword_8A7F6C = v4;
  if ( dword_8A7F64 >= -32768 )
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
    *(_DWORD *)word_8A7F24 = -32768;
  }
  if ( dword_8A7F68 >= -32768 )
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
    *(_DWORD *)word_8A7F28 = -32768;
  }
  if ( v4 >= -32768 )
  {
    if ( v4 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v4;
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
    *(_DWORD *)word_8A7F2C = -32768;
  }
  unk_8A7F50 = dword_8A7F54;
  v5 = dword_8A7F68 >> 4;
  v6 = v4 >> 4;
  dword_8A7F54 = unk_8A7F58;
  dword_8A8004 = dword_8A7F64 >> 4;
  dword_8A8008 = dword_8A7F68 >> 4;
  dword_8A800C = v6;
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
  if ( v5 >= 0 )
  {
    if ( v5 <= 255 )
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
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      unk_8A7F5A = v6;
    }
    else
    {
      dword_8A7FFC |= 0x80000u;
      LOBYTE(v6) = byte_8A7F1B;
      unk_8A7F5A = -1;
    }
    byte_8A7F5B = byte_8A7F1B;
  }
  else
  {
    LOBYTE(v6) = dword_8A7FFC;
    unk_8A7F5A = 0;
    dword_8A7FFC |= 0x80000u;
    byte_8A7F5B = byte_8A7F1B;
  }
  return v6;
}
