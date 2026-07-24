/**
 * PPF (PlayStation Patch File) Format - C++ Structure Definition
 * 
 * The PPF format is used to patch PlayStation CD/DVD ROM images.
 * Unlike IPS patches (limited to 16MB), PPF supports full CD (700MB)
 * and DVD (4.7GB) images with minimal patch size[reference:1].
 * 
 * Versions: PPF1.0, PPF2.0, PPF3.0[reference:2]
 * 
 * @see http://www.problemkaputt.de/psxspx-cdrom-patch-files.htm
 */

#pragma once

#pragma pack(push, 1)

// ============================================================================
// PPF Header Structures
// ============================================================================

/**
 * PPF Header - Common fields for all versions
 */
struct PPFHeaderCommon {
    char     id[5];              // "PPF10", "PPF20", or "PPF30"
    uint8_t  encodingMethod;     // 0=v1.0, 1=v2.0, 2=v3.0
    char     description[50];    // 50-char patch description, space-padded
};

/**
 * PPF Header v1.0
 * 
 * Offset | Size | Description
 * -------+------+-------------
 * 0x000  | 5    | ID ("PPF10")
 * 0x005  | 1    | Encoding Method (0)
 * 0x006  | 50   | Patch Description
 * 0x038  | ...  | Patch entries begin
 */
struct PPFHeaderV1 {
    char     id[5];              // "PPF10"
    uint8_t  encodingMethod;     // 0
    char     description[50];    // 50 chars, space-padded
    // Patch entries follow at offset 0x38
};

/**
 * PPF Header v2.0
 * 
 * Offset | Size | Description
 * -------+------+-------------
 * 0x000  | 5    | ID ("PPF20")
 * 0x005  | 1    | Encoding Method (usually 1)
 * 0x006  | 50   | Patch Description
 * 0x038  | 4    | Filesize of patched image (usually multiple of 0x930)
 * 0x03C  | 1024 | Validation data (from .BIN offset 0x9320)
 * 0x43C  | ...  | Patch entries begin
 */
struct PPFHeaderV2 {
    char     id[5];              // "PPF20"
    uint8_t  encodingMethod;     // 1
    char     description[50];    // 50 chars, space-padded
    uint32_t patchedFilesize;    // Size of patched image (multiple of 0x930h)
    uint8_t  validationData[0x400]; // 1024 bytes from offset 0x9320
    // Patch entries follow at offset 0x43C
};

/**
 * PPF Header v3.0
 * 
 * Offset | Size | Description
 * -------+------+-------------
 * 0x000  | 5    | ID ("PPF30")
 * 0x005  | 1    | Encoding Method (usually 2)
 * 0x006  | 50   | Patch Description
 * 0x038  | 1    | ImageType (0=BIN, 1=GI PrimoDVD)
 * 0x039  | 1    | ValidationDataPresent (0=No, 1=Yes)
 * 0x03A  | 1    | UndoDataPresent (0=No, 1=Yes)
 * 0x03B  | 1    | Dummy (unused, 0)
 * 0x03C  | 1024 | Validation data (optional, if ValidationDataPresent=1)
 *           ...  | Patch entries begin
 */
struct PPFHeaderV3 {
    char     id[5];                  // "PPF30"
    uint8_t  encodingMethod;         // 2
    char     description[50];        // 50 chars, space-padded
    uint8_t  imageType;              // 0=BIN, 1=GI PrimoDVD
    uint8_t  validationDataPresent;  // 0=No, 1=Yes
    uint8_t  undoDataPresent;        // 0=No, 1=Yes
    uint8_t  dummy;                  // Unused (0)
    uint8_t  validationData[0x400];  // Optional: from offset 0x9320 (BIN) or 0x80A0 (GI)
    // Patch entries follow
};

// ============================================================================
// PPF Patch Entry Structures
// ============================================================================

/**
 * PPF Patch Entry v1.0 / v2.0
 * 
 * Offset | Size | Description
 * -------+------+-------------
 * 0x000  | 4    | Offset (32-bit, good for CDROM up to ~4GB)
 * 0x004  | 1    | Length of new data (1-255 bytes)
 * 0x005  | LEN  | New data to write at offset
 * 
 * Note: v1.0 and v2.0 may differ in internal handling, but structure is identical.
 */
struct PPFPatchEntryV1V2 {
    uint32_t offset;     // Offset in target file to apply patch
    uint8_t  length;     // Length of new data (1-255 bytes)
    uint8_t  newData[1]; // Variable-length new data (length bytes)
};

/**
 * PPF Patch Entry v3.0
 * 
 * Offset | Size | Description
 * -------+------+-------------
 * 0x000  | 8    | Offset (64-bit, supports DVD images >4GB)
 * 0x008  | 1    | Length of new data (1-255 bytes)
 * 0x009  | LEN  | New data to write at offset
 * 0x009  |      | 
 *  +LEN  | LEN  | Old data (optional, if UndoDataPresent=1)
 * 
 * PPF3.0 uses 64-bit offsets to support DVD images and larger files[reference:3].
 */
struct PPFPatchEntryV3 {
    uint64_t offset;     // 64-bit offset (supports DVD >4GB)
    uint8_t  length;     // Length of new data (1-255 bytes)
    uint8_t  newData[1]; // Variable-length new data (length bytes)
    // Old data for undo follows immediately after newData
    // (if undoDataPresent flag is set in header)
};

// ============================================================================
// Optional Metadata Block (PPF v2.0 / v3.0)
// ============================================================================

/**
 * Optional FILE_ID.DIZ metadata block
 * 
 * Some PPF patches include a FILE_ID.DIZ description block at the end:
 * - ID "@BEGIN_FILE_ID.DIZ"
 * - ASCII text (max 3072 chars for v3.0, or variable for v2.0)
 * - ID "@END_FILE_ID.DIZ"
 * - Size field (v2.0: 4 bytes, v3.0: 2 bytes)
 */
struct PPFFileIdDiz {
    char     beginTag[12];    // "@BEGIN_FILE_ID.DIZ" (0x40 42 45 47 49 4E 5F 46 49 4C 45 5F 49 44 2E 44 49 5A)
    char     text[3072];      // ASCII description text (max 3072 chars for v3.0)
    char     endTag[10];      // "@END_FILE_ID.DIZ" (0x40 45 4E 44 5F 46 49 4C 45 5F 49 44 2E 44 49 5A)
    // Size field follows (v2.0: uint32_t, v3.0: uint16_t)
};

// ============================================================================
// Utility Constants
// ============================================================================

// PPF magic identifiers
#define PPF_ID_V1  "PPF10"
#define PPF_ID_V2  "PPF20"
#define PPF_ID_V3  "PPF30"

// Encoding methods
#define PPF_ENC_V1 0
#define PPF_ENC_V2 1
#define PPF_ENC_V3 2

// Image types (v3.0)
#define PPF_IMAGE_BIN         0
#define PPF_IMAGE_GI_PRIMODVD 1

// CDROM sector size (PPF expects 0x930-byte sectors)
#define PPF_SECTOR_SIZE 0x930

// Validation data offsets
#define PPF_VALIDATION_OFFSET_BIN    0x9320
#define PPF_VALIDATION_OFFSET_GI     0x80A0

#pragma pack(pop)
