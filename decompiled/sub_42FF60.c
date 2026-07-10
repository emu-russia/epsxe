#include "pch.h"
char __cdecl sub_42FF60(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  unsigned int v4; // esi
  int v5; // ebx
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  unsigned int v9; // ecx
  char *v10; // edi
  char *v11; // esi
  char v12; // cl
  unsigned int v13; // edx
  unsigned int v14; // eax
  unsigned int v15; // ecx
  size_t v16; // edi
  char *v17; // edi
  int v18; // eax

  v4 = sub_42C6D0(a1, a2, a3);
  if ( dword_505400 )
  {
    fseek(dword_505400, 96 * v4, 0);
    fread(&unk_505680, 1u, 0x60u, dword_505400);
    byte_50A1A4 = a1;
    byte_50A1A5 = a2;
    byte_50A1A6 = a3;
  }
  if ( v4 < dword_456D74 || v4 >= dword_456D74 + 8 )
  {
    v13 = dword_456D78;
    v14 = v4 * dword_456D78;
    v15 = 8 * dword_456D78;
    if ( v4 * dword_456D78 < dword_4FD9A8
      && (v14 < dword_4FD9A8 - v15 ? (v16 = 8 * dword_456D78) : (v16 = dword_4FD9A8 - v14), v16) )
    {
      fseek(dword_50A098, dword_4FD9AC + v14, 0);
      fread(&unk_505700, 1u, v16, dword_50A098);
      v13 = dword_456D78;
    }
    else
    {
      memset(&unk_505700, 0, 4 * (v15 >> 2));
    }
    v5 = a4;
    dword_456D74 = v4;
    v17 = (char *)(a4 - v13 + 2352);
    qmemcpy(v17, &unk_505700, 4 * (v13 >> 2));
    v11 = (char *)&unk_505700 + 4 * (v13 >> 2);
    v10 = &v17[4 * (v13 >> 2)];
    v12 = v13;
  }
  else
  {
    v5 = a4;
    v6 = dword_456D78;
    v7 = (char *)&unk_505700 + dword_456D78 * (v4 - dword_456D74);
    v8 = (char *)(a4 - dword_456D78 + 2352);
    v9 = (unsigned int)dword_456D78 >> 2;
    qmemcpy(v8, v7, 4 * ((unsigned int)dword_456D78 >> 2));
    v11 = &v7[4 * v9];
    v10 = &v8[4 * v9];
    v12 = v6;
  }
  qmemcpy(v10, v11, v12 & 3);
  v18 = *(_DWORD *)(v5 + 13);
  if ( !v18 )
  {
    *(_BYTE *)(v5 + 15) = 2;
    *(_BYTE *)(v5 + 12) = a1 % 10 + 16 * (a1 / 10);
    *(_BYTE *)(v5 + 13) = a2 % 10 + 16 * (a2 / 10);
    v18 = (unsigned __int8)(a3 % 10 + 16 * (a3 / 10));
    *(_BYTE *)(v5 + 14) = v18;
  }
  return v18;
}
