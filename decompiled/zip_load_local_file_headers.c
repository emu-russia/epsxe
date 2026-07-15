#include "pch.h"
int __cdecl zip_load_local_file_headers(FILE *Stream, int a2, ZipCentralDirectoryEntryInMem *a3)
{
  size_t v3; // esi
  int v5; // ebx
  ZipCentralDirectoryEntry *v6; // ebp
  int v7; // esi
  char v8; // al
  uint16_t filename_length; // cx
  int v10; // esi
  char *v11; // eax
  char *v12; // edx
  char v13; // cl
  ZipLocalFileHeaderInMem a3a; // [esp+8h] [ebp-124h] BYREF
  _BYTE v15[256]; // [esp+2Ch] [ebp-100h] BYREF

  v3 = *(_DWORD *)(a2 + 12);
  if ( v3 > 0x2000 )
    v3 = 0x2000;
  if ( fseek(Stream, *(_DWORD *)(a2 + 16), 0) )
  {
    zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)zip_filename);
    return -1;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, v3, Stream) == v3 )
  {
    v5 = 0;
    v6 = &zip_central_dir_buffer;
    while ( v5 < *(unsigned __int16 *)(a2 + 10) )
    {
      zip_parse_cd_entry(v6, a3);
      v7 = 0;
      if ( a3->filename_length )
      {
        do
        {
          if ( v7 >= 254 )
            break;
          v8 = toupper(a3->filename[v7]);
          filename_length = a3->filename_length;
          v15[v7++] = v8;
        }
        while ( v7 < filename_length );
      }
      v15[v7] = 0;
      if ( zip_read_local_file_header(Stream, (int)a3, &a3a, byte_4FA350) )
        zip_print("Error reading 'local file header' in zipfile %s\n", *(const char **)zip_filename);
      if ( v5 < 256 )
      {
        v10 = zip_num_entries_loaded;
        v11 = v15;
        v12 = &byte_566980[(zip_num_entries_loaded << 8) - (_DWORD)v15];
        do
        {
          v13 = *v11;
          v11[(_DWORD)v12] = *v11;
          ++v11;
        }
        while ( v13 );
        Size[v10] = a3a.uncompressed_size;
        zip_num_entries_loaded = v10 + 1;
      }
      v6 = (ZipCentralDirectoryEntry *)((char *)v6
                                      + a3->filename_length
                                      + a3->extra_field_length
                                      + a3->file_comment_length
                                      + 46);
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
