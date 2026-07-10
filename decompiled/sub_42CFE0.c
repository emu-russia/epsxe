#include "pch.h"
int __cdecl sub_42CFE0(int a1)
{
  int result; // eax

  result = a1;
  BYTE1(byte_50AF44) = a1;
  byte_50AEC1 = 0;
  byte_50AEC0 = 1;
  if ( a1 == 1 )
    dword_50AE80 = 2;
  return result;
}
