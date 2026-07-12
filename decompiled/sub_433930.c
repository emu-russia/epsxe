#include "pch.h"
char __cdecl sub_433930(unsigned int a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  char v4; // bl
  char v5; // cl
  char result; // al
  char v7; // [esp+Fh] [ebp-1h]
  unsigned __int8 v8; // [esp+18h] [ebp+8h]
  unsigned __int8 v9; // [esp+18h] [ebp+8h]
  unsigned __int8 v10; // [esp+1Ch] [ebp+Ch]
  char v11; // [esp+1Ch] [ebp+Ch]
  unsigned __int8 v12; // [esp+1Ch] [ebp+Ch]

  *(_DWORD *)a4 = 0;
  *(_DWORD *)(a4 + 4) = 0;
  v7 = 0;
  if ( (_BYTE)dword_5053E0 )
  {
    if ( a3 )
    {
      v10 = a3 - 1;
    }
    else
    {
      v10 = 74;
      if ( a2 )
      {
        --a2;
      }
      else
      {
        a2 = 59;
        LOBYTE(a1) = a1 - 1;
      }
    }
    v4 = (unsigned __int8)a1 % 10 + 16 * ((unsigned __int8)a1 / 10);
    v8 = a2 % 10 + 16 * (a2 / 10);
    v11 = v10 % 10 + 16 * (v10 / 10);
    *(_DWORD *)a4 = *(int *)((char *)&dword_5053E0 + 1);
    *(_BYTE *)(a4 + 4) = BYTE1(dword_5053E4);
    *(_WORD *)(a4 + 5) = *(_WORD *)((char *)&dword_5053E4 + 3);
    *(_BYTE *)(a4 + 7) = BYTE1(dword_5053E8);
    if ( v4 != *(_BYTE *)(a4 + 5) )
      v7 = 1;
    if ( v4 != *(_BYTE *)(a4 + 2) )
      ++v7;
    if ( v8 != *(_BYTE *)(a4 + 6) )
      ++v7;
    v5 = v7;
    if ( ((v8 & 0xF) % 10 + 10 * (v8 >> 4) - 2) % 10 + 16 * (((v8 & 0xF) % 10 + 10 * (v8 >> 4) - 2) / 10) != *(unsigned __int8 *)(a4 + 3) )
      v5 = v7 + 1;
    result = v11;
    if ( v11 != *(_BYTE *)(a4 + 7) )
      ++v5;
    if ( v11 != *(_BYTE *)(a4 + 4) )
      ++v5;
    if ( (unsigned __int8)v5 >= 2u )
    {
      result = 0;
      *(_DWORD *)(a4 + 2) = 0;
      *(_WORD *)(a4 + 6) = 0;
      if ( v4 == 3 )
        byte_4F8320 = 1;
    }
  }
  else
  {
    LOBYTE(a1) = (unsigned __int8)a1 % 10 + 16 * ((unsigned __int8)a1 / 10);
    v9 = a2 % 10 + 16 * (a2 / 10);
    v12 = a3 % 10 + 16 * (a3 / 10);
    sub_433630(a1, v9, v12, (_BYTE *)a4, (_BYTE *)(a4 + 2), (_BYTE *)(a4 + 3), (_BYTE *)(a4 + 4));
    *(_BYTE *)(a4 + 1) = 1;
    *(_BYTE *)(a4 + 5) = a1;
    *(_BYTE *)(a4 + 6) = v9;
    *(_BYTE *)(a4 + 7) = v12;
    return v12;
  }
  return result;
}
