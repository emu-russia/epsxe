#include "pch.h"
int sub_429C30()
{
  int v0; // edi
  int v1; // esi
  int v2; // edx
  int v3; // ecx
  int v4; // eax
  int v5; // esi
  int v6; // edx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int result; // eax

  v0 = 0;
  v1 = 0;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  do
  {
    dword_4FD050[v4] = v3 >> 12;
    dword_4FCC50[v4] = v2 >> 12;
    dword_4FD450[v4] = v1 >> 12;
    dword_4FC850[v4] = v0 >> 12;
    v3 += 5743;
    v2 -= 1408;
    v1 -= 2925;
    v0 += 7258;
    ++v4;
  }
  while ( v3 < 735104 );
  v5 = -929024;
  v6 = -735104;
  v7 = 374400;
  v8 = 180224;
  v9 = 0;
  do
  {
    dword_4FD250[v9] = v6 >> 12;
    dword_4FCE50[v9] = v8 >> 12;
    dword_4FD650[v9] = v7 >> 12;
    dword_4FCA50[v9] = v5 >> 12;
    v8 -= 1408;
    v6 += 5743;
    v5 += 7258;
    v7 -= 2925;
    ++v9;
  }
  while ( v8 > 0 );
  for ( result = 0; result < 256; ++result )
  {
    byte_4FC550[result] = 0;
    byte_4FC650[result] = result;
    byte_4FC750[result] = -1;
  }
  return result;
}
