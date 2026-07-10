#include "pch.h"
int __cdecl sub_420DB0(unsigned __int8 a1, int a2, char a3)
{
  int v3; // eax
  int v4; // eax
  void *v5; // eax
  int v6; // ecx
  char v7; // dl
  int v8; // ecx
  int v10; // edx
  _BYTE v11[9]; // [esp+4h] [ebp-10h] BYREF

  v3 = dword_456048[a1];
  if ( !v3 )
    goto LABEL_24;
  v4 = v3 - 1;
  if ( v4 )
  {
    if ( v4 == 3 )
    {
      byte_4FC464[(unsigned __int8)byte_516560] = a3;
      if ( a3 == 66 || a3 == 67 )
      {
        if ( dword_4FD8E0[a1] )
        {
          sub_42D0E0(a1, v11);
        }
        else
        {
          sub_42D010(a1, v11);
          *(_DWORD *)&v11[5] = -2139062144;
        }
      }
      switch ( a3 )
      {
        case 'D':
          v5 = dword_4557B0;
          v6 = dword_4557B4;
          v7 = byte_4557B8;
          goto LABEL_17;
        case 'E':
          *(_DWORD *)v11 = dword_4557BC;
          *(_DWORD *)&v11[4] = dword_4557C0;
          v8 = dword_4FD8E0[a1];
          v11[8] = byte_4557C4;
          if ( v8 == 1 )
            v11[5] = 1;
          break;
        case 'F':
          v5 = dword_4557C8;
          v6 = dword_4557CC;
          v7 = byte_4557D0;
          goto LABEL_17;
        case 'G':
          v5 = dword_4557D4;
          v6 = dword_4557D8;
          v7 = byte_4557DC;
          goto LABEL_17;
        case 'L':
          v5 = (void *)dword_4557EC;
          v6 = dword_4557F0;
          v7 = byte_4557F4;
          goto LABEL_17;
        case 'M':
          v5 = dword_4557E0;
          v6 = dword_4557E4;
          v7 = byte_4557E8;
LABEL_17:
          *(_DWORD *)v11 = v5;
          *(_DWORD *)&v11[4] = v6;
          v11[8] = v7;
          break;
        default:
          break;
      }
      v10 = *(_DWORD *)&v11[5];
      *(_DWORD *)a2 = *(_DWORD *)&v11[1];
      *(_DWORD *)(a2 + 4) = v10;
      return a2;
    }
LABEL_24:
    *(_BYTE *)(a2 + 3) = -1;
    *(_BYTE *)(a2 + 2) = -1;
    *(_BYTE *)(a2 + 1) = 90;
    *(_BYTE *)a2 = 65;
    *(_DWORD *)(a2 + 4) = -2139062144;
    return a2 + 4;
  }
  sub_42D010(a1, v11);
  if ( a3 != 66 )
    v11[1] = a3;
  if ( a3 == 69 )
  {
    *(_DWORD *)v11 = dword_4557F8;
    v11[4] = byte_4557FC;
  }
  *(_DWORD *)a2 = *(_DWORD *)&v11[1];
  *(_DWORD *)(a2 + 4) = -2139062144;
  return a2 + 4;
}
