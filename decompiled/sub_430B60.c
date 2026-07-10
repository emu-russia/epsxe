#include "pch.h"
char __cdecl sub_430B60(int a1, int a2, int a3, int a4)
{
  int v4; // ecx
  char v5; // bl
  char v6; // dl
  char result; // al
  char v8; // [esp+Bh] [ebp-1h]
  unsigned __int8 v9; // [esp+14h] [ebp+8h]
  unsigned __int8 v10; // [esp+18h] [ebp+Ch]
  char v11; // [esp+18h] [ebp+Ch]

  *(_DWORD *)a4 = 0;
  *(_DWORD *)(a4 + 4) = 0;
  v8 = 0;
  if ( CDRgetBufferSub
    && ((v4 = CDRgetBufferSub(), !extsubchanhle) || (dword_50C280 & 0x1F000000) != 0x1F000000 || (_BYTE)a1 == 3)
    && v4 )
  {
    if ( (_BYTE)a3 )
    {
      v10 = a3 - 1;
    }
    else
    {
      v10 = 74;
      if ( (_BYTE)a2 )
      {
        LOBYTE(a2) = a2 - 1;
      }
      else
      {
        LOBYTE(a2) = 59;
        LOBYTE(a1) = a1 - 1;
      }
    }
    v5 = (unsigned __int8)a1 % 10 + 16 * ((unsigned __int8)a1 / 10);
    v9 = (unsigned __int8)a2 % 10 + 16 * ((unsigned __int8)a2 / 10);
    v11 = v10 % 10 + 16 * (v10 / 10);
    *(_DWORD *)a4 = *(_DWORD *)(v4 + 13);
    *(_BYTE *)(a4 + 4) = *(_BYTE *)(v4 + 17);
    *(_WORD *)(a4 + 5) = *(_WORD *)(v4 + 19);
    *(_BYTE *)(a4 + 7) = *(_BYTE *)(v4 + 21);
    if ( v5 != *(_BYTE *)(v4 + 19) )
      v8 = 1;
    if ( v5 != *(_BYTE *)(v4 + 15) )
      ++v8;
    if ( v9 != *(_BYTE *)(v4 + 20) )
      ++v8;
    v6 = v8;
    if ( (((v9 - 2) & 0xF) + 10 * ((v9 - 2) >> 4)) % 10 + 16 * ((((v9 - 2) & 0xF) + 10 * ((v9 - 2) >> 4)) / 10) != *(unsigned __int8 *)(v4 + 16) )
      v6 = v8 + 1;
    result = v11;
    if ( v11 != *(_BYTE *)(v4 + 21) )
      ++v6;
    if ( v11 != *(_BYTE *)(v4 + 17) )
      ++v6;
    if ( (unsigned __int8)v6 >= 2u )
    {
      result = 0;
      *(_DWORD *)(a4 + 2) = 0;
      *(_WORD *)(a4 + 6) = 0;
      if ( v5 == 3 )
        byte_4F8320 = 1;
    }
  }
  else
  {
    LOBYTE(a1) = (unsigned __int8)a1 % 10 + 16 * ((unsigned __int8)a1 / 10);
    LOBYTE(a2) = (unsigned __int8)a2 % 10 + 16 * ((unsigned __int8)a2 / 10);
    LOBYTE(a3) = (unsigned __int8)a3 % 10 + 16 * ((unsigned __int8)a3 / 10);
    sub_430820(a1, a2, a3, a4, a4 + 2, a4 + 3, a4 + 4);
    *(_BYTE *)(a4 + 1) = 1;
    *(_BYTE *)(a4 + 5) = a1;
    *(_BYTE *)(a4 + 6) = a2;
    *(_BYTE *)(a4 + 7) = a3;
    return a3;
  }
  return result;
}
