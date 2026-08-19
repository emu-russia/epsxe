#pragma once
/* Decompiled globals (previously generated in src/_gen) */

/* Function prototypes (previously generated in src/_gen) */
int cdrom_fake_create_file(char *FileName);
int cdrom_fake_load_file(char *FileName);
size_t cdrom_fake_read_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer);
FILE *cdrom_fake_write();
void * cdrom_fake_write_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer);
