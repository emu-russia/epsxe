#include "pch.h"
BOOL __cdecl sub_43DF70(int a1)
{
  unsigned int v1; // edi
  unsigned int v2; // edx
  unsigned __int16 *v3; // eax
  int v4; // ecx
  unsigned __int16 v5; // si
  unsigned __int16 *v6; // eax
  int v7; // ecx
  unsigned __int16 v8; // bp
  unsigned __int16 *v9; // ecx
  int v10; // eax
  unsigned __int16 v11; // si
  unsigned int v12; // edi

  v1 = 0;
  v2 = 0;
  v3 = (unsigned __int16 *)(a1 + 140);
  v4 = 7;
  do
  {
    v5 = *v3;
    v3 += 2;
    v2 += v5;
    --v4;
  }
  while ( v4 );
  v6 = (unsigned __int16 *)(a1 + 168);
  v7 = 121;
  do
  {
    v8 = *v6;
    v6 += 2;
    v1 += v8;
    --v7;
  }
  while ( v7 );
  v9 = (unsigned __int16 *)(a1 + 652);
  v10 = 128;
  do
  {
    v11 = *v9;
    v9 += 2;
    v2 += v11;
    --v10;
  }
  while ( v10 );
  v12 = v1 >> 2;
  *(_BYTE *)(a1 + 28) = v2 <= v12;
  return v2 <= v12;
}
