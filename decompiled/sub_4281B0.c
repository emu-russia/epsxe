#include "pch.h"
unsigned int __cdecl sub_4281B0(int a1, int a2)
{
  int v2; // eax
  char *v3; // esi
  LPVOID v4; // ecx
  int v5; // edx
  LPVOID v6; // ebp
  unsigned int v7; // edi
  unsigned int result; // eax
  unsigned int v9; // edx

  if ( (a1 & 0xFFF00000) == 0xBFC00000 )
    v2 = (a1 & 0x7FFFC) + 0x200000;
  else
    v2 = a1 & 0x1FFFFC;
  v3 = (char *)dword_5164C4;
  v4 = dword_5164C0;
  if ( *(LPVOID *)((char *)dword_5164C4 + v2) != dword_5164C0 )
  {
    v5 = ((_BYTE *)dword_5164C0 - (_BYTE *)dword_5164C8) >> 2;
    *(_DWORD *)((char *)dword_5164C4 + v2) = dword_5164C0;
    if ( v5 )
    {
      while ( 1 )
      {
        v3 = (char *)dword_5164C4;
        v4 = dword_5164C0;
        v6 = *(LPVOID *)((char *)dword_5164C4 + v2 - 4);
        v2 -= 4;
        if ( v6 == dword_5164C0 )
          break;
        --v5;
        *(_DWORD *)((char *)dword_5164C4 + v2) = dword_5164C0;
        if ( !v5 )
          goto LABEL_8;
      }
    }
    else
    {
LABEL_8:
      v4 = dword_5164C0;
      v3 = (char *)dword_5164C4;
    }
  }
  if ( (a1 & 0xFFF00000) == 0xBFC00000 )
    v7 = (a1 & 0x7FFFC) + 0x200000;
  else
    v7 = a1 & 0x1FFFFC;
  result = v7;
  v9 = v7 + 4 * a2;
  if ( v7 < v9 )
  {
    while ( 1 )
    {
      *(_DWORD *)&v3[result] = v4;
      result += 4;
      if ( result >= v9 )
        break;
      v4 = dword_5164C0;
      v3 = (char *)dword_5164C4;
    }
  }
  return result;
}
