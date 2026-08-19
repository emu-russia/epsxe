#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char system_cnf_buffer[1];
extern unsigned char system_cnf_buffer_8[0xff8];
extern unsigned char root_directory_buffer[0x800];
extern unsigned char root_directory_buffer_2[0x800];

/* Function prototypes (previously generated in src/_gen) */
int *__cdecl cdfs_find_file(const char *a1, int *a2, int **a3);
unsigned __int8 __cdecl cdfs_load_executable(char *Buffer);
unsigned __int8 __cdecl cdfs_parse_system_cnf_for_exec(int a1, int a2, char *Buffer, int *a4, int **a5);
unsigned int __cdecl cdfs_read_data(int a1, int a2, unsigned int a3, void *a4);
int __cdecl cdfs_read_le32(unsigned __int8 *a1);
char *cdfs_read_root_directory();
