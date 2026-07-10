#include "pch.h"
int __cdecl sub_4203E0(FILE *Stream, int a2, int a3, unsigned __int8 *Buffer)
{
  int v4; // ecx
  size_t v5; // edi
  int v6; // ebx

  v4 = *(_DWORD *)(a2 + 44);
  v5 = ElementCount - v4;
  if ( ElementCount - v4 >= 0x2000 )
    v5 = 0x2000;
  v6 = fseek(Stream, v4, 0);
  if ( v6 )
  {
    sub_420210("Error in zipfile %s: couldn't fseek to local file header\n", *(const char **)ArgList);
    return v6;
  }
  else if ( fread(Buffer, 1u, v5, Stream) == v5 )
  {
    *(_DWORD *)a3 = sub_420CC0(Buffer);
    *(_WORD *)(a3 + 4) = sub_420CB0((int)(Buffer + 4));
    *(_WORD *)(a3 + 6) = sub_420CB0((int)(Buffer + 6));
    *(_WORD *)(a3 + 8) = sub_420CB0((int)(Buffer + 8));
    *(_WORD *)(a3 + 10) = sub_420CB0((int)(Buffer + 10));
    *(_WORD *)(a3 + 12) = sub_420CB0((int)(Buffer + 12));
    *(_DWORD *)(a3 + 16) = sub_420CC0(Buffer + 14);
    *(_DWORD *)(a3 + 20) = sub_420CC0(Buffer + 18);
    *(_DWORD *)(a3 + 24) = sub_420CC0(Buffer + 22);
    *(_WORD *)(a3 + 28) = sub_420CB0((int)(Buffer + 26));
    *(_WORD *)(a3 + 30) = sub_420CB0((int)(Buffer + 28));
    *(_DWORD *)(a3 + 32) = Buffer + 30;
    return 0;
  }
  else
  {
    sub_420210("Error in zipfile %s: couldn't read %ld bytes from local file header", *(const char **)ArgList, v5);
    return -1;
  }
}
