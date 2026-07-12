#pragma once

#pragma pack(push, 1)
typedef struct {
    uint32_t signature;                // +0  (0x02014b50 для центрального директория)
    uint8_t  version_made_by[2];       // +4, +5
    uint8_t  version_needed[2];        // +6, +7
    uint16_t general_purpose_flag;     // +8
    uint16_t compression_method;       // +10
    uint16_t last_mod_time;            // +12
    uint16_t last_mod_date;            // +14
    uint32_t crc32;                    // +16
    uint32_t compressed_size;          // +20
    uint32_t uncompressed_size;        // +24
    uint16_t file_name_length;         // +28
    uint16_t extra_field_length;       // +30
    uint16_t file_comment_length;      // +32
    uint16_t disk_number_start;        // +34
    uint16_t internal_attributes;      // +36
    uint32_t external_attributes;      // +40
    uint32_t relative_offset;          // +44   (смещение локального заголовка файла)
    const uint8_t* file_name;          // +48   (указатель на начало имени файла в исходном буфере)
} ZipCentralDirectoryEntry;
#pragma pack(pop)
