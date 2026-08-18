#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int FileHandle;
extern unsigned char byte_50A090;
extern unsigned char byte_50A091;
extern unsigned int cdrom_fake_data;
extern unsigned int dword_5056E0;

/* Function prototypes (previously generated in src/_gen) */
int __cdecl cdrom_fake_create_file(char *FileName);
int __cdecl cdrom_fake_load_file(char *FileName);
size_t __cdecl cdrom_fake_read_portion(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer);
FILE *cdrom_fake_write();
void *__cdecl cdrom_fake_write_portion(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer);
