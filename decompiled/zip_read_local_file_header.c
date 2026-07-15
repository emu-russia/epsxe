#include "pch.h"
int __cdecl zip_read_local_file_header(FILE *Stream, int a2, ZipLocalFileHeaderInMem *a3, unsigned __int8 *Buffer)
{
  int v4; // ecx
  size_t v5; // edi
  int v6; // ebx

  v4 = *(_DWORD *)(a2 + 44);
  v5 = zip_file_size - v4;
  if ( zip_file_size - v4 >= 0x2000 )
    v5 = 0x2000;
  v6 = fseek(Stream, v4, 0);
  if ( v6 )
  {
    zip_print("Error in zipfile %s: couldn't fseek to local file header\n", *(const char **)zip_filename);
    return v6;
  }
  else if ( fread(Buffer, 1u, v5, Stream) == v5 )
  {

    a3->signature = zip_read_uint32_le(Buffer);
    a3->version_needed = zip_read_uint16_le((int)(Buffer + 4));
    a3->general_purpose_bit_flag = zip_read_uint16_le((int)(Buffer + 6));
    a3->compression_method = zip_read_uint16_le((int)(Buffer + 8));
    a3->last_mod_time = zip_read_uint16_le((int)(Buffer + 10));
    a3->last_mod_date = zip_read_uint16_le((int)(Buffer + 12));
    a3->crc32 = zip_read_uint32_le(Buffer + 14);
    a3->compressed_size = zip_read_uint32_le(Buffer + 18);
    a3->uncompressed_size = zip_read_uint32_le(Buffer + 22);
    a3->filename_length = zip_read_uint16_le((int)(Buffer + 26));
    a3->extra_field_length = zip_read_uint16_le((int)(Buffer + 28));
    a3->filename = (char *)(Buffer + 30);
    return 0;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from local file header", *(const char **)zip_filename, v5);
    return -1;
  }
}
