#pragma once

/**
 * \file zip.h
 * \brief ZIP archive reader used to load ROM/demo (EXE/PLL) images.
 *
 * Reads ZIP archives whose entries are stored or deflated (method 0 or 8):
 * locates the end-of-central-directory record in the tail of the file,
 * parses the central directory and the local file headers, and either
 * copies the stored data or inflates the deflated entry into a freshly
 * allocated buffer.
 *
 * All source files of the module are plain C; the declaration below is
 * intentionally C-compatible (no C++ constructs).
 */

/* ---------------------------------------------------------------------------
 * Limits and on-disk signatures
 * ------------------------------------------------------------------------- */

/** \brief Size of the inflate sliding window (32 KB), as required by DEFLATE. */
#define ZIP_SLIDING_WINDOW_SIZE     0x8000u
/** \brief Size of the file-read buffer (8 KB) used when scanning the archive tail and the central directory. */
#define ZIP_READ_BUFFER_SIZE        0x2000u
/** \brief Maximum accepted entry filename length in bytes. */
#define ZIP_MAX_FILENAME_LEN        256
/** \brief "PK\x05\x06" - signature of the end-of-central-directory record. */
#define ZIP_END_OF_CD_SIGNATURE     0x06054b50u
/** \brief "PK\x03\x04" - signature of a local file header (start of a file entry). */
#define ZIP_LOCAL_FILE_HEADER_SIG   0x04034b50u
/** \brief "PK\x01\x02" - signature of a central directory entry. */
#define ZIP_CENTRAL_DIR_HEADER_SIG  0x02014b50u

/* ---------------------------------------------------------------------------
 * On-disk ZIP structures (packed, little-endian fields as stored in the file)
 * ------------------------------------------------------------------------- */

#pragma pack(push, 1)
/**
 * \brief On-disk ZIP local file header; the start of each file entry.
 *
 * Immediately followed by the entry filename (filename_length bytes) and
 * the optional extra field (extra_field_length bytes); the entry data
 * starts right after them.
 */
typedef struct _ZipLocalFileHeader {
    uint32_t signature;                  /**< Local file header signature (ZIP_LOCAL_FILE_HEADER_SIG). */
    uint16_t version_needed;             /**< Minimum ZIP version needed to extract the entry. */
    uint16_t general_purpose_bit_flag;   /**< General purpose bit flag (bit 0: encrypted, bit 3: sizes in data descriptor). */
    uint16_t compression_method;         /**< Compression method: 0 = stored, 8 = deflated. */
    uint16_t last_mod_time;              /**< DOS last modification time. */
    uint16_t last_mod_date;              /**< DOS last modification date. */
    uint32_t crc32;                      /**< CRC-32 of the uncompressed data. */
    uint32_t compressed_size;            /**< Size of the stored (compressed) data in bytes. */
    uint32_t uncompressed_size;          /**< Size of the uncompressed data in bytes. */
    uint16_t filename_length;            /**< Length of the entry filename that follows this header. */
    uint16_t extra_field_length;         /**< Length of the extra field that follows the filename. */
} ZipLocalFileHeader;
#pragma pack(pop)

#pragma pack(push, 1)
/**
 * \brief On-disk ZIP central directory entry; one per file in the archive.
 *
 * Immediately followed by the entry filename (filename_length bytes),
 * the extra field (extra_field_length bytes) and the entry comment
 * (file_comment_length bytes).
 */
