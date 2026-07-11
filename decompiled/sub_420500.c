#include "pch.h"
int __cdecl sub_420500(FILE *Stream, const char *a2, int a3, int a4)
{
  int v4; // ebp
  size_t v5; // esi
  int v7; // edi
  char v8; // al
  unsigned __int16 v9; // dx
  __int16 v10; // ax
  int v11; // [esp+10h] [ebp-10Ch]
  unsigned __int8 *v12; // [esp+14h] [ebp-108h]
  char v13[256]; // [esp+1Ch] [ebp-100h] BYREF

  v4 = 0;
  v5 = 0x2000;
  if ( *(_DWORD *)(a3 + 12) <= 0x2000u )
    v5 = *(_DWORD *)(a3 + 12);
  if ( fseek(Stream, *(_DWORD *)(a3 + 16), 0) )
  {
    sub_420210("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)ArgList);
    return -1;
  }
  else if ( fread(byte_4F8350, 1u, v5, Stream) == v5 )
  {
    v11 = 0;
    v12 = (unsigned __int8 *)byte_4F8350;
    while ( v11 < *(unsigned __int16 *)(a3 + 10) )
    {
      sub_420A00(v12, a4);
      v7 = 0;
      if ( *(_WORD *)(a4 + 28) )
      {
        do
        {
          if ( v7 >= 254 )
            break;
          v8 = toupper(*(char *)(*(_DWORD *)(a4 + 48) + v7));
          v9 = *(_WORD *)(a4 + 28);
          v13[v7++] = v8;
        }
        while ( v7 < v9 );
      }
      v13[v7] = 0;
      if ( !sub_4208D0(v13, a2) )
      {
        v10 = *(_WORD *)(a4 + 10);
        v4 = 1;
        if ( v10 && v10 != 8 )
        {
          v4 = 0;
          sub_420210("Error in zipfile %s: compression method for file %s unsupported.\n", *(const char **)ArgList, a2);
          sub_420210("Method: $%04x  must be $0000 (Stored) or $0008 (Deflated)\n", *(unsigned __int16 *)(a4 + 10));
        }
        if ( *(_BYTE *)(a4 + 6) > 0x14u )
        {
          v4 = 0;
          sub_420210("Error in zipfile %s: version for file %s too new.\n", *(const char **)ArgList, a2);
          sub_420210("Version: $%02x must be $14 or less\n", *(unsigned __int8 *)(a4 + 6));
        }
        if ( *(_BYTE *)(a4 + 7) )
        {
          v4 = 0;
          sub_420210("Error in zipfile %s: OS for file %s not supported.\n", *(const char **)ArgList, a2);
          sub_420210("OS: $%02x must be $00\n", *(unsigned __int8 *)(a4 + 7));
        }
        if ( *(_WORD *)(a4 + 34) != *(_WORD *)(a3 + 4) )
        {
          v4 = 0;
          sub_420210("Error in zipfile %s: zipfile cannot span disks\n", *(const char **)ArgList);
        }
      }
      v12 += *(unsigned __int16 *)(a4 + 28) + *(unsigned __int16 *)(a4 + 30) + *(unsigned __int16 *)(a4 + 32) + 46;
      ++v11;
      if ( v4 )
        return 0;
    }
    return -1;
  }
  else
  {
    sub_420210("Error in zipfile %s: couldn't read %ld bytes from central directory\n", *(const char **)ArgList, v5);
    return -1;
  }
}
