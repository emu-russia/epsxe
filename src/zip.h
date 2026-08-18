#pragma once

#define ZIP_SLIDING_WINDOW_SIZE     0x8000u   /* 32 KB */
#define ZIP_READ_BUFFER_SIZE        0x2000u   /* 8 KB – used for reading from file */
#define ZIP_MAX_FILENAME_LEN        256
#define ZIP_END_OF_CD_SIGNATURE     0x06054b50u
#define ZIP_LOCAL_FILE_HEADER_SIG   0x04034b50u
#define ZIP_CENTRAL_DIR_HEADER_SIG  0x02014b50u

#pragma pack(push, 1)
typedef struct _ZipLocalFileHeader {
    uint32_t signature;            /* 0x04034b50 */
    uint16_t version_needed;
    uint16_t general_purpose_bit_flag;
    uint16_t compression_method;   /* 0 = stored, 8 = deflated */
    uint16_t last_mod_time;
    uint16_t last_mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_length;
    uint16_t extra_field_length;
    /* сразу после структуры идут: filename (filename_length байт) и extra field (extra_field_length байт) */
} ZipLocalFileHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _ZipCentralDirectoryEntry {
    uint32_t signature;            /* 0x02014b50 */
    uint16_t version_made_by;
    uint16_t version_needed;
    uint16_t general_purpose_bit_flag;
    uint16_t compression_method;
    uint16_t last_mod_time;
    uint16_t last_mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_length;
    uint16_t extra_field_length;
    uint16_t file_comment_length;
    uint16_t disk_number_start;
    uint16_t internal_attributes;
    uint32_t external_attributes;
    uint32_t local_header_offset;  /* смещение до локального заголовка в ZIP-файле */
    /* сразу после структуры: filename (filename_length), extra (extra_field_length), comment (file_comment_length) */
} ZipCentralDirectoryEntry;
#pragma pack(pop)

typedef struct _ZipLocalFileHeaderInMem {
    uint32_t signature;            /* 0x04034b50 */
    uint16_t version_needed;
    uint16_t general_purpose_bit_flag;
    uint16_t compression_method;   /* 0 = stored, 8 = deflated */
    uint16_t last_mod_time;
    uint16_t last_mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_length;
    uint16_t extra_field_length;
    /* сразу после структуры идут: filename (filename_length байт) и extra field (extra_field_length байт) */
    char *filename;
} ZipLocalFileHeaderInMem;

typedef struct _ZipCentralDirectoryEntryInMem {
    uint32_t signature;            /* 0x02014b50 */
    uint16_t version_made_by;
    uint16_t version_needed;
    uint16_t general_purpose_bit_flag;
    uint16_t compression_method;
    uint16_t last_mod_time;
    uint16_t last_mod_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t filename_length;
    uint16_t extra_field_length;
    uint16_t file_comment_length;
    uint16_t disk_number_start;
    uint16_t internal_attributes;
    uint32_t external_attributes;
    uint32_t local_header_offset;  /* смещение до локального заголовка в ZIP-файле */
    /* сразу после структуры: filename (filename_length), extra (extra_field_length), comment (file_comment_length) */
    char *filename;
} ZipCentralDirectoryEntryInMem;
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int Stream;
extern unsigned char byte_4FA350[0x2000];
extern unsigned char byte_4FC350[0x100];
extern unsigned short zip_bit_masks[12];
extern unsigned char zip_central_dir_buffer[0x2000];
extern unsigned int zip_code_length_order[14];
extern unsigned char zip_distance_base[17];
extern unsigned char zip_distance_extra_bits[22];
extern unsigned int zip_file_size;
extern unsigned int zip_filename;
extern unsigned int zip_inflate_bit_buffer;
extern unsigned int zip_inflate_bit_count;
extern unsigned int zip_inflate_dtree;
extern unsigned int zip_inflate_dtree_bits;
extern unsigned int zip_inflate_ltree;
extern unsigned int zip_inflate_ltree_bits;
extern unsigned int zip_inflate_max_memory_used;
extern unsigned int zip_inflate_output_ptr;
extern unsigned int zip_inflate_window_pos;
extern unsigned char zip_length_base[17];
extern unsigned char zip_length_extra_bits[30];
extern unsigned char zip_signature;
extern unsigned int zip_sliding_window;
extern unsigned int zip_static_dtree_max_bits;
extern unsigned int zip_static_ltree_max_bits;
extern unsigned int zipfile_input_buffer;

/* Function prototypes (previously generated in src/_gen) */
int __cdecl zip_build_huffman_tree( _DWORD *a1, unsigned int a2, unsigned int a3, int a4, int a5, _DWORD *a6, unsigned int *a7);
int __cdecl zip_compare_filename_case_insensitive(const char *a1, const char *a2);
unsigned int __cdecl zip_copy_sliding_window_to_output(const void *a1, unsigned int a2);
int __cdecl zip_extract_file(char *FileName, char *arg4, LPVOID *arg8, size_t *a4);
BOOL __cdecl zip_find_end_of_central_dir_signature(int a1, int a2, _DWORD *a3);
int __cdecl zip_free_huffman_tree(int a1);
int __cdecl zip_get_file_size(FILE *Stream, _DWORD *a2);
char *__cdecl zip_get_filename_from_path(const char *a1);
int __cdecl zip_inflate_block(int *a1);
int __cdecl zip_inflate_data_with_trees(int a1, int a2, unsigned int a3, unsigned int a4);
int zip_inflate_file();
int __cdecl zip_load_central_directory(FILE *Stream, const char *arg4, int a3, ZipCentralDirectoryEntry *a2);
int __cdecl zip_load_file(char *FileName);
int __cdecl zip_load_local_file_headers(FILE *Stream, int arg4, ZipCentralDirectoryEntryInMem *a2);
int __cdecl zip_locate_central_dir(FILE *Stream, int *a2);
int __cdecl zip_parse_cd_entry(ZipCentralDirectoryEntry *a1, ZipCentralDirectoryEntryInMem *a2);
int zip_print(char *Format, ...);
int __cdecl zip_read_compressed_data_to_buffer(FILE *Stream, int a2, int a3, LPVOID *a4);
int __cdecl zip_read_local_file_header(FILE *Stream, int a2, ZipLocalFileHeaderInMem *a3, unsigned __int8 *Buffer);
__int16 __cdecl zip_read_uint16_le(int a1);
uint32_t __cdecl zip_read_uint32_le(unsigned __int8 *a1);
