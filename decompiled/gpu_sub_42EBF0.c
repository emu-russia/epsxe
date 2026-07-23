#include "pch.h"
_BYTE *__cdecl sub_42EBF0(char *a1, int a2)
{
  char *v2; // esi
  char *v3; // edx
  int v4; // ebp
  int v5; // edi
  unsigned __int8 v6; // cl
  _BYTE *v7; // esi
  unsigned __int8 v8; // cl
  char v9; // cl
  int v10; // edx
  char *v11; // eax
  int v12; // edx
  _BYTE *v13; // eax
  _BYTE *result; // eax
  int v15; // edx
  _BYTE *v16; // eax

  v2 = a1 + 309;
  gpu_draw_text_on_screen("FREE SLOT", a1);
  v3 = &byte_4560D0[120 * a2];
  v4 = 20;
  do
  {
    v5 = 6;
    do
    {
      gpu_sub_42E940(v2, (unsigned __int8)*v3 >> 6);
      v7 = v2 + 3;
      gpu_sub_42E940(v7, (v6 >> 4) & 3);
      v7 += 3;
      gpu_sub_42E940(v7, (v8 >> 2) & 3);
      v7 += 3;
      gpu_sub_42E940(v7, v9 & 3);
      v2 = v7 + 3;
      v3 = (char *)(v10 + 1);
      --v5;
    }
    while ( v5 );
    v2 += 312;
    --v4;
  }
  while ( v4 );
  v11 = a1;
  v12 = 128;
  do
  {
    v11[36480] = 0;
    *v11 = 0;
    v13 = v11 + 1;
    v13[36480] = 0;
    *v13++ = 0;
    v13[36480] = -1;
    *v13 = -1;
    v11 = v13 + 1;
    --v12;
  }
  while ( v12 );
  result = a1;
  v15 = 96;
  do
  {
    result[381] = 0;
    *result = 0;
    v16 = result + 1;
    v16[381] = 0;
    *v16++ = 0;
    v16[381] = -1;
    *v16 = -1;
    result = v16 + 382;
    --v15;
  }
  while ( v15 );
  return result;
}
