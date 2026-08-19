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
extern unsigned char zip_local_file_header_buffer[0x2000];
extern unsigned char zip_path_buffer[0x100];
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
int zip_extract_file(char *FileName, char *arg4, LPVOID *arg8, size_t *a4);
int zip_load_file(char *FileName);
