#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int FileHandle;
extern unsigned char fake_file_version;
extern unsigned char fake_file_version2;
extern unsigned int cdrom_fake_data;
extern unsigned int fake_file_sector_offset;

/* Function prototypes (previously generated in src/_gen) */
int cdrom_fake_create_file(char *FileName);
int cdrom_fake_load_file(char *FileName);
size_t cdrom_fake_read_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer);
FILE *cdrom_fake_write();
void * cdrom_fake_write_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer);