typedef struct _ZipCentralDirectoryEntry {
    uint32_t signature;                  /**< Central directory entry signature (ZIP_CENTRAL_DIR_HEADER_SIG). */
    uint16_t version_made_by;            /**< Version and host OS that created the entry (low byte: version, high byte: OS). */
    uint16_t version_needed;             /**< Minimum ZIP version needed to extract the entry. */
    uint16_t general_purpose_bit_flag;   /**< General purpose bit flag. */
    uint16_t compression_method;         /**< Compression method: 0 = stored, 8 = deflated. */
    uint16_t last_mod_time;              /**< DOS last modification time. */
    uint16_t last_mod_date;              /**< DOS last modification date. */
    uint32_t crc32;                      /**< CRC-32 of the uncompressed data. */
    uint32_t compressed_size;            /**< Size of the stored (compressed) data in bytes. */
    uint32_t uncompressed_size;          /**< Size of the uncompressed data in bytes. */
    uint16_t filename_length;            /**< Length of the entry filename that follows this entry. */
    uint16_t extra_field_length;         /**< Length of the extra field that follows the filename. */
    uint16_t file_comment_length;        /**< Length of the entry comment that follows the extra field. */
    uint16_t disk_number_start;          /**< Number of the disk holding the start of the entry data. */
    uint16_t internal_attributes;        /**< Internal file attributes. */
    uint32_t external_attributes;        /**< External file attributes (host OS dependent). */
    uint32_t local_header_offset;        /**< File offset of the entry's local file header. */
} ZipCentralDirectoryEntry;
#pragma pack(pop)

#pragma pack(push, 1)
/**
 * \brief On-disk ZIP end-of-central-directory record; the last record of the archive.
 *
 * Located by scanning the tail of the archive for the "PK\x05\x06"
 * signature; its fields describe the whole archive (multi-disk state,
 * entry counts and the position of the central directory).
 */
typedef struct _ZipEndOfCentralDirectory {
    uint32_t signature;                  /**< End-of-central-directory signature (ZIP_END_OF_CD_SIGNATURE). */
    uint16_t disk_number;                /**< Number of the disk this record was found on. */
    uint16_t cd_start_disk;              /**< Number of the disk where the central directory starts. */
    uint16_t entries_this_disk;          /**< Number of central directory entries on this disk. */
    uint16_t total_entries;              /**< Total number of central directory entries. */
    uint32_t central_dir_size;           /**< Size of the central directory in bytes. */
    uint32_t central_dir_offset;         /**< File offset of the start of the central directory. */
    uint16_t comment_length;             /**< Length of the archive comment that follows this record. */
} ZipEndOfCentralDirectory;
#pragma pack(pop)

/* ---------------------------------------------------------------------------
 * In-memory ZIP structures (fields re-read little-endian, filename resolved)
 * ------------------------------------------------------------------------- */

/**
 * \brief In-memory copy of a ZIP local file header.
 *
 * Same fields as ZipLocalFileHeader, but with a pointer to the entry
 * filename instead of the filename_length/extra_field_length byte runs.
 */
typedef struct _ZipLocalFileHeaderInMem {
    uint32_t signature;                  /**< Local file header signature (ZIP_LOCAL_FILE_HEADER_SIG). */
    uint16_t version_needed;             /**< Minimum ZIP version needed to extract the entry. */
    uint16_t general_purpose_bit_flag;   /**< General purpose bit flag. */
    uint16_t compression_method;         /**< Compression method: 0 = stored, 8 = deflated. */
    uint16_t last_mod_time;              /**< DOS last modification time. */
    uint16_t last_mod_date;              /**< DOS last modification date. */
    uint32_t crc32;                      /**< CRC-32 of the uncompressed data. */
    uint32_t compressed_size;            /**< Size of the stored (compressed) data in bytes. */
    uint32_t uncompressed_size;          /**< Size of the uncompressed data in bytes. */
    uint16_t filename_length;            /**< Length of the entry filename. */
    uint16_t extra_field_length;         /**< Length of the extra field. */
    char *filename;                      /**< Pointer to the entry filename (into the header read buffer). */
} ZipLocalFileHeaderInMem;

/**
 * \brief In-memory copy of a ZIP central directory entry.
 *
 * Same fields as ZipCentralDirectoryEntry, but with a pointer to the
 * entry filename (into the central directory read buffer) instead of the
 * filename_length/extra_field_length/file_comment_length byte runs.
 */
