#include "pch.h"
int __cdecl zip_locate_central_dir(FILE *Stream, int *a2)
{
  size_t v2; // esi
  FILE *v3; // ebx
  int v4; // edi
  BOOL v6; // ebx
  char *v7; // esi
  int uint32_le; // eax
  int *v9; // edi

  v2 = ElementCount;
  if ( (int)ElementCount > 0x2000 )
    v2 = 0x2000;
  v3 = Stream;
  v4 = fseek(Stream, -v2, 2);
  if ( v4 )
  {
    zip_print("Error in zipfile %s: fseek failed\n", *(const char **)zip_filename);
    return v4;
  }
  else if ( fread(byte_4F8350, 1u, v2, v3) == v2 )
  {
    v6 = zip_check_signature_PK((int)byte_4F8350, v2, &Stream);
    if ( v6 )
    {
      zip_print("Error in zipfile %s: couldn't find 'end of central dir' signature\n", *(const char **)zip_filename);
      return v6;
    }
    else
    {
      v7 = &byte_4F8350[(_DWORD)Stream];
      uint32_le = zip_read_uint32_le((unsigned __int8 *)&byte_4F8350[(_DWORD)Stream]);
      v9 = a2;
      *a2 = uint32_le;
      *((_WORD *)v9 + 2) = zip_read_uint16_le((int)(v7 + 4));
      *((_WORD *)v9 + 3) = zip_read_uint16_le((int)(v7 + 6));
      *((_WORD *)v9 + 4) = zip_read_uint16_le((int)(v7 + 8));
      *((_WORD *)v9 + 5) = zip_read_uint16_le((int)(v7 + 10));
      v9[3] = zip_read_uint32_le((unsigned __int8 *)v7 + 12);
      v9[4] = zip_read_uint32_le((unsigned __int8 *)v7 + 16);
      *((_WORD *)v9 + 10) = zip_read_uint16_le((int)(v7 + 20));
      return 0;
    }
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from end of file\n", *(const char **)zip_filename, v2);
    return -1;
  }
}
