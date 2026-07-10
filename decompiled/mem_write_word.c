#include "pch.h"
int __cdecl sub_41D0B0(unsigned int a1, int a2)
{
  int result; // eax
  int v3; // ecx
  LPVOID v4; // edi

  dword_50C270 -= 4;
  result = a1;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 >= 0x1000u )
    {
      return hw_reg_write_word(a1, a2);
    }
    else
    {
      *(int *)((char *)&dcache + (a1 & 0xFFF)) = a2;
      return a1 & 0xFFF;
    }
  }
  else if ( (dword_50C2A4 & 0x10000) == 0 )
  {
    *(_DWORD *)((unsigned __int16)a1 + mem_hooks[HIWORD(a1)]) = a2;
    if ( dword_5164C0 )
    {
      result = (a1 & 0xFFF00000) == 0xBFC00000 ? (a1 & 0x7FFFC) + 0x200000 : a1 & 0x1FFFFC;
      if ( *(LPVOID *)((char *)dword_5164C4 + result) != dword_5164C0 )
      {
        v3 = ((_BYTE *)dword_5164C0 - (_BYTE *)dword_5164C8) >> 2;
        for ( *(_DWORD *)((char *)dword_5164C4 + result) = dword_5164C0;
              v3;
              *(_DWORD *)((char *)dword_5164C4 + result) = dword_5164C0 )
        {
          v4 = *(LPVOID *)((char *)dword_5164C4 + result - 4);
          result -= 4;
          if ( v4 == dword_5164C0 )
            break;
          --v3;
        }
      }
    }
  }
  return result;
}