typedef struct _ZipCentralDirectoryEntryInMem {
    uint32_t signature;                  /**< Central directory entry signature (ZIP_CENTRAL_DIR_HEADER_SIG). */
    uint16_t version_made_by;            /**< Version and host OS that created the entry. */
    uint16_t version_needed;             /**< Minimum ZIP version needed to extract the entry. */
    uint16_t general_purpose_bit_flag;   /**< General purpose bit flag. */
    uint16_t compression_method;         /**< Compression method: 0 = stored, 8 = deflated. */
    uint16_t last_mod_time;              /**< DOS last modification time. */
    uint16_t last_mod_date;              /**< DOS last modification date. */
    uint32_t crc32;                      /**< CRC-32 of the uncompressed data. */
    uint32_t compressed_size;            /**< Size of the stored (compressed) data in bytes. */
    uint32_t uncompressed_size;          /**< Size of the uncompressed data in bytes. */
    uint16_t filename_length;            /**< Length of the entry filename. */
    uint16_t extra_field_length;         /**< Length of the extra field. */
    uint16_t file_comment_length;        /**< Length of the entry comment. */
    uint16_t disk_number_start;          /**< Number of the disk holding the start of the entry data. */
    uint16_t internal_attributes;        /**< Internal file attributes. */
    uint32_t external_attributes;        /**< External file attributes. */
    uint32_t local_header_offset;        /**< File offset of the entry's local file header. */
    char *filename;                      /**< Pointer to the entry filename (into the central directory read buffer). */
} ZipCentralDirectoryEntryInMem;

/* ---------------------------------------------------------------------------
 * Public variables
 * ------------------------------------------------------------------------- */

/**
 * \brief Names of the ZIP entries loaded by zip_load_file().
 *
 * One 256-byte slot per entry (zip_entry_names[slot << 8]), upper-cased
 * and NUL-terminated; the number of valid slots is zip_num_entries_loaded.
 * Filled by zip_load_file(), read by the demo loader (loader.c).
 */
extern unsigned char zip_entry_names[0x10000];

/** \brief Number of ZIP entries loaded by the last zip_load_file() call (max 256). */
extern unsigned int zip_num_entries_loaded;

/**
 * \brief Shared global stream handle (a decompilation leftover).
 *
 * Declared here for compatibility with the decompiled sources; the CD-ROM
 * cores (cdrom_w2k.c / cdrom_w9x.c) use it as their FILE* handle, while
 * the ZIP reader passes FILE* explicitly to its functions.
 */
extern unsigned int Stream;

/* ---------------------------------------------------------------------------
 * Public functions
 * ------------------------------------------------------------------------- */

/**
 * \brief Extracts a named entry from a ZIP archive into a newly allocated buffer.
 *
 * Opens the archive, searches the central directory for \p search_name
 * (case-insensitive, matching either the full entry name or its final
 * path component), reads the local file header and either copies the
 * stored data or inflates the deflated data into a malloc'd buffer.
 *
 * \param FileName    Path of the ZIP file.
 * \param search_name Name of the entry to extract (case-insensitive).
 * \param out_data    Receives a pointer to the malloc'd uncompressed data
 *                    (caller must free() it); untouched on error.
 * \param out_size    Receives the uncompressed size in bytes; untouched on error.
 * \return 0 on success, non-zero on error.
 */
int zip_extract_file(char *FileName, char *search_name, LPVOID *out_data, size_t *out_size);

/**
 * \brief Loads the central directory and local file headers of a ZIP archive.
 *
 * Opens the archive, locates the end-of-central-directory record and fills
 * zip_entry_names / zip_num_entries_loaded (and the Size[] array with the
 * uncompressed entry sizes) with the entries found.
 *
 * \param FileName Path of the ZIP file.
 * \return 0 on success, non-zero on error.
 */
int zip_load_file(char *FileName);
