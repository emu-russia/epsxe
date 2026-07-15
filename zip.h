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