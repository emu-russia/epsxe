#include "pch.h"
char __cdecl ext_CDR_verify_subchannel_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  int v4; // ecx
  char v5; // bl
  char v6; // dl
  char result; // al
  char v8; // [esp+Bh] [ebp-1h]
  unsigned __int8 v9; // [esp+14h] [ebp+8h]
  unsigned __int8 v10; // [esp+14h] [ebp+8h]
  unsigned __int8 v11; // [esp+18h] [ebp+Ch]
  char v12; // [esp+18h] [ebp+Ch]
  unsigned __int8 v13; // [esp+18h] [ebp+Ch]

  *(_DWORD *)a4 = 0;
  *(_DWORD *)(a4 + 4) = 0;
  v8 = 0;
  if ( CDRgetBufferSub
    && ((v4 = CDRgetBufferSub(), !extsubchanhle) || (dword_50C280[0] & 0x1F000000) != 0x1F000000 || a1 == 3)
    && v4 )
  {
    if ( a3 )
    {
      v11 = a3 - 1;
    }
    else
    {
      v11 = 74;
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
    v5 = a1 % 10 + 16 * (a1 / 10);
    v9 = a2 % 10 + 16 * (a2 / 10);
    v12 = v11 % 10 + 16 * (v11 / 10);
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
    result = v12;
    if ( v12 != *(_BYTE *)(v4 + 21) )
      ++v6;
    if ( v12 != *(_BYTE *)(v4 + 17) )
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
    v10 = a2 % 10 + 16 * (a2 / 10);
    v13 = a3 % 10 + 16 * (a3 / 10);
    ext_CDR_lba_to_msf_with_track(
      a1 % 10 + 16 * (a1 / 10),
      v10,
      v13,
      (_BYTE *)a4,
      (_BYTE *)(a4 + 2),
      (_BYTE *)(a4 + 3),
      (_BYTE *)(a4 + 4));
    *(_BYTE *)(a4 + 1) = 1;
    *(_BYTE *)(a4 + 5) = a1 % 10 + 16 * (a1 / 10);
    *(_BYTE *)(a4 + 6) = v10;
    *(_BYTE *)(a4 + 7) = v13;
    return v13;
  }
  return result;
}
