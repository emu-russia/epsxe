#include "pch.h"
char sub_42C7E0()
{
  char result; // al
  bool v1; // zf

  result = ++BYTE2(dword_50AF50);
  if ( BYTE2(dword_50AF50) == 75 )
  {
    result = BYTE1(dword_50AF50) + 1;
    v1 = BYTE1(dword_50AF50)++ == 59;
    *(_WORD *)((char *)&dword_50AF50 + 1) = BYTE1(dword_50AF50);
    if ( v1 )
    {
      result = dword_50AF50 + 1;
      LOBYTE(dword_50AF50) = dword_50AF50 + 1;
      LOWORD(dword_50AF50) = (unsigned __int8)dword_50AF50;
    }
  }
  return result;
}
