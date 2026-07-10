#include "pch.h"
int sub_40C560()
{
  int v0; // ecx
  int result; // eax
  _BYTE *v2; // esi
  int v3; // ebp
  int v4; // edi
  char v5; // dl

  v0 = 0;
  result = 0;
  v2 = &unk_45B900;
  v3 = 256;
  do
  {
    v4 = 128;
    do
    {
      v5 = byte_44F720[(unsigned __int8)v0++] + byte_44F720[(unsigned __int8)result--];
      *v2++ = v5;
      --v4;
    }
    while ( v4 );
    --result;
    --v3;
  }
  while ( v3 );
  return result;
}
