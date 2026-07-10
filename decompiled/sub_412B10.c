#include "pch.h"
int sub_412B10()
{
  int v0; // esi
  int v1; // esi
  int v2; // edi
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int result; // eax
  int v7; // edx
  int v8; // ebx
  int v9; // [esp-4h] [ebp-18h]
  int v10; // [esp+10h] [ebp-4h]

  LOBYTE(v0) = unk_8A7F50;
  v10 = 3;
  do
  {
    v9 = dword_8A7FD4 - 16 * (unsigned __int8)v0;
    v1 = 16 * BYTE1(unk_8A7F50);
    v2 = 16 * BYTE2(unk_8A7F50);
    v3 = gte_clamp(-2130706432, v9);
    dword_8A7F64 = v4 + ((word_8A7F20 * v3) >> 12);
    dword_8A7F68 = v1 + ((word_8A7F20 * gte_clamp(-2139095040, dword_8A7FD8 - v1)) >> 12);
    v5 = gte_clamp(0x400000, dword_8A7FDC - v2);
    v0 = dword_8A7F54;
    result = v2 + ((word_8A7F20 * v5) >> 12);
    dword_8A7F54 = unk_8A7F58;
    v7 = dword_8A7F68 >> 4;
    v8 = result >> 4;
    dword_8A7F6C = result;
    unk_8A7F50 = v0;
    dword_8A8004 = dword_8A7F64 >> 4;
    dword_8A8008 = dword_8A7F68 >> 4;
    dword_8A800C = result >> 4;
    if ( dword_8A7F64 >> 4 >= 0 )
    {
      if ( dword_8A7F64 >> 4 <= 255 )
      {
        LOBYTE(unk_8A7F58) = dword_8A7F64 >> 4;
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
        BYTE1(unk_8A7F58) = dword_8A7F68 >> 4;
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
        BYTE2(unk_8A7F58) = result >> 4;
      }
      else
      {
        dword_8A7FFC |= 0x80000u;
        BYTE2(unk_8A7F58) = -1;
      }
    }
    else
    {
      dword_8A7FFC |= 0x80000u;
      BYTE2(unk_8A7F58) = 0;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(word_8A7F18);
    --v10;
  }
  while ( v10 );
  if ( dword_8A7F64 >= -32768 )
  {
    if ( dword_8A7F64 <= 0x7FFF )
    {
      word_8A7F24 = dword_8A7F64;
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
    word_8A7F24 = -32768;
  }
  if ( dword_8A7F68 >= -32768 )
  {
    if ( dword_8A7F68 <= 0x7FFF )
    {
      word_8A7F28 = dword_8A7F68;
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
    word_8A7F28 = -32768;
  }
  if ( result >= -32768 )
  {
    if ( result <= 0x7FFF )
    {
      word_8A7F2C = result;
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
    word_8A7F2C = -32768;
  }
  return result;
}
