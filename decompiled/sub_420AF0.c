#include "pch.h"
int __cdecl sub_420AF0(FILE *Stream, int *a2)
{
  size_t v2; // esi
  FILE *v3; // ebx
  int v4; // edi
  BOOL v6; // ebx
  char *v7; // esi
  int v8; // eax
  int *v9; // edi

  v2 = ElementCount;
  if ( (int)ElementCount > 0x2000 )
    v2 = 0x2000;
  v3 = Stream;
  v4 = fseek(Stream, -v2, 2);
  if ( v4 )
  {
    sub_420210("Error in zipfile %s: fseek failed\n", *(const char **)ArgList);
    return v4;
  }
  else if ( fread(byte_4F8350, 1u, v2, v3) == v2 )
  {
    v6 = sub_420C20((int)byte_4F8350, v2, &Stream);
    if ( v6 )
    {
      sub_420210("Error in zipfile %s: couldn't find 'end of central dir' signature\n", *(const char **)ArgList);
      return v6;
    }
    else
    {
      v7 = &byte_4F8350[(_DWORD)Stream];
      v8 = sub_420CC0((unsigned __int8 *)&byte_4F8350[(_DWORD)Stream]);
      v9 = a2;
      *a2 = v8;
      *((_WORD *)v9 + 2) = sub_420CB0((int)(v7 + 4));
      *((_WORD *)v9 + 3) = sub_420CB0((int)(v7 + 6));
      *((_WORD *)v9 + 4) = sub_420CB0((int)(v7 + 8));
      *((_WORD *)v9 + 5) = sub_420CB0((int)(v7 + 10));
      v9[3] = sub_420CC0((unsigned __int8 *)v7 + 12);
      v9[4] = sub_420CC0((unsigned __int8 *)v7 + 16);
      *((_WORD *)v9 + 10) = sub_420CB0((int)(v7 + 20));
      return 0;
    }
  }
  else
  {
    sub_420210("Error in zipfile %s: couldn't read %ld bytes from end of file\n", *(const char **)ArgList, v2);
    return -1;
  }
}
