#pragma once

/**
 * \file zip.h
 * \brief Declarations for the ZIP archive reader used to load ROM/demo images.
 *
 * Reads ZIP archives (stored or deflated entries) containing PS-X EXE/PLL
 * demos: locates the end-of-central-directory record, parses the central
 * directory and local file headers, and inflates the selected entry into
 * memory.
 */

#define ZIP_SLIDING_WINDOW_SIZE     0x8000u   /* 32 KB */
#define ZIP_READ_BUFFER_SIZE        0x2000u   /* 8 KB – used for reading from file */
#define ZIP_MAX_FILENAME_LEN        256
#define ZIP_END_OF_CD_SIGNATURE     0x06054b50u
#define ZIP_LOCAL_FILE_HEADER_SIG   0x04034b50u
#define ZIP_CENTRAL_DIR_HEADER_SIG  0x02014b50u

#pragma pack(push, 1)
/**
 * \brief On-disk ZIP local file header (start of a file entry in the archive).
 */
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
/**
 * \brief On-disk ZIP central directory entry (one per file in the archive).
 */
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

/**
 * \brief In-memory ZIP local file header (with a pointer to the entry filename).
 */
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

/**
 * \brief In-memory ZIP central directory entry (with a pointer to the entry filename).
 */
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
/** \brief Global ZIP stream handle (a decompilation leftover; the ZIP reader functions take their FILE* explicitly). */
extern unsigned int Stream;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Extracts a named entry from a ZIP archive into a newly allocated buffer.
 *
 * Opens the archive, searches the central directory for \p search_name
 * (case-insensitive), reads the local file header and either copies the
 * stored data or inflates the deflated data into a malloc'd buffer.
 *
 * \param FileName    Path of the ZIP file.
 * \param search_name Name of the entry to extract.
 * \param out_data    Receives a pointer to the malloc'd uncompressed data.
 * \param out_size    Receives the uncompressed size in bytes.
 * \return 0 on success, non-zero on error.
 */
int zip_extract_file(char *FileName, char *search_name, LPVOID *out_data, size_t *out_size);
/**
 * \brief Loads the central directory and local file headers of a ZIP archive into memory.
 *
 * Opens the archive, locates the end-of-central-directory record and fills
 * zip_entry_names / zip_num_entries_loaded with the entries found.
 *
 * \param FileName Path of the ZIP file.
 * \return 0 on success, non-zero on error.
 */
int zip_load_file(char *FileName);
