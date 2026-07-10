#include "pch.h"
_WORD *__cdecl sub_43C600(int a1)
{
  int v1; // ecx
  _WORD *v2; // eax
  _WORD *v3; // eax
  int v4; // ecx
  _WORD *result; // eax
  int v6; // ecx

  v1 = 286;
  v2 = (_WORD *)(a1 + 140);
  do
  {
    *v2 = 0;
    v2 += 2;
    --v1;
  }
  while ( v1 );
  v3 = (_WORD *)(a1 + 2432);
  v4 = 30;
  do
  {
    *v3 = 0;
    v3 += 2;
    --v4;
  }
  while ( v4 );
  result = (_WORD *)(a1 + 2676);
  v6 = 19;
  do
  {
    *result = 0;
    result += 2;
    --v6;
  }
  while ( v6 );
  *(_DWORD *)(a1 + 5796) = 0;
  *(_DWORD *)(a1 + 5792) = 0;
  *(_DWORD *)(a1 + 5800) = 0;
  *(_DWORD *)(a1 + 5784) = 0;
  *(_WORD *)(a1 + 1164) = 1;
  return result;
}
