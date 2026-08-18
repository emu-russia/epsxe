#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int FileHandle;
extern unsigned char fake_file_version;
extern unsigned char fake_file_version2;
extern unsigned int cdrom_fake_data;
extern unsigned int fake_file_sector_offset;

/* Function prototypes (previously generated in src/_gen) */
int __cdecl cdrom_fake_create_file(char *FileName);
int __cdecl cdrom_fake_load_file(char *FileName);
size_t __cdecl cdrom_fake_read_portion(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer);
FILE *cdrom_fake_write();
void *__cdecl cdrom_fake_write_portion(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer);
