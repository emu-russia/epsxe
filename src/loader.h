#pragma once

/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char active_mini_cheat_count;
extern unsigned char bios_image[0x80000];
extern unsigned char bios_name[0x800];
extern unsigned char cd_inc;
extern unsigned int cheat_entries_count;
extern unsigned int country_setting;
extern unsigned char default_filename[0x400];
extern unsigned int mini_cheat_attr_array[1];
extern unsigned int mini_cheat_count;
extern unsigned int mini_cheat_id_array[0x1f];
extern unsigned char noauto;
extern unsigned char nocdstatus;
extern unsigned char old_timing;
extern unsigned char parasite_eve_cheat;
extern unsigned char unknown_cd_setting;
extern unsigned int video_scanlines;
extern unsigned char zip_entry_names[0x10000];
extern unsigned int zip_num_entries_loaded;

/* Function prototypes (previously generated in src/_gen) */
char __cdecl loader_apply_mini_cheats(const char *a1);
int loader_cdrom_detect_region();
int loader_check_bios_file_exists();
void __cdecl loader_check_demo_header(FILE *Stream, int a2);
void loader_load_bios();
FILE *__cdecl loader_load_cheat_file(char *FileName);
FILE *loader_load_cheats();
int __cdecl loader_load_demo(char *FileName);
void __cdecl loader_load_file(char *a1, size_t Size);
void loader_load_zip();
char __cdecl loader_mini_cheat_find(int a1, int a2);
char __cdecl loader_mini_cheat_find_by_id(int a1, int a2);
char __cdecl loader_parse_cheat_entry(const char *a1, char *Buffer);
size_t __cdecl loader_pll_get_file_size(const char *a1);
int __cdecl loader_pll_parse_section(int a1, unsigned int *a2, unsigned int a3, const char *a4, int a5);
int __cdecl loader_set_bios_name(const char *a1);
int __cdecl loader_set_filename(const char *a1);
int loader_touch_demo_file();
