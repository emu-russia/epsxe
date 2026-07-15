#include "pch.h"
int __cdecl zip_parse_cd_entry(ZipCentralDirectoryEntry *a1, ZipCentralDirectoryEntryInMem *a2)
{
  int result; // eax

  a2->signature = zip_read_uint32_le((unsigned __int8 *)a1);
  a2->version_made_by = a1->version_made_by;
  a2->version_needed = a1->version_needed;
  a2->general_purpose_bit_flag = zip_read_uint16_le((int)&a1->general_purpose_bit_flag);
  a2->compression_method = zip_read_uint16_le((int)&a1->compression_method);
  a2->last_mod_time = zip_read_uint16_le((int)&a1->last_mod_time);
  a2->last_mod_date = zip_read_uint16_le((int)&a1->last_mod_date);
  a2->crc32 = zip_read_uint32_le((unsigned __int8 *)&a1->crc32);
  a2->compressed_size = zip_read_uint32_le((unsigned __int8 *)&a1->compressed_size);
  a2->uncompressed_size = zip_read_uint32_le((unsigned __int8 *)&a1->uncompressed_size);
  a2->filename_length = zip_read_uint16_le((int)&a1->filename_length);
  a2->extra_field_length = zip_read_uint16_le((int)&a1->extra_field_length);
  a2->file_comment_length = zip_read_uint16_le((int)&a1->file_comment_length);
  a2->disk_number_start = zip_read_uint16_le((int)&a1->disk_number_start);
  a2->internal_attributes = zip_read_uint16_le((int)&a1->internal_attributes);
  a2->external_attributes = zip_read_uint32_le((unsigned __int8 *)&a1->external_attributes);
  result = zip_read_uint32_le((unsigned __int8 *)&a1->local_header_offset);
  a2->filename = (char *)&a1[1];
  a2->local_header_offset = result;
  return result;
}
