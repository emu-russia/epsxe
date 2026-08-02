#include "pch.h"
char __cdecl iso_verify_sub(unsigned __int8 a1, unsigned __int8 a2, char a3, int a4)
{
  int v4; // eax
  unsigned __int8 v5; // bh
  int v6; // eax
  int v7; // eax
  unsigned __int8 v8; // dl
  unsigned __int8 v9; // bl
  unsigned __int8 v10; // al
  int v11; // eax
  unsigned __int8 v13; // [esp+Bh] [ebp-1h]
  unsigned __int8 v14; // [esp+10h] [ebp+4h]
  unsigned __int8 v15; // [esp+18h] [ebp+Ch]
  char v16; // [esp+18h] [ebp+Ch]

  *(_DWORD *)a4 = 0;
  *(_DWORD *)(a4 + 4) = 0;
  if ( use_subchannel )
  {
    *(_DWORD *)a4 = dword_50568D;
    *(_BYTE *)(a4 + 4) = byte_505691;
    *(_WORD *)(a4 + 5) = word_505693;
    *(_BYTE *)(a4 + 7) = byte_505695[0];
    if ( (unsigned __int8)byte_50A1A5 - 2 < 0 )
    {
      v13 = (unsigned __int8)byte_50A1A4 % 10 + 16 * ((unsigned __int8)byte_50A1A4 / 10) != (unsigned __int8)word_505693;
      if ( ((unsigned __int8)byte_50A1A4 - 1) % 10 + 16 * (((unsigned __int8)byte_50A1A4 - 1) / 10) != BYTE2(dword_50568D) )
        ++v13;
      v5 = byte_505695[0];
      if ( (unsigned __int8)byte_50A1A5 % 10 + 16 * ((unsigned __int8)byte_50A1A5 / 10) != HIBYTE(word_505693) )
        ++v13;
      v6 = (unsigned __int8)byte_50A1A5 + 58;
    }
    else
    {
      v4 = (unsigned __int8)byte_50A1A4 % 10 + 16 * ((unsigned __int8)byte_50A1A4 / 10);
      v13 = v4 != (unsigned __int8)word_505693;
      if ( v4 != BYTE2(dword_50568D) )
        ++v13;
      v5 = byte_505695[0];
      if ( (unsigned __int8)byte_50A1A5 % 10 + 16 * ((unsigned __int8)byte_50A1A5 / 10) != HIBYTE(word_505693) )
        ++v13;
      v6 = (unsigned __int8)byte_50A1A5 - 2;
    }
    if ( v6 % 10 + 16 * (v6 / 10) != HIBYTE(dword_50568D) )
      ++v13;
    v7 = (unsigned __int8)byte_50A1A6 % 10 + 16 * ((unsigned __int8)byte_50A1A6 / 10);
    v8 = v13;
    if ( v7 != v5 )
      v8 = v13 + 1;
    if ( v7 != (unsigned __int8)byte_505691 )
      ++v8;
    if ( v8 >= 2u && a1 == 3 )
    {
      *(_DWORD *)(a4 + 2) = 0;
      *(_WORD *)(a4 + 6) = 0;
      v7 = (unsigned __int8)byte_50A1A4 % 10 + 16 * ((unsigned __int8)byte_50A1A4 / 10);
      if ( v7 == 3 )
        byte_4F8320 = 1;
    }
  }
  else
  {
    if ( a3 )
    {
      v15 = a3 - 1;
    }
    else
    {
      v15 = 74;
      if ( a2 )
      {
        --a2;
      }
      else
      {
        a2 = 59;
        --a1;
      }
    }
    *(_BYTE *)a4 = 1;
    *(_BYTE *)(a4 + 1) = 1;
    v14 = a1 % 10 + 16 * (a1 / 10);
    v9 = a2 % 10 + 16 * (a2 / 10);
    v16 = v15 % 10 + 16 * (v15 / 10);
    v10 = v14;
    if ( v9 < 2u )
      v10 = ((v14 & 0xF) + 10 * (v14 >> 4) - 1) % 10 + 16 * (((v14 & 0xF) + 10 * (v14 >> 4) - 1) / 10);
    *(_BYTE *)(a4 + 2) = v10;
    v11 = v9 & 0xF;
    if ( v9 < 2u )
      v7 = v11 + 10 * (v9 >> 4) + 58;
    else
      v7 = v11 + 10 * (v9 >> 4) - 2;
    *(_BYTE *)(a4 + 6) = v9;
    *(_BYTE *)(a4 + 3) = v7 % 10 + 16 * (v7 / 10);
    *(_BYTE *)(a4 + 4) = v16;
    *(_BYTE *)(a4 + 5) = v14;
    *(_BYTE *)(a4 + 7) = v16;
    LOBYTE(v7) = v16;
  }
  return v7;
}
