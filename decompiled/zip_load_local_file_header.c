#include "pch.h"
int __cdecl zip_load_local_file_header(FILE *Stream, int a2, int a3)
{
  size_t v3; // esi
  int v5; // ebx
  unsigned __int8 *v6; // ebp
  int v7; // esi
  char v8; // al
  unsigned __int16 v9; // cx
  int v10; // esi
  char *v11; // eax
  char *v12; // edx
  char v13; // cl
  int v14[9]; // [esp+8h] [ebp-124h] BYREF
  _BYTE v15[256]; // [esp+2Ch] [ebp-100h] BYREF

  v3 = *(_DWORD *)(a2 + 12);
  if ( v3 > 0x2000 )
    v3 = 0x2000;
  if ( fseek(Stream, *(_DWORD *)(a2 + 16), 0) )
  {
    zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)zip_filename);
    return -1;
  }
  else if ( fread(byte_4F8350, 1u, v3, Stream) == v3 )
  {
    v5 = 0;
    v6 = (unsigned __int8 *)byte_4F8350;
    while ( v5 < *(unsigned __int16 *)(a2 + 10) )
    {
      zip_parse_cd_entry(v6, a3);
      v7 = 0;
      if ( *(_WORD *)(a3 + 28) )
      {
        do
        {
          if ( v7 >= 254 )
            break;
          v8 = toupper(*(char *)(*(_DWORD *)(a3 + 48) + v7));
          v9 = *(_WORD *)(a3 + 28);
          v15[v7++] = v8;
        }
        while ( v7 < v9 );
      }
      v15[v7] = 0;
      if ( zip_read_local_file_header(Stream, a3, (int)v14, (unsigned __int8 *)&byte_4F8350[0x2000]) )
        zip_print("Error reading 'local file header' in zipfile %s\n", *(const char **)zip_filename);
      if ( v5 < 256 )
      {
        v10 = dword_4FC458;
        v11 = v15;
        v12 = &byte_566980[(dword_4FC458 << 8) - (_DWORD)v15];
        do
        {
          v13 = *v11;
          v11[(_DWORD)v12] = *v11;
          ++v11;
        }
        while ( v13 );
        Size[v10] = v14[6];
        dword_4FC458 = v10 + 1;
      }
      v6 += *(unsigned __int16 *)(a3 + 28) + *(unsigned __int16 *)(a3 + 30) + *(unsigned __int16 *)(a3 + 32) + 46;
      ++v5;
    }
    return -1;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from central directory\n", *(const char **)zip_filename, v3);
    return -1;
  }
}
