#include "pch.h"
int __cdecl zip_load_central_directory(FILE *Stream, const char *arg4, int a3, ZipCentralDirectoryEntry *a2)
{
  int v4; // ebp
  size_t v5; // esi
  int v7; // edi
  char v8; // al
  uint16_t filename_length; // dx
  uint16_t compression_method; // ax
  int v11; // [esp+10h] [ebp-10Ch]
  ZipCentralDirectoryEntry *a1; // [esp+14h] [ebp-108h]
  char v13[256]; // [esp+1Ch] [ebp-100h] BYREF

  v4 = 0;
  v5 = 0x2000;
  if ( *(_DWORD *)(a3 + 12) <= 0x2000u )
    v5 = *(_DWORD *)(a3 + 12);
  if ( fseek(Stream, *(_DWORD *)(a3 + 16), 0) )
  {
    zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)zip_filename);
    return -1;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, v5, Stream) == v5 )
  {
    v11 = 0;
    a1 = &zip_central_dir_buffer;
    while ( v11 < *(unsigned __int16 *)(a3 + 10) )
    {
      zip_parse_cd_entry(a1, (ZipCentralDirectoryEntryInMem *)a2);
      v7 = 0;
      if ( a2->filename_length )
      {
        do
        {
          if ( v7 >= 254 )
            break;
          v8 = toupper(*(char *)(*(uint32_t *)((char *)&a2[1].signature + 2) + v7));
          filename_length = a2->filename_length;
          v13[v7++] = v8;
        }
        while ( v7 < filename_length );
      }
      v13[v7] = 0;
      if ( !zip_compare_filename_case_insensitive(v13, arg4) )
      {
        compression_method = a2->compression_method;
        v4 = 1;
        if ( compression_method && compression_method != 8 )
        {
          v4 = 0;
          zip_print(
            "Error in zipfile %s: compression method for file %s unsupported.\n",
            *(const char **)zip_filename,
            arg4);
          zip_print("Method: $%04x  must be $0000 (Stored) or $0008 (Deflated)\n", a2->compression_method);
        }
        if ( LOBYTE(a2->version_needed) > 0x14u )
        {
          v4 = 0;
          zip_print("Error in zipfile %s: version for file %s too new.\n", *(const char **)zip_filename, arg4);
          zip_print("Version: $%02x must be $14 or less\n", LOBYTE(a2->version_needed));
        }
        if ( HIBYTE(a2->version_needed) )
        {
          v4 = 0;
          zip_print("Error in zipfile %s: OS for file %s not supported.\n", *(const char **)zip_filename, arg4);
          zip_print("OS: $%02x must be $00\n", HIBYTE(a2->version_needed));
        }
        if ( a2->disk_number_start != *(_WORD *)(a3 + 4) )
        {
          v4 = 0;
          zip_print("Error in zipfile %s: zipfile cannot span disks\n", *(const char **)zip_filename);
        }
      }
      a1 = (ZipCentralDirectoryEntry *)((char *)a1
                                      + a2->filename_length
                                      + a2->extra_field_length
                                      + a2->file_comment_length
                                      + 46);
      ++v11;
      if ( v4 )
        return 0;
    }
    return -1;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from central directory\n", *(const char **)zip_filename, v5);
    return -1;
  }
}
