#include "pch.h"
int __cdecl zip_read_local_file_header(FILE *Stream, int a2, int a3, unsigned __int8 *Buffer)
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
    zip_print("Error in zipfile %s: couldn't fseek to local file header\n", *(const char **)zip_filename);
    return v6;
  }
  else if ( fread(Buffer, 1u, v5, Stream) == v5 )
  {
    *(_DWORD *)a3 = zip_read_uint32_le(Buffer);
    *(_WORD *)(a3 + 4) = zip_read_uint16_le((int)(Buffer + 4));
    *(_WORD *)(a3 + 6) = zip_read_uint16_le((int)(Buffer + 6));
    *(_WORD *)(a3 + 8) = zip_read_uint16_le((int)(Buffer + 8));
    *(_WORD *)(a3 + 10) = zip_read_uint16_le((int)(Buffer + 10));
    *(_WORD *)(a3 + 12) = zip_read_uint16_le((int)(Buffer + 12));
    *(_DWORD *)(a3 + 16) = zip_read_uint32_le(Buffer + 14);
    *(_DWORD *)(a3 + 20) = zip_read_uint32_le(Buffer + 18);
    *(_DWORD *)(a3 + 24) = zip_read_uint32_le(Buffer + 22);
    *(_WORD *)(a3 + 28) = zip_read_uint16_le((int)(Buffer + 26));
    *(_WORD *)(a3 + 30) = zip_read_uint16_le((int)(Buffer + 28));
    *(_DWORD *)(a3 + 32) = Buffer + 30;
    return 0;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from local file header", *(const char **)zip_filename, v5);
    return -1;
  }
}
